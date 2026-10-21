/* Original packed PS2 VM slots and movie script wrappers. */
#include "script_movie.h"
#include "movie_manager.h"
#include "movie_draw.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveScriptVmAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t scrGetIntPara(uint64_t index){
 uint32_t work=r32(0x551c78),cursor=r32(work+0x1c)-(uint32_t)index;
 uint8_t tag=*at(work+0x1f+cursor);
 if(tag>4)return 0;
 uint32_t slot=work+0x3c+((cursor-1)*4),value=r32(slot);
 switch(tag){
 case 0:case 4:return sx(value);
 case 1:return sx(EE_FPU_CVT_W_S(value));
 case 2:return sx(r32(r32(0x54ea20)+0x40+value*4));
 case 3:return sx(EE_FPU_CVT_W_S(r32(r32(0x54ea20)+0x440+value*4)));
 default:return 0;
 }
}
void scrSetIntReturnValue(uint64_t value){
 *at(r32(0x551c78)+0x3b)=0;
 /* Reload after the byte store: original memory may alias the work pointer. */
 uint32_t low=(uint32_t)value;memcpy(at(r32(0x551c78)+0xa8),&low,4);
}
uint64_t mviScrCmd_MOVIE_PLAY(void){ps2MoviePlayIndex(scrGetIntPara(0));return 1;}
uint64_t mviScrCmd_MOVIE_STOP(void){ps2MovieStop();return 1;}
uint64_t mviScrCmd_MOVIE_CHK(void){scrSetIntReturnValue(ps2MovieCheckEnd()==0);return 1;}
uint64_t mviScrCmd_MOVIE_CHKDRAW(void){return ps2MovieCheckDrawState()==2;}
