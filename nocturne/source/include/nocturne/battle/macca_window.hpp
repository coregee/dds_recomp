// The battle's Macca window (original unit: nbMakaProcess, the "nb_maka"
// process), as far as rewritten: shown while a demon asks for Macca.
#pragma once

#include <cstdint>

namespace nocturne::nb {

// nbMakaProcessData_t (the process's data).
struct MaccaWindow {
    int32_t state;        // 1 opening, 2 closing (HD: stat)
    int32_t macca;        // the amount shown (HD: oldmaka)
    int32_t open;         // nonzero while shown (HD: disp)
    int32_t x, y;         // where it goes (HD: targetx, targety)
    int32_t basex, basey;
    int32_t keep;         // nonzero: shown where it was, closed at once (HD: type)
    float ritu;
    int32_t closeframes;  // (HD: offtime)
    int32_t alpha;        // 0..0x80
};
static_assert(sizeof(MaccaWindow) == 0x2c);

MaccaWindow* maccaWindow();          // GetMakaProcessData: none without the process
void showMacca(int32_t keep);        // nbMakaDispOn: the player's Macca
void hideMacca();                    // nbMakaDispOff

// The process ("nb_maka"): started by the battle, its window fading in
// (state 1) and out (state 2) by 0x20 and 0x14 a frame.
uint32_t startMaccaWindow(uint32_t parent);   // nbInitMakaProcess: the process, a child of `parent` (if any)
uint32_t newMaccaWindow();                    // InitMakaProcessData: the record (Macca on hand)
uint32_t runMaccaWindow(uint32_t process);    // nbMakaProcess1: a frame
void shutdownMaccaWindow(uint32_t process);   // nbMakaShutdown
void stepMaccaWindow(MaccaWindow& w);         // (0x28F600) the fade
// DispMaka: the window at x, y (panel units) and the Macca on hand, seven
// digits without leading zeros.
void drawMaccaWindow(MaccaWindow& w, int32_t x, int32_t y, uint32_t color, uint32_t alpha);
int32_t maccaDigit(int32_t value, int32_t place);   // (0x28F2F8) the digit at 10^place

} // namespace nocturne::nb
