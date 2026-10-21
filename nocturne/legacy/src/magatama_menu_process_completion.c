/* Genuine2144A0 five-word external API. No physical completion is supplied.
 * The code is currently outside the9065 recognized inventory;zero admitted
 * identity credit until a separate definition/native proof is reviewed. */
#include "magatama_menu_process.h"
#include <string.h>
uint64_t ps2MagatamaResourceCompletion_002144A0(uint64_t job,uint64_t event,
    uint64_t data,uint64_t bytes,uint64_t payload)
{
    (void)job;(void)bytes;
    if(event==8){
        uint32_t word=(uint32_t)data;
#if UINTPTR_MAX > UINT32_MAX
        memcpy(nocturneResolveMagatamaMenuProcessAddress((uint32_t)payload),&word,4);
#else
        memcpy((void *)(uintptr_t)(uint32_t)payload,&word,4);
#endif
    }
    return 0;
}
