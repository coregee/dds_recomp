// Sacrifice fusion (original unit: cmbCombine): Hardtype's own (shared/src/fusion/combine.cpp has the rest).
#include "nocturne/fusion/combine.hpp"

namespace nocturne::cmb {

// cmbCalcIkenieExp @ 0x001FE880: the sacrifice's EXP x1 (its constant at 0x1FE8C8).
ee::Float sacrificeExpScale() { return ee::Float(1.0f); }

} // namespace nocturne::cmb
