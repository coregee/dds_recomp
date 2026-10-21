/* Real canonical bank and guest-RAM owners; no observation/operand storage. */
#include "../src/battle_panel_color_native.h"
#include "../src/fusion_core_transport.h"
#include <stdlib.h>
#include <string.h>

void *nocturneEffectHostAddress(uint32_t address);
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);
void nocturneEffectHostCpuWrite(unsigned reg,const uint32_t words[4]);
uint32_t *nocturneEffectHostFpr(void);
#if defined(NOCTURNE_PANEL_COLOR_PROBE)
__declspec(dllimport) extern uint32_t g_pathRotationVu[32][4];
#else
extern uint32_t g_pathRotationVu[32][4];
#endif

void nocturneBattlePanelColorCpuRead(unsigned reg,uint32_t words[4])
{nocturneEffectHostCpuRead(reg,words);}
void nocturneBattlePanelColorCpuWrite(unsigned reg,const uint32_t words[4])
{nocturneEffectHostCpuWrite(reg,words);}
uint32_t nocturneBattlePanelColorReadFpr(unsigned reg)
{uint32_t *f=nocturneEffectHostFpr();if(reg>=32u||!f)abort();return f[reg];}
void nocturneBattlePanelColorWriteFpr(unsigned reg,uint32_t bits)
{uint32_t *f=nocturneEffectHostFpr();if(reg>=32u||!f)abort();f[reg]=bits;}
void nocturneBattlePanelColorVuRead(unsigned reg,uint32_t words[4])
{
 if(reg>=32u||!words)abort();
 if(!reg){words[0]=words[1]=words[2]=0;words[3]=UINT32_C(0x3f800000);}
 else memcpy(words,g_pathRotationVu[reg],16);
}
void nocturneBattlePanelColorVuWrite(unsigned reg,const uint32_t words[4])
{if(reg>=32u||!words)abort();if(reg)memcpy(g_pathRotationVu[reg],words,16);}
uint32_t nocturneBattlePanelColorStackPointer(void)
{
 uint32_t words[4],sp=nocturneFusionCoreStackPointer();nocturneEffectHostCpuRead(29,words);
 if(words[0]!=sp||words[1])abort();return sp;
}
void nocturneBattlePanelColorSetStackPointer(uint32_t address)
{
 uint32_t words[4];nocturneEffectHostCpuRead(29,words);
 nocturneFusionCoreSetStackPointer(address);
 words[0]=address;words[1]=0;nocturneEffectHostCpuWrite(29,words);
}
void *nocturneResolveBattlePanelColorAddress(uint32_t address)
{return nocturneEffectHostAddress(address);}
