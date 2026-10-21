#include "battle_alarm_runtime.h"
#include "battle_syscall_kernel_resume.h"
#include "battle_irq_kernel.h"
#include "battle_alarm_payload.h"
#include "battle_alarm_callbacks.h"
#include <string.h>
typedef struct RuntimeMemory {const NocturneWakeupMemory *ram;NocturneAlarmRuntime *runtime;}RuntimeMemory;
static uint32_t physical_bus(uint32_t p){return p>=0x80000000u&&p<0xc0000000u?p&0x1fffffffu:p;}
static int bus(uint32_t p){return p==0x10001800u||p==0x10001810u||p==0x10001820u||p==0x1000f000u||p==0x1000f010u;}
static int read_memory(void *v,uint32_t a,void *p,uint32_t n)
{
 RuntimeMemory *owner=(RuntimeMemory*)v;uint32_t b=physical_bus(a),value;
 if(bus(b)){if(n!=4||!nocturneTimer3ClockRead(&owner->runtime->clock,b,&value))return 0;memcpy(p,&value,4);if(owner->runtime->observe_bus)owner->runtime->observe_bus(owner->runtime->bus_observer_owner,0,b,value);return 1;}
 return owner->ram->read(owner->ram->owner,a,p,n);
}
static int write_memory(void *v,uint32_t a,const void *p,uint32_t n)
{
 RuntimeMemory *owner=(RuntimeMemory*)v;uint32_t b=physical_bus(a),value;
 if(bus(b)){if(n!=4)return 0;memcpy(&value,p,4);if(!nocturneTimer3ClockWrite(&owner->runtime->clock,b,value))return 0;if(owner->runtime->observe_bus)owner->runtime->observe_bus(owner->runtime->bus_observer_owner,1,b,value);return 1;}
 return owner->ram->write(owner->ram->owner,a,p,n);
}
static uint64_t low(const NocturneWakeupMachine *m,unsigned r){return(uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t outcome,uint32_t a,uint32_t n)
{s->outcome=outcome;s->pc=m->pc;s->address=a;s->bytes=n;s->target=(outcome==8||outcome==0)?(uint64_t)(int64_t)(int32_t)m->pc:0;return outcome;}
static void syscall_exception(NocturneWakeupMachine *m,NocturneAlarmRuntime *runtime)
{
 /* Installed emulator cpuException(0x20,bd=0), at a genuine SYS boundary.
  * Device IP delivery is owned separately; no stale frozen IRQ Cause reply. */
 m->cause=0x20u;m->epc=m->pc;m->status|=2u;m->pc=0x80000180u;++runtime->syscall_entries;
}
static int idle_pc(uint32_t p){return p>=0x81fc0u&&p<0x81fe0u&&!(p&3u);}
static uint32_t idle(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,NocturneAlarmRuntime *runtime,uint64_t end,NocturneWakeupStop *s)
{
 uint32_t word,slot=(m->pc-0x81fc0u)/4u;
 if(m->instructions>=end)return stop(m,s,7,0,0);
 if(!ram->read(ram->owner,m->pc,&word,4))return stop(m,s,2,m->pc,4);
 if(word!=(slot==6u?0x1000fff9u:0u))return stop(m,s,10,m->pc,4);
 if(slot==6u){
  if(end-m->instructions<2u)return stop(m,s,7,0,0);
  uint32_t delay;
  if(!ram->read(ram->owner,m->pc+4u,&delay,4))return stop(m,s,2,m->pc+4u,4);
  if(delay)return stop(m,s,10,m->pc+4u,4);
  m->instructions+=2u;runtime->idle_words+=2u;m->pc=0x81fc0u;++runtime->idle_spins;
  if(!nocturneTimer3ClockHblank(&runtime->clock))return stop(m,s,10,0,0);
  /* Pending INTC12 is consumed only with actual CPU interrupt eligibility.
   * This profile arbitrates between complete spins, never in a delay slot. */
  if(nocturneTimer3ClockIntcEligible(&runtime->clock,m->status)){
   m->cause=0x400u;m->epc=m->pc;m->status|=2u;m->pc=(m->status&0x400000u)?0xbfc00400u:0x80000200u;++runtime->irq_entries;
  }
 }else{++m->instructions;++runtime->idle_words;m->pc+=4u;}
 return 8;
}
uint32_t nocturneBattleAlarmRuntimeSyscall(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,NocturneAlarmRuntime *runtime,uint32_t pc,uint64_t limit,NocturneWakeupStop *s)
{
 RuntimeMemory owner;NocturneWakeupMemory memory;uint64_t started,end,selector;uint32_t outcome,return_pc;
 if(!m||!ram||!ram->read||!ram->write||!runtime||!s||!nocturneTimer3ClockValid(&runtime->clock))return 6;
 memset(s,0,sizeof(*s));selector=low(m,3);
 if((m->status&0x400006u)||!((selector==47u&&pc==0x2dbd94u)||(selector==50u&&pc==0x2dbdc4u)||(selector==51u&&pc==0x2dbdd4u)||(selector==53u&&pc==0x2dbdf4u)||(selector==252u&&pc==0x2dbc24u)))return stop(m,s,6,0,0);
 if(!limit)return stop(m,s,7,0,0);
 for(unsigned i=0;i<4;++i)if(m->gpr[0][i])return stop(m,s,6,0,0);
 started=m->instructions;if(UINT64_MAX-started<limit)return stop(m,s,6,0,0);end=started+limit;return_pc=pc+4;
 owner.ram=ram;owner.runtime=runtime;memory.owner=&owner;memory.read=read_memory;memory.write=write_memory;
 m->pc=pc;syscall_exception(m,runtime);
 while(1){
  uint32_t initial_pc=m->pc;uint64_t initial_steps=m->instructions;
  if(idle_pc(m->pc)){outcome=idle(m,&memory,runtime,end,s);if(outcome!=8)return outcome;continue;}
  if(m->instructions>=end)return stop(m,s,7,0,0);
  outcome=nocturneBattleSyscallKernelResume(m,&memory,end-m->instructions,s);
  if(outcome==8&&m->pc==initial_pc&&m->instructions==initial_steps)outcome=nocturneBattleIrqKernelResume(m,&memory,end-m->instructions,s);
  if(outcome==8&&m->pc==initial_pc&&m->instructions==initial_steps)outcome=nocturneBattleAlarmPayloadResume(m,&memory,end-m->instructions,s);
  if(outcome==8&&m->pc==initial_pc&&m->instructions==initial_steps)outcome=nocturneBattleAlarmCallbacks(m,&memory,end-m->instructions,s);
  if(outcome==9){
   if(m->status&0x400006u)return stop(m,s,10,0,0);
   if(m->instructions>=end)return stop(m,s,7,0,0);
   ++m->instructions;syscall_exception(m,runtime);
  }else if(outcome==0)++runtime->erets;
  else if(outcome==8){
   if(m->pc==initial_pc&&m->instructions==initial_steps)return stop(m,s,m->pc==return_pc?0u:8u,0,0);
  }else return outcome;
 }
}
