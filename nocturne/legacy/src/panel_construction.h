#ifndef NOCTURNE_PANEL_CONSTRUCTION_H
#define NOCTURNE_PANEL_CONSTRUCTION_H
#include <stdint.h>
void *nocturneResolvePanelConstructionAddress(uint32_t address);
uint64_t itfPnlRegist2(uint64_t type,uint64_t texture);
void itfPnlSetPosition(uint64_t panel,uint64_t x0,uint64_t y0,uint64_t x1,uint64_t y1,uint64_t z);
void itfPnlSetColor(uint64_t panel,uint64_t red,uint64_t green,uint64_t blue,uint64_t alpha);
void ps2MessageOpenPanel(uint64_t instance);
void ps2MessageOpenSpeakerPanel(uint64_t instance);
void ps2PanelScaleColors(uint64_t out,uint64_t red,uint64_t green,uint64_t blue,uint64_t alpha,uint64_t ratios,uint64_t count);
void ps2PanelVertexNormal(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelVertexMessage(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelVertexSelection(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelVertexPlain(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelVertexFacility(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelVertexPera(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelColorNormal(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelColorMessage(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelColorSelection(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelColorPlain(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelColorLeftFade(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelColorFacility(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
void ps2PanelColorPera(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d);
#endif
