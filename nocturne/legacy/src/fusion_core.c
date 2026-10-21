/* Complete29 SLUS_209.11 fusion algorithms/1790 native instructions.
 * Fixed original-PC C control, local semantic values, real typed prerequisites.
 * Guest-backed temporary objects retain actual addresses/alias/call ordering.
 * This is not a shared CPU bank or full volatile/private-frame contract.
 */
#include "fusion_core.h"
#include "nocturne.h"
#include "ee_fpu.h"

#include "exp.h"
#include "fusion_accident.h"
#include "fusion_sort.h"
#include "inheritance_queries.h"
#include "libc_printf.h"
#include "rst_rng_frontier.h"
#include "rst_stats.h"
#include "stat_neighbors.h"
#include "unit_batch.h"
#include "unit_neighbors.h"
#include <string.h>
typedef struct FusionValues {uint64_t r[32],lo,hi;uint32_t f[32],condition;} FusionValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveFusionCoreAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint32_t le_single(uint32_t a,uint32_t b){
 /* Original sole use compares locally derived finite nonnegative EXP*1.5
  * against2^31. Raw sign/order also retains signed-zero comparison. */
 if(((a|b)&UINT32_C(0x7fffffff))==0)return 1;
 if((a^b)&UINT32_C(0x80000000))return a>>31;
 return (a>>31)?a>=b:a<=b;
}
#define A0 c->r[4]
#define A1 c->r[5]
#define UNIT(v) ((datUnitWork_PS2 *)at((uint32_t)(v)))

static void body_001fd498(FusionValues *c);
static void body_001fd4e0(FusionValues *c);
static void body_001fd538(FusionValues *c);
static void body_001fd610(FusionValues *c);
static void body_001fd708(FusionValues *c);
static void body_001fd730(FusionValues *c);
static void body_001fd878(FusionValues *c);
static void body_001fda08(FusionValues *c);
static void body_001fdac0(FusionValues *c);
static void body_001fdca0(FusionValues *c);
static void body_001fdd18(FusionValues *c);
static void body_001fdde8(FusionValues *c);
static void body_001fdec0(FusionValues *c);
static void body_001fdf78(FusionValues *c);
static void body_001fe170(FusionValues *c);
static void body_001fe1a0(FusionValues *c);
static void body_001fe280(FusionValues *c);
static void body_001fe5f0(FusionValues *c);
static void body_001fe690(FusionValues *c);
static void body_001fe880(FusionValues *c);
static void body_001fea20(FusionValues *c);
static void body_001feb28(FusionValues *c);
static void body_001fec40(FusionValues *c);
static void body_001fec68(FusionValues *c);
static void body_001ff428(FusionValues *c);
static void body_001ff4d0(FusionValues *c);
static void body_001ff648(FusionValues *c);
static void body_001ff758(FusionValues *c);
static void body_001ff790(FusionValues *c);

static void body_001fd498(FusionValues *c){
/* 001fd498: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fd49c: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fd4a0: addiu a1,v0,-0x2448 */ c->r[5]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdbb8));
/* 001fd4a4: move v1,zero */ c->r[3]=c->r[0];
/* 001fd4a8: lhu v0,0x0(a1) */ c->r[2]=hword((uint32_t)c->r[5]+UINT32_C(0x00000000));
/* 001fd4ac: nop  */ (void)0;
L_001fd4b0:;
/* 001fd4b0: bne v0,a0,0x001fd4c8 */ {int taken=(c->r[2]!=c->r[4]);/* delay 001fd4b4 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000008));if(taken){goto L_001fd4c8;}}
/* 001fd4b8: sll v0,v1,0x18 */ c->r[2]=sx((uint32_t)c->r[3]<<24u);
/* 001fd4bc: jr ra */ /* delay 001fd4c0 */ c->r[2]=sar((uint32_t)c->r[2],24u);return;
L_001fd4c8:;
/* 001fd4c8: addiu v1,v1,0x1 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 001fd4cc: sltiu v0,v1,0x4 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000004)));
/* 001fd4d0: bnel v0,zero,0x001fd4b0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001fd4d4 */ c->r[2]=hword((uint32_t)c->r[5]+UINT32_C(0x00000000));goto L_001fd4b0;}}
/* 001fd4d8: jr ra */ /* delay 001fd4dc */ c->r[2]=sx(UINT32_C(0xffffffff));return;
}

static void body_001fd4e0(FusionValues *c){
/* 001fd4e0: andi a3,a3,0xff */ c->r[7]=c->r[7]&UINT64_C(0xff);
/* 001fd4e4: li v1,0x64 */ c->r[3]=sx(UINT32_C(0x00000064));
/* 001fd4e8: mult a3,a0,a3 */ {int64_t p=(int64_t)(int32_t)(uint32_t)c->r[4]*(int64_t)(int32_t)(uint32_t)c->r[7];c->lo=sx((uint32_t)(uint64_t)p);c->hi=sx((uint32_t)((uint64_t)p>>32));c->r[7]=c->lo;}
/* 001fd4ec: move t2,a1 */ c->r[10]=c->r[5];
/* 001fd4f0: addiu t1,t2,0x1 */ c->r[9]=sx((uint32_t)c->r[10]+UINT32_C(0x00000001));
/* 001fd4f4: beql v1,zero,0x001fd4fc */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 001fd4f8 */ nocturne_break(7);goto L_001fd4fc;}}
L_001fd4fc:;
/* 001fd4fc: sll t0,a0,0x1 */ c->r[8]=sx((uint32_t)c->r[4]<<1u);
/* 001fd500: subu v0,a2,a0 */ c->r[2]=sx((uint32_t)c->r[6]-(uint32_t)c->r[4]);
/* 001fd504: div a3,v1 */ {int32_t n=(int32_t)(uint32_t)c->r[7],d=(int32_t)(uint32_t)c->r[3];if(d==0){c->lo=n<0?UINT64_C(1):UINT64_MAX;c->hi=sx((uint32_t)n);}else if(n==INT32_MIN&&d==-1){c->lo=sx(UINT32_C(0x80000000));c->hi=0;}else{c->lo=sx((uint32_t)(n/d));c->hi=sx((uint32_t)(n%d));}}
/* 001fd508: mflo a3 */ c->r[7]=c->lo;
/* 001fd50c: subu a3,a3,a0 */ c->r[7]=sx((uint32_t)c->r[7]-(uint32_t)c->r[4]);
/* 001fd510: addu v1,t2,a3 */ c->r[3]=sx((uint32_t)c->r[10]+(uint32_t)c->r[7]);
/* 001fd514: move t2,t1 */ c->r[10]=c->r[9];
/* 001fd518: movn t2,v1,a3 */ if(c->r[7]!=0){c->r[10]=c->r[3];}
/* 001fd51c: addu a1,a0,t2 */ c->r[5]=sx((uint32_t)c->r[4]+(uint32_t)c->r[10]);
/* 001fd520: slt t0,t0,a1 */ c->r[8]=less(c->r[8],c->r[5]);
/* 001fd524: movn t2,a0,t0 */ if(c->r[8]!=0){c->r[10]=c->r[4];}
/* 001fd528: addu a0,a0,t2 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[10]);
/* 001fd52c: slt a2,a2,a0 */ c->r[6]=less(c->r[6],c->r[4]);
/* 001fd530: jr ra */ /* delay 001fd534 */ if(c->r[6]==0){c->r[2]=c->r[10];}return;
}

static void body_001fd538(FusionValues *c){
/* 001fd538: addiu sp,sp,-0x40 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffc0));
/* 001fd53c: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fd540: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001fd544: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001fd548: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001fd54c: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 001fd550: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 001fd554: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 001fd558: sd ra,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[31]);
/* 001fd55c: jal 0x001fd498 */ c->r[31]=UINT64_C(0x001fd564);/* delay 001fd560 */ c->r[16]=c->r[5];body_001fd498(c);
/* 001fd564: move v1,v0 */ c->r[3]=c->r[2];
/* 001fd568: bltz v1,0x001fd5ec */ {int taken=(neg(c->r[3]));/* delay 001fd56c */ c->r[2]=c->r[0];if(taken){goto L_001fd5ec;}}
/* 001fd570: sll v0,v1,0x3 */ c->r[2]=sx((uint32_t)c->r[3]<<3u);
/* 001fd574: addiu s5,s0,0xa */ c->r[21]=sx((uint32_t)c->r[16]+UINT32_C(0x0000000a));
/* 001fd578: lui at,0x33 */ c->r[1]=sx(UINT32_C(0x00330000));
/* 001fd57c: addiu at,at,-0x2448 */ c->r[1]=sx((uint32_t)c->r[1]+UINT32_C(0xffffdbb8));
/* 001fd580: addu v0,at,v0 */ c->r[2]=sx((uint32_t)c->r[1]+(uint32_t)c->r[2]);
/* 001fd584: addiu s4,s0,0x6 */ c->r[20]=sx((uint32_t)c->r[16]+UINT32_C(0x00000006));
/* 001fd588: lbu s3,0x6(v0) */ c->r[19]=*at((uint32_t)c->r[2]+UINT32_C(0x00000006));
/* 001fd58c: addiu s1,v0,0x2 */ c->r[17]=sx((uint32_t)c->r[2]+UINT32_C(0x00000002));
/* 001fd590: li s2,0x1 */ c->r[18]=sx(UINT32_C(0x00000001));
/* 001fd594: lb v0,0x0(s1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[17]+UINT32_C(0x00000000)));
L_001fd598:;
/* 001fd598: addiu s1,s1,0x2 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000002));
/* 001fd59c: blez v0,0x001fd5dc */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 001fd5a0 */ c->r[3]=less(c->r[2],sx(UINT32_C(0x00000007)));if(taken){goto L_001fd5dc;}}
/* 001fd5a4: beql v1,zero,0x001fd5e0 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 001fd5a8 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0xffffffff));goto L_001fd5e0;}}
/* 001fd5ac: addiu v0,v0,-0x1 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffffff));
/* 001fd5b0: li a2,0x28 */ c->r[6]=sx(UINT32_C(0x00000028));
/* 001fd5b4: sll v0,v0,0x18 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);
/* 001fd5b8: move a3,s3 */ c->r[7]=c->r[19];
/* 001fd5bc: sra v0,v0,0x18 */ c->r[2]=sar((uint32_t)c->r[2],24u);
/* 001fd5c0: addiu s0,v0,0x70 */ c->r[16]=sx((uint32_t)c->r[2]+UINT32_C(0x00000070));
/* 001fd5c4: addu v0,v0,s4 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[20]);
/* 001fd5c8: addu s0,s5,s0 */ c->r[16]=sx((uint32_t)c->r[21]+(uint32_t)c->r[16]);
/* 001fd5cc: lb a0,0x10(v0) */ c->r[4]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000010)));
/* 001fd5d0: jal 0x001fd4e0 */ c->r[31]=UINT64_C(0x001fd5d8);/* delay 001fd5d4 */ c->r[5]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000000)));body_001fd4e0(c);
/* 001fd5d8: sb v0,0x0(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x00000000))=(uint8_t)c->r[2];
L_001fd5dc:;
/* 001fd5dc: addiu s2,s2,-0x1 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0xffffffff));
L_001fd5e0:;
/* 001fd5e0: bgezl s2,0x001fd598 */ {int taken=(!neg(c->r[18]));if(taken){/* delay 001fd5e4 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[17]+UINT32_C(0x00000000)));goto L_001fd598;}}
/* 001fd5e8: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_001fd5ec:;
/* 001fd5ec: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fd5f0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001fd5f4: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fd5f8: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fd5fc: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001fd600: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001fd604: ld ra,0x30(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fd608: jr ra */ /* delay 001fd60c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000040));return;
}

static void body_001fd610(FusionValues *c){
/* 001fd610: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fd614: andi a1,a1,0xffff */ c->r[5]=c->r[5]&UINT64_C(0xffff);
/* 001fd618: andi a2,a2,0xffff */ c->r[6]=c->r[6]&UINT64_C(0xffff);
/* 001fd61c: sll a3,a0,0x4 */ c->r[7]=sx((uint32_t)c->r[4]<<4u);
/* 001fd620: sll t0,a1,0x4 */ c->r[8]=sx((uint32_t)c->r[5]<<4u);
/* 001fd624: sll v0,a2,0x4 */ c->r[2]=sx((uint32_t)c->r[6]<<4u);
/* 001fd628: subu a3,a3,a0 */ c->r[7]=sx((uint32_t)c->r[7]-(uint32_t)c->r[4]);
/* 001fd62c: subu t0,t0,a1 */ c->r[8]=sx((uint32_t)c->r[8]-(uint32_t)c->r[5]);
/* 001fd630: subu v0,v0,a2 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[6]);
/* 001fd634: lui v1,0x35 */ c->r[3]=sx(UINT32_C(0x00350000));
/* 001fd638: addiu v1,v1,-0x6840 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffff97c0));
/* 001fd63c: sll a3,a3,0x2 */ c->r[7]=sx((uint32_t)c->r[7]<<2u);
/* 001fd640: sll t0,t0,0x2 */ c->r[8]=sx((uint32_t)c->r[8]<<2u);
/* 001fd644: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001fd648: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 001fd64c: addu t0,t0,v1 */ c->r[8]=sx((uint32_t)c->r[8]+(uint32_t)c->r[3]);
/* 001fd650: addu a3,a3,v1 */ c->r[7]=sx((uint32_t)c->r[7]+(uint32_t)c->r[3]);
/* 001fd654: lbu a0,0x4(v0) */ c->r[4]=*at((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fd658: lbu a1,0x4(t0) */ c->r[5]=*at((uint32_t)c->r[8]+UINT32_C(0x00000004));
/* 001fd65c: move t0,zero */ c->r[8]=c->r[0];
/* 001fd660: lbu v1,0x4(a3) */ c->r[3]=*at((uint32_t)c->r[7]+UINT32_C(0x00000004));
/* 001fd664: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 001fd668: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fd66c: sb a1,0x1(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[5];
/* 001fd670: sb v1,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[3];
/* 001fd674: addiu t2,v0,-0x2428 */ c->r[10]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdbd8));
/* 001fd678: sb a0,0x2(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000002))=(uint8_t)c->r[4];
/* 001fd67c: move t1,a0 */ c->r[9]=c->r[4];
L_001fd680:;
/* 001fd680: lbu a1,0x1(sp) */ c->r[5]=*at((uint32_t)c->r[29]+UINT32_C(0x00000001));
/* 001fd684: move a0,zero */ c->r[4]=c->r[0];
/* 001fd688: lbu a3,0x0(sp) */ c->r[7]=*at((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fd68c: addiu v1,t2,0x3 */ c->r[3]=sx((uint32_t)c->r[10]+UINT32_C(0x00000003));
/* 001fd690: andi a2,a1,0xff */ c->r[6]=c->r[5]&UINT64_C(0xff);
/* 001fd694: nop  */ (void)0;
L_001fd698:;
/* 001fd698: lbu v0,-0x3(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0xfffffffd));
/* 001fd69c: bnel v0,a3,0x001fd6c8 */ {int taken=(c->r[2]!=c->r[7]);if(taken){/* delay 001fd6a0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));goto L_001fd6c8;}}
/* 001fd6a4: lbu v0,-0x2(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0xfffffffe));
/* 001fd6a8: bnel v0,a2,0x001fd6c8 */ {int taken=(c->r[2]!=c->r[6]);if(taken){/* delay 001fd6ac */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));goto L_001fd6c8;}}
/* 001fd6b0: lbu v0,-0x1(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0xffffffff));
/* 001fd6b4: bnel v0,t1,0x001fd6c8 */ {int taken=(c->r[2]!=c->r[9]);if(taken){/* delay 001fd6b8 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));goto L_001fd6c8;}}
/* 001fd6bc: b 0x001fd6fc */ /* delay 001fd6c0 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000000)));goto L_001fd6fc;
L_001fd6c8:;
/* 001fd6c8: nop  */ (void)0;
/* 001fd6cc: nop  */ (void)0;
/* 001fd6d0: beq a0,zero,0x001fd698 */ {int taken=(c->r[4]==c->r[0]);/* delay 001fd6d4 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000004));if(taken){goto L_001fd698;}}
/* 001fd6d8: addiu v0,t0,0x1 */ c->r[2]=sx((uint32_t)c->r[8]+UINT32_C(0x00000001));
/* 001fd6dc: lbu v1,0x0(sp) */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fd6e0: sll v0,v0,0x18 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);
/* 001fd6e4: sb a1,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[5];
/* 001fd6e8: sra t0,v0,0x18 */ c->r[8]=sar((uint32_t)c->r[2],24u);
/* 001fd6ec: slti v0,t0,0x2 */ c->r[2]=less(c->r[8],sx(UINT32_C(0x00000002)));
/* 001fd6f0: bne v0,zero,0x001fd680 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd6f4 */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[3];if(taken){goto L_001fd680;}}
/* 001fd6f8: move v0,zero */ c->r[2]=c->r[0];
L_001fd6fc:;
/* 001fd6fc: jr ra */ /* delay 001fd700 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_001fd708(FusionValues *c){
/* 001fd708: li v0,0xc1 */ c->r[2]=sx(UINT32_C(0x000000c1));
/* 001fd70c: bne a2,v0,0x001fd724 */ {int taken=(c->r[6]!=c->r[2]);/* delay 001fd710 */ c->r[2]=c->r[0];if(taken){goto L_001fd724;}}
/* 001fd714: beq a0,a2,0x001fd724 */ {int taken=(c->r[4]==c->r[6]);/* delay 001fd718 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_001fd724;}}
/* 001fd71c: bnel a1,a2,0x001fd724 */ {int taken=(c->r[5]!=c->r[6]);if(taken){/* delay 001fd720 */ c->r[2]=c->r[0];goto L_001fd724;}}
L_001fd724:;
/* 001fd724: jr ra */ /* delay 001fd728 */ (void)0;return;
}

static void body_001fd730(FusionValues *c){
/* 001fd730: andi a2,a2,0xffff */ c->r[6]=c->r[6]&UINT64_C(0xffff);
/* 001fd734: addiu sp,sp,-0x60 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffa0));
/* 001fd738: sll v0,a2,0x4 */ c->r[2]=sx((uint32_t)c->r[6]<<4u);
/* 001fd73c: lui v1,0x35 */ c->r[3]=sx(UINT32_C(0x00350000));
/* 001fd740: subu v0,v0,a2 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[6]);
/* 001fd744: sd s6,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[22]);
/* 001fd748: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001fd74c: sd s0,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[16]);
/* 001fd750: addiu s6,v1,-0x6840 */ c->r[22]=sx((uint32_t)c->r[3]+UINT32_C(0xffff97c0));
/* 001fd754: lui v1,0x33 */ c->r[3]=sx(UINT32_C(0x00330000));
/* 001fd758: sd s1,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[17]);
/* 001fd75c: sd s4,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[20]);
/* 001fd760: sd ra,0x58(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000058),c->r[31]);
/* 001fd764: sd s2,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[18]);
/* 001fd768: andi s2,a1,0xffff */ c->r[18]=c->r[5]&UINT64_C(0xffff);
/* 001fd76c: sd s3,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[19]);
/* 001fd770: andi s3,a0,0xffff */ c->r[19]=c->r[4]&UINT64_C(0xffff);
/* 001fd774: sd s5,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[21]);
/* 001fd778: move s5,zero */ c->r[21]=c->r[0];
/* 001fd77c: sd s7,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[23]);
/* 001fd780: addu s7,v0,s6 */ c->r[23]=sx((uint32_t)c->r[2]+(uint32_t)c->r[22]);
/* 001fd784: sd s8,0x50(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000050),c->r[30]);
/* 001fd788: addiu s8,v1,-0x2370 */ c->r[30]=sx((uint32_t)c->r[3]+UINT32_C(0xffffdc90));
/* 001fd78c: nop  */ (void)0;
L_001fd790:;
/* 001fd790: lbu v1,0x4(s7) */ c->r[3]=*at((uint32_t)c->r[23]+UINT32_C(0x00000004));
/* 001fd794: sll v0,s2,0x4 */ c->r[2]=sx((uint32_t)c->r[18]<<4u);
/* 001fd798: subu v0,v0,s2 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[18]);
/* 001fd79c: move s4,zero */ c->r[20]=c->r[0];
/* 001fd7a0: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001fd7a4: sb v1,0x1(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[3];
/* 001fd7a8: addu v0,v0,s6 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[22]);
/* 001fd7ac: move s0,s8 */ c->r[16]=c->r[30];
/* 001fd7b0: lbu v1,0x4(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fd7b4: sb v1,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[3];
L_001fd7b8:;
/* 001fd7b8: lhu v0,0x0(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fd7bc: bnel v0,s3,0x001fd81c */ {int taken=(c->r[2]!=c->r[19]);if(taken){/* delay 001fd7c0 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));goto L_001fd81c;}}
/* 001fd7c4: lbu v1,0x2(s0) */ c->r[3]=*at((uint32_t)c->r[16]+UINT32_C(0x00000002));
/* 001fd7c8: lbu v0,0x0(sp) */ c->r[2]=*at((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fd7cc: bnel v1,v0,0x001fd81c */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 001fd7d0 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));goto L_001fd81c;}}
/* 001fd7d4: lbu v1,0x3(s0) */ c->r[3]=*at((uint32_t)c->r[16]+UINT32_C(0x00000003));
/* 001fd7d8: lbu v0,0x1(sp) */ c->r[2]=*at((uint32_t)c->r[29]+UINT32_C(0x00000001));
/* 001fd7dc: bnel v1,v0,0x001fd81c */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 001fd7e0 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));goto L_001fd81c;}}
/* 001fd7e4: lhu s1,0x4(s0) */ c->r[17]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));
/* 001fd7e8: jal 0x001fd3b0 */ c->r[31]=UINT64_C(0x001fd7f0);/* delay 001fd7ec */ c->r[4]=c->r[17];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentEventDisabled_001FD3B0(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fd7f0: move a0,s3 */ c->r[4]=c->r[19];
/* 001fd7f4: move a1,s2 */ c->r[5]=c->r[18];
/* 001fd7f8: bne v0,zero,0x001fd818 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd7fc */ c->r[6]=c->r[17];if(taken){goto L_001fd818;}}
/* 001fd800: jal 0x001fd708 */ c->r[31]=UINT64_C(0x001fd808);/* delay 001fd804 */ (void)0;body_001fd708(c);
/* 001fd808: bne v0,zero,0x001fd81c */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd80c */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));if(taken){goto L_001fd81c;}}
/* 001fd810: b 0x001fd844 */ /* delay 001fd814 */ c->r[2]=c->r[17];goto L_001fd844;
L_001fd818:;
/* 001fd818: addiu s4,s4,0x1 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));
L_001fd81c:;
/* 001fd81c: sltiu v0,s4,0x2 */ c->r[2]=(c->r[20]<sx(UINT32_C(0x00000002)));
/* 001fd820: bne v0,zero,0x001fd7b8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd824 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000006));if(taken){goto L_001fd7b8;}}
/* 001fd828: addiu s5,s5,0x1 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x00000001));
/* 001fd82c: andi v0,s3,0xff */ c->r[2]=c->r[19]&UINT64_C(0xff);
/* 001fd830: slti v1,s5,0x2 */ c->r[3]=less(c->r[21],sx(UINT32_C(0x00000002)));
/* 001fd834: move s3,s2 */ c->r[19]=c->r[18];
/* 001fd838: bne v1,zero,0x001fd790 */ {int taken=(c->r[3]!=c->r[0]);/* delay 001fd83c */ c->r[18]=c->r[2];if(taken){goto L_001fd790;}}
/* 001fd840: move v0,zero */ c->r[2]=c->r[0];
L_001fd844:;
/* 001fd844: ld s0,0x10(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fd848: ld s1,0x18(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fd84c: ld s2,0x20(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001fd850: ld s3,0x28(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001fd854: ld s4,0x30(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fd858: ld s5,0x38(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001fd85c: ld s6,0x40(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001fd860: ld s7,0x48(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 001fd864: ld s8,0x50(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000050));
/* 001fd868: ld ra,0x58(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000058));
/* 001fd86c: jr ra */ /* delay 001fd870 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000060));return;
}

static void body_001fd878(FusionValues *c){
/* 001fd878: addiu sp,sp,-0x60 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffa0));
/* 001fd87c: sll a3,a3,0x18 */ c->r[7]=sx((uint32_t)c->r[7]<<24u);
/* 001fd880: sd s3,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[19]);
/* 001fd884: move s3,zero */ c->r[19]=c->r[0];
/* 001fd888: sd s4,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[20]);
/* 001fd88c: move s4,a0 */ c->r[20]=c->r[4];
/* 001fd890: sd s5,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[21]);
/* 001fd894: move s5,a1 */ c->r[21]=c->r[5];
/* 001fd898: sd s6,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[22]);
/* 001fd89c: move s6,a2 */ c->r[22]=c->r[6];
/* 001fd8a0: sd s7,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[23]);
/* 001fd8a4: sll t0,t0,0x18 */ c->r[8]=sx((uint32_t)c->r[8]<<24u);
/* 001fd8a8: sd s8,0x50(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000050),c->r[30]);
/* 001fd8ac: sra s8,a3,0x18 */ c->r[30]=sar((uint32_t)c->r[7],24u);
/* 001fd8b0: sd s0,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[16]);
/* 001fd8b4: sra s7,t0,0x18 */ c->r[23]=sar((uint32_t)c->r[8],24u);
/* 001fd8b8: sd s1,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[17]);
/* 001fd8bc: sd s2,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[18]);
/* 001fd8c0: sd ra,0x58(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000058),c->r[31]);
/* 001fd8c4: lhu v0,0x4(s4) */ c->r[2]=hword((uint32_t)c->r[20]+UINT32_C(0x00000004));
/* 001fd8c8: lhu a1,0x4(s5) */ c->r[5]=hword((uint32_t)c->r[21]+UINT32_C(0x00000004));
/* 001fd8cc: lhu a0,0x4(s6) */ c->r[4]=hword((uint32_t)c->r[22]+UINT32_C(0x00000004));
/* 001fd8d0: sh v0,0x0(sp) */ sh((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint16_t)c->r[2]);
/* 001fd8d4: sh a1,0x2(sp) */ sh((uint32_t)c->r[29]+UINT32_C(0x00000002),(uint16_t)c->r[5]);
/* 001fd8d8: sh a0,0x4(sp) */ sh((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint16_t)c->r[4]);
/* 001fd8dc: nop  */ (void)0;
L_001fd8e0:;
/* 001fd8e0: lhu a1,0x2(sp) */ c->r[5]=hword((uint32_t)c->r[29]+UINT32_C(0x00000002));
/* 001fd8e4: move s2,zero */ c->r[18]=c->r[0];
/* 001fd8e8: lui s0,0x33 */ c->r[16]=sx(UINT32_C(0x00330000));
/* 001fd8ec: addiu s0,s0,-0x2420 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffdbe0));
L_001fd8f0:;
/* 001fd8f0: lhu v1,0x0(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fd8f4: lhu v0,0x0(sp) */ c->r[2]=hword((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fd8f8: bnel v1,v0,0x001fd934 */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 001fd8fc */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_001fd934;}}
/* 001fd900: lhu v0,0x2(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000002));
/* 001fd904: bnel v0,a1,0x001fd934 */ {int taken=(c->r[2]!=c->r[5]);if(taken){/* delay 001fd908 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_001fd934;}}
/* 001fd90c: lhu v1,0x4(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));
/* 001fd910: lhu v0,0x4(sp) */ c->r[2]=hword((uint32_t)c->r[29]+UINT32_C(0x00000004));
/* 001fd914: bnel v1,v0,0x001fd934 */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 001fd918 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_001fd934;}}
/* 001fd91c: lhu s1,0x6(s0) */ c->r[17]=hword((uint32_t)c->r[16]+UINT32_C(0x00000006));
/* 001fd920: jal 0x001fd3b0 */ c->r[31]=UINT64_C(0x001fd928);/* delay 001fd924 */ c->r[4]=c->r[17];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentEventDisabled_001FD3B0(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fd928: beq v0,zero,0x001fd9bc */ {int taken=(c->r[2]==c->r[0]);/* delay 001fd92c */ c->r[5]=hword((uint32_t)c->r[29]+UINT32_C(0x00000002));if(taken){goto L_001fd9bc;}}
/* 001fd930: addiu s2,s2,0x1 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));
L_001fd934:;
/* 001fd934: sltiu v0,s2,0x7 */ c->r[2]=(c->r[18]<sx(UINT32_C(0x00000007)));
/* 001fd938: bne v0,zero,0x001fd8f0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd93c */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000008));if(taken){goto L_001fd8f0;}}
/* 001fd940: lhu v1,0x0(sp) */ c->r[3]=hword((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fd944: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
/* 001fd948: slti v0,s3,0x2 */ c->r[2]=less(c->r[19],sx(UINT32_C(0x00000002)));
/* 001fd94c: sh a1,0x0(sp) */ sh((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint16_t)c->r[5]);
/* 001fd950: bne v0,zero,0x001fd8e0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd954 */ sh((uint32_t)c->r[29]+UINT32_C(0x00000002),(uint16_t)c->r[3]);if(taken){goto L_001fd8e0;}}
/* 001fd958: move a1,s5 */ c->r[5]=c->r[21];
/* 001fd95c: move a0,s4 */ c->r[4]=c->r[20];
/* 001fd960: move a2,s8 */ c->r[6]=c->r[30];
/* 001fd964: jal 0x001fe5f0 */ c->r[31]=UINT64_C(0x001fd96c);/* delay 001fd968 */ c->r[7]=c->r[23];body_001fe5f0(c);
/* 001fd96c: lhu a1,0x4(s6) */ c->r[5]=hword((uint32_t)c->r[22]+UINT32_C(0x00000004));
/* 001fd970: sh v0,0x0(sp) */ sh((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint16_t)c->r[2]);
/* 001fd974: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fd978: sh a1,0x2(sp) */ sh((uint32_t)c->r[29]+UINT32_C(0x00000002),(uint16_t)c->r[5]);
/* 001fd97c: addiu s0,v0,-0x23e8 */ c->r[16]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdc18));
/* 001fd980: move s2,zero */ c->r[18]=c->r[0];
/* 001fd984: nop  */ (void)0;
L_001fd988:;
/* 001fd988: lhu v1,0x0(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fd98c: lhu v0,0x0(sp) */ c->r[2]=hword((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fd990: bnel v1,v0,0x001fd9c8 */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 001fd994 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_001fd9c8;}}
/* 001fd998: lhu v1,0x2(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x00000002));
/* 001fd99c: lhu v0,0x2(sp) */ c->r[2]=hword((uint32_t)c->r[29]+UINT32_C(0x00000002));
/* 001fd9a0: bnel v1,v0,0x001fd9c8 */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 001fd9a4 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_001fd9c8;}}
/* 001fd9a8: lhu s1,0x4(s0) */ c->r[17]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));
/* 001fd9ac: jal 0x001fd3b0 */ c->r[31]=UINT64_C(0x001fd9b4);/* delay 001fd9b0 */ c->r[4]=c->r[17];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentEventDisabled_001FD3B0(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fd9b4: bne v0,zero,0x001fd9c8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd9b8 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));if(taken){goto L_001fd9c8;}}
L_001fd9bc:;
/* 001fd9bc: b 0x001fd9d8 */ /* delay 001fd9c0 */ c->r[2]=c->r[17];goto L_001fd9d8;
L_001fd9c8:;
/* 001fd9c8: sltiu v0,s2,0x13 */ c->r[2]=(c->r[18]<sx(UINT32_C(0x00000013)));
/* 001fd9cc: bne v0,zero,0x001fd988 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fd9d0 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000006));if(taken){goto L_001fd988;}}
/* 001fd9d4: move v0,zero */ c->r[2]=c->r[0];
L_001fd9d8:;
/* 001fd9d8: ld s0,0x10(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fd9dc: ld s1,0x18(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fd9e0: ld s2,0x20(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001fd9e4: ld s3,0x28(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001fd9e8: ld s4,0x30(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fd9ec: ld s5,0x38(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001fd9f0: ld s6,0x40(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001fd9f4: ld s7,0x48(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 001fd9f8: ld s8,0x50(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000050));
/* 001fd9fc: ld ra,0x58(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000058));
/* 001fda00: jr ra */ /* delay 001fda04 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000060));return;
}

static void body_001fda08(FusionValues *c){
/* 001fda08: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fda0c: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fda10: addiu v0,v0,-0x2420 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdbe0));
/* 001fda14: move a1,zero */ c->r[5]=c->r[0];
/* 001fda18: addiu a2,v0,0x6 */ c->r[6]=sx((uint32_t)c->r[2]+UINT32_C(0x00000006));
/* 001fda1c: lhu v1,0x0(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));
L_001fda20:;
/* 001fda20: addiu a2,a2,0x8 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000008));
/* 001fda24: beq a0,v1,0x001fdab8 */ {int taken=(c->r[4]==c->r[3]);/* delay 001fda28 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_001fdab8;}}
/* 001fda2c: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
/* 001fda30: sltiu v0,a1,0x7 */ c->r[2]=(c->r[5]<sx(UINT32_C(0x00000007)));
/* 001fda34: nop  */ (void)0;
/* 001fda38: nop  */ (void)0;
/* 001fda3c: bnel v0,zero,0x001fda20 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001fda40 */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));goto L_001fda20;}}
/* 001fda44: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fda48: move a1,zero */ c->r[5]=c->r[0];
/* 001fda4c: addiu v0,v0,-0x23e8 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdc18));
/* 001fda50: addiu a2,v0,0x4 */ c->r[6]=sx((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fda54: lhu v1,0x0(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));
L_001fda58:;
/* 001fda58: addiu a2,a2,0x6 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000006));
/* 001fda5c: beq a0,v1,0x001fdab8 */ {int taken=(c->r[4]==c->r[3]);/* delay 001fda60 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_001fdab8;}}
/* 001fda64: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
/* 001fda68: sltiu v0,a1,0x13 */ c->r[2]=(c->r[5]<sx(UINT32_C(0x00000013)));
/* 001fda6c: nop  */ (void)0;
/* 001fda70: nop  */ (void)0;
/* 001fda74: bnel v0,zero,0x001fda58 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001fda78 */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));goto L_001fda58;}}
/* 001fda7c: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fda80: move a1,zero */ c->r[5]=c->r[0];
/* 001fda84: addiu v0,v0,-0x2370 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdc90));
/* 001fda88: addiu a2,v0,0x4 */ c->r[6]=sx((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fda8c: lhu v1,0x0(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));
L_001fda90:;
/* 001fda90: addiu a2,a2,0x6 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000006));
/* 001fda94: beq a0,v1,0x001fdab8 */ {int taken=(c->r[4]==c->r[3]);/* delay 001fda98 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_001fdab8;}}
/* 001fda9c: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
/* 001fdaa0: sltiu v0,a1,0x2 */ c->r[2]=(c->r[5]<sx(UINT32_C(0x00000002)));
/* 001fdaa4: nop  */ (void)0;
/* 001fdaa8: nop  */ (void)0;
/* 001fdaac: bnel v0,zero,0x001fda90 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001fdab0 */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));goto L_001fda90;}}
/* 001fdab4: move v0,zero */ c->r[2]=c->r[0];
L_001fdab8:;
/* 001fdab8: jr ra */ /* delay 001fdabc */ (void)0;return;
}

static void body_001fdac0(FusionValues *c){
/* 001fdac0: addiu sp,sp,-0x80 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffff80));
/* 001fdac4: sd s0,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[16]);
/* 001fdac8: andi s0,a0,0xffff */ c->r[16]=c->r[4]&UINT64_C(0xffff);
/* 001fdacc: sd s1,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[17]);
/* 001fdad0: move s1,zero */ c->r[17]=c->r[0];
/* 001fdad4: sd s3,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[19]);
/* 001fdad8: li s3,-0x1 */ c->r[19]=sx(UINT32_C(0xffffffff));
/* 001fdadc: sd s4,0x50(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000050),c->r[20]);
/* 001fdae0: andi s4,a1,0xff */ c->r[20]=c->r[5]&UINT64_C(0xff);
/* 001fdae4: sd s5,0x58(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000058),c->r[21]);
/* 001fdae8: sll v1,s0,0x4 */ c->r[3]=sx((uint32_t)c->r[16]<<4u);
/* 001fdaec: sd s6,0x60(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000060),c->r[22]);
/* 001fdaf0: move s6,sp */ c->r[22]=c->r[29];
/* 001fdaf4: sd s8,0x70(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000070),c->r[30]);
/* 001fdaf8: move s8,sp */ c->r[30]=c->r[29];
/* 001fdafc: sd s2,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[18]);
/* 001fdb00: subu v1,v1,s0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[16]);
/* 001fdb04: sd s7,0x68(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000068),c->r[23]);
/* 001fdb08: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 001fdb0c: sd ra,0x78(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000078),c->r[31]);
/* 001fdb10: lw s2,-0x4258(gp) */ c->r[18]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffbda8)));
/* 001fdb14: lui at,0x35 */ c->r[1]=sx(UINT32_C(0x00350000));
/* 001fdb18: addu at,at,v1 */ c->r[1]=sx((uint32_t)c->r[1]+(uint32_t)c->r[3]);
/* 001fdb1c: lbu v1,-0x683c(at) */ c->r[3]=*at((uint32_t)c->r[1]+UINT32_C(0xffff97c4));
/* 001fdb20: sll v0,s2,0x3 */ c->r[2]=sx((uint32_t)c->r[18]<<3u);
/* 001fdb24: lhu a1,-0x4258(gp) */ c->r[5]=hword((uint32_t)c->r[28]+UINT32_C(0xffffbda8));
/* 001fdb28: addiu v0,v0,0xf */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x0000000f));
/* 001fdb2c: sw v1,0x0(s8) */ sw((uint32_t)c->r[30]+UINT32_C(0x00000000),(uint32_t)c->r[3]);
/* 001fdb30: srl v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]>>4u);
/* 001fdb34: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 001fdb38: subu sp,sp,v0 */ c->r[29]=sx((uint32_t)c->r[29]-(uint32_t)c->r[2]);
/* 001fdb3c: move a0,sp */ c->r[4]=c->r[29];
/* 001fdb40: jal 0x002133a0 */ c->r[31]=UINT64_C(0x001fdb48);/* delay 001fdb44 */ c->r[21]=c->r[29];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);ps2FusionSortDescriptors_002133A0(A0,A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fdb48: move a0,zero */ c->r[4]=c->r[0];
/* 001fdb4c: blez s2,0x001fdb94 */ {int taken=((neg(c->r[18])||!c->r[18]));/* delay 001fdb50 */ sw((uint32_t)c->r[30]+UINT32_C(0x00000004),(uint32_t)c->r[0]);if(taken){goto L_001fdb94;}}
/* 001fdb54: lhu v0,0x0(sp) */ c->r[2]=hword((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fdb58: bne v0,s0,0x001fdb68 */ {int taken=(c->r[2]!=c->r[16]);/* delay 001fdb5c */ c->r[5]=c->r[18];if(taken){goto L_001fdb68;}}
/* 001fdb60: b 0x001fdb94 */ /* delay 001fdb64 */ c->r[19]=c->r[0];goto L_001fdb94;
L_001fdb68:;
/* 001fdb68: addiu a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
L_001fdb6c:;
/* 001fdb6c: sll v0,a0,0x3 */ c->r[2]=sx((uint32_t)c->r[4]<<3u);
/* 001fdb70: slt v1,a0,a1 */ c->r[3]=less(c->r[4],c->r[5]);
/* 001fdb74: beq v1,zero,0x001fdb94 */ {int taken=(c->r[3]==c->r[0]);/* delay 001fdb78 */ c->r[2]=sx((uint32_t)c->r[21]+(uint32_t)c->r[2]);if(taken){goto L_001fdb94;}}
/* 001fdb7c: lhu v0,0x0(v0) */ c->r[2]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 001fdb80: nop  */ (void)0;
/* 001fdb84: nop  */ (void)0;
/* 001fdb88: bnel v0,s0,0x001fdb6c */ {int taken=(c->r[2]!=c->r[16]);if(taken){/* delay 001fdb8c */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));goto L_001fdb6c;}}
/* 001fdb90: move s3,a0 */ c->r[19]=c->r[4];
L_001fdb94:;
/* 001fdb94: bltzl s3,0x001fdc20 */ {int taken=(neg(c->r[19]));if(taken){/* delay 001fdb98 */ c->r[29]=c->r[22];goto L_001fdc20;}}
/* 001fdb9c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 001fdba0: beq s4,v0,0x001fdbd4 */ {int taken=(c->r[20]==c->r[2]);/* delay 001fdba4 */ c->r[2]=sx(UINT32_C(0xffffffff));if(taken){goto L_001fdbd4;}}
/* 001fdba8: slti v0,s4,0x2 */ c->r[2]=less(c->r[20],sx(UINT32_C(0x00000002)));
/* 001fdbac: beql v0,zero,0x001fdbc8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 001fdbb0 */ c->r[2]=sx(UINT32_C(0x00000002));goto L_001fdbc8;}}
/* 001fdbb4: beq s4,zero,0x001fdc1c */ {int taken=(c->r[20]==c->r[0]);/* delay 001fdbb8 */ c->r[23]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffbda8)));if(taken){goto L_001fdc1c;}}
/* 001fdbbc: b 0x001fdbe0 */ /* delay 001fdbc0 */ c->r[20]=sx((uint32_t)c->r[21]+UINT32_C(0x00000004));goto L_001fdbe0;
L_001fdbc8:;
/* 001fdbc8: bne s4,v0,0x001fdbdc */ {int taken=(c->r[20]!=c->r[2]);/* delay 001fdbcc */ c->r[23]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffbda8)));if(taken){goto L_001fdbdc;}}
/* 001fdbd0: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_001fdbd4:;
/* 001fdbd4: sw v0,0x4(s8) */ sw((uint32_t)c->r[30]+UINT32_C(0x00000004),(uint32_t)c->r[2]);
/* 001fdbd8: lw s7,-0x4258(gp) */ c->r[23]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffbda8)));
L_001fdbdc:;
/* 001fdbdc: addiu s4,s5,0x4 */ c->r[20]=sx((uint32_t)c->r[21]+UINT32_C(0x00000004));
L_001fdbe0:;
/* 001fdbe0: li s2,0x1 */ c->r[18]=sx(UINT32_C(0x00000001));
/* 001fdbe4: lw v0,0x4(s8) */ c->r[2]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000004)));
L_001fdbe8:;
/* 001fdbe8: addu s3,s3,v0 */ c->r[19]=sx((uint32_t)c->r[19]+(uint32_t)c->r[2]);
/* 001fdbec: sll v0,s3,0x3 */ c->r[2]=sx((uint32_t)c->r[19]<<3u);
/* 001fdbf0: slt v1,s3,s7 */ c->r[3]=less(c->r[19],c->r[23]);
/* 001fdbf4: addu s0,s5,v0 */ c->r[16]=sx((uint32_t)c->r[21]+(uint32_t)c->r[2]);
/* 001fdbf8: blez s3,0x001fdc1c */ {int taken=((neg(c->r[19])||!c->r[19]));/* delay 001fdbfc */ c->r[2]=sx((uint32_t)c->r[20]+(uint32_t)c->r[2]);if(taken){goto L_001fdc1c;}}
/* 001fdc00: beql v1,zero,0x001fdc20 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 001fdc04 */ c->r[29]=c->r[22];goto L_001fdc20;}}
/* 001fdc08: lw v0,0x0(v0) */ c->r[2]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 001fdc0c: lbu v1,0x4(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fdc10: lw v0,0x0(s8) */ c->r[2]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000000)));
/* 001fdc14: beq v0,v1,0x001fdc28 */ {int taken=(c->r[2]==c->r[3]);/* delay 001fdc18 */ (void)0;if(taken){goto L_001fdc28;}}
L_001fdc1c:;
/* 001fdc1c: move sp,s6 */ c->r[29]=c->r[22];
L_001fdc20:;
/* 001fdc20: b 0x001fdc68 */ /* delay 001fdc24 */ c->r[2]=c->r[0];goto L_001fdc68;
L_001fdc28:;
/* 001fdc28: jal 0x001fe280 */ c->r[31]=UINT64_C(0x001fdc30);/* delay 001fdc2c */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));body_001fe280(c);
/* 001fdc30: lhu a0,0x0(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fdc34: jal 0x001fda08 */ c->r[31]=UINT64_C(0x001fdc3c);/* delay 001fdc38 */ c->r[17]=(c->r[0]<c->r[2]);body_001fda08(c);
/* 001fdc3c: lhu a0,0x0(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fdc40: jal 0x001fd3b0 */ c->r[31]=UINT64_C(0x001fdc48);/* delay 001fdc44 */ if(c->r[2]!=0){c->r[17]=c->r[18];}nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentEventDisabled_001FD3B0(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fdc48: lhu a0,0x0(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fdc4c: jal 0x001fe2c8 */ c->r[31]=UINT64_C(0x001fdc54);/* delay 001fdc50 */ if(c->r[2]!=0){c->r[17]=c->r[18];}nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentMetaOnly_001FE2C8(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fdc54: movn s1,s2,v0 */ if(c->r[2]!=0){c->r[17]=c->r[18];}
/* 001fdc58: bne s1,zero,0x001fdbe8 */ {int taken=(c->r[17]!=c->r[0]);/* delay 001fdc5c */ c->r[2]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000004)));if(taken){goto L_001fdbe8;}}
/* 001fdc60: lhu v0,0x0(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fdc64: move sp,s6 */ c->r[29]=c->r[22];
L_001fdc68:;
/* 001fdc68: move sp,s8 */ c->r[29]=c->r[30];
/* 001fdc6c: ld s0,0x30(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fdc70: ld s1,0x38(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001fdc74: ld s2,0x40(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001fdc78: ld s3,0x48(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 001fdc7c: ld s4,0x50(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000050));
/* 001fdc80: ld s5,0x58(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000058));
/* 001fdc84: ld s6,0x60(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000060));
/* 001fdc88: ld s7,0x68(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000068));
/* 001fdc8c: ld s8,0x70(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000070));
/* 001fdc90: ld ra,0x78(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000078));
/* 001fdc94: jr ra */ /* delay 001fdc98 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000080));return;
}

static void body_001fdca0(FusionValues *c){
/* 001fdca0: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fdca4: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fdca8: addiu t0,v0,-0x2590 */ c->r[8]=sx((uint32_t)c->r[2]+UINT32_C(0xffffda70));
/* 001fdcac: andi a1,a1,0xff */ c->r[5]=c->r[5]&UINT64_C(0xff);
/* 001fdcb0: move a3,zero */ c->r[7]=c->r[0];
/* 001fdcb4: move t1,t0 */ c->r[9]=c->r[8];
L_001fdcb8:;
/* 001fdcb8: lhu v0,0x0(t0) */ c->r[2]=hword((uint32_t)c->r[8]+UINT32_C(0x00000000));
/* 001fdcbc: bne v0,a0,0x001fdd00 */ {int taken=(c->r[2]!=c->r[4]);/* delay 001fdcc0 */ c->r[3]=sx((uint32_t)c->r[7]<<5u);if(taken){goto L_001fdd00;}}
/* 001fdcc4: addu v0,v1,a3 */ c->r[2]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 001fdcc8: move a2,zero */ c->r[6]=c->r[0];
/* 001fdccc: sll v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]<<1u);
/* 001fdcd0: addu v0,v0,t1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[9]);
/* 001fdcd4: addiu v1,v0,0x3 */ c->r[3]=sx((uint32_t)c->r[2]+UINT32_C(0x00000003));
L_001fdcd8:;
/* 001fdcd8: lbu v0,-0x1(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0xffffffff));
/* 001fdcdc: bnel v0,a1,0x001fdcf0 */ {int taken=(c->r[2]!=c->r[5]);if(taken){/* delay 001fdce0 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));goto L_001fdcf0;}}
/* 001fdce4: jr ra */ /* delay 001fdce8 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000000)));return;
L_001fdcf0:;
/* 001fdcf0: slti v0,a2,0x20 */ c->r[2]=less(c->r[6],sx(UINT32_C(0x00000020)));
/* 001fdcf4: nop  */ (void)0;
/* 001fdcf8: bne v0,zero,0x001fdcd8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fdcfc */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000002));if(taken){goto L_001fdcd8;}}
L_001fdd00:;
/* 001fdd00: addiu a3,a3,0x1 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000001));
/* 001fdd04: sltiu v0,a3,0x4 */ c->r[2]=(c->r[7]<sx(UINT32_C(0x00000004)));
/* 001fdd08: bne v0,zero,0x001fdcb8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fdd0c */ c->r[8]=sx((uint32_t)c->r[8]+UINT32_C(0x00000042));if(taken){goto L_001fdcb8;}}
/* 001fdd10: jr ra */ /* delay 001fdd14 */ c->r[2]=sx(UINT32_C(0xffffffff));return;
}

static void body_001fdd18(FusionValues *c){
/* 001fdd18: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fdd1c: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fdd20: andi a1,a1,0xffff */ c->r[5]=c->r[5]&UINT64_C(0xffff);
/* 001fdd24: addiu t0,v0,-0x2470 */ c->r[8]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdb90));
/* 001fdd28: move t1,zero */ c->r[9]=c->r[0];
/* 001fdd2c: li t3,0x1 */ c->r[11]=sx(UINT32_C(0x00000001));
/* 001fdd30: li t2,0x2 */ c->r[10]=sx(UINT32_C(0x00000002));
/* 001fdd34: nop  */ (void)0;
L_001fdd38:;
/* 001fdd38: lhu a3,0x0(t0) */ c->r[7]=hword((uint32_t)c->r[8]+UINT32_C(0x00000000));
/* 001fdd3c: lhu a2,0x2(t0) */ c->r[6]=hword((uint32_t)c->r[8]+UINT32_C(0x00000002));
/* 001fdd40: xor v0,a3,a0 */ c->r[2]=c->r[7]^c->r[4];
/* 001fdd44: sltiu v0,v0,0x1 */ c->r[2]=(c->r[2]<sx(UINT32_C(0x00000001)));
/* 001fdd48: xor v1,a2,a0 */ c->r[3]=c->r[6]^c->r[4];
/* 001fdd4c: movz v0,t2,v1 */ if(c->r[3]==0){c->r[2]=c->r[10];}
/* 001fdd50: beq v0,t3,0x001fdd68 */ {int taken=(c->r[2]==c->r[11]);/* delay 001fdd54 */ (void)0;if(taken){goto L_001fdd68;}}
/* 001fdd58: beq v0,t2,0x001fdd78 */ {int taken=(c->r[2]==c->r[10]);/* delay 001fdd5c */ (void)0;if(taken){goto L_001fdd78;}}
/* 001fdd60: b 0x001fdd90 */ /* delay 001fdd64 */ c->r[9]=sx((uint32_t)c->r[9]+UINT32_C(0x00000001));goto L_001fdd90;
L_001fdd68:;
/* 001fdd68: bnel a2,a1,0x001fdd90 */ {int taken=(c->r[6]!=c->r[5]);if(taken){/* delay 001fdd6c */ c->r[9]=sx((uint32_t)c->r[9]+UINT32_C(0x00000001));goto L_001fdd90;}}
L_001fdd70:;
/* 001fdd70: jr ra */ /* delay 001fdd74 */ c->r[2]=hword((uint32_t)c->r[8]+UINT32_C(0x00000004));return;
L_001fdd78:;
/* 001fdd78: nop  */ (void)0;
/* 001fdd7c: nop  */ (void)0;
/* 001fdd80: nop  */ (void)0;
/* 001fdd84: beq a3,a1,0x001fdd70 */ {int taken=(c->r[7]==c->r[5]);/* delay 001fdd88 */ (void)0;if(taken){goto L_001fdd70;}}
/* 001fdd8c: addiu t1,t1,0x1 */ c->r[9]=sx((uint32_t)c->r[9]+UINT32_C(0x00000001));
L_001fdd90:;
/* 001fdd90: sltiu v0,t1,0x6 */ c->r[2]=(c->r[9]<sx(UINT32_C(0x00000006)));
/* 001fdd94: bne v0,zero,0x001fdd38 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fdd98 */ c->r[8]=sx((uint32_t)c->r[8]+UINT32_C(0x00000006));if(taken){goto L_001fdd38;}}
/* 001fdd9c: jr ra */ /* delay 001fdda0 */ c->r[2]=c->r[0];return;
}

static void body_001fdde8(FusionValues *c){
/* 001fdde8: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fddec: andi a1,a1,0xffff */ c->r[5]=c->r[5]&UINT64_C(0xffff);
/* 001fddf0: sll v1,a0,0x4 */ c->r[3]=sx((uint32_t)c->r[4]<<4u);
/* 001fddf4: sll v0,a1,0x4 */ c->r[2]=sx((uint32_t)c->r[5]<<4u);
/* 001fddf8: subu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[4]);
/* 001fddfc: lui a3,0x35 */ c->r[7]=sx(UINT32_C(0x00350000));
/* 001fde00: subu v0,v0,a1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[5]);
/* 001fde04: li a1,0x26 */ c->r[5]=sx(UINT32_C(0x00000026));
/* 001fde08: addiu a3,a3,-0x6840 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0xffff97c0));
/* 001fde0c: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 001fde10: addu v1,v1,a3 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 001fde14: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001fde18: lbu a0,0x4(v1) */ c->r[4]=*at((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 001fde1c: addu v0,v0,a3 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[7]);
/* 001fde20: lbu v1,0x4(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fde24: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 001fde28: sll a2,a2,0x18 */ c->r[6]=sx((uint32_t)c->r[6]<<24u);
/* 001fde2c: move v0,a0 */ c->r[2]=c->r[4];
/* 001fde30: sb a0,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[4];
/* 001fde34: sra a2,a2,0x18 */ c->r[6]=sar((uint32_t)c->r[6],24u);
/* 001fde38: bne v0,a1,0x001fde48 */ {int taken=(c->r[2]!=c->r[5]);/* delay 001fde3c */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[3];if(taken){goto L_001fde48;}}
/* 001fde40: li v0,0x13 */ c->r[2]=sx(UINT32_C(0x00000013));
/* 001fde44: sb v0,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[2];
L_001fde48:;
/* 001fde48: lbu v1,0x1(sp) */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000001));
/* 001fde4c: bne v1,a1,0x001fde64 */ {int taken=(c->r[3]!=c->r[5]);/* delay 001fde50 */ c->r[4]=*at((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_001fde64;}}
/* 001fde54: li v0,0x13 */ c->r[2]=sx(UINT32_C(0x00000013));
/* 001fde58: li v1,0x13 */ c->r[3]=sx(UINT32_C(0x00000013));
/* 001fde5c: sb v0,0x1(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[2];
/* 001fde60: lbu a0,0x0(sp) */ c->r[4]=*at((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_001fde64:;
/* 001fde64: sltu v0,a0,v1 */ c->r[2]=(c->r[4]<c->r[3]);
/* 001fde68: beq v0,zero,0x001fde78 */ {int taken=(c->r[2]==c->r[0]);/* delay 001fde6c */ c->r[2]=*at((uint32_t)c->r[29]+UINT32_C(0x00000001));if(taken){goto L_001fde78;}}
/* 001fde70: sb a0,0x1(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[4];
/* 001fde74: sb v0,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[2];
L_001fde78:;
/* 001fde78: beq a2,zero,0x001fdea0 */ {int taken=(c->r[6]==c->r[0]);/* delay 001fde7c */ c->r[2]=*at((uint32_t)c->r[29]+UINT32_C(0x00000001));if(taken){goto L_001fdea0;}}
/* 001fde80: lbu v1,0x0(sp) */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fde84: sll v0,v0,0x5 */ c->r[2]=sx((uint32_t)c->r[2]<<5u);
/* 001fde88: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 001fde8c: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fde90: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 001fde94: lbu v0,-0x29b1(v0) */ c->r[2]=*at((uint32_t)c->r[2]+UINT32_C(0xffffd64f));
/* 001fde98: b 0x001fdeb8 */ /* delay 001fde9c */ (void)0;goto L_001fdeb8;
L_001fdea0:;
/* 001fdea0: lbu v1,0x0(sp) */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fdea4: sll v0,v0,0x5 */ c->r[2]=sx((uint32_t)c->r[2]<<5u);
/* 001fdea8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 001fdeac: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fdeb0: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 001fdeb4: lbu v0,-0x2db1(v0) */ c->r[2]=*at((uint32_t)c->r[2]+UINT32_C(0xffffd24f));
L_001fdeb8:;
/* 001fdeb8: jr ra */ /* delay 001fdebc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_001fdec0(FusionValues *c){
/* 001fdec0: sll a3,a3,0x18 */ c->r[7]=sx((uint32_t)c->r[7]<<24u);
/* 001fdec4: move v0,a1 */ c->r[2]=c->r[5];
/* 001fdec8: bne a3,zero,0x001fdf28 */ {int taken=(c->r[7]!=c->r[0]);/* delay 001fdecc */ c->r[8]=c->r[0];if(taken){goto L_001fdf28;}}
/* 001fded0: lhu a1,0x4(a0) */ c->r[5]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 001fded4: lui v1,0x35 */ c->r[3]=sx(UINT32_C(0x00350000));
/* 001fded8: lhu a0,0x4(v0) */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fdedc: addiu a3,v1,-0x6840 */ c->r[7]=sx((uint32_t)c->r[3]+UINT32_C(0xffff97c0));
/* 001fdee0: sll v0,a1,0x4 */ c->r[2]=sx((uint32_t)c->r[5]<<4u);
/* 001fdee4: sll v1,a0,0x4 */ c->r[3]=sx((uint32_t)c->r[4]<<4u);
/* 001fdee8: subu v0,v0,a1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[5]);
/* 001fdeec: subu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[4]);
/* 001fdef0: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001fdef4: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 001fdef8: addu v0,v0,a3 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[7]);
/* 001fdefc: addu v1,v1,a3 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 001fdf00: lbu a1,0x5(v0) */ c->r[5]=*at((uint32_t)c->r[2]+UINT32_C(0x00000005));
/* 001fdf04: beq a2,zero,0x001fdf38 */ {int taken=(c->r[6]==c->r[0]);/* delay 001fdf08 */ c->r[4]=*at((uint32_t)c->r[3]+UINT32_C(0x00000005));if(taken){goto L_001fdf38;}}
/* 001fdf0c: lhu v1,0x4(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 001fdf10: sll v0,v1,0x4 */ c->r[2]=sx((uint32_t)c->r[3]<<4u);
/* 001fdf14: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 001fdf18: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001fdf1c: addu v0,v0,a3 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[7]);
/* 001fdf20: b 0x001fdf38 */ /* delay 001fdf24 */ c->r[8]=*at((uint32_t)c->r[2]+UINT32_C(0x00000005));goto L_001fdf38;
L_001fdf28:;
/* 001fdf28: lhu a1,0x14(a0) */ c->r[5]=hword((uint32_t)c->r[4]+UINT32_C(0x00000014));
/* 001fdf2c: beq a2,zero,0x001fdf38 */ {int taken=(c->r[6]==c->r[0]);/* delay 001fdf30 */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000014));if(taken){goto L_001fdf38;}}
/* 001fdf34: lhu t0,0x14(a2) */ c->r[8]=hword((uint32_t)c->r[6]+UINT32_C(0x00000014));
L_001fdf38:;
/* 001fdf38: bne t0,zero,0x001fdf50 */ {int taken=(c->r[8]!=c->r[0]);/* delay 001fdf3c */ c->r[2]=sx((uint32_t)c->r[5]+(uint32_t)c->r[4]);if(taken){goto L_001fdf50;}}
/* 001fdf40: addiu v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 001fdf44: sra v0,v0,0x1 */ c->r[2]=sar((uint32_t)c->r[2],1u);
/* 001fdf48: jr ra */ /* delay 001fdf4c */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));return;
L_001fdf50:;
/* 001fdf50: li v1,0x3 */ c->r[3]=sx(UINT32_C(0x00000003));
/* 001fdf54: addu v0,v0,t0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[8]);
/* 001fdf58: beql v1,zero,0x001fdf60 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 001fdf5c */ nocturne_break(7);goto L_001fdf60;}}
L_001fdf60:;
/* 001fdf60: addiu v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000002));
/* 001fdf64: div v0,v1 */ {int32_t n=(int32_t)(uint32_t)c->r[2],d=(int32_t)(uint32_t)c->r[3];if(d==0){c->lo=n<0?UINT64_C(1):UINT64_MAX;c->hi=sx((uint32_t)n);}else if(n==INT32_MIN&&d==-1){c->lo=sx(UINT32_C(0x80000000));c->hi=0;}else{c->lo=sx((uint32_t)(n/d));c->hi=sx((uint32_t)(n%d));}}
/* 001fdf68: mflo v0 */ c->r[2]=c->lo;
/* 001fdf6c: jr ra */ /* delay 001fdf70 */ (void)0;return;
}

static void body_001fdf78(FusionValues *c){
/* 001fdf78: addiu sp,sp,-0x80 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffff80));
/* 001fdf7c: andi a1,a1,0xff */ c->r[5]=c->r[5]&UINT64_C(0xff);
/* 001fdf80: sd s2,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[18]);
/* 001fdf84: sd s3,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[19]);
/* 001fdf88: move s3,zero */ c->r[19]=c->r[0];
/* 001fdf8c: sd s4,0x50(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000050),c->r[20]);
/* 001fdf90: sd s5,0x58(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000058),c->r[21]);
/* 001fdf94: andi s5,a0,0xff */ c->r[21]=c->r[4]&UINT64_C(0xff);
/* 001fdf98: sd s6,0x60(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000060),c->r[22]);
/* 001fdf9c: move s6,sp */ c->r[22]=c->r[29];
/* 001fdfa0: sd s8,0x70(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000070),c->r[30]);
/* 001fdfa4: move s8,sp */ c->r[30]=c->r[29];
/* 001fdfa8: sd s0,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[16]);
/* 001fdfac: sd s1,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[17]);
/* 001fdfb0: sd s7,0x68(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000068),c->r[23]);
/* 001fdfb4: sd ra,0x78(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000078),c->r[31]);
/* 001fdfb8: sw a1,0x0(s8) */ sw((uint32_t)c->r[30]+UINT32_C(0x00000000),(uint32_t)c->r[5]);
/* 001fdfbc: lw s0,-0x4258(gp) */ c->r[16]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffbda8)));
/* 001fdfc0: sw zero,0x4(s8) */ sw((uint32_t)c->r[30]+UINT32_C(0x00000004),(uint32_t)c->r[0]);
/* 001fdfc4: addiu v1,s0,-0x1 */ c->r[3]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 001fdfc8: sll v0,v1,0x3 */ c->r[2]=sx((uint32_t)c->r[3]<<3u);
/* 001fdfcc: sll v1,v1,0x1 */ c->r[3]=sx((uint32_t)c->r[3]<<1u);
/* 001fdfd0: addiu v0,v0,0x17 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000017));
/* 001fdfd4: addiu v1,v1,0x11 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000011));
/* 001fdfd8: srl v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]>>4u);
/* 001fdfdc: srl v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]>>4u);
/* 001fdfe0: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 001fdfe4: sll v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]<<4u);
/* 001fdfe8: subu sp,sp,v0 */ c->r[29]=sx((uint32_t)c->r[29]-(uint32_t)c->r[2]);
/* 001fdfec: move s2,sp */ c->r[18]=c->r[29];
/* 001fdff0: subu sp,sp,v1 */ c->r[29]=sx((uint32_t)c->r[29]-(uint32_t)c->r[3]);
/* 001fdff4: beq s5,zero,0x001fe0a8 */ {int taken=(c->r[21]==c->r[0]);/* delay 001fdff8 */ c->r[20]=c->r[29];if(taken){goto L_001fe0a8;}}
/* 001fdffc: lhu a1,-0x4258(gp) */ c->r[5]=hword((uint32_t)c->r[28]+UINT32_C(0xffffbda8));
/* 001fe000: move a0,s2 */ c->r[4]=c->r[18];
/* 001fe004: jal 0x002133a0 */ c->r[31]=UINT64_C(0x001fe00c);/* delay 001fe008 */ c->r[17]=c->r[0];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);ps2FusionSortDescriptors_002133A0(A0,A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe00c: blez s0,0x001fe0a0 */ {int taken=((neg(c->r[16])||!c->r[16]));/* delay 001fe010 */ c->r[3]=sx((uint32_t)c->r[17]<<3u);if(taken){goto L_001fe0a0;}}
/* 001fe014: sw s0,0x8(s8) */ sw((uint32_t)c->r[30]+UINT32_C(0x00000008),(uint32_t)c->r[16]);
/* 001fe018: addiu s7,s2,0x4 */ c->r[23]=sx((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 001fe01c: nop  */ (void)0;
L_001fe020:;
/* 001fe020: addu a0,s7,v1 */ c->r[4]=sx((uint32_t)c->r[23]+(uint32_t)c->r[3]);
/* 001fe024: addu s0,s2,v1 */ c->r[16]=sx((uint32_t)c->r[18]+(uint32_t)c->r[3]);
/* 001fe028: lw v0,0x0(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 001fe02c: lbu v1,0x4(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fe030: bne v1,s5,0x001fe090 */ {int taken=(c->r[3]!=c->r[21]);/* delay 001fe034 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));if(taken){goto L_001fe090;}}
/* 001fe038: jal 0x001fe280 */ c->r[31]=UINT64_C(0x001fe040);/* delay 001fe03c */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));body_001fe280(c);
/* 001fe040: bne v0,zero,0x001fe094 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe044 */ c->r[3]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000008)));if(taken){goto L_001fe094;}}
/* 001fe048: jal 0x001fda08 */ c->r[31]=UINT64_C(0x001fe050);/* delay 001fe04c */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));body_001fda08(c);
/* 001fe050: bne v0,zero,0x001fe094 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe054 */ c->r[3]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000008)));if(taken){goto L_001fe094;}}
/* 001fe058: jal 0x001fd3b0 */ c->r[31]=UINT64_C(0x001fe060);/* delay 001fe05c */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentEventDisabled_001FD3B0(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe060: bne v0,zero,0x001fe094 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe064 */ c->r[3]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000008)));if(taken){goto L_001fe094;}}
/* 001fe068: jal 0x001fe2c8 */ c->r[31]=UINT64_C(0x001fe070);/* delay 001fe06c */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentMetaOnly_001FE2C8(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe070: move v1,s3 */ c->r[3]=c->r[19];
/* 001fe074: sll a0,v1,0x1 */ c->r[4]=sx((uint32_t)c->r[3]<<1u);
/* 001fe078: addiu v1,v1,0x1 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 001fe07c: bne v0,zero,0x001fe090 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe080 */ c->r[4]=sx((uint32_t)c->r[20]+(uint32_t)c->r[4]);if(taken){goto L_001fe090;}}
/* 001fe084: lhu v0,0x0(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fe088: andi s3,v1,0xffff */ c->r[19]=c->r[3]&UINT64_C(0xffff);
/* 001fe08c: sh v0,0x0(a0) */ sh((uint32_t)c->r[4]+UINT32_C(0x00000000),(uint16_t)c->r[2]);
L_001fe090:;
/* 001fe090: lw v1,0x8(s8) */ c->r[3]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000008)));
L_001fe094:;
/* 001fe094: slt v0,s1,v1 */ c->r[2]=less(c->r[17],c->r[3]);
/* 001fe098: bne v0,zero,0x001fe020 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe09c */ c->r[3]=sx((uint32_t)c->r[17]<<3u);if(taken){goto L_001fe020;}}
L_001fe0a0:;
/* 001fe0a0: bne s3,zero,0x001fe0c0 */ {int taken=(c->r[19]!=c->r[0]);/* delay 001fe0a4 */ (void)0;if(taken){goto L_001fe0c0;}}
L_001fe0a8:;
/* 001fe0a8: move sp,s6 */ c->r[29]=c->r[22];
/* 001fe0ac: b 0x001fe13c */ /* delay 001fe0b0 */ c->r[2]=c->r[0];goto L_001fe13c;
L_001fe0b8:;
/* 001fe0b8: b 0x001fe13c */ /* delay 001fe0bc */ c->r[2]=hword((uint32_t)c->r[20]+UINT32_C(0x00000000));goto L_001fe13c;
L_001fe0c0:;
/* 001fe0c0: beq s3,zero,0x001fe12c */ {int taken=(c->r[19]==c->r[0]);/* delay 001fe0c4 */ c->r[17]=c->r[0];if(taken){goto L_001fe12c;}}
/* 001fe0c8: lui v0,0x35 */ c->r[2]=sx(UINT32_C(0x00350000));
/* 001fe0cc: move a0,s4 */ c->r[4]=c->r[20];
/* 001fe0d0: addiu a1,v0,-0x6840 */ c->r[5]=sx((uint32_t)c->r[2]+UINT32_C(0xffff97c0));
/* 001fe0d4: nop  */ (void)0;
L_001fe0d8:;
/* 001fe0d8: lhu v0,0x0(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 001fe0dc: sll v1,v0,0x4 */ c->r[3]=sx((uint32_t)c->r[2]<<4u);
/* 001fe0e0: subu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[2]);
/* 001fe0e4: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 001fe0e8: addu v1,v1,a1 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[5]);
/* 001fe0ec: lbu v0,0x5(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0x00000005));
/* 001fe0f0: lw v1,0x0(s8) */ c->r[3]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000000)));
/* 001fe0f4: sltu v0,v0,v1 */ c->r[2]=(c->r[2]<c->r[3]);
/* 001fe0f8: beq v0,zero,0x001fe118 */ {int taken=(c->r[2]==c->r[0]);/* delay 001fe0fc */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));if(taken){goto L_001fe118;}}
/* 001fe100: lw v0,0x4(s8) */ c->r[2]=sx(word((uint32_t)c->r[30]+UINT32_C(0x00000004)));
/* 001fe104: beq v0,zero,0x001fe0b8 */ {int taken=(c->r[2]==c->r[0]);/* delay 001fe108 */ c->r[29]=c->r[22];if(taken){goto L_001fe0b8;}}
/* 001fe10c: b 0x001fe13c */ /* delay 001fe110 */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0xfffffffe));goto L_001fe13c;
L_001fe118:;
/* 001fe118: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 001fe11c: slt v0,s1,s3 */ c->r[2]=less(c->r[17],c->r[19]);
/* 001fe120: sw v1,0x4(s8) */ sw((uint32_t)c->r[30]+UINT32_C(0x00000004),(uint32_t)c->r[3]);
/* 001fe124: bne v0,zero,0x001fe0d8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe128 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000002));if(taken){goto L_001fe0d8;}}
L_001fe12c:;
/* 001fe12c: sll v1,s3,0x1 */ c->r[3]=sx((uint32_t)c->r[19]<<1u);
/* 001fe130: move sp,s6 */ c->r[29]=c->r[22];
/* 001fe134: addu v1,v1,s4 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[20]);
/* 001fe138: lhu v0,-0x2(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0xfffffffe));
L_001fe13c:;
/* 001fe13c: move sp,s8 */ c->r[29]=c->r[30];
/* 001fe140: ld s0,0x30(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fe144: ld s1,0x38(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001fe148: ld s2,0x40(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001fe14c: ld s3,0x48(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 001fe150: ld s4,0x50(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000050));
/* 001fe154: ld s5,0x58(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000058));
/* 001fe158: ld s6,0x60(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000060));
/* 001fe15c: ld s7,0x68(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000068));
/* 001fe160: ld s8,0x70(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000070));
/* 001fe164: ld ra,0x78(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000078));
/* 001fe168: jr ra */ /* delay 001fe16c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000080));return;
}

static void body_001fe170(FusionValues *c){
/* 001fe170: lhu v0,0x4(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 001fe174: sh v0,0x0(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x00000000),(uint16_t)c->r[2]);
/* 001fe178: lhu v1,0x4(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 001fe17c: sll v0,v1,0x4 */ c->r[2]=sx((uint32_t)c->r[3]<<4u);
/* 001fe180: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 001fe184: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001fe188: lui v1,0x35 */ c->r[3]=sx(UINT32_C(0x00350000));
/* 001fe18c: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 001fe190: lbu v1,-0x683c(v1) */ c->r[3]=*at((uint32_t)c->r[3]+UINT32_C(0xffff97c4));
/* 001fe194: jr ra */ /* delay 001fe198 */ *at((uint32_t)c->r[6]+UINT32_C(0x00000000))=(uint8_t)c->r[3];return;
}

static void body_001fe1a0(FusionValues *c){
/* 001fe1a0: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 001fe1a4: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fe1a8: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001fe1ac: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001fe1b0: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001fe1b4: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 001fe1b8: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 001fe1bc: andi s3,a0,0xffff */ c->r[19]=c->r[4]&UINT64_C(0xffff);
/* 001fe1c0: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 001fe1c4: andi s4,a1,0xffff */ c->r[20]=c->r[5]&UINT64_C(0xffff);
/* 001fe1c8: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 001fe1cc: move s5,zero */ c->r[21]=c->r[0];
/* 001fe1d0: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 001fe1d4: li s6,0x2 */ c->r[22]=sx(UINT32_C(0x00000002));
/* 001fe1d8: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 001fe1dc: addiu s7,v0,-0x2488 */ c->r[23]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdb78));
L_001fe1e0:;
/* 001fe1e0: move s2,zero */ c->r[18]=c->r[0];
/* 001fe1e4: move s0,s7 */ c->r[16]=c->r[23];
L_001fe1e8:;
/* 001fe1e8: lhu v0,0x0(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001fe1ec: lhu a0,0x2(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000002));
/* 001fe1f0: xor v0,v0,s3 */ c->r[2]=c->r[2]^c->r[19];
/* 001fe1f4: sltiu v0,v0,0x1 */ c->r[2]=(c->r[2]<sx(UINT32_C(0x00000001)));
/* 001fe1f8: xor a0,a0,s4 */ c->r[4]=c->r[4]^c->r[20];
/* 001fe1fc: addiu v1,v0,0x1 */ c->r[3]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 001fe200: movz v0,v1,a0 */ if(c->r[4]==0){c->r[2]=c->r[3];}
/* 001fe204: bnel v0,s6,0x001fe228 */ {int taken=(c->r[2]!=c->r[22]);if(taken){/* delay 001fe208 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_001fe228;}}
/* 001fe20c: lhu s1,0x4(s0) */ c->r[17]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));
/* 001fe210: jal 0x001fd3b0 */ c->r[31]=UINT64_C(0x001fe218);/* delay 001fe214 */ c->r[4]=c->r[17];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentEventDisabled_001FD3B0(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe218: bne v0,zero,0x001fe228 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe21c */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));if(taken){goto L_001fe228;}}
/* 001fe220: b 0x001fe250 */ /* delay 001fe224 */ c->r[2]=c->r[17];goto L_001fe250;
L_001fe228:;
/* 001fe228: sltiu v0,s2,0x3 */ c->r[2]=(c->r[18]<sx(UINT32_C(0x00000003)));
/* 001fe22c: bne v0,zero,0x001fe1e8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fe230 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000006));if(taken){goto L_001fe1e8;}}
/* 001fe234: addiu s5,s5,0x1 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x00000001));
/* 001fe238: move v0,s3 */ c->r[2]=c->r[19];
/* 001fe23c: slti v1,s5,0x2 */ c->r[3]=less(c->r[21],sx(UINT32_C(0x00000002)));
/* 001fe240: move s3,s4 */ c->r[19]=c->r[20];
/* 001fe244: bne v1,zero,0x001fe1e0 */ {int taken=(c->r[3]!=c->r[0]);/* delay 001fe248 */ c->r[20]=c->r[2];if(taken){goto L_001fe1e0;}}
/* 001fe24c: move v0,zero */ c->r[2]=c->r[0];
L_001fe250:;
/* 001fe250: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fe254: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001fe258: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fe25c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fe260: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001fe264: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001fe268: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fe26c: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001fe270: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001fe274: jr ra */ /* delay 001fe278 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_001fe280(FusionValues *c){
/* 001fe280: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001fe284: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fe288: addiu v0,v0,-0x2488 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdb78));
/* 001fe28c: move a2,zero */ c->r[6]=c->r[0];
/* 001fe290: addiu a1,v0,0x4 */ c->r[5]=sx((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 001fe294: lhu v1,0x0(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000000));
L_001fe298:;
/* 001fe298: addiu a1,a1,0x6 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000006));
/* 001fe29c: beq a0,v1,0x001fe2c0 */ {int taken=(c->r[4]==c->r[3]);/* delay 001fe2a0 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_001fe2c0;}}
/* 001fe2a4: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 001fe2a8: sltiu v0,a2,0x3 */ c->r[2]=(c->r[6]<sx(UINT32_C(0x00000003)));
/* 001fe2ac: nop  */ (void)0;
/* 001fe2b0: nop  */ (void)0;
/* 001fe2b4: bnel v0,zero,0x001fe298 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001fe2b8 */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000000));goto L_001fe298;}}
/* 001fe2bc: move v0,zero */ c->r[2]=c->r[0];
L_001fe2c0:;
/* 001fe2c0: jr ra */ /* delay 001fe2c4 */ (void)0;return;
}

static void body_001fe5f0(FusionValues *c){
/* 001fe5f0: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 001fe5f4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001fe5f8: sll s0,a3,0x18 */ c->r[16]=sx((uint32_t)c->r[7]<<24u);
/* 001fe5fc: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001fe600: sll s1,a2,0x18 */ c->r[17]=sx((uint32_t)c->r[6]<<24u);
/* 001fe604: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001fe608: sra s1,s1,0x18 */ c->r[17]=sar((uint32_t)c->r[17],24u);
/* 001fe60c: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 001fe610: move s3,a0 */ c->r[19]=c->r[4];
/* 001fe614: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 001fe618: move s4,a1 */ c->r[20]=c->r[5];
/* 001fe61c: sd ra,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[31]);
/* 001fe620: move a2,s1 */ c->r[6]=c->r[17];
/* 001fe624: sra s0,s0,0x18 */ c->r[16]=sar((uint32_t)c->r[16],24u);
/* 001fe628: lhu a0,0x4(s3) */ c->r[4]=hword((uint32_t)c->r[19]+UINT32_C(0x00000004));
/* 001fe62c: jal 0x001fdde8 */ c->r[31]=UINT64_C(0x001fe634);/* delay 001fe630 */ c->r[5]=hword((uint32_t)c->r[20]+UINT32_C(0x00000004));body_001fdde8(c);
/* 001fe634: move a0,s3 */ c->r[4]=c->r[19];
/* 001fe638: move a3,s0 */ c->r[7]=c->r[16];
/* 001fe63c: move a1,s4 */ c->r[5]=c->r[20];
/* 001fe640: move a2,zero */ c->r[6]=c->r[0];
/* 001fe644: jal 0x001fdec0 */ c->r[31]=UINT64_C(0x001fe64c);/* delay 001fe648 */ c->r[18]=c->r[2];body_001fdec0(c);
/* 001fe64c: move a0,s2 */ c->r[4]=c->r[18];
/* 001fe650: jal 0x001fdf78 */ c->r[31]=UINT64_C(0x001fe658);/* delay 001fe654 */ c->r[5]=c->r[2]&UINT64_C(0xff);body_001fdf78(c);
/* 001fe658: move a0,zero */ c->r[4]=c->r[0];
/* 001fe65c: movn a0,v0,s1 */ if(c->r[17]!=0){c->r[4]=c->r[2];}
/* 001fe660: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001fe664: xori v1,v0,0xcd */ c->r[3]=c->r[2]^UINT64_C(0xcd);
/* 001fe668: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fe66c: movz v0,a0,v1 */ if(c->r[3]==0){c->r[2]=c->r[4];}
/* 001fe670: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fe674: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fe678: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 001fe67c: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001fe680: ld ra,0x28(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001fe684: jr ra */ /* delay 001fe688 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_001fe690(FusionValues *c){
/* 001fe690: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 001fe694: sll a2,a2,0x18 */ c->r[6]=sx((uint32_t)c->r[6]<<24u);
/* 001fe698: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001fe69c: sll a3,a3,0x18 */ c->r[7]=sx((uint32_t)c->r[7]<<24u);
/* 001fe6a0: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001fe6a4: sra s0,a3,0x18 */ c->r[16]=sar((uint32_t)c->r[7],24u);
/* 001fe6a8: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001fe6ac: move s2,t0 */ c->r[18]=c->r[8];
/* 001fe6b0: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 001fe6b4: move s3,t1 */ c->r[19]=c->r[9];
/* 001fe6b8: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 001fe6bc: sra s4,a2,0x18 */ c->r[20]=sar((uint32_t)c->r[6],24u);
/* 001fe6c0: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 001fe6c4: move s5,a0 */ c->r[21]=c->r[4];
/* 001fe6c8: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 001fe6cc: move s6,a1 */ c->r[22]=c->r[5];
/* 001fe6d0: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 001fe6d4: move s7,t2 */ c->r[23]=c->r[10];
/* 001fe6d8: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 001fe6dc: lhu a0,0x0(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000000));
/* 001fe6e0: jal 0x001fe1a0 */ c->r[31]=UINT64_C(0x001fe6e8);/* delay 001fe6e4 */ c->r[5]=hword((uint32_t)c->r[18]+UINT32_C(0x00000002));body_001fe1a0(c);
/* 001fe6e8: move s1,v0 */ c->r[17]=c->r[2];
/* 001fe6ec: bne s1,zero,0x001fe848 */ {int taken=(c->r[17]!=c->r[0]);/* delay 001fe6f0 */ c->r[4]=sx(UINT32_C(0x00000007));if(taken){goto L_001fe848;}}
/* 001fe6f4: lbu a2,0x0(s3) */ c->r[6]=*at((uint32_t)c->r[19]+UINT32_C(0x00000000));
/* 001fe6f8: li v1,0x7 */ c->r[3]=sx(UINT32_C(0x00000007));
/* 001fe6fc: andi v0,a2,0xff */ c->r[2]=c->r[6]&UINT64_C(0xff);
/* 001fe700: beq v0,v1,0x001fe718 */ {int taken=(c->r[2]==c->r[3]);/* delay 001fe704 */ c->r[4]=*at((uint32_t)c->r[19]+UINT32_C(0x00000001));if(taken){goto L_001fe718;}}
/* 001fe708: bnel a0,v1,0x001fe7d8 */ {int taken=(c->r[4]!=c->r[3]);if(taken){/* delay 001fe70c */ c->r[5]=sx(UINT32_C(0x00000008));goto L_001fe7d8;}}
/* 001fe710: b 0x001fe71c */ /* delay 001fe714 */ c->r[5]=sx(UINT32_C(0x00000026));goto L_001fe71c;
L_001fe718:;
/* 001fe718: li a1,0x26 */ c->r[5]=sx(UINT32_C(0x00000026));
L_001fe71c:;
/* 001fe71c: beq v0,a1,0x001fe7d0 */ {int taken=(c->r[2]==c->r[5]);/* delay 001fe720 */ c->r[3]=c->r[4]&UINT64_C(0xff);if(taken){goto L_001fe7d0;}}
/* 001fe724: beql v1,a1,0x001fe7d4 */ {int taken=(c->r[3]==c->r[5]);if(taken){/* delay 001fe728 */ c->r[2]=c->r[6]&UINT64_C(0xff);goto L_001fe7d4;}}
/* 001fe72c: bne v0,v1,0x001fe750 */ {int taken=(c->r[2]!=c->r[3]);/* delay 001fe730 */ c->r[2]=c->r[2]^UINT64_C(0x7);if(taken){goto L_001fe750;}}
/* 001fe734: lhu a0,0x0(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000000));
/* 001fe738: jal 0x001fdd18 */ c->r[31]=UINT64_C(0x001fe740);/* delay 001fe73c */ c->r[5]=hword((uint32_t)c->r[18]+UINT32_C(0x00000002));body_001fdd18(c);
/* 001fe740: li a0,0x3 */ c->r[4]=sx(UINT32_C(0x00000003));
/* 001fe744: b 0x001fe848 */ /* delay 001fe748 */ c->r[17]=c->r[2];goto L_001fe848;
L_001fe750:;
/* 001fe750: sltu s0,zero,v0 */ c->r[16]=(c->r[0]<c->r[2]);
/* 001fe754: sll v1,s0,0x1 */ c->r[3]=sx((uint32_t)c->r[16]<<1u);
/* 001fe758: sltiu s1,s0,0x1 */ c->r[17]=(c->r[16]<sx(UINT32_C(0x00000001)));
/* 001fe75c: addu v1,v1,s2 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[18]);
/* 001fe760: addu v0,s3,s1 */ c->r[2]=sx((uint32_t)c->r[19]+(uint32_t)c->r[17]);
/* 001fe764: lhu a0,0x0(v1) */ c->r[4]=hword((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 001fe768: jal 0x001fdca0 */ c->r[31]=UINT64_C(0x001fe770);/* delay 001fe76c */ c->r[5]=*at((uint32_t)c->r[2]+UINT32_C(0x00000000));body_001fdca0(c);
/* 001fe770: beq s4,zero,0x001fe7a4 */ {int taken=(c->r[20]==c->r[0]);/* delay 001fe774 */ c->r[16]=c->r[2];if(taken){goto L_001fe7a4;}}
/* 001fe778: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 001fe77c: beq s0,v0,0x001fe798 */ {int taken=(c->r[16]==c->r[2]);/* delay 001fe780 */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_001fe798;}}
/* 001fe784: beq s0,v0,0x001fe7a0 */ {int taken=(c->r[16]==c->r[2]);/* delay 001fe788 */ c->r[2]=sx((uint32_t)c->r[17]<<1u);if(taken){goto L_001fe7a0;}}
/* 001fe78c: b 0x001fe7ac */ /* delay 001fe790 */ c->r[5]=c->r[16]&UINT64_C(0xff);goto L_001fe7ac;
L_001fe798:;
/* 001fe798: b 0x001fe7a4 */ /* delay 001fe79c */ c->r[16]=sx(UINT32_C(0x00000002));goto L_001fe7a4;
L_001fe7a0:;
/* 001fe7a0: li s0,0x1 */ c->r[16]=sx(UINT32_C(0x00000001));
L_001fe7a4:;
/* 001fe7a4: sll v0,s1,0x1 */ c->r[2]=sx((uint32_t)c->r[17]<<1u);
/* 001fe7a8: andi a1,s0,0xff */ c->r[5]=c->r[16]&UINT64_C(0xff);
L_001fe7ac:;
/* 001fe7ac: addu v0,v0,s2 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[18]);
/* 001fe7b0: jal 0x001fdac0 */ c->r[31]=UINT64_C(0x001fe7b8);/* delay 001fe7b4 */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));body_001fdac0(c);
/* 001fe7b8: li v1,0x5 */ c->r[3]=sx(UINT32_C(0x00000005));
/* 001fe7bc: move s1,v0 */ c->r[17]=c->r[2];
/* 001fe7c0: xori v0,s0,0x2 */ c->r[2]=c->r[16]^UINT64_C(0x2);
/* 001fe7c4: li a0,0x6 */ c->r[4]=sx(UINT32_C(0x00000006));
/* 001fe7c8: b 0x001fe848 */ /* delay 001fe7cc */ if(c->r[2]!=0){c->r[4]=c->r[3];}goto L_001fe848;
L_001fe7d0:;
/* 001fe7d0: andi v0,a2,0xff */ c->r[2]=c->r[6]&UINT64_C(0xff);
L_001fe7d4:;
/* 001fe7d4: li a1,0x8 */ c->r[5]=sx(UINT32_C(0x00000008));
L_001fe7d8:;
/* 001fe7d8: beq v0,a1,0x001fe7ec */ {int taken=(c->r[2]==c->r[5]);/* delay 001fe7dc */ (void)0;if(taken){goto L_001fe7ec;}}
/* 001fe7e0: andi v1,a0,0xff */ c->r[3]=c->r[4]&UINT64_C(0xff);
/* 001fe7e4: bne v1,a1,0x001fe808 */ {int taken=(c->r[3]!=c->r[5]);/* delay 001fe7e8 */ (void)0;if(taken){goto L_001fe808;}}
L_001fe7ec:;
/* 001fe7ec: beql v0,a0,0x001fe814 */ {int taken=(c->r[2]==c->r[4]);if(taken){/* delay 001fe7f0 */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000000));goto L_001fe814;}}
/* 001fe7f4: bnel v0,a1,0x001fe800 */ {int taken=(c->r[2]!=c->r[5]);if(taken){/* delay 001fe7f8 */ c->r[17]=hword((uint32_t)c->r[18]+UINT32_C(0x00000000));goto L_001fe800;}}
/* 001fe7fc: lhu s1,0x2(s2) */ c->r[17]=hword((uint32_t)c->r[18]+UINT32_C(0x00000002));
L_001fe800:;
/* 001fe800: b 0x001fe848 */ /* delay 001fe804 */ c->r[4]=sx(UINT32_C(0x00000002));goto L_001fe848;
L_001fe808:;
/* 001fe808: bnel v0,v1,0x001fe830 */ {int taken=(c->r[2]!=c->r[3]);if(taken){/* delay 001fe80c */ c->r[4]=c->r[21];goto L_001fe830;}}
/* 001fe810: lhu a0,0x0(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000000));
L_001fe814:;
/* 001fe814: move a2,s4 */ c->r[6]=c->r[20];
/* 001fe818: jal 0x001fdde8 */ c->r[31]=UINT64_C(0x001fe820);/* delay 001fe81c */ c->r[5]=hword((uint32_t)c->r[18]+UINT32_C(0x00000002));body_001fdde8(c);
/* 001fe820: li a0,0x4 */ c->r[4]=sx(UINT32_C(0x00000004));
/* 001fe824: b 0x001fe848 */ /* delay 001fe828 */ c->r[17]=c->r[2];goto L_001fe848;
L_001fe830:;
/* 001fe830: move a1,s6 */ c->r[5]=c->r[22];
/* 001fe834: move a2,s4 */ c->r[6]=c->r[20];
/* 001fe838: jal 0x001fe5f0 */ c->r[31]=UINT64_C(0x001fe840);/* delay 001fe83c */ c->r[7]=c->r[16];body_001fe5f0(c);
/* 001fe840: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 001fe844: move s1,v0 */ c->r[17]=c->r[2];
L_001fe848:;
/* 001fe848: bnel s7,zero,0x001fe850 */ {int taken=(c->r[23]!=c->r[0]);if(taken){/* delay 001fe84c */ *at((uint32_t)c->r[23]+UINT32_C(0x00000000))=(uint8_t)c->r[4];goto L_001fe850;}}
L_001fe850:;
/* 001fe850: move v0,s1 */ c->r[2]=c->r[17];
/* 001fe854: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fe858: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001fe85c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fe860: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fe864: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001fe868: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001fe86c: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fe870: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001fe874: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001fe878: jr ra */ /* delay 001fe87c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_001fe880(FusionValues *c){
/* 001fe880: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 001fe884: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001fe888: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001fe88c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001fe890: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 001fe894: lw v0,0x10(a3) */ c->r[2]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00000010)));
/* 001fe898: bltz v0,0x001fe8b0 */ {int taken=(neg(c->r[2]));/* delay 001fe89c */ c->r[17]=c->r[4];if(taken){goto L_001fe8b0;}}
/* 001fe8a0: mtc1 v0,f2 */ c->f[2]=(uint32_t)c->r[2];
/* 001fe8a4: cvt.s.W f2,f2 */ c->f[2]=EE_FPU_CVT_S_W(c->f[2]);
/* 001fe8a8: b 0x001fe8c8 */ /* delay 001fe8ac */ (void)0;goto L_001fe8c8;
L_001fe8b0:;
/* 001fe8b0: srl v1,v0,0x1 */ c->r[3]=sx((uint32_t)c->r[2]>>1u);
/* 001fe8b4: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 001fe8b8: or v0,v0,v1 */ c->r[2]=c->r[2]|c->r[3];
/* 001fe8bc: mtc1 v0,f2 */ c->f[2]=(uint32_t)c->r[2];
/* 001fe8c0: cvt.s.W f2,f2 */ c->f[2]=EE_FPU_CVT_S_W(c->f[2]);
/* 001fe8c4: add.S f2,f2,f2 */ c->f[2]=EE_FPU_ADD_S(c->f[2],c->f[2]);
L_001fe8c8:;
/* 001fe8c8: lui at,0x3fc0 */ c->r[1]=sx(UINT32_C(0x3fc00000));
/* 001fe8cc: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 001fe8d0: clear f1 */ c->f[1]=0;
/* 001fe8d4: mul.S f0,f2,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[2],c->f[0]);
/* 001fe8d8: lui at,0x4f00 */ c->r[1]=sx(UINT32_C(0x4f000000));
/* 001fe8dc: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 001fe8e0: add.S f0,f0,f1 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[1]);
/* 001fe8e4: c.le.S f2,f0 */ c->condition=le_single(c->f[2],c->f[0]);nocturneFusionCoreFpuCondition(c->condition);
/* 001fe8e8: cvt.w.S f1,f0 */ c->f[1]=EE_FPU_CVT_W_S(c->f[0]);
/* 001fe8ec: mfc1 s2,f1 */ c->r[18]=sx(c->f[1]);
/* 001fe8f0: bc1f 0x001fe90c */ {int taken=(!c->condition);/* delay 001fe8f4 */ c->r[5]=hword((uint32_t)c->r[17]+UINT32_C(0x00000014));if(taken){goto L_001fe90c;}}
/* 001fe8f8: sub.S f0,f0,f2 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[2]);
/* 001fe8fc: lui v0,0x8000 */ c->r[2]=sx(UINT32_C(0x80000000));
/* 001fe900: cvt.w.S f1,f0 */ c->f[1]=EE_FPU_CVT_W_S(c->f[0]);
/* 001fe904: mfc1 s2,f1 */ c->r[18]=sx(c->f[1]);
/* 001fe908: or s2,s2,v0 */ c->r[18]=c->r[18]|c->r[2];
L_001fe90c:;
/* 001fe90c: jal 0x00223668 */ c->r[31]=UINT64_C(0x001fe914);/* delay 001fe910 */ c->r[4]=c->r[17];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(cmbCalcLevelUpExp(UNIT(A0),(int32_t)(uint32_t)A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe914: lw v1,0x10(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000010)));
/* 001fe918: move a0,s1 */ c->r[4]=c->r[17];
/* 001fe91c: move a1,s2 */ c->r[5]=c->r[18];
/* 001fe920: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 001fe924: jal 0x00223928 */ c->r[31]=UINT64_C(0x001fe92c);/* delay 001fe928 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000010),(uint32_t)c->r[3]);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbGetLevelUpCount(UNIT(A0),(int32_t)(uint32_t)A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe92c: lhu a2,0x14(s1) */ c->r[6]=hword((uint32_t)c->r[17]+UINT32_C(0x00000014));
/* 001fe930: move s0,v0 */ c->r[16]=c->r[2];
/* 001fe934: lw v0,0x10(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000010)));
/* 001fe938: addu a0,a2,s0 */ c->r[4]=sx((uint32_t)c->r[6]+(uint32_t)c->r[16]);
/* 001fe93c: addu v0,v0,s2 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[18]);
/* 001fe940: slti v1,a0,0x100 */ c->r[3]=less(c->r[4],sx(UINT32_C(0x00000100)));
/* 001fe944: bne v1,zero,0x001fe958 */ {int taken=(c->r[3]!=c->r[0]);/* delay 001fe948 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000010),(uint32_t)c->r[2]);if(taken){goto L_001fe958;}}
/* 001fe94c: li v0,0xff */ c->r[2]=sx(UINT32_C(0x000000ff));
/* 001fe950: subu s0,v0,a2 */ c->r[16]=sx((uint32_t)c->r[2]-(uint32_t)c->r[6]);
/* 001fe954: addu a0,a2,s0 */ c->r[4]=sx((uint32_t)c->r[6]+(uint32_t)c->r[16]);
L_001fe958:;
/* 001fe958: move v0,s0 */ c->r[2]=c->r[16];
/* 001fe95c: addiu s0,s0,-0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 001fe960: blez v0,0x001fe9a0 */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 001fe964 */ sh((uint32_t)c->r[17]+UINT32_C(0x00000014),(uint16_t)c->r[4]);if(taken){goto L_001fe9a0;}}
/* 001fe968: addiu s2,s1,0x6 */ c->r[18]=sx((uint32_t)c->r[17]+UINT32_C(0x00000006));
/* 001fe96c: move a0,s1 */ c->r[4]=c->r[17];
L_001fe970:;
/* 001fe970: jal 0x00222e00 */ c->r[31]=UINT64_C(0x001fe978);/* delay 001fe974 */ c->r[5]=sx(UINT32_C(0x00000001));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbAddLevelUpParamEx(UNIT(A0),(int8_t)(uint8_t)A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe978: move a0,s0 */ c->r[4]=c->r[16];
/* 001fe97c: addiu v1,v0,0x10 */ c->r[3]=sx((uint32_t)c->r[2]+UINT32_C(0x00000010));
/* 001fe980: addiu s0,s0,-0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 001fe984: bltz v0,0x001fe998 */ {int taken=(neg(c->r[2]));/* delay 001fe988 */ c->r[3]=sx((uint32_t)c->r[18]+(uint32_t)c->r[3]);if(taken){goto L_001fe998;}}
/* 001fe98c: lbu v0,0x0(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 001fe990: addiu v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 001fe994: sb v0,0x0(v1) */ *at((uint32_t)c->r[3]+UINT32_C(0x00000000))=(uint8_t)c->r[2];
L_001fe998:;
/* 001fe998: bgtz a0,0x001fe970 */ {int taken=((!neg(c->r[4])&&c->r[4]));/* delay 001fe99c */ c->r[4]=c->r[17];if(taken){goto L_001fe970;}}
L_001fe9a0:;
/* 001fe9a0: lw v0,0x0(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 001fe9a4: li a0,0xff */ c->r[4]=sx(UINT32_C(0x000000ff));
/* 001fe9a8: lhu v1,0x14(s1) */ c->r[3]=hword((uint32_t)c->r[17]+UINT32_C(0x00000014));
/* 001fe9ac: ori v0,v0,0x200 */ c->r[2]=c->r[2]|UINT64_C(0x200);
/* 001fe9b0: bne v1,a0,0x001fe9c8 */ {int taken=(c->r[3]!=c->r[4]);/* delay 001fe9b4 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000000),(uint32_t)c->r[2]);if(taken){goto L_001fe9c8;}}
/* 001fe9b8: move a0,s1 */ c->r[4]=c->r[17];
/* 001fe9bc: jal 0x00223668 */ c->r[31]=UINT64_C(0x001fe9c4);/* delay 001fe9c0 */ c->r[5]=sx(UINT32_C(0x000000ff));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(cmbCalcLevelUpExp(UNIT(A0),(int32_t)(uint32_t)A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fe9c4: sw v0,0x10(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000010),(uint32_t)c->r[2]);
L_001fe9c8:;
/* 001fe9c8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fe9cc: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001fe9d0: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fe9d4: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fe9d8: jr ra */ /* delay 001fe9dc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_001fea20(FusionValues *c){
/* 001fea20: addiu sp,sp,-0x110 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffef0));
/* 001fea24: sll a2,a3,0x18 */ c->r[6]=sx((uint32_t)c->r[7]<<24u);
/* 001fea28: sll a3,t0,0x18 */ c->r[7]=sx((uint32_t)c->r[8]<<24u);
/* 001fea2c: move t0,t1 */ c->r[8]=c->r[9];
/* 001fea30: sra a2,a2,0x18 */ c->r[6]=sar((uint32_t)c->r[6],24u);
/* 001fea34: sra a3,a3,0x18 */ c->r[7]=sar((uint32_t)c->r[7],24u);
/* 001fea38: move t1,t2 */ c->r[9]=c->r[10];
/* 001fea3c: sd s0,0x100(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000100),c->r[16]);
/* 001fea40: sd ra,0x108(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000108),c->r[31]);
/* 001fea44: jal 0x001fe690 */ c->r[31]=UINT64_C(0x001fea4c);/* delay 001fea48 */ c->r[10]=sx((uint32_t)c->r[29]+UINT32_C(0x000000f0));body_001fe690(c);
/* 001fea4c: lbu v1,0xf0(sp) */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x000000f0));
/* 001fea50: andi s0,v0,0xffff */ c->r[16]=c->r[2]&UINT64_C(0xffff);
/* 001fea54: li a1,0x2 */ c->r[5]=sx(UINT32_C(0x00000002));
/* 001fea58: move a0,s0 */ c->r[4]=c->r[16];
/* 001fea5c: beq v1,a1,0x001fea88 */ {int taken=(c->r[3]==c->r[5]);/* delay 001fea60 */ c->r[2]=c->r[0];if(taken){goto L_001fea88;}}
/* 001fea64: jal 0x001fe9e0 */ c->r[31]=UINT64_C(0x001fea6c);/* delay 001fea68 */ (void)0;nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbChkIkenieIllegalDevil((uint16_t)A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fea6c: movn s0,zero,v0 */ if(c->r[2]!=0){c->r[16]=c->r[0];}
/* 001fea70: move v0,zero */ c->r[2]=c->r[0];
/* 001fea74: beq s0,zero,0x001fea88 */ {int taken=(c->r[16]==c->r[0]);/* delay 001fea78 */ c->r[5]=c->r[29];if(taken){goto L_001fea88;}}
/* 001fea7c: jal 0x001fee68 */ c->r[31]=UINT64_C(0x001fea84);/* delay 001fea80 */ c->r[4]=c->r[16];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);cmbCopyDefaultDevilToStock((uint16_t)A0,UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fea84: move v0,s0 */ c->r[2]=c->r[16];
L_001fea88:;
/* 001fea88: ld s0,0x100(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000100));
/* 001fea8c: ld ra,0x108(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000108));
/* 001fea90: jr ra */ /* delay 001fea94 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000110));return;
}

static void body_001feb28(FusionValues *c){
/* 001feb28: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 001feb2c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001feb30: move s0,a1 */ c->r[16]=c->r[5];
/* 001feb34: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001feb38: move s1,a0 */ c->r[17]=c->r[4];
/* 001feb3c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001feb40: addiu s0,s0,0x3a */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x0000003a));
/* 001feb44: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 001feb48: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 001feb4c: move s4,zero */ c->r[20]=c->r[0];
/* 001feb50: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 001feb54: move s5,zero */ c->r[21]=c->r[0];
/* 001feb58: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 001feb5c: addiu s6,s1,0x6 */ c->r[22]=sx((uint32_t)c->r[17]+UINT32_C(0x00000006));
/* 001feb60: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 001feb64: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 001feb68: jal 0x001fdda8 */ c->r[31]=UINT64_C(0x001feb70);/* delay 001feb6c */ c->r[23]=sx(UINT32_C(0x00000001));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbGetKeisyoSkillEndIndex(UNIT(A0));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001feb70: move s3,v0 */ c->r[19]=c->r[2];
/* 001feb74: sll v0,s3,0x1 */ c->r[2]=sx((uint32_t)c->r[19]<<1u);
/* 001feb78: addu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[17]);
/* 001feb7c: addiu s2,v0,0x86 */ c->r[18]=sx((uint32_t)c->r[2]+UINT32_C(0x00000086));
L_001feb80:;
/* 001feb80: lhu v0,0x0(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001feb84: beq v0,zero,0x001fec00 */ {int taken=(c->r[2]==c->r[0]);/* delay 001feb88 */ c->r[4]=c->r[2];if(taken){goto L_001fec00;}}
/* 001feb8c: jal 0x001feda0 */ c->r[31]=UINT64_C(0x001feb94);/* delay 001feb90 */ c->r[5]=c->r[17];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbChkSkillOwner((uint16_t)A0,UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001feb94: bgez v0,0x001fec00 */ {int taken=(!neg(c->r[2]));/* delay 001feb98 */ c->r[4]=c->r[17];if(taken){goto L_001fec00;}}
/* 001feb9c: jal 0x00222bf0 */ c->r[31]=UINT64_C(0x001feba4);/* delay 001feba0 */ c->r[5]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=cmbCalcKeisyoSkillRate(UNIT(A0),(uint16_t)A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001feba4: beq v0,zero,0x001fec00 */ {int taken=(c->r[2]==c->r[0]);/* delay 001feba8 */ c->r[5]=c->r[17];if(taken){goto L_001fec00;}}
/* 001febac: jal 0x001fedf0 */ c->r[31]=UINT64_C(0x001febb4);/* delay 001febb0 */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbChkKeisyoSkillOwner((uint16_t)A0,UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001febb4: addu v1,s3,s5 */ c->r[3]=sx((uint32_t)c->r[19]+(uint32_t)c->r[21]);
/* 001febb8: addiu a0,v0,0xb0 */ c->r[4]=sx((uint32_t)c->r[2]+UINT32_C(0x000000b0));
/* 001febbc: slti v1,v1,0x18 */ c->r[3]=less(c->r[3],sx(UINT32_C(0x00000018)));
/* 001febc0: bltz v0,0x001febe8 */ {int taken=(neg(c->r[2]));/* delay 001febc4 */ c->r[4]=sx((uint32_t)c->r[22]+(uint32_t)c->r[4]);if(taken){goto L_001febe8;}}
/* 001febc8: lbu v0,0x0(a0) */ c->r[2]=*at((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 001febcc: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 001febd0: andi v0,v0,0xff */ c->r[2]=c->r[2]&UINT64_C(0xff);
/* 001febd4: beql v0,zero,0x001fec00 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 001febd8 */ *at((uint32_t)c->r[4]+UINT32_C(0x00000000))=(uint8_t)c->r[23];goto L_001fec00;}}
/* 001febdc: b 0x001fec04 */ /* delay 001febe0 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));goto L_001fec04;
L_001febe8:;
/* 001febe8: beql v1,zero,0x001fec14 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 001febec */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_001fec14;}}
/* 001febf0: lhu v0,0x0(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001febf4: addiu s5,s5,0x1 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x00000001));
/* 001febf8: sh v0,0x0(s2) */ sh((uint32_t)c->r[18]+UINT32_C(0x00000000),(uint16_t)c->r[2]);
/* 001febfc: addiu s2,s2,0x2 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000002));
L_001fec00:;
/* 001fec00: addiu s4,s4,0x1 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));
L_001fec04:;
/* 001fec04: slti v0,s4,0x8 */ c->r[2]=less(c->r[20],sx(UINT32_C(0x00000008)));
/* 001fec08: bne v0,zero,0x001feb80 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001fec0c */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000002));if(taken){goto L_001feb80;}}
/* 001fec10: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_001fec14:;
/* 001fec14: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001fec18: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fec1c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001fec20: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001fec24: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001fec28: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001fec2c: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001fec30: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001fec34: jr ra */ /* delay 001fec38 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_001fec40(FusionValues *c){
/* 001fec40: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 001fec44: andi a1,a1,0xff */ c->r[5]=c->r[5]&UINT64_C(0xff);
/* 001fec48: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 001fec4c: sll a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]<<1u);
/* 001fec50: addu a1,a1,a0 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[4]);
/* 001fec54: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fec58: sh zero,0x86(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x00000086),(uint16_t)c->r[0]);
/* 001fec5c: j 0x00213350 */ /* delay 001fec60 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);ps2FusionSortSkills_00213350(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);return;
}

static void body_001fec68(FusionValues *c){
/* 001fec68: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 001fec6c: andi a0,a0,0xffff */ c->r[4]=c->r[4]&UINT64_C(0xffff);
/* 001fec70: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001fec74: move s1,a1 */ c->r[17]=c->r[5];
/* 001fec78: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001fec7c: move a3,zero */ c->r[7]=c->r[0];
/* 001fec80: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 001fec84: move a1,zero */ c->r[5]=c->r[0];
/* 001fec88: lhu v0,0x86(s1) */ c->r[2]=hword((uint32_t)c->r[17]+UINT32_C(0x00000086));
/* 001fec8c: beq v0,a0,0x001fecc8 */ {int taken=(c->r[2]==c->r[4]);/* delay 001fec90 */ c->r[6]=sx((uint32_t)c->r[17]+UINT32_C(0x00000006));if(taken){goto L_001fecc8;}}
/* 001fec94: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
L_001fec98:;
/* 001fec98: sll a3,a1,0x1 */ c->r[7]=sx((uint32_t)c->r[5]<<1u);
/* 001fec9c: slti v0,a1,0x18 */ c->r[2]=less(c->r[5],sx(UINT32_C(0x00000018)));
/* 001feca0: beq v0,zero,0x001fecc8 */ {int taken=(c->r[2]==c->r[0]);/* delay 001feca4 */ c->r[3]=sx((uint32_t)c->r[7]+(uint32_t)c->r[6]);if(taken){goto L_001fecc8;}}
/* 001feca8: lhu v0,0x80(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x00000080));
/* 001fecac: nop  */ (void)0;
/* 001fecb0: nop  */ (void)0;
/* 001fecb4: bnel v0,a0,0x001fec98 */ {int taken=(c->r[2]!=c->r[4]);if(taken){/* delay 001fecb8 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));goto L_001fec98;}}
/* 001fecbc: b 0x001feccc */ /* delay 001fecc0 */ c->r[2]=sx((uint32_t)c->r[7]+(uint32_t)c->r[6]);goto L_001feccc;
L_001fecc8:;
/* 001fecc8: addu v0,a3,a2 */ c->r[2]=sx((uint32_t)c->r[7]+(uint32_t)c->r[6]);
L_001feccc:;
/* 001feccc: move a0,s1 */ c->r[4]=c->r[17];
/* 001fecd0: lhu s0,0x80(v0) */ c->r[16]=hword((uint32_t)c->r[2]+UINT32_C(0x00000080));
/* 001fecd4: jal 0x001fec40 */ c->r[31]=UINT64_C(0x001fecdc);/* delay 001fecd8 */ c->r[5]=c->r[5]&UINT64_C(0xff);body_001fec40(c);
/* 001fecdc: move a1,s1 */ c->r[5]=c->r[17];
/* 001fece0: jal 0x001fed00 */ c->r[31]=UINT64_C(0x001fece8);/* delay 001fece4 */ c->r[4]=c->r[16];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbAddSkill((uint16_t)A0,UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001fece8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001fecec: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001fecf0: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001fecf4: jr ra */ /* delay 001fecf8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_001ff428(FusionValues *c){
/* 001ff428: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 001ff42c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001ff430: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001ff434: move s2,a0 */ c->r[18]=c->r[4];
/* 001ff438: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 001ff43c: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001ff440: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 001ff444: sd ra,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[31]);
/* 001ff448: jal 0x001ff3b8 */ c->r[31]=UINT64_C(0x001ff450);/* delay 001ff44c */ c->r[19]=c->r[0];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbCalcTotalKeisyoSkillRate(UNIT(A0));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ff450: move s0,v0 */ c->r[16]=c->r[2];
/* 001ff454: beq s0,zero,0x001ff4b0 */ {int taken=(c->r[16]==c->r[0]);/* delay 001ff458 */ c->r[4]=c->r[0];if(taken){goto L_001ff4b0;}}
/* 001ff45c: jal 0x002c0ba8 */ c->r[31]=UINT64_C(0x001ff464);/* delay 001ff460 */ c->r[17]=c->r[0];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRand(A0==0?NULL:(uint32_t *)at((uint32_t)A0)));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ff464: beql s0,zero,0x001ff46c */ {int taken=(c->r[16]==c->r[0]);if(taken){/* delay 001ff468 */ nocturne_break(7);goto L_001ff46c;}}
L_001ff46c:;
/* 001ff46c: divu v0,s0 */ {uint32_t n=(uint32_t)c->r[2],d=(uint32_t)c->r[16];c->lo=d?sx(n/d):UINT64_MAX;c->hi=sx(d?n%d:n);}
/* 001ff470: addiu s0,s2,0x86 */ c->r[16]=sx((uint32_t)c->r[18]+UINT32_C(0x00000086));
/* 001ff474: mfhi s4 */ c->r[20]=c->hi;
L_001ff478:;
/* 001ff478: lhu a1,0x0(s0) */ c->r[5]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 001ff47c: jal 0x00222bf0 */ c->r[31]=UINT64_C(0x001ff484);/* delay 001ff480 */ c->r[4]=c->r[18];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=cmbCalcKeisyoSkillRate(UNIT(A0),(uint16_t)A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ff484: addu s3,s3,v0 */ c->r[19]=sx((uint32_t)c->r[19]+(uint32_t)c->r[2]);
/* 001ff488: slt v0,s4,s3 */ c->r[2]=less(c->r[20],c->r[19]);
/* 001ff48c: beq v0,zero,0x001ff4a0 */ {int taken=(c->r[2]==c->r[0]);/* delay 001ff490 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));if(taken){goto L_001ff4a0;}}
/* 001ff494: b 0x001ff4b0 */ /* delay 001ff498 */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));goto L_001ff4b0;
L_001ff4a0:;
/* 001ff4a0: slti v0,s1,0x18 */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000018)));
/* 001ff4a4: bne v0,zero,0x001ff478 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001ff4a8 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000002));if(taken){goto L_001ff478;}}
/* 001ff4ac: move v0,zero */ c->r[2]=c->r[0];
L_001ff4b0:;
/* 001ff4b0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001ff4b4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001ff4b8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001ff4bc: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001ff4c0: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001ff4c4: ld ra,0x28(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001ff4c8: jr ra */ /* delay 001ff4cc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_001ff4d0(FusionValues *c){
/* 001ff4d0: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 001ff4d4: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001ff4d8: move s2,t0 */ c->r[18]=c->r[8];
/* 001ff4dc: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 001ff4e0: move s3,a3 */ c->r[19]=c->r[7];
/* 001ff4e4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001ff4e8: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001ff4ec: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 001ff4f0: lb s0,0x38(a0) */ c->r[16]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[4]+UINT32_C(0x00000038)));
/* 001ff4f4: lbu v0,0x38(a1) */ c->r[2]=*at((uint32_t)c->r[5]+UINT32_C(0x00000038));
/* 001ff4f8: addu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 001ff4fc: sll v0,v0,0x18 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);
/* 001ff500: beq a2,zero,0x001ff540 */ {int taken=(c->r[6]==c->r[0]);/* delay 001ff504 */ c->r[16]=sar((uint32_t)c->r[2],24u);if(taken){goto L_001ff540;}}
/* 001ff508: lbu v0,0x38(a2) */ c->r[2]=*at((uint32_t)c->r[6]+UINT32_C(0x00000038));
/* 001ff50c: lwc1 f2,-0x5d8c(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa274));
/* 001ff510: addu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 001ff514: lwc1 f1,-0x5d88(gp) */ c->f[1]=word((uint32_t)c->r[28]+UINT32_C(0xffffa278));
/* 001ff518: sll v0,v0,0x18 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);
/* 001ff51c: sra s0,v0,0x18 */ c->r[16]=sar((uint32_t)c->r[2],24u);
/* 001ff520: mtc1 s0,f0 */ c->f[0]=(uint32_t)c->r[16];
/* 001ff524: cvt.s.W f0,f0 */ c->f[0]=EE_FPU_CVT_S_W(c->f[0]);
/* 001ff528: add.S f0,f0,f2 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[2]);
/* 001ff52c: nop  */ (void)0;
/* 001ff530: nop  */ (void)0;
/* 001ff534: div.S f0,f0,f1 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[1]);
/* 001ff538: b 0x001ff560 */ /* delay 001ff53c */ (void)0;goto L_001ff560;
L_001ff540:;
/* 001ff540: mtc1 s0,f0 */ c->f[0]=(uint32_t)c->r[16];
/* 001ff544: cvt.s.W f0,f0 */ c->f[0]=EE_FPU_CVT_S_W(c->f[0]);
/* 001ff548: lwc1 f1,-0x5d84(gp) */ c->f[1]=word((uint32_t)c->r[28]+UINT32_C(0xffffa27c));
/* 001ff54c: lwc1 f2,-0x5d80(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa280));
/* 001ff550: add.S f0,f0,f1 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[1]);
/* 001ff554: nop  */ (void)0;
/* 001ff558: nop  */ (void)0;
/* 001ff55c: div.S f0,f0,f2 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[2]);
L_001ff560:;
/* 001ff560: cvt.w.S f1,f0 */ c->f[1]=EE_FPU_CVT_W_S(c->f[0]);
/* 001ff564: mfc1 v0,f1 */ c->r[2]=sx(c->f[1]);
/* 001ff568: sll v0,v0,0x18 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);
/* 001ff56c: beq s2,zero,0x001ff578 */ {int taken=(c->r[18]==c->r[0]);/* delay 001ff570 */ c->r[16]=sar((uint32_t)c->r[2],24u);if(taken){goto L_001ff578;}}
/* 001ff574: sb zero,0x10(s2) */ *at((uint32_t)c->r[18]+UINT32_C(0x00000010))=(uint8_t)c->r[0];
L_001ff578:;
/* 001ff578: jal 0x001fee30 */ c->r[31]=UINT64_C(0x001ff580);/* delay 001ff57c */ c->r[4]=c->r[19];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)cmbChkKeisyoSkillNums(UNIT(A0));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ff580: beql v0,zero,0x001ff624 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 001ff584 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_001ff624;}}
/* 001ff588: lhu v0,0x38(s3) */ c->r[2]=hword((uint32_t)c->r[19]+UINT32_C(0x00000038));
/* 001ff58c: addu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 001ff590: slti v0,v0,0x9 */ c->r[2]=less(c->r[2],sx(UINT32_C(0x00000009)));
/* 001ff594: bne v0,zero,0x001ff5ac */ {int taken=(c->r[2]!=c->r[0]);/* delay 001ff598 */ c->r[2]=sx(UINT32_C(0x00000008));if(taken){goto L_001ff5ac;}}
/* 001ff59c: lbu v1,0x38(s3) */ c->r[3]=*at((uint32_t)c->r[19]+UINT32_C(0x00000038));
/* 001ff5a0: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 001ff5a4: sll v0,v0,0x18 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);
/* 001ff5a8: sra s0,v0,0x18 */ c->r[16]=sar((uint32_t)c->r[2],24u);
L_001ff5ac:;
/* 001ff5ac: blezl s0,0x001ff624 */ {int taken=((neg(c->r[16])||!c->r[16]));if(taken){/* delay 001ff5b0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_001ff624;}}
/* 001ff5b4: nop  */ (void)0;
L_001ff5b8:;
/* 001ff5b8: jal 0x001ff428 */ c->r[31]=UINT64_C(0x001ff5c0);/* delay 001ff5bc */ c->r[4]=c->r[19];body_001ff428(c);
/* 001ff5c0: move a1,s3 */ c->r[5]=c->r[19];
/* 001ff5c4: move s1,v0 */ c->r[17]=c->r[2];
/* 001ff5c8: addiu v0,s0,-0x1 */ c->r[2]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 001ff5cc: move a0,s1 */ c->r[4]=c->r[17];
/* 001ff5d0: bne s1,zero,0x001ff5e0 */ {int taken=(c->r[17]!=c->r[0]);/* delay 001ff5d4 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);if(taken){goto L_001ff5e0;}}
/* 001ff5d8: b 0x001ff618 */ /* delay 001ff5dc */ c->r[16]=sar((uint32_t)c->r[2],24u);goto L_001ff618;
L_001ff5e0:;
/* 001ff5e0: jal 0x001fec68 */ c->r[31]=UINT64_C(0x001ff5e8);/* delay 001ff5e4 */ (void)0;body_001fec68(c);
/* 001ff5e8: addiu v1,s0,-0x1 */ c->r[3]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 001ff5ec: bltz v0,0x001ff618 */ {int taken=(neg(c->r[2]));/* delay 001ff5f0 */ c->r[4]=sx((uint32_t)c->r[3]<<24u);if(taken){goto L_001ff618;}}
/* 001ff5f4: beq s2,zero,0x001ff618 */ {int taken=(c->r[18]==c->r[0]);/* delay 001ff5f8 */ c->r[16]=sar((uint32_t)c->r[4],24u);if(taken){goto L_001ff618;}}
/* 001ff5fc: lbu v0,0x10(s2) */ c->r[2]=*at((uint32_t)c->r[18]+UINT32_C(0x00000010));
/* 001ff600: sll v1,v0,0x18 */ c->r[3]=sx((uint32_t)c->r[2]<<24u);
/* 001ff604: addiu v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 001ff608: sra v1,v1,0x17 */ c->r[3]=sar((uint32_t)c->r[3],23u);
/* 001ff60c: sb v0,0x10(s2) */ *at((uint32_t)c->r[18]+UINT32_C(0x00000010))=(uint8_t)c->r[2];
/* 001ff610: addu v1,s2,v1 */ c->r[3]=sx((uint32_t)c->r[18]+(uint32_t)c->r[3]);
/* 001ff614: sh s1,0x0(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x00000000),(uint16_t)c->r[17]);
L_001ff618:;
/* 001ff618: bgtz s0,0x001ff5b8 */ {int taken=((!neg(c->r[16])&&c->r[16]));/* delay 001ff61c */ (void)0;if(taken){goto L_001ff5b8;}}
/* 001ff620: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_001ff624:;
/* 001ff624: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001ff628: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001ff62c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001ff630: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001ff634: jr ra */ /* delay 001ff638 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_001ff648(FusionValues *c){
/* 001ff648: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 001ff64c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001ff650: andi s0,a0,0xffff */ c->r[16]=c->r[4]&UINT64_C(0xffff);
/* 001ff654: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001ff658: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 001ff65c: jal 0x001e9998 */ c->r[31]=UINT64_C(0x001ff664);/* delay 001ff660 */ c->r[17]=sx(UINT32_C(0xffffffff));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(evtGetAgeOfMoon());nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ff664: move a1,v0 */ c->r[5]=c->r[2];
/* 001ff668: sll v0,s0,0x4 */ c->r[2]=sx((uint32_t)c->r[16]<<4u);
/* 001ff66c: subu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[16]);
/* 001ff670: li s0,-0x1 */ c->r[16]=sx(UINT32_C(0xffffffff));
/* 001ff674: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001ff678: lui v1,0x33 */ c->r[3]=sx(UINT32_C(0x00330000));
/* 001ff67c: lui a2,0x35 */ c->r[6]=sx(UINT32_C(0x00350000));
/* 001ff680: addu a2,a2,v0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[2]);
/* 001ff684: lbu a2,-0x683c(a2) */ c->r[6]=*at((uint32_t)c->r[6]+UINT32_C(0xffff97c4));
/* 001ff688: addiu v1,v1,-0x2230 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffddd0));
/* 001ff68c: move a0,zero */ c->r[4]=c->r[0];
L_001ff690:;
/* 001ff690: lbu v0,0x0(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 001ff694: slt v0,a1,v0 */ c->r[2]=less(c->r[5],c->r[2]);
/* 001ff698: bnel v0,zero,0x001ff6b0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001ff69c */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));goto L_001ff6b0;}}
/* 001ff6a0: lbu v0,0x1(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 001ff6a4: slt v0,v0,a1 */ c->r[2]=less(c->r[2],c->r[5]);
/* 001ff6a8: movz s1,a0,v0 */ if(c->r[2]==0){c->r[17]=c->r[4];}
/* 001ff6ac: addiu a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
L_001ff6b0:;
/* 001ff6b0: sltiu v0,a0,0x5 */ c->r[2]=(c->r[4]<sx(UINT32_C(0x00000005)));
/* 001ff6b4: bne v0,zero,0x001ff690 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001ff6b8 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000002));if(taken){goto L_001ff690;}}
/* 001ff6bc: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 001ff6c0: move a0,zero */ c->r[4]=c->r[0];
/* 001ff6c4: addiu a1,v0,-0x2220 */ c->r[5]=sx((uint32_t)c->r[2]+UINT32_C(0xffffdde0));
/* 001ff6c8: addu v0,a0,a1 */ c->r[2]=sx((uint32_t)c->r[4]+(uint32_t)c->r[5]);
/* 001ff6cc: nop  */ (void)0;
L_001ff6d0:;
/* 001ff6d0: lbu v1,0x0(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 001ff6d4: xor v1,v1,a2 */ c->r[3]=c->r[3]^c->r[6];
/* 001ff6d8: movz s0,a0,v1 */ if(c->r[3]==0){c->r[16]=c->r[4];}
/* 001ff6dc: addiu a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
/* 001ff6e0: sltiu v0,a0,0x4 */ c->r[2]=(c->r[4]<sx(UINT32_C(0x00000004)));
/* 001ff6e4: bnel v0,zero,0x001ff6d0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001ff6e8 */ c->r[2]=sx((uint32_t)c->r[4]+(uint32_t)c->r[5]);goto L_001ff6d0;}}
/* 001ff6ec: li a0,0x8d */ c->r[4]=sx(UINT32_C(0x0000008d));
/* 001ff6f0: jal 0x002443f8 */ c->r[31]=UINT64_C(0x001ff6f8);/* delay 001ff6f4 */ c->r[5]=sx(UINT32_C(0x00000001));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=(uint64_t)(int64_t)datCheckItem((int32_t)(uint32_t)A0,(int32_t)(uint32_t)A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ff6f8: beql v0,zero,0x001ff744 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 001ff6fc */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_001ff744;}}
/* 001ff700: bltz s1,0x001ff740 */ {int taken=(neg(c->r[17]));/* delay 001ff704 */ c->r[2]=c->r[0];if(taken){goto L_001ff740;}}
/* 001ff708: bgezl s0,0x001ff718 */ {int taken=(!neg(c->r[16]));if(taken){/* delay 001ff70c */ c->r[2]=sx((uint32_t)c->r[16]<<2u);goto L_001ff718;}}
/* 001ff710: b 0x001ff744 */ /* delay 001ff714 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_001ff744;
L_001ff718:;
/* 001ff718: addu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 001ff71c: addu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[17]);
/* 001ff720: sll v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]<<1u);
/* 001ff724: lui s0,0x33 */ c->r[16]=sx(UINT32_C(0x00330000));
/* 001ff728: addu s0,s0,v0 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[2]);
/* 001ff72c: lhu s0,-0x2218(s0) */ c->r[16]=hword((uint32_t)c->r[16]+UINT32_C(0xffffdde8));
/* 001ff730: jal 0x001fd3b0 */ c->r[31]=UINT64_C(0x001ff738);/* delay 001ff734 */ c->r[4]=c->r[16];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentEventDisabled_001FD3B0(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ff738: movn s0,zero,v0 */ if(c->r[2]!=0){c->r[16]=c->r[0];}
/* 001ff73c: move v0,s0 */ c->r[2]=c->r[16];
L_001ff740:;
/* 001ff740: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_001ff744:;
/* 001ff744: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001ff748: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001ff74c: jr ra */ /* delay 001ff750 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_001ff758(FusionValues *c){
/* 001ff758: lhu v1,0x4(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 001ff75c: li a0,0xc0 */ c->r[4]=sx(UINT32_C(0x000000c0));
/* 001ff760: beq v1,a0,0x001ff788 */ {int taken=(c->r[3]==c->r[4]);/* delay 001ff764 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_001ff788;}}
/* 001ff768: lhu v1,0x4(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000004));
/* 001ff76c: beq v1,a0,0x001ff788 */ {int taken=(c->r[3]==c->r[4]);/* delay 001ff770 */ (void)0;if(taken){goto L_001ff788;}}
/* 001ff774: beql a2,zero,0x001ff788 */ {int taken=(c->r[6]==c->r[0]);if(taken){/* delay 001ff778 */ c->r[2]=c->r[0];goto L_001ff788;}}
/* 001ff77c: lhu v1,0x4(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 001ff780: bnel v1,a0,0x001ff788 */ {int taken=(c->r[3]!=c->r[4]);if(taken){/* delay 001ff784 */ c->r[2]=c->r[0];goto L_001ff788;}}
L_001ff788:;
/* 001ff788: jr ra */ /* delay 001ff78c */ (void)0;return;
}

static void body_001ff790(FusionValues *c){
/* 001ff790: addiu sp,sp,-0x170 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffe90));
/* 001ff794: sll t2,t2,0x18 */ c->r[10]=sx((uint32_t)c->r[10]<<24u);
/* 001ff798: sd s1,0x128(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000128),c->r[17]);
/* 001ff79c: move s1,a0 */ c->r[17]=c->r[4];
/* 001ff7a0: sd s2,0x130(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000130),c->r[18]);
/* 001ff7a4: move s2,a1 */ c->r[18]=c->r[5];
/* 001ff7a8: sd s3,0x138(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000138),c->r[19]);
/* 001ff7ac: move s3,a2 */ c->r[19]=c->r[6];
/* 001ff7b0: sd s4,0x140(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000140),c->r[20]);
/* 001ff7b4: sll t0,t0,0x18 */ c->r[8]=sx((uint32_t)c->r[8]<<24u);
/* 001ff7b8: sd s5,0x148(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000148),c->r[21]);
/* 001ff7bc: move s5,a3 */ c->r[21]=c->r[7];
/* 001ff7c0: sd s6,0x150(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000150),c->r[22]);
/* 001ff7c4: sra s6,t0,0x18 */ c->r[22]=sar((uint32_t)c->r[8],24u);
/* 001ff7c8: sd s8,0x160(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000160),c->r[30]);
/* 001ff7cc: sll t1,t1,0x18 */ c->r[9]=sx((uint32_t)c->r[9]<<24u);
/* 001ff7d0: sd s0,0x120(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000120),c->r[16]);
/* 001ff7d4: li t4,0x1 */ c->r[12]=sx(UINT32_C(0x00000001));
/* 001ff7d8: sd s7,0x158(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000158),c->r[23]);
/* 001ff7dc: sra t2,t2,0x18 */ c->r[10]=sar((uint32_t)c->r[10],24u);
/* 001ff7e0: sd ra,0x168(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000168),c->r[31]);
/* 001ff7e4: sra s4,t1,0x18 */ c->r[20]=sar((uint32_t)c->r[9],24u);
/* 001ff7e8: lw v0,0x0(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 001ff7ec: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 001ff7f0: andi v0,v0,0x1000 */ c->r[2]=c->r[2]&UINT64_C(0x1000);
/* 001ff7f4: sw t3,0x118(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000118),(uint32_t)c->r[11]);
/* 001ff7f8: sltu s8,zero,v0 */ c->r[30]=(c->r[0]<c->r[2]);
/* 001ff7fc: andi v1,v1,0x1000 */ c->r[3]=c->r[3]&UINT64_C(0x1000);
/* 001ff800: sw t2,0x114(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000114),(uint32_t)c->r[10]);
/* 001ff804: movn s8,t4,v1 */ if(c->r[3]!=0){c->r[30]=c->r[12];}
/* 001ff808: beq s3,zero,0x001ff81c */ {int taken=(c->r[19]==c->r[0]);/* delay 001ff80c */ sw((uint32_t)c->r[29]+UINT32_C(0x0000011c),(uint32_t)c->r[0]);if(taken){goto L_001ff81c;}}
/* 001ff810: lw v0,0x0(s3) */ c->r[2]=sx(word((uint32_t)c->r[19]+UINT32_C(0x00000000)));
/* 001ff814: andi v0,v0,0x1000 */ c->r[2]=c->r[2]&UINT64_C(0x1000);
/* 001ff818: movn s8,t4,v0 */ if(c->r[2]!=0){c->r[30]=c->r[12];}
L_001ff81c:;
/* 001ff81c: jal 0x001ff758 */ c->r[31]=UINT64_C(0x001ff824);/* delay 001ff820 */ sh((uint32_t)c->r[29]+UINT32_C(0x00000024),(uint16_t)c->r[0]);body_001ff758(c);
/* 001ff824: beql v0,zero,0x001ff838 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 001ff828 */ c->r[4]=hword((uint32_t)c->r[17]+UINT32_C(0x00000004));goto L_001ff838;}}
/* 001ff82c: sh zero,0x4(s5) */ sh((uint32_t)c->r[21]+UINT32_C(0x00000004),(uint16_t)c->r[0]);
/* 001ff830: b 0x001ffc44 */ /* delay 001ff834 */ c->r[2]=c->r[0];goto L_001ffc44;
L_001ff838:;
/* 001ff838: lhu a1,0x4(s2) */ c->r[5]=hword((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 001ff83c: beql a0,a1,0x001ffc44 */ {int taken=(c->r[4]==c->r[5]);if(taken){/* delay 001ff840 */ sh((uint32_t)c->r[21]+UINT32_C(0x00000004),(uint16_t)c->r[0]);goto L_001ffc44;}}
/* 001ff844: beql s3,zero,0x001ff868 */ {int taken=(c->r[19]==c->r[0]);if(taken){/* delay 001ff848 */ c->r[3]=hword((uint32_t)c->r[17]+UINT32_C(0x00000014));goto L_001ff868;}}
/* 001ff84c: lhu v1,0x4(s3) */ c->r[3]=hword((uint32_t)c->r[19]+UINT32_C(0x00000004));
/* 001ff850: beql a0,v1,0x001ffc44 */ {int taken=(c->r[4]==c->r[3]);if(taken){/* delay 001ff854 */ sh((uint32_t)c->r[21]+UINT32_C(0x00000004),(uint16_t)c->r[0]);goto L_001ffc44;}}
/* 001ff858: bnel a1,v1,0x001ff868 */ {int taken=(c->r[5]!=c->r[3]);if(taken){/* delay 001ff85c */ c->r[3]=hword((uint32_t)c->r[17]+UINT32_C(0x00000014));goto L_001ff868;}}
/* 001ff860: b 0x001ffc44 */ /* delay 001ff864 */ sh((uint32_t)c->r[21]+UINT32_C(0x00000004),(uint16_t)c->r[0]);goto L_001ffc44;
L_001ff868:;
/* 001ff868: lhu v0,0x14(s2) */ c->r[2]=hword((uint32_t)c->r[18]+UINT32_C(0x00000014));
/* 001ff86c: sltu v0,v0,v1 */ c->r[2]=(c->r[2]<c->r[3]);
/* 001ff870: beq v0,zero,0x001ff8a8 */ {int taken=(c->r[2]==c->r[0]);/* delay 001ff874 */ c->r[4]=c->r[17];if(taken){goto L_001ff8a8;}}
/* 001ff878: addiu s7,sp,0x10 */ c->r[23]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001ff87c: move a1,sp */ c->r[5]=c->r[29];
/* 001ff880: move a2,s7 */ c->r[6]=c->r[23];
/* 001ff884: jal 0x001fe170 */ c->r[31]=UINT64_C(0x001ff88c);/* delay 001ff888 */ c->r[4]=c->r[17];body_001fe170(c);
/* 001ff88c: move a0,s2 */ c->r[4]=c->r[18];
/* 001ff890: addiu a1,sp,0x2 */ c->r[5]=sx((uint32_t)c->r[29]+UINT32_C(0x00000002));
/* 001ff894: jal 0x001fe170 */ c->r[31]=UINT64_C(0x001ff89c);/* delay 001ff898 */ c->r[6]=sx((uint32_t)c->r[29]+UINT32_C(0x00000011));body_001fe170(c);
/* 001ff89c: b 0x001ff8c8 */ /* delay 001ff8a0 */ (void)0;goto L_001ff8c8;
L_001ff8a8:;
/* 001ff8a8: addiu a1,sp,0x2 */ c->r[5]=sx((uint32_t)c->r[29]+UINT32_C(0x00000002));
/* 001ff8ac: addiu a2,sp,0x11 */ c->r[6]=sx((uint32_t)c->r[29]+UINT32_C(0x00000011));
/* 001ff8b0: jal 0x001fe170 */ c->r[31]=UINT64_C(0x001ff8b8);/* delay 001ff8b4 */ c->r[23]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_001fe170(c);
/* 001ff8b8: move a0,s2 */ c->r[4]=c->r[18];
/* 001ff8bc: move a1,sp */ c->r[5]=c->r[29];
/* 001ff8c0: jal 0x001fe170 */ c->r[31]=UINT64_C(0x001ff8c8);/* delay 001ff8c4 */ c->r[6]=c->r[23];body_001fe170(c);
L_001ff8c8:;
/* 001ff8c8: beq s3,zero,0x001ff8e8 */ {int taken=(c->r[19]==c->r[0]);/* delay 001ff8cc */ c->r[4]=c->r[19];if(taken){goto L_001ff8e8;}}
/* 001ff8d0: addiu a1,sp,0x4 */ c->r[5]=sx((uint32_t)c->r[29]+UINT32_C(0x00000004));
/* 001ff8d4: jal 0x001fe170 */ c->r[31]=UINT64_C(0x001ff8dc);/* delay 001ff8d8 */ c->r[6]=sx((uint32_t)c->r[29]+UINT32_C(0x00000012));body_001fe170(c);
/* 001ff8dc: b 0x001ff8f0 */ /* delay 001ff8e0 */ c->r[2]=hword((uint32_t)c->r[29]+UINT32_C(0x00000004));goto L_001ff8f0;
L_001ff8e8:;
/* 001ff8e8: sh zero,0x4(sp) */ sh((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint16_t)c->r[0]);
/* 001ff8ec: lhu v0,0x4(sp) */ c->r[2]=hword((uint32_t)c->r[29]+UINT32_C(0x00000004));
L_001ff8f0:;
/* 001ff8f0: beq v0,zero,0x001ff9b0 */ {int taken=(c->r[2]==c->r[0]);/* delay 001ff8f4 */ c->r[4]=c->r[17];if(taken){goto L_001ff9b0;}}
/* 001ff8f8: move a1,s2 */ c->r[5]=c->r[18];
/* 001ff8fc: move a2,s3 */ c->r[6]=c->r[19];
/* 001ff900: move a3,s6 */ c->r[7]=c->r[22];
/* 001ff904: jal 0x001fd878 */ c->r[31]=UINT64_C(0x001ff90c);/* delay 001ff908 */ c->r[8]=c->r[20];body_001fd878(c);
/* 001ff90c: move s0,v0 */ c->r[16]=c->r[2];
/* 001ff910: bne s0,zero,0x001ff974 */ {int taken=(c->r[16]!=c->r[0]);/* delay 001ff914 */ c->r[2]=sx(UINT32_C(0x00000009));if(taken){goto L_001ff974;}}
/* 001ff918: lhu a0,0x0(sp) */ c->r[4]=hword((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001ff91c: lhu a1,0x2(sp) */ c->r[5]=hword((uint32_t)c->r[29]+UINT32_C(0x00000002));
/* 001ff920: jal 0x001fd730 */ c->r[31]=UINT64_C(0x001ff928);/* delay 001ff924 */ c->r[6]=hword((uint32_t)c->r[29]+UINT32_C(0x00000004));body_001fd730(c);
/* 001ff928: move s0,v0 */ c->r[16]=c->r[2];
/* 001ff92c: bne s0,zero,0x001ff974 */ {int taken=(c->r[16]!=c->r[0]);/* delay 001ff930 */ c->r[2]=sx(UINT32_C(0x00000009));if(taken){goto L_001ff974;}}
/* 001ff934: lhu a0,0x0(sp) */ c->r[4]=hword((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001ff938: lhu a1,0x2(sp) */ c->r[5]=hword((uint32_t)c->r[29]+UINT32_C(0x00000002));
/* 001ff93c: jal 0x001fd610 */ c->r[31]=UINT64_C(0x001ff944);/* delay 001ff940 */ c->r[6]=hword((uint32_t)c->r[29]+UINT32_C(0x00000004));body_001fd610(c);
/* 001ff944: andi s0,v0,0xff */ c->r[16]=c->r[2]&UINT64_C(0xff);
/* 001ff948: beq s0,zero,0x001ff980 */ {int taken=(c->r[16]==c->r[0]);/* delay 001ff94c */ c->r[7]=c->r[20];if(taken){goto L_001ff980;}}
/* 001ff950: move a1,s2 */ c->r[5]=c->r[18];
/* 001ff954: move a2,s3 */ c->r[6]=c->r[19];
/* 001ff958: jal 0x001fdec0 */ c->r[31]=UINT64_C(0x001ff960);/* delay 001ff95c */ c->r[4]=c->r[17];body_001fdec0(c);
/* 001ff960: move a0,s0 */ c->r[4]=c->r[16];
/* 001ff964: jal 0x001fdf78 */ c->r[31]=UINT64_C(0x001ff96c);/* delay 001ff968 */ c->r[5]=c->r[2]&UINT64_C(0xff);body_001fdf78(c);
/* 001ff96c: move s0,v0 */ c->r[16]=c->r[2];
/* 001ff970: li v0,0x9 */ c->r[2]=sx(UINT32_C(0x00000009));
L_001ff974:;
/* 001ff974: b 0x001ff9d0 */ /* delay 001ff978 */ *at((uint32_t)c->r[29]+UINT32_C(0x00000110))=(uint8_t)c->r[2];goto L_001ff9d0;
L_001ff980:;
/* 001ff980: move a3,s6 */ c->r[7]=c->r[22];
/* 001ff984: move t0,s4 */ c->r[8]=c->r[20];
/* 001ff988: move t2,s7 */ c->r[10]=c->r[23];
/* 001ff98c: move a0,s1 */ c->r[4]=c->r[17];
/* 001ff990: move a1,s2 */ c->r[5]=c->r[18];
/* 001ff994: move a2,s3 */ c->r[6]=c->r[19];
/* 001ff998: jal 0x001fea20 */ c->r[31]=UINT64_C(0x001ff9a0);/* delay 001ff99c */ c->r[9]=c->r[29];body_001fea20(c);
/* 001ff9a0: move s0,v0 */ c->r[16]=c->r[2];
/* 001ff9a4: li v0,0x8 */ c->r[2]=sx(UINT32_C(0x00000008));
/* 001ff9a8: b 0x001ff9d0 */ /* delay 001ff9ac */ *at((uint32_t)c->r[29]+UINT32_C(0x00000110))=(uint8_t)c->r[2];goto L_001ff9d0;
L_001ff9b0:;
/* 001ff9b0: move a2,s6 */ c->r[6]=c->r[22];
/* 001ff9b4: move a3,s4 */ c->r[7]=c->r[20];
/* 001ff9b8: move t1,s7 */ c->r[9]=c->r[23];
/* 001ff9bc: move a1,s2 */ c->r[5]=c->r[18];
/* 001ff9c0: move t0,sp */ c->r[8]=c->r[29];
/* 001ff9c4: jal 0x001fe690 */ c->r[31]=UINT64_C(0x001ff9cc);/* delay 001ff9c8 */ c->r[10]=sx((uint32_t)c->r[29]+UINT32_C(0x00000110));body_001fe690(c);
/* 001ff9cc: andi s0,v0,0xffff */ c->r[16]=c->r[2]&UINT64_C(0xffff);
L_001ff9d0:;
/* 001ff9d0: lbu v1,0x110(sp) */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000110));
/* 001ff9d4: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 001ff9d8: beq v1,v0,0x001ff9e8 */ {int taken=(c->r[3]==c->r[2]);/* delay 001ff9dc */ c->r[2]=sx(UINT32_C(0x00000008));if(taken){goto L_001ff9e8;}}
/* 001ff9e0: bne v1,v0,0x001ffa38 */ {int taken=(c->r[3]!=c->r[2]);/* delay 001ff9e4 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000007)));if(taken){goto L_001ffa38;}}
L_001ff9e8:;
/* 001ff9e8: jal 0x001ff648 */ c->r[31]=UINT64_C(0x001ff9f0);/* delay 001ff9ec */ c->r[4]=c->r[16];body_001ff648(c);
/* 001ff9f0: move a0,v0 */ c->r[4]=c->r[2];
/* 001ff9f4: beq a0,zero,0x001ffa30 */ {int taken=(c->r[4]==c->r[0]);/* delay 001ff9f8 */ c->r[2]=*at((uint32_t)c->r[29]+UINT32_C(0x00000010));if(taken){goto L_001ffa30;}}
/* 001ff9fc: li v1,0x26 */ c->r[3]=sx(UINT32_C(0x00000026));
/* 001ffa00: beq v0,v1,0x001ffa10 */ {int taken=(c->r[2]==c->r[3]);/* delay 001ffa04 */ c->r[2]=*at((uint32_t)c->r[29]+UINT32_C(0x00000011));if(taken){goto L_001ffa10;}}
/* 001ffa08: bne v0,v1,0x001ffa20 */ {int taken=(c->r[2]!=c->r[3]);/* delay 001ffa0c */ c->r[2]=sx(UINT32_C(0x0000000c));if(taken){goto L_001ffa20;}}
L_001ffa10:;
/* 001ffa10: sb zero,0x110(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000110))=(uint8_t)c->r[0];
/* 001ffa14: move s0,zero */ c->r[16]=c->r[0];
/* 001ffa18: b 0x001ffa34 */ /* delay 001ffa1c */ c->r[3]=c->r[0];goto L_001ffa34;
L_001ffa20:;
/* 001ffa20: move s0,a0 */ c->r[16]=c->r[4];
/* 001ffa24: sb v0,0x110(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000110))=(uint8_t)c->r[2];
/* 001ffa28: b 0x001ffa34 */ /* delay 001ffa2c */ c->r[3]=sx(UINT32_C(0x0000000c));goto L_001ffa34;
L_001ffa30:;
/* 001ffa30: lbu v1,0x110(sp) */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000110));
L_001ffa34:;
/* 001ffa34: slti v0,v1,0x7 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000007)));
L_001ffa38:;
/* 001ffa38: beq v0,zero,0x001ffa60 */ {int taken=(c->r[2]==c->r[0]);/* delay 001ffa3c */ c->r[2]=sx(UINT32_C(0x00000008));if(taken){goto L_001ffa60;}}
/* 001ffa40: slti v0,v1,0x3 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000003)));
/* 001ffa44: beq v0,zero,0x001ffa6c */ {int taken=(c->r[2]==c->r[0]);/* delay 001ffa48 */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000114)));if(taken){goto L_001ffa6c;}}
/* 001ffa4c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 001ffa50: beq v1,v0,0x001ffa68 */ {int taken=(c->r[3]==c->r[2]);/* delay 001ffa54 */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));if(taken){goto L_001ffa68;}}
/* 001ffa58: b 0x001ffab4 */ /* delay 001ffa5c */ (void)0;goto L_001ffab4;
L_001ffa60:;
/* 001ffa60: bne v1,v0,0x001ffab0 */ {int taken=(c->r[3]!=c->r[2]);/* delay 001ffa64 */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));if(taken){goto L_001ffab0;}}
L_001ffa68:;
/* 001ffa68: lw v0,0x114(sp) */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000114)));
L_001ffa6c:;
/* 001ffa6c: beq v0,zero,0x001ffab0 */ {int taken=(c->r[2]==c->r[0]);/* delay 001ffa70 */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));if(taken){goto L_001ffab0;}}
/* 001ffa74: jal 0x001fe2f0 */ c->r[31]=UINT64_C(0x001ffa7c);/* delay 001ffa78 */ (void)0;nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentCheck_001FE2F0();nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffa7c: beq v0,zero,0x001ffab0 */ {int taken=(c->r[2]==c->r[0]);/* delay 001ffa80 */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));if(taken){goto L_001ffab0;}}
/* 001ffa84: jal 0x001fe368 */ c->r[31]=UINT64_C(0x001ffa8c);/* delay 001ffa88 */ (void)0;nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentType_001FE368();nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffa8c: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 001ffa90: addiu v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 001ffa94: addiu a0,a0,-0x3508 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0xffffcaf8));
/* 001ffa98: sll v0,v0,0x18 */ c->r[2]=sx((uint32_t)c->r[2]<<24u);
/* 001ffa9c: sra v0,v0,0x18 */ c->r[2]=sar((uint32_t)c->r[2],24u);
/* 001ffaa0: addiu a1,v0,-0x1 */ c->r[5]=sx((uint32_t)c->r[2]+UINT32_C(0xffffffff));
/* 001ffaa4: jal 0x002d4748 */ c->r[31]=UINT64_C(0x001ffaac);/* delay 001ffaa8 */ sw((uint32_t)c->r[29]+UINT32_C(0x0000011c),(uint32_t)c->r[2]);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2LibcPrintf(A0,A1);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffaac: lw v1,0x11c(sp) */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));
L_001ffab0:;
/* 001ffab0: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_001ffab4:;
/* 001ffab4: bne v1,v0,0x001ffad0 */ {int taken=(c->r[3]!=c->r[2]);/* delay 001ffab8 */ (void)0;if(taken){goto L_001ffad0;}}
/* 001ffabc: jal 0x001fe410 */ c->r[31]=UINT64_C(0x001ffac4);/* delay 001ffac0 */ c->r[4]=c->r[16];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentSelect_001FE410(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffac4: move s0,v0 */ c->r[16]=c->r[2];
/* 001ffac8: li v0,0xa */ c->r[2]=sx(UINT32_C(0x0000000a));
/* 001ffacc: sb v0,0x110(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000110))=(uint8_t)c->r[2];
L_001ffad0:;
/* 001ffad0: beq s0,zero,0x001ffbe8 */ {int taken=(c->r[16]==c->r[0]);/* delay 001ffad4 */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000110));if(taken){goto L_001ffbe8;}}
/* 001ffad8: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 001ffadc: beq v1,v0,0x001ffb10 */ {int taken=(c->r[3]==c->r[2]);/* delay 001ffae0 */ c->r[20]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));if(taken){goto L_001ffb10;}}
/* 001ffae4: move a0,s0 */ c->r[4]=c->r[16];
/* 001ffae8: jal 0x001fee68 */ c->r[31]=UINT64_C(0x001ffaf0);/* delay 001ffaec */ c->r[5]=c->r[20];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);cmbCopyDefaultDevilToStock((uint16_t)A0,UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffaf0: move a0,s4 */ c->r[4]=c->r[20];
/* 001ffaf4: jal 0x001feb28 */ c->r[31]=UINT64_C(0x001ffafc);/* delay 001ffaf8 */ c->r[5]=c->r[17];body_001feb28(c);
/* 001ffafc: move a0,s4 */ c->r[4]=c->r[20];
/* 001ffb00: jal 0x001feb28 */ c->r[31]=UINT64_C(0x001ffb08);/* delay 001ffb04 */ c->r[5]=c->r[18];body_001feb28(c);
/* 001ffb08: b 0x001ffb7c */ /* delay 001ffb0c */ (void)0;goto L_001ffb7c;
L_001ffb10:;
/* 001ffb10: lhu v0,0x4(s1) */ c->r[2]=hword((uint32_t)c->r[17]+UINT32_C(0x00000004));
/* 001ffb14: bne v0,s0,0x001ffb50 */ {int taken=(c->r[2]!=c->r[16]);/* delay 001ffb18 */ (void)0;if(taken){goto L_001ffb50;}}
/* 001ffb1c: move a1,s1 */ c->r[5]=c->r[17];
/* 001ffb20: jal 0x001fef20 */ c->r[31]=UINT64_C(0x001ffb28);/* delay 001ffb24 */ c->r[4]=c->r[20];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);cmbCopyCustomDevilToStock(UNIT(A0),UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffb28: jal 0x001ff0a8 */ c->r[31]=UINT64_C(0x001ffb30);/* delay 001ffb2c */ c->r[4]=c->r[20];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);cmbClearKeisyoSkill(UNIT(A0));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffb30: move a0,s4 */ c->r[4]=c->r[20];
/* 001ffb34: jal 0x001feb28 */ c->r[31]=UINT64_C(0x001ffb3c);/* delay 001ffb38 */ c->r[5]=c->r[18];body_001feb28(c);
/* 001ffb3c: lhu a0,0x4(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 001ffb40: jal 0x001fd538 */ c->r[31]=UINT64_C(0x001ffb48);/* delay 001ffb44 */ c->r[5]=c->r[20];body_001fd538(c);
/* 001ffb48: b 0x001ffb7c */ /* delay 001ffb4c */ (void)0;goto L_001ffb7c;
L_001ffb50:;
/* 001ffb50: move a1,s2 */ c->r[5]=c->r[18];
/* 001ffb54: jal 0x001fef20 */ c->r[31]=UINT64_C(0x001ffb5c);/* delay 001ffb58 */ c->r[4]=c->r[20];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);cmbCopyCustomDevilToStock(UNIT(A0),UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffb5c: jal 0x001ff0a8 */ c->r[31]=UINT64_C(0x001ffb64);/* delay 001ffb60 */ c->r[4]=c->r[20];nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);cmbClearKeisyoSkill(UNIT(A0));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffb64: move a0,s4 */ c->r[4]=c->r[20];
/* 001ffb68: jal 0x001feb28 */ c->r[31]=UINT64_C(0x001ffb70);/* delay 001ffb6c */ c->r[5]=c->r[17];body_001feb28(c);
/* 001ffb70: lhu a0,0x4(s1) */ c->r[4]=hword((uint32_t)c->r[17]+UINT32_C(0x00000004));
/* 001ffb74: jal 0x001fd538 */ c->r[31]=UINT64_C(0x001ffb7c);/* delay 001ffb78 */ c->r[5]=c->r[20];body_001fd538(c);
L_001ffb7c:;
/* 001ffb7c: beq s3,zero,0x001ffbd0 */ {int taken=(c->r[19]==c->r[0]);/* delay 001ffb80 */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));if(taken){goto L_001ffbd0;}}
/* 001ffb84: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 001ffb88: beq v1,v0,0x001ffba0 */ {int taken=(c->r[3]==c->r[2]);/* delay 001ffb8c */ c->r[4]=c->r[20];if(taken){goto L_001ffba0;}}
/* 001ffb90: move a1,s1 */ c->r[5]=c->r[17];
/* 001ffb94: move a2,s2 */ c->r[6]=c->r[18];
/* 001ffb98: jal 0x001fe880 */ c->r[31]=UINT64_C(0x001ffba0);/* delay 001ffb9c */ c->r[7]=c->r[19];body_001fe880(c);
L_001ffba0:;
/* 001ffba0: move a0,s4 */ c->r[4]=c->r[20];
/* 001ffba4: jal 0x001feb28 */ c->r[31]=UINT64_C(0x001ffbac);/* delay 001ffba8 */ c->r[5]=c->r[19];body_001feb28(c);
/* 001ffbac: move a0,s1 */ c->r[4]=c->r[17];
/* 001ffbb0: lw t0,0x118(sp) */ c->r[8]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000118)));
/* 001ffbb4: move a1,s2 */ c->r[5]=c->r[18];
/* 001ffbb8: move a2,s3 */ c->r[6]=c->r[19];
/* 001ffbbc: jal 0x001ff4d0 */ c->r[31]=UINT64_C(0x001ffbc4);/* delay 001ffbc0 */ c->r[7]=c->r[20];body_001ff4d0(c);
/* 001ffbc4: b 0x001ffbec */ /* delay 001ffbc8 */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));goto L_001ffbec;
L_001ffbd0:;
/* 001ffbd0: lw t0,0x118(sp) */ c->r[8]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000118)));
/* 001ffbd4: move a0,s1 */ c->r[4]=c->r[17];
/* 001ffbd8: move a1,s2 */ c->r[5]=c->r[18];
/* 001ffbdc: move a3,s4 */ c->r[7]=c->r[20];
/* 001ffbe0: jal 0x001ff4d0 */ c->r[31]=UINT64_C(0x001ffbe8);/* delay 001ffbe4 */ c->r[6]=c->r[0];body_001ff4d0(c);
L_001ffbe8:;
/* 001ffbe8: lw v1,0x11c(sp) */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x0000011c)));
L_001ffbec:;
/* 001ffbec: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 001ffbf0: bne v1,v0,0x001ffc08 */ {int taken=(c->r[3]!=c->r[2]);/* delay 001ffbf4 */ (void)0;if(taken){goto L_001ffc08;}}
/* 001ffbf8: jal 0x001fe570 */ c->r[31]=UINT64_C(0x001ffc00);/* delay 001ffbfc */ c->r[4]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FusionAccidentBoost_001FE570(A0);nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffc00: li v0,0xb */ c->r[2]=sx(UINT32_C(0x0000000b));
/* 001ffc04: sb v0,0x110(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000110))=(uint8_t)c->r[2];
L_001ffc08:;
/* 001ffc08: beq s5,zero,0x001ffc38 */ {int taken=(c->r[21]==c->r[0]);/* delay 001ffc0c */ c->r[4]=c->r[21];if(taken){goto L_001ffc38;}}
/* 001ffc10: jal 0x001fef20 */ c->r[31]=UINT64_C(0x001ffc18);/* delay 001ffc14 */ c->r[5]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);cmbCopyCustomDevilToStock(UNIT(A0),UNIT(A1));nocturneFusionCoreSetStackPointer((uint32_t)c->r[29]);
/* 001ffc18: lhu v0,0x8(s5) */ c->r[2]=hword((uint32_t)c->r[21]+UINT32_C(0x00000008));
/* 001ffc1c: lhu v1,0xc(s5) */ c->r[3]=hword((uint32_t)c->r[21]+UINT32_C(0x0000000c));
/* 001ffc20: sh v0,0x6(s5) */ sh((uint32_t)c->r[21]+UINT32_C(0x00000006),(uint16_t)c->r[2]);
/* 001ffc24: beq s8,zero,0x001ffc38 */ {int taken=(c->r[30]==c->r[0]);/* delay 001ffc28 */ sh((uint32_t)c->r[21]+UINT32_C(0x0000000a),(uint16_t)c->r[3]);if(taken){goto L_001ffc38;}}
/* 001ffc2c: lw v0,0x0(s5) */ c->r[2]=sx(word((uint32_t)c->r[21]+UINT32_C(0x00000000)));
/* 001ffc30: ori v0,v0,0x1000 */ c->r[2]=c->r[2]|UINT64_C(0x1000);
/* 001ffc34: sw v0,0x0(s5) */ sw((uint32_t)c->r[21]+UINT32_C(0x00000000),(uint32_t)c->r[2]);
L_001ffc38:;
/* 001ffc38: lbu v0,0x110(sp) */ c->r[2]=*at((uint32_t)c->r[29]+UINT32_C(0x00000110));
/* 001ffc3c: xori v1,s0,0x0 */ c->r[3]=c->r[16]^UINT64_C(0x0);
/* 001ffc40: movz v0,zero,v1 */ if(c->r[3]==0){c->r[2]=c->r[0];}
L_001ffc44:;
/* 001ffc44: ld s0,0x120(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000120));
/* 001ffc48: ld s1,0x128(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000128));
/* 001ffc4c: ld s2,0x130(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000130));
/* 001ffc50: ld s3,0x138(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000138));
/* 001ffc54: ld s4,0x140(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000140));
/* 001ffc58: ld s5,0x148(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000148));
/* 001ffc5c: ld s6,0x150(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000150));
/* 001ffc60: ld s7,0x158(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000158));
/* 001ffc64: ld s8,0x160(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000160));
/* 001ffc68: ld ra,0x168(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000168));
/* 001ffc6c: jr ra */ /* delay 001ffc70 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000170));return;
}
static FusionValues begin(void){FusionValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneFusionCoreStackPointer();return c;}
uint64_t ps2FusionCore_001FD498(uint64_t p0){FusionValues c=begin();c.r[4]=p0;body_001fd498(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FD4E0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;body_001fd4e0(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FD538(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fd538(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FD610(uint64_t p0,uint64_t p1,uint64_t p2){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_001fd610(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FD708(uint64_t p0,uint64_t p1,uint64_t p2){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_001fd708(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FD730(uint64_t p0,uint64_t p1,uint64_t p2){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_001fd730(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FD878(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;c.r[8]=p4;body_001fd878(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FDA08(uint64_t p0){FusionValues c=begin();c.r[4]=p0;body_001fda08(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FDAC0(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fdac0(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FDCA0(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fdca0(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FDD18(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fdd18(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FDDE8(uint64_t p0,uint64_t p1,uint64_t p2){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_001fdde8(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FDEC0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;body_001fdec0(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FDF78(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fdf78(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2FusionCore_001FE170(uint64_t p0,uint64_t p1,uint64_t p2){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_001fe170(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2FusionCore_001FE1A0(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fe1a0(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FE280(uint64_t p0){FusionValues c=begin();c.r[4]=p0;body_001fe280(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FE5F0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;body_001fe5f0(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FE690(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;c.r[8]=p4;c.r[9]=p5;c.r[10]=p6;body_001fe690(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2FusionCore_001FE880(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;body_001fe880(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2FusionCore_001FEA20(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;c.r[8]=p4;c.r[9]=p5;c.r[10]=p6;body_001fea20(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2FusionCore_001FEB28(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001feb28(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);}
void ps2FusionCore_001FEC40(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fec40(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2FusionCore_001FEC68(uint64_t p0,uint64_t p1){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;body_001fec68(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FF428(uint64_t p0){FusionValues c=begin();c.r[4]=p0;body_001ff428(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2FusionCore_001FF4D0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;c.r[8]=p4;body_001ff4d0(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2FusionCore_001FF648(uint64_t p0){FusionValues c=begin();c.r[4]=p0;body_001ff648(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FF758(uint64_t p0,uint64_t p1,uint64_t p2){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_001ff758(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2FusionCore_001FF790(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6,uint64_t p7){FusionValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;c.r[8]=p4;c.r[9]=p5;c.r[10]=p6;c.r[11]=p7;body_001ff790(&c);nocturneFusionCoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
