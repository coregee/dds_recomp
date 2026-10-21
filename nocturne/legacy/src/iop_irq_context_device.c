#include "iop_irq_context.h"
static int event(NocturneIopIrqContext *d,uint32_t w,uint32_t a,uint32_t v)
{uint32_t n=d->event_count;if(n>=64u)return 0;d->events[n][0]=w;d->events[n][1]=a;d->events[n][2]=4u;d->events[n][3]=v;d->event_count=n+1u;if(w)++d->writes;else ++d->reads;return 1;}
int nocturneIopCp0Event(NocturneIopIrqContext *d,uint32_t kind,uint32_t reg,uint32_t v)
{uint32_t n=d->cp0_event_count;if(n>=16u)return 0;d->cp0_events[n][0]=kind;d->cp0_events[n][1]=reg;d->cp0_events[n][2]=v;d->cp0_event_count=n+1u;return 1;}
static void wake(NocturneIopIrqContext *d)
{if(d->dma.sifman.irq.ictrl&&(d->dma.intc_status&d->intc_mask))++d->wake_requests;}
int nocturneIopIrqRead(NocturneIopIrqContext *d,uint32_t a,uint32_t *v)
{
 if(!d||!v)return 0;
 if(a==0xbf801070u)*v=d->dma.intc_status;
 else if(a==0xbf801074u)*v=d->intc_mask;
 else if(a==0xbf801078u){*v=d->dma.sifman.irq.ictrl;d->dma.sifman.irq.ictrl=0u;++d->dma.sifman.irq.reads;}
 else return 0;
 return event(d,0u,a,*v);
}
int nocturneIopIrqWrite(NocturneIopIrqContext *d,uint32_t a,uint32_t v)
{
 if(!d||!event(d,1u,a,v))return 0;
 if(a==0xbf801070u){d->dma.intc_status&=v;if(v==0xffffffffu)d->dma.intc_status|=12u;}
 else if(a==0xbf801074u){d->intc_mask=v;wake(d);}
 else if(a==0xbf801078u){d->dma.sifman.irq.ictrl=v;++d->dma.sifman.irq.writes;wake(d);}
 else return 0;
 return 1;
}
uint32_t nocturneIopIrqContextRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopIrqContext *d)
{
 uint64_t start;uint32_t r;
 if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x4c3cu&&m->pc<0x50f4u&&m->pc!=0x5094u)||(m->pc>=0x4ba0u&&m->pc<0x4bc8u)||(m->pc>=0x5110u&&m->pc<0x512cu)||(m->pc>=0xc170u&&m->pc<0xc1a4u))r=nocturneIopIrqContextResume(m,ram,n,1u,d);
  else{d->dma.cause=d->cp0[13];r=nocturneIopDmaRoute(m,ram,n,1u,&d->dma);d->cp0[13]=d->dma.cause;}
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
