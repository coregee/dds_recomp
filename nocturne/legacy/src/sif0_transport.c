#include "sif0_transport.h"
#include <string.h>
/* Contract reconstruction from pinned PCSX2 Sif0.cpp/Sif.h, revision
 * fc4d0cdf609e704abd9c41915e898adba5264b29. Emulator reference semantics,
 * not recovered game instructions or exact custom-build source identity. */
static uint32_t smaller(uint32_t a,uint32_t b){return a<b?a:b;}
static int span(uint32_t a,uint32_t n,uint32_t size)
{return !(a&3u)&&n<=size&&a<=size-n;}
static void fifo_write(NocturneSif0Transport *s,const uint8_t *b,uint32_t n)
{uint32_t i;for(i=0;i<n;++i){memcpy(&s->fifo[s->write_pos],b+4u*i,4u);s->write_pos=(s->write_pos+1u)&127u;}s->size+=n;}
static void fifo_read(NocturneSif0Transport *s,uint8_t *b,uint32_t n)
{uint32_t i;for(i=0;i<n;++i){memcpy(b+4u*i,&s->fifo[s->read_pos],4u);s->read_pos=(s->read_pos+1u)&127u;}s->size-=n;}
static int event(NocturneSif0Transport *s,uint32_t kind,uint32_t a,uint32_t b)
{uint32_t n=s->event_count;if(n>=64u)return 0;s->events[n][0]=kind;s->events[n][1]=a;s->events[n][2]=b;s->event_count=n+1u;return 1;}
uint32_t nocturneSif0Drive(NocturneSif0Transport *s,uint8_t *iop,uint32_t ni,
 uint8_t *ee,uint32_t ne,uint32_t action,uint32_t limit)
{
 uint32_t iterations=0,work,n,a,i,tag[4],id;
 if(!s||!iop||!ee||s->size>128u||s->read_pos>127u||s->write_pos>127u||
    s->iop_busy>1u||s->ee_busy>1u||s->iop_end>1u||s->ee_end>1u||
    s->iop_padding>3u||s->ee_cycle_scale>16u||s->event_count>64u)return NOCTURNE_SIF0_DOMAIN;
 if(action==3u){
  if(!s->pending_iop)return NOCTURNE_SIF0_DOMAIN;
  if(!event(s,3u,2u,0u))return NOCTURNE_SIF0_DOMAIN;
  s->iop_chcr&=~0x01000000u;s->pending_iop=0u;++s->iop_irq;return NOCTURNE_SIF0_WAIT;
 }
 if(action==4u){
  if(!s->pending_ee)return NOCTURNE_SIF0_DOMAIN;
  if(!event(s,4u,5u,0u))return NOCTURNE_SIF0_DOMAIN;
  s->ee_chcr&=~0x100u;s->pending_ee=0u;++s->ee_irq;return NOCTURNE_SIF0_WAIT;
 }
 if(action==1u){s->iop_busy=1u;s->iop_end=0u;}
 else if(action==2u){s->sbus_control|=0x2000u;s->ee_busy=1u;s->ee_end=0u;++s->stall_clears;}
 else if(action!=0u)return NOCTURNE_SIF0_DOMAIN;
 s->ee_cycles=0u;s->iop_cycles=0u;
 do{
  if(iterations++>=limit)return NOCTURNE_SIF0_LIMIT;
  work=0u;
  if(!s->iop_counter&&s->iop_padding&&128u-s->size>=s->iop_padding){
   n=s->iop_padding;a=(s->write_pos-(8u-n))&127u;
   for(i=0;i<4u;++i)s->junk[i]=s->fifo[(a+i)&127u];
   /* writeJunk's split copy is retained even across a non-QW-aligned
    * FIFO wrap; this covers the reference ring's exact byte behavior. */
   a=smaller(128u-s->write_pos,n);
   memcpy(&s->fifo[s->write_pos],&s->junk[4u-a],4u*a);
   memcpy(&s->fifo[0],&s->junk[a],4u*(n-a));
   s->write_pos=(s->write_pos+n)&127u;s->size+=n;s->iop_padding=0u;
  }
  if(s->iop_busy&&(s->size<128u||(s->iop_end&&!s->iop_counter))){
   ++work;
   if(!s->iop_counter){
    if(s->iop_end){
     s->iop_tag[0]=0u;s->iop_end=0u;s->iop_busy=0u;
     if(!s->iop_cycles)s->iop_cycles=1u;
     if(s->iop_cycles>1000u)s->iop_cycles>>=1;
     s->pending_iop=1u;s->iop_delay=s->iop_cycles;
     if(!event(s,1u,0u,s->iop_delay))return NOCTURNE_SIF0_DOMAIN;
    }else{
     if(128u-s->size<4u)return NOCTURNE_SIF0_DOMAIN;
     a=s->iop_tadr;if(!span(a,24u,ni))return NOCTURNE_SIF0_MEMORY;
     memcpy(s->iop_tag,iop+a,16u);fifo_write(s,iop+a+8u,4u);s->iop_tadr+=16u;
     s->iop_madr=s->iop_tag[0]&0xffffffu;s->iop_counter=s->iop_tag[1]&0xfffffu;
     s->iop_padding=(4u-(s->iop_counter&3u))&3u;s->iop_end=(s->iop_tag[0]>>30)!=0u;
    }
   }else{
    n=smaller(s->iop_counter,128u-s->size);a=s->iop_madr;
    if(!span(a,n*4u,ni))return NOCTURNE_SIF0_MEMORY;
    fifo_write(s,iop+a,n);s->iop_madr+=n*4u;s->iop_cycles+=n;s->iop_counter-=n;
   }
  }
  if(s->ee_busy&&(s->size>=4u||(s->ee_end&&!s->ee_qwc))){
   ++work;
   if(!(s->ee_chcr&0x100u)){s->ee_end=0u;s->ee_busy=0u;}
   else{
    if(!s->ee_qwc){
     if(!(s->ee_chcr&0xcu)||s->ee_end){
      s->ee_end=0u;s->ee_busy=0u;if(!s->ee_cycles)s->ee_cycles=1u;
      ++s->stall_clears;s->pending_ee=1u;s->ee_delay=s->ee_cycles*s->ee_cycle_scale;
      if(!event(s,2u,5u,s->ee_delay))return NOCTURNE_SIF0_DOMAIN;
     }else if(s->size>=4u){
      fifo_read(s,(uint8_t *)tag,4u);s->ee_chcr=(s->ee_chcr&0xffffu)|(tag[0]&0xffff0000u);
      s->ee_qwc=tag[0]&65535u;s->ee_madr=tag[1];id=(tag[0]>>28)&7u;
      if((s->ee_chcr&0x80u)&&(tag[0]&0x80000000u))s->ee_end=1u;
      if(id==0u&&s->stall_source==1u)s->stall_address=s->ee_madr;
      else if(id==7u)s->ee_end=1u;
     }
    }
    if(s->ee_qwc&&s->size>=4u){
     n=smaller(s->ee_qwc,s->size/4u);a=s->ee_madr;
     if(!span(a,n*16u,ne))return NOCTURNE_SIF0_MEMORY;
     fifo_read(s,ee+a,n*4u);s->ee_madr+=n*16u;s->ee_cycles+=n;s->ee_qwc-=n;
     /* Reference tests (chcr.TAG >> 28), although TAG is only16 bits.
      * That expression is always0; preserve its actual emulator effect. */
     if(!s->ee_qwc&&s->stall_source==1u)s->stall_address=s->ee_madr;
    }
   }
  }
 }while(work);
 s->sbus_control&=~0x2020u;return NOCTURNE_SIF0_WAIT;
}
