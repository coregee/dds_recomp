// The kouka process (original unit: nbKoukaProcess): plays the presentation
// queue every frame. Each packet waits `startframe` frames, then its player
// runs once a frame for `framelength` frames (or once, for a packet of
// length 0) and the packet leaves the queue. A packet on a unit waits while
// the unit's formation is busy (flag bits 0..2). The packets themselves are
// built in kouka.hpp.
//
// Players not rewritten yet run as original code (guest::callEffectPlayer).
// Names are the HD remaster's.
#pragma once

#include <cstdint>

#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// ---- the process ----
int32_t runEffectQueue(uint32_t process);    // nbKoukaProcess1: one frame
void shutdownEffectQueue(uint32_t process);  // nbKoukaShutdown: every packet deleted
uint32_t newEffectQueue(MainProcessData& data);
void startEffectQueue(MainProcessData& data);
void deleteNonEventPackets();                // nbDelUnEventKoukaPacket: units return, the rest go

// ---- the players (k: the queue, p: the packet) ----
void playBossEffect(EffectQueue& k, EffectPacket& p);         // Ongyo-Ki's clones and exits
void playSkillEffect(EffectQueue& k, EffectPacket& p);
void playPassiveEffectEnd(EffectQueue& k, EffectPacket& p);   // cuts the action's first cut short
void playMove(EffectQueue& k, EffectPacket& p);
void playUnitColor(EffectQueue& k, EffectPacket& p);
void playMotionStop(EffectQueue& k, EffectPacket& p);
void playReturn(EffectQueue& k, EffectPacket& p);
void playDodge(EffectQueue& k, EffectPacket& p);
void playSummon(EffectQueue& k, EffectPacket& p);
void playMotion(EffectQueue& k, EffectPacket& p);
void playDamageMotion(EffectQueue& k, EffectPacket& p);
void playSound(EffectQueue& k, EffectPacket& p);
void playAilmentEffect(EffectQueue& k, EffectPacket& p);
void playAilmentCureEffect(EffectQueue& k, EffectPacket& p);
void playHitEffect(EffectQueue& k, EffectPacket& p);
void playHpMp(EffectQueue& k, EffectPacket& p);
void playAilment(EffectQueue& k, EffectPacket& p);
void playPress(EffectQueue& k, EffectPacket& p);
void playAilmentMotionCure(EffectQueue& k, EffectPacket& p);
void playFade(EffectQueue& k, EffectPacket& p);
void playHitStop(EffectQueue& k, EffectPacket& p);
void playAnalyze(EffectQueue& k, EffectPacket& p);
void playStatusMessage(EffectQueue& k, EffectPacket& p);
void playFormationShow(EffectQueue& k, EffectPacket& p);
void playFormationFlag(EffectQueue& k, EffectPacket& p);
void playDeathEvent(EffectQueue& k, EffectPacket& p);
void playSkillName(EffectQueue& k, EffectPacket& p);
void playBuff(EffectQueue& k, EffectPacket& p);
void playFlareCharge(EffectQueue& k, EffectPacket& p);
void playPadShock(EffectQueue& k, EffectPacket& p);
void playSkillColor(EffectQueue& k, EffectPacket& p);
void playStockPanelFadeOut(EffectQueue& k, EffectPacket& p);
void playStockPanelEnd(EffectQueue& k, EffectPacket& p);

// A formation dodges: it steps `step` back at `speed` (nbSetSakeMotion's
// counterpart; tentative name).
void startDodge(ee::Float step, ee::Float speed, Formation& form);

// nbSetPlayerFormation: the player's side laid out again.
void setPlayerFormation(MainProcessData& data, int32_t empty);

// The stock panel starts fading out (tentative name).
void startStockPanelFadeOut();

} // namespace nocturne::nb
