// The event screen effects' switches and parameters (original unit: effEvent).
#include "nocturne/effect/event.hpp"

#include "nocturne/address.hpp"

namespace nocturne::eff {

namespace {

// The library's objects for the partial effects (made by Eve_EffectInit).
struct Objects {
    Ptr32<DistortionBlur> distortionBlur;
    Ptr32<PartialMultiBlur> multiBlur;
    Ptr32<PartialMultiFilter> multiFilter;
    Ptr32<RippleBlur> rippleBlur;
};
Objects& objects() { return *guest::table<Objects>(addr(0x00551de8)); }

} // namespace

Switches& switches() { return *guest::table<Switches>(addr(0x0054f278)); }
Blur& blurParam() { return *guest::table<Blur>(addr(0x003201d0)); }
Filter& filterParam() { return *guest::table<Filter>(addr(0x00320258)); }
PartialMultiBlur* multiBlur() { return objects().multiBlur.get(); }
DistortionBlur* distortionBlur() { return objects().distortionBlur.get(); }
PartialMultiFilter* multiFilter() { return objects().multiFilter.get(); }
RippleBlur* rippleBlur() { return objects().rippleBlur.get(); }

// Eve_BlurON @ 0x001AD230
void Eve_BlurON() { switches().blur = 1; }
// Eve_BlurOFF @ 0x001AD240
void Eve_BlurOFF() { switches().blur = 0; }
// Eve_BlurSetParam @ 0x001AD248
void Eve_BlurSetParam(const Blur& param) { blurParam() = param; }
// Eve_BlurGetParam @ 0x001AD2A8
Blur* Eve_BlurGetParam() { return &blurParam(); }

// Eve_PartialMultiBlurON @ 0x001AD2B8
void Eve_PartialMultiBlurON() { switches().multiBlur = 1; }
// Eve_PartialMultiBlurOFF @ 0x001AD2C8
void Eve_PartialMultiBlurOFF() { switches().multiBlur = 0; }
// Eve_PartialMultiBlurSetParam @ 0x001AD2D0
void Eve_PartialMultiBlurSetParam(const PartialMultiBlurParam& param) { multiBlur()->param = param; }
// Eve_PartialMultiBlurEditorGetParams @ 0x001AD330
PartialMultiBlurParam* Eve_PartialMultiBlurEditorGetParams() { return &multiBlur()->param; }

// Eve_DistortionBlurON @ 0x001AD370
void Eve_DistortionBlurON() { switches().distortionBlur = 1; }
// Eve_DistortionBlurOFF @ 0x001AD380
void Eve_DistortionBlurOFF() { switches().distortionBlur = 0; }
// Eve_DistortionBlurSetParam @ 0x001AD388
void Eve_DistortionBlurSetParam(const DistortionBlurParam& param) { distortionBlur()->param = param; }
// Eve_DistortionBlurEditorGetParams @ 0x001AD3E8
DistortionBlurParam* Eve_DistortionBlurEditorGetParams() { return &distortionBlur()->param; }
// Eve_DistortionBlurSetTex @ 0x001AD3F0
void Eve_DistortionBlurSetTex(uint32_t texture) { distortionBlur()->texture = texture; }

// Eve_RippleBlurON @ 0x001AD428
void Eve_RippleBlurON() { switches().rippleBlur = 1; }
// Eve_RippleBlurOFF @ 0x001AD438
void Eve_RippleBlurOFF() { switches().rippleBlur = 0; }
// Eve_RippleBlurSetParam @ 0x001AD440
void Eve_RippleBlurSetParam(const RippleBlurParam& param) { rippleBlur()->param = param; }
// Eve_RippleBlurEditorGetParams @ 0x001AD4A0
RippleBlurParam* Eve_RippleBlurEditorGetParams() { return &rippleBlur()->param; }

// Eve_FilterON @ 0x001AD4E0
void Eve_FilterON() { switches().filter = 1; }
// Eve_FilterOFF @ 0x001AD4F0
void Eve_FilterOFF() { switches().filter = 0; }
// Eve_FilterSetParam @ 0x001AD4F8
void Eve_FilterSetParam(const Filter& param) { filterParam() = param; }
// Eve_FilterEditorGetParams @ 0x001AD538
Filter* Eve_FilterEditorGetParams() { return &filterParam(); }

// Eve_PartialMultiFilterON @ 0x001AD548
void Eve_PartialMultiFilterON() { switches().multiFilter = 1; }
// Eve_PartialMultiFilterOFF @ 0x001AD558
void Eve_PartialMultiFilterOFF() { switches().multiFilter = 0; }
// Eve_PartialMultiFilterSetParam @ 0x001AD560
void Eve_PartialMultiFilterSetParam(const PartialMultiFilterParam& param) { multiFilter()->param = param; }
// Eve_PartialMultiFilterEditorGetParams @ 0x001AD5B0
PartialMultiFilterParam* Eve_PartialMultiFilterEditorGetParams() { return &multiFilter()->param; }

} // namespace nocturne::eff
