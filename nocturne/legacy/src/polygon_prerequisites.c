/* Shared polygon ownership and the original nine vertex-colour callbacks. */
#include "polygon_prerequisites.h"
#include "model_motion_creation.h"
#include "memory_handle_allocation.h"
#include "material_construction_release.h"
#include "material_lists.h"
#include "material_motion_scalars.h"
#include "ps2_memory.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include <string.h>
_Noreturn void nocturne_break(uint32_t code);
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolvePolygonPrerequisiteAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void store(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void shalf(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t udiv(uint32_t n,uint32_t d){return d?n/d:UINT32_MAX;}
static uint32_t unsignedFloat(uint32_t v){if(v>>31){uint32_t f=EE_FPU_CVT_S_W((v>>1)|(v&1));return EE_FPU_ADD_S(f,f);}return EE_FPU_CVT_S_W(v);}
static void scalar(unsigned r,uint32_t x){uint32_t v[4]={x,x>>31?UINT32_MAX:0,0,0};EE_ROT_VU_WRITE(r,v);}
static void unpack(uint32_t c,uint32_t v[4]){for(unsigned k=0;k<4;k++)v[k]=(uint32_t)EE_ROT_VU_MUL(EE_FPU_CVT_S_W((c>>(8*k))&255),0x3c000000);EE_ROT_VU_WRITE(10,v);scalar(2,0x3c000000);}
static void derivative(uint32_t c,uint32_t groups,uint32_t constant,uint32_t out[4]){
 uint32_t a[4],v[4],r3[4],acc[4],of[4];unpack(c&0xff000000,a);EE_ROT_VU_WRITE(11,a);memcpy(v,at(constant),16);EE_ROT_VU_WRITE(10,v);
 uint32_t step=EE_FPU_DIV_S(0x3f800000,unsignedFloat(groups));scalar(2,step);EE_ROT_VU_READ(3,r3);r3[3]=(uint32_t)EE_ROT_VU_SUB(0x3f800000,step);EE_ROT_VU_WRITE(3,r3);
 for(unsigned k=0;k<4;k++){uint64_t p=EE_ROT_VU_MUL(a[k],step);acc[k]=(uint32_t)p;of[k]=(uint32_t)(p>>32);out[k]=(uint32_t)EE_ROT_VU_MAC(acc[k],v[k],r3[3],of[k],0);}EE_ROT_ACC_WRITE(acc,of);EE_ROT_VU_WRITE(10,out);
}
static uint32_t packed(const uint32_t current[4]){uint32_t v[4],c=0;EE_ROT_VU_WRITE(10,current);EE_ROT_VU_WRITE(11,current);scalar(2,0x43000000);for(unsigned k=0;k<4;k++){v[k]=EE_FPU_CVT_W_S((uint32_t)EE_ROT_VU_MUL(current[k],0x43000000));c|=(v[k]&255)<<(8*k);}EE_ROT_VU_WRITE(10,v);return c;}
static void advance(uint32_t current[4],const uint32_t delta[4],unsigned add,unsigned move10){for(unsigned k=0;k<4;k++)current[k]=(uint32_t)(add?EE_ROT_VU_ADD(current[k],delta[k]):EE_ROT_VU_SUB(current[k],delta[k]));EE_ROT_VU_WRITE(11,current);if(move10)EE_ROT_VU_WRITE(10,current);}
uint64_t ps2PolygonStateArrayCreate(uint64_t count){uint32_t bytes=(uint32_t)count<<6,h=ps2MemoryHandleAllocate((int32_t)(bytes+8)),base=ps2MemoryHandleAcquirePointer(h),w=base+bytes;store(w,h);store(w+4,base);if((int64_t)count>0){uint32_t remaining=(uint32_t)count;do{store(base+0x20,0);store(base+0x24,0);base+=64;}while(--remaining);}return sx(w);}
uint64_t ps2PolygonHistoryCreate(uint64_t count,uint64_t width,uint64_t source){uint32_t n=(uint32_t)count,len=(uint16_t)width,stride=len<<4,bytes=(stride+16)*n,h=ps2MemoryHandleAllocate((int32_t)(bytes+16)),base=ps2MemoryHandleAcquirePointer(h),w=base+bytes,records=base+stride*n;shalf(w+2,(uint16_t)len);store(w+8,(uint32_t)source);store(w+12,h);shalf(w,(uint16_t)n);store(w+4,records);if(count!=0){uint32_t i=0;do{store(records,base);shalf(records+4,0);store(records+8,0);records+=16;base+=stride;i++;}while((uint64_t)sx(i)<count);}return sx(w);}
void ps2PolygonColorSetup(uint64_t record,uint64_t time){uint32_t r=(uint32_t)record,a=word(r+4)&0xffffff,b=word(r+8)&0xffffff,c=word(r+12)&0xffffff,alpha=word(r+16)<<24;int32_t in=(int32_t)word(r+20),out=(int32_t)word(r+24);store(r+4,a);store(r+8,b);store(r+12,c);store(r+60,in>0?alpha/(uint32_t)in:alpha);store(r+64,out>0?alpha/(uint32_t)out:alpha);uint32_t kind=word(r),t=(uint32_t)time;store(r+28,t);if(kind==1)return;uint32_t period=kind==2?t:(uint32_t)((int32_t)t>>1);store(r+32,period);uint32_t denominator=EE_FPU_CVT_S_W(period);if(EE_FPU_COMPARE_S(denominator,0,0))denominator=0x3f800000;for(unsigned k=0;k<3;k++){uint32_t diff=EE_FPU_SUB_S(EE_FPU_CVT_S_W((b>>(k*8))&255),EE_FPU_CVT_S_W((a>>(k*8))&255));store(r+36+k*8,EE_FPU_DIV_S(diff,denominator));}if(kind==2)return;for(unsigned k=0;k<3;k++){uint32_t diff=EE_FPU_SUB_S(EE_FPU_CVT_S_W((c>>(k*8))&255),EE_FPU_CVT_S_W((b>>(k*8))&255));store(r+40+k*8,EE_FPU_DIV_S(diff,denominator));}}
uint64_t ps2PolygonSampleLookup(uint64_t width){(void)width;return 0;}
void ps2PolygonVertexReset(uint64_t work,uint64_t index){uint32_t cell=word((uint32_t)work+20)+(uint32_t)index*20;store(cell+16,0x80808080);store(cell+8,0);store(cell+12,0);}
uint64_t ps2PolygonVertexCreate(uint64_t count,uint64_t width,uint64_t step,uint64_t kind){uint64_t w=width;uint32_t n=(uint32_t)count;if(kind==4)w=sx((uint32_t)w*5+5);else if(kind==3)w=sx((uint32_t)w*4+4);else if(kind==2)w=sx((uint32_t)w*6+6);else{w=sx((uint32_t)w<<1);if(step!=0){int32_t a=(int32_t)w,d=(int32_t)step,q,rem;if(!d){q=a<0?1:-1;rem=a;}else if(a==INT32_MIN&&d==-1){q=INT32_MIN;rem=0;}else{q=a/d;rem=a%d;}w=rem?sx((uint32_t)q+2):sx((uint32_t)q);}w=sx(((uint32_t)w&~1u)+2);if(kind==1)w=sx((uint32_t)w+(uint32_t)((int32_t)w>>1));}uint32_t len=(uint32_t)w,product=n*len,bytes=(product+n)*20,h=ps2MemoryHandleAllocate((int32_t)(bytes+44)),base=ps2MemoryHandleAcquirePointer(h),footer=base+bytes;ps2Memset(at(footer),0,44);store(footer+24,base);store(footer+28,base+product*16);store(footer+20,base+product*20);if((int64_t)count>0){uint32_t i=0,offset=0;do{uint32_t cell=word(footer+20)+i*20;store(cell,word(footer+24)+offset*16);store(cell+4,word(footer+28)+offset*4);ps2PolygonVertexReset(sx(footer),sx(i));offset+=len;i++;}while((int64_t)sx(i)<(int64_t)count);}uint32_t mat=ps2MatCreate();store(footer+32,mat);sdfMatSetConstant(at(mat),0x3f800000);shalf(footer,(uint16_t)kind);shalf(footer+2,2);store(footer+4,n);store(footer+8,len);store(footer+12,(uint32_t)step);store(footer+16,h);store(footer+36,0);store(footer+40,0);return sx(footer);}
void ps2PolygonVertexSetMode(uint64_t work,uint64_t mode){shalf((uint32_t)work+2,(uint16_t)mode);}
void ps2PolygonVertexColors(uint64_t work,uint64_t operation,uint64_t first,uint64_t second){uint32_t target=word(0x317600+((uint32_t)half((uint32_t)work)*3+(uint32_t)operation)*4);
#if UINTPTR_MAX > UINT32_MAX
 nocturneCallPolygonColor(target,work,first,second);
#else
 ((void (*)(uint64_t,uint64_t,uint64_t))(uintptr_t)target)(work,first,second);
#endif
}
static void flat(uint32_t work,uint32_t first,uint32_t second,unsigned arity){int32_t n=(int32_t)word(work+4),width=(int32_t)word(work+8),groups=arity==3?width/3:width>>(arity==2?1:2);for(int32_t i=0;i<n;i++){uint32_t p=word(word(work+20)+(uint32_t)i*20+4);for(int32_t j=0;j<groups;j++,p+=arity*4){if(arity==2){store(p,first);store(p+4,second);}else{store(p,second);store(p+4,first);store(p+8,arity==3?second:first);if(arity==4)store(p+12,second);}}}}
void ps2PolygonPairColors(uint64_t w,uint64_t a,uint64_t b){flat((uint32_t)w,(uint32_t)a,(uint32_t)b,2);}
void ps2PolygonTripleColors(uint64_t w,uint64_t a,uint64_t b){flat((uint32_t)w,(uint32_t)a,(uint32_t)b,3);}
void ps2PolygonQuadColors(uint64_t w,uint64_t a,uint64_t b){flat((uint32_t)w,(uint32_t)a,(uint32_t)b,4);}
void ps2PolygonPairFade(uint64_t work,uint64_t first,uint64_t second){(void)second;uint32_t w=(uint32_t)work,n=word(w+4),groups=(uint32_t)((int32_t)word(w+8)>>1),delta[4];derivative((uint32_t)first,groups,0x3175d0,delta);EE_ROT_VU_WRITE(12,delta);for(uint32_t i=0;i<n;i++){uint32_t p=word(word(w+20)+i*20+4),current[4];unpack((uint32_t)first,current);for(uint32_t j=0;j<groups;j++,p+=8){uint32_t c=packed(current);store(p,c);store(p+4,c);advance(current,delta,0,1);}}}
void ps2PolygonPairRiseFall(uint64_t work,uint64_t first,uint64_t second){(void)second;uint32_t w=(uint32_t)work,n=word(w+4),width=word(w+8),groups=width>>2,delta[4];derivative((uint32_t)first,groups,0x3175e0,delta);EE_ROT_VU_WRITE(12,delta);for(uint32_t i=0;i<n;i++){uint32_t p=word(word(w+20)+i*20+4),current[4];unpack((uint32_t)first&0xffffff,current);for(uint32_t j=0;j<groups;j++,p+=8){uint32_t c=packed(current);store(p,c);store(p+4,c);advance(current,delta,1,1);}if((width>>1)&1){store(p,(uint32_t)first);store(p+4,(uint32_t)first);p+=8;}for(uint32_t j=0;j<groups;j++,p+=8){uint32_t c=packed(current);store(p,c);store(p+4,c);advance(current,delta,0,1);}}}
void ps2PolygonTripleFade(uint64_t work,uint64_t first,uint64_t second){uint32_t w=(uint32_t)work,n=word(w+4),groups=(uint32_t)((int32_t)word(w+8)/3),da[4],db[4];derivative((uint32_t)first,groups,0x3175f0,da);derivative((uint32_t)second,groups,0x3175f0,db);for(uint32_t i=0;i<n;i++){uint32_t p=word(word(w+20)+i*20+4),a[4],b[4];unpack((uint32_t)first,a);unpack((uint32_t)second,b);for(uint32_t j=0;j<groups;j++,p+=12){store(p+4,packed(a));EE_ROT_VU_WRITE(12,da);advance(a,da,0,0);uint32_t c=packed(b);store(p+8,c);store(p,c);EE_ROT_VU_WRITE(12,db);advance(b,db,0,0);}}}
static void integerRamp(uint32_t work,uint32_t first,uint32_t second,unsigned arity,unsigned riseFall){int32_t n=(int32_t)word(work+4),width=(int32_t)word(work+8),groups=arity==3?(width/3)>>1:width>>(riseFall?3:2);uint32_t fa=first&0xff000000,sa=second&0xff000000,df=udiv(fa,(uint32_t)groups),ds=udiv(sa,(uint32_t)groups);if(arity==4&&!groups)nocturne_break(7);for(int32_t i=0;i<n;i++){uint32_t p=word(word(work+20)+(uint32_t)i*20+4),a=riseFall?0:fa,b=riseFall?0:sa;for(unsigned pass=0;pass<(riseFall?2u:1u);pass++){if(pass){a=fa;b=sa;}for(int32_t j=0;j<groups;j++,p+=arity*4){if(!riseFall||pass){a-=df;b-=ds;}uint32_t ca=(first&0xffffff)|(a&0xff000000),cb=(second&0xffffff)|(b&0xff000000);store(p+4,ca);store(p,cb);store(p+8,arity==3?cb:ca);if(arity==4)store(p+12,cb);if(riseFall&&!pass){a+=df;b+=ds;}}}}}
void ps2PolygonTripleRiseFall(uint64_t w,uint64_t a,uint64_t b){integerRamp((uint32_t)w,(uint32_t)a,(uint32_t)b,3,1);}
void ps2PolygonQuadFade(uint64_t w,uint64_t a,uint64_t b){integerRamp((uint32_t)w,(uint32_t)a,(uint32_t)b,4,0);}
void ps2PolygonQuadRiseFall(uint64_t w,uint64_t a,uint64_t b){integerRamp((uint32_t)w,(uint32_t)a,(uint32_t)b,4,1);}
