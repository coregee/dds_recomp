// The battle's Macca window (original unit: nbMakaProcess). Rewritten from
// the original instructions.
#include "nocturne/battle/macca_window.hpp"

#include "nocturne/battle/process.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/interface/font.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = 0x00551560;   // "nb_maka"
constexpr uint32_t kDigits = 0x00551568;        // char[10][8]: "0".."9"
constexpr uint32_t kRunMaccaWindow = 0x0028f698;
constexpr uint32_t kShutdownMaccaWindow = 0x0028f6f0;

} // namespace

// GetMakaProcessData @ 0x0028F218
MaccaWindow* maccaWindow()
{
    const uint32_t process = dds3::SearchProcessName(kProcessName);
    return process ? guest::table<MaccaWindow>(dds3::GetProcessData(process)) : nullptr;
}

// nbMakaDispOn @ 0x0028F258: opens on the Macca on hand (at its usual place
// unless kept where it was).
void showMacca(int32_t keep)
{
    MaccaWindow& w = *maccaWindow();
    if (keep == 0) {
        w.x = 0x112;
        w.y = 0x10d;
    }
    w.keep = keep;
    w.state = 1;
    w.macca = dat::globalWork().macca;
}

// nbMakaDispOff @ 0x0028F2B0: closes, if open (over 20 frames unless kept).
void hideMacca()
{
    MaccaWindow& w = *maccaWindow();
    if (w.open != 0) {
        if (w.keep == 0)
            w.closeframes = 20;
        w.state = 2;
    }
}

// 0x0028F2F8 (no original name): (value % 10^(place+1)) / 10^place,
// with the original's trap on a zero divisor (which a power of ten never is).
int32_t maccaDigit(int32_t value, int32_t place)
{
    int32_t power = 10;
    for (int32_t i = place; i > 0; --i)
        power *= 10;
    if (power == 0)
        divideByZeroTrap();
    return value % power / (power / 10);
}

// DispMaka @ 0x0028F348: the frame (panel texture 4: its two ends and a
// stretched middle), the Macca label (texture 1), then the digits.
void drawMaccaWindow(MaccaWindow&, int32_t x, int32_t y, uint32_t color, uint32_t alpha)
{
    const MainProcessData& main = *GetMainProcessData();
    PanelSetOrderingOffset(0x48);
    PanelSetPrimitive(1, 0, 0x80, 3, 0, 0, 1, 1);
    PanelSetAlpha(0);
    const uint32_t rgba = (color & 0xffffff) | alpha << 24;
    PanelDrawTexturedRect(x, y, 0x36, 0x21, 2, 0x5d, 0x36, 0x21, rgba, main.hPnlTex4);
    PanelDrawTexturedRect(x + 0xe1, y, -0x36, 0x21, 2, 0x5d, 0x36, 0x21, rgba, main.hPnlTex4);
    PanelDrawTexturedRect(x + 0x36, y, 0x75, 0x21, 0x37, 0x5d, 1, 0x21, rgba, main.hPnlTex4);
    const int32_t textY = y + 6;
    PanelDrawTexturedRect(x + 0x2c, textY, 0x2f, 0x14, 0x86, 1, 0x2f, 0x14, rgba, main.hPnlTex1);
    PanelDrawTexturedRect(x + 0xba, textY, 0xd, 0x14, 0xb6, 1, 0xd, 0x14, rgba, main.hPnlTex1);
    int32_t digitX = x + 0x5d;
    bool shown = false;
    for (int32_t place = 6; place >= 0; --place) {
        const int32_t digit = maccaDigit(dat::globalWork().macca, place);
        const int32_t at = digitX << 4;
        digitX += 0xd;
        if (digit != 0 || place == 0)
            shown = true;
        if (!shown)
            continue;
        fr::Request* font = fr::StringRequest(at, textY * 8, 0xff0051, (alpha & 0xff) | 0x89feff00,
                                              kDigits + static_cast<uint32_t>(digit % 10) * 8, nullptr);
        fr::DrawFontEx2(*font, 1, 0x48);
        fr::frDestroyFontRequestAfter(font);
    }
}

// 0x0028F600 (no original name) the fade: opening, up by 0x20 to 0x80;
// closing, after its frames, down by 0x14 to 0, then closed.
void stepMaccaWindow(MaccaWindow& w)
{
    if (w.state == 1) {
        w.open = 1;
        if (w.alpha == 0x80) {
            w.state = 0;
            return;
        }
        w.alpha += 0x20;
        if (w.alpha > 0x80)
            w.alpha = 0x80;
    } else if (w.state == 2) {
        if (w.closeframes > 0) {
            --w.closeframes;
            return;
        }
        if (w.alpha < 1) {
            w.state = 0;
            w.open = 0;
            return;
        }
        w.alpha -= 0x14;
        if (w.alpha < 0)
            w.alpha = 0;
    }
}

// nbMakaProcess1 @ 0x0028F698
uint32_t runMaccaWindow(uint32_t process)
{
    MaccaWindow& w = *guest::table<MaccaWindow>(dds3::GetProcessData(process));
    stepMaccaWindow(w);
    if (w.open != 0)
        drawMaccaWindow(w, w.x, w.y, 0x80808080u, static_cast<uint32_t>(w.alpha));
    return 0;
}

// nbMakaShutdown @ 0x0028F6F0
void shutdownMaccaWindow(uint32_t process)
{
    if (const uint32_t data = dds3::GetProcessData(process))
        mem::PoolRelease(data);
}

// InitMakaProcessData @ 0x0028F728
uint32_t newMaccaWindow()
{
    const uint32_t data = mem::PoolAllocate(sizeof(MaccaWindow));
    *guest::table<MaccaWindow>(data) = MaccaWindow{};
    guest::table<MaccaWindow>(data)->macca = dat::globalWork().macca;
    return data;
}

// nbInitMakaProcess @ 0x0028F770
uint32_t startMaccaWindow(uint32_t parent)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x2b0e, 1, 1, kRunMaccaWindow, kShutdownMaccaWindow, newMaccaWindow());
    if (parent != 0)
        dds3::LinkProcess(parent, process);
    return process;
}

} // namespace nocturne::nb
