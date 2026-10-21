#include "battle_ai_startup.h"
#include "script_construction.h"
#include "script_process.h"
#include "script_core.h"
#include "script_movie.h"
#include "process_lists.h"
#include "process_shutdown.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "ps2_memory.h"
#include "sound_bank_support.h"
#include "libc_stream.h"
#include <string.h>
extern void *nocturneTryLibcStreamLocalAddress(uint32_t address);
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 void *local=nocturneTryLibcStreamLocalAddress(a);
 return local?(uint8_t *)local:(uint8_t *)nocturneResolveBattleAiStartupAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int64_t s32(uint32_t v){return v&0x80000000u?(int64_t)v-INT64_C(0x100000000):v;}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}

/* 00101AF8: detach first, then walk the live sibling chain and append. */
void dds3LinkProcess(uint64_t parent,uint64_t target){
 uint32_t p=(uint32_t)parent,t=(uint32_t)target;
 if(r32(t+0x44))dds3UnlinkProcess(target);
 uint32_t child=r32(p+0x48);
 if(!child)w32(p+0x48,t);
 else{uint32_t next=r32(child+0x4c);while(next){child=next;next=r32(child+0x4c);}w32(child+0x4c,t);}
 w32(t+0x44,p);
}

/* 00288D80: the native executable always selects the embedded BF. */
void nbInitAiScript(uint64_t context,uint64_t procedure){
 uint32_t c=(uint32_t)context,parent=r32(r32(c)+0xbc);
 uint64_t process=scrStartScript2(sx(r32(parent+0x20)-1u),0x4f0800,procedure);
 scrSetUserData(process,context);
 uint32_t work=(uint32_t)dds3GetProcessData(process),id=r32(work+0xcc);
 if(!(id&0x80000000u))itfMesMngSetVar(sx(id),0,r16(r32(c+0x2c)+4),1);
 dds3LinkProcess(sx(r32(r32(c)+0xbc)),process);
 w32(r32(c)+0x104,(uint32_t)process);
}
/* 001CD710 / command113: negative message handles skip parameter reads. */
uint64_t itfMesMngSetVarScr(void){
 uint64_t id=scrGetMessageHandle();
 if(!(id>>63)){
  uint64_t index=scrGetIntPara(0),number=scrGetIntPara(1),type=scrGetIntPara(2);
  itfMesMngSetVar(id,index,number,type);
 }
 return 1;
}

/* 001CF320: rounded string copies include the bytes after NUL; retain them.
 * Positive explicit lengths clear the whole rounded allocation before copy. */
uint64_t itfMesSetVar(uint64_t instance,uint64_t index,uint64_t string,uint64_t bytes){
 uint32_t base=(uint32_t)instance+0xc4,offset=(uint32_t)index*4u,slot=base+offset;
 if(r32(slot)){ps2MemoryHandleFree(r32(base+offset+0x80));w32(slot,0);}
 uint32_t size;
 int positive=bytes!=0&&!(bytes>>63);
 if(positive)size=((uint32_t)bytes+5u)&~3u;
 else size=(ps2Strlen((char *)at((uint32_t)string))+4u)&~3u;
 uint32_t handle=ps2MemoryHandleAllocate((int32_t)s32(size));w32(base+offset+0x80,handle);
 uint32_t p=ps2MemoryHandleAcquirePointer(handle);w32(slot,p);
 if(positive){(void)ps2Memset(at(p),0,size);p=r32(slot);(void)ps2Memcpy(at(p),at((uint32_t)string),(uint32_t)bytes);}
 else (void)ps2Memcpy(at(p),at((uint32_t)string),size);
 return sx(p);
}
void itfMesMngSetVariableString(uint64_t id,uint64_t index,uint64_t string){
 (void)itfMesSetVar(sx(r32(0x56be8c+(uint32_t)id*20u)),index,string,0);
}
void itfMesMngSetVariableBytes(uint64_t id,uint64_t index,uint64_t string,uint64_t bytes){
 (void)itfMesSetVar(sx(r32(0x56be8c+(uint32_t)id*20u)),index,string,bytes);
}

/* 001CFE48: negative inputs retain low-byte signed remainders, not a sign. */
uint64_t ps2MessageWriteDecimal(uint64_t number,uint64_t output){
 int32_t digits[10];unsigned count=0;int64_t value=s32((uint32_t)number);
 do{digits[count++]=(int32_t)(value%10);value/=10;}while(value>0&&count<10);
 uint32_t p=(uint32_t)output;while(count)*at(p++)=(uint8_t)((uint8_t)digits[--count]+0x30u);
 *at(p)=0;return sx(p);
}

/* 001CE538: original two-byte character records and live character counts. */
void ps2MessageBuildCharacterName(uint64_t index){
 uint32_t root=r32(0x54ea20),i=(uint32_t)index,p=0x56c880,k=0;
 if(*at(root+i+0x6654)){
  do{uint32_t source=root+4u+i*20u+0x6600u+k*2u;uint8_t lead=*at(source);
   if(lead&0x80)*at(p++)=lead;
   *at(p++)=*at(source+1);k++;
  }while(k<*at(root+i+0x6654));
 }
 *at(p)=0;
}

/* 001CE5E8: exact native eleven-way conversion table; type2 is empty. */
void itfMesMngSetVar(uint64_t id,uint64_t index,uint64_t number,uint64_t type){
 if(type>=11||type==2)return;
 uint32_t pointer=0,n=(uint32_t)number;
 switch(type){
 case 0:case 4:{
  uint8_t frame[80];
#if UINTPTR_MAX > UINT32_MAX
  nocturneBattleAiMessageAmbientFrame(frame,sizeof(frame));
  uint32_t local=nocturneLibcStreamLocalAddress(frame,sizeof(frame));
#else
  uint32_t local=(uint32_t)(uintptr_t)frame;
#endif
  if(type==0)(void)ps2LibcSprintf(local,0x54f4c0,number);
  else{uint32_t p=local+0x10;
   if(!less(number,1001)){*at(p)='R';*at(p+1)=0;}
   else{uint32_t cursor=p;
    if(number>>63){n=0u-n;*at(cursor++)='B';}
    cursor=(uint32_t)ps2MessageWriteDecimal(sx(n),sx(cursor));*at(cursor)='F';*at(cursor+1)=0;
   }
  }
  itfMesMngSetVariableString(id,index,sx(local+(type==4?0x10u:0u)));
#if UINTPTR_MAX > UINT32_MAX
  nocturneLibcStreamEndLocal();
#endif
  return;
 }
 case 1:pointer=r32(0x3e7328+n*4u);break;
 case 3:pointer=r32(0x3e8170+n*4u);break;
 case 5:pointer=r32(0x3e83f0+n*4u);break;
 case 6:pointer=0x311450+n*32u;break;
 case 7:pointer=0x311850+n*32u;break;
 case 8:pointer=r32(0x3e7930+n*4u);break;
 case 9:pointer=r32(0x3e8c30+n*4u);break;
 default:ps2MessageBuildCharacterName(number);itfMesMngSetVariableBytes(id,index,0x56c880,ps2Strlen((char *)at(0x56c880)));return;
 }
 itfMesMngSetVariableString(id,index,sx(pointer));
}
