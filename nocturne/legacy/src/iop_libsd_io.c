#include "iop_libsd.h"
int nocturneIopLibSdIo(NocturneIopLibSd *d,uint32_t write,uint32_t address,uint32_t width,uint32_t *v)
{
 static const uint32_t addresses[6]={0xbf801404u,0xbf80140cu,0xbf8010f0u,0xbf801570u,0xbf801014u,0xbf801414u};
 uint32_t i,n;NocturneIopIrqContext *irq;
 if(!d||!v)return 0;irq=&d->prior.thread.queue.thread.irq;
 if(width==4u&&(address==0xbf801070u||address==0xbf801074u||address==0xbf801078u))
  return write?nocturneIopIrqWrite(irq,address,*v):nocturneIopIrqRead(irq,address,v);
 if(width==4u&&(address==0xbf8010f4u||address==0xbf801574u||address==0xbf801578u))
  return write?nocturneIopDmaWrite(&irq->dma,address,*v):nocturneIopDmaRead(&irq->dma,address,v);
 if(d->io_event_count>=4096u)return 0;
 if(width==2u&&address>=0xbf900000u&&address<0xbf900800u&&!(address&1u)){
  i=(address-0xbf900000u)/2u;if(write)d->spu2[i]=(uint16_t)*v;else *v=d->spu2[i];*v&=0xffffu;
 }else{
  if(width!=4u)return 0;
  for(i=0;i<6u&&addresses[i]!=address;++i){}
  if(i==6u)return 0;
  if(write)d->iop[i]=*v;else *v=d->iop[i];
 }
 n=d->io_event_count++;d->io_events[n][0]=write;d->io_events[n][1]=address;d->io_events[n][2]=width;d->io_events[n][3]=*v;return 1;
}
