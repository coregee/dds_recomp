/* Native camera view construction, preserving vector scratch and ACC values. */
#include "camera_view.h"
#include "basic_creation.h"
#include "basic_pose.h"
#include "ee_vu_rotation.h"
#include "script_construction.h"
#include "script_movie.h"
#include "libc_stream.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static void load(unsigned r,uint32_t p){uint32_t v[4];memcpy(v,at(p),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t p){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(p),v,16);}
static void move(unsigned d,unsigned s,unsigned mask){uint32_t a[4],v[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(d,v);for(unsigned i=0;i<4;i++)if(mask&(8u>>i))v[i]=a[i];EE_ROT_VU_WRITE(d,v);}
static void value(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned op)
{
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<4;i++)if(mask&(8u>>i))v[i]=(uint32_t)(op==0?EE_ROT_VU_ADD(a[i],b[i]):op==1?EE_ROT_VU_SUB(a[i],b[i]):EE_ROT_VU_MUL(a[i],b[i]));EE_ROT_VU_WRITE(d,v);
}
/* op: ADD=0,MUL=1,MADD=2,MSUB=3,SUB=4. d32 denotes ACC. */
static void accum(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned bc,unsigned op)
{
 uint32_t a[4],b[4],v[4],ac[4],of[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_ACC_READ(ac,of);
 if(d==32)memcpy(v,ac,16);else EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<4;i++)if(mask&(8u>>i)){
  uint32_t bv=b[bc==4?i:bc];uint64_t r=op==0?EE_ROT_VU_ADD(a[i],bv):op==1?EE_ROT_VU_MUL(a[i],bv):op==4?EE_ROT_VU_SUB(a[i],bv):EE_ROT_VU_MAC(ac[i],a[i],bv,of[i],op==3);
  v[i]=(uint32_t)r;if(d==32)of[i]=(uint32_t)(r>>32)&1;
 }
 if(d==32)EE_ROT_ACC_WRITE(v,of);else EE_ROT_VU_WRITE(d,v);
}
static void cross(unsigned d,unsigned s,unsigned t,int subtract)
{
 uint32_t a[4],b[4],v[4],ac[4],of[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_ACC_READ(ac,of);
 if(d==32)memcpy(v,ac,16);else EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<3;i++){uint64_t r=subtract?EE_ROT_VU_MAC(ac[i],a[(i+1)%3],b[(i+2)%3],of[i],1):EE_ROT_VU_MUL(a[(i+1)%3],b[(i+2)%3]);v[i]=(uint32_t)r;if(d==32)of[i]=(uint32_t)(r>>32)&1;}
 if(d==32)EE_ROT_ACC_WRITE(v,of);else EE_ROT_VU_WRITE(d,v);
}
static void normalize3(void)
{
 value(2,10,10,14,2);accum(32,0,2,1,0,1);accum(32,0,2,1,1,2);accum(2,0,2,1,2,2);
 uint32_t v[4];EE_ROT_VU_READ(2,v);uint32_t q=EE_ROT_VU_RSQRT(0x3f800000,v[3]);EE_ROT_Q_WRITE(q);
 EE_ROT_VU_READ(10,v);for(unsigned i=0;i<3;i++)v[i]=(uint32_t)EE_ROT_VU_MUL(v[i],q);EE_ROT_VU_WRITE(10,v);
}
void ps2RigidInverseMatrix(void)
{
 uint32_t a[4],b[4],c[4],out[4];EE_ROT_VU_READ(28,a);EE_ROT_VU_READ(29,b);EE_ROT_VU_READ(30,c);
 move(31,0,1);for(unsigned i=0;i<3;i++){out[0]=a[i];out[1]=b[i];out[2]=c[i];out[3]=0;EE_ROT_VU_WRITE(28+i,out);}
 accum(32,0,0,14,4,4);accum(32,28,31,14,0,3);accum(32,29,31,14,1,3);accum(31,30,31,14,2,3);
}
void sdfVu0LookAtMatrix(uint64_t target,uint64_t position,uint64_t up)
{
 load(10,(uint32_t)position);move(31,10,15);move(11,10,15);load(10,(uint32_t)target);value(10,10,11,15,1);normalize3();move(30,10,15);move(11,10,15);
 load(10,(uint32_t)up);cross(32,10,11,0);cross(10,11,10,1);normalize3();move(28,10,15);move(11,10,15);move(10,30,15);cross(32,10,11,0);cross(10,11,10,1);move(29,10,15);ps2RigidInverseMatrix();
}
static void transform(void){accum(32,28,10,15,0,1);accum(32,29,10,15,1,2);accum(32,30,10,15,2,2);accum(10,31,10,15,3,2);}
void dds3CameraObjectBasicMakeCamera(uint64_t basic)
{
 uint32_t b=(uint32_t)basic,p=word(b+28),d=word(b+24);load(10,p+80);sdfQuatToMatrix();load(10,d+80);transform();move(10,0,1);store(10,d+112);
 if(word(d+132)==1){load(10,d+64);transform();load(11,p+64);value(10,10,11,15,0);move(10,0,1);store(10,d+96);}
 sdfVu0LookAtMatrix(d+96,p+64,d+112);store(28,d);store(29,d+16);store(30,d+32);store(31,d+48);
}
uint64_t dds3AddCameraObjectBasicTypeFree(uint64_t serial,uint64_t position,uint64_t rotation)
{
 uint32_t defaults[8];memcpy(defaults,at(0x530d38),32);uint64_t b=dds3AddCameraObjectBasicDef(serial);uint32_t d=word((uint32_t)b+24);
 put(d+132,1);put(d+140,word(0x54c1bc));dds3SetRotPoseSet(b,rotation);dds3SetPosPoseSet(b,position);dds3BackupPoseSet(word((uint32_t)b+28));memcpy(at(d+80),defaults,16);memcpy(at(d+64),defaults+4,16);dds3CameraObjectBasicMakeCamera(b);return b;
}
uint64_t dds3AddCameraObjectBasicTypeLookAt(uint64_t serial,uint64_t position,uint64_t target,uint64_t up)
{
 uint64_t b=dds3AddCameraObjectBasicDef(serial);uint32_t d=word((uint32_t)b+24);put(d+140,word(0x54c1c0));put(d+132,0);
 dds3SetPosPoseSet(b,position);dds3BackupPoseSet(word((uint32_t)b+28));uint32_t v[4];memcpy(v,at((uint32_t)up),16);memcpy(at(d+80),v,16);memcpy(v,at((uint32_t)target),16);memcpy(at(d+96),v,16);dds3CameraObjectBasicMakeCamera(b);return b;
}
uint64_t evtCommand_CAM_CREATE(void)
{
 uint32_t vectors[8];ps2Memset(vectors,0,16);ps2Memset(vectors+4,0,16);vectors[7]=0x3f800000;
 uint32_t local=nocturneLibcStreamLocalAddress(vectors,32);uint64_t serial=dds3SerializeID();uint64_t camera=dds3AddCameraObjectBasicTypeFree(serial,local,local+16);dds3SetRadiusPoseSet(camera,1.0f);scrSetIntReturnValue(serial);nocturneLibcStreamEndLocal();return 1;
}
