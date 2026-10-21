/* Original billboard ownership and animation-record reconstruction.
 * Native load/store order, dirty allocation bytes and signed frame delays
 * remain authoritative; managed reference layouts are not imported. */
#include "billboard_copy.h"
#include "model_motion_creation.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "texture_upload.h"
#include "libc_printf.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelMotionCreationAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t sar(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000u)?(~UINT32_C(0)<<(32-n)):0);}
/* 0015B1B0: 0x400-byte drawing area followed by a 0x4C-byte owner.
 * Width/height retain the native signed twelve-bit and half-size extraction. */
uint64_t ps2BillboardTextureResourceCreate(uint64_t texture){
 uint32_t handle=ps2MemoryHandleAllocate(0x44c),base=ps2MemoryHandleAcquirePointer(handle),p=base+0x400;
 w32(p+8,0);w32(p+0x40,handle);w32(p+0x44,base);w32(base+0x3fc,0);w32(p+0x48,p);w16(p+4,0);
 uint32_t cursor=base+0x438;for(int count=3;count>=0;--count,cursor-=4)w32(cursor,0);
 w16(p+0x3c,0);uint32_t t=(uint32_t)ps2TextureTmxCopy(texture),references=r32(p+8)+1u;
 uint32_t height=(uint32_t)r16(t+14)<<20,width=(uint32_t)r16(t+12)<<20;
 uint32_t halfHeight=EE_FPU_CVT_S_W(sar(height,21)),halfWidth=EE_FPU_CVT_S_W(sar(width,21));
 w32(p+8,references);w16(p+0x14,(uint16_t)sar(width,16));w16(p+0x1a,(uint16_t)sar(height,16));
 halfHeight=EE_FPU_MUL_S(halfHeight,0x3d800000);w32(p,t);halfWidth=EE_FPU_MUL_S(halfWidth,0x3d800000);
 w16(p+12,0);w16(p+14,0);w16(p+16,(uint16_t)sar(width,16));w32(p+0x28,halfHeight);w32(p+0x24,halfWidth);
 w16(p+0x12,0);w16(p+0x16,(uint16_t)sar(height,16));w16(p+0x18,0);w32(p+0x1c,0);w32(p+0x20,0);return sx(p);
}
void dds3BillboardBasicInit(uint64_t billboard){uint32_t p=(uint32_t)billboard;w32(p+0x20,0);w32(p+0x10,0x3f800000);w32(p+0x24,0x80808080);w16(p+0x2e,0);w32(p+12,0);w32(p+8,0);w32(p+4,0);w32(p,0);w32(p+0x18,0x3f800000);w32(p+0x14,0x3f800000);w32(p+0x1c,0);}
/* 0015C230: unlike the reviewed DDS source, a null texture does not clear
 * word30 in the freshly allocated block. */
uint64_t ps2BillboardNormalAllocate(uint64_t texture){uint32_t p=ps2PoolAllocate(0x34);if(texture)w32(p+0x30,(uint32_t)ps2BillboardTextureResourceCreate(texture));return sx(p);}
uint64_t dds3BillboardP2ACopy(uint64_t source){
 uint32_t resource=r32((uint32_t)source+0x30),count=r32(resource+12);w32(resource+0x14,r32(resource+0x14)+1u);
 uint32_t p=ps2PoolAllocate((int32_t)(count*20u+0x6c));w32(p+0x30,resource);w32(p+0x60,p+0x6c);w16(p+0x50,1);w32(p+0x48,0);w32(p+0x4c,0);dds3BillboardP2ASetNumber(sx(p),0);return sx(p);
}
void ps2BillboardP2ABindFrame(uint64_t resource,uint64_t index,uint64_t output){
 uint32_t r=(uint32_t)resource,entry=r32(r+8)+(uint32_t)index*20u,base=r32(r+4),offset=r32(entry),p=(uint32_t)output;
 w32(p+12,entry);base+=offset;w32(p+4,0);uint32_t delay=(uint32_t)(int32_t)(int16_t)r16(base+0x12);w32(p+16,base);w32(p+8,delay);
}
void dds3BillboardP2ASetNumber(uint64_t billboard,uint64_t index){
 uint32_t p=(uint32_t)billboard,i=(uint32_t)index,resource=r32(p+0x30),entry=r32(resource+8)+i*20u;
 if(!r32(entry+12)){w16(p+0x50,0);return;}
 if(r32(entry+16)&0x10000000u){
  (void)ps2LibcPrintf(0x532c70);w32(p+0x54,0x10000000);w32(p+0x58,i);w32(p+0x5c,r32(entry+12));uint32_t records=r32(resource+4)+r32(entry);
  for(uint32_t k=0,offset=0;k<r32(entry+12);k++,offset+=20,records+=24){
   uint32_t output=r32(p+0x60)+offset;ps2BillboardP2ABindFrame(sx(resource),(uint64_t)(int64_t)(int16_t)r16(records),sx(output));output=r32(p+0x60)+offset;w32(output+4,0u-(uint32_t)(int32_t)(int16_t)r16(records+2));
  }
 }else if(r32(entry+8)&0xc0u){
  (void)ps2LibcPrintf(0x532c88);w32(p+0x58,i);w32(p+0x54,r32(entry+8));w32(p+0x5c,2);ps2BillboardP2ABindFrame(sx(resource),sx(i),sx(r32(p+0x60)));ps2BillboardP2ABindFrame(sx(resource),sx(i+1u),sx(r32(p+0x60)+20));
 }else{w32(p+0x54,0);w32(p+0x5c,1);w32(p+0x58,i);ps2BillboardP2ABindFrame(sx(resource),sx(i),sx(r32(p+0x60)));}
 if(r32(entry+8)&0x100u)(void)ps2LibcPrintf(0x532ca0);w16(p+0x50,1);
}
uint64_t dds3BillboardCopy(uint64_t source){
 uint32_t s=(uint32_t)source,p;
 if(r16(s+0x2c)==1){p=(uint32_t)dds3BillboardP2ACopy(source);dds3BillboardBasicInit(sx(p));w16(p+0x2c,r16(s+0x2c));w32(p+0x28,r32(s+0x28));}
 else{p=(uint32_t)ps2BillboardNormalAllocate(0);dds3BillboardBasicInit(sx(p));uint16_t kind=r16(s+0x2c);uint32_t resource=r32(s+0x30),value=r32(s+0x28),references=r32(resource+8)+1u;w16(p+0x2c,kind);w32(p+0x28,value);w32(resource+8,references);w32(p+0x30,resource);}
 return sx(p);
}
uint64_t mdlEffectDupBillboard(uint64_t resource){uint32_t r=(uint32_t)resource;uint64_t p=dds3BillboardCopy(sx(r32(r+8)));w32(r+4,r32(r+4)+1u);return p;}
