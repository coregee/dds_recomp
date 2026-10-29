// The battle's particle effects and the effect library's lists under them:
// their deletion (effPCP*Delete, dds3*Delete). Each frees what it holds,
// then its own work. Rewritten from the original instructions.
#include "nocturne/effect/particles.hpp"

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

namespace {

constexpr uint32_t kBlinkMultiBlur = addr(0x00551dd0);   // the blink effect playing (gp-relative)
constexpr uint32_t kBlinkUsers = addr(0x0054f1e8);       // int32 (gp-relative): the effects sharing it

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }

// A thunder spell's bolts (ThunderPoly effects), from +0x1C.
void deleteBolts(uint32_t effect, int32_t bolts)
{
    for (int32_t k = 0; k < bolts; ++k)
        deleteThunderPoly(word(effect + 0x1c + 4u * static_cast<uint32_t>(k)));
    mem::PoolRelease(effect);
}

} // namespace

// effPCPThunderSpherePolyDelete @ 0x001764F0
void deleteThunderSpherePoly(uint32_t effect)
{
    TrackPolyDelete(word(effect + 0x5c));
    mem::HandleFree(word(effect + 0x60));
}

// effPCP_ThunderPolyDelete @ 0x001785E8
void deleteThunderPoly(uint32_t effect)
{
    TrackPolyDelete(word(effect + 0x60));
    mem::HandleFree(word(effect + 0x64));
}

// effPCP_ThunderPolyLowDelete @ 0x001790E0
void deleteThunderPolyLow(uint32_t effect)
{
    TrackPolyDelete(word(effect + 0x5c));
    TrackPolyDelete(word(effect + 0x60));
    mem::HandleFree(word(effect + 0x64));
}

// effPCP_ThunderRadiatePolyDelete @ 0x00179B08
void deleteThunderRadiatePoly(uint32_t effect)
{
    TrackPolyDelete(word(effect + 0x50));
    mem::HandleFree(word(effect + 0x54));
}

// dds3FlashPolyListDelete @ 0x00182C40
// dds3FlashPolyList2Delete @ 0x00183060
// dds3FlashPolyList3Delete @ 0x00183368
// The flash effects' polygon lists: their material, then their memory.
void deleteFlashPolyList(uint32_t list)
{
    tex::MaterialDeferredRelease(word(list + 0x68));
    mem::HandleFree(word(list + 0x6c));
}

// effPCPFlashPolySphere2Delete @ 0x0017D1F8
void deleteFlashPolySphere2(uint32_t effect)
{
    deleteFlashPolyList(word(effect + 0x44));
    mem::HandleFree(word(effect + 0x40));
}

// effPCPFlashPolySphereDelete @ 0x0017D8A8
void deleteFlashPolySphere(uint32_t effect)
{
    deleteFlashPolyList(word(effect + 0x54));
    mem::HandleFree(word(effect + 0x50));
}

// effPCPFlashPolyRingDelete @ 0x0017E260
void deleteFlashPolyRing(uint32_t effect)
{
    deleteFlashPolyList(word(effect + 0x5c));
    mem::HandleFree(word(effect + 0x58));
}

// effPCPFlashPolyPipeDelete @ 0x0017EA88
void deleteFlashPolyPipe(uint32_t effect)
{
    deleteFlashPolyList(word(effect + 0x64));
    mem::HandleFree(word(effect + 0x60));
}

// effPCPFlashPolyRingExpDelete @ 0x0017F388
void deleteFlashPolyRingExp(uint32_t effect)
{
    deleteFlashPolyList(word(effect + 0x7c));
    mem::HandleFree(word(effect + 0x78));
}

// effPCPFlashPolySphereExpDelete @ 0x0017FC00
void deleteFlashPolySphereExp(uint32_t effect)
{
    deleteFlashPolyList(word(effect + 0x60));
    mem::HandleFree(word(effect + 0x5c));
}

// dds3ScatterPolyListTexResourceDelete @ 0x00186080: one user fewer; the
// last lets the texture and the resource go.
void releaseTextureResource(uint32_t resource)
{
    if (--word(resource + 4) != 0)
        return;
    tex::DeferredRelease(word(resource));
    mem::PoolRelease(resource);
}

// dds3ScatterPolyListDelete @ 0x00185D88
void deleteScatterPolyList(uint32_t list)
{
    if (word(list + 0x30))
        releaseTextureResource(word(list + 0x30));
    tex::MaterialDeferredRelease(word(list + 0x28));
    mem::HandleFree(word(list + 0x2c));
}

// dds3WhirlwindPolyListDelete @ 0x00188DA0
void deleteWhirlwindPolyList(uint32_t list)
{
    if (word(list + 0x7c))
        releaseTextureResource(word(list + 0x7c));
    tex::MaterialDeferredRelease(word(list + 0x74));
    mem::HandleFree(word(list + 0x78));
    mem::PoolRelease(list);
}

// effPCPWhirlwindPolyDelete @ 0x00186390
void deleteWhirlwindPoly(uint32_t effect)
{
    deleteWhirlwindPolyList(word(effect + 0x184));
    mem::HandleFree(word(effect + 0x188));
}

// effPCPWwSpherePolyDelete @ 0x001884C8
void deleteWhirlwindSpherePoly(uint32_t effect)
{
    deleteWhirlwindPolyList(word(effect + 0x134));
    mem::HandleFree(word(effect + 0x138));
}

// dds3NeedleModelVNCListDelete @ 0x0018A070 (with a complaint naming it)
void deleteNeedleVertexList(uint32_t model)
{
    if (word(model + 0x68) == 0)
        return;
    diag::print(diag::Message::NeedleListDelete, static_cast<int32_t>(word(model + 0x68)));
    mem::HandleFree(word(model + 0x68));
}

// dds3NeedleModelDelete @ 0x00189B68
void deleteNeedleModel(uint32_t model)
{
    tex::MaterialDeferredRelease(word(model + 0x6c));
    deleteNeedleVertexList(model);
    mem::HandleFree(word(model + 0x70));
}

// effPCPNeedleSpiralDelete @ 0x001893D0
void deleteNeedleSpiral(uint32_t effect)
{
    TrackPolyDelete(word(effect + 0x68));
    deleteNeedleModel(word(effect + 0x6c));
    mem::HandleFree(word(effect + 0x70));
}

// effPCPSparkleSphereDelete @ 0x0018A1D8
void deleteSparkleSphere(uint32_t effect)
{
    deleteBillboard(word(effect + 0x1c));
    mem::PoolRelease(effect);
}

// effPCPZiodin01Delete @ 0x0018C000
// effPCPZiodin02Delete @ 0x0018C478
// effPCPZiodin04Delete @ 0x0018CD88
// effPCPMZiodin01Delete @ 0x0018D0F8
void deleteZiodyne(uint32_t effect) { deleteBolts(effect, 12); }

// effPCPZiodin03Delete @ 0x0018C910
// effPCPShockWave02Delete @ 0x0018DB50
void deleteZiodyne03(uint32_t effect) { deleteBolts(effect, 30); }

// effPCPMZiodin02Delete @ 0x0018D468
void deleteMaziodyne02(uint32_t effect) { deleteBolts(effect, 8); }

// effPCPShockWave01Delete @ 0x0018D678
// effPCPHouden01Delete @ 0x0018DD60
// effPCPMegidora01Delete @ 0x0018F5C0
// effPCPMegidoraon01Delete @ 0x0018F870
// Effects around one thunder sphere (at +0x1C).
void deleteSphereEffect(uint32_t effect)
{
    deleteThunderSpherePoly(word(effect + 0x1c));
    mem::PoolRelease(effect);
}

// effPCPThunderSphereExpDelete @ 0x001932E0
void deleteThunderSphereExp(uint32_t effect)
{
    deleteThunderSpherePoly(word(effect + 0x30));
    mem::PoolRelease(effect);
}

// effPCPEyeThunderDelete @ 0x00192F90
void deleteEyeThunder(uint32_t effect)
{
    deleteThunderPoly(word(effect + 0x20));
    mem::PoolRelease(effect);
}

// effPCPFilterExpDelete @ 0x0018EAF8
// effPCPBlurExpDelete @ 0x0018ED10
// dds3EffectPartialMultiBlurDelete @ 0x001A2098
// dds3EffectPartialMultiFilterDelete @ 0x001A2EB8
// Effects that hold nothing: their work.
void deleteWork(uint32_t effect) { mem::PoolRelease(effect); }

// effPCPBlinkMultiBlurDelete @ 0x0018E000: the last of the effects sharing
// the blink effect lets it go, and its blur.
void deleteBlinkMultiBlur(uint32_t effect)
{
    mem::PoolRelease(effect);
    if (--word(kBlinkUsers) != 0)
        return;
    deleteWork(word(word(kBlinkMultiBlur) + 0x38));
    mem::PoolRelease(word(kBlinkMultiBlur));
}

// effPCPMultiBlurExpDelete @ 0x0018E260
void deleteMultiBlurExp(uint32_t effect)
{
    deleteWork(word(effect + 0x34));
    mem::PoolRelease(effect);
}

// effPCPMultiFilterExpDelete @ 0x0018E4E0
// effPCPMultiBlurExp2Delete @ 0x0018E838
void deleteMultiFilterExp(uint32_t effect)
{
    deleteWork(word(effect + 0x38));
    mem::PoolRelease(effect);
}

// dds3EffectDistortionBlurDelete @ 0x001A23E0
// dds3EffectRippleBlurDelete @ 0x001A28C8
void deleteScreenBlur(uint32_t blur) { mem::HandleFree(word(blur + 0x30)); }

// effPCPDistortionBlurExpDelete @ 0x0018EFA8
// effPCPRippleBlurExpDelete @ 0x0018F318
void deleteScreenBlurExp(uint32_t effect)
{
    deleteScreenBlur(word(effect + 0x34));
    mem::PoolRelease(effect);
}

// effPCPBufuLightDelete @ 0x00192A90: nothing to let go.
void deleteBufuLight(uint32_t) {}

// dds3RingPolyExpListDelete @ 0x001935C8
void deleteRingPolyExpList(uint32_t list)
{
    tex::MaterialDeferredRelease(word(list + 0xa8));
    mem::HandleFree(word(list + 0xac));
    mem::PoolRelease(list);
}

// effPCPRingPolyExpDelete @ 0x00193B58
void deleteRingPolyExp(uint32_t effect)
{
    deleteRingPolyExpList(word(effect + 0x5c));
    mem::PoolRelease(effect);
}

} // namespace nocturne::eff
