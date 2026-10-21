#include "battle_timer3_clock.h"
/* Counter transition rules corroborated against pinned PCSX2 Counters.cpp.
 * This is a finite device profile, not an EE cycle/video/IOP simulator. */
int nocturneTimer3ClockValid(const NocturneTimer3Clock *s)
{return s&&s->count<=0xffffu&&s->comp<=0xffffu&&s->mode<=0xfffu&&(s->mode&0x7fu)==3u&&s->target_future<=1u;}
int nocturneTimer3ClockRead(const NocturneTimer3Clock *s,uint32_t p,uint32_t *out)
{
 if(!out||!nocturneTimer3ClockValid(s))return 0;
 switch(p){case 0x10001800:*out=s->count;break;case 0x10001810:*out=s->mode;break;
 case 0x10001820:*out=s->comp;break;case 0x1000f000:*out=s->intc_stat;break;case 0x1000f010:*out=s->intc_mask;break;default:return 0;}return 1;
}
int nocturneTimer3ClockWrite(NocturneTimer3Clock *s,uint32_t p,uint32_t v)
{
 if(!nocturneTimer3ClockValid(s))return 0;
 switch(p){
 case 0x10001800:s->count=v&0xffffu;s->target_future=s->count>=s->comp;break;
 case 0x10001810:
  if((v&0x7fu)!=3u)return 0;
  s->mode=(v&0x3ffu)|((s->mode&0xc00u)&~v);break;
 case 0x10001820:s->comp=v&0xffffu;s->target_future=s->comp<=s->count;break;
 case 0x1000f000:s->intc_stat&=~v;break;
 default:return 0;
 }return 1;
}
int nocturneTimer3ClockHblank(NocturneTimer3Clock *s)
{
 if(!nocturneTimer3ClockValid(s))return 0;
 ++s->edges;if(!(s->mode&0x80u))return 1;
 ++s->count;
 if(s->count>0xffffu){
  if((s->mode&0x200u)&&!(s->mode&0x800u)){s->mode|=0x800u;s->intc_stat|=0x1000u;++s->overflow_requests;}
  s->count-=0x10000u;s->target_future=0;
 }
 if(!s->target_future&&s->count>=s->comp){
  if((s->mode&0x100u)&&!(s->mode&0x400u)){s->mode|=0x400u;s->intc_stat|=0x1000u;++s->compare_requests;}
  s->target_future=1;
 }return 1;
}
int nocturneTimer3ClockIntcEligible(const NocturneTimer3Clock *s,uint32_t status)
{return nocturneTimer3ClockValid(s)&&(s->intc_stat&s->intc_mask)!=0u&&(status&0x10401u)==0x10401u&&!(status&6u);}
