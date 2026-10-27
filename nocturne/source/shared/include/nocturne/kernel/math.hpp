// The engine's trigonometry (original unit: sdf's math), as the game computes
// it: short polynomials on the EE's floats, its constants from the
// executable's table (0x54E758..0x54E780).
#pragma once

#include "nocturne/ee/float.hpp"
#include "nocturne/kernel/draw.hpp"

namespace nocturne::sdf {

ee::Float sine(ee::Float radians);     // sdfSin (0x2C0060): reduced to a quarter turn, then 5 terms
ee::Float cosine(ee::Float radians);   // sdfCos (0x2C0160): the sine a quarter turn on
ee::Float arctangent(ee::Float x);     // sdfAtan (0x2C0228): 3 terms (for small x)
// Mult (0x2C0488, the VU0's vf10 x vf11): the quaternion product a b.
dds3::Vector4 quaternionMultiply(const dds3::Vector4& a, const dds3::Vector4& b);

} // namespace nocturne::sdf
