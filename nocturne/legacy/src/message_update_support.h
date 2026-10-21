#ifndef NOCTURNE_MESSAGE_UPDATE_SUPPORT_H
#define NOCTURNE_MESSAGE_UPDATE_SUPPORT_H
#include <stdint.h>
void itfPnlSetPositionOffset(uint64_t panel,uint64_t x0,uint64_t y0,uint64_t x1,uint64_t y1,uint64_t z);
uint64_t ps2MessageUnchainFontUnit(uint64_t font,uint64_t index,uint64_t lines);
void ps2MessageChangeFontPosition(uint64_t font,uint64_t x,uint64_t y);
void ps2MessageChangeFontColorAll(uint64_t font,uint64_t color);
void ps2MessageChangeFontAlpha(uint64_t font,uint64_t alpha);
uint64_t ps2MessageGetMaskedIndex(uint64_t index,uint64_t mask);
void ps2MessageRaiseSpeedAll(uint64_t font);
void ps2MessageForceCursor(uint64_t cursor,uint64_t phase,uint64_t alpha,uint64_t expansion);
void ps2MessageCalcWindow(uint64_t instance);
void ps2MessageSlide(uint64_t instance,uint64_t y);
uint64_t ps2MessageSelectDefaultKey(uint64_t selection);
void ps2MessageCalcCursor(uint64_t instance);
uint64_t ps2MessageDrawPauseCheck(void);
uint64_t ps2MessageDrawManager(void);
#endif
