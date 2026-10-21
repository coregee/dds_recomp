#ifndef NOCTURNE_SCRIPT_MOVIE_H
#define NOCTURNE_SCRIPT_MOVIE_H
#include <stdint.h>
uint64_t scrGetIntPara(uint64_t index);
void scrSetIntReturnValue(uint64_t value);
uint64_t mviScrCmd_MOVIE_PLAY(void);
uint64_t mviScrCmd_MOVIE_STOP(void);
uint64_t mviScrCmd_MOVIE_CHK(void);
uint64_t mviScrCmd_MOVIE_CHKDRAW(void);
void *nocturneResolveScriptVmAddress(uint32_t address);
#endif
