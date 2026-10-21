#include <stdint.h>
#include <string.h>
#include "material_fiveword_pool.h"
#include "draw_request_ring.h"

/* Host relocation includes the request ring and explicit MMIO reads. */
extern void *nocturneResolveDrawRequestAddress(uint32_t address);
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveDrawRequestAddress(a),4);return v;}
static uint8_t r8(uint32_t a){uint8_t v;memcpy(&v,nocturneResolveDrawRequestAddress(a),1);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolveDrawRequestAddress(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(nocturneResolveDrawRequestAddress(a),&v,2);}
static void w8(uint32_t a,uint8_t v){memcpy(nocturneResolveDrawRequestAddress(a),&v,1);}
/* 002a8570: original counter LW; callers use its low word. */
uint32_t ps2ReadDrawCounterWord(void)
{return *(volatile uint32_t *)nocturneResolveDrawRequestAddress(UINT32_C(0x10000000));}
/* 002a8580: SUBU wraps as a word, then ANDI retains the low16 bits. */
uint32_t ps2ReadDrawCounterDelta(uint32_t start)
{return (ps2ReadDrawCounterWord()-start)&UINT32_C(0xffff);}
/* 002ada68: sole direct caller discards V0. Full64 null tests retained. */
void ps2DrawPublishRequest(uint64_t tag_chain,uint64_t pre_draw_links)
{
    uint32_t start=ps2ReadDrawCounterWord();
    while(*(volatile uint8_t *)nocturneResolveDrawRequestAddress(UINT32_C(0x55188b))){ }
    w16(UINT32_C(0x55188c),(uint16_t)ps2ReadDrawCounterDelta(start));
    uint32_t enabled=ps2KernelDisableInterrupts();
    uint32_t index=r32(UINT32_C(0x551890))+1;
    if(index==3)index=0;
    uint32_t slot=UINT32_C(0x5293f8)+(index<<4);
    w32(slot,0);w32(slot+4,0);w8(slot+8,0);
    if(tag_chain && r32((uint32_t)tag_chain+8)){
        w32(slot,(uint32_t)tag_chain);
        if(pre_draw_links){
            uint32_t first=r32(r32((uint32_t)pre_draw_links)+4);
            w32(slot+4,first);
            if(first){uint32_t last=r32((uint32_t)pre_draw_links+4);uint32_t tail=r32(last+8);w32(tail,0);}
        }
        w8(slot+9,r8(UINT32_C(0x551842)));
    }
    uint32_t serial=r32(UINT32_C(0x551898))+1;
    w32(UINT32_C(0x551890),index);
    w8(UINT32_C(0x5520b5),1);
    w32(UINT32_C(0x551898),serial);
    if(enabled)(void)ps2KernelEnableInterrupts();
}
