/* Complete native pose and quaternion transform bodies. Managed HD objects
 * identify roles; native memory layout, operation order and cache are retained. */
#include "basic_pose.h"
#include "path_rotation.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
#include "material_lists.h"
#include "material_construction_release.h"
#include "ee_vu_rotation.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t p){return p&0x80000000u?UINT64_C(0xffffffff00000000)|p:p;}
static void copy16(uint32_t to,uint32_t from){uint32_t v[4];memcpy(v,at(from),16);memcpy(at(to),v,16);}
static void load(unsigned r,uint32_t p){uint32_t v[4];memcpy(v,at(p),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t p){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(p),v,16);}
static void move(unsigned d,unsigned s,unsigned mask){uint32_t a[4],v[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(d,v);for(unsigned i=0;i<4;i++)if(mask&(8u>>i))v[i]=a[i];EE_ROT_VU_WRITE(d,v);}
static void split(uint64_t result,uint32_t *v,uint32_t *of){*v=(uint32_t)result;*of=(uint32_t)(result>>32)&1;}
/* bc=4 chooses the matching lane; lower values broadcast X/Y/Z/W. */
static void value(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned bc,unsigned op)
{
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<4;i++)if(mask&(8u>>i))v[i]=(uint32_t)(op==0?EE_ROT_VU_ADD(a[i],b[bc==4?i:bc]):op==1?EE_ROT_VU_SUB(a[i],b[bc==4?i:bc]):EE_ROT_VU_MUL(a[i],b[bc==4?i:bc]));
 EE_ROT_VU_WRITE(d,v);
}
/* op: ADD=0, MUL=1, MADD=2, MSUB=3. Destination32 denotes ACC. */
static void accum(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned bc,unsigned op)
{
 uint32_t a[4],b[4],v[4],ac[4],of[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_ACC_READ(ac,of);
 if(d==32)memcpy(v,ac,16);else EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<4;i++)if(mask&(8u>>i)){
  uint32_t next;uint64_t r=op==0?EE_ROT_VU_ADD(a[i],b[bc]):op==1?EE_ROT_VU_MUL(a[i],b[bc]):EE_ROT_VU_MAC(ac[i],a[i],b[bc],of[i],op==3);
  split(r,&v[i],&next);if(d==32)of[i]=next;
 }
 if(d==32)EE_ROT_ACC_WRITE(v,of);else EE_ROT_VU_WRITE(d,v);
}
static void cross(unsigned d,unsigned s,unsigned t,int subtract)
{
 uint32_t a[4],b[4],ac[4],of[4],v[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_ACC_READ(ac,of);
 if(d==32)memcpy(v,ac,16);else EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<3;i++){
  uint32_t next;uint64_t r=subtract?EE_ROT_VU_MAC(ac[i],a[(i+1)%3],b[(i+2)%3],of[i],1):EE_ROT_VU_MUL(a[(i+1)%3],b[(i+2)%3]);
  split(r,&v[i],&next);if(d==32)of[i]=next;
 }
 if(d==32)EE_ROT_ACC_WRITE(v,of);else EE_ROT_VU_WRITE(d,v);
}
/* 002C0488: retains native intermediate registers and ACC, no normalization. */
void sdfQuatMult(void)
{
 value(2,10,11,15,4,2);cross(32,10,11,0);
 accum(32,11,10,14,3,2);accum(32,10,11,14,3,2);cross(10,11,10,1);
 accum(32,10,11,1,3,1);accum(32,0,2,1,0,3);accum(32,0,2,1,1,3);accum(10,0,2,1,2,3);
}
/* 002C0600: all four rows and native scratch/ACC values, including nonunit q. */
void sdfQuatToMatrix(void)
{
 value(1,0,0,14,3,0);value(2,10,10,15,4,0);
 value(28,0,0,1,0,2);value(29,0,0,1,0,2);value(30,0,0,1,0,2);
 value(3,10,2,15,4,2);value(4,10,2,15,1,2);value(5,10,2,15,2,2);value(6,10,2,15,0,2);
 accum(32,0,0,14,3,0);accum(32,1,3,8,1,3);accum(28,1,3,8,2,3);
 accum(32,1,3,4,0,3);accum(29,1,3,4,2,3);accum(32,1,3,2,0,3);accum(30,1,3,2,1,3);
 accum(32,1,4,4,0,1);accum(28,1,5,4,3,3);value(29,4,5,8,3,0);value(30,5,4,8,3,1);
 accum(32,1,5,2,0,1);accum(28,1,4,2,3,2);accum(32,1,5,2,1,1);accum(29,1,6,2,3,3);value(30,5,6,4,3,0);move(31,0,15);
}
/* 0010DE28: untouched matrices/backups, identity position/quaternion and scale. */
void dds3InitPoseSetValue(uint64_t pose)
{
 uint32_t p=(uint32_t)pose;store(0,p+64);store(0,p+80);
 value(10,0,0,14,3,0);value(10,0,0,1,0,2);store(10,p+96);
}
/* 0010DD38: existing pointer succeeds only through the initial zero result. */
uint64_t dds3InitPoseSet(uint64_t basic)
{
 if(!basic)return 0;uint32_t b=(uint32_t)basic;if(word(b+28))return 0;
 uint32_t p=ps2PoolAllocate(208);if(!p)return 0;
 put(p+192,1);dds3InitPoseSetValue(sx(p));store(0,p+176);put(b+28,p);put(p+196,0);put(p+200,0);return 1;
}
void dds3FreePoseSet(uint64_t basic)
{if(basic){uint32_t b=(uint32_t)basic,p=word(b+28);if(p){ps2PoolRelease(p);put(b+28,0);}}}
void dds3OnPoseSetFlag(uint64_t p,uint64_t f){put((uint32_t)p+192,word((uint32_t)p+192)|(uint32_t)f);}
void dds3OffPoseSetFlag(uint64_t p,uint64_t f){put((uint32_t)p+192,word((uint32_t)p+192)&~(uint32_t)f);}
uint64_t dds3CheckPoseSetFlag(uint64_t p,uint64_t f){return (sx(word((uint32_t)p+192))&f)!=0;}
void dds3BackupPoseSet(uint64_t pose){uint32_t p=(uint32_t)pose;copy16(p+160,p+96);copy16(p+144,p+80);copy16(p+128,p+64);}
void dds3SetRadiusPoseSet(uint64_t basic,float radius){uint32_t b;memcpy(&b,&radius,4);put(word((uint32_t)basic+28)+196,b);}
static uint32_t changed(uint64_t basic){uint32_t p=word((uint32_t)basic+28);put(p+192,(word(p+192)|1u)&~2u);return p;}
static void set(uint64_t basic,uint64_t v,unsigned offset){uint32_t p=changed(basic);copy16(p+offset,(uint32_t)v);}
void dds3SetPosPoseSet(uint64_t b,uint64_t v){set(b,v,64);}
void dds3SetRotPoseSet(uint64_t b,uint64_t v){set(b,v,80);}
void dds3SetSclPoseSet(uint64_t b,uint64_t v){set(b,v,96);}
void dds3GetPosPoseSetMCR(uint64_t b){load(10,word((uint32_t)b+28)+64);move(10,0,1);}
void dds3GetRotPoseSet(uint64_t b){load(10,word((uint32_t)b+28)+80);ps2QuaternionNormalize();}
void dds3AddPosPoseSet(uint64_t b,uint64_t v){uint32_t p=changed(b)+64;load(10,p);load(11,(uint32_t)v);value(10,10,11,15,4,0);store(10,p);}
void dds3AddRotPoseSet(uint64_t b,uint64_t v){uint32_t p=changed(b)+80;load(10,p);load(11,(uint32_t)v);sdfQuatMult();store(10,p);}
void dds3AddSclPoseSet(uint64_t b,uint64_t v){uint32_t p=changed(b)+96;load(10,p);load(11,(uint32_t)v);value(10,10,11,15,4,2);store(10,p);}
void ps2PoseBuildTransform(uint64_t scale,uint64_t rotation,uint64_t position)
{
 load(10,(uint32_t)rotation);sdfQuatToMatrix();load(10,(uint32_t)scale);
 value(28,28,10,15,0,2);value(29,29,10,15,1,2);value(30,30,10,15,2,2);
 load(10,(uint32_t)position);move(10,0,1);move(31,10,15);
}
void dds3GetTMPoseSet(uint64_t basic)
{
 uint32_t p=word((uint32_t)basic+28),flags=word(p+192);
 if(flags&2){for(unsigned i=0;i<4;i++)load(28+i,p+i*16);}
 else{put(p+192,flags|2);ps2PoseBuildTransform(p+96,p+80,p+64);for(unsigned i=0;i<4;i++)store(28+i,p+i*16);}
}
uint64_t dds3SerializeID(void){uint32_t v=(word(0x54e9c0)+1)&65535;put(0x54e9c0,v);return v;}
