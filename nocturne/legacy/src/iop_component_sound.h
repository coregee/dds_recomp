#ifndef NOCTURNE_IOP_COMPONENT_SOUND_H
#define NOCTURNE_IOP_COMPONENT_SOUND_H
#include "iop_hardware_timer.h"
/* Original 32-bit guest addresses; these layouts are module-local contracts. */
typedef struct {uint32_t type,table,unknown08,unknown0c,unknown10;} NocturneIopCslModule;
typedef struct {uint32_t record_word_count,ports,buffer_count,buffers;} NocturneIopCslTable;
typedef struct {uint32_t unknown00,bank,unknown08,work;} NocturneIopCslPort;
typedef struct {uint32_t unknown00,data;} NocturneIopCslBuffer;
typedef struct {uint32_t next,prev;uint8_t unknown08[0x38],core,index,unknown42[0xe6];} NocturneIopCslVoice;
_Static_assert(sizeof(NocturneIopCslModule)==20,"Observed module descriptor");
_Static_assert(sizeof(NocturneIopCslTable)==16,"Original CSL table");
_Static_assert(sizeof(NocturneIopCslPort)==16,"Original port record");
_Static_assert(sizeof(NocturneIopCslBuffer)==8,"Original buffer view");
_Static_assert(sizeof(NocturneIopCslVoice)==0x128,"Original synthesizer voice");
_Static_assert(offsetof(NocturneIopCslVoice,core)==0x40,"Original core byte");
uint32_t nocturneIopComponentSoundResume(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopHardwareTimer *);
uint32_t nocturneIopComponentSoundRoute(NocturneIopMachine *,uint8_t *,uint32_t,uint64_t,NocturneIopHardwareTimer *);
#endif
