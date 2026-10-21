#include "native_runtime_router.h"
static uint32_t finish(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why)
{
 s->outcome=why;s->pc=m->pc;s->address=s->bytes=0;
 s->target=why==NOCTURNE_NATIVE_TRANSFER?(uint64_t)(int64_t)(int32_t)m->pc:0;
 return why;
}
static int zero_bank(const NocturneWakeupMachine *m)
{return !(m->gpr[0][0]|m->gpr[0][1]|m->gpr[0][2]|m->gpr[0][3]);}
uint32_t nocturneNativeEnterSyscall(NocturneWakeupMachine *m,uint64_t remaining,NocturneWakeupStop *s)
{
 if(!m||!s)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
 if(!zero_bank(m)||(m->pc&3u))return finish(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN);
 if(!remaining)return finish(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT);
 if(m->status&UINT32_C(0x00400006))return finish(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN);
 ++m->instructions;m->epc=m->pc;
 m->cause=(m->cause&~UINT32_C(0x8000007c))|UINT32_C(0x20);
 m->status|=2u;m->pc=UINT32_C(0x80000180);
 return finish(m,s,NOCTURNE_NATIVE_TRANSFER);
}
uint32_t nocturneNativeRouteResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,const NocturneNativeRouter *router,uint64_t remaining,uint32_t stop_pc,NocturneWakeupStop *s,NocturneNativeRouteCounts *counts)
{
 uint64_t started,prior;uint32_t outcome,prior_pc;
 if(!m||!ram||!ram->read||!ram->write||!router||!router->contains||!router->resume||!s||!counts)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
 if(!zero_bank(m))return finish(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN);
 started=m->instructions;
 for(;;){
  if(m->pc==stop_pc||!router->contains(router->owner,m->pc))return finish(m,s,NOCTURNE_NATIVE_TRANSFER);
  if(m->instructions-started>=remaining)return finish(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT);
  prior=m->instructions;prior_pc=m->pc;++counts->dispatches;
  outcome=router->resume(router->owner,m,ram,remaining-(m->instructions-started),s);
  if(m->instructions<prior||m->instructions-started>remaining)return finish(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN);
  if(outcome==NOCTURNE_NATIVE_SYSCALL){
   outcome=nocturneNativeEnterSyscall(m,remaining-(m->instructions-started),s);
   if(outcome!=NOCTURNE_NATIVE_TRANSFER)return outcome;
   ++counts->syscalls;
  }else if(outcome==NOCTURNE_WAKEUP_RETURNED){++counts->erets;}
  else if(outcome!=NOCTURNE_NATIVE_TRANSFER)return outcome;
  if(m->instructions==prior&&m->pc==prior_pc)return finish(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN);
 }
}
