#pragma once
#include <stddef.h>
#include <stdint.h>
#include "sound_worker_protocol.h"

/* Original callback reads only +8/+C. The first two wire words remain opaque. */
typedef struct NocturneSoundRpcRequest32 {
    uint32_t unknown0, unknown4, iop_destination, requested_bytes;
} NocturneSoundRpcRequest32;
_Static_assert(sizeof(NocturneSoundRpcRequest32) == 16, "native reply request prefix");
_Static_assert(offsetof(NocturneSoundRpcRequest32, iop_destination) == 8, "native IOP destination");
_Static_assert(offsetof(NocturneSoundRpcRequest32, requested_bytes) == 12, "native requested bytes");

/* Source reconstruction candidate for 002C2338. Not in the canonical build.
 * Two actual integer inputs; the RPC size argument is not read by this body.
 * This semantic interface does not expose the whole native register bank. */
uint32_t ps2SoundRpcReplyCandidate(uint64_t command, uint64_t request);

/* Unprovided services remain explicit. Implementations must execute their real
 * dependencies or stop; none may manufacture a successful response. */
void nocturneSoundReplyWaitSemaphore(uint64_t semaphore); /* 002DBEE0 */
void nocturneSoundReplyDmaToIop(uint64_t destination, uint64_t source, uint64_t bytes); /* 002C1278 */
uint64_t nocturneSoundReplyInvokeBufferCallback(uint32_t callback, uint64_t bytes);
uint32_t nocturneSoundReplyBeginFrame(void *buffer, uint32_t bytes);
void nocturneSoundReplyEndFrame(void);
