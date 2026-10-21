#include "texture_construction.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "texture_environment.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveTextureAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint64_t v){uint16_t n=(uint16_t)v;memcpy(at(a),&n,2);}
static void w8(uint32_t a,uint64_t v){*at(a)=(uint8_t)v;}
static uint64_t sx(uint32_t v){return v&0x80000000 ? UINT64_C(0xffffffff00000000)|v : v;}
static uint32_t sar(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000)?(~UINT32_C(0)<<(32-n)):0);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
/* First fit: free VRAM records are split from their high end. The original
 * exhaustion callback is followed by an unchecked load through the zero node. */
uint64_t ps2VramAllocate(uint64_t size,uint64_t category)
{
    uint32_t enabled=ps2KernelDisableInterrupts(),node=r32(0x552094);
    for(;;){
        if(!node){
            uint32_t callback=r32(0x55185c);
            if(enabled){ps2KernelEnableInterrupts();callback=r32(0x55185c);}
            if(callback)nocturneVramErrorCallback(callback,size,category);
        }
        if(!r32(node+8) && !less(sx(r32(node+16)),size))break;
        node=r32(node);
    }
    if(sx(r32(node+16))==size){w32(node+8,(uint32_t)category);if(enabled)ps2KernelEnableInterrupts();return sx(node);}
    uint32_t allocated=ps2PoolAllocate(28),previous=r32(node+4);
    w32(allocated+4,previous);
    if(!previous)w32(0x552094,allocated);else w32(r32(node+4),allocated);
    w32(allocated+8,(uint32_t)category);w32(node+4,allocated);
    uint32_t delta=r32(node+16)-(uint32_t)size,address=r32(node+12);
    w32(allocated+16,(uint32_t)size);w32(allocated,node);w32(allocated+12,address+delta);
    w32(node+16,r32(node+16)-(uint32_t)size);
    if(enabled)ps2KernelEnableInterrupts();return sx(allocated);
}
void ps2TextureRegister(uint64_t texture)
{
    uint32_t t=(uint32_t)texture,tail=r32(0x551860);w32(t,0);
    if(tail){w32(t+4,tail);w32(tail,t);}else w32(t+4,0);
    w32(0x551860,t);
}
uint64_t ps2TextureDescriptorCreate(uint64_t width,uint64_t height,uint64_t format,uint64_t mip,uint64_t base,uint64_t paletteFormat,uint64_t paletteEntries,uint64_t palette)
{
    uint32_t t=ps2PoolAllocateZeroed(64);
    w8(t+0x18,paletteEntries);w8(t+0x19,paletteFormat);w16(t+12,width);w16(t+14,height);
    w8(t+0x1a,format);w8(t+0x1b,mip);w32(t+0x14,(uint32_t)palette);w32(t+0x10,(uint32_t)base);
    ps2TextureRegister(sx(t));w32(t+0x38,0x80808080);return sx(t);
}
uint64_t ps2TexturePaletteVramCreate(uint64_t format,uint64_t paletteFormat,uint64_t unused)
{
    (void)unused;uint32_t bits,height,size;
    if(paletteFormat==0)bits=32;else if(paletteFormat==2 || paletteFormat==10)bits=16;else return 0;
    uint64_t index=sx((uint32_t)format-19);if(index>=26)return 0;
    uint32_t f=(uint32_t)format;
    if(f==19 || f==27){size=bits*8;height=32;}
    else if(f==20 || f==36 || f==44){size=64;height=8;}else return 0;
    uint64_t result=ps2VramAllocate(size,3);uint32_t p=(uint32_t)result;
    w32(p+24,(uint32_t)paletteFormat);w16(p+20,8);w16(p+22,height);return result;
}
uint64_t ps2TextureMipCreate(uint64_t width,uint64_t height,uint64_t format,uint64_t mip,uint64_t paletteFormat,uint64_t paletteEntries)
{
    uint32_t bits;uint64_t palette=0;
    if(format>=21)return 0;
    switch(format){case 0:case 1:bits=32;break;case 2:case 10:bits=16;break;
        case 19:bits=8;palette=ps2TexturePaletteVramCreate(format,paletteFormat,paletteEntries);break;
        case 20:bits=4;palette=ps2TexturePaletteVramCreate(format,paletteFormat,paletteEntries);break;default:return 0;}
    uint32_t w=(uint32_t)width,h=(uint32_t)height,total=0,index=0;
    for(;;){uint32_t product=w*h;w=sar(w,1);h=sar(h,1);uint32_t old=index++;product*=bits;total+=sar(product,5);if(sx(old)==mip)break;}
    uint64_t extent=ps2VramAllocate(sx(total),2);uint32_t e=(uint32_t)extent;
    w16(e+20,width);w16(e+22,height);w32(e+24,(uint32_t)format);
    return ps2TextureDescriptorCreate(width,height,format,mip,extent,paletteFormat,paletteEntries,palette);
}
uint64_t ps2TexturePaletteCount(uint64_t texture){return *at((uint32_t)texture+0x18);}
uint64_t ps2TexturePaletteAddress(uint64_t texture){uint32_t p=r32((uint32_t)texture+0x14);return p?sx(r32(p+12)):0;}
uint64_t ps2TextureBaseAddress(uint64_t texture){return sx(r32(r32((uint32_t)texture+0x10)+12));}
uint64_t ps2TextureFormatBits(uint64_t format){return format==2 || format==10 ? 16 : format==19 ? 8 : format==20 ? 4 : 32;}
uint64_t ps2TexturePaletteBytes(uint64_t format,uint64_t paletteFormat,uint64_t count)
{uint32_t entries=(format==19 || format==27)?256:16,stride=paletteFormat?2:4;return sx(entries*stride*(uint32_t)count);}
uint64_t ps2TextureStagingAllocate(uint64_t size)
{
    /* The original pool entry classifies its raw64 request with SLTI <17.
     * Its existing C interface accepts32 bits. Normalize that class0 branch
     * so negative64 requests with positive low words retain their EE class. */
    if(less(size,1025))return sx(ps2PoolAllocate(less(size,17)?1:(int32_t)(uint32_t)size));
    return sx(ps2MemoryHandleAcquirePointer(ps2MemoryHandleAllocate((int32_t)(uint32_t)size)));
}
void ps2TexturePaletteStagingAllocate(uint64_t texture)
{
    uint32_t t=(uint32_t)texture;uint64_t bytes=ps2TexturePaletteBytes(*at(t+0x1a),*at(t+0x19),*at(t+0x18));
    w32(t+0x34,(uint32_t)bytes);w32(t+0x30,(uint32_t)ps2TextureStagingAllocate(bytes));
}
uint64_t ps2TexturePaletteCopy(uint64_t texture,uint64_t source)
{
    uint32_t t=(uint32_t)texture,count=r32(t+0x34),dest=r32(t+0x30);
    ps2Memcpy(at(dest),at((uint32_t)source),count);return sx(dest);
}
uint64_t ps2TextureRegisterCacheCreate(uint64_t texture,uint64_t context)
{
    uint32_t t=(uint32_t)texture,cache=ps2PoolAllocate(64);
    uint64_t base=ps2TextureBaseAddress(texture),palette=ps2TexturePaletteAddress(texture);
    uint32_t filterValue=r16(t+0x1c),width=r16(t+12),height=r16(t+14);
    width=width&32768?width|0xffff0000:width;height=height&32768?height|0xffff0000:height;
    ps2DrawBuildTextureRegisterGroup(cache,width,height,(uint32_t)base,*at(t+0x1a),palette,*at(t+0x19),1,*at(t+0x1b),filterValue,*at(t+0x1f),(uint32_t)context);
    return sx(cache);
}
void ps2TextureDefaultCacheCreate(uint64_t texture){uint64_t cache=ps2TextureRegisterCacheCreate(texture,0);w32((uint32_t)texture+0x28,(uint32_t)cache);}
