#ifndef NOCTURNE_MESSAGE_FRAME_DRAW_H
#define NOCTURNE_MESSAGE_FRAME_DRAW_H
#include <stdint.h>
uint64_t ps2FontSwapColorBytes(uint64_t value);
void ps2FontCreateDrawPacket(uint64_t x,uint64_t y,uint64_t width,uint64_t height,uint64_t colorIndex,uint64_t color,uint64_t depth,uint64_t mode,uint64_t uv,uint64_t params,uint64_t ot);
uint64_t frDrawEffect(uint64_t font,uint64_t text,uint64_t alphaDelay,uint64_t drawSpeed);
uint64_t frDrawFont(uint64_t font);
uint64_t frDrawFontEx(uint64_t font,uint64_t mode);
uint64_t frDrawFontEx2(uint64_t font,uint64_t mode,uint64_t ot);
void ps2PanelDrawFlatSprite(uint64_t rect,uint64_t color,uint64_t depth,uint64_t context,uint64_t chain);
void ps2PanelSubmitDraw(uint64_t panel,uint64_t ot);
void ps2PanelAppendDrawState(uint64_t chain);
void ps2MessageMarkSelectionText(uint64_t font,uint64_t first,uint64_t last,uint64_t mode);
void ps2MessageDrawFlow(uint64_t instance);
void ps2MessageDrawWindow(uint64_t instance);
void ps2MessageDrawSelectionCursor(uint64_t instance);
void ps2MessageDrawWaitCursor(uint64_t instance);
void ps2MessageDebugDrawWindow(uint64_t panel);
/* Translate an original callback word to its actual recovered implementation. */
void nocturneInvokeMessageDrawOrder(uint32_t target,uint64_t ot,uint64_t tag);
#endif
