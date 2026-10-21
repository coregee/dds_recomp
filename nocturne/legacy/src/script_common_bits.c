/* Original PS2 common-command slots 7, 8 and 9. */
#include "script_common_bits.h"
#include "script_movie.h"
#include "nocturne.h"

/* 0010b888: the native command has no HD configuration override. */
uint64_t scrCommand_BIT_CHK(void)
{
    scrSetIntReturnValue(evtBitCheck((int32_t)scrGetIntPara(0)));
    return 1;
}

/* 0010b8b8: side effects do not publish an integer return register. */
uint64_t scrCommand_BIT_ON(void)
{
    evtBitOn((int32_t)scrGetIntPara(0));
    return 1;
}

/* 0010b8e0. */
uint64_t scrCommand_BIT_OFF(void)
{
    evtBitOff((int32_t)scrGetIntPara(0));
    return 1;
}
