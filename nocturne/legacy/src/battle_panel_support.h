#ifndef NOCTURNE_BATTLE_PANEL_SUPPORT_H
#define NOCTURNE_BATTLE_PANEL_SUPPORT_H
#include <stdint.h>
uint64_t effColorMultiply(uint64_t first,uint64_t second);
void ps2FontSetSize(uint64_t size);
void frSetFontColor(uint64_t font,uint64_t color);
uint64_t ps2FontBuildDrawString(uint64_t x,uint64_t y,uint64_t z,uint64_t color,uint64_t text,uint64_t prior);
uint64_t ps2FontBuildPanelString(uint64_t x,uint64_t y,uint64_t z,uint64_t color,uint64_t text,uint64_t prior);
void ps2BattlePanelSetPrimitive(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
void ps2BattlePanelSetAlpha(uint64_t mode);
void ps2BattlePanelDrawTexturedRect(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
void nbPanelBaseColorSet(uint64_t color);
void ps2BattlePanelDrawNumber(uint64_t x,uint64_t y,uint64_t layout,uint64_t color,uint64_t text);
void ps2BattlePanelDrawName(uint64_t x,uint64_t y,uint64_t layout,uint64_t color,uint64_t unit);
uint64_t nbPanelHPColor(uint64_t unit);
uint64_t nbPanelMPColor(uint64_t unit);
void ps2BattlePanelDrawCursorGradient(uint64_t x,uint64_t y);
uint64_t nbPanelStockSelectCtrl(void);
void ps2DrawBuildColoredQuadPacket(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
void ps2DrawAppendColoredQuadPacket(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
uint64_t ps2PanelCreateTexturedSpritePacket(uint64_t loops);
uint32_t sdfSinBits(uint32_t radians);
/* CPU transport/indirect-call boundaries. These do not replace game results. */
void EE_BATTLE_PANEL_COLOR_QMTC2(uint32_t low);
uint64_t nocturneBattlePanelAllocate(uint32_t target,uint64_t bytes);
void *nocturneResolveBattlePanelSupportAddress(uint32_t address);
#endif
