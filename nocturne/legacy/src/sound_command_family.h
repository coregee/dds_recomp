#ifndef NOCTURNE_SOUND_COMMAND_FAMILY_H
#define NOCTURNE_SOUND_COMMAND_FAMILY_H
#include <stdint.h>
uint64_t ps2SoundPlayMidi_002C1670(uint64_t);
uint64_t ps2SoundStopMidi_002C16B8(uint64_t);
uint64_t ps2SoundPlayEffectMidi_002C16E8(uint64_t);
uint64_t ps2SoundStopEffectMidi_002C1730(uint64_t);
uint64_t ps2SoundStopAllMidi_002C1760(void);
uint64_t ps2SoundStopAll_002C17B0(void);
uint64_t ps2SoundSetPosition_002C1AA0(uint64_t,uint64_t,float,float,float);
void ps2SoundSetEnvironment_002C1AF8(float,float,float,float,float,float);
uint64_t ps2SoundLoadBankPath_002C1D78(uint64_t);
uint64_t ps2SoundSetBankSource_002C1DB0(uint64_t,uint64_t);
uint64_t ps2SoundSelectChannel_002C1E70(uint64_t);
void ps2SoundReleaseBank_002C1EA0(uint64_t);
uint64_t ps2SoundFadeIn_002C1FF0(uint64_t);
uint64_t ps2SoundFadeInResident_002C2038(uint64_t);
uint64_t ps2SoundVolumeHalfDown_002C20A0(void);
uint64_t ps2SoundVolumeHalfUp_002C20C8(void);
uint64_t ps2SoundSelectOutput_002C20F0(uint64_t);
uint64_t ps2SoundPlayStreamPath_002C2120(uint64_t,uint64_t);
/* Existing ordinary guest SP and RAM; unwritten packet bytes are not cleared.
 * Queue/cache/kernel values are owned by the existing native dependencies. */
void *nocturneResolveSoundCommandFamilyAddress(uint32_t);
uint32_t nocturneSoundCommandFamilyStack(void);
void nocturneSoundCommandFamilySetStack(uint32_t);
#endif
