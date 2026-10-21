/* Original CPU stream loops, including the distinct 002B6BC0 branch/store. */
#include "model_render_streams.h"
#include "ee_vu_rotation.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
extern void EE_RENDER_STREAMS_CPU_QUAD(unsigned gpr,const uint32_t words[4]);
#else
#define EE_RENDER_STREAMS_CPU_QUAD(gpr,words) ((void)0)
#endif
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveRenderStreamsAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static void packed(uint32_t a,uint32_t v[4]){memcpy(v,at(a),8);v[2]=word(a+8);v[3]=v[2]&0x80000000u?UINT32_MAX:0;EE_RENDER_STREAMS_CPU_QUAD(2,v);}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void loadFullPacked(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_RENDER_STREAMS_CPU_QUAD(2,v);EE_ROT_VU_WRITE(r,v);}
static void loadPacked(unsigned r,uint32_t a){uint32_t v[4];packed(a,v);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void matrices(uint32_t a){for(unsigned k=0;k<4;k++)load(28+k,a+k*16);}
static void acc(unsigned fs,unsigned ft,unsigned bc,unsigned mask,unsigned add){
 uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=add?EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0):EE_ROT_VU_MUL(a[k],b[bc]);v[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}
 EE_ROT_ACC_WRITE(v,of);
}
static void mac(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],v[4],of[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0);EE_ROT_VU_WRITE(fd,out);
}
static void mul(unsigned fd,unsigned fs,unsigned ft,int bc,unsigned mask){
 uint32_t a[4],b[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[bc<0?k:(unsigned)bc]);EE_ROT_VU_WRITE(fd,out);
}
static void transform(void){acc(28,2,0,15,0);acc(29,2,1,15,1);acc(30,2,2,15,1);mac(4,31,0,3,15);}
void ps2RenderTransformWeightedPointsOddLoop(uint64_t control,uint64_t count,uint64_t matrix,uint64_t positions){
 uint32_t stop=(uint32_t)control,n=(uint32_t)count,src=(uint32_t)positions;matrices((uint32_t)matrix);
 do{loadFullPacked(2,src);src+=16;transform();--n;stop+=96;mul(4,4,2,3,15);store(4,src-96);}while(stop);
 (void)n; /* Original A1 decrement remains distinct from the A0 branch. */
}
void ps2RenderAccumulateWeightedPoints(uint64_t output,uint64_t count,uint64_t matrix,uint64_t positions){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,src=(uint32_t)positions;matrices((uint32_t)matrix);
 do{loadFullPacked(2,src);load(5,p);transform();src+=16;--n;acc(5,0,3,15,0);mac(4,4,2,3,15);p+=96;store(4,p-96);}while(n);
}
void ps2RenderCopyPackedVectors(uint64_t output,uint64_t count,uint64_t vectors){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,src=(uint32_t)vectors,v[4];
 do{packed(src,v);src+=12;--n;memcpy(at(p),v,16);p+=96;}while(n);
}
void ps2RenderCopyPackedVectorPairs(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,pos=(uint32_t)positions,normal=(uint32_t)normals,v[4];
 do{packed(pos,v);pos+=12;memcpy(at(p),v,16);packed(normal,v);normal+=12;memcpy(at(p+16),v,16);--n;p+=96;}while(n);
}
void ps2RenderBlendPackedVectorPairs(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals,float weight){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,pos=(uint32_t)positions,normal=(uint32_t)normals;EE_RENDER_STREAMS_FLOAT_TO_VU(6,8,bits(weight));
 do{loadPacked(2,pos);load(4,p);loadPacked(3,normal);load(5,p+16);acc(4,0,3,14,0);mac(2,2,6,0,14);pos+=12;acc(5,0,3,14,0);mac(3,3,6,0,14);normal+=12;--n;store(2,p);store(3,p+16);p+=96;}while(n);
}
void ps2RenderBlendPackedVectors(uint64_t output,uint64_t count,uint64_t vectors,float weight){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,src=(uint32_t)vectors;EE_RENDER_STREAMS_FLOAT_TO_VU(6,7,bits(weight));
 do{load(4,p);loadPacked(2,src);src+=12;acc(4,0,3,14,0);mac(2,2,6,0,14);p+=96;--n;store(2,p-96);}while(n);
}
void ps2RenderNormalizeNormals(uint64_t output,uint64_t count){
 uint32_t p=(uint32_t)output,n=(uint32_t)count;
 do{
  load(2,p+16);mul(3,2,2,-1,14);
  uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(3,a);EE_ROT_ACC_READ(v,of);uint64_t sum=EE_ROT_VU_ADD(a[0],a[1]);v[0]=(uint32_t)sum;of[0]=(uint32_t)(sum>>32)&1;EE_ROT_ACC_WRITE(v,of);
  mac(4,1,3,2,8);EE_ROT_VU_READ(0,a);EE_ROT_VU_READ(4,b);uint32_t q=EE_ROT_VU_RSQRT(a[3],b[0]);EE_ROT_Q_WRITE(q);
  EE_ROT_VU_READ(2,v);for(unsigned k=0;k<3;k++)v[k]=(uint32_t)EE_ROT_VU_MUL(v[k],q);EE_ROT_VU_WRITE(2,v);--n;p+=96;store(2,p-80);
 }while(n);
}
