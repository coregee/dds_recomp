#include "iop_sifman_irq.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopSifmanIrqResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopSifmanDevice *device)
{
 uint64_t start;uint32_t pc,next,old_branch,old_target,old_load,old_value;
 uint32_t wr,wv,nl,nv,address,value;uint16_t value16;
 if(!m||!ram||!device||m->gpr[0]||m->load_register>31u||m->branch_pending>1u)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
#define R(r) (m->gpr[(r)])
#define D(r,v) do{wr=(r);wv=(v);}while(0)
#define B(v) do{if(old_branch)return NOCTURNE_IOP_DOMAIN;m->branch_pending=1u;m->branch_target=(v);}while(0)
#define EVENT(w,a,n,v) do{if(device->event_count>=16u)return NOCTURNE_IOP_DOMAIN;device->events[device->event_count][0]=(w);device->events[device->event_count][1]=(a);device->events[device->event_count][2]=(n);device->events[device->event_count][3]=(v);++device->event_count;}while(0)
#define PHYSICAL(a) ((a)>=0x80000000u&&(a)<0xc0000000u?(a)&0x1fffffffu:(a))
#define READ(a) do{address=(a);if(address==0xbf801528u){value=device->chcr;++device->chcr_reads;EVENT(0u,address,4u,value);}else if(address==0xbd000040u){value=device->sbus_control|0xf0000002u;++device->sbus_reads;EVENT(0u,address,4u,value);}else{address=PHYSICAL(address);if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(&value,ram+address,4u);}}while(0)
#define WRITE(a,v) do{address=(a);value=(v);if(address==0xbf801528u){device->chcr=value;device->pending_start=(value>>24)&1u;++device->chcr_writes;if(device->pending_start){device->start_tag=device->tadr;++device->start_requests;}EVENT(1u,address,4u,value);}else if(address==0xbf80152cu){device->tadr=value;++device->tadr_writes;EVENT(1u,address,4u,value);}else if(address==0xbd000040u){uint32_t mask=value&0xf0u;if(value&0xa0u)device->sbus_control=(device->sbus_control&~0xf000u)|0x2000u;if(device->sbus_control&mask)device->sbus_control&=~mask;else device->sbus_control|=mask;++device->sbus_writes;EVENT(1u,address,4u,value);}else{address=PHYSICAL(address);if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(ram+address,&value,4u);}}while(0)
#define READ16(a) do{address=PHYSICAL(a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;memcpy(&value16,ram+address,2u);}while(0)
#define WRITE16(a,v) do{address=(a);value16=(v);if(address==0xbf801524u){device->bcr=(device->bcr&0xffff0000u)|value16;++device->bcr_writes;EVENT(1u,address,2u,value16);}else{address=PHYSICAL(address);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;memcpy(ram+address,&value16,2u);}}while(0)
 for(;;){
  if(m->instructions-start>=limit)return NOCTURNE_IOP_LIMIT;
  pc=m->pc;next=pc+4u;old_branch=m->branch_pending;old_target=m->branch_target;
  old_load=m->load_register;old_value=m->load_value;wr=0u;wv=0u;nl=0u;nv=0u;
  m->branch_pending=0u;
  switch(pc){
  case UINT32_C(0x0001ae78): /* 27bdffd8 */ D(29u,R(29u)+UINT32_C(0xffffffd8)); break;
  case UINT32_C(0x0001ae7c): /* afb1001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(17u)); break;
  case UINT32_C(0x0001ae80): /* 00808821 */ D(17u,R(4u)+R(0u)); break;
  case UINT32_C(0x0001ae84): /* afbf0020 */ WRITE(R(29u)+UINT32_C(0x00000020),R(31u)); break;
  case UINT32_C(0x0001ae88): /* afb00018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(16u)); break;
  case UINT32_C(0x0001ae8c): /* 8e22061c */ READ(R(17u)+UINT32_C(0x0000061c));nl=2u;nv=value; break;
  case UINT32_C(0x0001ae90): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ae94): /* 10400004 */ B((R(2u)==R(0u))?UINT32_C(0x0001aea8):pc+8u); break;
  case UINT32_C(0x0001ae98): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ae9c): /* 8e240620 */ READ(R(17u)+UINT32_C(0x00000620));nl=4u;nv=value; break;
  case UINT32_C(0x0001aea0): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x0001aea4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001aea8): /* 8e23040c */ READ(R(17u)+UINT32_C(0x0000040c));nl=3u;nv=value; break;
  case UINT32_C(0x0001aeac): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001aeb0): /* 8c620100 */ READ(R(3u)+UINT32_C(0x00000100));nl=2u;nv=value; break;
  case UINT32_C(0x0001aeb4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001aeb8): /* 1840000f */ B(((int32_t)R(2u)<=0)?UINT32_C(0x0001aef8):pc+8u); break;
  case UINT32_C(0x0001aebc): /* 00008021 */ D(16u,R(0u)+R(0u)); break;
  case UINT32_C(0x0001aec0): /* 001010c0 */ D(2u,R(16u)<<3u); break;
  case UINT32_C(0x0001aec4): /* 00621021 */ D(2u,R(3u)+R(2u)); break;
  case UINT32_C(0x0001aec8): /* 8c440004 */ READ(R(2u)+UINT32_C(0x00000004));nl=4u;nv=value; break;
  case UINT32_C(0x0001aecc): /* 8c420000 */ READ(R(2u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001aed0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001aed4): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x0001aed8): /* 26100001 */ D(16u,R(16u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001aedc): /* 8e23040c */ READ(R(17u)+UINT32_C(0x0000040c));nl=3u;nv=value; break;
  case UINT32_C(0x0001aee0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001aee4): /* 8c620100 */ READ(R(3u)+UINT32_C(0x00000100));nl=2u;nv=value; break;
  case UINT32_C(0x0001aee8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001aeec): /* 0202102a */ D(2u,(int32_t)R(16u)<(int32_t)R(2u)); break;
  case UINT32_C(0x0001aef0): /* 1440fff4 */ B((R(2u)!=R(0u))?UINT32_C(0x0001aec4):pc+8u); break;
  case UINT32_C(0x0001aef4): /* 001010c0 */ D(2u,R(16u)<<3u); break;
  case UINT32_C(0x0001aef8): /* 3c06bf80 */ D(6u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001aefc): /* 8e22040c */ READ(R(17u)+UINT32_C(0x0000040c));nl=2u;nv=value; break;
  case UINT32_C(0x0001af00): /* 34c61528 */ D(6u,R(6u)|UINT32_C(0x00001528)); break;
  case UINT32_C(0x0001af04): /* ac400100 */ WRITE(R(2u)+UINT32_C(0x00000100),R(0u)); break;
  case UINT32_C(0x0001af08): /* 8cc20000 */ READ(R(6u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001af0c): /* 3c030100 */ D(3u,UINT32_C(0x01000000)); break;
  case UINT32_C(0x0001af10): /* 00431024 */ D(2u,R(2u)&R(3u)); break;
  case UINT32_C(0x0001af14): /* 14400030 */ B((R(2u)!=R(0u))?UINT32_C(0x0001afd8):pc+8u); break;
  case UINT32_C(0x0001af18): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001af1c): /* 8e220004 */ READ(R(17u)+UINT32_C(0x00000004));nl=2u;nv=value; break;
  case UINT32_C(0x0001af20): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001af24): /* 1840002c */ B(((int32_t)R(2u)<=0)?UINT32_C(0x0001afd8):pc+8u); break;
  case UINT32_C(0x0001af28): /* 3c03bf80 */ D(3u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001af2c): /* 3463152c */ D(3u,R(3u)|UINT32_C(0x0000152c)); break;
  case UINT32_C(0x0001af30): /* 3c04bf80 */ D(4u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001af34): /* 34841524 */ D(4u,R(4u)|UINT32_C(0x00001524)); break;
  case UINT32_C(0x0001af38): /* 3c05bd00 */ D(5u,UINT32_C(0xbd000000)); break;
  case UINT32_C(0x0001af3c): /* 8e220008 */ READ(R(17u)+UINT32_C(0x00000008));nl=2u;nv=value; break;
  case UINT32_C(0x0001af40): /* 34a50040 */ D(5u,R(5u)|UINT32_C(0x00000040)); break;
  case UINT32_C(0x0001af44): /* acc00000 */ WRITE(R(6u)+UINT32_C(0x00000000),R(0u)); break;
  case UINT32_C(0x0001af48): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001af4c): /* 24020020 */ D(2u,R(0u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001af50): /* a4820000 */ WRITE16(R(4u)+UINT32_C(0x00000000),(uint16_t)R(2u)); break;
  case UINT32_C(0x0001af54): /* 8ca20000 */ READ(R(5u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001af58): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001af5c): /* 30420020 */ D(2u,R(2u)&UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001af60): /* 14400002 */ B((R(2u)!=R(0u))?UINT32_C(0x0001af6c):pc+8u); break;
  case UINT32_C(0x0001af64): /* 24020020 */ D(2u,R(0u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001af68): /* aca20000 */ WRITE(R(5u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001af6c): /* 96220000 */ READ16(R(17u)+UINT32_C(0x00000000));nl=2u;nv=value16; break;
  case UINT32_C(0x0001af70): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001af74): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001af78): /* a6220000 */ WRITE16(R(17u)+UINT32_C(0x00000000),(uint16_t)R(2u)); break;
  case UINT32_C(0x0001af7c): /* 8e220008 */ READ(R(17u)+UINT32_C(0x00000008));nl=2u;nv=value; break;
  case UINT32_C(0x0001af80): /* 2623000c */ D(3u,R(17u)+UINT32_C(0x0000000c)); break;
  case UINT32_C(0x0001af84): /* 14430007 */ B((R(2u)!=R(3u))?UINT32_C(0x0001afa4):pc+8u); break;
  case UINT32_C(0x0001af88): /* ae200004 */ WRITE(R(17u)+UINT32_C(0x00000004),R(0u)); break;
  case UINT32_C(0x0001af8c): /* 2622020c */ D(2u,R(17u)+UINT32_C(0x0000020c)); break;
  case UINT32_C(0x0001af90): /* ae220008 */ WRITE(R(17u)+UINT32_C(0x00000008),R(2u)); break;
  case UINT32_C(0x0001af94): /* 26220518 */ D(2u,R(17u)+UINT32_C(0x00000518)); break;
  case UINT32_C(0x0001af98): /* ae220410 */ WRITE(R(17u)+UINT32_C(0x00000410),R(2u)); break;
  case UINT32_C(0x0001af9c): /* 08006bed */ B(UINT32_C(0x0001afb4)); break;
  case UINT32_C(0x0001afa0): /* 26220414 */ D(2u,R(17u)+UINT32_C(0x00000414)); break;
  case UINT32_C(0x0001afa4): /* 26220414 */ D(2u,R(17u)+UINT32_C(0x00000414)); break;
  case UINT32_C(0x0001afa8): /* ae220410 */ WRITE(R(17u)+UINT32_C(0x00000410),R(2u)); break;
  case UINT32_C(0x0001afac): /* 26220518 */ D(2u,R(17u)+UINT32_C(0x00000518)); break;
  case UINT32_C(0x0001afb0): /* ae230008 */ WRITE(R(17u)+UINT32_C(0x00000008),R(3u)); break;
  case UINT32_C(0x0001afb4): /* ae22040c */ WRITE(R(17u)+UINT32_C(0x0000040c),R(2u)); break;
  case UINT32_C(0x0001afb8): /* 3c03bf80 */ D(3u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001afbc): /* 34631528 */ D(3u,R(3u)|UINT32_C(0x00001528)); break;
  case UINT32_C(0x0001afc0): /* 3c020100 */ D(2u,UINT32_C(0x01000000)); break;
  case UINT32_C(0x0001afc4): /* 34420701 */ D(2u,R(2u)|UINT32_C(0x00000701)); break;
  case UINT32_C(0x0001afc8): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001afcc): /* 8c620000 */ READ(R(3u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001afd0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001afd4): /* afa20010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(2u)); break;
  case UINT32_C(0x0001afd8): /* 8fbf0020 */ READ(R(29u)+UINT32_C(0x00000020));nl=31u;nv=value; break;
  case UINT32_C(0x0001afdc): /* 8fb1001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=17u;nv=value; break;
  case UINT32_C(0x0001afe0): /* 8fb00018 */ READ(R(29u)+UINT32_C(0x00000018));nl=16u;nv=value; break;
  case UINT32_C(0x0001afe4): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001afe8): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001afec): /* 27bd0028 */ D(29u,R(29u)+UINT32_C(0x00000028)); break;
  case UINT32_C(0x0001bad8): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001badc): /* 00000000 */ /* nop */ break;
  default:m->branch_pending=old_branch;return NOCTURNE_IOP_TRANSFER;
  }
  if(old_load)m->gpr[old_load]=old_value;
  if(wr)m->gpr[wr]=wv;
  m->load_register=nl;m->load_value=nv;m->gpr[0]=0u;
  m->pc=old_branch?old_target:next;++m->instructions;
 }
#undef R
#undef D
#undef B
#undef READ
#undef WRITE
#undef READ16
#undef WRITE16
#undef PHYSICAL
#undef EVENT
}
