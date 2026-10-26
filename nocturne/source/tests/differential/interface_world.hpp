// The world around the interface code (messages, fonts): the original
// instructions run by the EE interpreter, the game's fonts and message
// tables, and generators for their state. Shared by message_tests.cpp and
// font_tests.cpp.
#pragma once

#include <cstdint>
#include <initializer_list>
#include <array>
#include <vector>

#include "harness.hpp"
#include "nocturne/interface/font.hpp"

namespace difftest::iface {

// Runs an original function (32-bit results sign-extended, like norm()).
uint64_t orig(uint32_t entry, std::initializer_list<uint64_t> args);
uint64_t origVoid(uint32_t entry, std::initializer_list<uint64_t> args);
// The same with the script VM's own functions run as original code.
uint64_t origVm(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> floatArgs = {});
uint64_t origVmVoid(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> floatArgs = {});
uint32_t origVmFloat();   // the float result (f0) of the last origVm
// A function that takes vectors in vf10 (and vf11) and leaves one in vf10.
std::array<uint32_t, 4> origVmVector(uint32_t entry, const uint32_t (&vf10)[4], const uint32_t (&vf11)[4]);
// A function's own instructions where the harness hooks it to a fake (its
// callers see the fake; this tests the function itself), and those of the
// hooked callees it calls.
uint64_t origOwn(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> callees = {});
// The entries above are US Maniax's addresses (mapped for another build,
// version_map.hpp); these take the version's own, for the bridges the
// rewrite calls with addresses it read or formed.
uint64_t origVmAt(uint32_t entry, std::initializer_list<uint64_t> args);
uint64_t origVmVoidAt(uint32_t entry, std::initializer_list<uint64_t> args);
uint64_t interpretedCalls();   // calls into the original instructions so far

inline uint32_t addr(const void* p) { return p ? fw_address_of(p) : 0; }
inline uint64_t A(const void* p) { return addr(p); }
inline uint64_t I(int32_t v) { return sx(v); }

// Message tables (English script messages) and the fonts, from the disc.
void loadData(const char* elfPath);
const std::vector<std::vector<uint8_t>>& messageTables();
const std::vector<std::vector<uint8_t>>& scriptFiles();   // a few .bf files

// Fonts loaded into styles 0..3 (and sometimes 8), pools, texture cells,
// font settings, {var n} strings and the entered names.
void fontWorld(Gen& g);

// A page of text to lay out: from the current message table when one is
// loaded (FW_MES_TABLE, relocated), or a made-up one. Only characters the
// fonts have.
uint32_t someText(Gen& g);

// A string in guest memory (from the fakes' pool).
uint32_t guestString(const char* s);

// A chain laid out by the rewrite, for state.
nocturne::fr::Request* chain(Gen& g, int32_t x, int32_t y);

// Puts a message table at FW_MES_TABLE, relocated or not.
void loadTable(Gen& g, bool relocate);

// The battle's help line (nocturne/battle/help.hpp): fonts, a message window
// on a table with messages at each of `needed`, and the help record at
// FW_HELP showing something. Built on top of the caller's world (it only
// takes from the fakes' pool).
struct HelpWorld {
    int32_t id;                      // the window
    std::vector<int32_t> messages;   // the table's messages (not selections)
};
HelpWorld helpWorld(Gen& g, std::initializer_list<int32_t> needed = {});
// Whether some message table helpWorld can choose has messages at all these indexes.
bool messageTableHas(std::initializer_list<int32_t> needed);

} // namespace difftest::iface
