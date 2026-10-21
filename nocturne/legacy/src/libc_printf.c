/* 002d4748: stdout context publication and real variadic formatter call.
 * Native FPR12..19 saves precede, and are not read by, the integer va cursor.
 * Compiler/private register-save layout is not a matching-binary claim. */
#include "libc_printf.h"
#include "libc_formatter.h"
#include "libc_stream.h"
#include "heap_queue.h"
#include <stdarg.h>
#include <string.h>
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(nocturneResolveHeapAddress(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2LibcPrintf(uint64_t format,...)
{
    va_list arguments;va_start(arguments,format);
    uint32_t cursor;
#if UINTPTR_MAX > UINT32_MAX
    /* Windows x64 va_list is a contiguous eight-byte argument-slot cursor.
     * This adapter backs consumed words; it does not format or truncate args. */
    cursor=nocturneLibcStreamLocalAddress(arguments,0x10000);
#else
    cursor=(uint32_t)(uintptr_t)arguments;
#endif
    uint32_t context=word(0x52be28),stream=word(context+8);
    put(stream+84,context);
    uint64_t result=ps2LibcVfprintfStream(sx(stream),format,cursor);
#if UINTPTR_MAX > UINT32_MAX
    nocturneLibcStreamEndLocal();
#endif
    va_end(arguments);return result;
}
