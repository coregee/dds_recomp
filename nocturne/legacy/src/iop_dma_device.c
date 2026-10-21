#include "iop_dma_dispatch.h"
/* Pinned PCSX2 fc4d0cdf609e704abd9c41915e898adba5264b29 value semantics.
 * Ordered accesses and IRQ requests only; no CPU exception or handler entry. */
static int access_log(NocturneIopDmaDevice *d,uint32_t w,uint32_t a,uint32_t v)
{uint32_t n=d->event_count;if(n>=512u)return 0;d->events[n][0]=w;d->events[n][1]=a;d->events[n][2]=4u;d->events[n][3]=v;d->event_count=n+1u;if(w)++d->writes;else ++d->reads;return 1;}
static void request(NocturneIopDmaDevice *d){d->intc_status|=8u;++d->irq_requests;}
static void recheck(NocturneIopDmaDevice *d,uint32_t group)
{
 uint32_t i,r=group?d->dicr2:d->dicr1;
 for(i=0;i<6u;++i)if((r&(1u<<(24u+i)))&&((r&(1u<<(16u+i)))||(group&&(i==2u||i==3u)))){
  if(r&0x800000u){if(group)d->dicr2|=0x80000000u;else d->dicr1|=0x80000000u;}
  if(!group)d->cause&=~0x7cu;
  request(d);break;
 }
}
int nocturneIopDmaRead(NocturneIopDmaDevice *d,uint32_t a,uint32_t *v)
{
 if(!d||!v)return 0;
 if(a==0xbf8010f4u)*v=d->dicr1;
 else if(a==0xbf801574u)*v=d->dicr2;
 else if(a==0xbf801578u)*v=d->dma_enable;
 else return 0;
 return access_log(d,0u,a,*v);
}
int nocturneIopDmaWrite(NocturneIopDmaDevice *d,uint32_t a,uint32_t v)
{
 uint32_t r,group;
 if(!d)return 0;
 if(a==0xbf801578u){if(!access_log(d,1u,a,v))return 0;d->dma_enable=v;return 1;}
 if(a!=0xbf8010f4u&&a!=0xbf801574u)return 0;
 if(!access_log(d,1u,a,v))return 0;
 group=(a==0xbf801574u);r=group?d->dicr2:d->dicr1;
 r=((r&0xff000000u)|(v&0xffffffu))&~(v&0x7f000000u);
 if((r&0x8000u)||((r&0x800000u)&&(((r>>8)&r&0x7f0000u)!=0u)))r|=0x80000000u;
 else r&=~0x80000000u;
 if(group)d->dicr2=r;else d->dicr1=r;
 if(r&0x8000u){d->cause&=~0x7cu;request(d);}
 else recheck(d,group);
 return 1;
}
int nocturneIopDmaPublishSif0(NocturneIopDmaDevice *d)
{
 if(!d)return 0;
 /* Actual psxDmaInterrupt2(2): SIF0 tag/end interrupts bypass mask18. */
 d->dicr2|=1u<<26;if(d->dicr2&0x800000u)d->dicr2|=0x80000000u;
 request(d);return 1;
}
uint32_t nocturneIopDmaRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopDmaDevice *d)
{
 uint64_t start;uint32_t r;
 if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x473cu&&m->pc<0x4b50u)||(m->pc>=0x5100u&&m->pc<0x5108u))r=nocturneIopDmaDispatchResume(m,ram,n,1u,d);
  else if((m->pc>=0x1ae78u&&m->pc<0x1aff0u)||(m->pc>=0x1bad8u&&m->pc<0x1bae0u))r=nocturneIopSifmanIrqResume(m,ram,n,1u,&d->sifman);
  else if(m->pc>=0x1b074u&&m->pc<0x1b3d4u)r=nocturneIopSifmanResume(m,ram,n,1u,&d->sifman);
  else return NOCTURNE_IOP_TRANSFER;
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
