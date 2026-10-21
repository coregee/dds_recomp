#include "battle_panel_renderer_bundle.h"
#include "battle_panel_color_native.h"
#include "battle_panel_color_privileged.h"
/* Whole93 registered SKILL dependency native variants; zero new identities.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_registered_frames.h"
#include "battle_action_consumer.h"
#include "battle_action_formula_frames.h"
#include "effect_host_bindings.h"
#include "pcp_effect_helpers.h"
#include "magatuhi_helpers.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#pragma warning(disable:4102)
#endif
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattlePanelColorAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}


static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
/* Genuine EE word division is defined even before a late native BREAK.
 * Primary and secondary banks are distinct; use the existing Formula bank
 * for cross-unit secondary state rather than a private or primary substitute.
 */



#include "ee_vu_rotation.h"
/* Each partial-word instruction performs its own original merge/store.
 * Preserve upper128 CPU lanes. LWL always sign-extends; EE LWR preserves
 * bits63:32 except at aligned offset0, where it sign-extends the full word.
 */
static void loadPartial32(unsigned r,uint32_t a,int left){uint8_t d[4],s[4];uint64_t old=cpu(r);uint32_t value=(uint32_t)old;memcpy(d,&value,4);memcpy(s,at(a&~3u),4);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[3u-o+i]=s[i];}else{for(unsigned i=o;i<4;i++)d[i-o]=s[i];}memcpy(&value,d,4);set(r,left||!o?sx(value):(old&UINT64_C(0xffffffff00000000))|value);}
static void storePartial32(uint32_t a,unsigned r,int left){uint8_t s[4];uint32_t value=(uint32_t)cpu(r);memcpy(s,&value,4);uint8_t *d=at(a&~3u);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[3u-o+i];}else{for(unsigned i=o;i<4;i++)d[i]=s[i-o];}}
















static void body_00100418(void){
nocturneEffectAxisNoteEntry(0x00100418u);
uint64_t incoming=cpu(31);
/* 00100418: jr ra */ {uint64_t target=cpu(31);/* delay 0010041c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffda10)));checkReturn(target,incoming);return;}
}
static void body_001c6018(void){
nocturneEffectAxisNoteEntry(0x001c6018u);
uint64_t incoming=cpu(31);
/* 001c6018: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c601c: addiu a3,v1,-0x4998 */ set(7,sx((uint32_t)cpu(3)+UINT32_C(0xffffb668)));
/* 001c6020: lw a0,0x1c(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x0000001c)));
/* 001c6024: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001c6028: lw v1,0x0(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 001c602c: beq v1,zero,0x001c605c */ {int taken=(cpu(3)==cpu(0));/* delay 001c6030 */ set(2,cpu(0));if(taken){goto L_001c605c;}}
/* 001c6034: lw a0,0x1c(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 001c6038: move v0,a2 */ set(2,cpu(6));
/* 001c603c: lw a1,0x18(a2) */ lw(5,ea(6,(int32_t)UINT32_C(0x00000018)));
/* 001c6040: lw v1,0x18(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000018)));
/* 001c6044: sw a0,0x1c(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));
/* 001c6048: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 001c604c: sw v1,0x18(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 001c6050: lw a0,0x1c(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 001c6054: lw v1,0x18(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000018)));
/* 001c6058: sw v1,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
L_001c605c:;
/* 001c605c: jr ra */ {uint64_t target=cpu(31);/* delay 001c6060 */ checkReturn(target,incoming);return;}
}
static void body_001c6128(void){
nocturneEffectAxisNoteEntry(0x001c6128u);
uint64_t incoming=cpu(31);
/* 001c6128: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001c612c: ori v0,zero,0x85ec */ set(2,cpu(0)|UINT32_C(0x000085ec));
/* 001c6130: beq a0,v0,0x001c6158 */ {int taken=(cpu(4)==cpu(2));/* delay 001c6134 */ set(3,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000002f));if(taken){goto L_001c6158;}}
/* 001c6138: bne v1,zero,0x001c6158 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c613c */ if(taken){goto L_001c6158;}}
/* 001c6140: ori v0,zero,0xffc6 */ set(2,cpu(0)|UINT32_C(0x0000ffc6));
/* 001c6144: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c6148: andi v0,v0,0xffff */ set(2,cpu(2)&UINT32_C(0x0000ffff));
/* 001c614c: sltiu v0,v0,0x7 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000007));
/* 001c6150: beql v0,zero,0x001c6158 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c6154 */ sh(ea(28,(int32_t)UINT32_C(0xffffa890)),(uint16_t)cpu(4));goto L_001c6158;}}
L_001c6158:;
/* 001c6158: jr ra */ {uint64_t target=cpu(31);/* delay 001c615c */ checkReturn(target,incoming);return;}
}
static void body_001c6ff8(void){
nocturneEffectAxisNoteEntry(0x001c6ff8u);
uint64_t incoming=cpu(31);
/* 001c6ff8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c6ffc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7000: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7004: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7008: jal 0x00100418 */ set(31,0x001c7010u);/* delay 001c700c */ set(17,cpu(4));nocturneBattlePanelRendererCall(UINT32_C(0x00100418),UINT32_C(0x001c7008));
/* 001c7010: andi s0,v0,0xff */ set(16,cpu(2)&UINT32_C(0x000000ff));
/* 001c7014: move a1,s1 */ set(5,cpu(17));
/* 001c7018: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001c701c: move a2,zero */ set(6,cpu(0));
/* 001c7020: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c7024: addiu at,at,-0x443c */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffbbc4)));
/* 001c7028: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 001c702c: jal 0x001c8120 */ set(31,0x001c7034u);/* delay 001c7030 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));nocturneBattlePanelRendererCall(UINT32_C(0x001c8120),UINT32_C(0x001c702c));
/* 001c7034: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001c7038: move v0,zero */ set(2,cpu(0));
/* 001c703c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7040: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7044: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7048: jr ra */ {uint64_t target=cpu(31);/* delay 001c704c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c7080(void){
nocturneEffectAxisNoteEntry(0x001c7080u);
uint64_t incoming=cpu(31);
/* 001c7080: jr ra */ {uint64_t target=cpu(31);/* delay 001c7084 */ set(2,sx(UINT32_C(0x00000018)));checkReturn(target,incoming);return;}
}
static void body_001c7088(void){
nocturneEffectAxisNoteEntry(0x001c7088u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001c7088: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c708c: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 001c7090: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7094: move s0,a0 */ set(16,cpu(4));
/* 001c7098: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c709c: move s1,a1 */ set(17,cpu(5));
/* 001c70a0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c70a4: move s2,zero */ set(18,cpu(0));
/* 001c70a8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c70ac: swc1 f20,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 001c70b0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c70b4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001c70b8: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 001c70bc: lbu a0,0x15(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 001c70c0: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c70c4: slti v1,a0,0x2 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c70c8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c70cc: xori v1,v1,0x0 */ set(3,cpu(3)^UINT32_C(0x00000000));
/* 001c70d0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c70d4: lui s3,0x57 */ set(19,sx(UINT32_C(0x00570000)));
/* 001c70d8: addiu s3,s3,-0x45d0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffba30)));
/* 001c70dc: addu s3,s3,v0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(2)));
/* 001c70e0: jal 0x001c83b0 */ set(31,0x001c70e8u);/* delay 001c70e4 */ if(cpu(3)!=0){set(18,cpu(6));}nocturneBattlePanelRendererCall(UINT32_C(0x001c83b0),UINT32_C(0x001c70e0));
/* 001c70e8: sb v0,0x18(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(2));
/* 001c70ec: jal 0x001c8418 */ set(31,0x001c70f4u);/* delay 001c70f0 */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000015))));nocturneBattlePanelRendererCall(UINT32_C(0x001c8418),UINT32_C(0x001c70ec));
/* 001c70f4: lbu v1,0x15(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 001c70f8: sb v0,0x19(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000019)),(uint8_t)cpu(2));
/* 001c70fc: sltiu a0,v1,0x2 */ set(4,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c7100: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c7104: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c7108: lbu v0,0x6060(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x00006060))));
/* 001c710c: sll a1,v0,0x18 */ set(5,sx((uint32_t)cpu(2)<<24));
/* 001c7110: sra v1,a1,0x18 */ set(3,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c7114: beq a0,zero,0x001c7140 */ {int taken=(cpu(4)==cpu(0));/* delay 001c7118 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));if(taken){goto L_001c7140;}}
/* 001c711c: lbu v0,0x18(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000018))));
/* 001c7120: li s2,0x1 */ set(18,sx(UINT32_C(0x00000001)));
/* 001c7124: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 001c7128: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001c712c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 001c7130: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001c7134: nop  */ 
/* 001c7138: nop  */ 
/* 001c713c: div.S f20,f0,f1 */ f[20]=EE_FPU_DIV_S(f[0],f[1]);
L_001c7140:;
/* 001c7140: lbu a0,0x17(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000017))));
/* 001c7144: beq s2,zero,0x001c7168 */ {int taken=(cpu(18)==cpu(0));/* delay 001c7148 */ set(2,cpu(4)&UINT32_C(0x00000002));if(taken){goto L_001c7168;}}
/* 001c714c: lhu v1,0x0(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001c7150: sltiu v0,v1,0x80 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c7154: beq v0,zero,0x001c7170 */ {int taken=(cpu(2)==cpu(0));/* delay 001c7158 */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_001c7170;}}
/* 001c715c: sra v0,a1,0x19 */ set(2,sx((uint32_t)((int32_t)cpu(5)>>25)));
/* 001c7160: b 0x001c716c */ /* delay 001c7164 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));goto L_001c716c;
L_001c7168:;
/* 001c7168: lhu v1,0x0(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000000))));
L_001c716c:;
/* 001c716c: li v0,0x20 */ set(2,sx(UINT32_C(0x00000020)));
L_001c7170:;
/* 001c7170: bne v1,v0,0x001c71a8 */ {int taken=(cpu(3)!=cpu(2));/* delay 001c7174 */ set(2,sx(UINT32_C(0x000002c1)));if(taken){goto L_001c71a8;}}
/* 001c7178: lbu v1,0x15(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 001c717c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c7180: beql v1,v0,0x001c7194 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 001c7184 */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));goto L_001c7194;}}
/* 001c7188: bne v1,zero,0x001c71a8 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c718c */ set(2,sx(UINT32_C(0x000002c1)));if(taken){goto L_001c71a8;}}
/* 001c7190: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
L_001c7194:;
/* 001c7194: lw v1,-0x4d5c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb2a4)));
/* 001c7198: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 001c719c: addu v1,v0,v1 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c71a0: b 0x001c7268 */ /* delay 001c71a4 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));goto L_001c7268;
L_001c71a8:;
/* 001c71a8: bne s1,v0,0x001c71c0 */ {int taken=(cpu(17)!=cpu(2));/* delay 001c71ac */ set(2,cpu(4)&UINT32_C(0x00000001));if(taken){goto L_001c71c0;}}
/* 001c71b0: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001c71b4: addiu v0,v0,-0x7 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff9)));
/* 001c71b8: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c71bc: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
L_001c71c0:;
/* 001c71c0: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 001c71c4: beql v0,zero,0x001c726c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c71c8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001c726c;}}
/* 001c71cc: lw v0,0x4(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 001c71d0: lbu v1,0x16(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000016))));
/* 001c71d4: beq v1,zero,0x001c7268 */ {int taken=(cpu(3)==cpu(0));/* delay 001c71d8 */ set(17,sx((uint32_t)cpu(17)<<1));if(taken){goto L_001c7268;}}
/* 001c71dc: lw v0,0x8(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 001c71e0: slt v0,s1,v0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(2));
/* 001c71e4: beql v0,zero,0x001c726c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c71e8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001c726c;}}
/* 001c71ec: lw v0,0x10(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 001c71f0: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 001c71f4: lb a0,0x1(v0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000001))));
/* 001c71f8: beq a0,zero,0x001c7268 */ {int taken=(cpu(4)==cpu(0));/* delay 001c71fc */ set(3,sx((uint32_t)((int32_t)cpu(17)>>1)));if(taken){goto L_001c7268;}}
/* 001c7200: lb v0,0x0(v0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c7204: lui at,0x4180 */ set(1,sx(UINT32_C(0x41800000)));
/* 001c7208: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 001c720c: addiu a1,v1,0x20 */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001c7210: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 001c7214: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 001c7218: subu v0,a0,v0 */ set(2,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));
/* 001c721c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 001c7220: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001c7224: li v1,0x21 */ set(3,sx(UINT32_C(0x00000021)));
/* 001c7228: mul.S f1,f1,f2 */ f[1]=EE_FPU_MUL_S(f[1],f[2]);
/* 001c722c: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 001c7230: mul.S f1,f1,f20 */ f[1]=EE_FPU_MUL_S(f[1],f[20]);
/* 001c7234: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 001c7238: mfc1 a2,f2 */ set(6,sx(f[2]));
/* 001c723c: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 001c7240: mfc1 a0,f0 */ set(4,sx(f[0]));
/* 001c7244: beq a1,v1,0x001c7254 */ {int taken=(cpu(5)==cpu(3));/* delay 001c7248 */ set(2,sx(UINT32_C(0x00000031)));if(taken){goto L_001c7254;}}
/* 001c724c: bne a1,v0,0x001c7260 */ {int taken=(cpu(5)!=cpu(2));/* delay 001c7250 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));if(taken){goto L_001c7260;}}
L_001c7254:;
/* 001c7254: addiu a0,a0,-0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffe0)));
/* 001c7258: addiu a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000004)));
/* 001c725c: subu v0,zero,a0 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
L_001c7260:;
/* 001c7260: sw a2,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(6));
/* 001c7264: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_001c7268:;
/* 001c7268: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001c726c:;
/* 001c726c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7270: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7274: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7278: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c727c: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7280: jr ra */ {uint64_t target=cpu(31);/* delay 001c7284 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c7408(void){
nocturneEffectAxisNoteEntry(0x001c7408u);
uint64_t incoming=cpu(31);
/* 001c7408: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001c740c: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7410: sll s0,a3,0x18 */ set(16,sx((uint32_t)cpu(7)<<24));
/* 001c7414: sd s1,0x38(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7418: sra s0,s0,0x18 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>24)));
/* 001c741c: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c7420: move s2,a2 */ set(18,cpu(6));
/* 001c7424: sd s3,0x48(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c7428: move s3,a0 */ set(19,cpu(4));
/* 001c742c: sd s4,0x50(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c7430: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c7434: jal 0x001c6018 */ set(31,0x001c743cu);/* delay 001c7438 */ set(20,cpu(5));nocturneBattlePanelRendererCall(UINT32_C(0x001c6018),UINT32_C(0x001c7434));
/* 001c743c: lw a0,0x4(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 001c7440: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c7444: addiu a2,v1,-0x45d0 */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0xffffba30)));
/* 001c7448: lw s1,0x14(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x00000014)));
/* 001c744c: sra a0,a0,0x4 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>4)));
/* 001c7450: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001c7454: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001c7458: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 001c745c: sh a1,0x4(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(5));
/* 001c7460: lw v1,0x8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 001c7464: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001c7468: sra v1,v1,0x4 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>4)));
/* 001c746c: bne s0,zero,0x001c7480 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c7470 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));if(taken){goto L_001c7480;}}
/* 001c7474: b 0x001c7488 */ /* delay 001c7478 */ sb(ea(29,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(0));goto L_001c7488;
L_001c7480:;
/* 001c7480: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 001c7484: sb v0,0x18(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(2));
L_001c7488:;
/* 001c7488: lw v1,0x170(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000170)));
/* 001c748c: li v0,0x14 */ set(2,sx(UINT32_C(0x00000014)));
/* 001c7490: lhu a1,0x160(a2) */ set(5,half(ea(6,(int32_t)UINT32_C(0x00000160))));
/* 001c7494: lhu a3,0x0(sp) */ set(7,half(ea(29,(int32_t)UINT32_C(0x00000000))));
/* 001c7498: sll v1,v1,0x6 */ set(3,sx((uint32_t)cpu(3)<<6));
/* 001c749c: lhu a2,0x4(sp) */ set(6,half(ea(29,(int32_t)UINT32_C(0x00000004))));
/* 001c74a0: sw s2,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 001c74a4: sb v0,0x19(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000019)),(uint8_t)cpu(2));
/* 001c74a8: sh s3,0x24(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000024)),(uint16_t)cpu(19));
/* 001c74ac: sh s4,0x26(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000026)),(uint16_t)cpu(20));
/* 001c74b0: sh a1,0x1a(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(5));
/* 001c74b4: sw v1,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));
/* 001c74b8: sh a3,0x20(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000020)),(uint16_t)cpu(7));
/* 001c74bc: jal 0x002aa9e0 */ set(31,0x001c74c4u);/* delay 001c74c0 */ sh(ea(29,(int32_t)UINT32_C(0x00000022)),(uint16_t)cpu(6));nocturneBattlePanelRendererCall(UINT32_C(0x002aa9e0),UINT32_C(0x001c74bc));
/* 001c74c4: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c74c8: move v0,s1 */ set(2,cpu(17));
/* 001c74cc: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c74d0: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c74d4: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c74d8: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c74dc: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c74e0: jr ra */ {uint64_t target=cpu(31);/* delay 001c74e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_001c74e8(void){
nocturneEffectAxisNoteEntry(0x001c74e8u);
uint64_t incoming=cpu(31);
/* 001c74e8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c74ec: andi v0,a0,0xff */ set(2,cpu(4)&UINT32_C(0x000000ff));
/* 001c74f0: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c74f4: sll s0,v0,0x3 */ set(16,sx((uint32_t)cpu(2)<<3));
/* 001c74f8: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001c74fc: li a0,0x120 */ set(4,sx(UINT32_C(0x00000120)));
/* 001c7500: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001c7504: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7508: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c750c: addiu at,at,-0x45d0 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffba30)));
/* 001c7510: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 001c7514: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7518: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c751c: jal 0x002a8af8 */ set(31,0x001c7524u);/* delay 001c7520 */ set(18,cpu(5));nocturneBattlePanelRendererCall(UINT32_C(0x002a8af8),UINT32_C(0x001c751c));
/* 001c7524: lw a0,0x1c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001c7528: move a1,sp */ set(5,cpu(29));
/* 001c752c: jal 0x001ca9c8 */ set(31,0x001c7534u);/* delay 001c7530 */ set(17,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x001ca9c8),UINT32_C(0x001c752c));
/* 001c7534: move a0,s1 */ set(4,cpu(17));
/* 001c7538: lw a2,0x1c(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001c753c: move a1,s2 */ set(5,cpu(18));
/* 001c7540: jal 0x001caa18 */ set(31,0x001c7548u);/* delay 001c7544 */ set(7,cpu(29));nocturneBattlePanelRendererCall(UINT32_C(0x001caa18),UINT32_C(0x001c7540));
/* 001c7548: move v0,s1 */ set(2,cpu(17));
/* 001c754c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7550: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7554: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7558: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c755c: jr ra */ {uint64_t target=cpu(31);/* delay 001c7560 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c7568(void){
nocturneEffectAxisNoteEntry(0x001c7568u);
uint64_t incoming=cpu(31);
/* 001c7568: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c756c: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c7570: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7574: move s2,a0 */ set(18,cpu(4));
/* 001c7578: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c757c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7580: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7584: addiu s5,v1,-0x45d0 */ set(21,sx((uint32_t)cpu(3)+UINT32_C(0xffffba30)));
/* 001c7588: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c758c: move s6,a1 */ set(22,cpu(5));
/* 001c7590: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7594: sll s4,s6,0x2 */ set(20,sx((uint32_t)cpu(22)<<2));
/* 001c7598: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c759c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c75a0: lbu v0,0x15(s2) */ set(2,byte(ea(18,(int32_t)UINT32_C(0x00000015))));
/* 001c75a4: sll v1,v0,0x3 */ set(3,sx((uint32_t)cpu(2)<<3));
/* 001c75a8: move a0,v0 */ set(4,cpu(2));
/* 001c75ac: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c75b0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c75b4: addu s3,v1,s5 */ set(19,sx((uint32_t)cpu(3)+(uint32_t)cpu(21)));
/* 001c75b8: lw v0,0x18(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000018)));
/* 001c75bc: addu v0,s4,v0 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 001c75c0: lw a2,0x0(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001c75c4: beq a2,zero,0x001c75e0 */ {int taken=(cpu(6)==cpu(0));/* delay 001c75c8 */ set(2,cpu(6));if(taken){goto L_001c75e0;}}
/* 001c75cc: lhu v1,0x4(a2) */ set(3,half(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 001c75d0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c75d4: b 0x001c7634 */ /* delay 001c75d8 */ sh(ea(6,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));goto L_001c7634;
L_001c75e0:;
/* 001c75e0: jal 0x001c74e8 */ set(31,0x001c75e8u);/* delay 001c75e4 */ nocturneBattlePanelRendererCall(UINT32_C(0x001c74e8),UINT32_C(0x001c75e0));
/* 001c75e8: lbu a0,0x15(s2) */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000015))));
/* 001c75ec: jal 0x001c83f0 */ set(31,0x001c75f4u);/* delay 001c75f0 */ set(17,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x001c83f0),UINT32_C(0x001c75ec));
/* 001c75f4: lbu a0,0x15(s2) */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000015))));
/* 001c75f8: jal 0x001c8458 */ set(31,0x001c7600u);/* delay 001c75fc */ set(16,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x001c8458),UINT32_C(0x001c75f8));
/* 001c7600: move a0,s0 */ set(4,cpu(16));
/* 001c7604: move a2,s1 */ set(6,cpu(17));
/* 001c7608: move a1,v0 */ set(5,cpu(2));
/* 001c760c: jal 0x001c7408 */ set(31,0x001c7614u);/* delay 001c7610 */ set(7,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x001c7408),UINT32_C(0x001c760c));
/* 001c7614: lw v1,0x18(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000018)));
/* 001c7618: lw a0,0x144(s5) */ lw(4,ea(21,(int32_t)UINT32_C(0x00000144)));
/* 001c761c: move a2,v0 */ set(6,cpu(2));
/* 001c7620: addu v1,s4,v1 */ set(3,sx((uint32_t)cpu(20)+(uint32_t)cpu(3)));
/* 001c7624: sh s6,0x0(a2) */ sh(ea(6,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(22));
/* 001c7628: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 001c762c: sw a2,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 001c7630: sw a0,0x144(s5) */ sw(ea(21,(int32_t)UINT32_C(0x00000144)),(uint32_t)cpu(4));
L_001c7634:;
/* 001c7634: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7638: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c763c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7640: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7644: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7648: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c764c: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7650: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7654: jr ra */ {uint64_t target=cpu(31);/* delay 001c7658 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c7660(void){
nocturneEffectAxisNoteEntry(0x001c7660u);
uint64_t incoming=cpu(31);
/* 001c7660: sb a2,0x15(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000015)),(uint8_t)cpu(6));
/* 001c7664: li v0,-0x100 */ set(2,sx(UINT32_C(0xffffff00)));
/* 001c7668: sb a3,0x14(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(7));
/* 001c766c: and t0,t0,v0 */ set(8,cpu(8)&cpu(2));
/* 001c7670: sb t1,0x16(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(9));
/* 001c7674: sh a1,0x0(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(5));
/* 001c7678: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c767c: sw t0,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(8));
/* 001c7680: sb v0,0x17(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000017)),(uint8_t)cpu(2));
/* 001c7684: sw zero,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 001c7688: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001c768c: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001c7690: sw zero,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 001c7694: sh zero,0x2(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(0));
/* 001c7698: sw zero,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 001c769c: sw zero,0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 001c76a0: jr ra */ {uint64_t target=cpu(31);/* delay 001c76a4 */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_001c76a8(void){
nocturneEffectAxisNoteEntry(0x001c76a8u);
uint64_t incoming=cpu(31);
/* 001c76a8: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 001c76ac: sw zero,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 001c76b0: sb v0,0x0(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001c76b4: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001c76b8: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001c76bc: sb zero,0x1(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
/* 001c76c0: sw zero,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 001c76c4: sw zero,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 001c76c8: sw zero,0x24(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 001c76cc: sw zero,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 001c76d0: sw a0,0x2c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(4));
/* 001c76d4: sw zero,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 001c76d8: jr ra */ {uint64_t target=cpu(31);/* delay 001c76dc */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_001c76e0(void){
nocturneEffectAxisNoteEntry(0x001c76e0u);
uint64_t incoming=cpu(31);
/* 001c76e0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c76e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c76e8: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 001c76ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c76f0: andi s1,a2,0xff */ set(17,cpu(6)&UINT32_C(0x000000ff));
/* 001c76f4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c76f8: andi s2,a3,0xff */ set(18,cpu(7)&UINT32_C(0x000000ff));
/* 001c76fc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7700: andi s3,a0,0xffff */ set(19,cpu(4)&UINT32_C(0x0000ffff));
/* 001c7704: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7708: addiu s0,s0,-0x45d0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffba30)));
/* 001c770c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7710: andi s5,a1,0xff */ set(21,cpu(5)&UINT32_C(0x000000ff));
/* 001c7714: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7718: move s6,t0 */ set(22,cpu(8));
/* 001c771c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7720: jal 0x001cabd8 */ set(31,0x001c7728u);/* delay 001c7724 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000150)));nocturneBattlePanelRendererCall(UINT32_C(0x001cabd8),UINT32_C(0x001c7720));
/* 001c7728: lui t0,0xa09d */ set(8,sx(UINT32_C(0xa09d0000)));
/* 001c772c: move s4,v0 */ set(20,cpu(2));
/* 001c7730: lw v0,0x148(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000148)));
/* 001c7734: move a1,s3 */ set(5,cpu(19));
/* 001c7738: move a0,s4 */ set(4,cpu(20));
/* 001c773c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c7740: move a3,s1 */ set(7,cpu(17));
/* 001c7744: sw v0,0x148(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000148)),(uint32_t)cpu(2));
/* 001c7748: move s0,zero */ set(16,cpu(0));
/* 001c774c: move t1,s2 */ set(9,cpu(18));
/* 001c7750: move a2,s5 */ set(6,cpu(21));
/* 001c7754: jal 0x001c7660 */ set(31,0x001c775cu);/* delay 001c7758 */ set(8,cpu(8)|UINT32_C(0x0000c300));nocturneBattlePanelRendererCall(UINT32_C(0x001c7660),UINT32_C(0x001c7754));
/* 001c775c: move a0,s4 */ set(4,cpu(20));
/* 001c7760: lhu v1,0x0(s4) */ set(3,half(ea(20,(int32_t)UINT32_C(0x00000000))));
/* 001c7764: sltiu v0,v1,0x20 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 001c7768: bne v0,zero,0x001c77b4 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c776c */ set(5,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));if(taken){goto L_001c77b4;}}
/* 001c7770: beql a1,zero,0x001c7798 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 001c7774 */ set(2,half(ea(20,(int32_t)UINT32_C(0x00000000))));goto L_001c7798;}}
/* 001c7778: li v0,0x5e */ set(2,sx(UINT32_C(0x0000005e)));
/* 001c777c: bnel v1,v0,0x001c7790 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 001c7780 */ set(2,half(ea(20,(int32_t)UINT32_C(0x00000000))));goto L_001c7790;}}
/* 001c7784: li v0,0x26 */ set(2,sx(UINT32_C(0x00000026)));
/* 001c7788: sh v0,0x0(s4) */ sh(ea(20,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 001c778c: lhu v0,0x0(s4) */ set(2,half(ea(20,(int32_t)UINT32_C(0x00000000))));
L_001c7790:;
/* 001c7790: b 0x001c77b4 */ /* delay 001c7794 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffe0)));goto L_001c77b4;
L_001c7798:;
/* 001c7798: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 001c779c: ori v1,v1,0x7f80 */ set(3,cpu(3)|UINT32_C(0x00007f80));
/* 001c77a0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c77a4: andi a1,v0,0xff00 */ set(5,cpu(2)&UINT32_C(0x0000ff00));
/* 001c77a8: andi v0,v0,0x7f */ set(2,cpu(2)&UINT32_C(0x0000007f));
/* 001c77ac: sra a1,a1,0x1 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>1)));
/* 001c77b0: addu s0,a1,v0 */ set(16,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
L_001c77b4:;
/* 001c77b4: jal 0x001c7568 */ set(31,0x001c77bcu);/* delay 001c77b8 */ set(5,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x001c7568),UINT32_C(0x001c77b4));
/* 001c77bc: move a0,s4 */ set(4,cpu(20));
/* 001c77c0: sw v0,0x1c(s4) */ sw(ea(20,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 001c77c4: move a1,s0 */ set(5,cpu(16));
/* 001c77c8: jal 0x001c7088 */ set(31,0x001c77d0u);/* delay 001c77cc */ set(6,cpu(22));nocturneBattlePanelRendererCall(UINT32_C(0x001c7088),UINT32_C(0x001c77c8));
/* 001c77d0: sll a0,s5,0x18 */ set(4,sx((uint32_t)cpu(21)<<24));
/* 001c77d4: lbu v0,0x17(s4) */ set(2,byte(ea(20,(int32_t)UINT32_C(0x00000017))));
/* 001c77d8: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c77dc: andi v0,v0,0x10 */ set(2,cpu(2)&UINT32_C(0x00000010));
/* 001c77e0: beq v0,zero,0x001c77f8 */ {int taken=(cpu(2)==cpu(0));/* delay 001c77e4 */ set(5,cpu(16));if(taken){goto L_001c77f8;}}
/* 001c77e8: jal 0x001c7080 */ set(31,0x001c77f0u);/* delay 001c77ec */ nocturneBattlePanelRendererCall(UINT32_C(0x001c7080),UINT32_C(0x001c77e8));
/* 001c77f0: b 0x001c77fc */ /* delay 001c77f4 */ sw(ea(20,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));goto L_001c77fc;
L_001c77f8:;
/* 001c77f8: sw zero,0x8(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
L_001c77fc:;
/* 001c77fc: move v0,s4 */ set(2,cpu(20));
/* 001c7800: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7804: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7808: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c780c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7810: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7814: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7818: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c781c: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7820: jr ra */ {uint64_t target=cpu(31);/* delay 001c7824 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c7828(void){
nocturneEffectAxisNoteEntry(0x001c7828u);
uint64_t incoming=cpu(31);
/* 001c7828: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c782c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c7830: sll a2,a2,0x18 */ set(6,sx((uint32_t)cpu(6)<<24));
/* 001c7834: sll a3,a3,0x18 */ set(7,sx((uint32_t)cpu(7)<<24));
/* 001c7838: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c783c: move s0,t0 */ set(16,cpu(8));
/* 001c7840: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c7844: sra a2,a2,0x18 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c7848: sra a3,a3,0x18 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>24)));
/* 001c784c: move t0,zero */ set(8,cpu(0));
/* 001c7850: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7854: jal 0x001c7890 */ set(31,0x001c785cu);/* delay 001c7858 */ set(9,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x001c7890),UINT32_C(0x001c7854));
/* 001c785c: move a0,s0 */ set(4,cpu(16));
/* 001c7860: move v1,v0 */ set(3,cpu(2));
/* 001c7864: move v0,s0 */ set(2,cpu(16));
/* 001c7868: beq v1,zero,0x001c7880 */ {int taken=(cpu(3)==cpu(0));/* delay 001c786c */ set(5,cpu(3));if(taken){goto L_001c7880;}}
/* 001c7870: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7874: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7878: j 0x001c8108 */ /* delay 001c787c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattlePanelRendererCall(UINT32_C(0x001c8108),UINT32_C(0x001c7878));return;
L_001c7880:;
/* 001c7880: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7884: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7888: jr ra */ {uint64_t target=cpu(31);/* delay 001c788c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c7890(void){
nocturneEffectAxisNoteEntry(0x001c7890u);
uint64_t incoming=cpu(31);
/* 001c7890: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c7894: sll a3,a3,0x18 */ set(7,sx((uint32_t)cpu(7)<<24));
/* 001c7898: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001c789c: sll a2,a2,0x18 */ set(6,sx((uint32_t)cpu(6)<<24));
/* 001c78a0: sra a3,a3,0x18 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>24)));
/* 001c78a4: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c78a8: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c78ac: move s2,t0 */ set(18,cpu(8));
/* 001c78b0: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c78b4: move s5,a0 */ set(21,cpu(4));
/* 001c78b8: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c78bc: sra s6,a2,0x18 */ set(22,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c78c0: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c78c4: move s8,zero */ set(30,cpu(0));
/* 001c78c8: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c78cc: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c78d0: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c78d4: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c78d8: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c78dc: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c78e0: sw t1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(9));
/* 001c78e4: bltz a1,0x001c78f0 */ {int taken=((int64_t)cpu(5)<0);/* delay 001c78e8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));if(taken){goto L_001c78f0;}}
/* 001c78ec: sb a1,-0x4d4c(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffb2b4)),(uint8_t)cpu(5));
L_001c78f0:;
/* 001c78f0: lbu a1,-0x4d4c(gp) */ set(5,byte(ea(28,(int32_t)UINT32_C(0xffffb2b4))));
/* 001c78f4: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 001c78f8: addiu s0,v0,-0x45d0 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffba30)));
/* 001c78fc: sll v1,a1,0x3 */ set(3,sx((uint32_t)cpu(5)<<3));
/* 001c7900: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 001c7904: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c7908: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 001c790c: lw a1,0x1c(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x0000001c)));
/* 001c7910: beq a1,zero,0x001c7a2c */ {int taken=(cpu(5)==cpu(0));/* delay 001c7914 */ set(2,cpu(0));if(taken){goto L_001c7a2c;}}
/* 001c7918: beq s5,zero,0x001c792c */ {int taken=(cpu(21)==cpu(0));/* delay 001c791c */ if(taken){goto L_001c792c;}}
/* 001c7920: jal 0x002d5d0c */ set(31,0x001c7928u);/* delay 001c7924 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d5d0c),UINT32_C(0x001c7920));
/* 001c7928: move s8,v0 */ set(30,cpu(2));
L_001c792c:;
/* 001c792c: bnel s2,zero,0x001c7958 */ {int taken=(cpu(18)!=cpu(0));if(taken){/* delay 001c7930 */ lw(20,ea(18,(int32_t)UINT32_C(0x00000020)));goto L_001c7958;}}
/* 001c7934: jal 0x001cabd8 */ set(31,0x001c793cu);/* delay 001c7938 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000154)));nocturneBattlePanelRendererCall(UINT32_C(0x001cabd8),UINT32_C(0x001c7934));
/* 001c793c: move s2,v0 */ set(18,cpu(2));
/* 001c7940: lw v0,0x14c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000014c)));
/* 001c7944: move a0,s2 */ set(4,cpu(18));
/* 001c7948: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c794c: jal 0x001c76a8 */ set(31,0x001c7954u);/* delay 001c7950 */ sw(ea(16,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x001c76a8),UINT32_C(0x001c794c));
/* 001c7954: lw s4,0x20(s2) */ lw(20,ea(18,(int32_t)UINT32_C(0x00000020)));
L_001c7958:;
/* 001c7958: move s3,zero */ set(19,cpu(0));
/* 001c795c: beq s8,zero,0x001c7a0c */ {int taken=(cpu(30)==cpu(0));/* delay 001c7960 */ set(17,cpu(0));if(taken){goto L_001c7a0c;}}
/* 001c7964: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7968: andi s7,s6,0xff */ set(23,cpu(22)&UINT32_C(0x000000ff));
/* 001c796c: andi s6,v0,0xff */ set(22,cpu(2)&UINT32_C(0x000000ff));
/* 001c7970: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c7974: nop  */ 
L_001c7978:;
/* 001c7978: lbu s0,0x0(v0) */ set(16,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c797c: sltiu v0,s0,0x80 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c7980: bne v0,zero,0x001c7998 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7984 */ set(4,sx((uint32_t)cpu(16)<<8));if(taken){goto L_001c7998;}}
/* 001c7988: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 001c798c: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c7990: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c7994: or s0,v1,a0 */ set(16,cpu(3)|cpu(4));
L_001c7998:;
/* 001c7998: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 001c799c: move a0,s0 */ set(4,cpu(16));
/* 001c79a0: lbu a1,-0x4d4c(gp) */ set(5,byte(ea(28,(int32_t)UINT32_C(0xffffb2b4))));
/* 001c79a4: move a2,s7 */ set(6,cpu(23));
/* 001c79a8: sltu t0,zero,v0 */ set(8,cpu(0)<cpu(2));
/* 001c79ac: move a3,s6 */ set(7,cpu(22));
/* 001c79b0: movn t0,zero,s3 */ if(cpu(19)!=0){set(8,cpu(0));}
/* 001c79b4: jal 0x001c76e0 */ set(31,0x001c79bcu);/* delay 001c79b8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x001c76e0),UINT32_C(0x001c79b4));
/* 001c79bc: bne s4,zero,0x001c79d0 */ {int taken=(cpu(20)!=cpu(0));/* delay 001c79c0 */ set(17,cpu(2));if(taken){goto L_001c79d0;}}
/* 001c79c4: b 0x001c79d4 */ /* delay 001c79c8 */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(17));goto L_001c79d4;
L_001c79d0:;
/* 001c79d0: sw s1,0x28(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(17));
L_001c79d4:;
/* 001c79d4: lw a1,0xc(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 001c79d8: move a0,s0 */ set(4,cpu(16));
/* 001c79dc: lw v0,0xc(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 001c79e0: lw v1,0x18(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 001c79e4: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 001c79e8: sw s4,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(20));
/* 001c79ec: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c79f0: sw v0,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c79f4: sw v1,0x18(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 001c79f8: jal 0x001c6128 */ set(31,0x001c7a00u);/* delay 001c79fc */ set(20,cpu(17));nocturneBattlePanelRendererCall(UINT32_C(0x001c6128),UINT32_C(0x001c79f8));
/* 001c7a00: sltu v0,s3,s8 */ set(2,cpu(19)<cpu(30));
/* 001c7a04: bne v0,zero,0x001c7978 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7a08 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));if(taken){goto L_001c7978;}}
L_001c7a0c:;
/* 001c7a0c: beq s1,zero,0x001c7a2c */ {int taken=(cpu(17)==cpu(0));/* delay 001c7a10 */ set(2,cpu(18));if(taken){goto L_001c7a2c;}}
/* 001c7a14: sw s1,0x20(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(17));
/* 001c7a18: lbu v0,0x18(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 001c7a1c: sh v0,0x10(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(2));
/* 001c7a20: lbu v1,0x19(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000019))));
/* 001c7a24: sh v1,0x12(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(3));
/* 001c7a28: move v0,s2 */ set(2,cpu(18));
L_001c7a2c:;
/* 001c7a2c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7a30: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7a34: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7a38: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7a3c: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7a40: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7a44: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c7a48: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c7a4c: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c7a50: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c7a54: jr ra */ {uint64_t target=cpu(31);/* delay 001c7a58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_001c7a88(void){
nocturneEffectAxisNoteEntry(0x001c7a88u);
uint64_t incoming=cpu(31);
/* 001c7a88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c7a8c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7a90: move s0,a0 */ set(16,cpu(4));
/* 001c7a94: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7a98: jal 0x001c8230 */ set(31,0x001c7aa0u);/* delay 001c7a9c */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(5));nocturneBattlePanelRendererCall(UINT32_C(0x001c8230),UINT32_C(0x001c7a98));
/* 001c7aa0: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c7aa4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7aa8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7aac: jr ra */ {uint64_t target=cpu(31);/* delay 001c7ab0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c7b30(void){
nocturneEffectAxisNoteEntry(0x001c7b30u);
uint64_t incoming=cpu(31);
/* 001c7b30: sw a2,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 001c7b34: jr ra */ {uint64_t target=cpu(31);/* delay 001c7b38 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_001c7b40(void){
nocturneEffectAxisNoteEntry(0x001c7b40u);
uint64_t incoming=cpu(31);
/* 001c7b40: srl a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)>>4));
/* 001c7b44: jr ra */ {uint64_t target=cpu(31);/* delay 001c7b48 */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_001c7ba8(void){
nocturneEffectAxisNoteEntry(0x001c7ba8u);
uint64_t incoming=cpu(31);
/* 001c7ba8: beq a0,zero,0x001c7bf8 */ {int taken=(cpu(4)==cpu(0));/* delay 001c7bac */ if(taken){goto L_001c7bf8;}}
/* 001c7bb0: lw v0,0x1c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001c7bb4: nop  */ 
L_001c7bb8:;
/* 001c7bb8: beql v0,zero,0x001c7be8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c7bbc */ lw(4,ea(4,(int32_t)UINT32_C(0x00000024)));goto L_001c7be8;}}
/* 001c7bc0: sw a1,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));
/* 001c7bc4: nop  */ 
L_001c7bc8:;
/* 001c7bc8: lw v0,0x28(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 001c7bcc: nop  */ 
/* 001c7bd0: nop  */ 
/* 001c7bd4: nop  */ 
/* 001c7bd8: nop  */ 
/* 001c7bdc: bnel v0,zero,0x001c7bc8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c7be0 */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));goto L_001c7bc8;}}
/* 001c7be4: lw a0,0x24(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000024)));
L_001c7be8:;
/* 001c7be8: nop  */ 
/* 001c7bec: nop  */ 
/* 001c7bf0: bnel a0,zero,0x001c7bb8 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001c7bf4 */ lw(2,ea(4,(int32_t)UINT32_C(0x0000001c)));goto L_001c7bb8;}}
L_001c7bf8:;
/* 001c7bf8: jr ra */ {uint64_t target=cpu(31);/* delay 001c7bfc */ checkReturn(target,incoming);return;}
}
static void body_001c7c00(void){
nocturneEffectAxisNoteEntry(0x001c7c00u);
uint64_t incoming=cpu(31);
/* 001c7c00: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c7c04: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
/* 001c7c08: jr ra */ {uint64_t target=cpu(31);/* delay 001c7c0c */ sb(ea(28,(int32_t)UINT32_C(0xffffb2ac)),(uint8_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001c7c10(void){
nocturneEffectAxisNoteEntry(0x001c7c10u);
uint64_t incoming=cpu(31);
/* 001c7c10: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c7c14: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c7c18: nor a0,zero,a0 */ set(4,~(cpu(0)|cpu(4)));
/* 001c7c1c: and a0,v0,a0 */ set(4,cpu(2)&cpu(4));
/* 001c7c20: jr ra */ {uint64_t target=cpu(31);/* delay 001c7c24 */ sb(ea(28,(int32_t)UINT32_C(0xffffb2ac)),(uint8_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001c8108(void){
nocturneEffectAxisNoteEntry(0x001c8108u);
uint64_t incoming=cpu(31);
/* 001c8108: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c810c: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 001c8110: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c8114: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c8118: j 0x001c8120 */ /* delay 001c811c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattlePanelRendererCall(UINT32_C(0x001c8120),UINT32_C(0x001c8118));return;
}
static void body_001c8120(void){
nocturneEffectAxisNoteEntry(0x001c8120u);
uint64_t incoming=cpu(31);
/* 001c8120: move a3,a0 */ set(7,cpu(4));
/* 001c8124: beq a3,zero,0x001c81ac */ {int taken=(cpu(7)==cpu(0));/* delay 001c8128 */ set(2,cpu(5));if(taken){goto L_001c81ac;}}
/* 001c812c: beq a1,zero,0x001c81ac */ {int taken=(cpu(5)==cpu(0));/* delay 001c8130 */ set(2,cpu(7));if(taken){goto L_001c81ac;}}
/* 001c8134: lw v1,0x2c(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x0000002c)));
/* 001c8138: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c813c: sw v1,0x28(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 001c8140: lw v0,0x2c(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000002c)));
/* 001c8144: sw a3,0x24(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(7));
/* 001c8148: lw v1,0x2c(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x0000002c)));
/* 001c814c: bne a2,a0,0x001c81a8 */ {int taken=(cpu(6)!=cpu(4));/* delay 001c8150 */ sw(ea(5,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(3));if(taken){goto L_001c81a8;}}
/* 001c8154: lw v0,0x1c(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 001c8158: beql v0,zero,0x001c8190 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c815c */ lw(2,ea(7,(int32_t)UINT32_C(0x0000000c)));goto L_001c8190;}}
/* 001c8160: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8164: li v0,0xd */ set(2,sx(UINT32_C(0x0000000d)));
/* 001c8168: bnel v1,v0,0x001c8190 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 001c816c */ lw(2,ea(7,(int32_t)UINT32_C(0x0000000c)));goto L_001c8190;}}
/* 001c8170: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 001c8174: lh a0,0x12(a3) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x00000012))));
/* 001c8178: sw v0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 001c817c: lw v1,0x8(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 001c8180: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001c8184: b 0x001c81a8 */ /* delay 001c8188 */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));goto L_001c81a8;
L_001c8190:;
/* 001c8190: lw v1,0x4(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 001c8194: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 001c8198: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c819c: sw v1,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001c81a0: lw v0,0x8(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 001c81a4: sw v0,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_001c81a8:;
/* 001c81a8: move v0,a1 */ set(2,cpu(5));
L_001c81ac:;
/* 001c81ac: jr ra */ {uint64_t target=cpu(31);/* delay 001c81b0 */ checkReturn(target,incoming);return;}
}
static void body_001c8230(void){
nocturneEffectAxisNoteEntry(0x001c8230u);
uint64_t incoming=cpu(31);
/* 001c8230: lw v1,0x1c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001c8234: beq v1,zero,0x001c825c */ {int taken=(cpu(3)==cpu(0));/* delay 001c8238 */ set(5,cpu(0));if(taken){goto L_001c825c;}}
/* 001c823c: lb a0,0x1(a0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000001))));
L_001c8240:;
/* 001c8240: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 001c8244: lw v1,0x28(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000028)));
/* 001c8248: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 001c824c: nop  */ 
/* 001c8250: nop  */ 
/* 001c8254: bne v1,zero,0x001c8240 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c8258 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));if(taken){goto L_001c8240;}}
L_001c825c:;
/* 001c825c: jr ra */ {uint64_t target=cpu(31);/* delay 001c8260 */ set(2,cpu(5));checkReturn(target,incoming);return;}
}
static void body_001c83b0(void){
nocturneEffectAxisNoteEntry(0x001c83b0u);
uint64_t incoming=cpu(31);
/* 001c83b0: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c83b4: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c83b8: slti v1,a0,0x2 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c83bc: beq v1,zero,0x001c83d8 */ {int taken=(cpu(3)==cpu(0));/* delay 001c83c0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));if(taken){goto L_001c83d8;}}
/* 001c83c4: bltzl a0,0x001c83dc */ {int taken=((int64_t)cpu(4)<0);if(taken){/* delay 001c83c8 */ set(2,sx((uint32_t)cpu(2)<<2));goto L_001c83dc;}}
/* 001c83cc: jr ra */ {uint64_t target=cpu(31);/* delay 001c83d0 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb2a0)));checkReturn(target,incoming);return;}
L_001c83d8:;
/* 001c83d8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
L_001c83dc:;
/* 001c83dc: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c83e0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c83e4: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c83e8: jr ra */ {uint64_t target=cpu(31);/* delay 001c83ec */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000010))));checkReturn(target,incoming);return;}
}
static void body_001c83f0(void){
nocturneEffectAxisNoteEntry(0x001c83f0u);
uint64_t incoming=cpu(31);
/* 001c83f0: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c83f4: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c83f8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c83fc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c8400: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c8404: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8408: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c840c: jr ra */ {uint64_t target=cpu(31);/* delay 001c8410 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000010))));checkReturn(target,incoming);return;}
}
static void body_001c8418(void){
nocturneEffectAxisNoteEntry(0x001c8418u);
uint64_t incoming=cpu(31);
/* 001c8418: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c841c: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c8420: slti v1,a0,0x2 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c8424: beq v1,zero,0x001c8440 */ {int taken=(cpu(3)==cpu(0));/* delay 001c8428 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));if(taken){goto L_001c8440;}}
/* 001c842c: bltzl a0,0x001c8444 */ {int taken=((int64_t)cpu(4)<0);if(taken){/* delay 001c8430 */ set(2,sx((uint32_t)cpu(2)<<2));goto L_001c8444;}}
/* 001c8434: jr ra */ {uint64_t target=cpu(31);/* delay 001c8438 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb2a0)));checkReturn(target,incoming);return;}
L_001c8440:;
/* 001c8440: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
L_001c8444:;
/* 001c8444: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c8448: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c844c: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c8450: jr ra */ {uint64_t target=cpu(31);/* delay 001c8454 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000012))));checkReturn(target,incoming);return;}
}
static void body_001c8458(void){
nocturneEffectAxisNoteEntry(0x001c8458u);
uint64_t incoming=cpu(31);
/* 001c8458: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c845c: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c8460: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c8464: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c8468: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c846c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8470: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c8474: jr ra */ {uint64_t target=cpu(31);/* delay 001c8478 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000012))));checkReturn(target,incoming);return;}
}
static void body_001c9d60(void){
nocturneEffectAxisNoteEntry(0x001c9d60u);
uint64_t incoming=cpu(31);
/* 001c9d60: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001c9d64: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c9d68: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9d6c: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c9d70: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9d74: addiu t1,a0,0x6650 */ set(9,sx((uint32_t)cpu(4)+UINT32_C(0x00006650)));
/* 001c9d78: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9d7c: move s2,a3 */ set(18,cpu(7));
/* 001c9d80: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c9d84: move s3,a2 */ set(19,cpu(6));
/* 001c9d88: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c9d8c: move s4,sp */ set(20,cpu(29));
/* 001c9d90: sd s8,0x48(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c9d94: move s8,sp */ set(30,cpu(29));
/* 001c9d98: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c9d9c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c9da0: sra s1,a1,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c9da4: move a3,zero */ set(7,cpu(0));
/* 001c9da8: lw t0,-0x5750(gp) */ lw(8,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9dac: move a2,zero */ set(6,cpu(0));
/* 001c9db0: addu v0,t0,t1 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(9)));
/* 001c9db4: lbu v1,0x4(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 001c9db8: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 001c9dbc: addiu v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 001c9dc0: andi v0,v0,0x3f0 */ set(2,cpu(2)&UINT32_C(0x000003f0));
/* 001c9dc4: subu sp,sp,v0 */ set(29,sx((uint32_t)cpu(29)-(uint32_t)cpu(2)));
/* 001c9dc8: beq v1,zero,0x001c9e44 */ {int taken=(cpu(3)==cpu(0));/* delay 001c9dcc */ set(16,cpu(29));if(taken){goto L_001c9e44;}}
/* 001c9dd0: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001c9dd4: move a1,sp */ set(5,cpu(29));
/* 001c9dd8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c9ddc: sll a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)<<2));
L_001c9de0:;
/* 001c9de0: addiu v0,t0,0x4 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 001c9de4: addu v1,a0,v0 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001c9de8: move v0,v1 */ set(2,cpu(3));
/* 001c9dec: lbu v0,0x6600(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x00006600))));
/* 001c9df0: bnel v0,zero,0x001c9e08 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c9df4 */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_001c9e08;}}
/* 001c9df8: lbu v0,0x6601(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00006601))));
/* 001c9dfc: b 0x001c9e20 */ /* delay 001c9e00 */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_001c9e20;
L_001c9e08:;
/* 001c9e08: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 001c9e0c: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c9e10: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9e14: addu v0,a0,v0 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001c9e18: lbu v1,0x6605(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00006605))));
/* 001c9e1c: sb v1,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
L_001c9e20:;
/* 001c9e20: lw t0,-0x5750(gp) */ lw(8,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9e24: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 001c9e28: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 001c9e2c: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c9e30: addu v1,t0,t1 */ set(3,sx((uint32_t)cpu(8)+(uint32_t)cpu(9)));
/* 001c9e34: lbu v0,0x4(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 001c9e38: slt v0,a3,v0 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(2));
/* 001c9e3c: bne v0,zero,0x001c9de0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c9e40 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));if(taken){goto L_001c9de0;}}
L_001c9e44:;
/* 001c9e44: addu v0,s0,a2 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));
/* 001c9e48: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c9e4c: jal 0x001c7c00 */ set(31,0x001c9e54u);/* delay 001c9e50 */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x001c7c00),UINT32_C(0x001c9e4c));
/* 001c9e54: sll a2,s2,0x18 */ set(6,sx((uint32_t)cpu(18)<<24));
/* 001c9e58: move a1,s1 */ set(5,cpu(17));
/* 001c9e5c: sra a2,a2,0x18 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c9e60: move t0,s3 */ set(8,cpu(19));
/* 001c9e64: move a3,zero */ set(7,cpu(0));
/* 001c9e68: jal 0x001c7828 */ set(31,0x001c9e70u);/* delay 001c9e6c */ set(4,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x001c7828),UINT32_C(0x001c9e68));
/* 001c9e70: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c9e74: jal 0x001c7c10 */ set(31,0x001c9e7cu);/* delay 001c9e78 */ set(16,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x001c7c10),UINT32_C(0x001c9e74));
/* 001c9e7c: move a0,s0 */ set(4,cpu(16));
/* 001c9e80: jal 0x001c7a88 */ set(31,0x001c9e88u);/* delay 001c9e84 */ set(5,sx(UINT32_C(0x00000004)));nocturneBattlePanelRendererCall(UINT32_C(0x001c7a88),UINT32_C(0x001c9e80));
/* 001c9e88: move sp,s4 */ set(29,cpu(20));
/* 001c9e8c: move v0,s0 */ set(2,cpu(16));
/* 001c9e90: move sp,s8 */ set(29,cpu(30));
/* 001c9e94: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9e98: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9e9c: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9ea0: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c9ea4: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c9ea8: ld s8,0x48(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c9eac: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c9eb0: jr ra */ {uint64_t target=cpu(31);/* delay 001c9eb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_001ca9c0(void){
nocturneEffectAxisNoteEntry(0x001ca9c0u);
uint64_t incoming=cpu(31);
/* 001ca9c0: jr ra */ {uint64_t target=cpu(31);/* delay 001ca9c4 */ set(2,cpu(4));checkReturn(target,incoming);return;}
}
static void body_001ca9c8(void){
nocturneEffectAxisNoteEntry(0x001ca9c8u);
uint64_t incoming=cpu(31);
/* 001ca9c8: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001ca9cc: lw a3,0x4(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001ca9d0: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001ca9d4: addu a2,a0,v0 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001ca9d8: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 001ca9dc: sw a2,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 001ca9e0: addu v1,v0,v1 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001ca9e4: addu v0,a0,v0 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001ca9e8: addu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 001ca9ec: sw v0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 001ca9f0: jr ra */ {uint64_t target=cpu(31);/* delay 001ca9f4 */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001caa18(void){
nocturneEffectAxisNoteEntry(0x001caa18u);
uint64_t incoming=cpu(31);
/* 001caa18: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001caa1c: sll a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)<<2));
/* 001caa20: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001caa24: move s0,a3 */ set(16,cpu(7));
/* 001caa28: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001caa2c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001caa30: move s3,a0 */ set(19,cpu(4));
/* 001caa34: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001caa38: move a0,a2 */ set(4,cpu(6));
/* 001caa3c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001caa40: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001caa44: lw s2,0x0(s0) */ lw(18,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001caa48: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 001caa4c: lwl v0,0x3(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000003)),1);
/* 001caa50: lwr v0,0x0(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000000)),0);
/* 001caa54: swl v0,0x3(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000003)),2,1);
/* 001caa58: swr v0,0x0(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000000)),2,0);
/* 001caa5c: lwl v0,0x7(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000007)),1);
/* 001caa60: lwr v0,0x4(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000004)),0);
/* 001caa64: swl v0,0x7(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000007)),2,1);
/* 001caa68: swr v0,0x4(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000004)),2,0);
/* 001caa6c: jal 0x001ca9c0 */ set(31,0x001caa74u);/* delay 001caa70 */ set(17,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x001ca9c0),UINT32_C(0x001caa6c));
/* 001caa74: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001caa78: lui a3,0x1 */ set(7,sx(UINT32_C(0x00010000)));
/* 001caa7c: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001caa80: addiu t1,s2,0x2 */ set(9,sx((uint32_t)cpu(18)+UINT32_C(0x00000002)));
/* 001caa84: srl v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)>>4));
/* 001caa88: lw a1,0x4(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 001caa8c: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 001caa90: andi a2,a0,0xf */ set(6,cpu(4)&UINT32_C(0x0000000f));
/* 001caa94: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001caa98: subu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));
/* 001caa9c: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001caaa0: move t0,v0 */ set(8,cpu(2));
/* 001caaa4: move a0,t1 */ set(4,cpu(9));
/* 001caaa8: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 001caaac: or v1,v1,a3 */ set(3,cpu(3)|cpu(7));
/* 001caab0: srav a2,v1,a2 */ set(6,sx((uint32_t)((int32_t)(uint32_t)cpu(3)>>((uint32_t)cpu(6)&31u))));
/* 001caab4: andi v1,a2,0x1 */ set(3,cpu(6)&UINT32_C(0x00000001));
L_001caab8:;
/* 001caab8: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 001caabc: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001caac0: lhu a0,0x0(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001caac4: sll v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)<<1));
/* 001caac8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001caacc: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 001caad0: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001caad4: addiu a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 001caad8: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 001caadc: bne v1,zero,0x001caaf8 */ {int taken=(cpu(3)!=cpu(0));/* delay 001caae0 */ set(6,sx((uint32_t)cpu(6)>>1));if(taken){goto L_001caaf8;}}
/* 001caae4: lbu v1,0x2(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000002))));
/* 001caae8: move a0,t1 */ set(4,cpu(9));
/* 001caaec: addu v0,s3,s1 */ set(2,sx((uint32_t)cpu(19)+(uint32_t)cpu(17)));
/* 001caaf0: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 001caaf4: sb v1,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
L_001caaf8:;
/* 001caaf8: bne a2,t2,0x001cab0c */ {int taken=(cpu(6)!=cpu(10));/* delay 001caafc */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));if(taken){goto L_001cab0c;}}
/* 001cab00: addiu t0,t0,0x2 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000002)));
/* 001cab04: lhu v0,0x0(t0) */ set(2,half(ea(8,(int32_t)UINT32_C(0x00000000))));
/* 001cab08: or a2,v0,a3 */ set(6,cpu(2)|cpu(7));
L_001cab0c:;
/* 001cab0c: bne a1,zero,0x001caab8 */ {int taken=(cpu(5)!=cpu(0));/* delay 001cab10 */ set(3,cpu(6)&UINT32_C(0x00000001));if(taken){goto L_001caab8;}}
/* 001cab14: move v0,s1 */ set(2,cpu(17));
/* 001cab18: sw s1,-0x22d0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdd30)),(uint32_t)cpu(17));
/* 001cab1c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cab20: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cab24: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cab28: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001cab2c: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001cab30: jr ra */ {uint64_t target=cpu(31);/* delay 001cab34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001cabd8(void){
nocturneEffectAxisNoteEntry(0x001cabd8u);
uint64_t incoming=cpu(31);
/* 001cabd8: lw a1,0x4(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001cabdc: lw v1,0x0(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001cabe0: beq v1,zero,0x001cabf8 */ {int taken=(cpu(3)==cpu(0));/* delay 001cabe4 */ set(2,cpu(0));if(taken){goto L_001cabf8;}}
/* 001cabe8: lw v1,0x4(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 001cabec: addiu v0,a1,0x8 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 001cabf0: sw v1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001cabf4: sw zero,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
L_001cabf8:;
/* 001cabf8: jr ra */ {uint64_t target=cpu(31);/* delay 001cabfc */ checkReturn(target,incoming);return;}
}
static void body_002acb90(void){
nocturneEffectAxisNoteEntry(0x002acb90u);
uint64_t incoming=cpu(31);
/* 002acb90: ori v0,zero,0xffff */ set(2,cpu(0)|UINT32_C(0x0000ffff));
/* 002acb94: sw zero,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 002acb98: sw v0,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002acb9c: sw zero,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002acba0: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002acba4: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002acba8: sw zero,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002acbac: sw zero,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002acbb0: jr ra */ {uint64_t target=cpu(31);/* delay 002acbb4 */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002acbb8(void){
nocturneEffectAxisNoteEntry(0x002acbb8u);
uint64_t incoming=cpu(31);
/* 002acbb8: lw a2,0x8(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002acbbc: bne a2,zero,0x002acbd0 */ {int taken=(cpu(6)!=cpu(0));/* delay 002acbc0 */ set(2,sx(UINT32_C(0x0fff0000)));if(taken){goto L_002acbd0;}}
/* 002acbc4: b 0x002acbe4 */ /* delay 002acbc8 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));goto L_002acbe4;
L_002acbd0:;
/* 002acbd0: li v1,0x20 */ set(3,sx(UINT32_C(0x00000020)));
/* 002acbd4: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002acbd8: sb v1,0x3(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(3));
/* 002acbdc: and v0,a1,v0 */ set(2,cpu(5)&cpu(2));
/* 002acbe0: sw v0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002acbe4:;
/* 002acbe4: jr ra */ {uint64_t target=cpu(31);/* delay 002acbe8 */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_002ad130(void){
nocturneEffectAxisNoteEntry(0x002ad130u);
uint64_t incoming=cpu(31);
/* 002ad130: addiu a3,a1,0x1 */ set(7,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002ad134: lui v0,0x5000 */ set(2,sx(UINT32_C(0x50000000)));
/* 002ad138: or v0,a3,v0 */ set(2,cpu(7)|cpu(2));
/* 002ad13c: lui a2,0x1000 */ set(6,sx(UINT32_C(0x10000000)));
/* 002ad140: lui v1,0x1000 */ set(3,sx(UINT32_C(0x10000000)));
/* 002ad144: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002ad148: ori v1,v1,0x8000 */ set(3,cpu(3)|UINT32_C(0x00008000));
/* 002ad14c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002ad150: or v1,a1,v1 */ set(3,cpu(5)|cpu(3));
/* 002ad154: li a1,0xe */ set(5,sx(UINT32_C(0x0000000e)));
/* 002ad158: or v0,v0,a2 */ set(2,cpu(2)|cpu(6));
/* 002ad15c: sd a1,0x18(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002ad160: sd v0,0x8(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002ad164: sd v1,0x10(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002ad168: jr ra */ {uint64_t target=cpu(31);/* delay 002ad16c */ save(7,ea(4,(int32_t)UINT32_C(0x00000000)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelRendererExisting5(uint32_t entry){switch(entry){case UINT32_C(0x00100418):(void)body_00100418();return 1u;case UINT32_C(0x001c6018):(void)body_001c6018();return 1u;case UINT32_C(0x001c6128):(void)body_001c6128();return 1u;case UINT32_C(0x001c6ff8):(void)body_001c6ff8();return 1u;case UINT32_C(0x001c7080):(void)body_001c7080();return 1u;case UINT32_C(0x001c7088):(void)body_001c7088();return 1u;case UINT32_C(0x001c7408):(void)body_001c7408();return 1u;case UINT32_C(0x001c74e8):(void)body_001c74e8();return 1u;case UINT32_C(0x001c7568):(void)body_001c7568();return 1u;case UINT32_C(0x001c7660):(void)body_001c7660();return 1u;case UINT32_C(0x001c76a8):(void)body_001c76a8();return 1u;case UINT32_C(0x001c76e0):(void)body_001c76e0();return 1u;case UINT32_C(0x001c7828):(void)body_001c7828();return 1u;case UINT32_C(0x001c7890):(void)body_001c7890();return 1u;case UINT32_C(0x001c7a88):(void)body_001c7a88();return 1u;case UINT32_C(0x001c7b30):(void)body_001c7b30();return 1u;case UINT32_C(0x001c7b40):(void)body_001c7b40();return 1u;case UINT32_C(0x001c7ba8):(void)body_001c7ba8();return 1u;case UINT32_C(0x001c7c00):(void)body_001c7c00();return 1u;case UINT32_C(0x001c7c10):(void)body_001c7c10();return 1u;case UINT32_C(0x001c8108):(void)body_001c8108();return 1u;case UINT32_C(0x001c8120):(void)body_001c8120();return 1u;case UINT32_C(0x001c8230):(void)body_001c8230();return 1u;case UINT32_C(0x001c83b0):(void)body_001c83b0();return 1u;case UINT32_C(0x001c83f0):(void)body_001c83f0();return 1u;case UINT32_C(0x001c8418):(void)body_001c8418();return 1u;case UINT32_C(0x001c8458):(void)body_001c8458();return 1u;case UINT32_C(0x001c9d60):(void)body_001c9d60();return 1u;case UINT32_C(0x001ca9c0):(void)body_001ca9c0();return 1u;case UINT32_C(0x001ca9c8):(void)body_001ca9c8();return 1u;case UINT32_C(0x001caa18):(void)body_001caa18();return 1u;case UINT32_C(0x001cabd8):(void)body_001cabd8();return 1u;case UINT32_C(0x002acb90):(void)body_002acb90();return 1u;case UINT32_C(0x002acbb8):(void)body_002acbb8();return 1u;case UINT32_C(0x002ad130):(void)body_002ad130();return 1u;default:return 0u;}}
