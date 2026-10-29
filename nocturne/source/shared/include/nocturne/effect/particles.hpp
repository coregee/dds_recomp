// The battle's particle effects (original names effPCP*: the skills'
// sparks, rings, lightning, ice ...), as far as rewritten: their setters.
// An effect is its work in guest memory (`effect`); each keeps its
// position, colour (0xAABBGGRR) and scale at its own offsets. Creating,
// running and drawing them is the effect library's part. Effect names
// follow smt3-decomp's, in English where they name a skill (Ziodin:
// Ziodyne, Megidora: Megidola, Agirao: Agilao, Houden: discharge).
#pragma once

#include <cstdint>

#include "nocturne/ee/float.hpp"
#include "nocturne/kernel/draw.hpp"

namespace nocturne::eff {

// A rotation matrix (four VU0 rows).
struct Matrix {
    dds3::Vector4 row[4];
};

// Moves an effect that keeps its position at the start of its work (most).
void setPosition(uint32_t effect, const dds3::Vector4& position);
// The thunder effects (ThunderPoly, ThunderPolyLow) move by the change.
void setThunderPolyPosition(uint32_t effect, const dds3::Vector4& position);
void setThunderPolyLowColor(uint32_t effect, uint32_t color);
void setFlashPolySphere2Color(uint32_t effect, uint32_t color);
void setFlashPolySphere2Scale(uint32_t effect, ee::Float scale);
void setFlashPolySphereColor(uint32_t effect, uint32_t color);
void setFlashPolyRingColor(uint32_t effect, uint32_t color);
void setFlashPolyPipeColor(uint32_t effect, uint32_t color);
void setFlashPolyRingExpColor(uint32_t effect, uint32_t color);
void setHamaCardSpiralColor(uint32_t effect, uint32_t color);
void setHamaCardSpiralScale(uint32_t effect, ee::Float scale);
void setHamaCardSphereColor(uint32_t effect, uint32_t color);
void setHamaCardSphereScale(uint32_t effect, ee::Float scale);
void setSparkleSphereColor(uint32_t effect, uint32_t color);
void setMahama01Color(uint32_t effect, uint32_t color);
void setHwave01Color(uint32_t effect, uint32_t color);
void setZiodyne01Color(uint32_t effect, uint32_t color);
void setZiodyne02Color(uint32_t effect, uint32_t color);
void setZiodyne03Color(uint32_t effect, uint32_t color);
void setZiodyne04Color(uint32_t effect, uint32_t color);
void setMaziodyne01Color(uint32_t effect, uint32_t color);
void setMaziodyne02Color(uint32_t effect, uint32_t color);
void setShockWave01Color(uint32_t effect, uint32_t color);
void setShockWave02Color(uint32_t effect, uint32_t color);
void setDischarge01Color(uint32_t effect, uint32_t color);
void setBlinkMultiBlurPosition(uint32_t effect, const dds3::Vector4& position);
void setBlinkMultiBlurColor(uint32_t effect, uint32_t color);
void setMultiBlurExpColor(uint32_t effect, uint32_t color);
void setMultiFilterExpColor(uint32_t effect, uint32_t color);
void setMultiBlurExp2Color(uint32_t effect, uint32_t color);
void setFilterExpColor(uint32_t effect, uint32_t color);
void setBlurExpColor(uint32_t effect, uint32_t color);
void setDistortionBlurExpColor(uint32_t effect, uint32_t color);
void setMegidola01Color(uint32_t effect, uint32_t color);
void setMegidolaon01Color(uint32_t effect, uint32_t color);
void setBreathPosition(uint32_t effect, const dds3::Vector4& position);
void setBreathColor(uint32_t effect, uint32_t color);
void setAgilaoFireColor(uint32_t effect, uint32_t color);
void setBufuIceColor(uint32_t effect, uint32_t color);
void setBufulaIceColor(uint32_t effect, uint32_t color);
void setBufudyneIceColor(uint32_t effect, uint32_t color);
void setThunderSpherePolyColor(uint32_t effect, uint32_t color);
void setThunderPolyColor(uint32_t effect, uint32_t color);
void setThunderRadiatePolyColor(uint32_t effect, uint32_t color);
void setHama01Color(uint32_t effect, uint32_t color);
void setHama02Color(uint32_t effect, uint32_t color);
void setHamaonColor(uint32_t effect, uint32_t color);
void setMudoColor(uint32_t effect, uint32_t color);
void setMudoPosition(uint32_t effect, const dds3::Vector4& position);
void setMudoScale(uint32_t effect, ee::Float scale);
void setHama01Scale(uint32_t effect, ee::Float scale);
void setHama02Scale(uint32_t effect, ee::Float scale);   // (and Hamaon's)
// An effect's area (how far it spreads).
void setSparkleSphereArea(uint32_t effect, ee::Float area);
void setBlinkMultiBlurArea(uint32_t effect, ee::Float area);
void setMultiBlurExpArea(uint32_t effect, ee::Float area);
void setMultiFilterExpArea(uint32_t effect, ee::Float area);
// The ice effects (Bufu, Bufula, Bufudyne): their scale and rotation.
void setIceScale(uint32_t effect, ee::Float scale);
void setIceRotation(uint32_t effect, const Matrix& rotation);

// Deleting them (particle_release.cpp): what each holds, then its work.
void deleteThunderSpherePoly(uint32_t effect);
void deleteThunderPoly(uint32_t effect);
void deleteThunderPolyLow(uint32_t effect);
void deleteThunderRadiatePoly(uint32_t effect);
void deleteFlashPolyList(uint32_t effect);
void deleteFlashPolySphere2(uint32_t effect);
void deleteFlashPolySphere(uint32_t effect);
void deleteFlashPolyRing(uint32_t effect);
void deleteFlashPolyPipe(uint32_t effect);
void deleteFlashPolyRingExp(uint32_t effect);
void deleteFlashPolySphereExp(uint32_t effect);
void releaseTextureResource(uint32_t effect);
void deleteScatterPolyList(uint32_t effect);
void deleteWhirlwindPolyList(uint32_t effect);
void deleteWhirlwindPoly(uint32_t effect);
void deleteWhirlwindSpherePoly(uint32_t effect);
void deleteNeedleVertexList(uint32_t effect);
void deleteNeedleModel(uint32_t effect);
void deleteNeedleSpiral(uint32_t effect);
void deleteSparkleSphere(uint32_t effect);
void deleteZiodyne(uint32_t effect);
void deleteZiodyne03(uint32_t effect);
void deleteMaziodyne02(uint32_t effect);
void deleteSphereEffect(uint32_t effect);
void deleteThunderSphereExp(uint32_t effect);
void deleteEyeThunder(uint32_t effect);
void deleteWork(uint32_t effect);
void deleteBlinkMultiBlur(uint32_t effect);
void deleteMultiBlurExp(uint32_t effect);
void deleteMultiFilterExp(uint32_t effect);
void deleteScreenBlur(uint32_t effect);
void deleteScreenBlurExp(uint32_t effect);
void deleteBufuLight(uint32_t effect);
void deleteRingPolyExpList(uint32_t effect);
void deleteRingPolyExp(uint32_t effect);

// The effect library's deletion by kind, billboards, particles and the
// effects holding parts (effect_release.cpp).
void deleteEffect(uint32_t handle);
void deletePart(uint32_t handle);
void deleteParticleEffect(uint32_t handle);
void releaseBillboardTexture(uint32_t handle);
void releaseBillboardAnimation(uint32_t handle);
void deleteNormalBillboard(uint32_t handle);
void deleteAnimatedBillboard(uint32_t handle);
void deleteBillboard(uint32_t handle);
void deleteParticlePhysics(uint32_t handle);
void deleteParticleBlur(uint32_t handle);
void deleteModelTrackPolyList(uint32_t handle);
void deleteParticleBasics(uint32_t handle);
void deleteSmokeOffsetParticle(uint32_t handle);
void deleteSphereSpiral2Particle(uint32_t handle);
void deleteParticle(uint32_t handle);
void deleteHamaCardSpiral(uint32_t handle);
void deleteHamaCardSphere(uint32_t handle);
void deleteHama01(uint32_t handle);
void deleteHama02(uint32_t handle);
void deleteHamaon(uint32_t handle);
void deleteMahama01(uint32_t handle);
void deleteMudo(uint32_t handle);
void deleteHwave01(uint32_t handle);
void deleteBreath(uint32_t handle);
void deleteAgilaoFire(uint32_t handle);
void deleteAgilaoFireball(uint32_t handle);
void deleteBufuIce(uint32_t handle);
void deleteBufulaIce(uint32_t handle);
void deleteRadiateThunder(uint32_t handle);

// Colours and placement by kind, a model's colour (effect_color.cpp).
void setEffectRgba(uint32_t effect, uint32_t rgba);
void setBillboardRgba(uint32_t billboard, uint32_t rgba);
void setP2APolygonRgba(uint32_t polygon, uint32_t rgba);
void setParticleRgba(uint32_t particle, uint32_t rgba);
void setSpPolyRgba(uint32_t polygon, uint32_t rgba);
void setPartColor(uint32_t part, uint32_t rgba);
void setPartModelColor(uint32_t model, uint32_t rgba);
void setParticleEffectPosition(uint32_t handle, uint32_t position);
void setParticleEffectDirection(uint32_t handle, uint32_t direction);
void setParticleEffectColor(uint32_t handle, uint32_t rgba);
void setMagatamaCylinderRgba(uint32_t effect, uint32_t rgba);
void setMagatamaSpiralRgba(uint32_t effect, uint32_t rgba);
void setMagatamaSmokeRgba(uint32_t effect, uint32_t rgba);
void setMagatamaRgba(uint32_t handle, uint32_t rgba);
void setModelEffectColor(uint32_t model, uint32_t node, uint32_t rgba);
void setModelEffectsColor(uint32_t model, uint32_t rgba);
void setModelColor(uint32_t model, uint32_t rgba);

// Rotation by kind (effect_matrix.cpp): `rotation` a matrix's address.
void setEffectRotation(uint32_t effect, uint32_t rotation);
void setP2APolygonRotation(uint32_t polygon, uint32_t rotation);
void setParticleRotation(uint32_t particle, uint32_t rotation);
void setSpPolyRotation(uint32_t polygon, uint32_t rotation);
void setPartRotation(uint32_t part, uint32_t rotation);
void setPartModelRotation(uint32_t model, uint32_t rotation);
void setParticleEffectRotation(uint32_t handle, uint32_t rotation);
void setMagatamaEffectRotation(uint32_t effect, uint32_t rotation);
void setMagatamaRotation(uint32_t handle, uint32_t rotation);

} // namespace nocturne::eff
