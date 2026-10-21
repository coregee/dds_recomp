/* Original SLUS_209.11 resource cloning and typed model ownership helpers. */
#include "model_bootstrap_resources.h"
#include "texture_construction.h"
#include "texture_upload.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "array_lists.h"
#include "emitter_initialization.h"
#include "d3p_loading.h"
#include "effect_recursive_release.h"
#include "particle_release.h"
#include "movie_decoder.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelBootstrapAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint8_t r8(uint32_t a){uint8_t v;memcpy(&v,at(a),1);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int32_t count(uint32_t a){return (int16_t)r16(a+4);}
void ps2TextureRefreshPalette(uint64_t texture){
 uint32_t t=(uint32_t)texture;if(r32(t+20))ps2TexturePaletteTransfer(texture,ps2TexturePaletteAddress(texture),sx(r32(t+48)),0);
}
uint64_t ps2TextureDescriptorClone(uint64_t texture){
 uint32_t s=(uint32_t)texture,p=ps2PoolAllocate(64);uint8_t block[32];
 /* Each original group loads all four doublewords before its stores. */
 memcpy(block,at(s),32);memcpy(at(p),block,32);memcpy(block,at(s+32),32);memcpy(at(p+32),block,32);
 uint32_t source=r32(p+8);if(!source){source=s;w32(p+8,source);}
 w32(p+40,0);w32(p+44,0);w32(p+48,0);w32(p+60,0);ps2TextureRegister(sx(p));
 if(r32(p+20)){
  w32(p+20,(uint32_t)ps2TexturePaletteVramCreate(r8(p+26),r8(p+25),r8(p+24)));
  ps2TexturePaletteStagingAllocate(sx(p));ps2TexturePaletteCopy(sx(p),sx(r32(source+48)));w32(p+56,0x80808080);
 }
 ps2TextureDefaultCacheCreate(sx(p));ps2TextureRefreshPalette(sx(p));return sx(p);
}
uint64_t ps2ModelTextureListClone(uint64_t list){
 if(!list)return 0;uint32_t s=(uint32_t)list;int32_t n=count(s);uint32_t p=ps2ArrayCreate(n,4,4);
 for(int32_t i=0;i<n;i++){uint64_t t=ps2TextureDescriptorClone(sx(r32(r32(s+12)+(uint32_t)i*4)));w32(r32(p+12)+(uint32_t)i*4,(uint32_t)t);}
 w16(p+4,(uint16_t)n);return sx(p);
}
uint64_t ps2ModelFindRegisteredResource(uint64_t major,uint64_t minor){
 uint32_t p=r32(0x32c458+((uint32_t)major<<2));while(p){if((uint64_t)r16(p+10)==minor)break;p=r32(p);}return sx(p);
}
uint64_t ps2ModelIsPending(uint64_t major,uint64_t minor){
 uint32_t p=r32(0x32c478+((uint32_t)major<<2));while(p){if(sx(r32(p+4))==minor)return 1;p=r32(p);}return 0;
}
void ps2ModelMarkPending(uint64_t major,uint64_t minor){
 uint32_t head=0x32c478+((uint32_t)major<<2),p=ps2PoolAllocate(8),next=r32(head);w32(p+4,(uint32_t)minor);w32(p,next);w32(head,p);
}
uint64_t ps2ModelResourceListCreate(uint64_t capacity){return sx(ps2ArrayCreate((int32_t)capacity,16,4));}
void ps2ModelResourceAppendBillboard(uint64_t list,uint64_t source){
 uint32_t l=(uint32_t)list,record=r32(l+12)+(uint32_t)count(l)*16;w32(record+4,0);w32(record,0);
 uint64_t object=dds3BillboardCreate(1,source);uint32_t n=r16(l+4);w32(record+8,(uint32_t)object);w16(l+4,(uint16_t)(n+1));
}
void ps2ModelResourceAppendEffect(uint64_t list,uint64_t source){
 uint32_t l=(uint32_t)list,record=r32(l+12)+(uint32_t)count(l)*16;w32(record,1);w32(record+4,0);
 uint64_t object=dds3EffectLoad(source);uint32_t n=r16(l+4);w32(record+8,(uint32_t)object);w16(l+4,(uint16_t)(n+1));
}
void ps2ModelResourceAppendMovie(uint64_t list,uint64_t first,uint64_t handle,uint64_t callback){
 uint32_t l=(uint32_t)list,p=ps2PoolAllocateZeroed(172),offset=(uint32_t)count(l)*16,used=r16(l+4),record=r32(l+12)+offset;
 w32(p+16,(uint32_t)callback);w32(p,(uint32_t)first);w16(l+4,(uint16_t)(used+1));w32(p+4,(uint32_t)handle);w32(record+8,p);w32(record,3);w32(record+4,0);
}
void ps2ModelMovieResourceRelease(uint64_t object){
 uint32_t p=(uint32_t)object;if(r8(p+9))ps2MovieDecoderDestroy(sx(p+32));ps2MemoryHandleFree(r32(p+4));ps2PoolRelease(p);
}
void ps2ModelResourceListRelease(uint64_t list){
 if(!list)return;uint32_t l=(uint32_t)list;int32_t i=0,n=count(l);
 while(i<n){uint32_t record=r32(l+12)+(uint32_t)i*16,kind=r32(record);i++;
  if(kind==0)dds3BillboardDelete(sx(r32(record+8)));else if(kind==1)dds3EffectDelete(sx(r32(record+8)));else if(kind==3)ps2ModelMovieResourceRelease(sx(r32(record+8)));
  n=count(l);
 }
 ps2ArrayFree(l);
}
