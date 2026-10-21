#include "script_process.h"
#include "script_core.h"
#include "process_creation.h"
#include "process_lists.h"
#include "ps2_memory.h"
#include <string.h>
static uint32_t r32(uint32_t a)
{ uint32_t v;memcpy(&v,nocturneResolveScriptProcessAddress(a),4);return v; }
static void w32(uint32_t a,uint32_t v)
{ memcpy(nocturneResolveScriptProcessAddress(a),&v,4); }
static uint64_t sx(uint32_t v)
{ return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v; }
static int64_t s32(uint32_t v)
{ return v&0x80000000u?(int64_t)v-INT64_C(0x100000000):v; }
/* 00109848: the tail's next word is written before publishing the new tail. */
void scrLinkScriptHandleList(uint64_t work)
{
 uint32_t w=(uint32_t)work,tail=r32(0x54e99c);
 if(tail){w32(w+0xe8,tail);w32(tail+0xec,w);w32(w+0xec,0);w32(0x54e99c,w);}
 else{w32(0x54e998,w);w32(0x54e99c,w);w32(w+0xec,0);w32(w+0xe8,0);}
 w32(0x54e994,r32(0x54e994)+1);
}
/* 00109888: retain full-width LW/pointer equality and live field reloads. */
void scrUnlinkScriptHandleList(uint64_t work)
{
 uint32_t w=(uint32_t)work;
 if(sx(r32(0x54e998))==work)w32(0x54e998,r32(w+0xec));
 else{uint32_t prev=r32(w+0xe8),next=r32(w+0xec);w32(prev+0xec,next);}
 if(sx(r32(0x54e99c))==work)w32(0x54e99c,r32(w+0xe8));
 else{uint32_t next=r32(w+0xec),prev=r32(w+0xe8);w32(next+0xe8,prev);}
 uint32_t count=r32(0x54e994);w32(w+0xec,0);w32(w+0xe8,0);w32(0x54e994,count-1);
}
/* 00109cb8: the existing scheduler owns an 80-byte process, not the VM work. */
uint64_t scrStartScriptProcess(uint64_t priority,uint64_t work)
{
 uint32_t w=(uint32_t)work,index=r32(w+0xc8),table=r32(w+0xb4);
 uint64_t p=dds3StartProcess(sx(table+(index<<5)),priority,1,1,0x10a268,0x10a210,work);
 w32(w+0xe4,(uint32_t)p);return p;
}
/* 00109d10: the context is loaded once; 256 integer/float stores interleave. */
void scrInitGlobalWork(void)
{
 uint32_t p=r32(0x54ea20)+0x440;
 for(unsigned i=0;i<256;i++,p+=4){w32(p-0x400,0);w32(p,0);}
}
/* 0010a078: the recovered PS2 strcmp executes, with the query as left operand. */
uint64_t scrSearchScriptName(uint64_t name)
{
 uint32_t w=r32(0x54e998);
 while(w){
  if(ps2Strcmp(nocturneResolveScriptProcessAddress((uint32_t)name),nocturneResolveScriptProcessAddress(w))==0)return sx(w);
  w=r32(w+0xec);
 }
 return 0;
}
/* 0010a0d0: first kind-zero descriptor wins; this routine never checks FLW0. */
uint64_t scrSearchProcedureName(uint64_t data,uint64_t name)
{
 if(!data)return UINT64_MAX;
 uint32_t d=(uint32_t)data,t=d+0x20,section=0,records=0;
 int64_t count=s32(r32(d+0x10));
 while((int64_t)section<count){
  uint32_t descriptor=t+(section<<4);
  if(r32(descriptor)==0){records=d+r32(descriptor+0xc);break;}
  section++;
 }
 if(!records)return UINT64_MAX;
 uint32_t descriptor=t+(section<<4),index=0,p=records;
 if(s32(r32(descriptor+8))<=0)return UINT64_MAX;
 do{
  uint32_t current=p;p+=32;
  if(ps2Strcmp(nocturneResolveScriptProcessAddress(current),nocturneResolveScriptProcessAddress((uint32_t)name))==0)return sx(index);
  index++;
 }while(s32(index)<s32(r32(descriptor+8)));
 return UINT64_MAX;
}
/* 0010a1c8 / 0010a1f0: process data holds a VM work pointer, whose F0 is user data. */
void scrSetUserData(uint64_t process,uint64_t data)
{ uint32_t w=(uint32_t)dds3GetProcessData(process);w32(w+0xf0,(uint32_t)data); }
uint64_t ps2ScriptGetUserData(uint64_t process)
{ uint32_t w=(uint32_t)dds3GetProcessData(process);return sx(r32(w+0xf0)); }
/* 0010a268: yield keeps the callback; an ended VM returns the scheduler sentinel. */
uint64_t scrScriptProcess(uint64_t process)
{
 uint64_t result=ps2ScriptTrace(dds3GetProcessData(process));
 return result==0||result==2?UINT64_MAX:0;
}
