// The next area's pack (original unit: the field's area loader, around
// 0x127378): an area's .LB file, loaded ahead while the battle's result
// screen shows. Names are descriptive; the original's are lost.
#pragma once

#include <cstdint>

namespace nocturne::fld {

// The loader's state (0x2FBF80, partial).
struct AreaLoadState {
    uint8_t unknown_00[4];
    int32_t currentMajor, currentMinor;   // the area being played (tentative)
    uint8_t unknown_0c[0x78];
    int32_t loading;   // 1 while the next area's pack loads
    int32_t major;     // the area it loads (f<major>_<minor>.LB)
    int32_t minor;
};
static_assert(sizeof(AreaLoadState) == 0x90);

AreaLoadState& areaLoadState();

// (0x128408) the folder an area's files are in: /fld/f/ below 200,
// /fld/b/ below 500, else /fld/e/, then f<major>/; into `out`.
void areaFolder(uint32_t out, int32_t major);
// (0x127510) the pack let go (its handles first), and nothing next.
void releaseNextArea();
// (0x127580) a loading pack checked: done, the loading stops. Always 0.
int32_t pollNextArea();
// ps2FieldNextLoadStatus (0x1275D0): 1 while loading.
int32_t nextAreaLoading();
// (0x127368) the area to load next.
void setNextArea(int32_t major, int32_t minor);
// (0x1275E0) the next area's pack is in, or on its way.
bool nextAreaPending();
// (0x127620) the same, for the area major/minor only.
bool nextAreaPendingFor(int32_t major, int32_t minor);
// (0x127688, 0x127700, 0x127778) part 0, 1 or 2 of the loaded pack, for
// area major/minor: copied into a new memory handle (returned; its memory
// at *out), or 0 for another area.
uint32_t copyAreaPart(int32_t part, uint32_t out, int32_t major, int32_t minor);

// (0x1221F0) the field's work memory (0x54EB00) let go (tentative).
void releaseFieldWork();

// ---- the current area's shared pack ----
// (0x1277F0) its file name, into `out`: f<area>_000.LB, but for areas 24,
// 25 and 34 a variant (_00b, _00c, _00d) by story flags or the area's
// minor number.
void areaPackName(uint32_t out);
// (0x1279B8) the name differs from the pack held.
bool areaPackChanged();
// (0x127B70) the pack and its memory let go, and no name held.
void releaseAreaPack();

} // namespace nocturne::fld
