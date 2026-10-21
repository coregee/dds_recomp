/* Packed PS2 script VM accessors, command bridge and dispatch loop. */
#include "script_core.h"
#include "script_movie.h"
#include "ee_fpu.h"
#include "script_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveScriptCoreAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t sh(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v&0x8000u?0xffff0000u|v:v;}
static uint64_t call(uint32_t entry,uint64_t work,unsigned command){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneInvokeScriptFunction(entry,work,command);
#else
 return command?((uint64_t (*)(void))(uintptr_t)entry)():((uint64_t (*)(uint64_t))(uintptr_t)entry)(work);
#endif
}
uint32_t scrGetFloatParaBits(uint64_t index){
 uint32_t work=r32(0x551c78),cursor=r32(work+0x1c)-(uint32_t)index;
 uint8_t tag=*at(work+0x1f+cursor);if(tag>4)return 0;
 uint32_t value=r32(work+0x3c+(cursor-1)*4);
 switch(tag){
 case 0:case 4:return EE_FPU_CVT_S_W(value);
 case 1:return value;
 case 2:return EE_FPU_CVT_S_W(r32(r32(0x54ea20)+0x40+value*4));
 case 3:return r32(r32(0x54ea20)+0x440+value*4);
 default:return 0;
 }
}
uint64_t scrGetStrPara(uint64_t index){
 uint32_t work=r32(0x551c78),cursor=r32(work+0x1c)-(uint32_t)index;
 if(*at(work+0x1f+cursor)!=5)return 0;
 return sx(r32(work+0x3c+(cursor-1)*4));
}
uint64_t scrGetLabelCodeAddress(uint64_t label){uint32_t w=r32(0x551c78);return sx(r32(r32(w+0xb8)+(uint32_t)label*32+0x18));}
void scrSetCodePointer(uint64_t code){w32(r32(0x551c78)+0x18,(uint32_t)code);}
uint64_t scrGetCommandTimer(void){return sx(r32(r32(0x551c78)+0xd4));}
uint64_t scrGetMessageHandle(void){return sx(r32(r32(0x551c78)+0xcc));}
uint64_t scrGetScriptHandle(void){return sx(r32(0x551c78));}
uint64_t scrGetData(void){return sx(r32(r32(0x551c78)+0xf0));}
uint64_t ps2ScriptSkipRequested(void){return scrGetCommandTimer()!=0&&(*at(0x5298c9)&0x80)!=0;}
uint64_t scrCommand_SYNC(void){return scrGetCommandTimer()!=0;}
uint64_t scrCommand_WAIT(void){
 uint64_t delay=scrGetIntPara(0);if((int64_t)delay<=0)return 1;
 uint64_t timer=scrGetCommandTimer();delay=scrGetIntPara(0);return (int64_t)timer>=(int64_t)delay;
}
uint64_t scrCommand_SEL_JMP(void){
 uint64_t choice=scrGetIntPara(0);if((int64_t)choice<0)return 1;
 uint64_t label=scrGetIntPara(sx((uint32_t)choice+1));if((int64_t)label<0)return 1;
 scrSetCodePointer(scrGetLabelCodeAddress(label));return 1;
}
uint64_t scrPopInt(uint64_t work_raw){
 uint32_t w=(uint32_t)work_raw,count=r32(w+0x1c);w32(w+0x1c,count-1);
 uint8_t tag=*at(w+0x1f+count);if(tag>4)return 0;
 uint32_t value=r32(w+0x3c+r32(w+0x1c)*4);
 switch(tag){
 case 0:case 4:return sx(value);
 case 1:return sx(EE_FPU_CVT_W_S(value));
 case 2:return sx(r32(r32(0x54ea20)+0x40+value*4));
 case 3:return sx(EE_FPU_CVT_W_S(r32(r32(0x54ea20)+0x440+value*4)));
 default:return 0;
 }
}
uint64_t scrCodeFunc_Minus(uint64_t raw){
 uint32_t w=(uint32_t)raw,count=r32(w+0x1c);uint8_t tag=*at(w+0x1f+count);
 if(tag<4){
  uint32_t slot=w+0x38+count*4;
  if(tag>=2)slot=r32(0x54ea20)+(tag==2?0x40:0x440)+r32(slot)*4;
  uint32_t value=r32(slot);w32(slot,tag&1?EE_FPU_NEG_S(value):0u-value);
 }
 w32(w+0x18,r32(w+0x18)+1);return 1;
}
uint64_t scrCodeFunc_Comm(uint64_t raw){
 uint32_t w=(uint32_t)raw,cp=r32(w+0x18),command=sh(r32(w+0xbc)+cp*4+2),descriptor=0x52e350+command*8;
 w32(0x551c78,w);if(!call(r32(descriptor),raw,1))return 2;
 /* Counts and the code pointer are deliberately reloaded after the callback. */
 w32(w+0x1c,r32(w+0x1c)-r32(descriptor+4));
 if(r32(w+0x18)==cp)w32(w+0x18,cp+1);return 1;
}
uint64_t scrCodeFunc_End(uint64_t raw){
 uint32_t w=(uint32_t)raw;if(!r32(w+0x1c))return 0;
 uint64_t code=scrPopInt(raw);w32(w+0x18,(uint32_t)code+1);return 1;
}
uint64_t scrCodeFunc_Goto(uint64_t raw){
 uint32_t w=(uint32_t)raw,label=sh(r32(w+0xbc)+r32(w+0x18)*4+2);
 w32(w+0x18,r32(r32(w+0xb8)+label*32+0x18));return 1;
}
uint64_t ps2ScriptTrace(uint64_t raw){
 uint32_t w=(uint32_t)raw;
 for(;;){
  uint32_t opcode=sh(r32(w+0xbc)+r32(w+0x18)*4);
  uint64_t result=call(r32(0x2fa528+opcode*4),raw,0);
  if(!result){w32(w+0xd4,0);return 2;}
  if(result==2){w32(w+0xd4,r32(w+0xd4)+1);w32(w+0xd0,r32(w+0xd0)+1);return 1;}
  if(result==1)w32(w+0xd4,0);
 }
}
