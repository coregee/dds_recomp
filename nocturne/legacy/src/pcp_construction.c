/* Original seven-entry PCP construction cohort; preset tables remain retail. */
#include "pcp_construction.h"
#include "model_memory_parts.h"
#include "model_pac_loading.h"
#include "model_effect_creation.h"
#include "model_cleanup.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "material_motion_scalars.h"
#include "polygon_prerequisites.h"
#include "battle_effect_copy.h"
#include "billboard_copy.h"
#include "d3p_loading.h"
#include "effect_matrix.h"
#include "libm_trig.h"
#include "resource_loader_flow.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "nocturne.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolvePcpConstructionAddress(a);}
static uint64_t ctor(uint32_t target,uint64_t data){return nocturnePcpConstructorCall(target,data);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
static uint64_t ctor(uint32_t target,uint64_t data){return ((uint64_t(*)(uint64_t))(uintptr_t)target)(data);}
#endif
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint32_t randWord(void){return sdfGetRand(at(0x316fe0));}
static uint32_t randFloat(void){return bits(sdfGetRandFloat(at(0x316fe0)));}
static uint32_t remainder(uint32_t n,uint32_t d){if(!d)nocturne_break(7);return n%d;}
static uint32_t divide(uint32_t n,uint32_t d){return d?n/d:UINT32_MAX;}
static uint64_t copyPart(uint64_t p){
 /* The previously recovered part-copy body has no host guest-frame helper.
  * Its original32-byte frame belongs around the actual call here. */
 ENTER(32);uint64_t v=dds3EffectPartCopy(p);LEAVE(32);return v;
}
static void blockCopy(uint32_t d,uint32_t s,unsigned bytes){
 for(unsigned i=0;i<64;i+=32){uint8_t v[32];memcpy(v,at(s+i),32);memcpy(at(d+i),v,32);}
 uint8_t tail[20];memcpy(tail,at(s+64),bytes-64);memcpy(at(d+64),tail,bytes-64);
}
uint64_t ps2PcpDescriptorKind(uint64_t data){return sx(r32((uint32_t)data));}
uint64_t ps2PcpDescriptorNumber(uint64_t data){return sx(r32((uint32_t)data+4));}
uint64_t ps2PcpDescriptorPartData(uint64_t data,uint64_t index){uint32_t d=(uint32_t)data;return sx(d+r32(d+((uint32_t)index<<4)+0x14));}
uint64_t ps2PcpDescriptorPartType(uint64_t data,uint64_t index){return sx(r32((uint32_t)data+((uint32_t)index<<4)+0x18));}
uint64_t ps2PcpDescriptorCreatePart(uint64_t data,uint64_t index){
 ENTER(32);uint32_t kind=(uint16_t)ps2PcpDescriptorPartType(data,index);
 uint64_t payload=ps2PcpDescriptorPartData(data,index);LEAVE(32);return dds3EffectPartCreate(kind,payload);
}
uint64_t ps2PcpWrapperCreate(uint64_t data){
 ENTER(32);uint32_t p=ps2PoolAllocate(12),kind=(uint32_t)ps2PcpDescriptorKind(data),number=(uint32_t)ps2PcpDescriptorNumber(data),table=0x31df90+kind*40;
 w32(p,kind);w32(p+4,number);uint64_t argument=data;
 if(!r32(table+12))argument=sx(r32(r32(0x31ddd0+kind*4)+number*4));
 w32(p+8,(uint32_t)ctor(r32(table),argument));LEAVE(32);return sx(p);
}
static void gradient(uint32_t p,uint32_t a,uint32_t b,uint32_t c,unsigned width,unsigned rise){
 int32_t steps=(int32_t)r32(p+8)/(int32_t)width;if(rise)steps>>=1;
 uint32_t aa=a&0xff000000,ba=b&0xff000000,ca=c&0xff000000;
 uint32_t da=divide(aa,(uint32_t)steps),db=divide(ba,(uint32_t)steps),dc=divide(ca,(uint32_t)steps);
 uint32_t rgb[3]={a&0xffffff,b&0xffffff,c&0xffffff};
 int32_t count=(int32_t)r32(p+4);
 if(count>0){uint32_t descriptors=r32(p+20);do{
  uint32_t out=r32(descriptors+4),alphas[3]={0,0,0},deltas[3]={da,db,dc};
  for(unsigned pass=0;pass<(rise?2u:1u);pass++){
   if(!rise||pass){alphas[0]=aa;alphas[1]=ba;alphas[2]=ca;}
   for(int32_t i=0;i<steps;i++){
    if(!rise||pass)for(unsigned k=0;k<3;k++)alphas[k]-=deltas[k];
    uint32_t colors[3]={rgb[0]|(alphas[0]&0xff000000),rgb[1]|(alphas[1]&0xff000000),rgb[2]|(alphas[2]&0xff000000)};
    w32(out,colors[2]);w32(out+4,colors[1]);w32(out+8,colors[0]);
    if(rise){w32(out+12,colors[1]);w32(out+16,colors[2]);out+=20;}
    else{w32(out+12,colors[0]);w32(out+16,colors[1]);w32(out+20,colors[2]);out+=24;}
    if(rise&&!pass)for(unsigned k=0;k<3;k++)alphas[k]+=deltas[k];
   }
  }
  descriptors+=20;
 }while(--count);}
}
void ps2PolygonFiveColorRiseFall(uint64_t system,uint64_t a,uint64_t b,uint64_t c){ENTER(48);gradient((uint32_t)system,(uint32_t)a,(uint32_t)b,(uint32_t)c,5,1);LEAVE(48);}
void ps2PolygonSixColorFade(uint64_t system,uint64_t a,uint64_t b,uint64_t c){ENTER(48);gradient((uint32_t)system,(uint32_t)a,(uint32_t)b,(uint32_t)c,6,0);LEAVE(48);}
void ps2PcpType1InitializeRecord(uint64_t object,uint64_t index){
 ENTER(32);uint32_t p=(uint32_t)object,r=r32(p+0x54)+(uint32_t)index*12;
 uint32_t first=randWord(),a=remainder(first,r32(p+0x30));w32(r,a);
 uint32_t second=randWord(),b=remainder(second,r32(p+0x34));w32(r+8,0x80808080);w32(r+4,b+1);LEAVE(32);
}
void ps2PcpType2InitializeRecord(uint64_t object,uint64_t index){
 ENTER(48);uint32_t p=(uint32_t)object,r=r32(p+0x48)+(uint32_t)index*20;
 for(unsigned k=0;k<3;k++){uint32_t f=EE_FPU_SUB_S(randFloat(),0x3f000000);w32(r+k*4,EE_FPU_ADD_S(f,f));}
 uint32_t a=randWord();w32(r+12,remainder(a,r32(p+0x24)));
 uint32_t b=randWord();w32(r+16,remainder(b,r32(p+0x28))+1);LEAVE(48);
}
uint64_t ps2PcpType0Create(uint64_t data){
 ENTER(32);uint32_t s=(uint32_t)data,h=ps2MemoryHandleAllocate((int32_t)(r32(s+20)*44+100)),p=ps2MemoryHandleAcquirePointer(h);
 blockCopy(p,s,76);w32(p+0x4c,p+100);w32(p+0x54,r32(s+0x1c));w32(p+0x58,r32(s+0x20));w32(p+0x60,h);
 uint32_t v=(uint32_t)ps2PolygonVertexCreate(sx(r32(p+20)),r16(p+0x30),0,4);w32(p+0x5c,v);
 ps2PolygonFiveColorRiseFall(sx(v),sx(r32(p+0x38)),sx(r32(p+0x40)),sx(r32(p+0x48)));
 ps2PolygonVertexSetMode(sx(v),r16(p+16));uint32_t count=r32(p+20),r=r32(p+0x4c);
 if(count){uint32_t i=0;do{w32(r,0);w32(r+4,0);w32(r+40,0);r+=44;i++;}while(i<r32(p+20));}
 w32(p+0x50,0x80808080);LEAVE(32);return sx(p);
}
uint64_t ps2PcpType1Create(uint64_t data){
 ENTER(32);uint32_t s=(uint32_t)data,h=ps2MemoryHandleAllocate((int32_t)(r32(s+0x24)*12+104)),p=ps2MemoryHandleAcquirePointer(h);
 blockCopy(p,s,84);w32(p+0x54,p+104);w32(p+0x64,h);
 uint32_t v=(uint32_t)ps2PolygonVertexCreate(sx(r32(p+0x24)),sx((uint32_t)r16(p+0x38)*2-1),0,4);w32(p+0x60,v);
 ps2PolygonFiveColorRiseFall(sx(v),sx(r32(p+0x40)),sx(r32(p+0x48)),sx(r32(p+0x50)));ps2PolygonVertexSetMode(sx(v),r16(p+0x20));
 if(r32(p+0x24)){uint32_t i=0;do{ps2PcpType1InitializeRecord(sx(p),i++);}while(i<r32(p+0x24));}
 w32(p+0x5c,0);w32(p+0x58,0x80808080);LEAVE(32);return sx(p);
}
uint64_t ps2PcpType2Create(uint64_t data){
 ENTER(32);uint32_t s=(uint32_t)data,h=ps2MemoryHandleAllocate((int32_t)(r32(s+0x18)*20+88)),p=ps2MemoryHandleAcquirePointer(h);
 blockCopy(p,s,72);w32(p+0x48,p+88);w32(p+0x54,h);
 uint32_t v=(uint32_t)ps2PolygonVertexCreate(sx(r32(p+0x18)),sx((uint32_t)r16(p+0x2c)*2-1),0,2);w32(p+0x50,v);
 ps2PolygonSixColorFade(sx(v),sx(r32(p+0x34)),sx(r32(p+0x3c)),sx(r32(p+0x44)));ps2PolygonVertexSetMode(sx(v),r16(p+0x10));
 if(r32(p+0x18)){uint32_t i=0;do{ps2PcpType2InitializeRecord(sx(p),i++);}while(i<r32(p+0x18));}
 LEAVE(32);return sx(p);
}
void ps2ModelChangeMotionSingle(uint64_t context,uint64_t group,uint64_t cut){ps2ModelChangeMotionEffects(context,group,cut,0,0.0f,0.0f);}
uint64_t ps2ModelPartClone(uint64_t context){ENTER(32);uint64_t group=mdlGetMajorNum(context),id=mdlGetMinorNum(context);uint64_t p=ps2ModelContextCreate(group,id);ps2ModelPartInitialize(p);LEAVE(32);return p;}
static void identity(uint32_t p){uint32_t v[4];EE_ROT_VU_READ(0,v);uint32_t rows[16]={v[3],0,0,0,0,v[3],0,0,v[2],0,v[3],0,v[0],v[1],v[2],v[3]};memcpy(at(p),rows,64);}
uint64_t ps2MaterialBillboardClone(uint64_t source){
 ENTER(32);uint32_t p=ps2PoolAllocate(136);w32(p+128,(uint32_t)dds3BillboardCopy(sx(r32((uint32_t)source+128))));
 uint32_t m=ps2MatCreate();w32(p+132,m);sdfMatSetConstant(at(m),0x3f800000);sdfMatSetAmbient(at(m),0x80808080);sdfMatSetDiffuse(at(m),0x80808080);sdfMatSetSpecular(at(m),0x80808080);
 identity(p+64);identity(p);LEAVE(32);return sx(p);
}
static void applyLocalMatrix(uint32_t first,uint32_t second,unsigned twoParts){
 uint32_t matrix[16];for(unsigned k=0;k<4;k++)EE_ROT_VU_READ(28+k,matrix+k*4);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t address=nocturneModelMemoryParserLocal(matrix,64);
#else
 uint32_t address=(uint32_t)(uintptr_t)matrix;
#endif
 ps2EffectPartSetMatrix(sx(first),sx(address));if(twoParts)ps2EffectPartSetMatrix(sx(second),sx(address));
#if UINTPTR_MAX > UINT32_MAX
 nocturneModelMemoryParserEnd();
#endif
}
static void motion(uint32_t part){ps2ModelChangeMotionSingle(dds3EffectPartGetHandle(sx(part)),0,0);}
void ps2PcpType3InitializePair(uint64_t object,uint64_t index){
 ENTER(112);uint32_t p=(uint32_t)object,i=(uint32_t)index;
 uint32_t f=EE_FPU_SUB_S(randFloat(),0x3f000000);f=EE_FPU_ADD_S(f,f);sdfRotationYFloat(real(EE_FPU_MUL_S(f,r32(0x54c808))));
 uint32_t a=r32(p+28+i*8),b=r32(p+32+i*8);applyLocalMatrix(a,b,1);motion(a);motion(b);w32(p+0x9c+i*4,randWord()%10);LEAVE(112);
}
void ps2PcpType4InitializePair(uint64_t object,uint64_t index){
 ENTER(112);uint32_t p=(uint32_t)object,i=(uint32_t)index;
 uint32_t f=EE_FPU_SUB_S(randFloat(),0x3f000000);f=EE_FPU_ADD_S(f,f);sdfRotationYFloat(real(EE_FPU_MUL_S(f,r32(0x54c80c))));
 uint32_t a=r32(p+56+i*8),b=r32(p+60+i*8);applyLocalMatrix(a,b,1);motion(a);motion(b);
 w32(p+24+i*4,EE_FPU_MUL_S(randFloat(),0x43160000));w32(p+120+i*4,randWord()%10);LEAVE(112);
}
void ps2PcpType5InitializePart(uint64_t object,uint64_t group,uint64_t index){
 ENTER(112);uint32_t p=(uint32_t)object,g=(uint32_t)group,i=(uint32_t)index,slot=(g*3+i)*4,part=r32(p+28+slot);motion(part);
 uint32_t f;if((int64_t)index>=0)f=EE_FPU_CVT_S_W(i);else{f=EE_FPU_CVT_S_W((i>>1)|(i&1));f=EE_FPU_ADD_S(f,f);}
 f=EE_FPU_MUL_S(f,r32(0x54c810));
 if(group==0)sdfRotationYFloat(real(f));else if(group==1)sdfRotationYFloat(real(f^0x80000000));else if(group==2)sdfRotationZFloat(real(f^0x80000000));else sdfRotationZFloat(real(f));
 applyLocalMatrix(part,0,0);w32(p+172+slot,((i+1)&1)?0:5);LEAVE(112);
}
void ps2PcpType6Reset(uint64_t object){uint32_t p=(uint32_t)object;w32(p+0x133c,0);w32(p+0x1340,0);w32(p+0x1344,0x80808080);}
uint64_t ps2PcpType3Create(uint64_t data){
 ENTER(80);uint32_t p=ps2PoolAllocate(188);
 for(unsigned i=0;i<8;i++){
  if(i==0){w32(p+28,(uint32_t)ps2PcpDescriptorCreatePart(data,0));w32(p+32,(uint32_t)ps2PcpDescriptorCreatePart(data,2));}
  else if(i==1){w32(p+36,(uint32_t)ps2PcpDescriptorCreatePart(data,1));w32(p+40,(uint32_t)copyPart(sx(r32(p+32))));}
  else{w32(p+28+i*8,(uint32_t)copyPart(sx(r32(p+28+(i&1)*8))));w32(p+32+i*8,(uint32_t)copyPart(sx(r32(p+32+(i&1)*8))));}
  ps2PcpType3InitializePair(sx(p),i);
 }
 w32(p+92,(uint32_t)ps2PcpDescriptorCreatePart(data,3));w32(p+124,0);
 for(unsigned i=0;i<7;i++){w32(p+96+i*4,(uint32_t)copyPart(sx(r32(p+92))));w32(p+128+i*4,0);}
 w32(p,0);w32(p+4,0);w32(p+8,0);w32(p+16,0x80808080);w32(p+20,0);w32(p+24,0x3f800000);LEAVE(80);return sx(p);
}
uint64_t ps2PcpType4Create(uint64_t data){
 ENTER(48);uint32_t p=ps2PoolAllocate(152);
 for(unsigned i=0;i<8;i++){
  w32(p+56+i*8,(uint32_t)(i?copyPart(sx(r32(p+56))):ps2PcpDescriptorCreatePart(data,0)));
  w32(p+60+i*8,(uint32_t)(i?copyPart(sx(r32(p+60))):ps2PcpDescriptorCreatePart(data,1)));
  ps2PcpType4InitializePair(sx(p),i);
 }
 w32(p,0);w32(p+4,0);w32(p+8,0);w32(p+16,0x80808080);w32(p+20,0x3f800000);LEAVE(48);return sx(p);
}
uint64_t ps2PcpType5Create(uint64_t data){
 ENTER(96);uint32_t p=ps2PoolAllocate(220);w32(p+24,(uint32_t)ps2PcpDescriptorCreatePart(data,0));motion(r32(p+24));
 for(unsigned g=0;g<4;g++)for(unsigned i=0;i<3;i++){
  w32(p+28+(g*3+i)*4,(uint32_t)(i?copyPart(sx(r32(p+28+g*12))):ps2PcpDescriptorCreatePart(data,g+1)));
  ps2PcpType5InitializePart(sx(p),g,i);
 }
 w32(p,0);w32(p+4,0);w32(p+8,0);w32(p+16,0x80808080);w32(p+20,0x3f800000);LEAVE(96);return sx(p);
}
uint64_t ps2PcpType6Create(uint64_t data){
 ENTER(32);uint32_t h=ps2MemoryHandleAllocate(0x1354),p=ps2MemoryHandleAcquirePointer(h);w32(p+0x1350,h);
 w32(p+0x134c,(uint32_t)ps2PcpDescriptorCreatePart(data,0));w32(p+0x1348,(uint32_t)ps2PcpDescriptorCreatePart(data,1));ps2PcpType6Reset(sx(p));
 w32(p+0xaf0,0);w32(p+0xaf4,0);w32(p+0xaf8,0);w32(p+0x1334,0x80808080);w32(p+0x1338,0x3f800000);LEAVE(32);return sx(p);
}
