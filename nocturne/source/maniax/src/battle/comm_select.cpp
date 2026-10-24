// The command menu (original unit: nbCommSel): US Maniax's own (shared/src/battle/comm_select.cpp has the rest).
#include "nocturne/battle/comm_select.hpp"

namespace nocturne::nb {

// SetCommList @ 0x0025CB80: only the Demi-fiend gets the items and the
// demons to summon.
bool listsItems(CommandMenu&, Party&, bool player) { return player; }
bool listsSummons(bool player) { return player; }

} // namespace nocturne::nb
