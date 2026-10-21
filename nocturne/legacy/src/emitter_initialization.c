/* Original common emitter initialization and its owned drawing dependencies. */
#include "emitter_initialization.h"
#include "polygon_prerequisites.h"
#include "billboard_copy.h"
#include "model_track_creation.h"
#include "model_cleanup.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "libc_printf.h"
#include "ps2_memory.h"
#include "ee_vu_rotation.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveEmitterInitializationAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void store(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void shalf(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
uint64_t ps2BillAnimationResourceCreate(uint64_t source){
 uint32_t src=(uint32_t)source,bytes=word(src),textures=word(src+bytes),cursor=src+bytes+4;
 uint32_t h=ps2MemoryHandleAllocate((int32_t)(bytes+textures*76+28)),base=ps2MemoryHandleAcquirePointer(h),data=base+28;
 store(base,h);ps2Memcpy(at(data),at(src),word(src));store(base+4,data);store(base+16,textures);store(base+8,base+36);store(base+24,data+word(data)+8);
 if((int32_t)textures>0){uint32_t i=0;do{uint64_t texture=ps2BillboardTextureResourceCreate(sx(src+word(cursor)));cursor+=4;store(word(base+24)+i*4,(uint32_t)texture);i++;}while((int32_t)i<(int32_t)textures);}
 store(base+12,1);store(base+20,1);uint32_t count=word(word(base+4)+4),i=0,offset=0;
 if((int32_t)count>0)do{uint32_t descriptor=word(base+8)+offset,flags=word(descriptor+16);offset+=20;
  if(flags&0x10000000){uint32_t max=word(descriptor+12);store(base+12,max);(void)ps2LibcPrintf(UINT64_C(0x532cb8),sx(i),sx(max));}
  else{uint32_t mode=word(descriptor+8);if(mode&0x40){store(base+12,2);(void)ps2LibcPrintf(UINT64_C(0x532cd8),sx(i),UINT64_C(2));}else if(mode&0x80){store(base+12,2);(void)ps2LibcPrintf(UINT64_C(0x532cf8),sx(i),UINT64_C(2));}}
  i++;}while((int32_t)i<(int32_t)count);
 return sx(base);
}
uint64_t ps2BillAnimationAllocate(uint64_t source){uint32_t resource=source?(uint32_t)ps2BillAnimationResourceCreate(source):0,p=ps2PoolAllocate((int32_t)(word(resource+12)*20+108));store(p+48,resource);store(p+96,p+108);shalf(p+80,1);store(p+72,0);store(p+76,0);shalf(p+60,0);dds3BillboardP2ASetNumber(sx(p),0);return sx(p);}
uint64_t dds3BillboardCreate(uint64_t kind,uint64_t source){uint32_t row=0x317080+(uint32_t)kind*12,target=word(row);uint64_t object;
#if UINTPTR_MAX > UINT32_MAX
 object=nocturneCallBillboardFactory(target,source);
#else
 object=((uint64_t (*)(uint64_t))(uintptr_t)target)(source);
#endif
 dds3BillboardBasicInit(object);uint32_t p=(uint32_t)object;shalf(p+44,(uint16_t)kind);store(p+40,word(row+4));return object;}
uint64_t ps2BillboardCloneCached(uint64_t index){uint32_t i=(uint32_t)index;uint64_t object=dds3BillboardCreate((uint64_t)(int64_t)(int16_t)half(0x316ff4+i*8),0);uint32_t owner=word(0x569848+i*4),resource=word(owner+48),count=word(resource+8);store((uint32_t)object+48,resource);store(resource+8,count+1);return object;}
void dds3BillboardSetScale(uint64_t billboard,float x,float y){uint32_t a,b;memcpy(&a,&x,4);memcpy(&b,&y,4);store((uint32_t)billboard+20,b);store((uint32_t)billboard+16,a);}
void dds3BillboardSetMode(uint64_t billboard,uint64_t mode){uint32_t p=(uint32_t)billboard;uint16_t kind=half(p+44);int32_t m=(int16_t)mode;if(kind==0||kind==3){shalf(p+46,(uint16_t)m);return;}if(kind!=1)return;int32_t n=(int32_t)word(p+92);if(n>0){uint32_t cursor=word(p+96)+12;do{uint32_t frame=word(cursor),flags=word(frame+16)&~6u;cursor+=20;store(frame+16,flags);if(m==2)store(frame+16,flags|2);else if(m==3)store(frame+16,flags|4);}while(--n);}}
void dds3BillboardSetAnimColorAdvMode(uint64_t billboard){uint32_t p=(uint32_t)billboard;if(half(p+44)==1)store(p+84,word(p+84)|0x01000000);}
void ps2EffectPointHistoryReset(uint64_t history,uint64_t index){shalf(word((uint32_t)history+4)+((uint32_t)index<<4)+4,0);}
void ps2HermitianTrackPolyReset(uint64_t record){uint32_t r=(uint32_t)record;store(r+16,2);store(r+4,0x80808080);store(r+12,0);}
void ps2SpecialTrackBundleReset(uint64_t bundle){uint32_t b=(uint32_t)bundle;store(b+40,0);ps2HermitianTrackPolyReset(sx(word(b+48)));}
void Eff_ModelTrackPolyReset(uint64_t work){uint32_t w=(uint32_t)work;if(ps2ModelNeedsSpecialRelease(sx(word(w))))ps2SpecialTrackBundleReset(sx(word(w+56)));else{store(w+52,0);ps2HermitianTrackPolyReset(sx(word(w+56)));}}
void Eff_ModelTrackPolyListReset(uint64_t list,uint64_t index){Eff_ModelTrackPolyReset(sx(word(word((uint32_t)list)+((uint32_t)index<<2))));}
uint64_t Eff_ModelTrackPolyListCreate(uint64_t parameters,uint64_t count){uint32_t h=ps2MemoryHandleAllocate((int32_t)(((uint32_t)count<<2)+12)),owner=ps2MemoryHandleAcquirePointer(h);store(owner+8,h);store(owner,owner+12);store(owner+4,(uint32_t)count);if(count!=0){uint32_t i=0;do{uint64_t child=ps2ModelTrackPolyCreate(parameters);uint32_t p=word(owner)+(i<<2);i++;store(p,(uint32_t)child);}while((uint64_t)sx(i)<count);}return sx(owner);}
void ps2ParticleKindReset(uint64_t kindState,uint64_t index){uint32_t k=(uint32_t)kindState;switch(half(k)){case 1:ps2EffectPointHistoryReset(sx(word(k+8)),index);break;case 2:ps2PolygonVertexReset(sx(word(k+16)),index);break;case 3:ps2PolygonVertexReset(sx(word(k+20)),index);break;case 4:Eff_ModelTrackPolyListReset(sx(word(k+20)),index);break;default:break;}}
void ps2ParticleBasicInitialize(uint64_t work){
 uint32_t w=(uint32_t)work;store(w+160,0x150);store(w+248,(uint32_t)ps2PolygonStateArrayCreate(sx(word(w+32))));
 if(sx(word(w+40))!=UINT64_MAX){uint64_t billboard=ps2BillboardCloneCached(sx(word(w+40)));float x,y;uint32_t xb=word(w+16),yb=word(w+20);memcpy(&x,&xb,4);memcpy(&y,&yb,4);store(w+244,(uint32_t)billboard);dds3BillboardSetScale(billboard,x,y);dds3BillboardSetMode(sx(word(w+244)),(uint64_t)(int64_t)(int16_t)half(w+44));}
 ps2PolygonColorSetup(sx(w+72),sx(word(w+36)));uint16_t kind=half(w+48);
 if(kind==1)store(w+56,(uint32_t)ps2PolygonHistoryCreate(sx(word(w+32)),half(w+52),sx(w+244)));
 else if(kind==2||kind==3){uint64_t step=ps2PolygonSampleLookup(half(w+52)),vertex=ps2PolygonVertexCreate(sx(word(w+32)),half(w+52),step,kind==2?0:1);store(w+(kind==2?64:68),(uint32_t)vertex);uint64_t first=sx(word(w+60)),second=kind==2?first:sx(word(w+64));ps2PolygonVertexColors(vertex,1,first,second);ps2PolygonVertexSetMode(sx(word(w+(kind==2?64:68))),half(w+44));}
 else if(kind==4){uint32_t words[13];nocturneEmitterIncomingFramePrefix(words);words[5]=1;words[6]=half(w+52);words[7]=10;words[8]=half(w+44);words[9]=word(w+60);words[10]=words[9];words[11]=word(w+64);words[12]=words[11];uint64_t list;
#if UINTPTR_MAX > UINT32_MAX
  list=nocturneEmitterTrackListFromFrame(words,sx(word(w+32)));
#else
  list=Eff_ModelTrackPolyListCreate((uintptr_t)words,sx(word(w+32)));
#endif
  store(w+68,(uint32_t)list);
 }
 store(w+252,word(w+164));uint32_t matrix[4][4];for(unsigned k=0;k<4;k++){memcpy(matrix[k],at(w+176+k*16),16);EE_ROT_VU_WRITE(28+k,matrix[k]);}for(unsigned k=0;k<4;k++)memcpy(at(w+256+k*16),matrix[k],16);shalf(w+322,1);store(w+240,0x80808080);
}
