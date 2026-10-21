/* Complete4 native model attachment/name/scale bodies; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "object_attachment.h"
#include "ee_vu_rotation.h"
#include "effect_ftoi0.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveObjectAttachmentAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneObjectAttachmentCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneObjectAttachmentCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneObjectAttachmentCpuWrite(r,q);if(r==29u)nocturneObjectAttachmentSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);























static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}
static void loadVu(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneObjectAttachmentVuWrite(d,q);}
static void storeVu(unsigned s,uint32_t a){uint32_t q[4];nocturneObjectAttachmentVuRead(s,q);memcpy(at(a&~15u),q,16);}
static void attachmentMoveW(unsigned d,unsigned s){uint32_t q[4],v[4];nocturneObjectAttachmentVuRead(d,q);nocturneObjectAttachmentVuRead(s,v);q[3]=v[3];nocturneObjectAttachmentVuWrite(d,q);}

static void body_00110408(void);
static void body_001dd7a8(void);
static void body_002b2688(void);
static void body_002b2748(void);
static void body_00110408(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00110408: addiu sp,sp,-0x1490 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffeb70)));
/* 0011040c: sd s3,0x1458(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00001458)));
/* 00110410: sw a0,0x1430(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00001430)),(uint32_t)cpu(4));
/* 00110414: sd s0,0x1440(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00001440)));
/* 00110418: sd s1,0x1448(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00001448)));
/* 0011041c: sd s2,0x1450(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00001450)));
/* 00110420: sd s4,0x1460(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00001460)));
/* 00110424: sd s5,0x1468(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00001468)));
/* 00110428: sd s6,0x1470(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00001470)));
/* 0011042c: sd s7,0x1478(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00001478)));
/* 00110430: sd s8,0x1480(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00001480)));
/* 00110434: sd ra,0x1488(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00001488)));
/* 00110438: sw a1,0x1434(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00001434)),(uint32_t)cpu(5));
/* 0011043c: jal 0x001122a0 */ set(31,UINT64_C(0x00110444));/* delay 00110440 */ sw(ea(29,(int32_t)UINT32_C(0x00001438)),(uint32_t)cpu(6));nocturneObjectAttachmentCall(UINT32_C(0x001122a0),UINT32_C(0x0011043c));
/* 00110444: move s3,v0 */ set(19,cpu(2));
/* 00110448: lw a0,0xc(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0011044c: beql a0,zero,0x00110460 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00110450 */ lw(4,ea(29,(int32_t)UINT32_C(0x00001434)));goto L_00110460;}}
/* 00110454: jal 0x001dd220 */ set(31,UINT64_C(0x0011045c));/* delay 00110458 */ nocturneObjectAttachmentCall(UINT32_C(0x001dd220),UINT32_C(0x00110454));
/* 0011045c: lw a0,0x1434(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00001434)));
L_00110460:;
/* 00110460: jal 0x001dd0d0 */ set(31,UINT64_C(0x00110468));/* delay 00110464 */ lw(5,ea(29,(int32_t)UINT32_C(0x00001438)));nocturneObjectAttachmentCall(UINT32_C(0x001dd0d0),UINT32_C(0x00110460));
/* 00110468: move s4,v0 */ set(20,cpu(2));
/* 0011046c: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 00110470: addiu v1,v0,-0x7b0 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xfffff850)));
/* 00110474: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 00110478: andi v0,v1,0x7 */ set(2,cpu(3)&UINT32_C(0x00000007));
/* 0011047c: beq v0,zero,0x001104e8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110480 */ set(5,cpu(4));if(taken){goto L_001104e8;}}
/* 00110484: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_00110488:;
/* 00110488: ldl a2,0x7(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 0011048c: ldr a2,0x0(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110490: ldl a3,0xf(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110494: ldr a3,0x8(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000008)),0u);
/* 00110498: ldl t0,0x17(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000017)),1u);
/* 0011049c: ldr t0,0x10(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000010)),0u);
/* 001104a0: ldl t1,0x1f(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 001104a4: ldr t1,0x18(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000018)),0u);
/* 001104a8: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 001104ac: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 001104b0: sdl a3,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),7u,1u);
/* 001104b4: sdr a3,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),7u,0u);
/* 001104b8: sdl t0,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),8u,1u);
/* 001104bc: sdr t0,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),8u,0u);
/* 001104c0: sdl t1,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),9u,1u);
/* 001104c4: sdr t1,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),9u,0u);
/* 001104c8: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001104cc: nop  */ 
/* 001104d0: nop  */ 
/* 001104d4: bne v1,v0,0x00110488 */ {int taken=(cpu(3)!=cpu(2));/* delay 001104d8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110488;}}
/* 001104dc: b 0x00110524 */ /* delay 001104e0 */ set(2,sx(UINT32_C(0x00530000)));goto L_00110524;
L_001104e8:;
/* 001104e8: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_001104ec:;
/* 001104ec: ld a0,0x0(v1) */ restore(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001104f0: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001104f4: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 001104f8: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 001104fc: sd a0,0x0(a1) */ save(4,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110500: sd a2,0x8(a1) */ save(6,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110504: sd a3,0x10(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110508: sd t0,0x18(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 0011050c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110510: nop  */ 
/* 00110514: nop  */ 
/* 00110518: bne v1,v0,0x001104ec */ {int taken=(cpu(3)!=cpu(2));/* delay 0011051c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_001104ec;}}
/* 00110520: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_00110524:;
/* 00110524: addiu t0,sp,0x180 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000180)));
/* 00110528: addiu a0,v0,-0x648 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xfffff9b8)));
/* 0011052c: ldl t1,0x7(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110530: ldr t1,0x0(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110534: sdl t1,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),9u,1u);
/* 00110538: sdr t1,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),9u,0u);
/* 0011053c: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 00110540: beq v0,zero,0x001105a8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110544 */ set(5,cpu(8));if(taken){goto L_001105a8;}}
/* 00110548: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_0011054c:;
/* 0011054c: ldl t1,0x7(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110550: ldr t1,0x0(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110554: ldl v1,0xf(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110558: ldr v1,0x8(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000008)),0u);
/* 0011055c: ldl a2,0x17(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110560: ldr a2,0x10(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110564: ldl a3,0x1f(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110568: ldr a3,0x18(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x00000018)),0u);
/* 0011056c: sdl t1,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),9u,1u);
/* 00110570: sdr t1,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),9u,0u);
/* 00110574: sdl v1,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),3u,1u);
/* 00110578: sdr v1,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),3u,0u);
/* 0011057c: sdl a2,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),6u,1u);
/* 00110580: sdr a2,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),6u,0u);
/* 00110584: sdl a3,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),7u,1u);
/* 00110588: sdr a3,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),7u,0u);
/* 0011058c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110590: nop  */ 
/* 00110594: nop  */ 
/* 00110598: bne a0,v0,0x0011054c */ {int taken=(cpu(4)!=cpu(2));/* delay 0011059c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011054c;}}
/* 001105a0: b 0x001105e4 */ /* delay 001105a4 */ set(2,sx(UINT32_C(0x00530000)));goto L_001105e4;
L_001105a8:;
/* 001105a8: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_001105ac:;
/* 001105ac: ld t0,0x0(a0) */ restore(8,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001105b0: ld t1,0x8(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 001105b4: ld v1,0x10(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 001105b8: ld a2,0x18(a0) */ restore(6,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001105bc: sd t0,0x0(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001105c0: sd t1,0x8(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 001105c4: sd v1,0x10(a1) */ save(3,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 001105c8: sd a2,0x18(a1) */ save(6,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 001105cc: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 001105d0: nop  */ 
/* 001105d4: nop  */ 
/* 001105d8: bne a0,v0,0x001105ac */ {int taken=(cpu(4)!=cpu(2));/* delay 001105dc */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_001105ac;}}
/* 001105e0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_001105e4:;
/* 001105e4: addiu s2,sp,0x2f0 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x000002f0)));
/* 001105e8: addiu v1,v0,-0x4e0 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xfffffb20)));
/* 001105ec: ldl a3,0x7(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 001105f0: ldr a3,0x0(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 001105f4: sdl a3,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),7u,1u);
/* 001105f8: sdr a3,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),7u,0u);
/* 001105fc: andi v0,v1,0x7 */ set(2,cpu(3)&UINT32_C(0x00000007));
/* 00110600: beq v0,zero,0x00110668 */ {int taken=(cpu(2)==cpu(0));/* delay 00110604 */ set(5,cpu(18));if(taken){goto L_00110668;}}
/* 00110608: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_0011060c:;
/* 0011060c: ldl a0,0x7(v1) */ loadPartial(4u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110610: ldr a0,0x0(v1) */ loadPartial(4u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110614: ldl a2,0xf(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110618: ldr a2,0x8(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000008)),0u);
/* 0011061c: ldl a3,0x17(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110620: ldr a3,0x10(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110624: ldl t0,0x1f(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110628: ldr t0,0x18(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000018)),0u);
/* 0011062c: sdl a0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),4u,1u);
/* 00110630: sdr a0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),4u,0u);
/* 00110634: sdl a2,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),6u,1u);
/* 00110638: sdr a2,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),6u,0u);
/* 0011063c: sdl a3,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),7u,1u);
/* 00110640: sdr a3,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),7u,0u);
/* 00110644: sdl t0,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),8u,1u);
/* 00110648: sdr t0,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),8u,0u);
/* 0011064c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110650: nop  */ 
/* 00110654: nop  */ 
/* 00110658: bne v1,v0,0x0011060c */ {int taken=(cpu(3)!=cpu(2));/* delay 0011065c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011060c;}}
/* 00110660: b 0x001106a4 */ /* delay 00110664 */ set(2,sx(UINT32_C(0x00530000)));goto L_001106a4;
L_00110668:;
/* 00110668: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_0011066c:;
/* 0011066c: ld t1,0x0(v1) */ restore(9,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00110670: ld a0,0x8(v1) */ restore(4,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00110674: ld a2,0x10(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 00110678: ld a3,0x18(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0011067c: sd t1,0x0(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110680: sd a0,0x8(a1) */ save(4,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110684: sd a2,0x10(a1) */ save(6,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110688: sd a3,0x18(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 0011068c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110690: nop  */ 
/* 00110694: nop  */ 
/* 00110698: bne v1,v0,0x0011066c */ {int taken=(cpu(3)!=cpu(2));/* delay 0011069c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011066c;}}
/* 001106a0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_001106a4:;
/* 001106a4: addiu a3,sp,0x460 */ set(7,sx((uint32_t)cpu(29)+UINT32_C(0x00000460)));
/* 001106a8: addiu a0,v0,-0x378 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xfffffc88)));
/* 001106ac: ldl t0,0x7(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 001106b0: ldr t0,0x0(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 001106b4: sdl t0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),8u,1u);
/* 001106b8: sdr t0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),8u,0u);
/* 001106bc: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 001106c0: beq v0,zero,0x00110728 */ {int taken=(cpu(2)==cpu(0));/* delay 001106c4 */ set(5,cpu(7));if(taken){goto L_00110728;}}
/* 001106c8: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_001106cc:;
/* 001106cc: ldl t0,0x7(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 001106d0: ldr t0,0x0(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 001106d4: ldl t1,0xf(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 001106d8: ldr t1,0x8(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000008)),0u);
/* 001106dc: ldl v1,0x17(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000017)),1u);
/* 001106e0: ldr v1,0x10(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000010)),0u);
/* 001106e4: ldl a2,0x1f(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 001106e8: ldr a2,0x18(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000018)),0u);
/* 001106ec: sdl t0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),8u,1u);
/* 001106f0: sdr t0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),8u,0u);
/* 001106f4: sdl t1,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),9u,1u);
/* 001106f8: sdr t1,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),9u,0u);
/* 001106fc: sdl v1,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),3u,1u);
/* 00110700: sdr v1,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),3u,0u);
/* 00110704: sdl a2,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),6u,1u);
/* 00110708: sdr a2,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),6u,0u);
/* 0011070c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110710: nop  */ 
/* 00110714: nop  */ 
/* 00110718: bne a0,v0,0x001106cc */ {int taken=(cpu(4)!=cpu(2));/* delay 0011071c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_001106cc;}}
/* 00110720: b 0x00110760 */ /* delay 00110724 */ goto L_00110760;
L_00110728:;
/* 00110728: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_0011072c:;
/* 0011072c: ld a3,0x0(a0) */ restore(7,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00110730: ld t0,0x8(a0) */ restore(8,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00110734: ld t1,0x10(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00110738: ld v1,0x18(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0011073c: sd a3,0x0(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110740: sd t0,0x8(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110744: sd t1,0x10(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110748: sd v1,0x18(a1) */ save(3,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 0011074c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110750: nop  */ 
/* 00110754: nop  */ 
/* 00110758: bne a0,v0,0x0011072c */ {int taken=(cpu(4)!=cpu(2));/* delay 0011075c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011072c;}}
L_00110760:;
/* 00110760: ldl a2,0x7(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110764: ldr a2,0x0(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110768: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 0011076c: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 00110770: addiu v1,v0,-0x210 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xfffffdf0)));
/* 00110774: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 00110778: addiu a0,sp,0x5d0 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x000005d0)));
/* 0011077c: andi v0,v1,0x7 */ set(2,cpu(3)&UINT32_C(0x00000007));
/* 00110780: beq v0,zero,0x001107e8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110784 */ set(5,cpu(4));if(taken){goto L_001107e8;}}
/* 00110788: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_0011078c:;
/* 0011078c: ldl a2,0x7(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110790: ldr a2,0x0(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110794: ldl a3,0xf(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110798: ldr a3,0x8(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000008)),0u);
/* 0011079c: ldl t0,0x17(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000017)),1u);
/* 001107a0: ldr t0,0x10(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000010)),0u);
/* 001107a4: ldl t1,0x1f(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 001107a8: ldr t1,0x18(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000018)),0u);
/* 001107ac: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 001107b0: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 001107b4: sdl a3,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),7u,1u);
/* 001107b8: sdr a3,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),7u,0u);
/* 001107bc: sdl t0,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),8u,1u);
/* 001107c0: sdr t0,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),8u,0u);
/* 001107c4: sdl t1,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),9u,1u);
/* 001107c8: sdr t1,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),9u,0u);
/* 001107cc: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001107d0: nop  */ 
/* 001107d4: nop  */ 
/* 001107d8: bne v1,v0,0x0011078c */ {int taken=(cpu(3)!=cpu(2));/* delay 001107dc */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011078c;}}
/* 001107e0: b 0x00110824 */ /* delay 001107e4 */ set(2,sx(UINT32_C(0x00530000)));goto L_00110824;
L_001107e8:;
/* 001107e8: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_001107ec:;
/* 001107ec: ld a0,0x0(v1) */ restore(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001107f0: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001107f4: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 001107f8: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 001107fc: sd a0,0x0(a1) */ save(4,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110800: sd a2,0x8(a1) */ save(6,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110804: sd a3,0x10(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110808: sd t0,0x18(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 0011080c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110810: nop  */ 
/* 00110814: nop  */ 
/* 00110818: bne v1,v0,0x001107ec */ {int taken=(cpu(3)!=cpu(2));/* delay 0011081c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_001107ec;}}
/* 00110820: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_00110824:;
/* 00110824: addiu s7,sp,0x740 */ set(23,sx((uint32_t)cpu(29)+UINT32_C(0x00000740)));
/* 00110828: addiu a0,v0,-0xa8 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xffffff58)));
/* 0011082c: ldl t1,0x7(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110830: ldr t1,0x0(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110834: sdl t1,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),9u,1u);
/* 00110838: sdr t1,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),9u,0u);
/* 0011083c: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 00110840: beq v0,zero,0x001108a8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110844 */ set(5,cpu(23));if(taken){goto L_001108a8;}}
/* 00110848: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_0011084c:;
/* 0011084c: ldl t0,0x7(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110850: ldr t0,0x0(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110854: ldl t1,0xf(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110858: ldr t1,0x8(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000008)),0u);
/* 0011085c: ldl v1,0x17(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110860: ldr v1,0x10(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110864: ldl a2,0x1f(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110868: ldr a2,0x18(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000018)),0u);
/* 0011086c: sdl t0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),8u,1u);
/* 00110870: sdr t0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),8u,0u);
/* 00110874: sdl t1,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),9u,1u);
/* 00110878: sdr t1,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),9u,0u);
/* 0011087c: sdl v1,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),3u,1u);
/* 00110880: sdr v1,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),3u,0u);
/* 00110884: sdl a2,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),6u,1u);
/* 00110888: sdr a2,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),6u,0u);
/* 0011088c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110890: nop  */ 
/* 00110894: nop  */ 
/* 00110898: bne a0,v0,0x0011084c */ {int taken=(cpu(4)!=cpu(2));/* delay 0011089c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011084c;}}
/* 001108a0: b 0x001108e4 */ /* delay 001108a4 */ set(2,sx(UINT32_C(0x00530000)));goto L_001108e4;
L_001108a8:;
/* 001108a8: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_001108ac:;
/* 001108ac: ld a3,0x0(a0) */ restore(7,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001108b0: ld t0,0x8(a0) */ restore(8,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 001108b4: ld t1,0x10(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 001108b8: ld v1,0x18(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001108bc: sd a3,0x0(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001108c0: sd t0,0x8(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 001108c4: sd t1,0x10(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 001108c8: sd v1,0x18(a1) */ save(3,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 001108cc: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 001108d0: nop  */ 
/* 001108d4: nop  */ 
/* 001108d8: bne a0,v0,0x001108ac */ {int taken=(cpu(4)!=cpu(2));/* delay 001108dc */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_001108ac;}}
/* 001108e0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_001108e4:;
/* 001108e4: ldl a2,0x7(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 001108e8: ldr a2,0x0(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 001108ec: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 001108f0: addiu v1,v0,0xc0 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x000000c0)));
/* 001108f4: addiu s8,sp,0x8b0 */ set(30,sx((uint32_t)cpu(29)+UINT32_C(0x000008b0)));
/* 001108f8: andi v0,v1,0x7 */ set(2,cpu(3)&UINT32_C(0x00000007));
/* 001108fc: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 00110900: beq v0,zero,0x00110968 */ {int taken=(cpu(2)==cpu(0));/* delay 00110904 */ set(5,cpu(30));if(taken){goto L_00110968;}}
/* 00110908: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_0011090c:;
/* 0011090c: ldl a0,0x7(v1) */ loadPartial(4u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110910: ldr a0,0x0(v1) */ loadPartial(4u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110914: ldl a2,0xf(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110918: ldr a2,0x8(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000008)),0u);
/* 0011091c: ldl a3,0x17(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110920: ldr a3,0x10(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110924: ldl t0,0x1f(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110928: ldr t0,0x18(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000018)),0u);
/* 0011092c: sdl a0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),4u,1u);
/* 00110930: sdr a0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),4u,0u);
/* 00110934: sdl a2,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),6u,1u);
/* 00110938: sdr a2,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),6u,0u);
/* 0011093c: sdl a3,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),7u,1u);
/* 00110940: sdr a3,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),7u,0u);
/* 00110944: sdl t0,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),8u,1u);
/* 00110948: sdr t0,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),8u,0u);
/* 0011094c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110950: nop  */ 
/* 00110954: nop  */ 
/* 00110958: bne v1,v0,0x0011090c */ {int taken=(cpu(3)!=cpu(2));/* delay 0011095c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011090c;}}
/* 00110960: b 0x001109a4 */ /* delay 00110964 */ set(2,sx(UINT32_C(0x00530000)));goto L_001109a4;
L_00110968:;
/* 00110968: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_0011096c:;
/* 0011096c: ld t1,0x0(v1) */ restore(9,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00110970: ld a0,0x8(v1) */ restore(4,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00110974: ld a2,0x10(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 00110978: ld a3,0x18(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0011097c: sd t1,0x0(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110980: sd a0,0x8(a1) */ save(4,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110984: sd a2,0x10(a1) */ save(6,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110988: sd a3,0x18(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 0011098c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110990: nop  */ 
/* 00110994: nop  */ 
/* 00110998: bne v1,v0,0x0011096c */ {int taken=(cpu(3)!=cpu(2));/* delay 0011099c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_0011096c;}}
/* 001109a0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_001109a4:;
/* 001109a4: addiu a3,sp,0xa20 */ set(7,sx((uint32_t)cpu(29)+UINT32_C(0x00000a20)));
/* 001109a8: addiu a0,v0,0x228 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000228)));
/* 001109ac: ldl t0,0x7(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 001109b0: ldr t0,0x0(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 001109b4: sdl t0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),8u,1u);
/* 001109b8: sdr t0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),8u,0u);
/* 001109bc: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 001109c0: beq v0,zero,0x00110a28 */ {int taken=(cpu(2)==cpu(0));/* delay 001109c4 */ set(5,cpu(7));if(taken){goto L_00110a28;}}
/* 001109c8: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_001109cc:;
/* 001109cc: ldl t0,0x7(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 001109d0: ldr t0,0x0(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 001109d4: ldl t1,0xf(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 001109d8: ldr t1,0x8(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000008)),0u);
/* 001109dc: ldl v1,0x17(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000017)),1u);
/* 001109e0: ldr v1,0x10(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000010)),0u);
/* 001109e4: ldl a2,0x1f(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 001109e8: ldr a2,0x18(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000018)),0u);
/* 001109ec: sdl t0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),8u,1u);
/* 001109f0: sdr t0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),8u,0u);
/* 001109f4: sdl t1,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),9u,1u);
/* 001109f8: sdr t1,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),9u,0u);
/* 001109fc: sdl v1,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),3u,1u);
/* 00110a00: sdr v1,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),3u,0u);
/* 00110a04: sdl a2,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),6u,1u);
/* 00110a08: sdr a2,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),6u,0u);
/* 00110a0c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110a10: nop  */ 
/* 00110a14: nop  */ 
/* 00110a18: bne a0,v0,0x001109cc */ {int taken=(cpu(4)!=cpu(2));/* delay 00110a1c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_001109cc;}}
/* 00110a20: b 0x00110a60 */ /* delay 00110a24 */ goto L_00110a60;
L_00110a28:;
/* 00110a28: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_00110a2c:;
/* 00110a2c: ld a3,0x0(a0) */ restore(7,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00110a30: ld t0,0x8(a0) */ restore(8,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00110a34: ld t1,0x10(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00110a38: ld v1,0x18(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 00110a3c: sd a3,0x0(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110a40: sd t0,0x8(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110a44: sd t1,0x10(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110a48: sd v1,0x18(a1) */ save(3,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 00110a4c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110a50: nop  */ 
/* 00110a54: nop  */ 
/* 00110a58: bne a0,v0,0x00110a2c */ {int taken=(cpu(4)!=cpu(2));/* delay 00110a5c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110a2c;}}
L_00110a60:;
/* 00110a60: ldl a2,0x7(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110a64: ldr a2,0x0(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110a68: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 00110a6c: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 00110a70: addiu v1,v0,0x390 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000390)));
/* 00110a74: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 00110a78: addiu a0,sp,0xb90 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000b90)));
/* 00110a7c: andi v0,v1,0x7 */ set(2,cpu(3)&UINT32_C(0x00000007));
/* 00110a80: beq v0,zero,0x00110ae8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110a84 */ set(5,cpu(4));if(taken){goto L_00110ae8;}}
/* 00110a88: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_00110a8c:;
/* 00110a8c: ldl a2,0x7(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110a90: ldr a2,0x0(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110a94: ldl a3,0xf(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110a98: ldr a3,0x8(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000008)),0u);
/* 00110a9c: ldl t0,0x17(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110aa0: ldr t0,0x10(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110aa4: ldl t1,0x1f(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110aa8: ldr t1,0x18(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000018)),0u);
/* 00110aac: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 00110ab0: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 00110ab4: sdl a3,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),7u,1u);
/* 00110ab8: sdr a3,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),7u,0u);
/* 00110abc: sdl t0,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),8u,1u);
/* 00110ac0: sdr t0,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),8u,0u);
/* 00110ac4: sdl t1,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),9u,1u);
/* 00110ac8: sdr t1,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),9u,0u);
/* 00110acc: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110ad0: nop  */ 
/* 00110ad4: nop  */ 
/* 00110ad8: bne v1,v0,0x00110a8c */ {int taken=(cpu(3)!=cpu(2));/* delay 00110adc */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110a8c;}}
/* 00110ae0: b 0x00110b24 */ /* delay 00110ae4 */ set(2,sx(UINT32_C(0x00530000)));goto L_00110b24;
L_00110ae8:;
/* 00110ae8: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_00110aec:;
/* 00110aec: ld a0,0x0(v1) */ restore(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00110af0: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00110af4: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 00110af8: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 00110afc: sd a0,0x0(a1) */ save(4,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110b00: sd a2,0x8(a1) */ save(6,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110b04: sd a3,0x10(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110b08: sd t0,0x18(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 00110b0c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110b10: nop  */ 
/* 00110b14: nop  */ 
/* 00110b18: bne v1,v0,0x00110aec */ {int taken=(cpu(3)!=cpu(2));/* delay 00110b1c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110aec;}}
/* 00110b20: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_00110b24:;
/* 00110b24: addiu s5,sp,0xd00 */ set(21,sx((uint32_t)cpu(29)+UINT32_C(0x00000d00)));
/* 00110b28: addiu a0,v0,0x4f8 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x000004f8)));
/* 00110b2c: ldl t1,0x7(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110b30: ldr t1,0x0(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110b34: sdl t1,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),9u,1u);
/* 00110b38: sdr t1,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),9u,0u);
/* 00110b3c: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 00110b40: beq v0,zero,0x00110ba8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110b44 */ set(5,cpu(21));if(taken){goto L_00110ba8;}}
/* 00110b48: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_00110b4c:;
/* 00110b4c: ldl t0,0x7(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110b50: ldr t0,0x0(a0) */ loadPartial(8u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110b54: ldl t1,0xf(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110b58: ldr t1,0x8(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000008)),0u);
/* 00110b5c: ldl v1,0x17(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110b60: ldr v1,0x10(a0) */ loadPartial(3u,ea(4u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110b64: ldl a2,0x1f(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110b68: ldr a2,0x18(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000018)),0u);
/* 00110b6c: sdl t0,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),8u,1u);
/* 00110b70: sdr t0,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),8u,0u);
/* 00110b74: sdl t1,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),9u,1u);
/* 00110b78: sdr t1,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),9u,0u);
/* 00110b7c: sdl v1,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),3u,1u);
/* 00110b80: sdr v1,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),3u,0u);
/* 00110b84: sdl a2,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),6u,1u);
/* 00110b88: sdr a2,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),6u,0u);
/* 00110b8c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110b90: nop  */ 
/* 00110b94: nop  */ 
/* 00110b98: bne a0,v0,0x00110b4c */ {int taken=(cpu(4)!=cpu(2));/* delay 00110b9c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110b4c;}}
/* 00110ba0: b 0x00110be0 */ /* delay 00110ba4 */ goto L_00110be0;
L_00110ba8:;
/* 00110ba8: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_00110bac:;
/* 00110bac: ld a3,0x0(a0) */ restore(7,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00110bb0: ld t0,0x8(a0) */ restore(8,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00110bb4: ld t1,0x10(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00110bb8: ld v1,0x18(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 00110bbc: sd a3,0x0(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110bc0: sd t0,0x8(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110bc4: sd t1,0x10(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110bc8: sd v1,0x18(a1) */ save(3,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 00110bcc: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110bd0: nop  */ 
/* 00110bd4: nop  */ 
/* 00110bd8: bne a0,v0,0x00110bac */ {int taken=(cpu(4)!=cpu(2));/* delay 00110bdc */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110bac;}}
L_00110be0:;
/* 00110be0: ldl a2,0x7(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110be4: ldr a2,0x0(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110be8: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 00110bec: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 00110bf0: addiu v1,v0,0x660 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000660)));
/* 00110bf4: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 00110bf8: addiu a0,sp,0xe70 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000e70)));
/* 00110bfc: andi v0,v1,0x7 */ set(2,cpu(3)&UINT32_C(0x00000007));
/* 00110c00: beq v0,zero,0x00110c68 */ {int taken=(cpu(2)==cpu(0));/* delay 00110c04 */ set(5,cpu(4));if(taken){goto L_00110c68;}}
/* 00110c08: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_00110c0c:;
/* 00110c0c: ldl a2,0x7(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110c10: ldr a2,0x0(v1) */ loadPartial(6u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110c14: ldl a3,0xf(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110c18: ldr a3,0x8(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000008)),0u);
/* 00110c1c: ldl t0,0x17(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110c20: ldr t0,0x10(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110c24: ldl t1,0x1f(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110c28: ldr t1,0x18(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000018)),0u);
/* 00110c2c: sdl a2,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),6u,1u);
/* 00110c30: sdr a2,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),6u,0u);
/* 00110c34: sdl a3,0xf(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000000f)),7u,1u);
/* 00110c38: sdr a3,0x8(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000008)),7u,0u);
/* 00110c3c: sdl t0,0x17(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000017)),8u,1u);
/* 00110c40: sdr t0,0x10(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000010)),8u,0u);
/* 00110c44: sdl t1,0x1f(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x0000001f)),9u,1u);
/* 00110c48: sdr t1,0x18(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000018)),9u,0u);
/* 00110c4c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110c50: nop  */ 
/* 00110c54: nop  */ 
/* 00110c58: bne v1,v0,0x00110c0c */ {int taken=(cpu(3)!=cpu(2));/* delay 00110c5c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110c0c;}}
/* 00110c60: b 0x00110ca4 */ /* delay 00110c64 */ set(2,sx(UINT32_C(0x00530000)));goto L_00110ca4;
L_00110c68:;
/* 00110c68: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_00110c6c:;
/* 00110c6c: ld a0,0x0(v1) */ restore(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00110c70: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00110c74: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 00110c78: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 00110c7c: sd a0,0x0(a1) */ save(4,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110c80: sd a2,0x8(a1) */ save(6,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110c84: sd a3,0x10(a1) */ save(7,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110c88: sd t0,0x18(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 00110c8c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110c90: nop  */ 
/* 00110c94: nop  */ 
/* 00110c98: bne v1,v0,0x00110c6c */ {int taken=(cpu(3)!=cpu(2));/* delay 00110c9c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));if(taken){goto L_00110c6c;}}
/* 00110ca0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_00110ca4:;
/* 00110ca4: addiu t0,sp,0xfe0 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000fe0)));
/* 00110ca8: addiu a0,v0,0x7c8 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x000007c8)));
/* 00110cac: ldl t1,0x7(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110cb0: ldr t1,0x0(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110cb4: sdl t1,0x7(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000007)),9u,1u);
/* 00110cb8: sdr t1,0x0(a1) */ storePartial(ea(5u,(int32_t)UINT32_C(0x00000000)),9u,0u);
/* 00110cbc: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 00110cc0: beq v0,zero,0x00110d28 */ {int taken=(cpu(2)==cpu(0));/* delay 00110cc4 */ set(3,cpu(8));if(taken){goto L_00110d28;}}
/* 00110cc8: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_00110ccc:;
/* 00110ccc: ldl t1,0x7(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110cd0: ldr t1,0x0(a0) */ loadPartial(9u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110cd4: ldl a1,0xf(a0) */ loadPartial(5u,ea(4u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110cd8: ldr a1,0x8(a0) */ loadPartial(5u,ea(4u,(int32_t)UINT32_C(0x00000008)),0u);
/* 00110cdc: ldl a2,0x17(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110ce0: ldr a2,0x10(a0) */ loadPartial(6u,ea(4u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110ce4: ldl a3,0x1f(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110ce8: ldr a3,0x18(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x00000018)),0u);
/* 00110cec: sdl t1,0x7(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000007)),9u,1u);
/* 00110cf0: sdr t1,0x0(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000000)),9u,0u);
/* 00110cf4: sdl a1,0xf(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x0000000f)),5u,1u);
/* 00110cf8: sdr a1,0x8(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000008)),5u,0u);
/* 00110cfc: sdl a2,0x17(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000017)),6u,1u);
/* 00110d00: sdr a2,0x10(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000010)),6u,0u);
/* 00110d04: sdl a3,0x1f(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x0000001f)),7u,1u);
/* 00110d08: sdr a3,0x18(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000018)),7u,0u);
/* 00110d0c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110d10: nop  */ 
/* 00110d14: nop  */ 
/* 00110d18: bne a0,v0,0x00110ccc */ {int taken=(cpu(4)!=cpu(2));/* delay 00110d1c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(taken){goto L_00110ccc;}}
/* 00110d20: b 0x00110d64 */ /* delay 00110d24 */ set(2,sx(UINT32_C(0x00530000)));goto L_00110d64;
L_00110d28:;
/* 00110d28: addiu v0,a0,0x160 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000160)));
L_00110d2c:;
/* 00110d2c: ld t0,0x0(a0) */ restore(8,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00110d30: ld t1,0x8(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00110d34: ld a1,0x10(a0) */ restore(5,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00110d38: ld a2,0x18(a0) */ restore(6,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 00110d3c: sd t0,0x0(v1) */ save(8,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00110d40: sd t1,0x8(v1) */ save(9,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00110d44: sd a1,0x10(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 00110d48: sd a2,0x18(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 00110d4c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 00110d50: nop  */ 
/* 00110d54: nop  */ 
/* 00110d58: bne a0,v0,0x00110d2c */ {int taken=(cpu(4)!=cpu(2));/* delay 00110d5c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(taken){goto L_00110d2c;}}
/* 00110d60: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_00110d64:;
/* 00110d64: addiu s6,sp,0x1150 */ set(22,sx((uint32_t)cpu(29)+UINT32_C(0x00001150)));
/* 00110d68: addiu a1,v0,0x930 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000930)));
/* 00110d6c: ldl a3,0x7(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110d70: ldr a3,0x0(a0) */ loadPartial(7u,ea(4u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110d74: sdl a3,0x7(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000007)),7u,1u);
/* 00110d78: sdr a3,0x0(v1) */ storePartial(ea(3u,(int32_t)UINT32_C(0x00000000)),7u,0u);
/* 00110d7c: andi v0,a1,0x7 */ set(2,cpu(5)&UINT32_C(0x00000007));
/* 00110d80: beq v0,zero,0x00110de8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110d84 */ set(4,cpu(22));if(taken){goto L_00110de8;}}
/* 00110d88: addiu v0,a1,0x160 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000160)));
L_00110d8c:;
/* 00110d8c: ldl v1,0x7(a1) */ loadPartial(3u,ea(5u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110d90: ldr v1,0x0(a1) */ loadPartial(3u,ea(5u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110d94: ldl a2,0xf(a1) */ loadPartial(6u,ea(5u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110d98: ldr a2,0x8(a1) */ loadPartial(6u,ea(5u,(int32_t)UINT32_C(0x00000008)),0u);
/* 00110d9c: ldl a3,0x17(a1) */ loadPartial(7u,ea(5u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110da0: ldr a3,0x10(a1) */ loadPartial(7u,ea(5u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110da4: ldl t0,0x1f(a1) */ loadPartial(8u,ea(5u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110da8: ldr t0,0x18(a1) */ loadPartial(8u,ea(5u,(int32_t)UINT32_C(0x00000018)),0u);
/* 00110dac: sdl v1,0x7(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000007)),3u,1u);
/* 00110db0: sdr v1,0x0(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000000)),3u,0u);
/* 00110db4: sdl a2,0xf(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x0000000f)),6u,1u);
/* 00110db8: sdr a2,0x8(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000008)),6u,0u);
/* 00110dbc: sdl a3,0x17(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000017)),7u,1u);
/* 00110dc0: sdr a3,0x10(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000010)),7u,0u);
/* 00110dc4: sdl t0,0x1f(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x0000001f)),8u,1u);
/* 00110dc8: sdr t0,0x18(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000018)),8u,0u);
/* 00110dcc: addiu a1,a1,0x20 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));
/* 00110dd0: nop  */ 
/* 00110dd4: nop  */ 
/* 00110dd8: bne a1,v0,0x00110d8c */ {int taken=(cpu(5)!=cpu(2));/* delay 00110ddc */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_00110d8c;}}
/* 00110de0: b 0x00110e24 */ /* delay 00110de4 */ set(2,sx(UINT32_C(0x00530000)));goto L_00110e24;
L_00110de8:;
/* 00110de8: addiu v0,a1,0x160 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000160)));
L_00110dec:;
/* 00110dec: ld t1,0x0(a1) */ restore(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00110df0: ld v1,0x8(a1) */ restore(3,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00110df4: ld a2,0x10(a1) */ restore(6,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00110df8: ld a3,0x18(a1) */ restore(7,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 00110dfc: sd t1,0x0(a0) */ save(9,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00110e00: sd v1,0x8(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00110e04: sd a2,0x10(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00110e08: sd a3,0x18(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 00110e0c: addiu a1,a1,0x20 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));
/* 00110e10: nop  */ 
/* 00110e14: nop  */ 
/* 00110e18: bne a1,v0,0x00110dec */ {int taken=(cpu(5)!=cpu(2));/* delay 00110e1c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_00110dec;}}
/* 00110e20: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_00110e24:;
/* 00110e24: addiu s1,sp,0x12c0 */ set(17,sx((uint32_t)cpu(29)+UINT32_C(0x000012c0)));
/* 00110e28: addiu v1,v0,0xa98 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000a98)));
/* 00110e2c: ldl t0,0x7(a1) */ loadPartial(8u,ea(5u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110e30: ldr t0,0x0(a1) */ loadPartial(8u,ea(5u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110e34: sdl t0,0x7(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000007)),8u,1u);
/* 00110e38: sdr t0,0x0(a0) */ storePartial(ea(4u,(int32_t)UINT32_C(0x00000000)),8u,0u);
/* 00110e3c: andi v0,v1,0x7 */ set(2,cpu(3)&UINT32_C(0x00000007));
/* 00110e40: beq v0,zero,0x00110ea8 */ {int taken=(cpu(2)==cpu(0));/* delay 00110e44 */ set(6,cpu(17));if(taken){goto L_00110ea8;}}
/* 00110e48: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_00110e4c:;
/* 00110e4c: ldl a3,0x7(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110e50: ldr a3,0x0(v1) */ loadPartial(7u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110e54: ldl t0,0xf(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x0000000f)),1u);
/* 00110e58: ldr t0,0x8(v1) */ loadPartial(8u,ea(3u,(int32_t)UINT32_C(0x00000008)),0u);
/* 00110e5c: ldl t1,0x17(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000017)),1u);
/* 00110e60: ldr t1,0x10(v1) */ loadPartial(9u,ea(3u,(int32_t)UINT32_C(0x00000010)),0u);
/* 00110e64: ldl a0,0x1f(v1) */ loadPartial(4u,ea(3u,(int32_t)UINT32_C(0x0000001f)),1u);
/* 00110e68: ldr a0,0x18(v1) */ loadPartial(4u,ea(3u,(int32_t)UINT32_C(0x00000018)),0u);
/* 00110e6c: sdl a3,0x7(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000007)),7u,1u);
/* 00110e70: sdr a3,0x0(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000000)),7u,0u);
/* 00110e74: sdl t0,0xf(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x0000000f)),8u,1u);
/* 00110e78: sdr t0,0x8(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000008)),8u,0u);
/* 00110e7c: sdl t1,0x17(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000017)),9u,1u);
/* 00110e80: sdr t1,0x10(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000010)),9u,0u);
/* 00110e84: sdl a0,0x1f(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x0000001f)),4u,1u);
/* 00110e88: sdr a0,0x18(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000018)),4u,0u);
/* 00110e8c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110e90: nop  */ 
/* 00110e94: nop  */ 
/* 00110e98: bne v1,v0,0x00110e4c */ {int taken=(cpu(3)!=cpu(2));/* delay 00110e9c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000020)));if(taken){goto L_00110e4c;}}
/* 00110ea0: b 0x00110ee4 */ /* delay 00110ea4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00110ee4;
L_00110ea8:;
/* 00110ea8: addiu v0,v1,0x160 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000160)));
L_00110eac:;
/* 00110eac: ld a1,0x0(v1) */ restore(5,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00110eb0: ld a3,0x8(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00110eb4: ld t0,0x10(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 00110eb8: ld t1,0x18(v1) */ restore(9,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 00110ebc: sd a1,0x0(a2) */ save(5,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 00110ec0: sd a3,0x8(a2) */ save(7,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 00110ec4: sd t0,0x10(a2) */ save(8,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 00110ec8: sd t1,0x18(a2) */ save(9,ea(6,(int32_t)UINT32_C(0x00000018)));
/* 00110ecc: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 00110ed0: nop  */ 
/* 00110ed4: nop  */ 
/* 00110ed8: bne v1,v0,0x00110eac */ {int taken=(cpu(3)!=cpu(2));/* delay 00110edc */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000020)));if(taken){goto L_00110eac;}}
/* 00110ee0: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00110ee4:;
/* 00110ee4: move a1,zero */ set(5,cpu(0));
/* 00110ee8: ldl v0,0x7(v1) */ loadPartial(2u,ea(3u,(int32_t)UINT32_C(0x00000007)),1u);
/* 00110eec: ldr v0,0x0(v1) */ loadPartial(2u,ea(3u,(int32_t)UINT32_C(0x00000000)),0u);
/* 00110ef0: sdl v0,0x7(a2) */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000007)),2u,1u);
/* 00110ef4: jal 0x002b2748 */ set(31,UINT64_C(0x00110efc));/* delay 00110ef8 */ storePartial(ea(6u,(int32_t)UINT32_C(0x00000000)),2u,0u);body_002b2748();
/* 00110efc: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 00110f00: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 00110f04: addiu a1,a1,-0x1630 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe9d0)));
/* 00110f08: jal 0x002b2688 */ set(31,UINT64_C(0x00110f10));/* delay 00110f0c */ set(16,cpu(2));body_002b2688();
/* 00110f10: blez v0,0x00110f68 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00110f14 */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_00110f68;}}
/* 00110f18: addiu v0,sp,0x180 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000180)));
/* 00110f1c: move s1,zero */ set(17,cpu(0));
/* 00110f20: addiu s2,v0,0x14 */ set(18,sx((uint32_t)cpu(2)+UINT32_C(0x00000014)));
/* 00110f24: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00110f28: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00110f2c: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00110f30:;
/* 00110f30: move a1,s2 */ set(5,cpu(18));
/* 00110f34: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00110f38: jal 0x002b2688 */ set(31,UINT64_C(0x00110f40));/* delay 00110f3c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00110f40: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00110f44: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00110f48: blez v0,0x00110f58 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00110f4c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00110f58;}}
/* 00110f50: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 00110f54: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00110f58:;
/* 00110f58: bnel v1,zero,0x00110f30 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00110f5c */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00110f30;}}
/* 00110f60: b 0x00111944 */ /* delay 00110f64 */ goto L_00111944;
L_00110f68:;
/* 00110f68: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 00110f6c: jal 0x002b2688 */ set(31,UINT64_C(0x00110f74));/* delay 00110f70 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c00)));body_002b2688();
/* 00110f74: blez v0,0x00110fd0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00110f78 */ set(5,cpu(17));if(taken){goto L_00110fd0;}}
/* 00110f7c: addiu v1,sp,0xa20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000a20)));
/* 00110f80: move s1,zero */ set(17,cpu(0));
/* 00110f84: addiu s2,v1,0x14 */ set(18,sx((uint32_t)cpu(3)+UINT32_C(0x00000014)));
/* 00110f88: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00110f8c: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00110f90: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 00110f94: nop  */ 
L_00110f98:;
/* 00110f98: move a1,s2 */ set(5,cpu(18));
/* 00110f9c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00110fa0: jal 0x002b2688 */ set(31,UINT64_C(0x00110fa8));/* delay 00110fa4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00110fa8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00110fac: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00110fb0: blez v0,0x00110fc0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00110fb4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00110fc0;}}
/* 00110fb8: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 00110fbc: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00110fc0:;
/* 00110fc0: bnel v1,zero,0x00110f98 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00110fc4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00110f98;}}
/* 00110fc8: b 0x00111944 */ /* delay 00110fcc */ goto L_00111944;
L_00110fd0:;
/* 00110fd0: jal 0x002d5ab4 */ set(31,UINT64_C(0x00110fd8));/* delay 00110fd4 */ set(4,cpu(16));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00110fd0));
/* 00110fd8: bne v0,zero,0x00111030 */ {int taken=(cpu(2)!=cpu(0));/* delay 00110fdc */ set(5,cpu(22));if(taken){goto L_00111030;}}
/* 00110fe0: move s1,zero */ set(17,cpu(0));
/* 00110fe4: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00110fe8: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00110fec: addiu s2,sp,0x12d4 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x000012d4)));
/* 00110ff0: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 00110ff4: nop  */ 
L_00110ff8:;
/* 00110ff8: move a1,s2 */ set(5,cpu(18));
/* 00110ffc: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111000: jal 0x002b2688 */ set(31,UINT64_C(0x00111008));/* delay 00111004 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111008: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011100c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111010: blez v0,0x00111020 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111014 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111020;}}
/* 00111018: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011101c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111020:;
/* 00111020: bnel v1,zero,0x00110ff8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111024 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00110ff8;}}
/* 00111028: b 0x00111944 */ /* delay 0011102c */ goto L_00111944;
L_00111030:;
/* 00111030: jal 0x002d5ab4 */ set(31,UINT64_C(0x00111038));/* delay 00111034 */ set(4,cpu(16));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111030));
/* 00111038: bne v0,zero,0x00111090 */ {int taken=(cpu(2)!=cpu(0));/* delay 0011103c */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000e70)));if(taken){goto L_00111090;}}
/* 00111040: move s1,zero */ set(17,cpu(0));
/* 00111044: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00111048: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 0011104c: addiu s2,sp,0x1164 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00001164)));
/* 00111050: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 00111054: nop  */ 
L_00111058:;
/* 00111058: move a1,s2 */ set(5,cpu(18));
/* 0011105c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111060: jal 0x002b2688 */ set(31,UINT64_C(0x00111068));/* delay 00111064 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111068: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011106c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111070: blez v0,0x00111080 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111074 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111080;}}
/* 00111078: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011107c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111080:;
/* 00111080: bnel v1,zero,0x00111058 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111084 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111058;}}
/* 00111088: b 0x00111944 */ /* delay 0011108c */ goto L_00111944;
L_00111090:;
/* 00111090: move a1,a0 */ set(5,cpu(4));
/* 00111094: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011109c));/* delay 00111098 */ set(4,cpu(16));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111094));
/* 0011109c: bne v0,zero,0x001110f0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001110a0 */ set(4,cpu(16));if(taken){goto L_001110f0;}}
/* 001110a4: move s1,zero */ set(17,cpu(0));
/* 001110a8: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 001110ac: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001110b0: addiu s2,sp,0xe84 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000e84)));
/* 001110b4: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_001110b8:;
/* 001110b8: move a1,s2 */ set(5,cpu(18));
/* 001110bc: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001110c0: jal 0x002b2688 */ set(31,UINT64_C(0x001110c8));/* delay 001110c4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001110c8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001110cc: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001110d0: blez v0,0x001110e0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001110d4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001110e0;}}
/* 001110d8: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 001110dc: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001110e0:;
/* 001110e0: bnel v1,zero,0x001110b8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001110e4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001110b8;}}
/* 001110e8: b 0x00111944 */ /* delay 001110ec */ goto L_00111944;
L_001110f0:;
/* 001110f0: jal 0x002d5ab4 */ set(31,UINT64_C(0x001110f8));/* delay 001110f4 */ set(5,cpu(21));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001110f0));
/* 001110f8: bne v0,zero,0x00111150 */ {int taken=(cpu(2)!=cpu(0));/* delay 001110fc */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_00111150;}}
/* 00111100: move s1,zero */ set(17,cpu(0));
/* 00111104: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00111108: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 0011110c: addiu s2,sp,0xd14 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000d14)));
/* 00111110: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 00111114: nop  */ 
L_00111118:;
/* 00111118: move a1,s2 */ set(5,cpu(18));
/* 0011111c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111120: jal 0x002b2688 */ set(31,UINT64_C(0x00111128));/* delay 00111124 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111128: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011112c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111130: blez v0,0x00111140 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111134 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111140;}}
/* 00111138: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011113c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111140:;
/* 00111140: bnel v1,zero,0x00111118 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111144 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111118;}}
/* 00111148: b 0x00111944 */ /* delay 0011114c */ goto L_00111944;
L_00111150:;
/* 00111150: move a0,s0 */ set(4,cpu(16));
/* 00111154: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011115c));/* delay 00111158 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c10)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111154));
/* 0011115c: bne v0,zero,0x001111b0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111160 */ set(4,cpu(16));if(taken){goto L_001111b0;}}
/* 00111164: addiu s2,s5,0x14 */ set(18,sx((uint32_t)cpu(21)+UINT32_C(0x00000014)));
/* 00111168: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 0011116c: move s1,zero */ set(17,cpu(0));
/* 00111170: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00111174: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111178:;
/* 00111178: move a1,s2 */ set(5,cpu(18));
/* 0011117c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111180: jal 0x002b2688 */ set(31,UINT64_C(0x00111188));/* delay 00111184 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111188: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011118c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111190: blez v0,0x001111a0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111194 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001111a0;}}
/* 00111198: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011119c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001111a0:;
/* 001111a0: bnel v1,zero,0x00111178 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001111a4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111178;}}
/* 001111a8: b 0x00111944 */ /* delay 001111ac */ goto L_00111944;
L_001111b0:;
/* 001111b0: jal 0x002d5ab4 */ set(31,UINT64_C(0x001111b8));/* delay 001111b4 */ set(5,cpu(30));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001111b0));
/* 001111b8: bne v0,zero,0x00111210 */ {int taken=(cpu(2)!=cpu(0));/* delay 001111bc */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_00111210;}}
/* 001111c0: move s1,zero */ set(17,cpu(0));
/* 001111c4: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 001111c8: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001111cc: addiu s2,sp,0x8c4 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x000008c4)));
/* 001111d0: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 001111d4: nop  */ 
L_001111d8:;
/* 001111d8: move a1,s2 */ set(5,cpu(18));
/* 001111dc: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001111e0: jal 0x002b2688 */ set(31,UINT64_C(0x001111e8));/* delay 001111e4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001111e8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001111ec: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001111f0: blez v0,0x00111200 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001111f4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111200;}}
/* 001111f8: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 001111fc: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111200:;
/* 00111200: bnel v1,zero,0x001111d8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111204 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001111d8;}}
/* 00111208: b 0x00111944 */ /* delay 0011120c */ goto L_00111944;
L_00111210:;
/* 00111210: move a0,s0 */ set(4,cpu(16));
/* 00111214: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011121c));/* delay 00111218 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe9d8)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111214));
/* 0011121c: bne v0,zero,0x00111270 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111220 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000b90)));if(taken){goto L_00111270;}}
/* 00111224: addiu s2,s8,0x14 */ set(18,sx((uint32_t)cpu(30)+UINT32_C(0x00000014)));
/* 00111228: move s1,zero */ set(17,cpu(0));
/* 0011122c: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00111230: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111234: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111238:;
/* 00111238: move a1,s2 */ set(5,cpu(18));
/* 0011123c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111240: jal 0x002b2688 */ set(31,UINT64_C(0x00111248));/* delay 00111244 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111248: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011124c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111250: blez v0,0x00111260 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111254 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111260;}}
/* 00111258: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011125c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111260:;
/* 00111260: bnel v1,zero,0x00111238 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111264 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111238;}}
/* 00111268: b 0x00111944 */ /* delay 0011126c */ goto L_00111944;
L_00111270:;
/* 00111270: move a0,s0 */ set(4,cpu(16));
/* 00111274: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011127c));/* delay 00111278 */ set(5,cpu(6));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111274));
/* 0011127c: bne v0,zero,0x001112d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111280 */ set(4,cpu(16));if(taken){goto L_001112d0;}}
/* 00111284: move s1,zero */ set(17,cpu(0));
/* 00111288: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 0011128c: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111290: addiu s2,sp,0xba4 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000ba4)));
/* 00111294: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111298:;
/* 00111298: move a1,s2 */ set(5,cpu(18));
/* 0011129c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001112a0: jal 0x002b2688 */ set(31,UINT64_C(0x001112a8));/* delay 001112a4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001112a8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001112ac: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001112b0: blez v0,0x001112c0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001112b4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001112c0;}}
/* 001112b8: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 001112bc: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001112c0:;
/* 001112c0: bnel v1,zero,0x00111298 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001112c4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111298;}}
/* 001112c8: b 0x00111944 */ /* delay 001112cc */ goto L_00111944;
L_001112d0:;
/* 001112d0: jal 0x002d5ab4 */ set(31,UINT64_C(0x001112d8));/* delay 001112d4 */ set(5,cpu(23));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001112d0));
/* 001112d8: bne v0,zero,0x00111330 */ {int taken=(cpu(2)!=cpu(0));/* delay 001112dc */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_00111330;}}
/* 001112e0: move s1,zero */ set(17,cpu(0));
/* 001112e4: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 001112e8: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001112ec: addiu s2,sp,0x754 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000754)));
/* 001112f0: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 001112f4: nop  */ 
L_001112f8:;
/* 001112f8: move a1,s2 */ set(5,cpu(18));
/* 001112fc: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111300: jal 0x002b2688 */ set(31,UINT64_C(0x00111308));/* delay 00111304 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111308: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011130c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111310: blez v0,0x00111320 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111314 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111320;}}
/* 00111318: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011131c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111320:;
/* 00111320: bnel v1,zero,0x001112f8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111324 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001112f8;}}
/* 00111328: b 0x00111944 */ /* delay 0011132c */ goto L_00111944;
L_00111330:;
/* 00111330: move a0,s0 */ set(4,cpu(16));
/* 00111334: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011133c));/* delay 00111338 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe9e0)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111334));
/* 0011133c: bne v0,zero,0x00111390 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111340 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_00111390;}}
/* 00111344: addiu s2,s7,0x14 */ set(18,sx((uint32_t)cpu(23)+UINT32_C(0x00000014)));
/* 00111348: move s1,zero */ set(17,cpu(0));
/* 0011134c: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 00111350: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111354: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111358:;
/* 00111358: move a1,s2 */ set(5,cpu(18));
/* 0011135c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111360: jal 0x002b2688 */ set(31,UINT64_C(0x00111368));/* delay 00111364 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111368: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011136c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111370: blez v0,0x00111380 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111374 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111380;}}
/* 00111378: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011137c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111380:;
/* 00111380: bnel v1,zero,0x00111358 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111384 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111358;}}
/* 00111388: b 0x00111944 */ /* delay 0011138c */ goto L_00111944;
L_00111390:;
/* 00111390: move a0,s0 */ set(4,cpu(16));
/* 00111394: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011139c));/* delay 00111398 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe9e8)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111394));
/* 0011139c: bne v0,zero,0x001113f0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001113a0 */ set(7,sx((uint32_t)cpu(29)+UINT32_C(0x000005d0)));if(taken){goto L_001113f0;}}
/* 001113a4: addiu s2,s7,0x14 */ set(18,sx((uint32_t)cpu(23)+UINT32_C(0x00000014)));
/* 001113a8: move s1,zero */ set(17,cpu(0));
/* 001113ac: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 001113b0: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001113b4: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_001113b8:;
/* 001113b8: move a1,s2 */ set(5,cpu(18));
/* 001113bc: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001113c0: jal 0x002b2688 */ set(31,UINT64_C(0x001113c8));/* delay 001113c4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001113c8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001113cc: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001113d0: blez v0,0x001113e0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001113d4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001113e0;}}
/* 001113d8: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 001113dc: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001113e0:;
/* 001113e0: bnel v1,zero,0x001113b8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001113e4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001113b8;}}
/* 001113e8: b 0x00111944 */ /* delay 001113ec */ goto L_00111944;
L_001113f0:;
/* 001113f0: move a0,s0 */ set(4,cpu(16));
/* 001113f4: jal 0x002d5ab4 */ set(31,UINT64_C(0x001113fc));/* delay 001113f8 */ set(5,cpu(7));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001113f4));
/* 001113fc: bne v0,zero,0x00111450 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111400 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_00111450;}}
/* 00111404: move s1,zero */ set(17,cpu(0));
/* 00111408: li s6,0x3 */ set(22,sx(UINT32_C(0x00000003)));
/* 0011140c: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111410: addiu s2,sp,0x5e4 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x000005e4)));
/* 00111414: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111418:;
/* 00111418: move a1,s2 */ set(5,cpu(18));
/* 0011141c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111420: jal 0x002b2688 */ set(31,UINT64_C(0x00111428));/* delay 00111424 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111428: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011142c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111430: blez v0,0x00111440 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111434 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111440;}}
/* 00111438: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011143c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111440:;
/* 00111440: bnel v1,zero,0x00111418 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111444 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111418;}}
/* 00111448: b 0x00111944 */ /* delay 0011144c */ goto L_00111944;
L_00111450:;
/* 00111450: move a0,s0 */ set(4,cpu(16));
/* 00111454: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011145c));/* delay 00111458 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe9f0)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111454));
/* 0011145c: bne v0,zero,0x001114b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111460 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_001114b8;}}
/* 00111464: addiu t0,sp,0x5d0 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x000005d0)));
/* 00111468: move s1,zero */ set(17,cpu(0));
/* 0011146c: addiu s2,t0,0x14 */ set(18,sx((uint32_t)cpu(8)+UINT32_C(0x00000014)));
/* 00111470: li s6,0x3 */ set(22,sx(UINT32_C(0x00000003)));
/* 00111474: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111478: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 0011147c: nop  */ 
L_00111480:;
/* 00111480: move a1,s2 */ set(5,cpu(18));
/* 00111484: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111488: jal 0x002b2688 */ set(31,UINT64_C(0x00111490));/* delay 0011148c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111490: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00111494: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111498: blez v0,0x001114a8 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0011149c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001114a8;}}
/* 001114a0: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 001114a4: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001114a8:;
/* 001114a8: bnel v1,zero,0x00111480 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001114ac */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111480;}}
/* 001114b0: b 0x00111944 */ /* delay 001114b4 */ goto L_00111944;
L_001114b8:;
/* 001114b8: move a0,s0 */ set(4,cpu(16));
/* 001114bc: jal 0x002d5ab4 */ set(31,UINT64_C(0x001114c4));/* delay 001114c0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe9f8)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001114bc));
/* 001114c4: bne v0,zero,0x00111520 */ {int taken=(cpu(2)!=cpu(0));/* delay 001114c8 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000fe0)));if(taken){goto L_00111520;}}
/* 001114cc: addiu t1,sp,0x5d0 */ set(9,sx((uint32_t)cpu(29)+UINT32_C(0x000005d0)));
/* 001114d0: move s1,zero */ set(17,cpu(0));
/* 001114d4: addiu s2,t1,0x14 */ set(18,sx((uint32_t)cpu(9)+UINT32_C(0x00000014)));
/* 001114d8: li s6,0x3 */ set(22,sx(UINT32_C(0x00000003)));
/* 001114dc: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001114e0: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 001114e4: nop  */ 
L_001114e8:;
/* 001114e8: move a1,s2 */ set(5,cpu(18));
/* 001114ec: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001114f0: jal 0x002b2688 */ set(31,UINT64_C(0x001114f8));/* delay 001114f4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001114f8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001114fc: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111500: blez v0,0x00111510 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111504 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111510;}}
/* 00111508: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011150c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111510:;
/* 00111510: bnel v1,zero,0x001114e8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111514 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001114e8;}}
/* 00111518: b 0x00111944 */ /* delay 0011151c */ goto L_00111944;
L_00111520:;
/* 00111520: move a0,s0 */ set(4,cpu(16));
/* 00111524: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011152c));/* delay 00111528 */ set(5,cpu(2));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111524));
/* 0011152c: bne v0,zero,0x00111580 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111530 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));if(taken){goto L_00111580;}}
/* 00111534: move s1,zero */ set(17,cpu(0));
/* 00111538: li s6,0x3 */ set(22,sx(UINT32_C(0x00000003)));
/* 0011153c: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111540: addiu s2,sp,0xff4 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000ff4)));
/* 00111544: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111548:;
/* 00111548: move a1,s2 */ set(5,cpu(18));
/* 0011154c: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111550: jal 0x002b2688 */ set(31,UINT64_C(0x00111558));/* delay 00111554 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111558: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 0011155c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111560: blez v0,0x00111570 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00111564 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111570;}}
/* 00111568: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 0011156c: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111570:;
/* 00111570: bnel v1,zero,0x00111548 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00111574 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111548;}}
/* 00111578: b 0x00111944 */ /* delay 0011157c */ goto L_00111944;
L_00111580:;
/* 00111580: move a0,s0 */ set(4,cpu(16));
/* 00111584: jal 0x002d5ab4 */ set(31,UINT64_C(0x0011158c));/* delay 00111588 */ set(5,cpu(3));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x00111584));
/* 0011158c: bne v0,zero,0x001115e0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111590 */ set(4,cpu(16));if(taken){goto L_001115e0;}}
/* 00111594: move s1,zero */ set(17,cpu(0));
/* 00111598: li s6,0x2 */ set(22,sx(UINT32_C(0x00000002)));
/* 0011159c: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001115a0: addiu s2,sp,0x24 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000024)));
/* 001115a4: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_001115a8:;
/* 001115a8: move a1,s2 */ set(5,cpu(18));
/* 001115ac: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001115b0: jal 0x002b2688 */ set(31,UINT64_C(0x001115b8));/* delay 001115b4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001115b8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001115bc: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001115c0: blez v0,0x001115d0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001115c4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001115d0;}}
/* 001115c8: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 001115cc: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001115d0:;
/* 001115d0: bnel v1,zero,0x001115a8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001115d4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001115a8;}}
/* 001115d8: b 0x00111944 */ /* delay 001115dc */ goto L_00111944;
L_001115e0:;
/* 001115e0: jal 0x002d5ab4 */ set(31,UINT64_C(0x001115e8));/* delay 001115e4 */ set(5,cpu(18));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001115e0));
/* 001115e8: bne v0,zero,0x00111638 */ {int taken=(cpu(2)!=cpu(0));/* delay 001115ec */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_00111638;}}
/* 001115f0: move s1,zero */ set(17,cpu(0));
/* 001115f4: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001115f8: addiu s2,sp,0x304 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000304)));
/* 001115fc: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111600:;
/* 00111600: move a1,s2 */ set(5,cpu(18));
/* 00111604: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111608: jal 0x002b2688 */ set(31,UINT64_C(0x00111610));/* delay 0011160c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111610: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00111614: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111618: blez v0,0x00111628 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0011161c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111628;}}
/* 00111620: sw zero,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 00111624: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111628:;
/* 00111628: bnel v1,zero,0x00111600 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0011162c */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111600;}}
/* 00111630: b 0x00111944 */ /* delay 00111634 */ goto L_00111944;
L_00111638:;
/* 00111638: move a0,s0 */ set(4,cpu(16));
/* 0011163c: jal 0x002d5ab4 */ set(31,UINT64_C(0x00111644));/* delay 00111640 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c20)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x0011163c));
/* 00111644: bne v0,zero,0x00111698 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111648 */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_00111698;}}
/* 0011164c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111650: move s1,zero */ set(17,cpu(0));
/* 00111654: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111658: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 0011165c: nop  */ 
L_00111660:;
/* 00111660: move a1,s2 */ set(5,cpu(18));
/* 00111664: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111668: jal 0x002b2688 */ set(31,UINT64_C(0x00111670));/* delay 0011166c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111670: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00111674: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111678: blez v0,0x00111688 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0011167c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111688;}}
/* 00111680: sw zero,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 00111684: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111688:;
/* 00111688: bnel v1,zero,0x00111660 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0011168c */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111660;}}
/* 00111690: b 0x00111944 */ /* delay 00111694 */ goto L_00111944;
L_00111698:;
/* 00111698: move a0,s0 */ set(4,cpu(16));
/* 0011169c: jal 0x002d5ab4 */ set(31,UINT64_C(0x001116a4));/* delay 001116a0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c30)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x0011169c));
/* 001116a4: bne v0,zero,0x001116f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001116a8 */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_001116f8;}}
/* 001116ac: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001116b0: move s1,zero */ set(17,cpu(0));
/* 001116b4: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001116b8: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 001116bc: nop  */ 
L_001116c0:;
/* 001116c0: move a1,s2 */ set(5,cpu(18));
/* 001116c4: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001116c8: jal 0x002b2688 */ set(31,UINT64_C(0x001116d0));/* delay 001116cc */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001116d0: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001116d4: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001116d8: blez v0,0x001116e8 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001116dc */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001116e8;}}
/* 001116e0: sw zero,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 001116e4: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001116e8:;
/* 001116e8: bnel v1,zero,0x001116c0 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001116ec */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001116c0;}}
/* 001116f0: b 0x00111944 */ /* delay 001116f4 */ goto L_00111944;
L_001116f8:;
/* 001116f8: move a0,s0 */ set(4,cpu(16));
/* 001116fc: jal 0x002d5ab4 */ set(31,UINT64_C(0x00111704));/* delay 00111700 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c40)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001116fc));
/* 00111704: bne v0,zero,0x00111758 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111708 */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_00111758;}}
/* 0011170c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111710: move s1,zero */ set(17,cpu(0));
/* 00111714: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111718: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 0011171c: nop  */ 
L_00111720:;
/* 00111720: move a1,s2 */ set(5,cpu(18));
/* 00111724: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111728: jal 0x002b2688 */ set(31,UINT64_C(0x00111730));/* delay 0011172c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111730: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00111734: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111738: blez v0,0x00111748 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0011173c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111748;}}
/* 00111740: sw zero,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 00111744: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111748:;
/* 00111748: bnel v1,zero,0x00111720 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0011174c */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111720;}}
/* 00111750: b 0x00111944 */ /* delay 00111754 */ goto L_00111944;
L_00111758:;
/* 00111758: move a0,s0 */ set(4,cpu(16));
/* 0011175c: jal 0x002d5ab4 */ set(31,UINT64_C(0x00111764));/* delay 00111760 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c50)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x0011175c));
/* 00111764: bne v0,zero,0x001117b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111768 */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_001117b8;}}
/* 0011176c: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111770: move s1,zero */ set(17,cpu(0));
/* 00111774: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111778: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 0011177c: nop  */ 
L_00111780:;
/* 00111780: move a1,s2 */ set(5,cpu(18));
/* 00111784: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111788: jal 0x002b2688 */ set(31,UINT64_C(0x00111790));/* delay 0011178c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111790: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00111794: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111798: blez v0,0x001117a8 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0011179c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001117a8;}}
/* 001117a0: sw zero,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 001117a4: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001117a8:;
/* 001117a8: bnel v1,zero,0x00111780 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001117ac */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111780;}}
/* 001117b0: b 0x00111944 */ /* delay 001117b4 */ goto L_00111944;
L_001117b8:;
/* 001117b8: move a0,s0 */ set(4,cpu(16));
/* 001117bc: jal 0x002d5ab4 */ set(31,UINT64_C(0x001117c4));/* delay 001117c0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c60)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x001117bc));
/* 001117c4: bne v0,zero,0x00111818 */ {int taken=(cpu(2)!=cpu(0));/* delay 001117c8 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000460)));if(taken){goto L_00111818;}}
/* 001117cc: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001117d0: move s1,zero */ set(17,cpu(0));
/* 001117d4: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001117d8: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 001117dc: nop  */ 
L_001117e0:;
/* 001117e0: move a1,s2 */ set(5,cpu(18));
/* 001117e4: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001117e8: jal 0x002b2688 */ set(31,UINT64_C(0x001117f0));/* delay 001117ec */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001117f0: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001117f4: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001117f8: blez v0,0x00111808 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001117fc */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111808;}}
/* 00111800: sw zero,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 00111804: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111808:;
/* 00111808: bnel v1,zero,0x001117e0 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0011180c */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001117e0;}}
/* 00111810: b 0x00111944 */ /* delay 00111814 */ goto L_00111944;
L_00111818:;
/* 00111818: move a0,s0 */ set(4,cpu(16));
/* 0011181c: jal 0x002d5ab4 */ set(31,UINT64_C(0x00111824));/* delay 00111820 */ set(5,cpu(6));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x0011181c));
/* 00111824: bne v0,zero,0x00111878 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111828 */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_00111878;}}
/* 0011182c: move s1,zero */ set(17,cpu(0));
/* 00111830: li s6,0x1 */ set(22,sx(UINT32_C(0x00000001)));
/* 00111834: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 00111838: addiu s2,sp,0x474 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000474)));
/* 0011183c: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
L_00111840:;
/* 00111840: move a1,s2 */ set(5,cpu(18));
/* 00111844: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 00111848: jal 0x002b2688 */ set(31,UINT64_C(0x00111850));/* delay 0011184c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 00111850: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 00111854: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00111858: blez v0,0x00111868 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0011185c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_00111868;}}
/* 00111860: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 00111864: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00111868:;
/* 00111868: bnel v1,zero,0x00111840 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0011186c */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_00111840;}}
/* 00111870: b 0x00111944 */ /* delay 00111874 */ goto L_00111944;
L_00111878:;
/* 00111878: move a0,s0 */ set(4,cpu(16));
/* 0011187c: jal 0x002d5ab4 */ set(31,UINT64_C(0x00111884));/* delay 00111880 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000c70)));nocturneObjectAttachmentCall(UINT32_C(0x002d5ab4),UINT32_C(0x0011187c));
/* 00111884: bne v0,zero,0x001118e0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111888 */ lw(8,ea(29,(int32_t)UINT32_C(0x00001434)));if(taken){goto L_001118e0;}}
/* 0011188c: addiu a3,sp,0x460 */ set(7,sx((uint32_t)cpu(29)+UINT32_C(0x00000460)));
/* 00111890: move s1,zero */ set(17,cpu(0));
/* 00111894: addiu s2,a3,0x14 */ set(18,sx((uint32_t)cpu(7)+UINT32_C(0x00000014)));
/* 00111898: li s6,0x1 */ set(22,sx(UINT32_C(0x00000001)));
/* 0011189c: addiu s5,s3,0xc */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 001118a0: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 001118a4: nop  */ 
L_001118a8:;
/* 001118a8: move a1,s2 */ set(5,cpu(18));
/* 001118ac: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 001118b0: jal 0x002b2688 */ set(31,UINT64_C(0x001118b8));/* delay 001118b4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002b2688();
/* 001118b8: slti v1,s1,0x11 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001118bc: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 001118c0: blez v0,0x001118d0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001118c4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(taken){goto L_001118d0;}}
/* 001118c8: sw s6,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(22));
/* 001118cc: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_001118d0:;
/* 001118d0: bnel v1,zero,0x001118a8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001118d4 */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));goto L_001118a8;}}
/* 001118d8: b 0x00111944 */ /* delay 001118dc */ goto L_00111944;
L_001118e0:;
/* 001118e0: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 001118e4: bne t0,v0,0x00111944 */ {int taken=(cpu(8)!=cpu(2));/* delay 001118e8 */ lw(9,ea(29,(int32_t)UINT32_C(0x00001438)));if(taken){goto L_00111944;}}
/* 001118ec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001118f0: bne t1,v0,0x00111944 */ {int taken=(cpu(9)!=cpu(2));/* delay 001118f4 */ if(taken){goto L_00111944;}}
/* 001118f8: lw v1,0x18(s4) */ lw(3,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 001118fc: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00111900: lh s0,0x4(v0) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 00111904: blez s0,0x00111944 */ {int taken=((int64_t)cpu(16)<=0);/* delay 00111908 */ set(17,cpu(0));if(taken){goto L_00111944;}}
/* 0011190c: lui s2,0x53 */ set(18,sx(UINT32_C(0x00530000)));
L_00111910:;
/* 00111910: bnel s1,zero,0x00111938 */ {int taken=(cpu(17)!=cpu(0));if(taken){/* delay 00111914 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00111938;}}
/* 00111918: lw a0,0x18(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000018)));
/* 0011191c: jal 0x002b2748 */ set(31,UINT64_C(0x00111924));/* delay 00111920 */ set(5,cpu(0));body_002b2748();
/* 00111924: addiu a0,s2,0xc80 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000c80)));
/* 00111928: move a2,v0 */ set(6,cpu(2));
/* 0011192c: jal 0x002d4748 */ set(31,UINT64_C(0x00111934));/* delay 00111930 */ set(5,cpu(0));nocturneObjectAttachmentCall(UINT32_C(0x002d4748),UINT32_C(0x0011192c));
/* 00111934: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00111938:;
/* 00111938: slt v0,s1,s0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(16));
/* 0011193c: bne v0,zero,0x00111910 */ {int taken=(cpu(2)!=cpu(0));/* delay 00111940 */ if(taken){goto L_00111910;}}
L_00111944:;
/* 00111944: jal 0x001dd7a8 */ set(31,UINT64_C(0x0011194c));/* delay 00111948 */ set(4,cpu(20));body_001dd7a8();
/* 0011194c: sqc2 vf10,0x0(sp) */ storeVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00111950: lw a0,0x1430(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00001430)));
/* 00111954: jal 0x0010df08 */ set(31,UINT64_C(0x0011195c));/* delay 00111958 */ set(5,cpu(29));nocturneObjectAttachmentCall(UINT32_C(0x0010df08),UINT32_C(0x00111954));
/* 0011195c: lw v1,0x1430(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00001430)));
/* 00111960: lw v0,0x1c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000001c)));
/* 00111964: addiu v0,v0,0x50 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000050)));
/* 00111968: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0011196c: jal 0x002c04e8 */ set(31,UINT64_C(0x00111974));/* delay 00111970 */ nocturneObjectAttachmentCall(UINT32_C(0x002c04e8),UINT32_C(0x0011196c));
/* 00111974: jal 0x001dd750 */ set(31,UINT64_C(0x0011197c));/* delay 00111978 */ set(4,cpu(20));nocturneObjectAttachmentCall(UINT32_C(0x001dd750),UINT32_C(0x00111974));
/* 0011197c: lw a0,0x1430(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00001430)));
/* 00111980: lw v0,0x1c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 00111984: addiu v0,v0,0x40 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000040)));
/* 00111988: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0011198c: vmove.w vf10,vf0 */ attachmentMoveW(10u,0u);
/* 00111990: jal 0x001dd720 */ set(31,UINT64_C(0x00111998));/* delay 00111994 */ set(4,cpu(20));nocturneObjectAttachmentCall(UINT32_C(0x001dd720),UINT32_C(0x00111990));
/* 00111998: lwc1 f0,0x34(s4) */ f[0]=word(ea(20,(int32_t)UINT32_C(0x00000034)));
/* 0011199c: lw a1,0x1430(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00001430)));
/* 001119a0: sw s4,0xc(s3) */ sw(ea(19,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(20));
/* 001119a4: lw v1,0x1c(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 001119a8: lw s0,0x18(a1) */ lw(16,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 001119ac: swc1 f0,0xc4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x000000c4)),f[0]);
/* 001119b0: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001119b4: sw zero,0x44(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(0));
/* 001119b8: bne v0,zero,0x001119d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001119bc */ sw(ea(19,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));if(taken){goto L_001119d0;}}
/* 001119c0: lw a0,0x1430(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00001430)));
/* 001119c4: jal 0x001e39e8 */ set(31,UINT64_C(0x001119cc));/* delay 001119c8 */ set(5,cpu(20));nocturneObjectAttachmentCall(UINT32_C(0x001e39e8),UINT32_C(0x001119c4));
/* 001119cc: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_001119d0:;
/* 001119d0: ld s0,0x1440(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00001440)));
/* 001119d4: ld s1,0x1448(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00001448)));
/* 001119d8: ld s2,0x1450(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00001450)));
/* 001119dc: ld s3,0x1458(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00001458)));
/* 001119e0: ld s4,0x1460(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00001460)));
/* 001119e4: ld s5,0x1468(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00001468)));
/* 001119e8: ld s6,0x1470(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00001470)));
/* 001119ec: ld s7,0x1478(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00001478)));
/* 001119f0: ld s8,0x1480(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00001480)));
/* 001119f4: ld ra,0x1488(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00001488)));
/* 001119f8: jr ra */ {uint64_t target=cpu(31);/* delay 001119fc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00001490)));checkReturn(target,incoming);return;}
}
static void body_001dd7a8(void){
uint64_t incoming=cpu(31);
/* 001dd7a8: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001dd7ac: addiu v0,v0,0x70 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));
/* 001dd7b0: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001dd7b4: jr ra */ {uint64_t target=cpu(31);/* delay 001dd7b8 */ checkReturn(target,incoming);return;}
}
static void body_002b2688(void){
uint64_t incoming=cpu(31);
/* 002b2688: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002b268c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2690: move s2,a1 */ set(18,cpu(5));
/* 002b2694: lui a1,0x4d4e */ set(5,sx(UINT32_C(0x4d4e0000)));
/* 002b2698: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b269c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b26a0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b26a4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b26a8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002b26ac: jal 0x002b2670 */ set(31,UINT64_C(0x002b26b4));/* delay 002b26b0 */ set(5,cpu(5)|UINT32_C(0x0000444e));nocturneObjectAttachmentCall(UINT32_C(0x002b2670),UINT32_C(0x002b26ac));
/* 002b26b4: move v1,v0 */ set(3,cpu(2));
/* 002b26b8: bnel v1,zero,0x002b26c8 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002b26bc */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));goto L_002b26c8;}}
/* 002b26c0: b 0x002b2724 */ /* delay 002b26c4 */ set(2,sx(UINT32_C(0xffffffff)));goto L_002b2724;
L_002b26c8:;
/* 002b26c8: move a0,s2 */ set(4,cpu(18));
/* 002b26cc: addiu s0,v1,0x8 */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 002b26d0: li s4,-0x4 */ set(20,sx(UINT32_C(0xfffffffc)));
/* 002b26d4: jal 0x002d5d0c */ set(31,UINT64_C(0x002b26dc));/* delay 002b26d8 */ set(19,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));nocturneObjectAttachmentCall(UINT32_C(0x002d5d0c),UINT32_C(0x002b26d4));
/* 002b26dc: move s1,v0 */ set(17,cpu(2));
L_002b26e0:;
/* 002b26e0: jal 0x002d5d0c */ set(31,UINT64_C(0x002b26e8));/* delay 002b26e4 */ set(4,cpu(16));nocturneObjectAttachmentCall(UINT32_C(0x002d5d0c),UINT32_C(0x002b26e0));
/* 002b26e8: move a0,s0 */ set(4,cpu(16));
/* 002b26ec: addu v1,s0,v0 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002b26f0: move a1,s2 */ set(5,cpu(18));
/* 002b26f4: addiu v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000004)));
/* 002b26f8: move a2,s1 */ set(6,cpu(17));
/* 002b26fc: bne v0,s1,0x002b2714 */ {int taken=(cpu(2)!=cpu(17));/* delay 002b2700 */ set(16,cpu(3)&cpu(20));if(taken){goto L_002b2714;}}
/* 002b2704: jal 0x002d4310 */ set(31,UINT64_C(0x002b270c));/* delay 002b2708 */ nocturneObjectAttachmentCall(UINT32_C(0x002d4310),UINT32_C(0x002b2704));
/* 002b270c: beql v0,zero,0x002b2724 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002b2710 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002b2724;}}
L_002b2714:;
/* 002b2714: addiu s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000004)));
/* 002b2718: sltu v0,s0,s3 */ set(2,cpu(16)<cpu(19));
/* 002b271c: bne v0,zero,0x002b26e0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002b2720 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002b26e0;}}
L_002b2724:;
/* 002b2724: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2728: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b272c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2730: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b2734: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b2738: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002b273c: jr ra */ {uint64_t target=cpu(31);/* delay 002b2740 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002b2748(void){
uint64_t incoming=cpu(31);
/* 002b2748: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b274c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2750: move s0,a1 */ set(16,cpu(5));
/* 002b2754: lui a1,0x4d4e */ set(5,sx(UINT32_C(0x4d4e0000)));
/* 002b2758: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b275c: jal 0x002b2670 */ set(31,UINT64_C(0x002b2764));/* delay 002b2760 */ set(5,cpu(5)|UINT32_C(0x0000444e));nocturneObjectAttachmentCall(UINT32_C(0x002b2670),UINT32_C(0x002b275c));
/* 002b2764: move v1,v0 */ set(3,cpu(2));
/* 002b2768: bnel v1,zero,0x002b2778 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002b276c */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));goto L_002b2778;}}
/* 002b2770: b 0x002b27d0 */ /* delay 002b2774 */ set(2,sx(UINT32_C(0x00530000)));goto L_002b27d0;
L_002b2778:;
/* 002b2778: addiu a0,v1,0x8 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 002b277c: li a2,-0x4 */ set(6,sx(UINT32_C(0xfffffffc)));
/* 002b2780: lui a3,0x53 */ set(7,sx(UINT32_C(0x00530000)));
/* 002b2784: addu a1,v1,v0 */ set(5,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002b2788: move v1,a0 */ set(3,cpu(4));
/* 002b278c: nop  */ 
L_002b2790:;
/* 002b2790: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 002b2794: nop  */ 
/* 002b2798: nop  */ 
/* 002b279c: nop  */ 
/* 002b27a0: nop  */ 
/* 002b27a4: bne v0,zero,0x002b2790 */ {int taken=(cpu(2)!=cpu(0));/* delay 002b27a8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));if(taken){goto L_002b2790;}}
/* 002b27ac: addiu v0,v1,0x3 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000003)));
/* 002b27b0: and v0,v0,a2 */ set(2,cpu(2)&cpu(6));
/* 002b27b4: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b27b8: beql v1,s0,0x002b27d8 */ {int taken=(cpu(3)==cpu(16));if(taken){/* delay 002b27bc */ set(2,cpu(4));goto L_002b27d8;}}
/* 002b27c0: addiu a0,v0,0x4 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 002b27c4: sltu v0,a0,a1 */ set(2,cpu(4)<cpu(5));
/* 002b27c8: bne v0,zero,0x002b2790 */ {int taken=(cpu(2)!=cpu(0));/* delay 002b27cc */ set(3,cpu(4));if(taken){goto L_002b2790;}}
L_002b27d0:;
/* 002b27d0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002b27d4: addiu v0,v0,-0x6bd8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff9428)));
L_002b27d8:;
/* 002b27d8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b27dc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b27e0: jr ra */ {uint64_t target=cpu(31);/* delay 002b27e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint32_t nocturneObjectAttachmentBody(uint32_t entry){switch(entry){
case UINT32_C(0x00110408):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_00110408();return 1u;case UINT32_C(0x001dd7a8):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_001dd7a8();return 1u;case UINT32_C(0x002b2688):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_002b2688();return 1u;case UINT32_C(0x002b2748):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_002b2748();return 1u;
default:return 0u;}}

void ps2ObjectBaseAttachModel_00110408(uint64_t a0,uint64_t a1,uint64_t a2){
set(4u,a0);
set(5u,a1);
set(6u,a2);
body_00110408();
return;
}

void ps2ObjectAttachmentGetScale_001DD7A8(uint64_t a0){
set(4u,a0);
body_001dd7a8();
return;
}

uint64_t ps2ModelFindNodeId_002B2688(uint64_t a0,uint64_t a1){
set(4u,a0);
set(5u,a1);
body_002b2688();
return cpu(2);
}

uint64_t ps2ModelGetNodeName_002B2748(uint64_t a0,uint64_t a1){
set(4u,a0);
set(5u,a1);
body_002b2748();
return cpu(2);
}
