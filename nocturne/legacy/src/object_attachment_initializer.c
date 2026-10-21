/* Complete24-word original model-resource initializer; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "object_attachment.h"
#include "object_attachment_initializer.h"
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

static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);























static void body_001dc0f8(void);
static void body_001dc0f8(void){
uint64_t incoming=cpu(31);
/* 001dc0f8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dc0fc: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001dc100: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 001dc104: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc108: jal 0x002a8080 */ set(31,UINT64_C(0x001dc110));/* delay 001dc10c */ set(6,cpu(0));nocturneObjectAttachmentCall(UINT32_C(0x002a8080),UINT32_C(0x001dc108));
/* 001dc110: sw v0,-0x2274(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdd8c)),(uint32_t)cpu(2));
/* 001dc114: lui v0,0x33 */ set(2,sx(UINT32_C(0x00330000)));
/* 001dc118: lui v1,0x33 */ set(3,sx(UINT32_C(0x00330000)));
/* 001dc11c: move a0,zero */ set(4,cpu(0));
/* 001dc120: addiu a3,v0,-0x3ba8 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0xffffc458)));
/* 001dc124: addiu a2,v1,-0x3b88 */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0xffffc478)));
/* 001dc128: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
/* 001dc12c: nop  */ 
L_001dc130:;
/* 001dc130: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001dc134: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 001dc138: addu v1,v0,a2 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 001dc13c: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 001dc140: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001dc144: bne a0,a1,0x001dc130 */ {int taken=(cpu(4)!=cpu(5));/* delay 001dc148 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));if(taken){goto L_001dc130;}}
/* 001dc14c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc150: jr ra */ {uint64_t target=cpu(31);/* delay 001dc154 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint32_t nocturneObjectAttachmentInitializerBody(uint32_t entry){switch(entry){
case UINT32_C(0x001dc0f8):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_001dc0f8();return 1u;
default:return 0u;}}

void ps2ObjectAttachmentInitializeModelResources_001DC0F8(void){
body_001dc0f8();
return;
}
