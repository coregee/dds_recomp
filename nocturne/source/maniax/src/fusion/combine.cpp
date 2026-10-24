// Sacrifice fusion (original unit: cmbCombine): US Maniax's own (shared/src/fusion/combine.cpp has the rest).
#include "nocturne/fusion/combine.hpp"

namespace nocturne::cmb {

// cmbCalcIkenieExp @ 0x001FE880: the sacrifice's EXP x1.5.
ee::Float sacrificeExpScale() { return ee::Float(1.5f); }

} // namespace nocturne::cmb
