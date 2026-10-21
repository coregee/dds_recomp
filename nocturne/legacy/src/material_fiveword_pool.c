#include <stdint.h>
#include <string.h>
#include "ee_fpu.h"
#include "motion_callback_leaves.h"
#include "motion_key_search.h"
#include "material_fiveword_pool.h"
static uint32_t r32(const void *p){uint32_t value;memcpy(&value,p,4);return value;}
static uint32_t r16(const void *p){uint16_t value;memcpy(&value,p,2);return value;}
static void w32(void *p,uint32_t value){memcpy(p,&value,4);}
static void w16(void *p,uint32_t value){uint16_t word=(uint16_t)value;memcpy(p,&word,2);}
static int32_t s16(uint32_t value){return (int32_t)(value&32767)-(int32_t)(value&32768);}
static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMotionAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
/* 002B4330: store each result before reading the next input pair. */
void ps2MotionBlendFiveWords(void *out,const void *previous,const void *next,uint32_t alpha)
{
    uint8_t *dst=out;const uint8_t *a=previous,*b=next;
    uint32_t inverse=EE_FPU_SUB_S(UINT32_C(0x3f800000),alpha);
    for(unsigned i=0;i<5;i++){
        uint32_t left=r32(a+4*i),right=r32(b+4*i);
        left=EE_FPU_MUL_S(left,inverse);right=EE_FPU_MUL_S(right,alpha);
        w32(dst+4*i,EE_FPU_ADD_S(left,right));
    }
}
/* 002B4380: header values load completely before any output store. */
void ps2MotionInterpolateFiveWords(const void *key_pair,void *out)
{
    const uint8_t *p=key_pair;uint32_t alpha=r32(p+8),a=r32(p),b=r32(p+4);
    ps2MotionBlendFiveWords(out,at(a),at(b),alpha);
}
uint32_t ps2KernelDisableInterrupts(void)
{
    uint32_t enabled=(EE_SYSTEM_READ_STATUS()&UINT32_C(0x10000))!=0;
    if(enabled){do{EE_SYSTEM_DI();EE_SYSTEM_SYNC(16);}while(EE_SYSTEM_READ_STATUS()&UINT32_C(0x10000));}
    return enabled;
}
uint32_t ps2KernelEnableInterrupts(void)
{
    uint32_t enabled=(EE_SYSTEM_READ_STATUS()&UINT32_C(0x10000))!=0;
    EE_SYSTEM_EI();return enabled;
}
/* 002A89C0: consume the available-page list; always replace the active head. */
void ps2PoolAdvancePageList(void *class_record)
{
    uint8_t *c=class_record;uint32_t next=r32(c+4);
    if(next)w32(c+4,r32(at(next)));
    w32(c,next);
}
uint32_t ps2PoolAllocateFreedSlot(void *class_record,void *page)
{
    uint8_t *c=class_record,*p=page;uint32_t used=r16(p+0x14)+1,slot=r32(p+0x10);
    w16(p+0x14,used);uint32_t next=r32(at(slot)+8);int32_t capacity=s16(r16(c+0xa));w32(p+0x10,next);
    if(s16(used)==capacity)ps2PoolAdvancePageList(c);
    return slot;
}
uint32_t ps2PoolAllocateBumpSlot(void *class_record,void *page)
{
    uint8_t *c=class_record,*p=page;uint32_t used=r16(p+0x14)+1;
    int32_t capacity=s16(r16(c+0xa)),remaining=s16(r16(p+0x16));w16(p+0x14,used);
    int32_t size=s16(r16(c+8));uint32_t data=r32(p+4);
    uint32_t offset=(uint32_t)((int64_t)(capacity-remaining)*size);
    w16(p+0x16,(uint32_t)(remaining-1));
    if(((uint32_t)(remaining-1)&65535)==0){
        w32(p+8,UINT32_C(0x2a89e0));
        if(s16(used)==capacity)ps2PoolAdvancePageList(c);
    }
    return data+offset;
}
uint32_t ps2PoolTakePage(void *class_record)
{
    uint8_t *c=class_record;uint32_t page=r32(at(UINT32_C(0x55205c)));
    uint8_t *p=at(page);uint32_t next=r32(p);w32(at(UINT32_C(0x55205c)),next);
    w16(p+0x14,0);w32(p+8,UINT32_C(0x2a8a30));uint32_t capacity=r16(c+0xa);
    w32(c,page);w16(p+0x16,capacity);
    w32(p+0xc,nocturneOriginalMotionAddress(c));return ps2PoolAllocateBumpSlot(c,p);
}
uint32_t ps2PoolAllocate(int32_t size)
{
    uint32_t bucket=0;
    if(size>=17)bucket=27-(EE_MMI_LEADING_SIGN_WORD((uint32_t)size-1)&255);
    uint8_t *c=at(UINT32_C(0x577ec0)+bucket*12);uint32_t enabled=ps2KernelDisableInterrupts();
    uint32_t page=r32(c),result;
    if(page){uint8_t *p=at(page);uint32_t entry=r32(p+8);result=nocturneCallPoolAllocator(entry,c,p);}
    else result=ps2PoolTakePage(c);
    if(enabled)ps2KernelEnableInterrupts();
    return result;
}
uint32_t ps2MatCreateFiveWords(void)
{
    uint32_t address=ps2PoolAllocate(24);uint8_t *p=at(address);
    w32(p+0x10,0);w32(p+8,UINT32_C(0x3f800000));w32(p+12,UINT32_C(0x3f800000));
    w32(p,0);w32(p+4,0);return address;
}
#define FIVEWORD_MATERIAL(role,offset,mask) \
uint32_t ps2MatGetFiveWords##role(void *material) \
{uint8_t *p=material;uint32_t result=r32(p+offset); \
 if(!result){result=ps2MatCreateFiveWords();w32(p+offset,result);}return result;} \
void ps2MatSetFiveWords##role(void *material,const void *values) \
{uint8_t *p=material;const uint8_t *src=values;uint8_t *dst=at(ps2MatGetFiveWords##role(p)); \
 for(unsigned i=0;i<5;i++){uint32_t word=r32(src+i*4);w32(dst+i*4,word);}p[6]=(uint8_t)(p[6]|mask);} \
void ps2MotionApplyMaterialFiveWords##role(void *node,uint32_t frame) \
{uint32_t key[3],words[5];sdfMotGetKey(node,frame,key);ps2MotionInterpolateFiveWords(key,words); \
 ps2MatSetFiveWords##role(at(r32((const uint8_t *)node+0xc)),words);} \
void ps2MotionBlendMaterialFiveWords##role(void *node,uint32_t frame,uint32_t blend) \
{uint32_t key[3],words[5],result[5];sdfMotGetKey(node,frame,key);ps2MotionInterpolateFiveWords(key,words); \
 ps2MotionBlendFiveWords(result,(const uint8_t *)node+0x10,words,blend); \
 ps2MatSetFiveWords##role(at(r32((const uint8_t *)node+0xc)),result);} \
void ps2MotionSaveMaterialFiveWords##role(void *node) \
{uint8_t *p=node,*src=at(ps2MatGetFiveWords##role(at(r32(p+0xc)))); \
 uint8_t first[8],second[8];uint32_t last;memcpy(first,src,8);memcpy(second,src+8,8);last=r32(src+16); \
 memcpy(p+0x10,first,8);memcpy(p+0x18,second,8);w32(p+0x20,last);}
FIVEWORD_MATERIAL(38,0x38,0x0c)
FIVEWORD_MATERIAL(3C,0x3c,0x30)
#undef FIVEWORD_MATERIAL
