// US Maniax's addresses in the version under test, for the harness.
//
// The tests name the original's functions and data by their US Maniax
// addresses (hooks, interpreted ranges, entry points, static memory). For
// another build (Chronicle, Vanilla) this maps them through
// reference/versions/<name>-function-map.tsv and -data-map.tsv
// (tools/match_functions.py, tools/match_data.py); for US Maniax and
// Hardtype every address is its own. The rewrite's addresses are already
// the version's (nocturne/address.hpp).
#pragma once

#include <cstdint>

namespace difftest::version {

// Reads the maps, found above the executable's folder; false if missing.
bool load(const char* elfPath);
bool active();   // a build at other addresses than US Maniax
uint32_t globalPointer();   // gp, as the entry point sets it (from the executable's .reginfo)

// The JP builds' font and message engine (Japanese text) isn't ported yet:
// a test that sets up the US one throws this there, and counts as pending.
struct UsTextOnly {};
void requireUsText();

// The version's address for a US Maniax one; 0 if it has none.
uint32_t code(uint32_t maniax);         // a function's start, or a place in one that matched
uint32_t codeBegin(uint32_t maniax);    // the start of an interpreted range (else the next function's)
uint32_t codeEnd(uint32_t maniax);      // the end of an interpreted range
uint32_t data(uint32_t maniax);
uint32_t functionSize(uint32_t maniax);   // a US Maniax function's size in bytes (0 if unknown)
// ... and back: the US Maniax address for one of the version's (0 if none).
uint32_t maniax(uint32_t address);
// The same for a code address read from the version's own memory (a
// function pointer), to hand to what takes US Maniax's addresses; throws
// NoCounterpart (with the version's address) when there is none.
uint32_t maniaxCodeOrDie(uint32_t address);

// code() and data() that throw NoCounterpart when there is none: the test
// counts as pending (main.cpp).
struct NoCounterpart {
    uint32_t maniax;
    bool code;
};
uint32_t codeOrDie(uint32_t maniax);
uint32_t dataOrDie(uint32_t maniax);

} // namespace difftest::version

// For the fake world (C): the US Maniax address of one of the version's.
extern "C" uint32_t fw_maniax_address(uint32_t address);
