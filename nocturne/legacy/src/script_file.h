#ifndef NOCTURNE_SCRIPT_FILE_H
#define NOCTURNE_SCRIPT_FILE_H
#include <stdint.h>
uint64_t ps2BlockingFileCompletion(uint64_t job,uint64_t event,uint64_t buffer,uint64_t result,uint64_t payload);
uint64_t ps2BlockingFileOpen(uint64_t path);
uint64_t ps2BlockingFileClose(uint64_t job);
uint64_t ps2BlockingFileRead(uint64_t job,uint64_t buffer,uint64_t bytes);
uint64_t ps2BlockingFileSize(uint64_t job);
uint64_t sdfDevLoadFileEx(uint64_t path,uint64_t data_out,uint64_t size_out,uint64_t margin);
uint64_t sdfDevLoadFile(uint64_t path,uint64_t data_out,uint64_t size_out);
uint64_t scrAddScript3(uint64_t path,uint64_t start);
uint64_t scrStartScript3(uint64_t priority,uint64_t path,uint64_t start);
void *nocturneResolveScriptFileAddress(uint32_t address);
#endif
