#include <stdint.h>
#include <string.h>
#include "material_callback_saves.h"
#include "motion_callback_leaves.h"
static uint32_t r32(const void *p){uint32_t word;memcpy(&word,p,4);return word;}
static uint8_t *material(const uint8_t *node){uint32_t address=r32(node+12);
#if UINTPTR_MAX > UINT32_MAX
return (uint8_t *)nocturneResolveMotionAddress(address);
#else
return (uint8_t *)(uintptr_t)address;
#endif
}
/* Every alias below describes PS2 behavior; no Unity method identity is claimed. */
void ps2MotionSaveMaterialFlag14(void *node)
{uint8_t *p=node,*src=material(p);uint16_t flag;memcpy(&flag,src+0x14,2);p[0x10]=(uint8_t)(((flag>>4)^1)&1);}
/* 002B4E60: load the raw word before the return-delay store. */
void ps2MotionSaveMaterialWord14(void *node)
{uint8_t *p=node;uint32_t word=r32(material(p)+0x14);memcpy(p+0x10,&word,4);}
/* 002B4FC0: load the raw word before the return-delay store. */
void ps2MotionSaveMaterialWord10(void *node)
{uint8_t *p=node;uint32_t word=r32(material(p)+0x10);memcpy(p+0x10,&word,4);}
/* 002B5120: load the raw word before the return-delay store. */
void ps2MotionSaveMaterialWord20(void *node)
{uint8_t *p=node;uint32_t word=r32(material(p)+0x20);memcpy(p+0x10,&word,4);}
/* 002B5280: load the raw word before the return-delay store. */
void ps2MotionSaveMaterialWord28(void *node)
{uint8_t *p=node;uint32_t word=r32(material(p)+0x28);memcpy(p+0x10,&word,4);}
/* 002B5388: load the raw word before the return-delay store. */
void ps2MotionSaveMaterialScalar1C(void *node)
{uint8_t *p=node;uint32_t word=r32(material(p)+0x1c);memcpy(p+0x10,&word,4);}
/* 002B57D8: load the raw word before the return-delay store. */
void ps2MotionSaveMaterialWord18(void *node)
{uint8_t *p=node;uint32_t word=r32(material(p)+0x18);memcpy(p+0x10,&word,4);}
void ps2MotionEmptyMaterialCallback58B8(void *node){(void)node;}
void ps2MotionEmptyMaterialCallback5990(void *node){(void)node;}
/* 002B5CA0: both merge-load pairs complete before either merge-store pair. */
void ps2MotionSaveMaterialFirstFourWords(void *node)
{uint8_t *p=node,snapshot[16];memcpy(snapshot,material(p),16);memcpy(p+0x10,snapshot,16);}
