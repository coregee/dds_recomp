#include <stdint.h>
#include <string.h>
#include "ee_fpu.h"
#include "motion_callback_leaves.h"
#include "motion_key_search.h"

/* 002B4120. Raw PS2 address slots and instruction-ordered memory accesses.
 * Complete original search, output stores and raw EE interpolation values. */
static uint32_t load32(const uint8_t *p) { uint32_t v; memcpy(&v,p,4); return v; }
static uint32_t load16(const uint8_t *p) { uint16_t v; memcpy(&v,p,2); return v; }
static void store32(uint8_t *p,uint32_t v) { memcpy(p,&v,4); }
static const uint8_t *resolve_original(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveMotionAddress(address);
#else
    return (const uint8_t *)(uintptr_t)address;
#endif
}
void sdfMotGetKey(const void *node_pointer,uint32_t frame_bits,void *output)
{
    const uint8_t *node=node_pointer;
    uint8_t *out=output;
    uint32_t frame_word=EE_FPU_CVT_W_S(frame_bits);
    int32_t frame; memcpy(&frame,&frame_word,4);
    uint32_t cut=load32(node+8),count=load16(resolve_original(cut+4));
    uint32_t times=cut+8,stride=load16(resolve_original(cut+6));
    int32_t low=0,high=(int32_t)count-1,selected;
    do {
        selected=(low+high+1)/2; /* range is 0..65535, even for count zero */
        uint32_t time=load16(resolve_original(times+(uint32_t)selected*2));
        if(frame<(int32_t)time) { --selected; high=selected; }
        else low=selected;
    } while(low<high);
    uint32_t data=times+((count+1)&~UINT32_C(1))*2;
    uint32_t previous=data+(uint32_t)selected*stride;
    uint32_t start=load16(resolve_original(times+(uint32_t)selected*2));
    store32(out,previous);
    uint32_t end;
    if((uint32_t)(selected+1)==count) {
        /* Out may overwrite the controller slot; LW occurs after first SW. */
        uint32_t controller=load32(node+4);
        if(*resolve_original(controller+0x32)!=0) {
            store32(out+4,data);
            end=load16(resolve_original(controller+0x2e));
        } else { store32(out+4,previous); end=start; }
    } else {
        store32(out+4,previous+stride);
        /* The next time may alias either preceding output store. */
        end=load16(resolve_original(times+(uint32_t)(selected+1)*2));
    }
    uint32_t delta=end-start;
    if(delta==0) { store32(out+4,previous); store32(out+8,0); }
    else {
        uint32_t left=EE_FPU_SUB_S(frame_bits,EE_FPU_CVT_S_W(start));
        store32(out+8,EE_FPU_DIV_S(left,EE_FPU_CVT_S_W(delta)));
    }
}
