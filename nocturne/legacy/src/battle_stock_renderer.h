#ifndef NOCTURNE_BATTLE_STOCK_RENDERER_H
#define NOCTURNE_BATTLE_STOCK_RENDERER_H
#include <stdint.h>
void ps2BattleDrawEmptyPartyRow(uint64_t x,uint64_t y,uint64_t main);
void nbPanelDrawPP1(uint64_t x,uint64_t y,uint64_t form,uint64_t unit,uint64_t ordinal,uint64_t selected,uint64_t main);
void nbPanelDrawPP(uint64_t x,uint64_t y,uint64_t selected,uint64_t unit,uint64_t mask);
uint64_t nbPanelStockSelect(uint64_t main,uint64_t allow_input);
void nbPanelPartyDraw(void);
#endif
