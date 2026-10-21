/* Original002B6060: Z rotation into VF28..31, including its actual96B frame.
 * The native VF0 words form the basis; no implicit identity/W is supplied.
 * Real recovered libm bodies execute both trig calls. No original execution
 * or captured output is used by this implementation.
 */
#include "battle_action_rotation_frame.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include "effect_trig_frames.h"
#include "ee_vu_rotation.h"
#include <stdlib.h>
#include <string.h>

static uint64_t low(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t sp(void){return (uint32_t)low(29);}
static void *at(uint32_t a){return nocturneResolveBattleActionConsumerAddress(a);}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}
static void pextuw(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);z[0]=y[2];z[1]=x[2];z[2]=y[3];z[3]=x[3];nocturneEffectHostCpuWrite(d,z);}
static void sq(unsigned r,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(r,q);memcpy(at(a&~15u),q,16);}
static void loadVu(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a),16);EE_ROT_VU_WRITE(r,q);}

void ps2BattleActionRotationZNative_002B6060(float angle)
{
    uint32_t *f=nocturneEffectHostFpr();
    f[12]=bits(angle);nocturneEffectAxisNoteEntry(0x002b6060u);
    uint64_t incoming=low(31);
    /* 6060 ADDIU;6064/68 SWC1;606C SD. */
    set(29,sx(sp()-96u));
    put(sp()+72u,f[20]);put(sp()+80u,f[21]);
    {uint64_t ra=low(31);memcpy(at(sp()+64u),&ra,8);}
    /* 6070 JAL Cos;6074 MOV.S delay. */
    set(31,sx(0x002b6078u));f[20]=f[12];
    f[0]=bits(ps2EffectLibmCosFloat_002CF4F8(real(f[12])));
    /* 6078 MOV.S;607C JAL Sin;6080 MOV.S delay. */
    f[12]=f[20];set(31,sx(0x002b6084u));f[21]=f[0];
    f[0]=bits(ps2EffectLibmSinFloat_002CF5D0(real(f[12])));
    /* 6084 QMFC2 and6088/8C/90 PEXTUW snapshot full native quads. */
    {uint32_t q[4];EE_ROT_VU_READ(0,q);nocturneEffectHostCpuWrite(5,q);}
    pextuw(4,0,5);pextuw(2,0,4);pextuw(3,4,0);
    /* 6094..60A0 SQ: every basis word derives from actual VF0/zero. */
    sq(2,sp());sq(3,sp()+16u);sq(4,sp()+32u);sq(5,sp()+48u);
    /* 60A4 NEG.S;60A8..60B4 SWC1. */
    f[1]=f[0]^UINT32_C(0x80000000);
    put(sp(),f[21]);put(sp()+4u,f[0]);put(sp()+16u,f[1]);put(sp()+20u,f[21]);
    /* 60B8..60C4 LQC2, followed by live60C8 LD and60CC/D0 LWC1. */
    loadVu(28,sp());loadVu(29,sp()+16u);loadVu(30,sp()+32u);loadVu(31,sp()+48u);
    {uint64_t ra;memcpy(&ra,at(sp()+64u),8);set(31,ra);}
    f[21]=word(sp()+80u);f[20]=word(sp()+72u);
    /* 60D4 JR latches its source before60D8 ADDIU delay. */
    {uint64_t target=low(31);set(29,sx(sp()+96u));if((uint32_t)target!=(uint32_t)incoming)abort();}
}
