#include "process_creation.h"
#include "process_lists.h"
#include "material_fiveword_pool.h"
#include "nocturne.h"
#include <string.h>
static uint32_t r32(uint32_t address)
{ uint32_t value;memcpy(&value,nocturneResolveProcessCreationAddress(address),4);return value; }
static uint32_t r8(uint32_t address)
{ return *(uint8_t *)nocturneResolveProcessCreationAddress(address); }
static void w32(uint32_t address,uint32_t value)
{ memcpy(nocturneResolveProcessCreationAddress(address),&value,4); }
static void w8(uint32_t address,uint32_t value)
{ *(uint8_t *)nocturneResolveProcessCreationAddress(address)=(uint8_t)value; }
static void w16(uint32_t address,uint32_t value)
{ uint16_t word=(uint16_t)value;memcpy(nocturneResolveProcessCreationAddress(address),&word,2); }
static uint64_t signword(uint32_t value)
{ return value&UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000)|value : value; }
/* 001015b0: retain the signed-byte hash and the byte24 copy over its low byte. */
uint64_t dds3StartProcess(uint64_t name,uint64_t priority,uint64_t startdelay,
    uint64_t shutdowndelay,uint64_t processfunc,uint64_t shutdownfunc,uint64_t data)
{
    uint32_t p=ps2PoolAllocate(80),input=(uint32_t)name;
    if(!p)return 0;
    w32(p+0x18,0);
    uint32_t byte=r8(input);w8(p,byte);
    if(byte){
        byte=r8(input);
        for(uint32_t index=1;;index++){
            uint32_t signedbyte=(byte&128) ? UINT32_C(0xffffff00)|byte : byte;
            w32(p+0x18,r32(p+0x18)+signedbyte);
            byte=r8(input+index);w8(p+index,byte);
            if(byte==0 || index>=24)break;
        }
    }
    w32(p+0x20,(uint32_t)priority);w32(p+0x1c,1);
    w16(p+0x2c,(uint32_t)startdelay);w16(p+0x2e,(uint32_t)shutdowndelay);
    w32(p+0x30,(uint32_t)processfunc);w32(p+0x34,(uint32_t)shutdownfunc);w32(p+0x38,(uint32_t)data);
    w8(p+0x17,0);w32(p+0x24,0);w32(p+0x28,0);
    w32(p+0x3c,0);w32(p+0x40,0);w32(p+0x44,0);w32(p+0x48,0);w32(p+0x4c,0);
    dds3AddProcessList(signword(p));
    uint16_t delay;memcpy(&delay,nocturneResolveProcessCreationAddress(p+0x2c),2);
    if(delay==0)dds3StartReadyProcess(signword(p));
    return signword(p);
}
/* 001eafb8: even a null constructor result is stored before resetting moon state. */
void evtInitMoonProcess(void)
{
    if(r32(UINT32_C(0x54f76c)))return;
    uint64_t process=dds3StartProcess(UINT32_C(0x54f780),0x2b0b,1,1,
        UINT32_C(0x1eadd8),UINT32_C(0x1eaf08),0);
    w32(UINT32_C(0x54f76c),(uint32_t)process);
    evtEnableMoonCalc();evtDisableMoonDraw();evtSetAgeOfMoon(0);
    g_datGlobalWork->unknown_0a42[0]=0;
    uint32_t value=0;memcpy((uint8_t *)g_datGlobalWork+0x11a7c,&value,4);
}
