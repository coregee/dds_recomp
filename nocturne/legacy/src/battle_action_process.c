/* Complete original dispatcher and its wait/finish/ADPCM prerequisites.
 * Native table/record layouts remain authoritative over managed HD delegates. */
#include "battle_action_process.h"
#include "battle_action_entry.h"
#include "battle_action_sequence.h"
#include "battle_panel_support.h"
#include "battle_stock_renderer.h"
#include "process_lists.h"
#include "event_camera.h"
#include "movie_draw.h"
#include "libc_printf.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattlePanelSupportAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t lb(uint32_t a){return (uint64_t)(int64_t)(int8_t)*at(a);}
/* Three distinct original empty table callbacks. Their HD bodies are shared. */
void ps2BattleActionEnterWait(uint64_t c){(void)c;}
void ps2BattleActionEnterCheck3(uint64_t c){(void)c;}
void ps2BattleActionEnterAfter(uint64_t c){(void)c;}
/* 00257468: WAIT update requests READY18, then the process defers entry. */
uint64_t nbActionCheckWait(uint64_t context){nbActionSetNextSeq(context,18);return 1;}
/* 00257BF0: shared-empty/constant HD body cannot establish unique identity. */
uint64_t ps2BattleActionCheckEnd(uint64_t context){(void)context;return 1;}
/* 00257B08: reload flags after each actual diagnostic printf. */
void nbActionSetEnd(uint64_t context){
 static const uint32_t texts[]={0x544070,0x544088,0x5440a0,0x5440b0,0x5440c0,0x5440d8};
 for(unsigned k=0;k<6;k++)if(r32((uint32_t)context+4)&(0x10000u<<k))(void)ps2LibcPrintf(texts[k]);
}
/* 0025E8E0: actual name search and unconditional process-data tail call. */
uint64_t nbGetKoukaProcessData(void){return dds3GetProcessData(dds3SearchProcessName(0x544350));}
/* 0025E928: full raw64 context equality against signed LW owner pointers. */
uint64_t ps2BattleCountContextKouka(uint64_t context){
 uint32_t node=r32((uint32_t)nbGetKoukaProcessData()+8),count=0;
 while(node){uint64_t owner=sx(r32(node+8));node=r32(node+12);if(owner==context)count++;}
 return sx(count);
}
/* 00257A70: native CHECK3 only waits for its original context-owned packets.
 * HD uses unique IDs and adds stock-hide behavior; neither is copied here. */
uint64_t nbActionCheckCheck3(uint64_t context){
 if((int64_t)ps2BattleCountContextKouka(context)>0)return 0;
 nbActionSetNextSeq(context,21);return 1;
}
/* 002C2178 /002C2180: ADPCM status and real command100 submission. */
uint64_t ps2MovieCheckAdpcmFlag(void){return sx(r32(0x5519c8));}
uint64_t ps2MovieStopAdpcm(void){return ps2MovieCommandSubmit(0x100,0,0,0);}
/* 00257CD0: A0 is the original process argument even though the old listing
 * omitted it. Indirect callbacks execute, rather than supplying canned results. */
uint64_t nbActionProcess1(uint64_t process){
 uint64_t context=dds3GetProcessData(process);uint32_t c=(uint32_t)context;
 if(r32(c+4)&0x400)(void)nbPanelStockSelect(sx(r32(c)),0);
 uint64_t previous=nbGetPrevActionSeq();uint32_t flags=r32(c+4);int advance=1;
 uint64_t state=lb(c+((flags&2)?9:8));
 if(state==7){advance=previous>=19;if(ps2MovieCheckAdpcmFlag()){(void)ps2LibcPrintf(0x5440e8);(void)ps2MovieStopAdpcm();}flags=r32(c+4);}
 if(flags&0x40)return 0;
 if(!advance)return 0;
 if(flags&2){if(lb(c+8)==22)return UINT64_MAX;nbActionSetSeq(context,lb(c+9));w32(c+4,r32(c+4)&~2u);return 0;}
 uint32_t target=r32(0x3fa7c4u+(uint32_t)lb(c+8)*8u);uint64_t value;
#if UINTPTR_MAX > UINT32_MAX
 value=nocturneInvokeBattleActionUpdate(target,context);
#else
 value=((uint64_t (*)(uint64_t))(uintptr_t)target)(context);
#endif
 if(value)w32(c+4,r32(c+4)|2u);
 uint32_t frame=r16(c+10);if(frame<=0xfffe)w16(c+10,(uint16_t)(frame+1));return 0;
}
