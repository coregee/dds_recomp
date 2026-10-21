/* Complete original EE sound command, bank and parameter callers.
 * Native queue/service completion remains asynchronous downstream ownership. */
#include "sound_command_family.h"
#include "sound_bank_flow.h"
#include "sound_bank_support.h"
#include "movie_draw.h"
#include "ps2_memory.h"
#include "ee_fpu.h"
#include <string.h>
static void *at(uint32_t a){return nocturneResolveSoundCommandFamilyAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void half(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static uint32_t packet(uint32_t frame){return nocturneSoundCommandFamilyStack()-frame;}
static uint64_t play(uint64_t id,uint32_t command,uint16_t volume,int ensure,int clear4)
{
 uint32_t p=packet(0x20);if(ensure)ps2SoundEnsureBank(id);
 put(p,(uint32_t)id);if(clear4)put(p+4,0);half(p+8,volume);
 return ps2MovieCommandEnqueue(command,0,p,16);
}
uint64_t ps2SoundPlayMidi_002C1670(uint64_t id){return play(id,0x20,0x7f,1,1);}
uint64_t ps2SoundStopMidi_002C16B8(uint64_t id){uint32_t p=packet(0x20);put(p,(uint32_t)id);return ps2MovieCommandEnqueue(0x30,0,p,16);}
uint64_t ps2SoundPlayEffectMidi_002C16E8(uint64_t id){return play(id,0x130,0x7f,1,0);}
uint64_t ps2SoundStopEffectMidi_002C1730(uint64_t id){uint32_t p=packet(0x20);put(p,(uint32_t)id);return ps2MovieCommandEnqueue(0x30,0,p,16);}
uint64_t ps2SoundStopAllMidi_002C1760(void){return ps2MovieCommandEnqueue(0x1a0,0,0,0);}
uint64_t ps2SoundStopAll_002C17B0(void){return ps2MovieCommandEnqueue(0x40,0,0,0);}
uint64_t ps2SoundSetPosition_002C1AA0(uint64_t id,uint64_t channel,float x,float y,float z)
{
 uint32_t p=packet(0x30),scale=word(0x54e7cc);put(p,(uint32_t)id);put(p+4,(uint32_t)channel);
 put(p+0x10,EE_FPU_CVT_W_S(EE_FPU_MUL_S(bits(z),scale)));
 put(p+8,EE_FPU_CVT_W_S(EE_FPU_MUL_S(bits(x),scale)));
 put(p+12,EE_FPU_CVT_W_S(EE_FPU_MUL_S(bits(y),scale)));
 return ps2MovieCommandSubmit(0x170,0,p,32);
}
void ps2SoundSetEnvironment_002C1AF8(float a,float b,float c,float d,float e,float f)
{
 uint32_t p=packet(0x30),scale=word(0x54e7d0),value[6];
 uint32_t input[6]={bits(a),bits(b),bits(c),bits(d),bits(e),bits(f)};
 for(unsigned i=0;i<6;i++){value[i]=EE_FPU_CVT_W_S(EE_FPU_MUL_S(input[i],scale));put(p+8+i*4,value[i]);}
 for(unsigned i=0;i<6;i++)if(word(0x5907f8+i*4)!=value[i]){
  (void)ps2MovieCommandSubmit(0x160,0,p,32);
  (void)ps2Memcpy(at(0x5907f0),at(p),32);return;
 }
}
uint64_t ps2SoundLoadBankPath_002C1D78(uint64_t path){return ps2MovieCommandSubmit(0xa0,0,path,ps2Strlen(at((uint32_t)path)));}
uint64_t ps2SoundSetBankSource_002C1DB0(uint64_t source,uint64_t bytes)
{
 uint32_t p=(uint32_t)source;put(0x593f28,p);put(0x593f24,1);put(0x593f20,(uint32_t)bytes);
 if(source&&(int64_t)bytes>0){put(0x552120,p);(void)ps2MovieCommandSubmit(0x1b0,0,0x552120,4);}
 put(0x5519c0,0xffffffffu);return UINT64_MAX;
}
uint64_t ps2SoundSelectChannel_002C1E70(uint64_t value){return ps2MovieCommandSubmit(((value>>3)&15)|0x150,0,0,0);}
void ps2SoundReleaseBank_002C1EA0(uint64_t sound)
{
 if(!ps2SoundBankStatus(sound))return;
 uint32_t p=packet(0x20);put(p,(uint32_t)sound);(void)ps2MovieCommandSubmit(0xb0,0,p,16);
 uint32_t bank=(uint32_t)((int32_t)(uint32_t)sound>>16);
 if(word(0x5519c0)==bank)put(0x5519c0,0xffffffffu);
}
uint64_t ps2SoundFadeIn_002C1FF0(uint64_t id){return play(id,0x20,0x17f,1,1);}
uint64_t ps2SoundFadeInResident_002C2038(uint64_t id){return play(id,0x20,0x17f,0,1);}
uint64_t ps2SoundVolumeHalfDown_002C20A0(void){return ps2MovieCommandEnqueue(0x180,0,0,0);}
uint64_t ps2SoundVolumeHalfUp_002C20C8(void){return ps2MovieCommandEnqueue(0x190,0,0,0);}
uint64_t ps2SoundSelectOutput_002C20F0(uint64_t value){return ps2MovieCommandEnqueue((((uint32_t)value+1)&15)|0xe0,0,0,0);}
uint64_t ps2SoundPlayStreamPath_002C2120(uint64_t path,uint64_t channel)
{
 if(word(0x5519c8))return 1;
 (void)ps2Strcpy(at(0x529be8),at((uint32_t)path));
 (void)ps2MovieCommandSubmit((((uint32_t)channel&255)>>3)|0xf0,0,0,0);return 0;
}
