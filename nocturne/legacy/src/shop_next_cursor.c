/* Eight complete native inline-cursor owners, SLUS_209.11, 896 bytes.
 * These routines own initialized cursor/effect RAM, not scheduler/UI replies. */
#include "shop_next_cursor.h"
#include "ps2_memory.h"
#include <string.h>

static void *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveShopNextCursorAddress(address);
#else
    return (void *)(uintptr_t)address;
#endif
}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sb(uint32_t v){return (v&0x80u)?(v&255u)|0xffffff00u:v&255u;}
static uint32_t sh(uint32_t v){return (v&0x8000u)?(v&65535u)|0xffff0000u:v&65535u;}
static uint64_t sx(uint32_t v){return (v&0x80000000u)?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}

void ps2ShopCursorEffectsInitialize_002416D0(uint64_t cursor)
{
    uint32_t row=(uint32_t)cursor+0x3c;
    for(uint32_t i=0;i<256;i++,row+=16){
        for(uint32_t j=0;j<2;j++){
            uint32_t p=row+j*8;
            w8(p+1,0);w8(p,0);w32(p+4,256);
        }
    }
}

void ps2ShopCursorEffectSet_00241728(uint64_t target,uint64_t type,uint64_t speed,uint64_t effect)
{
    uint32_t p=(uint32_t)effect+sb((uint32_t)target)*8u;
    if(sb(r8(p))!=3){w8(p+1,(uint32_t)speed);w8(p,(uint32_t)type);w32(p+4,0);}
}

uint64_t ps2ShopCursorEffectTimer_00241768(uint64_t target,uint64_t effect)
{
    return sx(r32((uint32_t)effect+sb((uint32_t)target)*8u+4));
}

uint64_t ps2ShopCursorEffectType_00241780(uint64_t target,uint64_t effect)
{
    return sx(sb(r8((uint32_t)effect+sb((uint32_t)target)*8u)));
}

void ps2ShopCursorEffectsUpdate_00241798(uint64_t cursor)
{
    uint32_t row=(uint32_t)cursor+0x3c;
    for(uint32_t i=0;i<256;i++,row+=16){
        for(uint32_t j=0;j<2;j++){
            uint32_t p=row+j*8;
            if(sb(r8(p))!=0){
                uint32_t timer=r32(p+4);
                if(si(timer)<256)w32(p+4,timer+r8(p+1));else w8(p,0);
                if(si(r32(p+4))>=256)w32(p+4,256);
            }
        }
    }
}

uint64_t ps2ShopCursorGeometryInitialize_00241820(uint64_t cursor,uint64_t x,uint64_t y,
    uint64_t width,uint64_t height,uint64_t stepY)
{
    uint32_t c=(uint32_t)cursor;
    (void)ps2Memset(at(c+8),0,0x18);
    w32(c+0x18,(uint32_t)x);w32(c+0x1c,(uint32_t)y);
    w32(c+8,(uint32_t)x);w32(c,(uint32_t)stepY);
    w32(c+0xc,(uint32_t)y);w32(c+0x10,(uint32_t)width);w32(c+0x14,(uint32_t)height);
    return sx(c+8);
}

void ps2ShopCursorInitialize_002418B8(uint64_t cursor,uint64_t count,uint64_t shiftMax,uint64_t strings)
{
    uint32_t c=(uint32_t)cursor,n=(uint8_t)count,maximum=(uint8_t)shiftMax;
    (void)ps2Memset(at(c+0x20),0,0x101c);
    w8(c+0x20,n);w32(c+0x28,(uint32_t)strings);
    w8(c+0x26,n<maximum?n:maximum);w16(c+0x22,0);
    w8(c+0x24,0);w8(c+0x25,0);w32(c+0x2c,0);
    w32(c+0x30,0);w32(c+0x34,0);w8(c+0x38,0);w8(c+4,0);
    ps2ShopCursorEffectsInitialize_002416D0(cursor);
}

void ps2ShopCursorListCountChange_00242118(uint64_t count,uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor,n=(uint8_t)count,old=r8(c+0x20),limit;
    if(old==n)return;
    if(old==0){ps2ShopCursorInitialize_002418B8(cursor,n,n,0);return;}
    limit=r8(c+0x26);
    if(n<limit){limit=n;w8(c+0x26,n);}
    else if(n!=0&&n<old&&si(n-sh(r16(c+0x22)))<si(limit)){
        w16(c+0x22,r16(c+0x22)-(r8(c+0x20)-n));
    }
    /* The native empty-list path stores FF here. HD's added zero guard
     * must not replace the actual unsigned-byte subtraction. */
    if(r8(c+0x24)>=limit)w8(c+0x24,limit-1u);
    uint32_t secondary=limit-sb(r8(c+0x21))-1u;
    if(si(secondary)<si(r8(c+0x25)))w8(c+0x25,secondary);
    if(r32(c+0xc)!=0){
        uint32_t y=(limit-1u)*r32(c),origin=r32(c+0x1c);
        if(si(y)<si(r32(c+0xc)-origin))w32(c+0xc,y+origin);
    }
    w8(c+0x20,n);
    ps2ShopCursorEffectsInitialize_002416D0(cursor);
}
