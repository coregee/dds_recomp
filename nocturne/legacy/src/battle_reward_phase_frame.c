/* Zero-identity-credit projection of Main's exact context swap words.
 * Native scheduler ordering/timer/VSync/full boot remain separate. This is
 * an explicit three-instruction harness operation,never a claimed RET body.
 * Only actual V1 low64 and the native context word change;upper64 survives. */
#include "battle_reward_phase_frame.h"
#include <string.h>
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
void *nocturneEffectHostAddress(uint32_t);
void nocturneBattleRewardPhaseFrameContextSwap(void){
 uint32_t gp[4],v[4],word;nocturneEffectHostCpuRead(28,gp);nocturneEffectHostCpuRead(3,v);
 /* 001004f8: lw v1,-0x25f0(gp) */
 memcpy(&word,nocturneEffectHostAddress(gp[0]-0x25f0u),4);
 v[0]=word;v[1]=(word&0x80000000u)?UINT32_MAX:0;
 /* 00100504: xori v1,v1,0x1 */ v[0]^=1u;
 nocturneEffectHostCpuWrite(3,v);
 /* 0010050c: sw v1,-0x25f0(gp) */
 memcpy(nocturneEffectHostAddress(gp[0]-0x25f0u),&v[0],4);
}
