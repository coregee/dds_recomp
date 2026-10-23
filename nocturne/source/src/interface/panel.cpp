// Window panels (original unit: itfPanel). Rewritten from the original
// instructions; drawing is not rewritten yet.
#include "nocturne/interface/panel.hpp"

#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::itf {

namespace {

namespace address {
constexpr uint32_t ShadeMesWin = 0x00326518;    // ColorRatio[6]
constexpr uint32_t ShadeSelWin = 0x00326578;    // ColorRatio[4]
constexpr uint32_t ShadePlain = 0x003265B8;     // ColorRatio[1]
constexpr uint32_t ShadePlainHalf = 0x003265C8; // ColorRatio[2]
} // namespace address

// The size of each type's work block (the table at 0x3264E0).
constexpr int32_t kWorkSize[] = {
    sizeof(NormalWork),   sizeof(MesWinWork),   sizeof(SelWinWork),   sizeof(PlainWork),    sizeof(Pera1Work),
    sizeof(LeftFadeWork), sizeof(TexturedWork), sizeof(TexturedWork), sizeof(FacilityWork),
};

// How far in from the top and bottom a message window's inner lines are
// (the table at 0x326508).
constexpr int32_t kMesWinLineOffset[] = {0, 8, 48};

const ColorRatio* ratios(uint32_t at) { return guest::table<const ColorRatio>(at); }

Panel& panelAt(uint32_t panel) { return *guest::table<Panel>(panel); }

template <class Work>
Work& work(const Panel& p)
{
    return *guest::table<Work>(p.pwork);
}

// The vertex builder of the panel's type (the table at 0x326428); the
// textured message and speaker windows have none.
void createVertex(const Panel& p, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    switch (p.type) {
    case kPanelNormal: CreateVertexNormal(work<NormalWork>(p), x0, y0, x1, y1); break;
    case kPanelMesWin: CreateVertexMesWin(work<MesWinWork>(p), x0, y0, x1, y1); break;
    case kPanelSelWin: CreateVertexSelWin(work<SelWinWork>(p), x0, y0, x1, y1); break;
    case kPanelPlain: CreateVertexPlain(work<PlainWork>(p), x0, y0, x1, y1); break;
    // (Pera1 shares the plain rectangle; both blocks start with it.)
    case kPanelPera1: CreateVertexPlain(work<PlainWork>(p), x0, y0, x1, y1); break;
    case kPanelLeftFade: CreateVertexLeftFade(work<LeftFadeWork>(p), x0, y0, x1, y1); break;
    case kPanelFacility: CreateVertexFacility(work<FacilityWork>(p), x0, y0, x1, y1); break;
    default: break;
    }
}

// The colour builder of the panel's type (the table at 0x326450).
void createColor(const Panel& p, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    switch (p.type) {
    case kPanelNormal: CreateColorNormal(work<NormalWork>(p), red, green, blue, alpha); break;
    case kPanelMesWin: CreateColorMesWin(work<MesWinWork>(p), red, green, blue, alpha); break;
    case kPanelSelWin: CreateColorSelWin(work<SelWinWork>(p), red, green, blue, alpha); break;
    case kPanelPlain: CreateColorPlain(work<PlainWork>(p), red, green, blue, alpha); break;
    case kPanelPera1: CreateColorPera1(work<Pera1Work>(p), red, green, blue, alpha); break;
    case kPanelLeftFade: CreateColorLeftFade(work<LeftFadeWork>(p), red, green, blue, alpha); break;
    case kPanelFacility: CreateColorFacility(work<FacilityWork>(p), red, green, blue, alpha); break;
    default: break;
    }
}

void setColor(PanelColor& c, int32_t red, int32_t green, int32_t blue, int32_t alpha) { c = {red, green, blue, alpha}; }

// A 4x4 grid around the rectangle: 16 pixels out at the sides, 8 above and
// below, with inner columns 32 pixels in from each side.
void createGrid(PanelVertex (&grid)[16], int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    const int32_t xs[4] = {x0 - 256, x0 + 512, x1 - 512, x1 + 256};
    const int32_t ys[4] = {y0 - 128, y0 + 128, y1 - 128, y1 + 128};
    for (int j = 0; j < 4; ++j)
        for (int i = 0; i < 4; ++i)
            grid[4 * j + i] = {xs[i], ys[j]};
}

} // namespace

// ---- vertices ------------------------------------------------------------------------------

// CreateVertexNormal @ 0x001CC358: the inner columns are 32 pixels in from
// each end, or both at the middle when the panel is narrower than that.
void CreateVertexNormal(NormalWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    int32_t xs[4] = {x0, x0 + 512, x1 - 512, x1};
    if (xs[2] < xs[1])
        xs[1] = xs[2] = x0 + ((x1 - x0) >> 1);
    for (int i = 0; i < 4; ++i) {
        pwork.vertex[2 * i] = {xs[i], y0};
        pwork.vertex[2 * i + 1] = {xs[i], y1};
    }
}

// CreateVertexMesWin @ 0x001CC3D0: the grid, then lines across the top
// and the bottom with columns 64 pixels in.
void CreateVertexMesWin(MesWinWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    createGrid(pwork.grid, x0, y0, x1, y1);
    const int32_t xs[4] = {x0 - 256, x0 + 1024, x1 - 1024, x1 + 256};
    for (int j = 0; j < 3; ++j)
        for (int i = 0; i < 4; ++i)
            pwork.top[4 * j + i] = {xs[i], y0 + kMesWinLineOffset[j]};
    for (int j = 0; j < 3; ++j)
        for (int i = 0; i < 4; ++i)
            pwork.bottom[4 * j + i] = {xs[i], y1 - kMesWinLineOffset[j]};
}

// CreateVertexSelWin @ 0x001CC540: as the message window, with two lines.
void CreateVertexSelWin(SelWinWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    createGrid(pwork.grid, x0, y0, x1, y1);
    const int32_t xs[4] = {x0 - 256, x0 + 1024, x1 - 1024, x1 + 256};
    for (int j = 0; j < 2; ++j)
        for (int i = 0; i < 4; ++i)
            pwork.top[4 * j + i] = {xs[i], y0 + 8 * j};
    for (int j = 0; j < 2; ++j)
        for (int i = 0; i < 4; ++i)
            pwork.bottom[4 * j + i] = {xs[i], y1 - 8 * j};
}

// CreateVertexPlain @ 0x001CC688: the rectangle's corners, clockwise.
void CreateVertexPlain(PlainWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    pwork.vertex[0] = {x0, y0};
    pwork.vertex[1] = {x1, y0};
    pwork.vertex[2] = {x1, y1};
    pwork.vertex[3] = {x0, y1};
}

// CreateVertexLeftFade @ 0x001CC6B8: solid for the last 90 pixels.
void CreateVertexLeftFade(LeftFadeWork& pwork, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    const int32_t xs[3] = {x0, x1 - 1440, x1};
    for (int i = 0; i < 3; ++i) {
        pwork.vertex[i] = {xs[i], y0};
        pwork.vertex[3 + i] = {xs[i], y1};
    }
}

// CreateVertexFacility @ 0x001CC728: the columns are fixed (26 to 485
// pixels); the top is 22 pixels below y0, the bottom 20 above y1.
void CreateVertexFacility(FacilityWork& pwork, int32_t, int32_t y0, int32_t, int32_t y1)
{
    static constexpr int32_t xs[4] = {416, 1152, 7024, 7760};
    for (int i = 0; i < 4; ++i) {
        pwork.vertex[2 * i] = {xs[i], y0 + 352};
        pwork.vertex[2 * i + 1] = {xs[i], y1 - 320};
    }
}

// ---- colours ------------------------------------------------------------------------------

// itfMiscSetRatioRGB @ 0x001CAF78 (the PS2 has no offset argument): `num`
// colours, each the given one scaled by a ratio and at most 255, with the
// given alpha. The products wrap at 32 bits.
void MiscSetRatioRGB(PanelColor* pout, int32_t red, int32_t green, int32_t blue, int32_t alpha, const ColorRatio* pratio,
                     int32_t num)
{
    auto scale = [](int32_t ratio, int32_t component) {
        int32_t v = static_cast<int32_t>(static_cast<uint32_t>(ratio) * static_cast<uint32_t>(component));
        if (v > 0xff0000)
            v = 0xff0000;
        return v >> 16;
    };
    for (; num > 0; --num, ++pout, ++pratio)
        *pout = {scale(pratio->r, red), scale(pratio->g, green), scale(pratio->b, blue), alpha};
}

// CreateColorNormal @ 0x001CC7A0
void CreateColorNormal(NormalWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    setColor(pwork.edge, red, green, blue, 0);
    setColor(pwork.body, red, green, blue, alpha);
}

// CreateColorMesWin @ 0x001CC7D0
void CreateColorMesWin(MesWinWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    setColor(pwork.edge, red, green, blue, 1);
    setColor(pwork.body, red, green, blue, alpha);
    MiscSetRatioRGB(pwork.shade, red, green, blue, alpha, ratios(address::ShadeMesWin), 6);
}

// CreateColorSelWin @ 0x001CC830
void CreateColorSelWin(SelWinWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    setColor(pwork.edge, red, green, blue, 1);
    setColor(pwork.body, red, green, blue, alpha);
    MiscSetRatioRGB(pwork.shade, red, green, blue, alpha, ratios(address::ShadeSelWin), 4);
}

// CreateColorPlain @ 0x001CC890
void CreateColorPlain(PlainWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    setColor(pwork.body, red, green, blue, alpha);
    MiscSetRatioRGB(&pwork.shade[0], red, green, blue, alpha, ratios(address::ShadePlain), 1);
    MiscSetRatioRGB(&pwork.shade[1], red, green, blue, 128, ratios(address::ShadePlainHalf), 2);
}

// CreateColorPera1 @ 0x001CC920
void CreateColorPera1(Pera1Work& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    setColor(pwork.body, red, green, blue, alpha);
}

// CreateColorLeftFade @ 0x001CC938
void CreateColorLeftFade(LeftFadeWork& pwork, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    setColor(pwork.edge, red, green, blue, 0);
    setColor(pwork.body, red, green, blue, alpha);
}

// CreateColorFacility @ 0x001CC968: always the same blue; the arguments are ignored.
void CreateColorFacility(FacilityWork& pwork, int32_t, int32_t, int32_t, int32_t)
{
    setColor(pwork.edge, 115, 135, 255, 0);
    setColor(pwork.body, 115, 135, 255, 0);
}

// ---- panels -------------------------------------------------------------------------------

// itfPnlRegist2 @ 0x001CC080: a panel and its work block. The textured
// types keep the texture at the start of the work.
uint32_t PnlRegist2(int32_t type, uint32_t texture)
{
    const uint32_t handle = mem::HandleAllocate(sizeof(Panel));
    const uint32_t panel = mem::HandleAcquirePointer(handle);
    Panel& p = panelAt(panel);
    p.type = static_cast<uint8_t>(type);
    p.handle = handle;
    p.workhandle = mem::HandleAllocate(kWorkSize[type]);
    p.pwork = mem::HandleAcquirePointer(p.workhandle);
    if (texture && (type == kPanelMesWin2 || type == kPanelSpkWin2 || type == kPanelFacility))
        guest::table<TexturedWork>(p.pwork)->texture = texture;
    return panel;
}

// itfPnlRelease @ 0x001CC150
void PnlRelease(uint32_t panel)
{
    if (!panel)
        return;
    const Panel& p = panelAt(panel);
    if (p.pwork)
        mem::HandleFree(p.workhandle);
    mem::HandleFree(p.handle);
}

// itfPnlSetPosition @ 0x001CC1A0
void PnlSetPosition(uint32_t panel, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t z)
{
    Panel& p = panelAt(panel);
    p.z = z;
    p.pos[0] = x0;
    p.pos[1] = y0;
    p.pos[2] = x1;
    p.pos[3] = y1;
    createVertex(p, x0, y0, x1, y1);
}

// itfPnlSetPositionOffset @ 0x001CC1E8: moves the panel by the offsets.
void PnlSetPositionOffset(uint32_t panel, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t z)
{
    Panel& p = panelAt(panel);
    p.pos[0] += x0;
    p.pos[1] += y0;
    p.pos[2] += x1;
    p.pos[3] += y1;
    p.z += z;
    createVertex(p, p.pos[0], p.pos[1], p.pos[2], p.pos[3]);
}

// itfPnlSetColor @ 0x001CC270
void PnlSetColor(uint32_t panel, int32_t red, int32_t green, int32_t blue, int32_t alpha)
{
    Panel& p = panelAt(panel);
    p.color[0] = red;
    p.color[1] = green;
    p.color[2] = blue;
    p.color[3] = alpha;
    createColor(p, red, green, blue, alpha);
}

} // namespace nocturne::itf
