#include <stdint.h>
#include <string.h>
#include "material_lists.h"
#include "motion_callback_leaves.h"
#include "material_motion_scalars.h"
#include "material_setter_leaves.h"
#include "material_construction_release.h"
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMotionAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t x;memcpy(&x,at(address),4);return x;}
static uint32_t r16(uint32_t address){uint16_t x;memcpy(&x,at(address),2);return x;}
static void w32(uint32_t address,uint32_t x){memcpy(at(address),&x,4);}
static void w16(uint32_t address,uint32_t x){uint16_t y=(uint16_t)x;memcpy(at(address),&y,2);}

uint32_t ps2MatReadDefinition(uint32_t material,uint32_t textures,uint32_t definition)
{
    uint32_t cursor=definition+8;
    w32(material,r32(definition));
    w16(material+4,r16(definition+4));
    uint32_t flags=r16(definition+6);
    if(flags&1){uint32_t x=r32(cursor);cursor+=4;sdfMatSetAmbient(at(material),x);}
    if(flags&2){uint32_t x=r32(cursor);cursor+=4;sdfMatSetDiffuse(at(material),x);}
    if(flags&4){uint32_t index=r16(cursor);cursor+=4;uint32_t array=r32(textures+12);ps2MatSetWord2C(at(material),r32(array+(index<<2)));}
    if(flags&8){
        uint32_t a=r32(cursor),b=r32(cursor+4),c=r32(cursor+8),d=r32(cursor+12),e=r32(cursor+16);
        cursor+=20;ps2MatSetFiveScalars38(at(material),a,b,c,d,e);
    }
    if(flags&16){uint32_t x=r32(cursor);cursor+=4;ps2MatSetWord18(at(material),x);}
    if(flags&32){
        uint32_t x=r32(cursor);cursor+=4;uint32_t array=r32(textures+12);
        ps2MatSetWord30(at(material),r32(array+((x&65535)<<2)));
        ps2MatSetWord34(at(material),x>>16);
    }
    if(flags&64){
        uint32_t a=r32(cursor),b=r32(cursor+4),c=r32(cursor+8),d=r32(cursor+12),e=r32(cursor+16);
        cursor+=20;ps2MatSetFiveScalars3C(at(material),a,b,c,d,e);
    }
    if(flags&128){uint32_t x=r32(cursor);cursor+=4;sdfMatSetSpecular(at(material),x);}
    if(flags&256){uint32_t x=r32(cursor);cursor+=4;ps2MatSetWord28(at(material),x);}
    if(flags&512){uint32_t x=r32(cursor);cursor+=4;sdfMatSetConstant(at(material),x);}
    if(flags&1024){uint32_t a=r32(cursor),b=r32(cursor+4);cursor+=8;ps2MatSetScalars40And44(at(material),a,b);}
    return cursor;
}

void ps2MatRelease(uint32_t material)
{
    if(!material)return;
    uint32_t count=r32(0x5518a0),first=r32(material+8);
    w32(0x5518a0,count-1);
    ps2PoolRelease(first);
    ps2PoolRelease(r32(material+12));
    ps2PoolRelease(r32(material+0x38));
    ps2PoolRelease(r32(material+0x3c));
    ps2PoolRelease(material);
}

uint32_t ps2MatWritePacketHeader(uint32_t commands,uint32_t output,uint32_t index)
{
    at(output)[3]=0x30;
    uint32_t word=r32(commands+(index<<2)+8);
    w32(output+8,0);
    w16(output,10);
    w32(output+4,word&0x0fffffff);
    w32(output+12,0);
    return output+16;
}

void ps2MatCopyScalars40And44(uint32_t material,uint32_t output)
{
    w32(output+0x28,r32(material+0x40));
    w32(output+0x2c,r32(material+0x44));
}

uint32_t ps2MemoryHandleAcquirePointer(uint32_t handle)
{
    uint32_t count=r16(handle+14),pointer=r32(handle+8);
    w16(handle+14,count+1);
    return pointer;
}

uint32_t ps2MemoryHandleReleasePointer(uint32_t handle)
{
    uint32_t count=r16(handle+14);
    if(count)w16(handle+14,count-1);
    return count;
}
