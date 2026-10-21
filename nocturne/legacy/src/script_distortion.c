/* Original command slots239..242 and their complete native setter closure.
 * Configuration semantics only: allocation, frame updates and drawing are separate. */
#include "script_distortion.h"
#include "script_core.h"
#include "script_movie.h"
#include <string.h>

static void *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveScriptDistortionAddress(address);
#else
    return (void *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address)
{ uint32_t value; memcpy(&value,at(address),4); return value; }
static void w32(uint32_t address,uint32_t value)
{ memcpy(at(address),&value,4); }
static void w16(uint32_t address,uint16_t value)
{ memcpy(at(address),&value,2); }
static uint32_t bits(float value)
{ uint32_t result; memcpy(&result,&value,4); return result; }
static float real(uint32_t value)
{ float result; memcpy(&result,&value,4); return result; }

/* Four integer registers and independent F12/F13/F14, not decompiler order. */
void ps2DistBlurSetPara_00105E78(uint64_t count,uint64_t width,uint64_t interval,
    uint64_t mode,float speed,float rotation,float distortion)
{
    if((count^UINT64_C(0x8000000000000000)) >=
       (UINT64_C(101)^UINT64_C(0x8000000000000000))) {
        count=100;
        w32(0x54e97c,r32(0x54e97c)+1u);
    }
    w32(0x557360,(uint32_t)mode);
    w32(0x557350,(uint32_t)count);
    w32(0x557378,(uint32_t)width);
    w32(0x557354,(uint32_t)interval);
    w32(0x557358,bits(speed));
    w32(0x557364,bits(rotation));
    w32(0x557368,bits(distortion));
}
void ps2DistBlurSetRgba_00105EC0(uint64_t colour)
{ w32(0x55735c,(uint32_t)colour); }
void ps2DistBlurSetArea_00105ED0(uint64_t area,uint64_t x,uint64_t y)
{
    w32(0x557370,(uint32_t)y);
    w32(0x557374,(uint32_t)area);
    w32(0x55736c,(uint32_t)x);
}
void ps2DistBlurFlagSet_001AD370(void)
{ *(uint8_t *)at(0x54f27a)=1; }
void ps2DistBlurFlagClear_001AD380(void)
{ *(uint8_t *)at(0x54f27a)=0; }
void ps2DistBlurCopyConfig_001AD388(uint64_t raw)
{
    uint32_t source=(uint32_t)raw,destination=r32(0x551de8);
    uint8_t first[32],last[12];
    /* LDL/LDR fetch32 before the first store; trailing12 are fetched later.
     * Preserve this ordering for exact self and partial source/destination alias. */
    memcpy(first,at(source),32);
    memcpy(at(destination),first,32);
    memcpy(last,at(source+32),12);
    memcpy(at(destination+32),last,12);
}
void ps2DistBlurOn_00105FC8(uint64_t frames)
{
    uint8_t alpha=*((uint8_t *)at(0x55735f));
    w16(0x551c20,0);
    w16(0x551c1c,0);
    w16(0x551c22,alpha);
    w16(0x551c1e,(uint16_t)frames);
    if(frames==0) {
        w32(0x54e95c,r32(0x54e95c)&0xffffdfffu);
        ps2DistBlurCopyConfig_001AD388(0x557350);
        ps2DistBlurFlagSet_001AD370();
    } else {
        w32(0x54e95c,r32(0x54e95c)|0x2000u);
        ps2DistBlurCopyConfig_001AD388(0x557350);
        ps2DistBlurFlagClear_001AD380();
    }
}
uint64_t scrCommand_DIST_BLUR_PARA(void)
{
    uint64_t mode=scrGetIntPara(6);
    uint64_t encoded=mode==1?0x48u:mode==2?0x42u:0x44u;
    uint64_t count=scrGetIntPara(0),width=scrGetIntPara(1),interval=scrGetIntPara(2);
    uint32_t speed=scrGetFloatParaBits(3),rotation=scrGetFloatParaBits(4),distortion=scrGetFloatParaBits(5);
    ps2DistBlurSetPara_00105E78(count,width,interval,encoded,real(speed),real(rotation),real(distortion));
    return 1;
}
uint64_t scrCommand_DIST_BLUR_RGBA(void)
{
    uint32_t r=(uint32_t)scrGetIntPara(0),a=(uint32_t)scrGetIntPara(3);
    uint32_t b=(uint32_t)scrGetIntPara(2),g=(uint32_t)scrGetIntPara(1);
    ps2DistBlurSetRgba_00105EC0((r&255u)|(a<<24)|((b&255u)<<16)|((g&255u)<<8));
    return 1;
}
uint64_t scrCommand_DIST_BLUR_AREA(void)
{
    uint64_t area=scrGetIntPara(0),x=scrGetIntPara(1),y=scrGetIntPara(2);
    ps2DistBlurSetArea_00105ED0(area,x,y);
    return 1;
}
uint64_t scrCommand_DIST_BLUR_ON(void)
{ ps2DistBlurOn_00105FC8(scrGetIntPara(0)); return 1; }
