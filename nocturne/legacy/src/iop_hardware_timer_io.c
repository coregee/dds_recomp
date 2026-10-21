#include "iop_hardware_timer.h"
uint32_t nocturneIopHardwareTimerIo(NocturneIopHardwareTimer *d,uint32_t write,uint32_t address,uint32_t width,uint32_t *value)
{
 uint32_t i,index;
 static const uint32_t addresses[6]={0xbf801104u,0xbf801114u,0xbf801124u,0xbf801484u,0xbf801494u,0xbf8014a4u};
 if(!d||!value)return 0u;
 for(i=0u;i<6u;i++)if(address==addresses[i]){
  if(!write||width!=2u||d->timer_event_count>=16u)return 0u;
  index=d->timer_event_count++;d->timer_mode[i]=*value&0xffffu;
  d->timer_events[index][0]=1u;d->timer_events[index][1]=address;
  d->timer_events[index][2]=width;d->timer_events[index][3]=*value&0xffffu;return 1u;
 }
 return nocturneIopLibSdEffectIo(&d->prior,write,address,width,value);
}
