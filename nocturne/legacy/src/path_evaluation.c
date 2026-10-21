/* Complete original path evaluation/progression and scalar spline bodies. */
#include "path_evaluation.h"
#include "script_construction.h"
#include "ps2_memory.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint16_t half(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t sub(uint32_t a,uint32_t b){return EE_FPU_SUB_S(a,b);}
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
static uint32_t divide(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static int order(uint32_t a,uint32_t b){uint32_t am=(a&0x7f800000u)?a&0x7fffffffu:0,bm=(b&0x7f800000u)?b&0x7fffffffu:0;int64_t av=a>>31?-(int64_t)am:am,bv=b>>31?-(int64_t)bm:bm;return av<bv?-1:av>bv?1:0;}
static uint32_t uintFloat(uint32_t v){if(!(v&0x80000000u))return EE_FPU_CVT_S_W(v);uint32_t f=EE_FPU_CVT_S_W((v>>1)|(v&1));return add(f,f);}
static void segmentStore(uint32_t address,uint32_t *local,uint32_t value){if(local)local[0]=value;else put(address,value);}
static void weightStore(uint32_t address,uint32_t *local,uint32_t value){if(local)local[1]=value;else put(address,value);}
/* 00116058: unsigned key conversion, original store/reload order and final fallback.
 * Local output represents the caller's two private stack words only. */
static void element(uint32_t segment,uint32_t weight,uint32_t resource,uint32_t frame,uint32_t *local)
{
 uint32_t count=word(resource),limit=count-1,times=word(resource+8),index=0;
 if(limit)do{
  if(order(uintFloat(word(times)),frame)<=0&&order(frame,uintFloat(word(times+4)))<0){
   uint32_t inverse=divide(0x3f800000u,uintFloat(word(times+4)-word(times)));
   segmentStore(segment,local,index);uint32_t lower=word(times);
   weightStore(weight,local,inverse);uint32_t cached=local?local[1]:word(weight);
   weightStore(weight,local,mul(cached,sub(frame,uintFloat(lower))));return;
  }
  index++;times+=4;
 }while(sx(index)<sx(limit));
 segmentStore(segment,local,count-2);weightStore(weight,local,0x3f800000u);
}
void dds3PathGetElement(uint64_t segment,uint64_t weight,uint64_t resource,float frame){element((uint32_t)segment,(uint32_t)weight,(uint32_t)resource,bits(frame),0);}
void nocturnePathElementPrivate(uint32_t key[2],uint32_t resource,uint32_t frame){element(0,0,resource,frame,key);}
/* VU instructions: xyz setters add against vf0, retain inactive lanes, and
 * broadcasts multiply in original source/scale order. vf10/vf11 are live. */
static void setxyz(uint32_t address){uint32_t v[4];EE_PATH_VU_READ(10,v);for(unsigned i=0;i<3;i++)v[i]=add(0,word(address+i*4));EE_PATH_VU_WRITE(10,v);}
static void setalpha(uint32_t address){uint32_t v[4];EE_PATH_VU_READ(10,v);v[3]=mul(0x3f800000u,word(address));EE_PATH_VU_WRITE(10,v);}
static void scale(uint32_t weight){uint32_t v[4];EE_PATH_VU_READ(10,v);for(unsigned i=0;i<4;i++)v[i]=mul(v[i],weight);EE_PATH_VU_WRITE(10,v);}
static void copyVector(void){uint32_t v[4];EE_PATH_VU_READ(10,v);EE_PATH_VU_WRITE(11,v);}
static void addVector(void){uint32_t a[4],b[4];EE_PATH_VU_READ(10,a);EE_PATH_VU_READ(11,b);for(unsigned i=0;i<4;i++)a[i]=add(a[i],b[i]);EE_PATH_VU_WRITE(10,a);}
void dds3PathBasicControlGetPos(uint64_t control)
{
 uint32_t c=(uint32_t)control,v[4];
 if(!(word(c+4)&1)){v[0]=v[1]=v[2]=0;v[3]=0x3f800000u;EE_PATH_VU_WRITE(10,v);return;}
 uint32_t channel=word(c+20),key[2];element(0,0,channel,word(c+12),key);
 uint32_t points=word(channel+4),previous=points+key[0]*12,next=previous+12;
 setxyz(next);scale(key[1]);copyVector();setxyz(previous);scale(sub(0x3f800000u,key[1]));addVector();
 EE_PATH_VU_READ(10,v);v[3]=mul(v[3],0);EE_PATH_VU_WRITE(10,v);
}
void dds3PathBasicControlGetLight(uint64_t control,uint64_t output)
{
 uint32_t c=(uint32_t)control,o=(uint32_t)output;
 if(!(word(c+4)&16)){ps2Memset(at(o),0,40);return;}
 uint32_t channel=word(c+32),key[2];element(0,0,channel,word(c+12),key);
 uint32_t records=word(channel+4),previous=records+key[0]*40,next=previous+40,v[4];
 setxyz(next);setalpha(next+12);scale(key[1]);copyVector();setxyz(previous);setalpha(previous+12);scale(sub(0x3f800000u,key[1]));addVector();
 EE_PATH_VU_READ(10,v);put(o,v[0]);put(o+4,v[1]);put(o+8,v[2]);put(o+12,add(0,v[3]));
 for(unsigned group=0;group<2;group++){
  uint32_t offset=group?28:16;
  setxyz(next+offset);scale(key[1]);copyVector();setxyz(previous+offset);scale(sub(0x3f800000u,key[1]));addVector();
  EE_PATH_VU_READ(10,v);put(o+offset,v[0]);put(o+offset+4,v[1]);put(o+offset+8,v[2]);
 }
}
float dds3PathBasicControlGetFovy(uint64_t control)
{
 uint32_t c=(uint32_t)control;if(!(word(c+4)&4))return real(0);
 uint32_t channel=word(c+28),key[2];element(0,0,channel,word(c+12),key);
 uint32_t p=word(channel+4)+key[0]*4,inverse=sub(0x3f800000u,key[1]),next=word(p+4),previous=word(p);
 return real(add(mul(previous,inverse),mul(next,key[1])));
}
uint64_t dds3PathBasicControlNextStep(uint64_t control)
{
 uint32_t c=(uint32_t)control,flags=word(c+4);if(flags&8)return 1;
 uint32_t mode=word(c),progress=word(c+12);
 if(mode==0){if(order(progress,word(c+8))<0){put(c+12,add(progress,0x3f800000u));return 1;}if(flags&32){put(c+12,0);return 1;}return 0;}
 if(mode==1){if(order(0,progress)<0){put(c+12,sub(progress,0x3f800000u));return 1;}if(flags&32){put(c+12,word(c+8));return 1;}return 0;}
 return 1;
}
void dds3PathBasicControlAlterMode(uint64_t control,uint64_t mode){put((uint32_t)control,(uint32_t)mode);}
void dds3PathBasicControlSetRatio(uint64_t control,float ratio){uint32_t c=(uint32_t)control;put(c+12,mul(bits(ratio),word(c+8)));}
void dds3PathBasicPause(uint64_t control){uint32_t c=(uint32_t)control;put(c+4,word(c+4)|8);}
void dds3PathBasicPauseOff(uint64_t control){uint32_t c=(uint32_t)control;put(c+4,word(c+4)&~8u);}
void dds3PathBasicLoopOn(uint64_t control){uint32_t c=(uint32_t)control;put(c+4,word(c+4)|32);}
void dds3PathBasicLoopOff(uint64_t control){uint32_t c=(uint32_t)control;put(c+4,word(c+4)&~32u);}
/* 001B0A60: per-axis loads occur after preceding stores. Cubic W is stored
 * after the third terms load and before Z; the linear branch leaves W alone. */
void ps2SplineEvaluate(uint64_t output,uint64_t spline,uint64_t segment,float weight)
{
 uint32_t o=(uint32_t)output,s=(uint32_t)spline,offset=(uint32_t)segment*12,w=bits(weight);
 if(!half(s+12)){
  uint32_t a=word(s+20)+offset,b=word(s+24)+offset,c=word(s+28)+offset,p=word(s+16)+offset;
  for(unsigned axis=0;axis<3;axis++){
   uint32_t av=word(a+axis*4),bv=word(b+axis*4),cv=word(c+axis*4),pv=word(p+axis*4);
   if(axis==2)put(o+12,0x3f800000u);
   put(o+axis*4,add(mul(add(mul(add(mul(av,w),bv),w),cv),w),pv));
  }
 }else{
  uint32_t p=word(s+16)+offset;
  for(unsigned axis=0;axis<3;axis++){uint32_t previous=word(p+axis*4),next=word(p+axis*4+12);put(o+axis*4,add(previous,mul(sub(next,previous),w)));}
 }
}
uint64_t ps2SplineAdvance(uint64_t output,uint64_t spline)
{
 uint32_t s=(uint32_t)spline,index=word(s+32),weight=word(s+36);
 ps2SplineEvaluate(output,spline,sx(index),real(weight));weight=add(weight,word(s+40));
 if(order(0x3f800000u,weight)<0){weight=sub(weight,0x3f800000u);index++;}
 uint64_t running=sx(index)<sx(word(s+8)-1);if(!running){index=0;weight=0;}
 put(s+36,weight);put(s+32,index);return running;
}
