#ifndef NOCTURNE_EFFECT_RELEASE_H
#define NOCTURNE_EFFECT_RELEASE_H
#include <stdint.h>
void Eff_ModelTrackPolyDelete(uint64_t effect);
void ps2HermitianTrackPolyRelease(uint64_t record);
void ps2SpecialTrackBundleRelease(uint64_t bundle);
void dds3TrackPolyDelete(uint64_t record);
void ps2SpPolyKind0Delete(uint64_t object);
void ps2SpPolyKind1Delete(uint64_t object);
void ps2SpPolyKind2Delete(uint64_t object);
void ps2SpPolyKind3Delete(uint64_t object);
void dds3SpPolyDelete(uint64_t object);
void nocturneCallSpPolyDestructor(uint32_t entry,uint64_t object);
#endif
