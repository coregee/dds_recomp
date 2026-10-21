#ifndef NOCTURNE_MATERIAL_FIVEWORD_POOL_H
#define NOCTURNE_MATERIAL_FIVEWORD_POOL_H
#include <stdint.h>
/* Partial ordinary-RAM interfaces. Float values retain their raw EE words.
 * Address results remain original raw32 slots in the host verification ABI. */
void ps2MotionBlendFiveWords(void *out,const void *previous,const void *next,uint32_t alpha);
void ps2MotionInterpolateFiveWords(const void *key_pair,void *out);
uint32_t ps2MatCreateFiveWords(void);
uint32_t ps2MatGetFiveWords38(void *material);
uint32_t ps2MatGetFiveWords3C(void *material);
void ps2MatSetFiveWords38(void *material,const void *values);
void ps2MatSetFiveWords3C(void *material,const void *values);
void ps2MotionApplyMaterialFiveWords38(void *node,uint32_t frame);
void ps2MotionBlendMaterialFiveWords38(void *node,uint32_t frame,uint32_t blend);
void ps2MotionSaveMaterialFiveWords38(void *node);
void ps2MotionApplyMaterialFiveWords3C(void *node,uint32_t frame);
void ps2MotionBlendMaterialFiveWords3C(void *node,uint32_t frame,uint32_t blend);
void ps2MotionSaveMaterialFiveWords3C(void *node);
void ps2PoolAdvancePageList(void *class_record);
uint32_t ps2PoolAllocateFreedSlot(void *class_record,void *page);
uint32_t ps2PoolAllocateBumpSlot(void *class_record,void *page);
uint32_t ps2PoolTakePage(void *class_record);
uint32_t ps2PoolAllocate(int32_t size);
uint32_t ps2KernelDisableInterrupts(void);
uint32_t ps2KernelEnableInterrupts(void);
/* Processor primitives and host relocation bindings, not recovered functions. */
uint32_t EE_SYSTEM_READ_STATUS(void);
void EE_SYSTEM_DI(void);
void EE_SYSTEM_EI(void);
void EE_SYSTEM_SYNC(uint32_t type);
uint32_t EE_MMI_LEADING_SIGN_WORD(uint32_t value);
uint32_t nocturneOriginalMotionAddress(const void *host);
uint32_t nocturneCallPoolAllocator(uint32_t entry,void *class_record,void *page);
#endif
