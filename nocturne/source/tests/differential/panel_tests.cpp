// Window panels (itfPanel): the rewrite against the original instructions,
// run by the EE interpreter (ee.hpp) in the same fake world.
#include <cstring>

#include "harness.hpp"
#include "interface_world.hpp"
#include "nocturne/interface/panel.hpp"

namespace difftest {

namespace {

namespace itf = nocturne::itf;
using iface::A;
using iface::I;
using iface::origVoid;

constexpr uint32_t kTexture = 0x00123450;

int32_t coordinate(Gen& g) { return g.chance(10) ? g.range(-0x8000, 0x8000) : g.range(0, 640 * 16); }

int32_t component(Gen& g)
{
    return g.chance(15) ? static_cast<int32_t>(g.rng()) : g.chance(20) ? g.range(-20, 300) : g.range(0, 255);
}

// An empty pool, and a registered panel of a random type with its fields
// and work block filled with noise.
uint32_t panelWorld(Gen& g)
{
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    const int32_t type = g.range(0, 8);
    const uint32_t panel = itf::PnlRegist2(type, g.chance(20) ? 0 : kTexture);
    itf::Panel& p = at<itf::Panel>(panel);
    p.z = g.below(0x1000000);
    for (int32_t& v : p.pos)
        v = coordinate(g);
    for (int32_t& v : p.color)
        v = g.range(0, 255);
    uint8_t* work = &at<uint8_t>(p.pwork);
    for (int i = 0; i < 0x1c0 && p.pwork + i < FW_MES_POOL_END; ++i)
        work[i] = static_cast<uint8_t>(g.below(256));
    return panel;
}

} // namespace

void addPanelTests(std::vector<TestCase>& t)
{
    t.push_back({"itfPnlRegist2", [](Gen& g) {
        std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
        const int32_t type = g.range(0, 8);
        const uint32_t texture = g.chance(20) ? 0 : kTexture;
        return Pair{[=] { return iface::orig(0x001cc080, {I(type), texture}); },
                    [=] { return norm(static_cast<int32_t>(itf::PnlRegist2(type, texture))); }};
    }});
    t.push_back({"itfPnlRelease", [](Gen& g) {
        uint32_t panel = panelWorld(g);
        if (g.chance(20))
            at<itf::Panel>(panel).pwork = 0;
        if (g.chance(5))
            panel = 0;
        return Pair{[=] { return origVoid(0x001cc150, {panel}); }, [=] { itf::PnlRelease(panel); return uint64_t{0}; }};
    }});
    t.push_back({"itfPnlSetPosition", [](Gen& g) {
        const uint32_t panel = panelWorld(g);
        const int32_t x0 = coordinate(g), y0 = coordinate(g), x1 = coordinate(g), y1 = coordinate(g);
        const uint32_t z = g.below(0x1000000);
        return Pair{[=] { return origVoid(0x001cc1a0, {panel, I(x0), I(y0), I(x1), I(y1), z}); },
                    [=] { itf::PnlSetPosition(panel, x0, y0, x1, y1, z); return uint64_t{0}; }};
    }});
    t.push_back({"itfPnlSetPositionOffset", [](Gen& g) {
        const uint32_t panel = panelWorld(g);
        const int32_t x0 = g.range(-400, 400), y0 = g.range(-400, 400), x1 = g.range(-400, 400), y1 = g.range(-400, 400);
        const uint32_t z = g.chance(50) ? 0 : g.below(0x1000);
        return Pair{[=] { return origVoid(0x001cc1e8, {panel, I(x0), I(y0), I(x1), I(y1), z}); },
                    [=] { itf::PnlSetPositionOffset(panel, x0, y0, x1, y1, z); return uint64_t{0}; }};
    }});
    t.push_back({"itfPnlSetColor", [](Gen& g) {
        const uint32_t panel = panelWorld(g);
        const int32_t r = component(g), gr = component(g), b = component(g), a = component(g);
        return Pair{[=] { return origVoid(0x001cc270, {panel, I(r), I(gr), I(b), I(a)}); },
                    [=] { itf::PnlSetColor(panel, r, gr, b, a); return uint64_t{0}; }};
    }});
    t.push_back({"itfMiscSetRatioRGB", [](Gen& g) {
        std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
        const uint32_t out = FW_MES_POOL, ratio = FW_MES_POOL + 0x400;
        auto* ratios = &at<itf::ColorRatio>(ratio);
        for (int i = 0; i < 8; ++i)
            ratios[i] = {g.chance(30) ? static_cast<int32_t>(g.rng()) : g.range(0, 0x30000),
                         g.range(0, 0x30000), g.range(0, 0x30000), 4096};
        const int32_t r = component(g), gr = component(g), b = component(g), a = component(g), num = g.range(-1, 8);
        return Pair{[=] { return origVoid(0x001caf78, {out, I(r), I(gr), I(b), I(a), ratio, I(num)}); },
                    [=] {
                        itf::MiscSetRatioRGB(&at<itf::PanelColor>(out), r, gr, b, a, ratios, num);
                        return uint64_t{0};
                    }};
    }});
}

} // namespace difftest
