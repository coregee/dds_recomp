/* Eight complete native buy/sell/quantity/input consumers,SLUS_209.11,2984B.
 * All actual price,script,Hearts,cursor and sound calls remain present.
 * Source reconstruction is separate from finite behavior/interface evidence. */
#include "shop_selection.h"
#include "shop_navigation.h"
#include "shop_transaction.h"
#include "shop_payment_controller.h"
#include "sound_bank_flow.h"
#include "nocturne.h"
#include <string.h>
static void *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveShopSelectionAddress(a);
#else
    return (void *)(uintptr_t)a;
#endif
}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sb(uint32_t v){return(v&128u)?(v&255u)|0xffffff00u:v&255u;}
static uint32_t sh(uint32_t v){return(v&32768u)?(v&65535u)|0xffff0000u:v&65535u;}
static uint64_t sx(uint32_t v){return(v>>31)?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static int less64(uint64_t a,uint64_t b){return(a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint32_t work(void){return r32(0x551f34);}
static uint32_t indexAt(uint32_t c){return sh(r16(c+0x22))+r8(c+0x24);}
static void start(uint32_t procedure)
{
    uint32_t s=work();(void)ps2ShopScriptStart_00213B48(sx(r32(s+0x238c)),procedure,sx(s+0x2390));
}
uint64_t ps2ShopCommonInput_002411B0(uint64_t control)
{
    static const struct{uint32_t bit;uint8_t offset,mask;} checks[]={
        {1,1,128},{2,3,128},{0x10,6,2},{0x20,7,2},{0x40,4,2},{0x80,5,2},
        {4,2,128},{8,0,128},{0x200,10,2},{0x100,8,2},{0x800,11,2},{0x400,9,2},
        {0x1000,12,128},{0x2000,13,128},{0x20000,10,128},{0x10000,8,128},{0x80000,11,128},{0x40000,9,128}};
    for(unsigned i=0;i<sizeof(checks)/sizeof(checks[0]);++i)
        if((control&checks[i].bit)&&(r8(0x2f5830u+checks[i].offset)&checks[i].mask))return checks[i].bit;
    return 0;
}
void ps2ShopInputSoundMode_002413B8(uint64_t type,uint64_t mode)
{
    uint64_t sound;
    if(type&0x8000u){(void)ps2SoundPlay(13,127,63);return;}
    if(type==1)sound=8;
    else if(type==2)sound=10;
    else if(type==0x4000)sound=12;
    else if(type==0x1000||type==0x2000)sound=8;
    else if(type==0x10||type==0x20||type==0x40||type==0x80||type==0x100||type==0x200||type==0x400||type==0x800||
            type==0x10000||type==0x20000||type==0x40000||type==0x80000){
        uint32_t m=sb((uint32_t)mode);
        sound=m==2?1:m==1?6:m==3?21:0;
    }else return;
    (void)ps2SoundPlay(sound,127,63);
}
void ps2ShopInputSound_002413A0(uint64_t type){ps2ShopInputSoundMode_002413B8(type,0);}
void ps2ShopListCursorMove_002135E0(uint64_t list,uint64_t direction)
{
    uint32_t l=(uint32_t)list,c=l+0x15c,dir=sb((uint32_t)direction),previous=indexAt(c);
    if(!dir){(void)ps2ShopCursorMove2_00242050(sx(c),0);return;}
    for(;;){
        if(!ps2ShopCursorMove2_00242050(sx(c),sx(dir)))return;
        uint32_t index=indexAt(c);
        if(index==previous||(r8(l+0x59+index)&1u))return;
    }
}
static void finishList(uint32_t key)
{
    ps2ShopListCursorMove_002135E0(sx(work()+0x1068),0);
    uint64_t actual=ps2ShopCursorPadMask_00242258(sx(work()+0x11c4),key,0x30);
    ps2ShopInputSound_002413A0(actual&65535u);
}
void ps2ShopBuyUpdate_00208A90(void)
{
    uint32_t key=(uint16_t)ps2ShopCommonInput_002411B0(0x33);
    if(!ps2ShopSignalCheck_002143B0(0))return;
    if(key==2){start(8);w8(work()+1,0);w8(work()+4,key);}
    else if(key==1){
        uint64_t item=ps2ShopItemId_002071E0(sx(indexAt(work()+0x11c4)),0);
        uint64_t maximum=ps2ShopChoiceMaximum_002075B8(UINT64_MAX,0,0);
        if(!maximum||(maximum>>63)){
            if(r8(r32(0x54ea20)+(uint32_t)item+0x1928)<99)key=0x8000;
            else{
                uint32_t s=work();w8(s+5,key);
                uint64_t process=ps2ShopScriptStart_00213B48(sx(r32(s+0x238c)),5,sx(s+0x2390));
                s=work();w8(s+1,7);w32(s+8,(uint32_t)process);w8(work()+2,key);
            }
        }else{
            int8_t heart=fclChkItemHearts((uint16_t)item);
            if(heart&&cmbChkGetHearts(heart))key=0x8000;
            else{start(2);w8(work()+1,5);w8(work()+4,1);}
        }
    }else if(key==0x10)ps2ShopListCursorMove_002135E0(sx(work()+0x1068),UINT64_MAX);
    else if(key==0x20)ps2ShopListCursorMove_002135E0(sx(work()+0x1068),1);
    finishList(key);
}
void ps2ShopSellUpdate_00208C70(void)
{
    uint32_t key=(uint16_t)ps2ShopCommonInput_002411B0(0x33);
    uint64_t item=ps2ShopItemId_002071E0(sx(indexAt(work()+0x11c4)),1);
    if(!ps2ShopSignalCheck_002143B0(0))return;
    if(key==2){start(8);w8(work()+1,0);w8(work()+4,key);}
    else if(key==1){
        (void)ps2ShopAffordableQuantity_002074C0(UINT64_MAX,1);
        if(!ps2ShopItemEligible_00242A18(item,1))key=0x8000;
        else{start(4);w8(work()+1,6);w8(work()+4,key);}
    }else if(key==0x10)ps2ShopListCursorMove_002135E0(sx(work()+0x1068),UINT64_MAX);
    else if(key==0x20)ps2ShopListCursorMove_002135E0(sx(work()+0x1068),1);
    finishList(key);
}
static void quantity(uint32_t sale)
{
    uint32_t key=(uint16_t)ps2ShopCommonInput_002411B0(0x333);
    if(!ps2ShopSignalCheck_002143B0(0))return;
    if(key==1){
        (void)ps2ShopFacilityValue_002143C8(0,sx(r32(work()+0x1c)));
        uint32_t cap=0;
        if(sale)cap=si(r32(r32(0x54ea20)+0xa48)+r32(work()+0x1c))>9999999;
        (void)ps2ShopFacilityValue_002143C8(7,cap);start(6);w8(work()+1,8);w8(work()+4,1);
    }else if(key==2){start(sale?3:1);w8(work()+0x24,1);w8(work()+1,sale?2:1);w8(work()+4,2);}
    else{
        uint32_t delta=0;
        if(key==0x10)delta=1;else if(key==0x20)delta=UINT32_MAX;else if(key==0x100)delta=0u-10u;else if(key==0x200)delta=10;
        if(delta)w8(work()+0x24,r8(work()+0x24)+delta);
    }
    uint32_t owner=work();uint64_t maximum=ps2ShopChoiceMaximum_002075B8(UINT64_MAX,sale,0);
    if(less64(maximum,sx(sb(r8(owner+0x24))))){
        key=0;maximum=ps2ShopChoiceMaximum_002075B8(UINT64_MAX,sale,0);w8(work()+0x24,(uint32_t)maximum);
    }
    if(si(sb(r8(work()+0x24)))<=0){key=0;w8(work()+0x24,1);}
    (void)ps2ShopAffordableQuantity_002074C0(UINT64_MAX,sale);
    ps2ShopInputSoundMode_002413B8(key,3);
}
void ps2ShopBuyQuantityUpdate_00208DE8(void){quantity(0);}
void ps2ShopSellQuantityUpdate_00208FC8(void){quantity(1);}
