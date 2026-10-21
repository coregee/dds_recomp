#ifndef NOCTURNE_FIELD_SEQUENCE_QUEUE_H
#define NOCTURNE_FIELD_SEQUENCE_QUEUE_H
#include <stdint.h>
uint64_t ps2FieldSequenceGetData_00102800(void);
uint64_t ps2FieldSequenceQueue_00102848(uint64_t sequence,uint64_t data,uint64_t size,uint64_t restore);
void *nocturneResolveFieldSequenceQueueAddress(uint32_t address);
#endif
