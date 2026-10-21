#include "sound_bank_flow.h"
#include "sound_bank_support.h"
#include "script_construction.h"
#include "libc_stream.h"
#include "movie_draw.h"
#include "disc_platform.h"
#include "ps2_memory.h"
#include <string.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 002c1ca0: only status2 waits. A missing bank queues its signed bank number
 * in the native filename and leaves completion to the asynchronous service. */
void ps2SoundEnsureBank(uint64_t sound)
{
 uint8_t frame[0x130];uint32_t guest;
#if UINTPTR_MAX > UINT32_MAX
 guest=nocturneLibcStreamLocalAddress(frame,sizeof(frame));
#else
 guest=(uint32_t)(uintptr_t)frame;
#endif
 uint64_t status=ps2SoundBankStatus(sound);
 if(!status){
  uint32_t bank=(uint32_t)((int32_t)(uint32_t)sound>>16);
  (void)ps2LibcSprintf(guest,0x549aa8,sx(bank));
  (void)ps2SoundBuildPath(guest+0x10,guest);
  uint32_t bytes=ps2Strlen(at(guest+0x10))+1;
  (void)ps2MovieCommandSubmit(0xa0,0,guest+0x10,sx(bytes));put(0x5519c0,bank);
 }else if(status==2){
  do{(void)ps2FileDelay(2);uint32_t entry=word(0x5519d8);if(entry)nocturneSoundWaitCallback(entry);status=ps2SoundBankStatus(sound);}while(status!=1);
 }
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
}
/* 002c18d8: packet+4 is not written by the original. Native source retains
 * that private padding; host comparison supplies its observed stack context. */
uint64_t ps2SoundPlay(uint64_t sound,uint64_t volume,uint64_t pan)
{
 uint8_t packet[12];uint32_t guest;ps2SoundEnsureBank(sound);
 uint32_t id=(uint32_t)sound;uint16_t v=(uint16_t)volume,p=(uint16_t)(pan&255);
 memcpy(packet,&id,4);memcpy(packet+8,&v,2);memcpy(packet+10,&p,2);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t privateWord=nocturneSoundPlayPrivateWord();memcpy(packet+4,&privateWord,4);
 guest=nocturneLibcStreamLocalAddress(packet,sizeof(packet));
#else
 guest=(uint32_t)(uintptr_t)packet;
#endif
 uint64_t result=ps2MovieCommandEnqueue(0x90,0,guest,12);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 return result;
}
