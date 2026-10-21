#ifndef NOCTURNE_PAC_BINARY_H
#define NOCTURNE_PAC_BINARY_H
#include <stdint.h>
void ps2PacBinaryPrepare(uint64_t parser,uint64_t header);
void ps2PacBinaryRawStream(uint64_t parser);
void ps2PacBinaryCompressedStream(uint64_t parser);
void ps2PacBinaryReferenceStream(uint64_t parser);
void ps2PacBinaryRecordInitialize(uint64_t parser,uint64_t header);
void ps2PacType6RecordInitialize(uint64_t parser,uint64_t header);
void ps2PacType8RecordInitialize(uint64_t parser,uint64_t header);
void ps2PacType6Complete(uint64_t parser);
void ps2PacType8Complete(uint64_t parser);
void ps2PacRelocatePointers(uint64_t destination,uint64_t base,uint64_t table,uint64_t bytes);
#endif
