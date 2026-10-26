// The next area's pack (original unit: the field's area loader, around
// 0x127378). Rewritten from the original instructions; the start of a load
// (0x127378) builds its path on the stack and is not rewritten yet.
#include "nocturne/field/next_area.hpp"

#include <cstdio>
#include <cstring>

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::fld {

namespace {

constexpr uint32_t kState = addr(0x002fbf80);
constexpr uint32_t kNextMajor = addr(0x0054ebf4), kNextMinor = addr(0x0054ebf8);   // int32: the area to load next
constexpr uint32_t kNextPack = addr(0x0054ebb8);   // its PAC request
constexpr uint32_t kAreaPack = addr(0x0054ebb0);   // the current area's shared pack (PAC request)
constexpr uint32_t kAreaPackMemory = addr(0x0054ebc8);   // ... a memory handle from it
constexpr uint32_t kHeldName = addr(0x0055dab8);   // char[]: the name of the pack held
constexpr uint32_t kEmptyString = addr(0x0054ec00);
constexpr uint32_t kPartData = addr(0x0054ebdc);   // uint32[3]: the loaded pack's three parts
constexpr uint32_t kPartSize = addr(0x0054ebe8);   // int32[3]: ... their sizes

int32_t& word(uint32_t address) { return *guest::table<int32_t>(address); }

void folderFor(char (&out)[16], int32_t major)
{
    const char* format = major < 200 ? "/fld/f/f%03d/" : major < 500 ? "/fld/b/f%03d/" : "/fld/e/f%03d/";
    std::snprintf(out, sizeof out, format, major);
}

// The shared pack's suffix (000, 00b, 00c, 00d) for the current area.
const char* packVariant(int32_t major, int32_t minor)
{
    const int32_t step = minor + 1;
    if (major == 25) {
        if (evt::BitCheck(0x599) && !evt::BitCheck(0x743))
            return "00c";
        if (step >= 17)
            return "00b";
    }
    if (major == 24) {
        if (evt::BitCheck(0x4f))
            return "00b";
        if (evt::BitCheck(0x16) && !evt::BitCheck(0x3e))
            return "00c";
    }
    if (major == 34) {
        if (step < 4) return "000";
        if (step < 11) return "00b";
        if (step < 19) return "00c";
        if (step < 26) return "00d";
    }
    return "000";
}

void buildPackName(char (&out)[32])
{
    const AreaLoadState& state = areaLoadState();
    char folder[16];
    folderFor(folder, state.currentMajor);
    std::snprintf(out, sizeof out, "%sf%03d_%s.LB", folder, state.currentMajor, packVariant(state.currentMajor, state.currentMinor));
}

} // namespace

AreaLoadState& areaLoadState() { return *guest::table<AreaLoadState>(kState); }

// 0x00128408 (no original name)
void areaFolder(uint32_t out, int32_t major)
{
    char folder[16];
    folderFor(folder, major);
    std::memcpy(guest::table<char>(out), folder, std::strlen(folder) + 1);
}

// 0x00127510 (no original name): the pack's memory handles (a list at
// +0x60, each node's handle at +8) are released, then the request.
void releaseNextArea()
{
    if (const uint32_t pack = static_cast<uint32_t>(word(kNextPack))) {
        for (uint32_t node = *guest::table<const uint32_t>(pack + 0x60); node != 0;
             node = *guest::table<const uint32_t>(node)) {
            mem::HandleDeferredRelease(*guest::table<const uint32_t>(node + 8));
        }
        file::PacRequestFree(static_cast<uint32_t>(word(kNextPack)));
        word(kNextPack) = 0;
    }
    word(kNextMajor) = 0;
    word(kNextMinor) = 0;
    AreaLoadState& state = areaLoadState();
    state.loading = 0;
    state.major = 0;
    state.minor = 0;
}

// 0x00127580 (no original name)
int32_t pollNextArea()
{
    AreaLoadState& state = areaLoadState();
    if (state.loading == 1 && file::PacCheckEnd(static_cast<uint32_t>(word(kNextPack))))
        state.loading = 0;
    return 0;
}

// ps2FieldNextLoadStatus_001275D0
int32_t nextAreaLoading() { return areaLoadState().loading; }

// 0x001277F0 (no original name)
void areaPackName(uint32_t out)
{
    char name[32];
    buildPackName(name);
    std::memcpy(guest::table<char>(out), name, std::strlen(name) + 1);
}

// 0x001279B8 (no original name)
bool areaPackChanged()
{
    char name[32];
    buildPackName(name);
    return std::strcmp(guest::table<const char>(kHeldName), name) != 0;
}

// 0x00127B70 (no original name)
void releaseAreaPack()
{
    if (const uint32_t memory = static_cast<uint32_t>(word(kAreaPackMemory))) {
        mem::HandleDeferredRelease(memory);
        word(kAreaPackMemory) = 0;
    }
    if (const uint32_t pack = static_cast<uint32_t>(word(kAreaPack))) {
        file::PacRequestFree(pack);
        word(kAreaPack) = 0;
    }
    *guest::table<char>(kHeldName) = *guest::table<const char>(kEmptyString);
}

// 0x00127368 (no original name)
void setNextArea(int32_t major, int32_t minor)
{
    word(kNextMajor) = major;
    word(kNextMinor) = minor;
}

// 0x001275E0 (no original name)
bool nextAreaPending()
{
    const uint32_t pack = static_cast<uint32_t>(word(kNextPack));
    if (pack != 0 && file::PacCheckEnd(pack))
        return true;
    return areaLoadState().loading != 0;
}

// 0x00127620 (no original name)
bool nextAreaPendingFor(int32_t major, int32_t minor)
{
    const AreaLoadState& state = areaLoadState();
    if (state.major != major || state.minor != minor)
        return false;
    return nextAreaPending();
}

// 0x00127688, 0x00127700, 0x00127778 (no original names): one function
// for each part.
uint32_t copyAreaPart(int32_t part, uint32_t out, int32_t major, int32_t minor)
{
    const AreaLoadState& state = areaLoadState();
    if (state.major != major || state.minor != minor)
        return 0;
    const int32_t size = word(kPartSize + 4 * static_cast<uint32_t>(part));
    const uint32_t handle = mem::HandleAllocate(size);
    const uint32_t memory = mem::HandleAcquirePointer(handle);
    *guest::table<uint32_t>(out) = memory;
    std::memcpy(guest::table<uint8_t>(memory),
                guest::table<const uint8_t>(static_cast<uint32_t>(word(kPartData + 4 * static_cast<uint32_t>(part)))),
                static_cast<uint32_t>(size));
    return handle;
}

} // namespace nocturne::fld
