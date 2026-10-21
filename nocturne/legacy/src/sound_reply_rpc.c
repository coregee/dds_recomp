#include "sound_reply_rpc.h"
#include "sound_bank_support.h"
#include "file_device.h"
#include "file_worker_control.h"
#include "file_loader_support.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "script_construction.h"
#include <string.h>

/* Descriptive roles, checked against the original GP=00554170 instructions.
 * Native request fields +8/+C are IOP destination and requested byte count.
 * The reply is one shared word; a rejected selector leaves its old value. */
enum {
    STREAM_CALLBACK = 0x5519c4, FILE_BUSY = 0x5519c8,
    CALLBACK_BUSY = 0x5519cc, REQUEST = 0x552124,
    STREAM_OFFSET = 0x552128, FILE_JOB = 0x55212c,
    FILE_SEMAPHORE = 0x552140, STREAM_BUFFER = 0x593f28,
    REPLY = 0x593f40, FILENAME = 0x529be8
};
static void *at(uint32_t address) { return nocturneResolveScriptConstructionAddress(address); }
static uint32_t word(uint32_t address) { uint32_t value; memcpy(&value, at(address), 4); return value; }
static void put(uint32_t address, uint32_t value) { memcpy(at(address), &value, 4); }
static uint64_t sx(uint32_t value) { return (uint64_t)(int64_t)(int32_t)value; }
static void wait_for_file(void) { nocturneSoundReplyWaitSemaphore(sx(word(FILE_SEMAPHORE))); }

/* 002C2338: all nine original switch arms, including the common reply address.
 * This readable C candidate preserves semantic memory/call order. Native frame
 * saves, volatile banks and physical IOP completion need separate validation. */
uint32_t ps2SoundRpcReplyCandidate(uint64_t command, uint64_t request)
{
    if (command >= UINT64_C(9)) return REPLY;
    switch ((uint32_t)command) {
    case 0: {
        uint32_t job = 0;
        if (*(const int8_t *)at(FILENAME) != 0) {
            uint8_t path[256];
            uint32_t guest = nocturneSoundReplyBeginFrame(path, sizeof(path));
            put(FILE_BUSY, 1);
            (void)ps2SoundBuildPath(sx(guest), sx(FILENAME));
            job = (uint32_t)ps2FileRequestRead(sx(guest), UINT64_C(0x2c22e0), 0);
            put(FILE_JOB, job);
            if (job) {
                wait_for_file();
                job = word(FILE_JOB);
                if (word(job + 0x2c) != 0) {
                    (void)ps2FileCommandRetry(sx(job));
                    (void)ps2FileJobReleaseIfTerminal(sx(word(FILE_JOB)));
                    put(FILE_JOB, 0);
                    job = 0;
                }
            }
            nocturneSoundReplyEndFrame();
        }
        put(REPLY, job);
        break;
    }
    case 1: {
        int32_t requested = (int32_t)word((uint32_t)request + 0xc);
        put(REQUEST, (uint32_t)request);
        uint32_t handle = ps2MemoryHandleAllocate(requested);
        uint32_t buffer = ps2MemoryHandleAcquirePointer(handle);
        uint32_t current = word(REQUEST); /* Native BEQ delay executes even for a null buffer. */
        if (buffer) {
            uint32_t file_job = word(FILE_JOB);
            uint32_t bytes = word(current + 0xc);
            (void)ps2FileCommandRead(sx(file_job), sx(buffer), sx(bytes));
            wait_for_file();
            current = word(REQUEST);
            uint32_t destination = word(current + 8);
            bytes = word(current + 0xc);
            nocturneSoundReplyDmaToIop(sx(destination), sx(buffer), sx(bytes));
            ps2MemoryHandleFree(handle);
            current = word(REQUEST);
            bytes = word(current + 0xc);
            put(REPLY, bytes);
        } else put(REPLY, 0);
        break;
    }
    case 2:
        (void)ps2FileCommandClose(sx(word(FILE_JOB)));
        wait_for_file();
        (void)ps2FileJobReleaseIfTerminal(sx(word(FILE_JOB)));
        put(FILE_JOB, 0);
        put(FILE_BUSY, 0);
        put(REPLY, 0);
        break;
    case 3:
        put(STREAM_OFFSET, 0);
        put(REPLY, 0);
        break;
    case 4: {
        uint32_t offset = word(STREAM_OFFSET);
        uint32_t source = word(STREAM_BUFFER);
        uint64_t destination = sx(word((uint32_t)request + 8));
        uint64_t bytes = sx(word((uint32_t)request + 0xc));
        source += offset;
        put(REQUEST, (uint32_t)request);
        nocturneSoundReplyDmaToIop(destination, sx(source), bytes);
        uint32_t current = word(REQUEST);
        offset = word(STREAM_OFFSET);
        uint32_t count = word(current + 0xc);
        uint32_t next = offset + count;
        put(REPLY, count);
        put(STREAM_OFFSET, next);
        break;
    }
    case 5:
        put(REPLY, 0);
        break;
    case 6: {
        uint32_t callback = word(STREAM_CALLBACK);
        if (callback) put(CALLBACK_BUSY, 1);
        put(REPLY, callback);
        break;
    }
    case 7: {
        put(REQUEST, (uint32_t)request);
        uint32_t callback = word(STREAM_CALLBACK);
        uint32_t bytes = word((uint32_t)request + 0xc);
        uint64_t source = nocturneSoundReplyInvokeBufferCallback(callback, sx(bytes));
        uint32_t current = word(REQUEST); /* Native BEQ delay executes on both paths. */
        if (source) {
            bytes = word(current + 0xc);
            uint32_t destination = word(current + 8);
            nocturneSoundReplyDmaToIop(sx(destination), source, sx(bytes));
            current = word(REQUEST);
            bytes = word(current + 0xc);
            put(REPLY, bytes);
        } else put(REPLY, UINT32_MAX);
        break;
    }
    case 8:
        put(CALLBACK_BUSY, 0);
        put(REPLY, 0);
        break;
    }
    return REPLY;
}
