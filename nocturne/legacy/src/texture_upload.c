#include "texture_upload.h"
#include "texture_construction.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "heap_queue.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveTextureUploadAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static uint32_t r16(const void *p){uint16_t v;memcpy(&v,p,2);return v;}
static void w32(void *p,uint32_t v){memcpy(p,&v,4);}
static void w16(void *p,uint64_t v){uint16_t n=(uint16_t)v;memcpy(p,&n,2);}
static void w64(uint32_t address,uint64_t v){memcpy(at(address),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000 ? UINT64_C(0xffffffff00000000)|v : v;}
static uint32_t sar(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000)?(~UINT32_C(0)<<(32-n)):0);}
static int64_t signed32(uint32_t v){return (int64_t)v-((v&0x80000000)?INT64_C(0x100000000):0);}
uint64_t ps2TextureImageQwc(uint64_t format,uint64_t width,uint64_t height)
{
    uint32_t f=(uint32_t)format,bits=32;uint64_t index=sx(f-1);
    if(index<58){
        if(f==1 || f==49)bits=24;
        else if(f==2 || f==10 || f==50 || f==58)bits=16;
        else if(f==19 || f==27)bits=8;
        else if(f==20 || f==36 || f==44)bits=4;
    }
    return sx(sar(bits*(uint32_t)width*(uint32_t)height,7));
}
/* 002aa9e0. Shared by the raw-entry adapter and the image's local24-byte view.
 * Loads remain at their original stages, including record/output aliases. */
static uint64_t queue_upload(const uint8_t *record)
{
    uint64_t format=record[9],width=r16(record+20),height=r16(record+22),pitch=r16(record+10)>>6;
    if(!pitch)pitch=1;
    uint64_t remaining=ps2TextureImageQwc(format,width,height);
    uint32_t rounded=(uint32_t)remaining+0x7fef;
    uint32_t chunks=(uint32_t)(signed32(rounded)/0x7ff0);
    uint32_t packet=ps2PoolAllocate((int32_t)(chunks*48+128));
    uint32_t handle=r32(record+4),source=r32(record);
    w32(at(packet+8),handle);w32(at(packet+4),source);w32(at(packet),0);
    at(packet)[12]=record[8];
    uint32_t chain=packet+16,tag=packet+112;
    w64(chain,0x10000005);
    uint32_t destination=r32(record+12),y=r16(record+18),x=r16(record+16);
    uint64_t bitblt=(format<<56)|(pitch<<48)|((uint64_t)(destination>>6)<<32);
    uint64_t position=((uint64_t)y<<48)|((uint64_t)x<<32),dimensions=width|(height<<32);
    source=r32(record)&0x0fffffff;
    w64(chain+32,bitblt);w64(chain+48,position);w64(chain+64,dimensions);
    w64(chain+72,0x52);w64(chain+88,0x53);w64(chain+80,0);
    w64(chain+8,UINT64_C(0x5000000500000000));w64(chain+16,UINT64_C(0x1000000000000004));
    w64(chain+24,14);w64(chain+40,0x50);w64(chain+56,0x51);
    for(;;){
        int last=(remaining^UINT64_C(0x8000000000000000))<(UINT64_C(0x7ff1)^UINT64_C(0x8000000000000000));
        uint64_t count=last?remaining:0x7ff0;
        uint64_t gif=count|((uint64_t)last<<15)|UINT64_C(0x0800000000000000);
        uint64_t dma=(count&65535)|0x30000000|((uint64_t)source<<32);
        uint64_t vif=(count|0x51000000)<<32;
        w64(tag+16,gif);source+=(uint32_t)count<<4;w64(tag+32,dma);
        remaining=sx((uint32_t)remaining-(uint32_t)count);w64(tag+40,vif);
        w64(tag,0x10000001);w64(tag+8,UINT64_C(0x5000000100000000));tag+=48;
        if(last)break;
    }
    ps2KernelWaitSema(r32(at(0x581018)));
    uint32_t tail=r32(at(0x581020));
    if(!tail)w32(at(0x58101c),packet);else w32(at(tail),packet);
    uint32_t previousTag=r32(at(0x581028));w32(at(0x581020),packet);chain&=0x0fffffff;
    if(previousTag){w64(previousTag+8,0);w64(previousTag,((uint64_t)chain<<32)|0x20000000);}
    else w32(at(0x581024),chain);
    w32(at(0x581028),tag);
    return sx(ps2KernelSignalSema(r32(at(0x581018))));
}
uint64_t ps2TextureQueueUpload(uint64_t record){return queue_upload(at((uint32_t)record));}
uint64_t ps2TextureImageTransfer(uint64_t address,uint64_t width,uint64_t height,uint64_t format,uint64_t source,uint64_t referenceMode)
{
    uint32_t bytes=(uint32_t)ps2TextureImageQwc(format,width,height)<<4;uint8_t record[24];
    w32(record+4,nocturneTextureImageScratchWord());
    if(!referenceMode){
        uint32_t data;
        if(signed32(bytes)<1025){data=ps2PoolAllocate((int32_t)bytes);record[8]=2;}
        else{uint32_t handle=ps2MemoryHandleAllocate((int32_t)bytes);w32(record+4,handle);data=ps2MemoryHandleAcquirePointer(handle);record[8]=1;}
        w32(record,data);ps2Memcpy(at(data),bytes?at((uint32_t)source):NULL,bytes);
    }else{w32(record,(uint32_t)source);record[8]=0;}
    record[9]=(uint8_t)format;w32(record+12,(uint32_t)address);w16(record+20,width);w16(record+22,height);
    w16(record+10,width);w16(record+16,0);w16(record+18,0);queue_upload(record);
    return sx((uint32_t)source+bytes);
}
uint64_t ps2TexturePaletteTransfer(uint64_t texture,uint64_t address,uint64_t source,uint64_t referenceMode)
{
    uint8_t *t=at((uint32_t)texture);uint32_t format=t[0x1a],width=8,height=2;
    if(format==19 || format==27){width=16;height=16;}
    return ps2TextureImageTransfer(address,width,height,t[0x19],source,referenceMode);
}
uint64_t ps2TextureTmxCreate(uint64_t header,uint64_t referenceMode)
{
    uint32_t h=(uint32_t)header;uint8_t *p=at(h);
    uint64_t width=sx((r16(p+0x12)&32768)?r16(p+0x12)|0xffff0000:r16(p+0x12));
    uint64_t height=sx((r16(p+0x14)&32768)?r16(p+0x14)|0xffff0000:r16(p+0x14));
    uint64_t texture=ps2TextureMipCreate(width,height,p[0x16],p[0x17],p[0x11],p[0x10]);uint8_t *t=at((uint32_t)texture);
    w16(t+0x1c,r16(p+0x18));t[0x1e]=p[0x1a];t[0x1f]=p[0x1b];w32(t+0x20,r32(p+0x1c));w32(t+0x24,r32(p+0x20));
    uint64_t source=sx(h+(p[1]&0xf0)+64);
    if(ps2TexturePaletteCount(texture)){
        ps2TexturePaletteStagingAllocate(texture);ps2TexturePaletteCopy(texture,source);
        source=ps2TexturePaletteTransfer(texture,ps2TexturePaletteAddress(texture),source,referenceMode);
    }
    uint64_t format=t[0x1a];width=sx((r16(t+12)&32768)?r16(t+12)|0xffff0000:r16(t+12));
    height=sx((r16(t+14)&32768)?r16(t+14)|0xffff0000:r16(t+14));uint32_t mip=t[0x1b];
    uint64_t address=ps2TextureBaseAddress(texture),bits=ps2TextureFormatBits(format);
    do{
        source=ps2TextureImageTransfer(address,width,height,format,source,referenceMode);--mip;
        uint32_t delta=sar((uint32_t)bits*(uint32_t)width*(uint32_t)height,5);
        width=sx(sar((uint32_t)width,1));address=sx((uint32_t)address+delta);height=sx(sar((uint32_t)height,1));
    }while(mip!=0xffffffff);
    ps2TextureDefaultCacheCreate(texture);return texture;
}
uint64_t ps2TextureTmxCopy(uint64_t header){return ps2TextureTmxCreate(header,0);}
uint64_t ps2TextureTmxReference(uint64_t header){return ps2TextureTmxCreate(header,1);}
