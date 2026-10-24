// Window panels (original unit: itfPanel): the backgrounds of message,
// selection and shop windows. A panel keeps its rectangle and colour and,
// in a work block of its type, the vertices and vertex colours it is drawn
// with; each type builds them its own way.
//
// Records are in their PS2 layout; field names are the HD remaster's.
// Positions are in 1/16 pixels.
#pragma once

#include <cstddef>
#include <cstdint>

namespace nocturne::itf {

// ITF_PANEL_TYPE
enum PanelType : int32_t {
    kPanelNormal = 0,
    kPanelMesWin = 1,     // a message window with rounded corners
    kPanelSelWin = 2,     // a selection window
    kPanelPlain = 3,
    kPanelPera1 = 4,
    kPanelLeftFade = 5,   // fades in from the left over 90 pixels
    kPanelMesWin2 = 6,    // textured; drawn from the texture alone
    kPanelSpkWin2 = 7,    // the speaker's name, textured
    kPanelFacility = 8,   // a shop window, full width, textured
};

// itfpanel_t: a window background.
struct Panel {
    uint32_t handle, workhandle;   // memory handles of the panel and its work
    uint32_t pwork;
    uint32_t z;
    int32_t pos[4];                // x0, y0, x1, y1
    int32_t color[4];              // r, g, b, alpha
    uint8_t type;
};
static_assert(offsetof(Panel, color) == 0x20 && offsetof(Panel, type) == 0x30);

struct PanelVertex {
    int32_t x, y;
};

struct PanelColor {
    int32_t r, g, b, a;
};

// A colour scaled from the panel's: each component times a 16.16 ratio,
// at most 255. (The fourth word, 4096, is unused.)
struct ColorRatio {
    int32_t r, g, b, unused;
};

// The work blocks (itfPanelTypeWork_t), by type.
struct NormalWork {           // a rectangle with soft left and right ends
    PanelVertex vertex[8];        // four columns, top and bottom
    PanelColor edge, body;        // alpha 0 at the ends
};
struct MesWinWork {
    PanelVertex grid[16];         // a 4x4 grid: the corners stick out 16 x 8 pixels
    PanelVertex top[12], bottom[12];   // lines 0, 0.5 and 3 pixels in from the edges
    PanelColor edge, body;        // the edge is all but transparent (alpha 1)
    PanelColor shade[6];
};
struct SelWinWork {
    PanelVertex grid[16];
    PanelVertex top[8], bottom[8];     // lines 0 and 0.5 pixels in
    PanelColor edge, body;
    PanelColor shade[4];
};
struct PlainWork {
    PanelVertex vertex[4];
    PanelColor body;
    PanelColor shade[3];          // the last two at half alpha (128)
};
struct Pera1Work {
    PanelVertex vertex[4];
    PanelColor body;
};
struct LeftFadeWork {
    PanelVertex vertex[6];        // three columns, top and bottom
    PanelColor edge, body;
};
struct TexturedWork {         // MesWin2, SpkWin2
    uint32_t texture;
};
struct FacilityWork {
    uint32_t texture;
    PanelVertex vertex[8];        // fixed columns, top and bottom
    PanelColor edge, body;        // always blue (115, 135, 255), alpha 0
};
static_assert(sizeof(NormalWork) == 0x60 && sizeof(MesWinWork) == 0x1c0 && sizeof(SelWinWork) == 0x160);
static_assert(sizeof(PlainWork) == 0x60 && sizeof(Pera1Work) == 0x30 && sizeof(LeftFadeWork) == 0x50);
static_assert(sizeof(FacilityWork) == 0x64);

// The vertex and colour builders of each type.
void CreateVertexNormal(NormalWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void CreateVertexMesWin(MesWinWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void CreateVertexSelWin(SelWinWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void CreateVertexPlain(PlainWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void CreateVertexLeftFade(LeftFadeWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void CreateVertexFacility(FacilityWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void CreateColorNormal(NormalWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha);
void CreateColorMesWin(MesWinWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha);
void CreateColorSelWin(SelWinWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha);
void CreateColorPlain(PlainWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha);
void CreateColorPera1(Pera1Work& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha);
void CreateColorLeftFade(LeftFadeWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha);
void CreateColorFacility(FacilityWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha);

void MiscSetRatioRGB(PanelColor* pout, int32_t red, int32_t green, int32_t blue, int32_t alpha, const ColorRatio* pratio,
                     int32_t num);

// Panels are addresses of Panel records.
uint32_t PnlRegist2(int32_t type, uint32_t texture);
void PnlRelease(uint32_t panel);
void PnlSetPosition(uint32_t panel, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t z);
void PnlSetPositionOffset(uint32_t panel, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t z);
void PnlSetColor(uint32_t panel, int32_t red, int32_t green, int32_t blue, int32_t alpha);

} // namespace nocturne::itf
