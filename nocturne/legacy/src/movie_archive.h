#ifndef NOCTURNE_MOVIE_ARCHIVE_H
#define NOCTURNE_MOVIE_ARCHIVE_H
#include <stdint.h>
uint64_t ps2MovieWaitForDisc(void);
uint64_t ps2MovieStreamSeek(uint64_t sector);
uint64_t ps2MovieStreamRead(uint64_t sectors,uint64_t output);
uint64_t ps2MovieLookupDiscFile(uint64_t path,uint64_t sector,uint64_t direct);
uint64_t ps2MovieLookupArchiveFile(uint64_t path,uint64_t sector,uint64_t direct);
_Noreturn void ps2FatalSpin(uint64_t format,...);
void *nocturneResolveMovieArchiveAddress(uint32_t address);
/* Native CD-path caller writes Open's path/flags but leaves A2 live.
 * Its exact transport must be supplied by the calling-platform adapter. */
uint64_t nocturneMovieArchiveOpenMode(void);
#endif
