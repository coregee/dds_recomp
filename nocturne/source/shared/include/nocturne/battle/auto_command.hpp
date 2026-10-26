// The party's automatic commands (original unit: nbAutoCommProcess), as far
// as rewritten: its process's start.
#pragma once

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbInitAutoCommProcess (0x289AC8): its process ("nb_autocomm") under the
// battle's, with the battle's record as its data.
void startAutoCommandProcess(MainProcessData& main);

} // namespace nocturne::nb
