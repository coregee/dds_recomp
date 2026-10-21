#ifndef NOCTURNE_PARTICLE_RELEASE_H
#define NOCTURNE_PARTICLE_RELEASE_H
#include <stdint.h>
void ps2BillTextureRelease(uint64_t resource);
void ps2BillAnimationRelease(uint64_t resource);
void ps2BillNormalDelete(uint64_t object);
void ps2BillAnimationDelete(uint64_t object);
void dds3BillboardDelete(uint64_t object);
void ps2ParticlePhysicsRelease(uint64_t resource);
void ps2ParticleBackingRelease(uint64_t resource);
void Eff_ModelTrackPolyListDelete(uint64_t list);
void dds3Particle_BasicDelete(uint64_t object);
void dds3ParticleDelete(uint64_t object);
void dds3ParticleExpDelete(uint64_t object);
void nocturneCallParticleRelease(uint32_t entry,uint64_t object);
void ps2ParticleKind0Delete(uint64_t object);
void ps2ParticleKind1Delete(uint64_t object);
void ps2ParticleKind2Delete(uint64_t object);
void ps2ParticleKind3Delete(uint64_t object);
void ps2ParticleKind4Delete(uint64_t object);
void ps2ParticleKind5Delete(uint64_t object);
void ps2ParticleKind6Delete(uint64_t object);
void ps2ParticleKind7Delete(uint64_t object);
void ps2ParticleKind8Delete(uint64_t object);
void ps2ParticleKind9Delete(uint64_t object);
void ps2ParticleKind10Delete(uint64_t object);
void ps2ParticleKind11Delete(uint64_t object);
void ps2ParticleKind12Delete(uint64_t object);
#endif
