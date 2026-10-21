#ifndef NOCTURNE_SCRIPT_LIFECYCLE_COMMANDS_H
#define NOCTURNE_SCRIPT_LIFECYCLE_COMMANDS_H
#include <stdint.h>
uint64_t scrCommand_SCR_RUN(void);
uint64_t scrCommand_SCR_KILL(void);
uint64_t scrCommand_SCR_WAIT(void);
uint64_t scrCommand_SCR_STAT(void);
uint64_t scrCommand_SCR_TIME(void);
uint64_t ps2ProcessGetRunTime(uint64_t process);
void *nocturneResolveScriptLifecycleCommandAddress(uint32_t address);
#endif
