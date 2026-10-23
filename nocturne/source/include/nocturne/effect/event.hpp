// The screen effects the event scripts drive (original unit: effEvent, the
// HD remaster's effBlur_Filter records): a whole-screen blur and filter, and
// partial (masked) multi-blur, distortion blur, ripple blur and multi-filter.
// Each is switched on or off and given its parameters here; drawing them is
// the effect library's part (not rewritten yet).
//
// Records are in their PS2 layout; field names are the HD remaster's.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/ee/float.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

// sdfIVector2_t
struct IVector2 {
    int32_t x, y;
};

// dds3Effect_Blur_t: the screen drawn over itself, rotated and scaled.
struct Blur {
    uint32_t abgr;               // colour and alpha (0xAABBGGRR)
    int32_t blend;               // the GS alpha blend (0x44, 0x48, 0x42; see docs/flowscript.md)
    ee::Float rotate;
    ee::Float scale;
    IVector2 center;
    IVector2 xy[2];              // the screen rectangle
};
static_assert(sizeof(Blur) == 0x28);

// dds3Effect_PartialMultiBlurParam_t
struct PartialMultiBlurParam {
    int32_t area;
    Blur blur;
};
static_assert(sizeof(PartialMultiBlurParam) == 0x2c);

// dds3Effect_DistortionBlurParam_t
struct DistortionBlurParam {
    uint32_t number;
    uint32_t interval;
    ee::Float speed;
    uint32_t abgr;
    int32_t blend;
    ee::Float rotate;
    ee::Float distortion;
    IVector2 center;
    int32_t area;
    int32_t width;
};
static_assert(sizeof(DistortionBlurParam) == 0x2c);

// dds3Effect_RippleBlurParam_t
struct RippleBlurParam {
    uint32_t number;
    ee::Float speed;
    ee::Float interval;
    uint32_t abgr;
    int32_t blend;
    ee::Float rotate;
    ee::Float power;
    ee::Float frequency;
    IVector2 center;
    int32_t area;
};
static_assert(sizeof(RippleBlurParam) == 0x2c);

// dds3Effect_Filter_t: a coloured rectangle over the screen.
struct Filter {
    uint32_t abgr;
    int32_t blend;
    IVector2 xy[2];
};
static_assert(sizeof(Filter) == 0x18);

// dds3Effect_PartialMultiFilterParam_t
struct PartialMultiFilterParam {
    int32_t area;
    IVector2 center;
    Filter filter;
};
static_assert(sizeof(PartialMultiFilterParam) == 0x24);

// The partial effects are objects the library created (Eve_EffectInit);
// their parameters come first, then the texture they draw with.
template <class Param> struct Object {
    Param param;
    uint32_t texture;
};
using PartialMultiBlur = Object<PartialMultiBlurParam>;
using DistortionBlur = Object<DistortionBlurParam>;
using RippleBlur = Object<RippleBlurParam>;
using PartialMultiFilter = Object<PartialMultiFilterParam>;
static_assert(offsetof(DistortionBlur, texture) == 0x2c && offsetof(PartialMultiFilter, texture) == 0x24);

// Which effects are drawn (0x54F278).
struct Switches {
    uint8_t blur, multiBlur, distortionBlur, filter, multiFilter, rippleBlur;
};

// The effects' state.
Switches& switches();
Blur& blurParam();               // 0x3201D0
Filter& filterParam();           // 0x320258
PartialMultiBlur* multiBlur();   // the library's objects (0x551DE8..)
DistortionBlur* distortionBlur();
PartialMultiFilter* multiFilter();
RippleBlur* rippleBlur();

void Eve_BlurON();
void Eve_BlurOFF();
void Eve_BlurSetParam(const Blur& param);
Blur* Eve_BlurGetParam();
void Eve_PartialMultiBlurON();
void Eve_PartialMultiBlurOFF();
void Eve_PartialMultiBlurSetParam(const PartialMultiBlurParam& param);
PartialMultiBlurParam* Eve_PartialMultiBlurEditorGetParams();
void Eve_DistortionBlurON();
void Eve_DistortionBlurOFF();
void Eve_DistortionBlurSetParam(const DistortionBlurParam& param);
DistortionBlurParam* Eve_DistortionBlurEditorGetParams();
void Eve_DistortionBlurSetTex(uint32_t texture);
void Eve_RippleBlurON();
void Eve_RippleBlurOFF();
void Eve_RippleBlurSetParam(const RippleBlurParam& param);
RippleBlurParam* Eve_RippleBlurEditorGetParams();
void Eve_FilterON();
void Eve_FilterOFF();
void Eve_FilterSetParam(const Filter& param);
Filter* Eve_FilterEditorGetParams();
void Eve_PartialMultiFilterON();
void Eve_PartialMultiFilterOFF();
void Eve_PartialMultiFilterSetParam(const PartialMultiFilterParam& param);
PartialMultiFilterParam* Eve_PartialMultiFilterEditorGetParams();

} // namespace nocturne::eff
