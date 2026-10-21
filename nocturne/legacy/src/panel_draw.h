#ifndef NOCTURNE_PANEL_DRAW_H
#define NOCTURNE_PANEL_DRAW_H
#include <stdint.h>
uint64_t ps2TextureGetFilterRegister(uint64_t texture);
uint64_t ps2TextureGetWrapRegister(uint64_t texture);
uint64_t ps2PanelTexturePacketSize(void);
uint64_t ps2PanelBuildTexturePacket(uint64_t dst,uint64_t texture,uint64_t context);
uint64_t ps2PanelAppendTexturePacket(uint64_t chain,uint64_t texture,uint64_t context);
uint64_t ps2PanelBuildInlineBytePacket(uint64_t dst,uint64_t bytes);
uint64_t ps2PanelPackedPacketSize(uint64_t registers,uint64_t loops);
uint64_t ps2PanelPacketPayload(uint64_t packet);
uint64_t ps2PanelBuildPackedTag(uint64_t dst,uint64_t primitive,uint64_t registers,uint64_t descriptor,uint64_t loops);
void ps2PanelDrawColoredFan4(uint64_t vertices,uint64_t colors,uint64_t vertexIndices,uint64_t colorIndices,uint64_t depth,uint64_t chain);
void ps2PanelDrawColoredStrip(uint64_t vertices,uint64_t colors,uint64_t vertexIndices,uint64_t colorIndices,uint64_t count,uint64_t depth,uint64_t chain);
void ps2PanelDrawColoredLineStrip(uint64_t vertices,uint64_t colors,uint64_t vertexIndices,uint64_t colorIndices,uint64_t count,uint64_t depth,uint64_t chain);
void ps2PanelDrawTexturedSprite(uint64_t rect,uint64_t uv,uint64_t color,uint64_t depth,uint64_t texture,uint64_t context,uint64_t chain);
void ps2PanelDrawSprite(uint64_t rect,uint64_t uv,uint64_t color,uint64_t depth,uint64_t context,uint64_t chain);
void ps2PanelAppendAlphaPacket(uint64_t chain,uint64_t type,uint64_t context);
void ps2PanelDrawNormal(uint64_t panel,uint64_t chain);
void ps2PanelDrawMessage(uint64_t panel,uint64_t chain);
void ps2PanelDrawSelection(uint64_t panel,uint64_t chain);
void ps2PanelDrawPlain(uint64_t panel,uint64_t chain);
void ps2PanelDrawLeftFade(uint64_t panel,uint64_t chain);
void ps2PanelDrawFacility(uint64_t panel,uint64_t chain);
void ps2PanelDrawMessage2(uint64_t panel,uint64_t chain);
void ps2PanelDrawSpeaker2(uint64_t panel,uint64_t chain);
void ps2PanelDrawPera(uint64_t panel,uint64_t chain);
void itfPnlDraw(uint64_t panel,uint64_t chain);
#endif
