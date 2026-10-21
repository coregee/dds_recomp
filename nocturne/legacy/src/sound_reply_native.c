/* Whole139-member original2C2338 reply callback.
 * Unlinked source candidate. Real DMA/cache completion remains external.
 * Every scalar write preserves the physical destination upper64. */
#include "sound_reply_native.h"
#include <stdlib.h>
#include <string.h>
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned reg){uint32_t q[4];if(!reg)return 0;nocturneBattlePanelColorCpuRead(reg,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned reg,uint64_t v){uint32_t q[4];if(!reg)return;nocturneBattlePanelColorCpuRead(reg,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneBattlePanelColorCpuWrite(reg,q);if(reg==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned reg,int32_t o){return (uint32_t)cpu(reg)+(uint32_t)o;}
static void *at(uint32_t a){void *p=nocturneResolveBattlePanelColorAddress(a);if(!p)abort();return p;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void save(unsigned reg,uint32_t a){uint64_t v=cpu(reg);memcpy(at(a),&v,8);}
static void restore(unsigned reg,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(reg,v);}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}

static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint8_t byte(uint32_t a){return *(const uint8_t *)at(a);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}

static void body_002c2338(void){
uint64_t incoming=cpu(31);
/* 002c2338: addiu sp,sp,-0x120 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffee0)));
/* 002c233c: sltiu v0,a0,0x9 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002c2340: sd s0,0x100(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 002c2344: move a3,a1 */ set(7,cpu(5));
/* 002c2348: sd s1,0x108(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000108)));
/* 002c234c: beq v0,zero,0x002c2560 */ {int taken=(cpu(2)==cpu(0));/* delay 002c2350 */ save(31,ea(29,(int32_t)UINT32_C(0x00000110)));if(taken){goto L_002c2560;}}
/* 002c2354: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 002c2358: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002c235c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002c2360: lw v1,-0x6520(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffff9ae0)));
/* 002c2364: jr v1 */ {uint64_t target=cpu(3);/* delay 002c2368 */ switch(target){case UINT64_C(0x002c2370):goto L_002c2370;case UINT64_C(0x002c23f0):goto L_002c23f0;case UINT64_C(0x002c2450):goto L_002c2450;case UINT64_C(0x002c2480):goto L_002c2480;case UINT64_C(0x002c2490):goto L_002c2490;case UINT64_C(0x002c24d0):goto L_002c24d0;case UINT64_C(0x002c24e0):goto L_002c24e0;case UINT64_C(0x002c2500):goto L_002c2500;case UINT64_C(0x002c2550):goto L_002c2550;default:nocturneSoundReplyNativeUnprovidedJump(target,UINT32_C(0x002c2364));}}
L_002c2370:;
/* 002c2370: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002c2374: addiu a1,v0,-0x6418 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0xffff9be8)));
/* 002c2378: lb v1,0x0(a1) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002c237c: beq v1,zero,0x002c24d0 */ {int taken=(cpu(3)==cpu(0));/* delay 002c2380 */ set(4,cpu(29));if(taken){goto L_002c24d0;}}
/* 002c2384: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c2388: jal 0x002262e8 */ set(31,UINT64_C(0x002c2390));/* delay 002c238c */ sw(ea(28,(int32_t)UINT32_C(0xffffd858)),(uint32_t)cpu(2));nocturneSoundReplyNativeInvoke(UINT64_C(0x002262e8),UINT32_C(0x002c2388));
/* 002c2390: lui a1,0x2c */ set(5,sx(UINT32_C(0x002c0000)));
/* 002c2394: move a0,sp */ set(4,cpu(29));
/* 002c2398: addiu a1,a1,0x22e0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000022e0)));
/* 002c239c: jal 0x002bf3a8 */ set(31,UINT64_C(0x002c23a4));/* delay 002c23a0 */ set(6,cpu(0));nocturneSoundReplyNativeInvoke(UINT64_C(0x002bf3a8),UINT32_C(0x002c239c));
/* 002c23a4: move a0,v0 */ set(4,cpu(2));
/* 002c23a8: beq a0,zero,0x002c23e0 */ {int taken=(cpu(4)==cpu(0));/* delay 002c23ac */ sw(ea(28,(int32_t)UINT32_C(0xffffdfbc)),(uint32_t)cpu(4));if(taken){goto L_002c23e0;}}
/* 002c23b0: jal 0x002dbee0 */ set(31,UINT64_C(0x002c23b8));/* delay 002c23b4 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfd0)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002dbee0),UINT32_C(0x002c23b0));
/* 002c23b8: lw a0,-0x2044(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfbc)));
/* 002c23bc: lw v0,0x2c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000002c)));
/* 002c23c0: beq v0,zero,0x002c23e4 */ {int taken=(cpu(2)==cpu(0));/* delay 002c23c4 */ set(5,sx(UINT32_C(0x00590000)));if(taken){goto L_002c23e4;}}
/* 002c23c8: jal 0x002bf608 */ set(31,UINT64_C(0x002c23d0));/* delay 002c23cc */ nocturneSoundReplyNativeInvoke(UINT64_C(0x002bf608),UINT32_C(0x002c23c8));
/* 002c23d0: jal 0x002bf688 */ set(31,UINT64_C(0x002c23d8));/* delay 002c23d4 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfbc)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002bf688),UINT32_C(0x002c23d0));
/* 002c23d8: sw zero,-0x2044(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdfbc)),(uint32_t)cpu(0));
/* 002c23dc: move a0,zero */ set(4,cpu(0));
L_002c23e0:;
/* 002c23e0: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
L_002c23e4:;
/* 002c23e4: b 0x002c2564 */ /* delay 002c23e8 */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(4));goto L_002c2564;
L_002c23f0:;
/* 002c23f0: lw a0,0xc(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x0000000c)));
/* 002c23f4: jal 0x002a9038 */ set(31,UINT64_C(0x002c23fc));/* delay 002c23f8 */ sw(ea(28,(int32_t)UINT32_C(0xffffdfb4)),(uint32_t)cpu(7));nocturneSoundReplyNativeInvoke(UINT64_C(0x002a9038),UINT32_C(0x002c23f4));
/* 002c23fc: move s1,v0 */ set(17,cpu(2));
/* 002c2400: jal 0x002a9688 */ set(31,UINT64_C(0x002c2408));/* delay 002c2404 */ set(4,cpu(17));nocturneSoundReplyNativeInvoke(UINT64_C(0x002a9688),UINT32_C(0x002c2400));
/* 002c2408: move s0,v0 */ set(16,cpu(2));
/* 002c240c: beq s0,zero,0x002c24d0 */ {int taken=(cpu(16)==cpu(0));/* delay 002c2410 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdfb4)));if(taken){goto L_002c24d0;}}
/* 002c2414: move a1,s0 */ set(5,cpu(16));
/* 002c2418: lw a0,-0x2044(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfbc)));
/* 002c241c: jal 0x002bf548 */ set(31,UINT64_C(0x002c2424));/* delay 002c2420 */ lw(6,ea(2,(int32_t)UINT32_C(0x0000000c)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002bf548),UINT32_C(0x002c241c));
/* 002c2424: jal 0x002dbee0 */ set(31,UINT64_C(0x002c242c));/* delay 002c2428 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfd0)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002dbee0),UINT32_C(0x002c2424));
/* 002c242c: lw v1,-0x204c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffdfb4)));
/* 002c2430: move a1,s0 */ set(5,cpu(16));
/* 002c2434: lw a0,0x8(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 002c2438: jal 0x002c1278 */ set(31,UINT64_C(0x002c2440));/* delay 002c243c */ lw(6,ea(3,(int32_t)UINT32_C(0x0000000c)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002c1278),UINT32_C(0x002c2438));
/* 002c2440: jal 0x002a9558 */ set(31,UINT64_C(0x002c2448));/* delay 002c2444 */ set(4,cpu(17));nocturneSoundReplyNativeInvoke(UINT64_C(0x002a9558),UINT32_C(0x002c2440));
/* 002c2448: b 0x002c252c */ /* delay 002c244c */ set(5,sx(UINT32_C(0x00590000)));goto L_002c252c;
L_002c2450:;
/* 002c2450: jal 0x002bf638 */ set(31,UINT64_C(0x002c2458));/* delay 002c2454 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfbc)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002bf638),UINT32_C(0x002c2450));
/* 002c2458: jal 0x002dbee0 */ set(31,UINT64_C(0x002c2460));/* delay 002c245c */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfd0)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002dbee0),UINT32_C(0x002c2458));
/* 002c2460: jal 0x002bf688 */ set(31,UINT64_C(0x002c2468));/* delay 002c2464 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfbc)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002bf688),UINT32_C(0x002c2460));
/* 002c2468: sw zero,-0x2044(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdfbc)),(uint32_t)cpu(0));
/* 002c246c: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
/* 002c2470: sw zero,-0x27a8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd858)),(uint32_t)cpu(0));
/* 002c2474: b 0x002c2564 */ /* delay 002c2478 */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(0));goto L_002c2564;
L_002c2480:;
/* 002c2480: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
/* 002c2484: sw zero,-0x2048(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdfb8)),(uint32_t)cpu(0));
/* 002c2488: b 0x002c2564 */ /* delay 002c248c */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(0));goto L_002c2564;
L_002c2490:;
/* 002c2490: lui v0,0x59 */ set(2,sx(UINT32_C(0x00590000)));
/* 002c2494: lw v1,-0x2048(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffdfb8)));
/* 002c2498: lw a1,0x3f28(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00003f28)));
/* 002c249c: lw a0,0x8(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 002c24a0: lw a2,0xc(a3) */ lw(6,ea(7,(int32_t)UINT32_C(0x0000000c)));
/* 002c24a4: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 002c24a8: jal 0x002c1278 */ set(31,UINT64_C(0x002c24b0));/* delay 002c24ac */ sw(ea(28,(int32_t)UINT32_C(0xffffdfb4)),(uint32_t)cpu(7));nocturneSoundReplyNativeInvoke(UINT64_C(0x002c1278),UINT32_C(0x002c24a8));
/* 002c24b0: lw a0,-0x204c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfb4)));
/* 002c24b4: lw v0,-0x2048(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdfb8)));
/* 002c24b8: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
/* 002c24bc: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002c24c0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002c24c4: sw v1,0x3f40(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(3));
/* 002c24c8: b 0x002c2564 */ /* delay 002c24cc */ sw(ea(28,(int32_t)UINT32_C(0xffffdfb8)),(uint32_t)cpu(2));goto L_002c2564;
L_002c24d0:;
/* 002c24d0: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
/* 002c24d4: b 0x002c2564 */ /* delay 002c24d8 */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(0));goto L_002c2564;
L_002c24e0:;
/* 002c24e0: lw v1,-0x27ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd854)));
/* 002c24e4: beq v1,zero,0x002c24f0 */ {int taken=(cpu(3)==cpu(0));/* delay 002c24e8 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002c24f0;}}
/* 002c24ec: sw v0,-0x27a4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd85c)),(uint32_t)cpu(2));
L_002c24f0:;
/* 002c24f0: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
/* 002c24f4: b 0x002c2564 */ /* delay 002c24f8 */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(3));goto L_002c2564;
L_002c2500:;
/* 002c2500: sw a3,-0x204c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdfb4)),(uint32_t)cpu(7));
/* 002c2504: lw v0,-0x27ac(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd854)));
/* 002c2508: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002c2510));/* delay 002c250c */ lw(4,ea(7,(int32_t)UINT32_C(0x0000000c)));nocturneSoundReplyNativeInvoke(target,UINT32_C(0x002c2508));}
/* 002c2510: move a1,v0 */ set(5,cpu(2));
/* 002c2514: beq a1,zero,0x002c2540 */ {int taken=(cpu(5)==cpu(0));/* delay 002c2518 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdfb4)));if(taken){goto L_002c2540;}}
/* 002c251c: lw a2,0xc(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002c2520: jal 0x002c1278 */ set(31,UINT64_C(0x002c2528));/* delay 002c2524 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));nocturneSoundReplyNativeInvoke(UINT64_C(0x002c1278),UINT32_C(0x002c2520));
/* 002c2528: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
L_002c252c:;
/* 002c252c: lw v0,-0x204c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdfb4)));
/* 002c2530: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002c2534: b 0x002c2564 */ /* delay 002c2538 */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(3));goto L_002c2564;
L_002c2540:;
/* 002c2540: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
/* 002c2544: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002c2548: b 0x002c2564 */ /* delay 002c254c */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(2));goto L_002c2564;
L_002c2550:;
/* 002c2550: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
/* 002c2554: sw zero,-0x27a4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd85c)),(uint32_t)cpu(0));
/* 002c2558: b 0x002c2564 */ /* delay 002c255c */ sw(ea(5,(int32_t)UINT32_C(0x00003f40)),(uint32_t)cpu(0));goto L_002c2564;
L_002c2560:;
/* 002c2560: lui a1,0x59 */ set(5,sx(UINT32_C(0x00590000)));
L_002c2564:;
/* 002c2564: ld s0,0x100(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 002c2568: addiu v0,a1,0x3f40 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00003f40)));
/* 002c256c: ld s1,0x108(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000108)));
/* 002c2570: ld ra,0x110(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000110)));
/* 002c2574: jr ra */ {uint64_t target=cpu(31);/* delay 002c2578 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000120)));checkReturn(target,incoming);return;}
}
uint32_t nocturneSoundReplyNativeBody(uint32_t entry){if(entry!=UINT32_C(0x002c2338))return 0u;if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c2338();return 1u;}
uint64_t ps2SoundRpcReplyNative_002C2338(uint64_t command,uint64_t request){set(4,command);set(5,request);if(!nocturneSoundReplyNativeBody(UINT32_C(0x002c2338)))abort();return cpu(2);}
