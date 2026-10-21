#include "battle_panel_renderer_bundle.h"
#include "battle_panel_color_native.h"
#include "battle_panel_color_privileged.h"
/* Complete fixed original registered packet/queue/Counter dependencies.
 * Shared live CPU/FPR/RAM, true guest frames and native volatile carry into
 * printf are preserved. No expected data, stack patch or game-result provider.
 */
#include "battle_action_packet_frames.h"
#include "battle_action_consumer.h"
#include "battle_action_scale_lookup_frames.h"
#include "effect_host_bindings.h"
#include "effect_model_child_dependency_frames.h"
#include "effect_random_frames.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattlePanelColorAddress(a);}






static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}


static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}
static void divideUnsigned(uint32_t n,uint32_t d){EE_ANCHOR_DIVU_STATE(d?n/d:UINT32_MAX,d?n%d:n);}


static uint64_t body_002c0c60(void){
nocturneEffectAxisNoteEntry(0x002c0c60u);
uint64_t incoming=cpu(31);
/* 002c0c60: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c0c64: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c68: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0c6c: jal 0x002c0ba8 */ set(31,0x002c0c74u);/* delay 002c0c70 */ set(16,cpu(5));nocturneBattlePanelRendererCall(UINT32_C(0x002c0ba8),UINT32_C(0x002c0c6c));
/* 002c0c74: divu v0,s0 */ divideUnsigned((uint32_t)cpu(2),(uint32_t)cpu(16));
/* 002c0c78: beql s0,zero,0x002c0c80 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 002c0c7c */ nocturneBattlePanelRendererTrap(7u,UINT32_C(0x002c0c7c));goto L_002c0c80;}}
L_002c0c80:;
/* 002c0c80: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c84: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0c88: mfhi v0 */ set(2,nocturneEffectHostHi());
/* 002c0c8c: jr ra */ {uint64_t target=cpu(31);/* delay 002c0c90 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint32_t nocturneBattlePanelRendererExisting2(uint32_t entry){switch(entry){case UINT32_C(0x002c0c60):(void)body_002c0c60();return 1u;default:return 0u;}}
