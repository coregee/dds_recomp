// An object's pose. Rewritten from the original instructions.
#include "nocturne/kernel/pose.hpp"

#include <cstddef>

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/kernel/math.hpp"

namespace nocturne::dds3 {

static_assert(sizeof(PoseSet) == 0xd0 && offsetof(PoseSet, flags) == 0xc0 && offsetof(PoseSet, savedPosition) == 0x80);

namespace {

constexpr uint32_t kObjectIds = addr(0x0054e9c0);   // uint32 (gp-relative): the last object ID

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }
PoseSet& poseOf(uint32_t object) { return *guest::table<PoseSet>(word(object + 0x1c)); }

// VU0's vf0: (0, 0, 0, 1).
constexpr Vector4 kUnit{ee::Float::fromBits(0), ee::Float::fromBits(0), ee::Float::fromBits(0), ee::Float::fromBits(0x3f800000)};

// Changed: its matrix is to be made again.
PoseSet& changed(uint32_t object)
{
    PoseSet& pose = poseOf(object);
    pose.flags = (pose.flags | kPoseChanged) & ~kPoseMatrixMade;
    return pose;
}

} // namespace

// dds3InitPoseSet @ 0x0010DD38
int32_t makePose(uint32_t object)
{
    if (object == 0 || word(object + 0x1c) != 0)
        return 0;
    const uint32_t block = mem::PoolAllocate(sizeof(PoseSet));
    if (block == 0)
        return 0;
    PoseSet& pose = *guest::table<PoseSet>(block);
    pose.flags = kPoseChanged;
    resetPose(pose);
    pose.unknown_b0 = kUnit;
    word(object + 0x1c) = block;
    pose.radius = ee::Float::fromBits(0);
    pose.unknown_c8 = 0;
    return 1;
}

// dds3FreePoseSet @ 0x0010DDB0
void freePose(uint32_t object)
{
    if (object == 0 || word(object + 0x1c) == 0)
        return;
    mem::PoolRelease(word(object + 0x1c));
    word(object + 0x1c) = 0;
}

// dds3OnPoseSetFlag @ 0x0010DDF0
void setPoseFlags(PoseSet& pose, uint32_t flags) { pose.flags |= flags; }

// dds3OffPoseSetFlag @ 0x0010DE00
void clearPoseFlags(PoseSet& pose, uint32_t flags) { pose.flags &= ~flags; }

// dds3CheckPoseSetFlag @ 0x0010DE18
bool anyPoseFlag(const PoseSet& pose, uint32_t flags) { return (pose.flags & flags) != 0; }

// dds3InitPoseSetValue @ 0x0010DE28: the scale from vf0 too, (1, 1, 1, 0)
// (its x, y, z plus w, its w times x).
void resetPose(PoseSet& pose)
{
    pose.position = kUnit;
    pose.rotation = kUnit;
    pose.scale = {kUnit.x + kUnit.w, kUnit.y + kUnit.w, kUnit.z + kUnit.w, kUnit.w * kUnit.x};
}

// dds3BackupPoseSet @ 0x0010DE50
void savePose(PoseSet& pose)
{
    pose.savedScale = pose.scale;
    pose.savedRotation = pose.rotation;
    pose.savedPosition = pose.position;
}

// dds3SetRadiusPoseSet @ 0x0010DE88
void setPoseRadius(uint32_t object, ee::Float radius) { poseOf(object).radius = radius; }

// dds3SetPosPoseSet @ 0x0010DEA8
void setPosition(uint32_t object, const Vector4& position) { changed(object).position = position; }

// dds3SetRotPoseSet @ 0x0010DED8
void setRotation(uint32_t object, const Vector4& rotation) { changed(object).rotation = rotation; }

// dds3SetSclPoseSet @ 0x0010DF08
void setScale(uint32_t object, const Vector4& scale) { changed(object).scale = scale; }

// dds3AddPosPoseSet @ 0x0010DF88
void movePosition(uint32_t object, const Vector4& by)
{
    PoseSet& pose = changed(object);
    pose.position = {pose.position.x + by.x, pose.position.y + by.y, pose.position.z + by.z, pose.position.w + by.w};
}

// dds3AddRotPoseSet @ 0x0010DFC0
void addRotation(uint32_t object, const Vector4& rotation)
{
    PoseSet& pose = changed(object);
    pose.rotation = sdf::quaternionMultiply(pose.rotation, rotation);
}

// dds3AddSclPoseSet @ 0x0010E010
void multiplyScale(uint32_t object, const Vector4& by)
{
    PoseSet& pose = changed(object);
    pose.scale = {pose.scale.x * by.x, pose.scale.y * by.y, pose.scale.z * by.z, pose.scale.w * by.w};
}

// dds3SerializeID @ 0x0010E248
uint32_t nextObjectId()
{
    word(kObjectIds) = (word(kObjectIds) + 1) & 0xffff;
    return word(kObjectIds);
}

} // namespace nocturne::dds3
