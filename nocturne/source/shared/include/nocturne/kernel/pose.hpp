// An object's pose (original unit: the engine's dds3PoseSet): where it
// stands, how it is turned and scaled, as far as rewritten. An object (its
// dds3ObjectBase, `object`) holds its pose at +0x1C. Field names are
// tentative, from their use.
#pragma once

#include <cstdint>

#include "nocturne/ee/float.hpp"
#include "nocturne/kernel/draw.hpp"

namespace nocturne::dds3 {

struct PoseSet {
    uint8_t unknown_00[0x40];
    Vector4 position;   // +0x40
    Vector4 rotation;   // +0x50, a quaternion
    Vector4 scale;      // +0x60
    uint8_t unknown_70[0x10];
    Vector4 savedPosition, savedRotation, savedScale;   // +0x80 (dds3BackupPoseSet)
    Vector4 unknown_b0;   // (0, 0, 0, 1) when made
    uint32_t flags;       // PoseFlag
    ee::Float radius;     // +0xC4
    uint32_t unknown_c8;
    uint32_t unknown_cc;
};

// PoseSet::flags
enum PoseFlag : uint32_t {
    kPoseChanged = 1,      // moved, turned or scaled since its matrix was made (tentative)
    kPoseMatrixMade = 2,   // its matrix is current (tentative)
};

// dds3InitPoseSet (0x10DD38): gives an object without one a pose at rest.
// 1 if it did.
int32_t makePose(uint32_t object);
// dds3FreePoseSet (0x10DDB0)
void freePose(uint32_t object);
// dds3OnPoseSetFlag / OffPoseSetFlag / CheckPoseSetFlag (0x10DDF0..)
void setPoseFlags(PoseSet& pose, uint32_t flags);
void clearPoseFlags(PoseSet& pose, uint32_t flags);
bool anyPoseFlag(const PoseSet& pose, uint32_t flags);
// dds3InitPoseSetValue (0x10DE28): at rest: at the origin, unturned, at scale 1.
void resetPose(PoseSet& pose);
// dds3BackupPoseSet (0x10DE50): keeps the position, rotation and scale.
void savePose(PoseSet& pose);
// dds3SetRadiusPoseSet (0x10DE88): sets the radius.
void setPoseRadius(uint32_t object, ee::Float radius);
// dds3SetPosPoseSet / SetRotPoseSet / SetSclPoseSet (0x10DEA8 ..)
void setPosition(uint32_t object, const Vector4& position);
void setRotation(uint32_t object, const Vector4& rotation);
void setScale(uint32_t object, const Vector4& scale);
// dds3AddPosPoseSet (0x10DF88): moves by `by`.
void movePosition(uint32_t object, const Vector4& by);
// dds3AddRotPoseSet (0x10DFC0): turns further by the quaternion.
void addRotation(uint32_t object, const Vector4& rotation);
// dds3AddSclPoseSet (0x10E010): scales by `by` (lane by lane).
void multiplyScale(uint32_t object, const Vector4& by);
// dds3SerializeID (0x10E248): the next object ID (16 bits, wrapping).
uint32_t nextObjectId();

} // namespace nocturne::dds3
