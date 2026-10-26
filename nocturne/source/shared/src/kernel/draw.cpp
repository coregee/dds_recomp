// The kernel's screen state (original unit: dds3KernelDraw).
#include "nocturne/kernel/draw.hpp"

#include "nocturne/address.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::dds3 {

namespace {

ee::Float& fovy() { return *guest::table<ee::Float>(addr(0x002f59bc)); }   // dds3ScreenParam.fovy
uint32_t* lights() { return guest::table<uint32_t>(addr(0x002f5b40)); }    // dds3DirLights: sdf3DLight_t*[]
uint32_t* ambient() { return guest::table<uint32_t>(addr(0x002f5b50)); }   // dds3Ambient
FogParam& fog() { return *guest::table<FogParam>(addr(0x002f5b60)); }      // dds3FogParam
ee::Float& soften() { return *guest::table<ee::Float>(addr(0x005518a8)); }  // the models' softening
ee::Float& bias() { return *guest::table<ee::Float>(addr(0x005518ac)); }

// A colour packed as the GS takes it (0xAABBGGRR): each lane scaled,
// truncated to an int and cut to its low byte (VFTOI0, PPACH, PPACB).
uint32_t pack(const Vector4& v, ee::Float scale)
{
    const ee::Float lanes[4] = {v.x, v.y, v.z, v.w};
    uint32_t out = 0;
    for (int i = 0; i < 4; ++i)
        out |= (static_cast<uint32_t>((lanes[i] * scale).toInt()) & 0xff) << (8 * i);
    return out;
}

// Vector operations as the VU0 code does them, lane by lane with the PS2's
// float rules (the multiplications by 1 are vf0.w's; they keep the
// hardware's handling of the products).
const ee::Float kOne = 1.0f;

// x*x + y*y + z*z (VMUL, VMULAx, VMADDAy, VMADDz)
ee::Float lengthSquared(const Vector4& v)
{
    const ee::Float x = v.x * v.x, y = v.y * v.y, z = v.z * v.z;
    return kOne * x + kOne * y + kOne * z;
}

// The xyz lanes scaled to length 1 (VRSQRT, VMULq); w untouched.
void normalize(Vector4& v)
{
    const ee::Float q = rsqrt(kOne, lengthSquared(v));
    v.x = v.x * q;
    v.y = v.y * q;
    v.z = v.z * q;
}

// (x*x' + y*y') + z*z' (VMUL, VADDy, VADDz)
ee::Float dot(const Vector4& a, const Vector4& b)
{
    const ee::Float x = a.x * b.x, y = a.y * b.y, z = a.z * b.z;
    return x + y + z;
}

// a x b in xyz (VOPMULA, VOPMSUB); w untouched.
void crossInto(Vector4& a, const Vector4& b)
{
    const ee::Float x = a.y * b.z - b.y * a.z;
    const ee::Float y = a.z * b.x - b.z * a.x;
    const ee::Float z = a.x * b.y - b.x * a.y;
    a.x = x;
    a.y = y;
    a.z = z;
}

// A colour's alpha as the setters store it: 0 (the w lane times vf0.x).
Vector4 withoutAlpha(Vector4 v)
{
    v.w = v.w * ee::Float(0.0f);
    return v;
}

void setFlags(uint32_t bits) { dds3DrawFlag() |= bits; }
void clearFlags(uint32_t bits) { dds3DrawFlag() &= ~bits; }

uint16_t alphaOf(uint32_t abgr) { return static_cast<uint16_t>(abgr >> 24); }

// A fade in from nothing to the target's alpha, or out from it.
void fadeIn(EffectFade& f, uint32_t abgr, int32_t frame)
{
    f.now = 0;
    f.abase = 0;
    f.atarget = alphaOf(abgr);
    f.max = static_cast<uint16_t>(frame);
}

void fadeOut(EffectFade& f, uint32_t abgr, int32_t frame)
{
    f.now = 0;
    f.abase = alphaOf(abgr);
    f.atarget = 0;
    f.max = static_cast<uint16_t>(frame);
}

void startSwap(EffectFade& f, int32_t frame)
{
    f.swapnow = 0;
    f.swapmax = static_cast<uint16_t>(frame);
}

} // namespace

uint32_t& dds3DrawFlag() { return *guest::table<uint32_t>(addr(0x0054e95c)); }
Quake& quake() { return *guest::table<Quake>(addr(0x0054e970)); }
ScreenBlur& screenBlur() { return *guest::table<ScreenBlur>(addr(0x0054e960)); }
BlurFade& blurFade() { return *guest::table<BlurFade>(addr(0x00551bac)); }
EffectFades& effectFades() { return *guest::table<EffectFades>(addr(0x00551c10)); }
Effects& effects() { return *guest::table<Effects>(addr(0x005572c0)); }
SceneFades& sceneFades() { return *guest::table<SceneFades>(addr(0x00551bc0)); }
SceneTargets& sceneTargets() { return *guest::table<SceneTargets>(addr(0x00557220)); }

// dds3GetActiveScene @ 0x0010E548: through the scene list (0x54E9C4) to its
// current entry (+0x18) and that one's scene (+0x8) (tentative names).
uint32_t dds3GetActiveScene()
{
    const uint32_t list = *guest::table<const uint32_t>(addr(0x0054e9c4));
    if (list == 0)
        return 0;
    const uint32_t current = *guest::table<const uint32_t>(list + 0x18);
    return *guest::table<const uint32_t>(current + 0x8);
}
Vector4& fogparabase() { return *guest::table<Vector4>(addr(0x005572a0)); }
Vector4& fogparatarget() { return *guest::table<Vector4>(addr(0x005572b0)); }
int32_t& distblurovercnt() { return *guest::table<int32_t>(addr(0x0054e97c)); }
int32_t& ripblurovercnt() { return *guest::table<int32_t>(addr(0x0054e980)); }

// ---- the camera, lights and fog -----------------------------------------------------------

// dds3SetScreenFovy @ 0x00105580
void dds3SetScreenFovy(ee::Float value) { fovy() = value; }

// dds3SetAmbient @ 0x00105590
void dds3SetAmbient(const uint32_t (&value)[4])
{
    for (int i = 0; i < 4; ++i)
        ambient()[i] = value[i];
}

// dds3SetFog @ 0x001055A8
void dds3SetFog(const FogParam& value) { fog() = value; }

// dds3SetLight @ 0x001055E0: directional light `no` (an sdf3DLight_t, or 0 for none).
void dds3SetLight(uint32_t light, int32_t no) { lights()[no] = light; }

// setdraw_xy @ 0x001055F8: the whole screen (512 x 448).
void setdraw_xy(eff::IVector2 (&xy)[2])
{
    xy[1] = {0x200, 0x1c0};
    xy[0] = {0, 0};
}

// dds3SetLightColor @ 0x001070D0
// Light `no`'s colour (if the light exists): at once, or a fade from its
// colour now to `col`, both packed at half intensity (x 128).
void dds3SetLightColor(uint32_t frame, uint32_t no, const Vector4& col)
{
    if (!lights()[no])
        return;
    Light* light = guest::table<Light>(lights()[no]);
    const uint32_t bit = 0x4u << (2 * no);
    if (frame == 0) {
        clearFlags(bit);
        light->color = withoutAlpha(col);
        return;
    }
    SceneFades& f = sceneFades();
    f.lightrgbmax[no] = static_cast<uint16_t>(frame);
    setFlags(bit);
    f.lightrgbnow[no] = 0;
    sceneTargets().lightrgbbase[no] = pack(light->color, ee::Float(128.0f));
    sceneTargets().lightrgbtarget[no] = pack(withoutAlpha(col), ee::Float(128.0f));
}

// dds3SetLightDir @ 0x001071D0
// Light `no`'s direction, normalized: at once, or a turn over `frame`
// frames from its direction now, kept as the start and the rotation.
void dds3SetLightDir(uint32_t frame, uint32_t no, const Vector4& dir)
{
    if (!lights()[no])
        return;
    Light* light = guest::table<Light>(lights()[no]);
    const uint32_t bit = 0x8u << (2 * no);
    if (frame == 0) {
        clearFlags(bit);
        Vector4 v = dir;
        normalize(v);
        light->v = withoutAlpha(v);
        return;
    }
    SceneFades& f = sceneFades();
    f.lightdirmax[no] = static_cast<uint16_t>(frame);
    setFlags(bit);
    f.lightdirnow[no] = 0;
    Vector4 target = withoutAlpha(dir);
    normalize(target);
    Vector4 current = withoutAlpha(light->v);
    normalize(current);
    sceneTargets().lightdirbase[no] = current;
    sceneTargets().lightdirquat[no] = dds3RotationArc(current, target);
}

// dds3RotationArc @ 0x00106EE0 (vectors passed in vf10 and vf11)
// Nearly the same directions: no rotation. Nearly opposite: half a turn
// about an axis at right angles to `from`. Otherwise: about the cross
// product, by way of the half-way vector.
Vector4 dds3RotationArc(Vector4 from, Vector4 to)
{
    from = withoutAlpha(from);
    normalize(from);
    to = withoutAlpha(to);
    normalize(to);
    const ee::Float same = *guest::table<ee::Float>(addr(0x0054c18c));       // 0.9999
    const ee::Float opposite = *guest::table<ee::Float>(addr(0x0054c190));   // -0.9999
    const ee::Float d = dot(from, to);
    if (same <= d)
        return {0.0f, 0.0f, 0.0f, 1.0f};
    if (d <= opposite) {
        Vector4 axis;
        if (same <= from.y.abs()) {
            axis = {ee::Float::fromBits(0), ee::Float::fromBits(0), ee::Float(0.0f) + ee::Float(-1.0f), kOne * ee::Float(0.0f)};
        } else {
            axis = {ee::Float::fromBits(from.z.bits() ^ 0x80000000u), ee::Float::fromBits(0), from.x, ee::Float::fromBits(0)};
            normalize(axis);
        }
        const ee::Float w = dot(axis, to);
        crossInto(axis, to);
        axis.w = kOne * w;
        return axis;
    }
    Vector4 half = {from.x + to.x, from.y + to.y, from.z + to.z, from.w + to.w};
    normalize(half);
    const ee::Float w = dot(half, from);
    crossInto(half, from);
    half.w = kOne * w;
    return ps2QuaternionNormalize(half);
}

// ps2QuaternionNormalize @ 0x002C04E8 (in vf10): all four lanes.
Vector4 ps2QuaternionNormalize(const Vector4& q)
{
    const ee::Float x = q.x * q.x, y = q.y * q.y, z = q.z * q.z, w = q.w * q.w;
    const ee::Float scale = rsqrt(kOne, w + x + kOne * y + kOne * z);
    return {q.x * scale, q.y * scale, q.z * scale, q.w * scale};
}

// dds3SetAmbientColor @ 0x00107310 (the alpha is 1)
void dds3SetAmbientColor(uint32_t frame, const Vector4& col)
{
    Vector4 color = col;
    color.w = ee::Float(1.0f);
    Vector4& ambient = *guest::table<Vector4>(addr(0x002f5b50));
    if (frame == 0) {
        clearFlags(kAmbientFade);
        ambient = color;
        return;
    }
    SceneFades& f = sceneFades();
    f.ambientmax = static_cast<uint16_t>(frame);
    setFlags(kAmbientFade);
    f.ambientnow = 0;
    f.ambientbase = pack(ambient, ee::Float(128.0f));
    f.ambienttarget = pack(color, ee::Float(128.0f));
}

// dds3SetFogColor @ 0x001073D0: packed at full intensity (x 255).
void dds3SetFogColor(uint32_t frame, const Vector4& col)
{
    const uint32_t color = pack(withoutAlpha(col), ee::Float(255.0f));
    if (frame == 0) {
        clearFlags(kFogColorFade);
        fog().color = color;
        return;
    }
    SceneFades& f = sceneFades();
    setFlags(kFogColorFade);
    f.fogrgbmax = static_cast<uint16_t>(frame);
    f.fogrgbtarget = color;
    f.fogrgbbase = fog().color;
    f.fogrgbnow = 0;
}

// dds3SetFogPara @ 0x00107458
void dds3SetFogPara(uint32_t frame, ee::Float max, ee::Float min, ee::Float near, ee::Float far)
{
    FogParam& now = fog();
    if (frame == 0) {
        now.fogFar = far;
        clearFlags(kFogParamFade);
        now.fogMax = max;
        now.fogMin = min;
        now.fogNear = near;
        return;
    }
    fogparabase() = {now.fogMax, now.fogMin, now.fogNear, now.fogFar};
    fogparatarget() = {max, min, near, far};
    setFlags(kFogParamFade);
    sceneFades().fogparamax = static_cast<uint16_t>(frame);
    sceneFades().fogparanow = 0;
}

// dds3SetSoftenBias @ 0x00107AF0
void dds3SetSoftenBias(uint32_t frame, ee::Float softenValue, ee::Float biasValue)
{
    if (frame == 0) {
        soften() = softenValue;
        clearFlags(kSoftenBiasFade);
        bias() = biasValue;
        return;
    }
    SceneFades& f = sceneFades();
    setFlags(kSoftenBiasFade);
    f.sbmax = static_cast<uint16_t>(frame);
    f.softenbase = soften();
    f.softentarget = softenValue;
    f.biasbase = bias();
    f.biastarget = biasValue;
    f.sbnow = 0;
}

// ---- the quake and the screen blur ---------------------------------------------------------

// dds3SetQuake @ 0x00104D38
// Shakes the view for `frame` frames (0: until stopped). The vertical range
// is `range` tenths; the horizontal one is 0.4 of it.
void dds3SetQuake(int32_t frame, uint32_t range)
{
    Quake& q = quake();
    if (range == 0) {
        q.dds3QuakeFlag = 0;
        return;
    }
    q.dds3QuakeFlag = 1;
    q.dds3QuakeFrame = static_cast<int16_t>(frame ? frame : -1);
    const uint16_t y = static_cast<uint16_t>(range * 10);
    q.dds3QuakeYRange = y;
    q.dds3QuakeXRange = static_cast<uint16_t>(y * 4 / 10);
}

// dds3StopQuake @ 0x00104D98
void dds3StopQuake() { quake().dds3QuakeFlag = 0; }

// dds3SetBlur @ 0x001059E8
// The screen blur's alpha and scale, at once or over `frame` frames; it is
// on while either is not 0.
void dds3SetBlur(uint32_t frame, int32_t alpha, int32_t scale)
{
    ScreenBlur& b = screenBlur();
    if (frame == 0) {
        b.dds3ScreenBlurAlpha = static_cast<int16_t>(alpha);
        b.dds3ScreenBlurScale = static_cast<int16_t>(scale);
        b.dds3ScreenBlurFlag = alpha != 0 || scale != 0;
        clearFlags(kScreenBlurFade);
        return;
    }
    BlurFade& f = blurFade();
    f.bluralphabase = b.dds3ScreenBlurAlpha;
    f.blurscalebase = b.dds3ScreenBlurScale;
    f.bluralphatarget = static_cast<int16_t>(alpha);
    f.blurscaletarget = static_cast<int16_t>(scale);
    f.blurmax = static_cast<uint16_t>(frame);
    setFlags(kScreenBlurFade);
    f.blurnow = 0;
}

// ---- Filter2: the whole-screen filter (Eve_Filter) -----------------------------------------

// dds3SetFilter2Para @ 0x00105618
void dds3SetFilter2Para(int32_t blend) { effects().filter2.target.blend = blend; }

// dds3SetFilter2RGBA @ 0x00105628
void dds3SetFilter2RGBA(uint32_t rgba) { effects().filter2.target.abgr = rgba; }

// dds3Filter2Swap @ 0x00105638
void dds3Filter2Swap(int32_t frame)
{
    EffectSettings<eff::Filter>& s = effects().filter2;
    s.base = *eff::Eve_FilterEditorGetParams();
    startSwap(effectFades().filter2, frame);
    if (frame == 0) {
        clearFlags(kFilter2Swap);
        setdraw_xy(s.target.xy);
        eff::Eve_FilterSetParam(s.target);
        return;
    }
    setFlags(kFilter2Swap);
}

// dds3Filter2On @ 0x00105700
void dds3Filter2On(int32_t frame)
{
    EffectSettings<eff::Filter>& s = effects().filter2;
    fadeIn(effectFades().filter2, s.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kFilter2Fade);
        setdraw_xy(s.target.xy);
        eff::Eve_FilterSetParam(s.target);
        eff::Eve_FilterON();
        return;
    }
    setFlags(kFilter2Fade);
}

// dds3Filter2Off @ 0x00105788
void dds3Filter2Off(int32_t frame)
{
    fadeOut(effectFades().filter2, effects().filter2.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kFilter2Fade | kFilter2Swap);
        eff::Eve_FilterOFF();
        return;
    }
    setFlags(kFilter2Fade);
}

// ---- MFilter: the partial multi-filter -------------------------------------------------------

// dds3SetMFilterPara @ 0x001057F8
void dds3SetMFilterPara(int32_t blend) { effects().mfilter.target.filter.blend = blend; }

// dds3SetMFilterRGBA @ 0x00105808
void dds3SetMFilterRGBA(uint32_t rgba) { effects().mfilter.target.filter.abgr = rgba; }

// dds3SetMFilterArea @ 0x00105818
void dds3SetMFilterArea(int32_t area, int32_t posx, int32_t posy)
{
    eff::PartialMultiFilterParam& t = effects().mfilter.target;
    t.center.y = posy;
    t.area = area;
    t.center.x = posx;
}

// dds3MFilterSwap @ 0x00105830
void dds3MFilterSwap(int32_t frame)
{
    EffectSettings<eff::PartialMultiFilterParam>& s = effects().mfilter;
    s.base = *eff::Eve_PartialMultiFilterEditorGetParams();
    startSwap(effectFades().mfilter, frame);
    if (frame == 0) {
        clearFlags(kMFilterSwap);
        eff::Eve_PartialMultiFilterSetParam(s.target);
        return;
    }
    setFlags(kMFilterSwap);
}

// dds3MFilterOn @ 0x00105900
void dds3MFilterOn(int32_t frame)
{
    EffectSettings<eff::PartialMultiFilterParam>& s = effects().mfilter;
    fadeIn(effectFades().mfilter, s.target.filter.abgr, frame);
    if (frame == 0) {
        clearFlags(kMFilterFade);
        eff::Eve_PartialMultiFilterSetParam(s.target);
        eff::Eve_PartialMultiFilterON();
        return;
    }
    setFlags(kMFilterFade);
}

// dds3MFilterOff @ 0x00105978
void dds3MFilterOff(int32_t frame)
{
    fadeOut(effectFades().mfilter, effects().mfilter.target.filter.abgr, frame);
    if (frame == 0) {
        clearFlags(kMFilterFade | kMFilterSwap);
        eff::Eve_PartialMultiFilterOFF();
        return;
    }
    setFlags(kMFilterFade);
}

// ---- Blur2: the whole-screen blur (Eve_Blur) -------------------------------------------------

// dds3SetBlur2Para @ 0x00105A60
void dds3SetBlur2Para(ee::Float rotate, ee::Float scale, int32_t blend)
{
    eff::Blur& t = effects().blur2.target;
    t.blend = blend;
    t.rotate = rotate;
    t.scale = scale;
}

// dds3SetBlur2RGBA @ 0x00105A78
void dds3SetBlur2RGBA(uint32_t rgba) { effects().blur2.target.abgr = rgba; }

// dds3SetBlur2Area @ 0x00105A88
void dds3SetBlur2Area(int32_t posx, int32_t posy)
{
    eff::Blur& t = effects().blur2.target;
    t.center.y = posy;
    t.center.x = posx;
}

// dds3Blur2Swap @ 0x00105AA0
void dds3Blur2Swap(int32_t frame)
{
    EffectSettings<eff::Blur>& s = effects().blur2;
    s.base = *eff::Eve_BlurGetParam();
    startSwap(effectFades().blur2, frame);
    if (frame == 0) {
        clearFlags(kBlur2Swap);
        setdraw_xy(s.target.xy);
        eff::Eve_BlurSetParam(s.target);
        return;
    }
    setFlags(kBlur2Swap);
}

// dds3Blur2On @ 0x00105B88
void dds3Blur2On(int32_t frame)
{
    EffectSettings<eff::Blur>& s = effects().blur2;
    fadeIn(effectFades().blur2, s.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kBlur2Fade);
        setdraw_xy(s.target.xy);
        eff::Eve_BlurSetParam(s.target);
        eff::Eve_BlurON();
        return;
    }
    setFlags(kBlur2Fade);
}

// dds3Blur2Off @ 0x00105C10
void dds3Blur2Off(int32_t frame)
{
    fadeOut(effectFades().blur2, effects().blur2.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kBlur2Fade | kBlur2Swap);
        eff::Eve_BlurOFF();
        return;
    }
    setFlags(kBlur2Fade);
}

// ---- MultiBlur: the partial multi-blur -------------------------------------------------------

// dds3SetMultiBlurPara @ 0x00105C80
void dds3SetMultiBlurPara(ee::Float rotate, ee::Float scale, int32_t blend)
{
    eff::Blur& t = effects().mulblur.target.blur;
    t.blend = blend;
    t.rotate = rotate;
    t.scale = scale;
}

// dds3SetMultiBlurRGBA @ 0x00105C98
void dds3SetMultiBlurRGBA(uint32_t rgba) { effects().mulblur.target.blur.abgr = rgba; }

// dds3SetMultiBlurArea @ 0x00105CA8
void dds3SetMultiBlurArea(int32_t area, int32_t posx, int32_t posy)
{
    eff::PartialMultiBlurParam& t = effects().mulblur.target;
    t.blur.center.y = posy;
    t.area = area;
    t.blur.center.x = posx;
}

// dds3MultiBlurSwap @ 0x00105CC0
void dds3MultiBlurSwap(int32_t frame)
{
    EffectSettings<eff::PartialMultiBlurParam>& s = effects().mulblur;
    s.base = *eff::Eve_PartialMultiBlurEditorGetParams();
    startSwap(effectFades().mulblur, frame);
    if (frame == 0) {
        clearFlags(kMultiBlurSwap);
        eff::Eve_PartialMultiBlurSetParam(s.target);
        return;
    }
    setFlags(kMultiBlurSwap);
}

// dds3MultiBlurOn @ 0x00105D98
void dds3MultiBlurOn(int32_t frame)
{
    EffectSettings<eff::PartialMultiBlurParam>& s = effects().mulblur;
    fadeIn(effectFades().mulblur, s.target.blur.abgr, frame);
    if (frame == 0) {
        clearFlags(kMultiBlurFade);
        eff::Eve_PartialMultiBlurSetParam(s.target);
        eff::Eve_PartialMultiBlurON();
        return;
    }
    setFlags(kMultiBlurFade);
}

// dds3MultiBlurOff @ 0x00105E00 (unlike the others, it sets the target first)
void dds3MultiBlurOff(int32_t frame)
{
    EffectSettings<eff::PartialMultiBlurParam>& s = effects().mulblur;
    fadeOut(effectFades().mulblur, s.target.blur.abgr, frame);
    if (frame == 0) {
        clearFlags(kMultiBlurFade | kMultiBlurSwap);
        eff::Eve_PartialMultiBlurSetParam(s.target);
        eff::Eve_PartialMultiBlurOFF();
        return;
    }
    setFlags(kMultiBlurFade);
}

// ---- DistBlur: the distortion blur ----------------------------------------------------------

// dds3SetDistBlurPara @ 0x00105E78 (at most 100 strips; more are counted as refused)
void dds3SetDistBlurPara(int32_t number, int32_t width, int32_t intval, int32_t blend, ee::Float speed, ee::Float rotate,
                         ee::Float distor)
{
    if (number > 100) {
        number = 100;
        ++distblurovercnt();
    }
    eff::DistortionBlurParam& t = effects().distblur.target;
    t.blend = blend;
    t.number = static_cast<uint32_t>(number);
    t.width = width;
    t.interval = static_cast<uint32_t>(intval);
    t.speed = speed;
    t.rotate = rotate;
    t.distortion = distor;
}

// dds3SetDistBlurRGBA @ 0x00105EC0
void dds3SetDistBlurRGBA(uint32_t rgba) { effects().distblur.target.abgr = rgba; }

// dds3SetDistBlurArea @ 0x00105ED0
void dds3SetDistBlurArea(int32_t area, int32_t posx, int32_t posy)
{
    eff::DistortionBlurParam& t = effects().distblur.target;
    t.center.y = posy;
    t.area = area;
    t.center.x = posx;
}

// dds3DistBlurSwap @ 0x00105EE8
void dds3DistBlurSwap(int32_t frame)
{
    EffectSettings<eff::DistortionBlurParam>& s = effects().distblur;
    s.base = *eff::Eve_DistortionBlurEditorGetParams();
    startSwap(effectFades().distblur, frame);
    if (frame == 0) {
        clearFlags(kDistBlurSwap);
        eff::Eve_DistortionBlurSetParam(s.target);
        return;
    }
    setFlags(kDistBlurSwap);
}

// dds3DistBlurOn @ 0x00105FC8
// Unlike the blurs and filters, the target is set at once either way; a fade
// keeps the effect off until dds3BlurUpdate turns it on.
void dds3DistBlurOn(int32_t frame)
{
    EffectSettings<eff::DistortionBlurParam>& s = effects().distblur;
    fadeIn(effectFades().distblur, s.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kDistBlurFade);
        eff::Eve_DistortionBlurSetParam(s.target);
        eff::Eve_DistortionBlurON();
        return;
    }
    setFlags(kDistBlurFade);
    eff::Eve_DistortionBlurSetParam(s.target);
    eff::Eve_DistortionBlurOFF();
}

// dds3DistBlurOff @ 0x00106038
void dds3DistBlurOff(int32_t frame)
{
    fadeOut(effectFades().distblur, effects().distblur.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kDistBlurFade | kDistBlurSwap);
        eff::Eve_DistortionBlurOFF();
        return;
    }
    setFlags(kDistBlurFade);
}

// ---- RipBlur: the ripple blur ------------------------------------------------------------------

// dds3SetRipBlurPara @ 0x001060A0 (at most 40 ripples; more are counted as refused)
void dds3SetRipBlurPara(ee::Float speed, ee::Float intval, ee::Float rotate, ee::Float distor, ee::Float distor_s,
                        int32_t number, int32_t blend)
{
    if (number > 40) {
        number = 40;
        ++ripblurovercnt();
    }
    eff::RippleBlurParam& t = effects().ripblur.target;
    t.blend = blend;
    t.number = static_cast<uint32_t>(number);
    t.speed = speed;
    t.interval = intval;
    t.rotate = rotate;
    t.power = distor;
    t.frequency = distor_s;
}

// dds3SetRipBlurRGBA @ 0x001060E8
void dds3SetRipBlurRGBA(uint32_t rgba) { effects().ripblur.target.abgr = rgba; }

// dds3SetRipBlurArea @ 0x001060F8
void dds3SetRipBlurArea(int32_t area, int32_t posx, int32_t posy)
{
    eff::RippleBlurParam& t = effects().ripblur.target;
    t.center.y = posy;
    t.area = area;
    t.center.x = posx;
}

// dds3RipBlurSwap @ 0x00106110
void dds3RipBlurSwap(int32_t frame)
{
    EffectSettings<eff::RippleBlurParam>& s = effects().ripblur;
    s.base = *eff::Eve_RippleBlurEditorGetParams();
    startSwap(effectFades().ripblur, frame);
    if (frame == 0) {
        clearFlags(kRipBlurSwap);
        eff::Eve_RippleBlurSetParam(s.target);
        return;
    }
    setFlags(kRipBlurSwap);
}

// dds3RipBlurOn @ 0x001061F0 (as dds3DistBlurOn)
void dds3RipBlurOn(int32_t frame)
{
    EffectSettings<eff::RippleBlurParam>& s = effects().ripblur;
    fadeIn(effectFades().ripblur, s.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kRipBlurFade);
        eff::Eve_RippleBlurSetParam(s.target);
        eff::Eve_RippleBlurON();
        return;
    }
    setFlags(kRipBlurFade);
    eff::Eve_RippleBlurSetParam(s.target);
    eff::Eve_RippleBlurOFF();
}

// dds3RipBlurOff @ 0x00106270
void dds3RipBlurOff(int32_t frame)
{
    fadeOut(effectFades().ripblur, effects().ripblur.target.abgr, frame);
    if (frame == 0) {
        clearFlags(kRipBlurFade | kRipBlurSwap);
        eff::Eve_RippleBlurOFF();
        return;
    }
    setFlags(kRipBlurFade);
}

} // namespace nocturne::dds3
