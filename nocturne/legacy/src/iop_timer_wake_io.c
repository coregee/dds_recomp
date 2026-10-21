#include "iop_timer_wake.h"
uint32_t nocturneIopTimerWakeIo(NocturneIopTimerWake *d,uint32_t write,uint32_t address,uint32_t width,uint32_t *value)
{
 static const uint32_t bases[6]={0xbf801100u,0xbf801110u,0xbf801120u,0xbf801480u,0xbf801490u,0xbf8014a0u};
 uint32_t i,index,mask;
 if(!d||!value)return 0u;
 for(i=0u;i<6u;i++)if(address==bases[i]+4u||address==bases[i]+8u){
  if(d->timer_access_count>=64u)return 0u;
  if(address==bases[i]+4u){
   if(width!=2u)return 0u;
   if(write){if(!nocturneIopHardwareTimerIo(&d->prior,write,address,width,value))return 0u;}
   else{
    if(d->read_count>16u||d->read_index>=d->read_count)return 0u;
    index=d->read_index;
    if(d->read_profile[index][0]!=address||d->read_profile[index][1]!=width||d->read_profile[index][2]>0xffffu)return 0u;
    *value=d->read_profile[index][2];d->read_index++;
   }
  }else{
   if(!write||width!=(i<3u?2u:4u))return 0u;
   mask=width==2u?0xffffu:0xffffffffu;
   d->timer_compare[i]=*value&mask;
  }
  index=d->timer_access_count++;
  d->timer_accesses[index][0]=write;d->timer_accesses[index][1]=address;
  d->timer_accesses[index][2]=width;d->timer_accesses[index][3]=*value&(width==2u?0xffffu:0xffffffffu);
  return 1u;
 }
 return nocturneIopHardwareTimerIo(&d->prior,write,address,width,value);
}
