#ifndef NOCTURNE_SCRIPT_CORE_H
#define NOCTURNE_SCRIPT_CORE_H
#include <stdint.h>
uint32_t scrGetFloatParaBits(uint64_t index);
uint64_t scrGetStrPara(uint64_t index);
uint64_t scrGetLabelCodeAddress(uint64_t label);
void scrSetCodePointer(uint64_t code);
uint64_t scrGetCommandTimer(void);
uint64_t scrGetMessageHandle(void);
uint64_t scrGetScriptHandle(void);
uint64_t scrGetData(void);
uint64_t ps2ScriptSkipRequested(void);
uint64_t scrCommand_SYNC(void);
uint64_t scrCommand_WAIT(void);
uint64_t scrCommand_SEL_JMP(void);
uint64_t scrPopInt(uint64_t work);
uint64_t scrCodeFunc_Minus(uint64_t work);
uint64_t scrCodeFunc_Comm(uint64_t work);
uint64_t scrCodeFunc_End(uint64_t work);
uint64_t scrCodeFunc_Goto(uint64_t work);
uint64_t ps2ScriptTrace(uint64_t work);
void *nocturneResolveScriptCoreAddress(uint32_t address);
uint64_t nocturneInvokeScriptFunction(uint32_t entry,uint64_t work,unsigned command);
#endif
