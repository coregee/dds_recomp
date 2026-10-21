#include "iop_libsd_effect.h"
int nocturneIopLibSdEffectIo(NocturneIopLibSdEffect *d,uint32_t write,uint32_t address,uint32_t width,uint32_t *v)
{
 static const uint32_t addresses[6]={0xbf8010c0u,0xbf8010c4u,0xbf8010c8u,0xbf801500u,0xbf801504u,0xbf801508u};
 uint32_t i,shift,mask,n;if(!d||!v)return 0;
 for(i=0u;i<6u;++i)if(address>=addresses[i]&&address+width<=addresses[i]+4u)break;
 if(i==6u)return nocturneIopLibSdIo(&d->prior,write,address,width,v);
 if((width!=2u&&width!=4u)||(address&(width-1u))||d->prior.io_event_count>=4096u)return 0;
 shift=(address-addresses[i])*8u;mask=width==2u?0xffffu:0xffffffffu;
 if(write)d->voice_dma[i]=(d->voice_dma[i]&~(mask<<shift))|((*v&mask)<<shift);else *v=(d->voice_dma[i]>>shift)&mask;
 n=d->prior.io_event_count++;d->prior.io_events[n][0]=write;d->prior.io_events[n][1]=address;d->prior.io_events[n][2]=width;d->prior.io_events[n][3]=*v&mask;return 1;
}
