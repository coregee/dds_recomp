// The kernel's screen state (original unit: dds3KernelDraw): the camera's
// field of view, lights and fog, the screen quake, the screen blur and the
// event effects (effect/event.hpp) faded in, out or between settings over a
// number of frames.
//
// Records are in their PS2 layout; names are the HD remaster's.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/effect/event.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne::dds3 {

// The effects and fades in progress (dds3DrawFlag, 0x54E95C): each runs for
// its frames in dds3BlurUpdate and clears its bit when done.
enum DrawFlag : uint32_t {
    kAmbientFade     = 0x100,
    kFogColorFade    = 0x200,
    kFogParamFade    = 0x400,
    kScreenBlurFade  = 0x800,
    kMultiBlurFade   = 0x1000,     // in or out
    kDistBlurFade    = 0x2000,
    kSoftenBiasFade  = 0x4000,     // and light n's colour 0x4 << 2n, direction 0x8 << 2n
    kMultiBlurSwap   = 0x8000,     // from the current settings to new ones
    kDistBlurSwap    = 0x10000,
    kBlur2Fade       = 0x20000,
    kBlur2Swap       = 0x40000,
    kFilter2Fade     = 0x80000,
    kFilter2Swap     = 0x100000,
    kMFilterFade     = 0x200000,
    kMFilterSwap     = 0x400000,
    kRipBlurFade     = 0x800000,
    kRipBlurSwap     = 0x1000000,
};
uint32_t& dds3DrawFlag();

// The screen quake (0x54E970).
struct Quake {
    uint16_t dds3QuakeFlag;      // shaking
    int16_t dds3QuakeFrame;      // frames left, or -1 until stopped
    uint16_t dds3QuakeXRange;
    uint16_t dds3QuakeYRange;
};
static_assert(sizeof(Quake) == 8);
Quake& quake();

// The screen blur (0x54E960): the last frame drawn over the next.
struct ScreenBlur {
    uint8_t dds3ScreenBlurFlag;
    uint8_t pad;
    int16_t dds3ScreenBlurAlpha;
    int16_t dds3ScreenBlurScale;
};
ScreenBlur& screenBlur();

// A screen blur fade (0x551BAC).
struct BlurFade {
    uint16_t blurnow, blurmax;
    int16_t bluralphabase, blurscalebase;
    int16_t bluralphatarget, blurscaletarget;
};
BlurFade& blurFade();

// An effect's fades: in or out (its alpha from abase to atarget), and a swap
// from the settings drawn now to the target settings.
struct EffectFade {
    uint16_t now, max;
    uint16_t abase, atarget;
    uint16_t swapnow, swapmax;
};
static_assert(sizeof(EffectFade) == 12);

// An effect's settings: those drawn when a swap started, and the target
// (each 8-byte aligned).
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4324)   // padded for alignment: the PS2 layout
#endif
template <class Param> struct EffectSettings {
    alignas(8) Param base;
    alignas(8) Param target;
};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

// The six event effects: their fades (0x551C10) and settings (0x5572C0).
struct EffectFades {
    EffectFade mulblur, distblur, ripblur, blur2, filter2, mfilter;
};
static_assert(sizeof(EffectFades) == 0x48);
struct Effects {
    EffectSettings<eff::PartialMultiBlurParam> mulblur;
    EffectSettings<eff::DistortionBlurParam> distblur;
    EffectSettings<eff::RippleBlurParam> ripblur;
    EffectSettings<eff::Blur> blur2;
    EffectSettings<eff::Filter> filter2;
    EffectSettings<eff::PartialMultiFilterParam> mfilter;
};
static_assert(offsetof(Effects, distblur) == 0x60 && offsetof(Effects, blur2) == 0x120);
static_assert(offsetof(Effects, filter2) == 0x170 && offsetof(Effects, mfilter) == 0x1a0 && sizeof(Effects) == 0x1f0);
EffectFades& effectFades();
Effects& effects();

// Settings refused for being too large (0x54E97C, 0x54E980).
int32_t& distblurovercnt();
int32_t& ripblurovercnt();

// sdf3DFogParam_t
struct FogParam {
    ee::Float fogMax, fogMin, fogNear, fogFar;
    uint32_t color;
};
static_assert(sizeof(FogParam) == 0x14);

// A VU0 vector (Vector4 in the HD remaster): a colour (0..1, or 0..2 for
// lights) or a direction.
struct Vector4 {
    ee::Float x, y, z, w;
};

// sdf3DLight_t (the part used here)
struct Light {
    Vector4 color;
    Vector4 v;                   // direction
    Vector4 p;
};

// The lights', ambient light's, fog's and soften / bias fades (0x551BC0).
// A colour fades between two packed colours (0xAABBGGRR); lights hold up
// to 4 (the direction fades: 3).
struct SceneFades {
    uint16_t lightrgbnow[4], lightrgbmax[4];
    uint16_t lightdirnow[4], lightdirmax[3];
    uint16_t ambientnow, ambientmax, pad;
    uint32_t ambientbase, ambienttarget;
    uint16_t fogrgbnow, fogrgbmax;
    uint16_t fogparanow, fogparamax;
    uint32_t fogrgbbase, fogrgbtarget;
    uint16_t sbnow, sbmax;
    ee::Float softenbase, softentarget, biasbase, biastarget;
};
static_assert(offsetof(SceneFades, ambientnow) == 0x1e && offsetof(SceneFades, fogrgbnow) == 0x2c);
static_assert(offsetof(SceneFades, softenbase) == 0x40 && sizeof(SceneFades) == 0x50);
SceneFades& sceneFades();

// The light colours' packed ends (0x557220), the light directions' start
// and the rotation to the end (a quaternion), and the fog parameters' ends
// (0x5572A0, 0x5572B0).
struct SceneTargets {
    uint32_t lightrgbbase[4], lightrgbtarget[4];
    Vector4 lightdirbase[3], lightdirquat[3];
};
static_assert(sizeof(SceneTargets) == 0x80);
SceneTargets& sceneTargets();
Vector4& fogparabase();
Vector4& fogparatarget();

// ---- the camera, lights and fog ----
void dds3SetScreenFovy(ee::Float fovy);
void dds3SetAmbient(const uint32_t (&ambient)[4]);
void dds3SetFog(const FogParam& fog);
void dds3SetLight(uint32_t light, int32_t no);
void setdraw_xy(eff::IVector2 (&xy)[2]);
// Colours at once or over `frame` frames (dds3SceneLightUpdateFirst runs the fades).
void dds3SetLightColor(uint32_t frame, uint32_t no, const Vector4& col);
void dds3SetLightDir(uint32_t frame, uint32_t no, const Vector4& dir);
void dds3SetAmbientColor(uint32_t frame, const Vector4& col);
// The rotation (a quaternion) taking direction `from` to `to`.
Vector4 dds3RotationArc(Vector4 from, Vector4 to);
Vector4 ps2QuaternionNormalize(const Vector4& q);
void dds3SetFogColor(uint32_t frame, const Vector4& col);
void dds3SetFogPara(uint32_t frame, ee::Float max, ee::Float min, ee::Float near, ee::Float far);
void dds3SetSoftenBias(uint32_t frame, ee::Float soften, ee::Float bias);

// ---- the quake and the screen blur ----
void dds3SetQuake(int32_t frame, uint32_t range);
void dds3StopQuake();
void dds3SetBlur(uint32_t frame, int32_t alpha, int32_t scale);

// ---- the event effects ----
// Para / RGBA / Area set the target; Swap moves to it over `frame` frames
// (0: at once); On / Off fade the effect in or out (0: at once).
void dds3SetFilter2Para(int32_t blend);
void dds3SetFilter2RGBA(uint32_t rgba);
void dds3Filter2Swap(int32_t frame);
void dds3Filter2On(int32_t frame);
void dds3Filter2Off(int32_t frame);
void dds3SetMFilterPara(int32_t blend);
void dds3SetMFilterRGBA(uint32_t rgba);
void dds3SetMFilterArea(int32_t area, int32_t posx, int32_t posy);
void dds3MFilterSwap(int32_t frame);
void dds3MFilterOn(int32_t frame);
void dds3MFilterOff(int32_t frame);
void dds3SetBlur2Para(ee::Float rotate, ee::Float scale, int32_t blend);
void dds3SetBlur2RGBA(uint32_t rgba);
void dds3SetBlur2Area(int32_t posx, int32_t posy);
void dds3Blur2Swap(int32_t frame);
void dds3Blur2On(int32_t frame);
void dds3Blur2Off(int32_t frame);
void dds3SetMultiBlurPara(ee::Float rotate, ee::Float scale, int32_t blend);
void dds3SetMultiBlurRGBA(uint32_t rgba);
void dds3SetMultiBlurArea(int32_t area, int32_t posx, int32_t posy);
void dds3MultiBlurSwap(int32_t frame);
void dds3MultiBlurOn(int32_t frame);
void dds3MultiBlurOff(int32_t frame);
void dds3SetDistBlurPara(int32_t number, int32_t width, int32_t intval, int32_t blend, ee::Float speed, ee::Float rotate,
                         ee::Float distor);
void dds3SetDistBlurRGBA(uint32_t rgba);
void dds3SetDistBlurArea(int32_t area, int32_t posx, int32_t posy);
void dds3DistBlurSwap(int32_t frame);
void dds3DistBlurOn(int32_t frame);
void dds3DistBlurOff(int32_t frame);
void dds3SetRipBlurPara(ee::Float speed, ee::Float intval, ee::Float rotate, ee::Float distor, ee::Float distor_s,
                        int32_t number, int32_t blend);
void dds3SetRipBlurRGBA(uint32_t rgba);
void dds3SetRipBlurArea(int32_t area, int32_t posx, int32_t posy);
void dds3RipBlurSwap(int32_t frame);
void dds3RipBlurOn(int32_t frame);
void dds3RipBlurOff(int32_t frame);

} // namespace nocturne::dds3
