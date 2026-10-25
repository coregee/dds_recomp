// The FlowScript commands every script can use (original unit: scrCommonCommand).
#include "nocturne/script/commands.hpp"

#include "nocturne/address.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"
#include "nocturne/kernel/draw.hpp"
#include "nocturne/script/vm.hpp"

namespace nocturne::scr {

// ---- flags, waiting, fades and other scripts ------------------------------------------------------

// scrCommand_BIT_CHK @ 0x0010B888: BIT_CHK(n), an event flag.
int32_t scrCommand_BIT_CHK()
{
    scrSetIntReturnValue(evt::BitCheck(scrGetIntPara(0)) ? 1 : 0);
    return 1;
}

// scrCommand_BIT_ON @ 0x0010B8B8
int32_t scrCommand_BIT_ON()
{
    evt::BitOn(scrGetIntPara(0));
    return 1;
}

// scrCommand_BIT_OFF @ 0x0010B8E0
int32_t scrCommand_BIT_OFF()
{
    evt::BitOff(scrGetIntPara(0));
    return 1;
}

// scrCommand_RND @ 0x0010B908: RND(n), 1..n.
int32_t scrCommand_RND()
{
    scrSetIntReturnValue(sdf::GetRandInt(scrGetIntPara(0)) + 1);
    return 1;
}

// scrCommand_SYNC @ 0x0010B940: waits one frame.
int32_t scrCommand_SYNC() { return scrGetCommandTimer() != 0; }

// scrCommand_WAIT @ 0x0010B960: WAIT(frames).
int32_t scrCommand_WAIT()
{
    if (scrGetIntPara(0) <= 0)
        return 1;
    const int32_t timer = scrGetCommandTimer();
    return timer >= scrGetIntPara(0);
}

// scrCommand_PUT @ 0x0010B9A8: PUT(n), a debug print.
int32_t scrCommand_PUT()
{
    diag::print(diag::Message::ScriptPut, scrGetIntPara(0));
    scrPrintf(optionalAddr(0x0052f598), static_cast<uint32_t>(scrGetIntPara(0)));
    return 1;
}

// scrCommand_PUTS @ 0x0010B9F0: PUTS(string)
int32_t scrCommand_PUTS()
{
    diag::print(diag::Message::ScriptPuts, scrGetStrPara(0));
    scrPrintf(optionalAddr(0x0052f5b8), scrGetStrPara(0));
    return 1;
}

namespace {

// FADE_IN / FADE_OUT(mode, frames): mode 0 from / to black, 1 white.
int32_t fade(bool in)
{
    if (scrGetCommandTimer())
        return 1;
    const int32_t mode = scrGetIntPara(0);
    if (mode != 0 && mode != 1)
        return 1;
    const int32_t frames = scrGetIntPara(1);
    const int32_t color = mode ? 255 : 0;
    if (in)
        dds3::FadeIn(color, color, color, frames);
    else
        dds3::FadeOut(color, color, color, frames);
    return 0;
}

} // namespace

// scrCommand_FADE_IN @ 0x0010BA38
int32_t scrCommand_FADE_IN() { return fade(true); }

// scrCommand_FADE_OUT @ 0x0010BAD8
int32_t scrCommand_FADE_OUT() { return fade(false); }

// scrCommand_SEL_JMP @ 0x0010BB78: SEL_JMP(n, label0, label1, ...) jumps to label n.
int32_t scrCommand_SEL_JMP()
{
    const int32_t choice = scrGetIntPara(0);
    if (choice < 0)
        return 1;
    const int32_t label = scrGetIntPara(choice + 1);
    if (label < 0)
        return 1;
    scrSetCodePointer(scrGetLabelCodeAddress(label));
    return 1;
}

namespace {

// The pad manager's state of each button (DDS3_PADCHECK_*): bit 7 when
// pressed this frame, bit 0 while held.
int8_t padButton(int32_t button) { return guest::table<int8_t>(addr(0x005298c8))[button]; }

} // namespace

// scrCommand_PAD_TRIG @ 0x0010BBD0: PAD_TRIG(button), pressed this frame.
int32_t scrCommand_PAD_TRIG()
{
    scrSetIntReturnValue(padButton(scrGetIntPara(0)) < 0 ? 1 : 0);
    return 1;
}

// scrCommand_PAD_PRESS @ 0x0010BC08: PAD_PRESS(button), held.
int32_t scrCommand_PAD_PRESS()
{
    scrSetIntReturnValue(padButton(scrGetIntPara(0)) & 1);
    return 1;
}

// scrCommand_SCR_RUN @ 0x0010BD20
// SCR_RUN(procedure, priority offset): starts another procedure of this
// script in a process of its own; returns the process.
int32_t scrCommand_SCR_RUN()
{
    const int32_t index = scrGetIntPara(0);
    ProcessWork* w = scrGetScriptHandle();
    if (!w)
        return 1;
    if (!w->ProcessID) {
        diag::print(diag::Message::ScriptRunWithoutProcess);
    } else if (index >= 0 && index < w->typeTable->ItemCount) {
        const int32_t displacement = scrGetIntPara(1);
        const int32_t priority = *guest::table<int32_t>(w->ProcessID + 0x20) + displacement;
        const uint32_t child = scrStartScript1a(priority, w->header.address, w->typeTable.address, w->procTable.address,
                                                w->labelTable.address, w->code.address, w->MessageData, w->StringData, index);
        scrSetIntReturnValue(static_cast<int32_t>(child));
    }
    return 1;
}

// scrCommand_SCR_KILL @ 0x0010BDE0: ends a process (on the next frame).
int32_t scrCommand_SCR_KILL()
{
    const uint32_t process = static_cast<uint32_t>(scrGetIntPara(0));
    if (dds3::ExistProcess(process))
        dds3::KillProcess(process, 1);
    return 1;
}

// scrCommand_SCR_WAIT @ 0x0010BE28: waits for a process to end.
int32_t scrCommand_SCR_WAIT() { return dds3::ExistProcess(static_cast<uint32_t>(scrGetIntPara(0))) ? 0 : 1; }

// scrCommand_SCR_STAT @ 0x0010BE50: whether a process is running.
int32_t scrCommand_SCR_STAT()
{
    scrSetIntReturnValue(dds3::ExistProcess(static_cast<uint32_t>(scrGetIntPara(0))) ? 1 : 0);
    return 1;
}

// scrCommand_SCR_TIME @ 0x0010BE98: how long a process has run.
int32_t scrCommand_SCR_TIME()
{
    const uint32_t process = static_cast<uint32_t>(scrGetIntPara(0));
    scrSetIntReturnValue(dds3::ExistProcess(process) ? dds3::GetRunTime(process) : 0);
    return 1;
}

// scrCommand_QUAKE_ON @ 0x0010BEF8: QUAKE_ON(frames, range) shakes the view.
int32_t scrCommand_QUAKE_ON()
{
    const int32_t frame = scrGetIntPara(0);
    dds3::dds3SetQuake(frame, static_cast<uint32_t>(scrGetIntPara(1)));
    return 1;
}

// scrCommand_QUAKE_OFF @ 0x0010BF38
int32_t scrCommand_QUAKE_OFF()
{
    dds3::dds3StopQuake();
    return 1;
}

// ---- the pad and the camera ------------------------------------------------------------------

// scrCommand_PAD_ACT @ 0x0010BC40: PAD_ACT(mode, power, frames) vibrates the pad.
int32_t scrCommand_PAD_ACT()
{
    const int32_t mode = scrGetIntPara(0);
    const int32_t power = scrGetIntPara(1);
    dds3::PadAct(static_cast<uint32_t>(mode), static_cast<uint8_t>(power), static_cast<uint32_t>(scrGetIntPara(2)));
    return 1;
}

// scrCommand_SET_FOVY @ 0x0010BC98: SET_FOVY(degrees), the camera's field of view.
// The angle is converted to radians and then refused unless strictly between
// 5 and 180 (a check written for degrees), so ordinary angles never apply.
int32_t scrCommand_SET_FOVY()
{
    const ee::Float fovy = ee::Float::fromBits(scrGetFloatPara(0)) * *guest::table<ee::Float>(addr(0x0054c194));   // pi / 180
    if (fovy <= ee::Float(5.0f) || ee::Float(180.0f) <= fovy) {
        scrPrintf(optionalAddr(0x0052f5c8));   // "WARNING: SET_FOVY over = %f"
        return 1;
    }
    dds3::dds3SetScreenFovy(fovy);
    return 1;
}

// ---- the screen effects ------------------------------------------------------------------------

namespace {

ee::Float floatPara(int32_t index) { return ee::Float::fromBits(scrGetFloatPara(index)); }

// The scripts' colours: four arguments red, green, blue, alpha.
uint32_t abgrPara()
{
    const uint32_t r = static_cast<uint32_t>(scrGetIntPara(0)), a = static_cast<uint32_t>(scrGetIntPara(3));
    const uint32_t b = static_cast<uint32_t>(scrGetIntPara(2)), g = static_cast<uint32_t>(scrGetIntPara(1));
    return (r & 0xff) | a << 24 | (b & 0xff) << 16 | (g & 0xff) << 8;
}

// The scripts' blend modes as GS alpha settings: 0 normal, 1 additive,
// 2 subtractive; filters also take 3, the screen inverted.
constexpr int32_t kBlendNormal = 0x44, kBlendAdd = 0x48, kBlendSubtract = 0x42, kBlendInvert = 0x06;

int32_t blurBlend(int32_t mode)
{
    if (mode == 1)
        return kBlendAdd;
    return mode == 2 ? kBlendSubtract : kBlendNormal;
}

int32_t filterBlend(int32_t mode, uint32_t error)
{
    switch (mode) {
    case 0: return kBlendNormal;
    case 1: return kBlendAdd;
    case 2: return kBlendSubtract;
    case 3: return kBlendInvert;
    default:
        scrPrintf(error);
        return kBlendNormal;
    }
}

} // namespace

// ---- the scene's light and fog --------------------------------------------------------------------

namespace {

// A colour from arguments 1..3, each added to 0 as the VU does (VADDx).
dds3::Vector4 colorPara(ee::Float w)
{
    const ee::Float r = ee::Float(0.0f) + floatPara(1);
    const ee::Float g = ee::Float(0.0f) + floatPara(2);
    return {r, g, ee::Float(0.0f) + floatPara(3), w};
}

// An int argument read as unsigned and converted to float, as the compiled
// code does it (halved and doubled when the top bit is set).
ee::Float unsignedPara(int32_t index)
{
    const int32_t v = scrGetIntPara(index);
    if (v >= 0)
        return ee::Float::fromInt(v);
    const uint32_t u = static_cast<uint32_t>(v);
    const ee::Float half = ee::Float::fromInt(static_cast<int32_t>(u >> 1 | (u & 1)));
    return half + half;
}

} // namespace

// scrCommand_SCENE_LIGHT_RGB @ 0x0010BF58: SCENE_LIGHT_RGB(frames, r, g, b), light 0's colour.
// (The alpha lane is whatever vf10 held, times 0; taken here as 0.)
int32_t scrCommand_SCENE_LIGHT_RGB()
{
    const dds3::Vector4 color = colorPara(ee::Float(0.0f) * ee::Float(0.0f));
    dds3::dds3SetLightColor(static_cast<uint32_t>(scrGetIntPara(0)), 0, color);
    return 1;
}

// scrCommand_SCENE_LIGHT_DIR @ 0x0010BFD0: SCENE_LIGHT_DIR(frames, x, y, z),
// light 0's direction; refused (a debug warning) when all three are within 0.01 of 0.
int32_t scrCommand_SCENE_LIGHT_DIR()
{
    const ee::Float x = floatPara(1), y = floatPara(2), z = floatPara(3);
    const ee::Float least = *guest::table<ee::Float>(addr(0x0054c198));   // 0.01
    if (x.abs() <= least && y.abs() <= least && z.abs() <= least) {
        scrPrintf(optionalAddr(0x0052f630));   // "WARNING: SCENE_LIGHT_DIR length zero"
        return 1;
    }
    dds3::dds3SetLightDir(static_cast<uint32_t>(scrGetIntPara(0)), 0, {x, y, z, ee::Float::fromBits(0)});
    return 1;
}

// scrCommand_SCENE_AMBIENT @ 0x0010C080: SCENE_AMBIENT(frames, r, g, b)
int32_t scrCommand_SCENE_AMBIENT()
{
    const dds3::Vector4 color = colorPara(ee::Float(1.0f));
    dds3::dds3SetAmbientColor(static_cast<uint32_t>(scrGetIntPara(0)), color);
    return 1;
}

// scrCommand_SCENE_FOG_RGB @ 0x0010C0F0: SCENE_FOG_RGB(frames, r, g, b)
int32_t scrCommand_SCENE_FOG_RGB()
{
    const ee::Float r = floatPara(1), g = floatPara(2);
    const dds3::Vector4 color = {r, g, floatPara(3), ee::Float::fromBits(0)};
    dds3::dds3SetFogColor(static_cast<uint32_t>(scrGetIntPara(0)), color);
    return 1;
}

// scrCommand_SCENE_FOG_PARA @ 0x0010C148: SCENE_FOG_PARA(frames, max, near, min, far), as ints.
int32_t scrCommand_SCENE_FOG_PARA()
{
    const int32_t frame = scrGetIntPara(0);
    const ee::Float max = unsignedPara(1), min = unsignedPara(3), near = unsignedPara(2);
    dds3::dds3SetFogPara(static_cast<uint32_t>(frame), max, min, near, unsignedPara(4));
    return 1;
}

// scrCommand_SOFTEN_BIAS @ 0x0010C280: SOFTEN_BIAS(frames, soften, bias)
int32_t scrCommand_SOFTEN_BIAS()
{
    const int32_t frame = scrGetIntPara(0);
    const ee::Float soften = floatPara(1);
    dds3::dds3SetSoftenBias(static_cast<uint32_t>(frame), soften, floatPara(2));
    return 1;
}

// ---- the screen effects (continued) ----------------------------------------------------------------

// scrCommand_BLUR @ 0x0010C2D8: BLUR(frames, alpha, scale), the screen blur.
int32_t scrCommand_BLUR()
{
    const int32_t frame = scrGetIntPara(0), alpha = scrGetIntPara(1);
    dds3::dds3SetBlur(static_cast<uint32_t>(frame), alpha, scrGetIntPara(2));
    return 1;
}

// scrCommand_MUL_BLUR_PARA @ 0x0010C330: MUL_BLUR_PARA(rotate, scale, blend)
int32_t scrCommand_MUL_BLUR_PARA()
{
    const int32_t blend = blurBlend(scrGetIntPara(2));
    const ee::Float rotate = floatPara(0);
    dds3::dds3SetMultiBlurPara(rotate, floatPara(1), blend);
    return 1;
}

// scrCommand_MUL_BLUR_RGBA @ 0x0010C3B8: MUL_BLUR_RGBA(r, g, b, a)
int32_t scrCommand_MUL_BLUR_RGBA()
{
    dds3::dds3SetMultiBlurRGBA(abgrPara());
    return 1;
}

// scrCommand_MUL_BLUR_AREA @ 0x0010C440: MUL_BLUR_AREA(area, x, y)
int32_t scrCommand_MUL_BLUR_AREA()
{
    const int32_t area = scrGetIntPara(0), x = scrGetIntPara(1);
    dds3::dds3SetMultiBlurArea(area, x, scrGetIntPara(2));
    return 1;
}

// scrCommand_MUL_BLUR_SWAP @ 0x0010C498: MUL_BLUR_SWAP(frames)
int32_t scrCommand_MUL_BLUR_SWAP()
{
    dds3::dds3MultiBlurSwap(scrGetIntPara(0));
    return 1;
}

// scrCommand_MUL_BLUR_ON @ 0x0010C4C0: MUL_BLUR_ON(frames)
int32_t scrCommand_MUL_BLUR_ON()
{
    dds3::dds3MultiBlurOn(scrGetIntPara(0));
    return 1;
}

// scrCommand_MUL_BLUR_OFF @ 0x0010C4E8: MUL_BLUR_OFF(frames)
int32_t scrCommand_MUL_BLUR_OFF()
{
    dds3::dds3MultiBlurOff(scrGetIntPara(0));
    return 1;
}

// scrCommand_DIST_BLUR_PARA @ 0x0010C510
// DIST_BLUR_PARA(number, width, interval, speed, rotate, distortion, blend)
int32_t scrCommand_DIST_BLUR_PARA()
{
    const int32_t blend = blurBlend(scrGetIntPara(6));
    const int32_t number = scrGetIntPara(0), width = scrGetIntPara(1), interval = scrGetIntPara(2);
    const ee::Float speed = floatPara(3), rotate = floatPara(4);
    dds3::dds3SetDistBlurPara(number, width, interval, blend, speed, rotate, floatPara(5));
    return 1;
}

// scrCommand_DIST_BLUR_RGBA @ 0x0010C5F8
int32_t scrCommand_DIST_BLUR_RGBA()
{
    dds3::dds3SetDistBlurRGBA(abgrPara());
    return 1;
}

// scrCommand_DIST_BLUR_AREA @ 0x0010C680: DIST_BLUR_AREA(area, x, y)
int32_t scrCommand_DIST_BLUR_AREA()
{
    const int32_t area = scrGetIntPara(0), x = scrGetIntPara(1);
    dds3::dds3SetDistBlurArea(area, x, scrGetIntPara(2));
    return 1;
}

// scrCommand_DIST_BLUR_SWAP @ 0x0010C6D8
int32_t scrCommand_DIST_BLUR_SWAP()
{
    dds3::dds3DistBlurSwap(scrGetIntPara(0));
    return 1;
}

// scrCommand_DIST_BLUR_ON @ 0x0010C700
int32_t scrCommand_DIST_BLUR_ON()
{
    dds3::dds3DistBlurOn(scrGetIntPara(0));
    return 1;
}

// scrCommand_DIST_BLUR_OFF @ 0x0010C728
int32_t scrCommand_DIST_BLUR_OFF()
{
    dds3::dds3DistBlurOff(scrGetIntPara(0));
    return 1;
}

// scrCommand_RIP_BLUR_PARA @ 0x0010C750
// RIP_BLUR_PARA(number, speed, interval, rotate, power, frequency, blend)
int32_t scrCommand_RIP_BLUR_PARA()
{
    const int32_t blend = blurBlend(scrGetIntPara(6));
    const int32_t number = scrGetIntPara(0);
    const ee::Float speed = floatPara(1), interval = floatPara(2), rotate = floatPara(3), power = floatPara(4);
    dds3::dds3SetRipBlurPara(speed, interval, rotate, power, floatPara(5), number, blend);
    return 1;
}

// scrCommand_RIP_BLUR_RGBA @ 0x0010C838
int32_t scrCommand_RIP_BLUR_RGBA()
{
    dds3::dds3SetRipBlurRGBA(abgrPara());
    return 1;
}

// scrCommand_RIP_BLUR_AREA @ 0x0010C8C0: RIP_BLUR_AREA(area, x, y)
int32_t scrCommand_RIP_BLUR_AREA()
{
    const int32_t area = scrGetIntPara(0), x = scrGetIntPara(1);
    dds3::dds3SetRipBlurArea(area, x, scrGetIntPara(2));
    return 1;
}

// scrCommand_RIP_BLUR_SWAP @ 0x0010C918
int32_t scrCommand_RIP_BLUR_SWAP()
{
    dds3::dds3RipBlurSwap(scrGetIntPara(0));
    return 1;
}

// scrCommand_RIP_BLUR_ON @ 0x0010C940
int32_t scrCommand_RIP_BLUR_ON()
{
    dds3::dds3RipBlurOn(scrGetIntPara(0));
    return 1;
}

// scrCommand_RIP_BLUR_OFF @ 0x0010C968
int32_t scrCommand_RIP_BLUR_OFF()
{
    dds3::dds3RipBlurOff(scrGetIntPara(0));
    return 1;
}

// scrCommand_BLUR2_PARA @ 0x0010C990: BLUR2_PARA(rotate, scale, blend)
int32_t scrCommand_BLUR2_PARA()
{
    const int32_t mode = scrGetIntPara(2);
    if (mode < 0 || mode > 2)
        scrPrintf(optionalAddr(0x0052f658));   // "error: BLUR2_PARA blend"
    const int32_t blend = blurBlend(mode);
    const ee::Float rotate = floatPara(0);
    dds3::dds3SetBlur2Para(rotate, floatPara(1), blend);
    return 1;
}

// scrCommand_BLUR2_RGBA @ 0x0010CA30
int32_t scrCommand_BLUR2_RGBA()
{
    dds3::dds3SetBlur2RGBA(abgrPara());
    return 1;
}

// scrCommand_BLUR2_AREA @ 0x0010CAB8: BLUR2_AREA(x, y)
int32_t scrCommand_BLUR2_AREA()
{
    const int32_t x = scrGetIntPara(0);
    dds3::dds3SetBlur2Area(x, scrGetIntPara(1));
    return 1;
}

// scrCommand_BLUR2_SWAP @ 0x0010CAF8
int32_t scrCommand_BLUR2_SWAP()
{
    dds3::dds3Blur2Swap(scrGetIntPara(0));
    return 1;
}

// scrCommand_BLUR2_ON @ 0x0010CB20
int32_t scrCommand_BLUR2_ON()
{
    dds3::dds3Blur2On(scrGetIntPara(0));
    return 1;
}

// scrCommand_BLUR2_OFF @ 0x0010CB48
int32_t scrCommand_BLUR2_OFF()
{
    dds3::dds3Blur2Off(scrGetIntPara(0));
    return 1;
}

// scrCommand_FILTER2_PARA @ 0x0010CB70: FILTER2_PARA(blend)
int32_t scrCommand_FILTER2_PARA()
{
    dds3::dds3SetFilter2Para(filterBlend(scrGetIntPara(0), addr(0x0052f678)));   // "error: FILTER2_PARA blend"
    return 1;
}

// scrCommand_FILTER2_RGBA @ 0x0010CBF0
int32_t scrCommand_FILTER2_RGBA()
{
    dds3::dds3SetFilter2RGBA(abgrPara());
    return 1;
}

// scrCommand_FILTER2_SWAP @ 0x0010CC78
int32_t scrCommand_FILTER2_SWAP()
{
    dds3::dds3Filter2Swap(scrGetIntPara(0));
    return 1;
}

// scrCommand_FILTER2_ON @ 0x0010CCA0
int32_t scrCommand_FILTER2_ON()
{
    dds3::dds3Filter2On(scrGetIntPara(0));
    return 1;
}

// scrCommand_FILTER2_OFF @ 0x0010CCC8
int32_t scrCommand_FILTER2_OFF()
{
    dds3::dds3Filter2Off(scrGetIntPara(0));
    return 1;
}

// scrCommand_MFILTER_PARA @ 0x0010CCF0: MFILTER_PARA(blend)
int32_t scrCommand_MFILTER_PARA()
{
    dds3::dds3SetMFilterPara(filterBlend(scrGetIntPara(0), addr(0x0052f698)));   // "error: MFILTER_PARA blend"
    return 1;
}

// scrCommand_MFILTER_RGBA @ 0x0010CD70
int32_t scrCommand_MFILTER_RGBA()
{
    dds3::dds3SetMFilterRGBA(abgrPara());
    return 1;
}

// scrCommand_MFILTER_AREA @ 0x0010CDF8: MFILTER_AREA(area, x, y)
int32_t scrCommand_MFILTER_AREA()
{
    const int32_t area = scrGetIntPara(0), x = scrGetIntPara(1);
    dds3::dds3SetMFilterArea(area, x, scrGetIntPara(2));
    return 1;
}

// scrCommand_MFILTER_SWAP @ 0x0010CE50
int32_t scrCommand_MFILTER_SWAP()
{
    dds3::dds3MFilterSwap(scrGetIntPara(0));
    return 1;
}

// scrCommand_MFILTER_ON @ 0x0010CE78
int32_t scrCommand_MFILTER_ON()
{
    dds3::dds3MFilterOn(scrGetIntPara(0));
    return 1;
}

// scrCommand_MFILTER_OFF @ 0x0010CEA0
int32_t scrCommand_MFILTER_OFF()
{
    dds3::dds3MFilterOff(scrGetIntPara(0));
    return 1;
}

// scrCommand_BLUR_ALLOFF @ 0x0010CEC8: every blur off at once.
int32_t scrCommand_BLUR_ALLOFF()
{
    dds3::dds3SetBlur(0, 0, 0);
    dds3::dds3Blur2Off(0);
    dds3::dds3MultiBlurOff(0);
    dds3::dds3DistBlurOff(0);
    dds3::dds3RipBlurOff(0);
    return 1;
}

// scrCommand_FILTER_ALLOFF @ 0x0010CF10: both filters off at once.
int32_t scrCommand_FILTER_ALLOFF()
{
    dds3::dds3Filter2Off(0);
    dds3::dds3MFilterOff(0);
    return 1;
}

// ---- the command table ---------------------------------------------------------------------------

namespace {

struct Command {
    uint32_t entry;
    int32_t (*function)();
};

constexpr Command kCommands[] = {
    {addr(0x0010b888), scrCommand_BIT_CHK},       {addr(0x0010b8b8), scrCommand_BIT_ON},
    {addr(0x0010b8e0), scrCommand_BIT_OFF},       {addr(0x0010b908), scrCommand_RND},
    {addr(0x0010b940), scrCommand_SYNC},          {addr(0x0010b960), scrCommand_WAIT},
    {addr(0x0010b9a8), scrCommand_PUT},           {addr(0x0010b9f0), scrCommand_PUTS},
    {addr(0x0010ba38), scrCommand_FADE_IN},       {addr(0x0010bad8), scrCommand_FADE_OUT},
    {addr(0x0010bb78), scrCommand_SEL_JMP},       {addr(0x0010bbd0), scrCommand_PAD_TRIG},
    {addr(0x0010bc08), scrCommand_PAD_PRESS},     {addr(0x0010bc40), scrCommand_PAD_ACT},
    {addr(0x0010bc98), scrCommand_SET_FOVY},      {addr(0x0010bd20), scrCommand_SCR_RUN},
    {addr(0x0010bde0), scrCommand_SCR_KILL},      {addr(0x0010be28), scrCommand_SCR_WAIT},
    {addr(0x0010be50), scrCommand_SCR_STAT},      {addr(0x0010be98), scrCommand_SCR_TIME},
    {addr(0x0010bef8), scrCommand_QUAKE_ON},      {addr(0x0010bf38), scrCommand_QUAKE_OFF},
    {addr(0x0010bf58), scrCommand_SCENE_LIGHT_RGB}, {addr(0x0010bfd0), scrCommand_SCENE_LIGHT_DIR},
    {addr(0x0010c080), scrCommand_SCENE_AMBIENT},
    {addr(0x0010c0f0), scrCommand_SCENE_FOG_RGB}, {addr(0x0010c148), scrCommand_SCENE_FOG_PARA},
    {addr(0x0010c280), scrCommand_SOFTEN_BIAS},   {addr(0x0010c2d8), scrCommand_BLUR},          {addr(0x0010c330), scrCommand_MUL_BLUR_PARA},
    {addr(0x0010c3b8), scrCommand_MUL_BLUR_RGBA}, {addr(0x0010c440), scrCommand_MUL_BLUR_AREA},
    {addr(0x0010c498), scrCommand_MUL_BLUR_SWAP}, {addr(0x0010c4c0), scrCommand_MUL_BLUR_ON},
    {addr(0x0010c4e8), scrCommand_MUL_BLUR_OFF},  {addr(0x0010c510), scrCommand_DIST_BLUR_PARA},
    {addr(0x0010c5f8), scrCommand_DIST_BLUR_RGBA}, {addr(0x0010c680), scrCommand_DIST_BLUR_AREA},
    {addr(0x0010c6d8), scrCommand_DIST_BLUR_SWAP}, {addr(0x0010c700), scrCommand_DIST_BLUR_ON},
    {addr(0x0010c728), scrCommand_DIST_BLUR_OFF}, {addr(0x0010c750), scrCommand_RIP_BLUR_PARA},
    {addr(0x0010c838), scrCommand_RIP_BLUR_RGBA}, {addr(0x0010c8c0), scrCommand_RIP_BLUR_AREA},
    {addr(0x0010c918), scrCommand_RIP_BLUR_SWAP}, {addr(0x0010c940), scrCommand_RIP_BLUR_ON},
    {addr(0x0010c968), scrCommand_RIP_BLUR_OFF},  {addr(0x0010c990), scrCommand_BLUR2_PARA},
    {addr(0x0010ca30), scrCommand_BLUR2_RGBA},    {addr(0x0010cab8), scrCommand_BLUR2_AREA},
    {addr(0x0010caf8), scrCommand_BLUR2_SWAP},    {addr(0x0010cb20), scrCommand_BLUR2_ON},
    {addr(0x0010cb48), scrCommand_BLUR2_OFF},     {addr(0x0010cb70), scrCommand_FILTER2_PARA},
    {addr(0x0010cbf0), scrCommand_FILTER2_RGBA},  {addr(0x0010cc78), scrCommand_FILTER2_SWAP},
    {addr(0x0010cca0), scrCommand_FILTER2_ON},    {addr(0x0010ccc8), scrCommand_FILTER2_OFF},
    {addr(0x0010ccf0), scrCommand_MFILTER_PARA},  {addr(0x0010cd70), scrCommand_MFILTER_RGBA},
    {addr(0x0010cdf8), scrCommand_MFILTER_AREA},  {addr(0x0010ce50), scrCommand_MFILTER_SWAP},
    {addr(0x0010ce78), scrCommand_MFILTER_ON},    {addr(0x0010cea0), scrCommand_MFILTER_OFF},
    {addr(0x0010cec8), scrCommand_BLUR_ALLOFF},   {addr(0x0010cf10), scrCommand_FILTER_ALLOFF},
    // scrParameterCommand
    {addr(0x0010cf38), addItem},            {addr(0x0010cf78), addMagatama},
    {addr(0x0010cfa0), equipMagatama},             {addr(0x0010cfe0), addMacca},
    {addr(0x0010d008), addMaccaPercent},        {addr(0x0010d030), hasMacca},
    {addr(0x0010d078), damageParty},         {addr(0x0010d0a0), healStock},
    {addr(0x0010d0d0), healStockSilently},       {addr(0x0010d0f0), addDevil},
    {addr(0x0010d1a0), hasDevil},             {addr(0x0010d1f0), storyDevilLeaves},
    {addr(0x0010d248), hasStoryDevil},            {addr(0x0010d298), storyDevilId},
    {addr(0x0010d2c8), storyDevilMayLeave},        {addr(0x0010d330), storyDevilMayNotLeave},
    {addr(0x0010d390), growStock},           {addr(0x0010d3d0), stockFull},
    {addr(0x0010d410), playerStat},     {addr(0x0010d440), addPlayerStat},
    {addr(0x0010d480), devilStat},     {addr(0x0010d4c8), playerAlignment},
    {addr(0x0010d4f0), playerLevel},     {addr(0x0010d518), devilDies},
    {addr(0x0010d540), isFirstPixie},    {addr(0x0010d5e8), firstPixieId},
    {addr(0x0010d658), recordBossPress},       {addr(0x0010d6a0), copyDevilStats},
};

} // namespace

int32_t CallCommand(uint32_t entry)
{
    for (const Command& c : kCommands)
        if (c.entry == entry)
            return c.function();
    return guest::callCommand(entry);
}

} // namespace nocturne::scr
