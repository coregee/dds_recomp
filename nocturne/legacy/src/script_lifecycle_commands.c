/* Original BF command slots165..169 and their process clock accessor.
 * Unity provides role names; original pointer handles and priority ADDU win. */
#include "script_lifecycle_commands.h"
#include "script_movie.h"
#include "script_core.h"
#include "script_construction.h"
#include "process_shutdown.h"
#include "battle_action_sequence.h"
#include "libc_printf.h"
#include <string.h>

static uint32_t word(uint32_t address)
{
    uint32_t value;
#if UINTPTR_MAX > UINT32_MAX
    memcpy(&value,nocturneResolveScriptLifecycleCommandAddress(address),4);
#else
    memcpy(&value,(void *)(uintptr_t)address,4);
#endif
    return value;
}
static uint64_t sx(uint32_t value)
{ return value&0x80000000u?UINT64_C(0xffffffff00000000)|value:value; }
static int less(uint64_t a,uint64_t b)
{ return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000)); }

/* 0010BD20: invalid index/current-work paths preserve the prior VM result.
 * The ninth start argument is SW S1 at caller SP+0, not a missing argument. */
uint64_t scrCommand_SCR_RUN(void)
{
    uint64_t index=scrGetIntPara(0),work=scrGetScriptHandle();
    if(work){
        uint32_t w=(uint32_t)work;
        if(!word(w+0xe4)) (void)ps2LibcPrintf(0x52f5e8);
        else if(!(index>>63)&&less(index,sx(word(word(w+0xb0)+8)))){
            uint64_t displacement=scrGetIntPara(1);
            uint64_t priority=sx(word(word(w+0xe4)+0x20)+(uint32_t)displacement);
            uint64_t child=scrStartScript1a(priority,sx(word(w+0xac)),sx(word(w+0xb0)),
                sx(word(w+0xb4)),sx(word(w+0xb8)),sx(word(w+0xbc)),
                sx(word(w+0xc0)),sx(word(w+0xc4)),(uint32_t)index);
            scrSetIntReturnValue(child);
        }
    }
    return 1;
}
/* 0010BDE0: request the original one-tick shutdown, after queue membership. */
uint64_t scrCommand_SCR_KILL(void)
{
    uint64_t process=scrGetIntPara(0);
    if(dds3ExistProcess(process)) (void)dds3KillProcess(process,1);
    return 1;
}
/* 0010BE28: zero keeps COMM pending, so its operand stays on the VM stack. */
uint64_t scrCommand_SCR_WAIT(void)
{ return dds3ExistProcess(scrGetIntPara(0))==0; }
/* 0010BE50: command completion and the published membership result differ. */
uint64_t scrCommand_SCR_STAT(void)
{
    scrSetIntReturnValue(dds3ExistProcess(scrGetIntPara(0))!=0);
    return 1;
}
/* 00101AA0: original unchecked signed LW. */
uint64_t ps2ProcessGetRunTime(uint64_t process)
{ return sx(word((uint32_t)process+0x28)); }
/* 0010BE98: membership guards this call site; the clock accessor has no guard. */
uint64_t scrCommand_SCR_TIME(void)
{
    uint64_t process=scrGetIntPara(0);
    scrSetIntReturnValue(dds3ExistProcess(process)?ps2ProcessGetRunTime(process):0);
    return 1;
}
