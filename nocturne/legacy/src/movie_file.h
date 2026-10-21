#ifndef NOCTURNE_MOVIE_FILE_H
#define NOCTURNE_MOVIE_FILE_H
#include <stdint.h>
uint64_t ps2MovieFileOpen(uint64_t path);
uint64_t ps2MovieFileRead(uint64_t output,uint64_t bytes);
uint64_t ps2MovieFileClose(void);
uint64_t ps2MovieFileSize(void);
#endif
