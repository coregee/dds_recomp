#ifndef NOCTURNE_LIBC_FORMATTER_H
#define NOCTURNE_LIBC_FORMATTER_H
#include <stdint.h>
uint64_t ps2LibcVfprintf(uint64_t context,uint64_t stream,uint64_t format,uint64_t arguments);
uint64_t ps2LibcVfprintfStream(uint64_t stream,uint64_t format,uint64_t arguments);
uint64_t ps2LibcVfprintfUnbuffered(uint64_t stream,uint64_t format,uint64_t arguments);
#endif
