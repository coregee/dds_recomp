#ifndef NOCTURNE_PACKET_BUILDERS_H
#define NOCTURNE_PACKET_BUILDERS_H
#include <stdint.h>
void ps2DrawInitializeInlineRegisterPacket(uint32_t arg0,uint64_t arg1);
void ps2DrawInitializeReferencedRegisterPacket(uint32_t arg0,uint64_t arg1,uint64_t arg2);
void ps2DrawBuildRegisterGroupPacket(uint32_t arg0,uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4,uint64_t arg5,uint64_t arg6,uint64_t arg7,uint32_t arg8);
void ps2DrawBuildOffsetRangePacket(uint32_t arg0,uint32_t arg1,uint32_t arg2);
void ps2DrawBuildFixedStatePacket(uint32_t arg0);
#endif
