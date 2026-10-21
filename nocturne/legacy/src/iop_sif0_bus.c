#include "iop_sif0_bus.h"
#include "iop_rpc_reply_native.h"
#include "iop_sifman_irq.h"
static void publish(NocturneIopSif0World *w)
{
 w->bus.madr=w->transport.iop_madr;w->bus.bcr=w->transport.iop_bcr;
 w->bus.chcr=w->transport.iop_chcr;w->bus.tadr=w->transport.iop_tadr;
 w->bus.sbus_control=w->transport.sbus_control;
 w->bus.pending_start=(w->bus.chcr>>24)&1u;
}
uint32_t nocturneIopSif0Resume(NocturneIopMachine *m,uint8_t *ram,uint32_t n,
 uint8_t *ee,uint32_t ne,uint64_t limit,NocturneIopSif0World *w)
{
 uint64_t start;uint32_t status,requests;
 if(!m||!ram||!ee||!w||!w->iop_cycles_per_instruction||w->iop_cycles_per_instruction>16u)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
 while(m->instructions-start<limit){
  requests=w->bus.start_requests;
  if((m->pc>=0x1ae78u&&m->pc<0x1aff0u)||(m->pc>=0x1bad8u&&m->pc<0x1bae0u))
   status=nocturneIopSifmanIrqResume(m,ram,n,1u,&w->bus);
  else if(m->pc>=0x1b074u&&m->pc<0x1b3d4u)
   status=nocturneIopSifmanResume(m,ram,n,1u,&w->bus);
  else status=nocturneIopRpcReplyResume(m,ram,n,1u,&w->bus.irq);
  if(status!=NOCTURNE_IOP_LIMIT)return status;
  w->instruction_clock+=w->iop_cycles_per_instruction;
  if(w->bus.start_requests!=requests){
   w->transport.iop_madr=w->bus.madr;w->transport.iop_bcr=w->bus.bcr;
   w->transport.iop_chcr=w->bus.chcr;w->transport.iop_tadr=w->bus.tadr;
   w->transport.sbus_control=w->bus.sbus_control;
   if(nocturneSif0Drive(&w->transport,ram,n,ee,ne,1u,100000u)!=NOCTURNE_SIF0_WAIT)return NOCTURNE_IOP_DOMAIN;
   publish(w);w->iop_event_armed=w->transport.pending_iop;
   w->iop_due=w->instruction_clock+w->transport.iop_delay;
  }
  if(w->iop_event_armed&&w->instruction_clock>=w->iop_due){
   if(nocturneSif0Drive(&w->transport,ram,n,ee,ne,3u,1u)!=NOCTURNE_SIF0_WAIT)return NOCTURNE_IOP_DOMAIN;
   w->iop_event_armed=0u;publish(w);
  }
 }
 return NOCTURNE_IOP_LIMIT;
}
