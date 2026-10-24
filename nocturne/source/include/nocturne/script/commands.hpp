// The FlowScript commands every script can use (original unit:
// scrCommonCommand): event flags, waiting, fades, the pad, other script
// processes, the screen quake and the event screen effects. Commands read
// their arguments with scrGetIntPara and friends (vm.hpp) and return 1 when
// done, 0 to run again next frame.
#pragma once

#include <cstdint>

namespace nocturne::scr {

// A command table entry's function (0x52E350 holds the original addresses):
// those rewritten run here, the rest through the engine.
int32_t CallCommand(uint32_t entry);

int32_t scrCommand_BIT_CHK();
int32_t scrCommand_BIT_ON();
int32_t scrCommand_BIT_OFF();
int32_t scrCommand_RND();
int32_t scrCommand_SYNC();
int32_t scrCommand_WAIT();
int32_t scrCommand_PUT();
int32_t scrCommand_PUTS();
int32_t scrCommand_FADE_IN();
int32_t scrCommand_FADE_OUT();
int32_t scrCommand_SEL_JMP();
int32_t scrCommand_PAD_TRIG();
int32_t scrCommand_PAD_PRESS();
int32_t scrCommand_PAD_ACT();
int32_t scrCommand_SET_FOVY();
int32_t scrCommand_SCR_RUN();
int32_t scrCommand_SCR_KILL();
int32_t scrCommand_SCR_WAIT();
int32_t scrCommand_SCR_STAT();
int32_t scrCommand_SCR_TIME();
int32_t scrCommand_QUAKE_ON();
int32_t scrCommand_QUAKE_OFF();
int32_t scrCommand_SCENE_LIGHT_RGB();
int32_t scrCommand_SCENE_LIGHT_DIR();
int32_t scrCommand_SCENE_AMBIENT();
int32_t scrCommand_SCENE_FOG_RGB();
int32_t scrCommand_SCENE_FOG_PARA();
int32_t scrCommand_SOFTEN_BIAS();
int32_t scrCommand_BLUR();
int32_t scrCommand_MUL_BLUR_PARA();
int32_t scrCommand_MUL_BLUR_RGBA();
int32_t scrCommand_MUL_BLUR_AREA();
int32_t scrCommand_MUL_BLUR_SWAP();
int32_t scrCommand_MUL_BLUR_ON();
int32_t scrCommand_MUL_BLUR_OFF();
int32_t scrCommand_DIST_BLUR_PARA();
int32_t scrCommand_DIST_BLUR_RGBA();
int32_t scrCommand_DIST_BLUR_AREA();
int32_t scrCommand_DIST_BLUR_SWAP();
int32_t scrCommand_DIST_BLUR_ON();
int32_t scrCommand_DIST_BLUR_OFF();
int32_t scrCommand_RIP_BLUR_PARA();
int32_t scrCommand_RIP_BLUR_RGBA();
int32_t scrCommand_RIP_BLUR_AREA();
int32_t scrCommand_RIP_BLUR_SWAP();
int32_t scrCommand_RIP_BLUR_ON();
int32_t scrCommand_RIP_BLUR_OFF();
int32_t scrCommand_BLUR2_PARA();
int32_t scrCommand_BLUR2_RGBA();
int32_t scrCommand_BLUR2_AREA();
int32_t scrCommand_BLUR2_SWAP();
int32_t scrCommand_BLUR2_ON();
int32_t scrCommand_BLUR2_OFF();
int32_t scrCommand_FILTER2_PARA();
int32_t scrCommand_FILTER2_RGBA();
int32_t scrCommand_FILTER2_SWAP();
int32_t scrCommand_FILTER2_ON();
int32_t scrCommand_FILTER2_OFF();
int32_t scrCommand_MFILTER_PARA();
int32_t scrCommand_MFILTER_RGBA();
int32_t scrCommand_MFILTER_AREA();
int32_t scrCommand_MFILTER_SWAP();
int32_t scrCommand_MFILTER_ON();
int32_t scrCommand_MFILTER_OFF();
int32_t scrCommand_BLUR_ALLOFF();
int32_t scrCommand_FILTER_ALLOFF();

// The commands on the save game's party, items and Macca (original unit:
// scrParameterCommand, parameter_commands.cpp).
int32_t addItem();
int32_t addMagatama();
int32_t equipMagatama();
int32_t addMacca();
int32_t addMaccaPercent();
int32_t hasMacca();
int32_t damageParty();
int32_t healStock();
int32_t healStockSilently();
int32_t addDevil();
int32_t hasDevil();
int32_t storyDevilLeaves();
int32_t hasStoryDevil();
int32_t storyDevilId();
int32_t storyDevilMayLeave();
int32_t storyDevilMayNotLeave();
int32_t growStock();
int32_t stockFull();
int32_t playerStat();
int32_t addPlayerStat();
int32_t devilStat();
int32_t playerAlignment();
int32_t playerLevel();
int32_t devilDies();
int32_t isFirstPixie();
int32_t firstPixieId();
int32_t recordBossPress();
int32_t copyDevilStats();

} // namespace nocturne::scr
