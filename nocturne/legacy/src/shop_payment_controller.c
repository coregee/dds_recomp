/* Complete SLUS_209.11 payment/sequence/process/signal bodies, 1216 bytes.
 * Full native calls remain; no scheduler, RPC, UI or callback result is supplied.
 * The finite behavior proof is separate from this source reconstruction. */
#include "shop_payment_controller.h"
#include "shop_transaction.h"
#include "shop_next_cursor.h"
#include "battle_action_sequence.h"
#include "process_shutdown.h"
#include "script_construction.h"
#include "script_movie.h"
#include "sound_bank_flow.h"
#include "nocturne.h"
#include <string.h>

static void *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveShopPaymentAddress(address);
#else
    return (void *)(uintptr_t)address;
#endif
}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sb(uint32_t v){return (v&0x80u)?(v&255u)|0xffffff00u:v&255u;}
static uint32_t sh(uint32_t v){return (v&0x8000u)?(v&65535u)|0xffff0000u:v&65535u;}
static uint64_t sx(uint32_t v){return (v&0x80000000u)?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t work(void){return r32(0x551f34);}

uint64_t ps2ShopProcessStatus_00101858(uint64_t process)
{
    if(!dds3ExistProcess(process))return 0;
    uint32_t state=r32((uint32_t)process+0x1c)&15u;
    return state<4?state:0;
}

void ps2ShopScriptForcedEnd_00213B08(uint64_t process)
{
    if(process&&ps2ShopProcessStatus_00101858(process))
        (void)dds3KillProcess(process,0);
}

void ps2ShopSignalClear_00214398(uint64_t index)
{
    w8(0x551f80u+sb((uint32_t)index),0);
}

uint64_t ps2ShopSignalCheck_002143B0(uint64_t index)
{
    return r8(0x551f80u+sb((uint32_t)index))!=0;
}

uint64_t ps2ShopSignalCommand_00214428(void)
{
    uint64_t index=scrGetIntPara(0);
    w8(0x551f80u+(uint32_t)index,1);
    return 1;
}

uint64_t ps2ShopScriptStart_00213B48(uint64_t data,uint64_t start,uint64_t slot)
{
    if(slot)ps2ShopScriptForcedEnd_00213B08(sx(r32((uint32_t)slot)));
    uint64_t process=scrStartScript2(2000,data,start);
    ps2ShopSignalClear_00214398(0);
    if(slot)w32((uint32_t)slot,(uint32_t)process);
    return process;
}

void ps2ShopSequenceInitialize_002427D8(uint64_t sequence,uint64_t parent)
{
    uint32_t s=(uint32_t)sequence;
    w32(s+0x10,(uint32_t)parent);w8(s,3);w8(s+2,255);w8(s+5,0);w32(s+0xc,0);
}

uint64_t ps2ShopSequenceStatus_002427F8(uint64_t sequence)
{
    uint32_t s=(uint32_t)sequence;
    if(r8(s+5)==0)return 0;
    if(ps2ShopProcessStatus_00101858(sx(r32(s+8)))==3){w8(s+5,0);return 2;}
    if(ps2ShopProcessStatus_00101858(sx(r32(s+8)))==0)w8(s+5,0);
    return 1;
}

uint64_t ps2ShopConfirmPayment_002091E8(uint64_t mode)
{
    if(ps2ShopProcessStatus_00101858(sx(r32(work()+0x2390)))==2)return 0;
    uint64_t signal=ps2ShopSignalCheck_002143B0(2);
    if(signal==1){
        uint32_t s=work();
        (void)ps2ShopScriptStart_00213B48(sx(r32(s+0x238c)),sb((uint32_t)mode)==0?2:4,sx(s+0x2390));
        w8(work()+1,sb((uint32_t)mode)==0?5:6);w8(work()+4,2);
    }else if(signal==0){
        uint32_t s=work(),total=r32(s+0x1c);
        w8(s+1,9);
        /* Original divisor is literal20. The zero-divisor BREAK delay is
         * statically excluded; signed quotient truncates toward zero. */
        uint32_t quotient=(uint32_t)(si(total)/20),again=work();
        w32(s+0x2384,quotient?quotient:1);w8(again+4,255);
    }
    /* The real signal checker returns only0/1; the generic original >1
     * dispatch cannot occur with that callee, but its return is also1. */
    return 1;
}

void ps2ShopPaymentUpdate_002092E8(void)
{
    uint32_t s=work(),sale=sb(r8(s+3))!=5;
    uint16_t item=(uint16_t)ps2ShopItemId_002071E0(sx(sh(r16(s+0x11e6))+r8(s+0x11e8)),sale);
    uint64_t state=ps2ShopSequenceStatus_002427F8(sx(work()));
    if(state==1)return;
    if(state==2){
        s=work();w8(s+0x24,1);
        if(!sale){
            s=work();(void)ps2ShopScriptStart_00213B48(sx(r32(s+0x238c)),1,sx(s+0x2390));
            w8(work()+1,1);
        }else{
            ps2ShopCreateInventoryList_00213C10(sx(work()+0x2242),1);
            s=work();ps2ShopCursorListCountChange_00242118(r8(s+0x2242),sx(s+0x11c4));
            s=work();uint32_t data=r32(s+0x238c),count=r8(s+0x2242);
            (void)ps2ShopScriptStart_00213B48(sx(data),count?3:8,sx(s+0x2390));
            w8(work()+1,count?2:0);
        }
        w8(work()+4,1);return;
    }
    s=work();uint32_t total=r32(s+0x1c);
    if(si(total)>0){
        uint32_t step=r32(s+0x2384);
        if(si(total)<si(step)){
            datAddMaka(si(sale?total:0u-total));
            if(!sale){s=work();w32(s+0x20,r32(s+0x20)+r32(s+0x1c));}
            w32(work()+0x1c,0);
        }else{
            datAddMaka(si(sale?step:0u-step));
            if(!sale){s=work();w32(s+0x20,r32(s+0x20)+r32(s+0x2384));}
            s=work();w32(s+0x1c,r32(s+0x1c)-r32(s+0x2384));
        }
        (void)ps2SoundPlay(5,127,63);return;
    }
    uint32_t quantity=sb(r8(s+0x24));
    (void)fclAddItem(item,si(sale?0u-quantity:quantity));
    w8(work()+5,1);
    s=work();uint64_t process=ps2ShopScriptStart_00213B48(sx(r32(s+0x238c)),7,sx(s+0x2390));
    w32(work()+8,(uint32_t)process);
}
