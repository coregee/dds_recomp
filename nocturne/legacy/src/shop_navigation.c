/* Thirteen complete native cursor/navigation owners, SLUS_209.11,1820B.
 * Inline guest layout and integer widths follow the original instructions.
 * No pad sample, UI selection, scheduler or audio result is supplied here. */
#include "shop_navigation.h"
#include "shop_next_cursor.h"
#include "ee_fpu.h"
#include <string.h>

static void *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveShopNavigationAddress(a);
#else
    return (void *)(uintptr_t)a;
#endif
}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sb(uint32_t v){return(v&128u)?(v&255u)|0xffffff00u:v&255u;}
static uint32_t sh(uint32_t v){return(v&32768u)?(v&65535u)|0xffff0000u:v&65535u;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t indexAt(uint32_t c){return sh(r16(c+0x22))+r8(c+0x24);}

void ps2ShopCursorInvisibleMove_00241958(uint64_t cursor,uint64_t direction)
{
    uint32_t c=(uint32_t)cursor,flags=r32(c+0x2c),dir=sb((uint32_t)direction);
    if(flags){
        uint32_t index=indexAt(c),offset=r8(c+0x24),step=si(dir)<0?UINT32_MAX:1;
        if(r8(flags+index)&2u){
            uint32_t n=r8(c+0x20),count=1;
            w8(c+0x24,offset+dir);
            if(n>1){
                do{
                    index+=step;
                    if(!(r8(flags+index)&2u))return;
                    ++count;w8(c+0x24,r8(c+0x24)+dir);
                }while(si(count)<si(n));
            }
        }
    }
}

void ps2ShopCursorPositionSet_00241AF0(uint64_t position,uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor;
    w16(c+0x22,(uint32_t)position);w8(c+4,0);w8(c+0x24,0);w8(c+0x25,0);
}

void ps2ShopCursorReset_00241B10(uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor,x=r32(c+0x18),y=r32(c+0x1c);
    w32(c+8,x);w32(c+0xc,y);
    ps2ShopCursorPositionSet_00241AF0(0,cursor);
    ps2ShopCursorInvisibleMove_00241958(cursor,1);
    ps2ShopCursorEffectsInitialize_002416D0(cursor);
}

uint64_t ps2ShopCursorIndexSelectable_00241B60(uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor,flags=r32(c+0x2c);
    return flags?((r8(flags+indexAt(c))&1u)^1u):1;
}

uint64_t ps2ShopCursorAtTop_00241B90(uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor,index=indexAt(c),flags=r32(c+0x2c),hidden=0;
    if(!flags)return index==0;
    for(uint32_t i=index-1u;si(i)>=0;--i)if(r8(flags+i)&2u)++hidden;
    return si(hidden)>=si(index);
}

uint64_t ps2ShopCursorAtBottom_00241C00(uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor,index=indexAt(c),flags=r32(c+0x2c),n=r8(c+0x20),hidden=0;
    if(!flags)return index==n-1u;
    for(uint32_t i=index+1u;si(i)<si(n);++i)if(r8(flags+i)&2u)++hidden;
    return si(index)>=si(n-hidden-1u);
}

uint64_t ps2ShopCursorMoveEx_00241C90(uint64_t cursor,uint64_t direction,uint64_t margin)
{
    uint32_t c=(uint32_t)cursor,dir=sb((uint32_t)direction),mg=sb((uint32_t)margin);
    if(r8(c+0x20)<2)return 0;
    if(!dir){w8(c+4,0);return 0;}
    if(r8(c+4)){w8(c+4,2);return 0;}
    uint32_t before=indexAt(c),skip;
    do{
        skip=0;
        if(si(dir)<0){
            if(ps2ShopCursorAtTop_00241B90(cursor)){
                uint32_t hidden=r8(c+0x21),limit=r8(c+0x26);
                uint32_t y=r32(c+0xc)+(limit-sb(hidden)-1u)*r32(c);
                w16(c+0x22,r8(c+0x20)-limit);w8(c+0x24,limit-1u);
                w8(c+0x25,limit-hidden-1u);w32(c+0xc,y);
                ps2ShopCursorInvisibleMove_00241958(cursor,UINT64_MAX);
            }else if(si(mg)>=si(r8(c+0x24))&&r16(c+0x22)!=0){
                w16(c+0x22,r16(c+0x22)-1u);
            }else{
                uint32_t flags=r32(c+0x2c);
                w8(c+0x24,r8(c+0x24)-1u);
                if(flags&&(r8(flags+indexAt(c))&2u))skip=1;
                if(!skip){w8(c+0x25,r8(c+0x25)-1u);w32(c+0xc,r32(c+0xc)-r32(c));}
            }
            if(ps2ShopCursorAtTop_00241B90(cursor))w8(c+4,1);
        }else{
            if(ps2ShopCursorAtBottom_00241C00(cursor)){
                uint32_t y=r32(c+0xc)-(r8(c+0x26)-sb(r8(c+0x21))-1u)*r32(c);
                w16(c+0x22,0);w8(c+0x24,0);w8(c+0x25,0);w32(c+0xc,y);
                ps2ShopCursorInvisibleMove_00241958(cursor,1);
            }else if(si(r8(c+0x24))>=si(r8(c+0x26)-mg-1u)&&sh(r16(c+0x22))+r8(c+0x26)!=r8(c+0x20)){
                w16(c+0x22,r16(c+0x22)+1u);
            }else{
                uint32_t flags=r32(c+0x2c);
                w8(c+0x24,r8(c+0x24)+1u);
                if(flags&&(r8(flags+indexAt(c))&2u))skip=1;
                if(!skip){w8(c+0x25,r8(c+0x25)+1u);w32(c+0xc,r32(c+0xc)+r32(c));}
            }
            if(ps2ShopCursorAtBottom_00241C00(cursor))w8(c+4,1);
        }
    }while(skip);
    w32(c+0x30,256);
    if(before!=indexAt(c))w8(c+0x38,si(dir)<0?1:2);
    return 1;
}

void ps2ShopCursorActiveEffectUpdate_00241FA8(uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor,old=r32(c+0x34),next=old+6u;
    w32(c+0x34,next);
    if(si(next)>512)w32(c+0x34,old-506u);
}

uint64_t ps2ShopCursorMove_00241FD0(uint64_t cursor,uint64_t direction)
{
    uint32_t c=(uint32_t)cursor,dir=sb((uint32_t)direction);
    if(!dir)ps2ShopCursorActiveEffectUpdate_00241FA8(cursor);else w32(c+0x34,0);
    return ps2ShopCursorMoveEx_00241C90(cursor,dir,1);
}

uint64_t ps2ShopCursorMoveIgnore_00242028(uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor;
    return r8(c+0x20)<2?1:r8(c+4)?2:0;
}

uint64_t ps2ShopCursorMove2_00242050(uint64_t cursor,uint64_t direction)
{
    uint32_t c=(uint32_t)cursor,dir=sb((uint32_t)direction);
    uint64_t ignore=ps2ShopCursorMoveIgnore_00242028(cursor);
    if(!dir)ps2ShopCursorActiveEffectUpdate_00241FA8(cursor);
    else if(ignore==0||ignore==2)w32(c+0x34,0);
    if(ignore==1){w8(c+4,2);return 0;}
    if(!dir&&ignore==2&&(r8(0x2f5836)||r8(0x2f5837)))return 0;
    return ps2ShopCursorMoveEx_00241C90(cursor,dir,1);
}

void ps2ShopCursorListEnd_00242238(uint64_t cursor)
{
    uint32_t c=(uint32_t)cursor,last=r8(c+0x20)+255u;
    w8(c+0x24,last);w8(c+0x25,last-r8(c+0x21));
}

uint64_t ps2ShopCursorPadMask_00242258(uint64_t cursor,uint64_t pad,uint64_t target)
{
    uint32_t c=(uint32_t)cursor,effect=sb(r8(c+0x38));
    if(si(effect)>=0)w8(c+0x38,0u-effect);
    else{
        uint32_t amount=r32(c+0x30);
        if(si(amount)<0)w32(c+0x30,0);
        else{
            amount=EE_FPU_CVT_W_S(EE_FPU_DIV_S(EE_FPU_CVT_S_W(amount),r32(0x54e474)));
            w32(c+0x30,amount);
            if(si(amount)<0)w32(c+0x30,0);
        }
        if(r32(c+0x30)==0)w8(c+0x38,0);
    }
    return sb(r8(c+4))==2?pad&~target:pad;
}
