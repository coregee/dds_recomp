#ifndef NOCTURNE_OBJECT_ATTACHMENT_H
#define NOCTURNE_OBJECT_ATTACHMENT_H
#include <stdint.h>
/* Complete fixed original bodies. Dispatch1/0 is never a guest result.
 * External owners must execute on live banks/RAM or stop genuinely. */
uint32_t nocturneObjectAttachmentBody(uint32_t entry);
void nocturneObjectAttachmentCall(uint32_t target,uint32_t pc);
void *nocturneResolveObjectAttachmentAddress(uint32_t address);
void nocturneObjectAttachmentCpuRead(unsigned reg,uint32_t words[4]);
void nocturneObjectAttachmentCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneObjectAttachmentVuRead(unsigned reg,uint32_t words[4]);
void nocturneObjectAttachmentVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneObjectAttachmentStackPointer(void);
void nocturneObjectAttachmentSetStackPointer(uint32_t address);
void ps2ObjectBaseAttachModel_00110408(uint64_t a0,uint64_t a1,uint64_t a2);
void ps2ObjectAttachmentGetScale_001DD7A8(uint64_t a0);
uint64_t ps2ModelFindNodeId_002B2688(uint64_t a0,uint64_t a1);
uint64_t ps2ModelGetNodeName_002B2748(uint64_t a0,uint64_t a1);
#endif
