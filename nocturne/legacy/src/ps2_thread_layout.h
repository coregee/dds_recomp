#ifndef NOCTURNE_PS2_THREAD_LAYOUT_H
#define NOCTURNE_PS2_THREAD_LAYOUT_H
#include <stddef.h>
#include <stdint.h>
/* Guest EE addresses are32-bit words, never host pointers.
 * Nocturne2C0FF8 writes entry/stack/size/GP/initial_priority before syscall32;
 * it does not initialize every member below. Preserve untouched guest bytes.
 * PS2SDK ee_thread_t corroborates the public layout, not BIOS implementation.
 * Native2A80A8 separately clears48 bytes around its36-byte descriptor. */
typedef struct NocturneEEThreadParameters32 {
    int32_t status;
    uint32_t entry,stack;
    int32_t stack_size;
    uint32_t gp;
    int32_t initial_priority,current_priority;
    uint32_t attr,option;
} NocturneEEThreadParameters32;
_Static_assert(sizeof(NocturneEEThreadParameters32)==36,"EE thread parameters36");
_Static_assert(offsetof(NocturneEEThreadParameters32,entry)==4,"EE entry+4");
_Static_assert(offsetof(NocturneEEThreadParameters32,stack)==8,"EE stack+8");
_Static_assert(offsetof(NocturneEEThreadParameters32,stack_size)==12,"EE stack size+12");
_Static_assert(offsetof(NocturneEEThreadParameters32,gp)==16,"EE GP+16");
_Static_assert(offsetof(NocturneEEThreadParameters32,initial_priority)==20,"EE priority+20");
_Static_assert(offsetof(NocturneEEThreadParameters32,option)==32,"EE option+32");
#endif
