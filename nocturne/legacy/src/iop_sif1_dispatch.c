#include "iop_sif1_dispatch.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopSif1DispatchResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopSif1Dispatch *device)
{
 uint64_t start;uint32_t pc,next,old_branch,old_target,old_load,old_value;
 uint32_t wr,wv,nl,nv,address,value;
 if(!m||!ram||!device||m->gpr[0]||m->load_register>31u||m->branch_pending>1u)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
#define R(r) (m->gpr[(r)])
#define D(r,v) do{wr=(r);wv=(v);}while(0)
#define B(v) do{if(old_branch)return NOCTURNE_IOP_DOMAIN;m->branch_pending=1u;m->branch_target=(v);}while(0)
#define SIF1_EVENT(a,n,v) do{if(device->event_count>=8u)return NOCTURNE_IOP_DOMAIN;device->events[device->event_count][0]=1u;device->events[device->event_count][1]=(a);device->events[device->event_count][2]=(n);device->events[device->event_count][3]=(v);++device->event_count;}while(0)
#define BUS (device->thread.queue.thread.irq.dma.sifman)
#define READ(a) do{address=(a);if(address==0xbd000040u){value=BUS.sbus_control|0xf0000002u;++BUS.sbus_reads;if(BUS.event_count>=16u)return NOCTURNE_IOP_DOMAIN;BUS.events[BUS.event_count][0]=0u;BUS.events[BUS.event_count][1]=address;BUS.events[BUS.event_count][2]=4u;BUS.events[BUS.event_count][3]=value;++BUS.event_count;}else{if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(&value,ram+address,4u);}}while(0)
#define WRITE(a,v) do{address=(a);value=(v);if(address==0xbf801538u){device->chcr=value;device->pending_start=(value>>24)&1u;++device->chcr_writes;if(device->pending_start)++device->start_requests;SIF1_EVENT(address,4u,value);}else if(address==0xbd000040u){uint32_t mask=value&0xf0u;if(value&0xa0u)BUS.sbus_control=(BUS.sbus_control&~0xf000u)|0x2000u;if(BUS.sbus_control&mask)BUS.sbus_control&=~mask;else BUS.sbus_control|=mask;++BUS.sbus_writes;if(BUS.event_count>=16u)return NOCTURNE_IOP_DOMAIN;BUS.events[BUS.event_count][0]=1u;BUS.events[BUS.event_count][1]=address;BUS.events[BUS.event_count][2]=4u;BUS.events[BUS.event_count][3]=value;++BUS.event_count;}else{if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(ram+address,&value,4u);}}while(0)
 for(;;){
  if(m->instructions-start>=limit)return NOCTURNE_IOP_LIMIT;
  pc=m->pc;next=pc+4u;old_branch=m->branch_pending;old_target=m->branch_target;
  old_load=m->load_register;old_value=m->load_value;wr=0u;wv=0u;nl=0u;nv=0u;
  m->branch_pending=0u;
  switch(pc){
  case UINT32_C(0x0001c9dc): /* 27bdff78 */ D(29u,R(29u)+UINT32_C(0xffffff78)); break;
  case UINT32_C(0x0001c9e0): /* afb00080 */ WRITE(R(29u)+UINT32_C(0x00000080),R(16u)); break;
  case UINT32_C(0x0001c9e4): /* 00808021 */ D(16u,R(4u)+R(0u)); break;
  case UINT32_C(0x0001c9e8): /* afbf0084 */ WRITE(R(29u)+UINT32_C(0x00000084),R(31u)); break;
  case UINT32_C(0x0001c9ec): /* 8e020024 */ READ(R(16u)+UINT32_C(0x00000024));nl=2u;nv=value; break;
  case UINT32_C(0x0001c9f0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001c9f4): /* 10400004 */ B((R(2u)==R(0u))?UINT32_C(0x0001ca08):pc+8u); break;
  case UINT32_C(0x0001c9f8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001c9fc): /* 8e040028 */ READ(R(16u)+UINT32_C(0x00000028));nl=4u;nv=value; break;
  case UINT32_C(0x0001ca00): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x0001ca04): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ca08): /* 8e070000 */ READ(R(16u)+UINT32_C(0x00000000));nl=7u;nv=value; break;
  case UINT32_C(0x0001ca0c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ca10): /* 90e20000 */ address=R(7u)+UINT32_C(0x00000000);if(address>=size)return NOCTURNE_IOP_MEMORY;nl=2u;nv=ram[address]; break;
  case UINT32_C(0x0001ca14): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ca18): /* 304600ff */ D(6u,R(2u)&UINT32_C(0x000000ff)); break;
  case UINT32_C(0x0001ca1c): /* 14c00005 */ B((R(6u)!=R(0u))?UINT32_C(0x0001ca34):pc+8u); break;
  case UINT32_C(0x0001ca20): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ca24): /* 0c00776c */ B(UINT32_C(0x0001ddb0));D(31u,pc+8u); break;
  case UINT32_C(0x0001ca28): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ca2c): /* 080072bf */ B(UINT32_C(0x0001cafc)); break;
  case UINT32_C(0x0001ca30): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001ca34): /* a0e00000 */ address=R(7u)+UINT32_C(0x00000000);if(address>=size)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(0u); break;
  case UINT32_C(0x0001ca38): /* 24c20003 */ D(2u,R(6u)+UINT32_C(0x00000003)); break;
  case UINT32_C(0x0001ca3c): /* 04410002 */ B(((int32_t)R(2u)>=0)?UINT32_C(0x0001ca48):pc+8u); break;
  case UINT32_C(0x0001ca40): /* 00e02021 */ D(4u,R(7u)+R(0u)); break;
  case UINT32_C(0x0001ca44): /* 24c20006 */ D(2u,R(6u)+UINT32_C(0x00000006)); break;
  case UINT32_C(0x0001ca48): /* 00023083 */ D(6u,(uint32_t)((int32_t)R(2u)>>2u)); break;
  case UINT32_C(0x0001ca4c): /* 18c00009 */ B(((int32_t)R(6u)<=0)?UINT32_C(0x0001ca74):pc+8u); break;
  case UINT32_C(0x0001ca50): /* 00001821 */ D(3u,R(0u)+R(0u)); break;
  case UINT32_C(0x0001ca54): /* 27a50010 */ D(5u,R(29u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0001ca58): /* 8c820000 */ READ(R(4u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001ca5c): /* 24840004 */ D(4u,R(4u)+UINT32_C(0x00000004)); break;
  case UINT32_C(0x0001ca60): /* 24630001 */ D(3u,R(3u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001ca64): /* aca20000 */ WRITE(R(5u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001ca68): /* 0066102a */ D(2u,(int32_t)R(3u)<(int32_t)R(6u)); break;
  case UINT32_C(0x0001ca6c): /* 1440fffa */ B((R(2u)!=R(0u))?UINT32_C(0x0001ca58):pc+8u); break;
  case UINT32_C(0x0001ca70): /* 24a50004 */ D(5u,R(5u)+UINT32_C(0x00000004)); break;
  case UINT32_C(0x0001ca74): /* 0c00776c */ B(UINT32_C(0x0001ddb0));D(31u,pc+8u); break;
  case UINT32_C(0x0001ca78): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ca7c): /* 27a70010 */ D(7u,R(29u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0001ca80): /* 8ce20008 */ READ(R(7u)+UINT32_C(0x00000008));nl=2u;nv=value; break;
  case UINT32_C(0x0001ca84): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ca88): /* 0441000b */ B(((int32_t)R(2u)>=0)?UINT32_C(0x0001cab8):pc+8u); break;
  case UINT32_C(0x0001ca8c): /* 3c047fff */ D(4u,UINT32_C(0x7fff0000)); break;
  case UINT32_C(0x0001ca90): /* 3484ffff */ D(4u,R(4u)|UINT32_C(0x0000ffff)); break;
  case UINT32_C(0x0001ca94): /* 8ce30008 */ READ(R(7u)+UINT32_C(0x00000008));nl=3u;nv=value; break;
  case UINT32_C(0x0001ca98): /* 8e020010 */ READ(R(16u)+UINT32_C(0x00000010));nl=2u;nv=value; break;
  case UINT32_C(0x0001ca9c): /* 00643024 */ D(6u,R(3u)&R(4u)); break;
  case UINT32_C(0x0001caa0): /* 00c2102a */ D(2u,(int32_t)R(6u)<(int32_t)R(2u)); break;
  case UINT32_C(0x0001caa4): /* 10400014 */ B((R(2u)==R(0u))?UINT32_C(0x0001caf8):pc+8u); break;
  case UINT32_C(0x0001caa8): /* 000610c0 */ D(2u,R(6u)<<3u); break;
  case UINT32_C(0x0001caac): /* 8e03000c */ READ(R(16u)+UINT32_C(0x0000000c));nl=3u;nv=value; break;
  case UINT32_C(0x0001cab0): /* 080072b7 */ B(UINT32_C(0x0001cadc)); break;
  case UINT32_C(0x0001cab4): /* 00431021 */ D(2u,R(2u)+R(3u)); break;
  case UINT32_C(0x0001cab8): /* 8ce60008 */ READ(R(7u)+UINT32_C(0x00000008));nl=6u;nv=value; break;
  case UINT32_C(0x0001cabc): /* 8e020018 */ READ(R(16u)+UINT32_C(0x00000018));nl=2u;nv=value; break;
  case UINT32_C(0x0001cac0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001cac4): /* 00c2102a */ D(2u,(int32_t)R(6u)<(int32_t)R(2u)); break;
  case UINT32_C(0x0001cac8): /* 1040000b */ B((R(2u)==R(0u))?UINT32_C(0x0001caf8):pc+8u); break;
  case UINT32_C(0x0001cacc): /* 000610c0 */ D(2u,R(6u)<<3u); break;
  case UINT32_C(0x0001cad0): /* 8e030014 */ READ(R(16u)+UINT32_C(0x00000014));nl=3u;nv=value; break;
  case UINT32_C(0x0001cad4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001cad8): /* 00431021 */ D(2u,R(2u)+R(3u)); break;
  case UINT32_C(0x0001cadc): /* 8c430000 */ READ(R(2u)+UINT32_C(0x00000000));nl=3u;nv=value; break;
  case UINT32_C(0x0001cae0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001cae4): /* 10600004 */ B((R(3u)==R(0u))?UINT32_C(0x0001caf8):pc+8u); break;
  case UINT32_C(0x0001cae8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001caec): /* 8c450004 */ READ(R(2u)+UINT32_C(0x00000004));nl=5u;nv=value; break;
  case UINT32_C(0x0001caf0): /* 0060f809 */ B(R(3u));D(31u,pc+8u); break;
  case UINT32_C(0x0001caf4): /* 00e02021 */ D(4u,R(7u)+R(0u)); break;
  case UINT32_C(0x0001caf8): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001cafc): /* 8fbf0084 */ READ(R(29u)+UINT32_C(0x00000084));nl=31u;nv=value; break;
  case UINT32_C(0x0001cb00): /* 8fb00080 */ READ(R(29u)+UINT32_C(0x00000080));nl=16u;nv=value; break;
  case UINT32_C(0x0001cb04): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001cb08): /* 27bd0088 */ D(29u,R(29u)+UINT32_C(0x00000088)); break;
  case UINT32_C(0x0001adfc): /* 3c03bd00 */ D(3u,UINT32_C(0xbd000000)); break;
  case UINT32_C(0x0001ae00): /* 34630040 */ D(3u,R(3u)|UINT32_C(0x00000040)); break;
  case UINT32_C(0x0001ae04): /* 8c620000 */ READ(R(3u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001ae08): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ae0c): /* 30420040 */ D(2u,R(2u)&UINT32_C(0x00000040)); break;
  case UINT32_C(0x0001ae10): /* 14400004 */ B((R(2u)!=R(0u))?UINT32_C(0x0001ae24):pc+8u); break;
  case UINT32_C(0x0001ae14): /* 3c04bf80 */ D(4u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001ae18): /* 24020040 */ D(2u,R(0u)+UINT32_C(0x00000040)); break;
  case UINT32_C(0x0001ae1c): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001ae20): /* 3c04bf80 */ D(4u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001ae24): /* 34841538 */ D(4u,R(4u)|UINT32_C(0x00001538)); break;
  case UINT32_C(0x0001ae28): /* 3c05bf80 */ D(5u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001ae2c): /* 34a51534 */ D(5u,R(5u)|UINT32_C(0x00001534)); break;
  case UINT32_C(0x0001ae30): /* 3c034100 */ D(3u,UINT32_C(0x41000000)); break;
  case UINT32_C(0x0001ae34): /* 34630300 */ D(3u,R(3u)|UINT32_C(0x00000300)); break;
  case UINT32_C(0x0001ae38): /* 24020020 */ D(2u,R(0u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001ae3c): /* ac800000 */ WRITE(R(4u)+UINT32_C(0x00000000),R(0u)); break;
  case UINT32_C(0x0001ae40): /* a4a20000 */ address=R(5u)+UINT32_C(0x00000000);value=R(2u)&65535u;if(address==0xbf801534u){device->bcr=(device->bcr&0xffff0000u)|value;++device->bcr_writes;SIF1_EVENT(address,2u,value);}else{if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)value;ram[address+1u]=(uint8_t)(value>>8);} break;
  case UINT32_C(0x0001ae44): /* ac830000 */ WRITE(R(4u)+UINT32_C(0x00000000),R(3u)); break;
  case UINT32_C(0x0001ae48): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001ae4c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001ddb0): /* 08006b7f */ B(UINT32_C(0x0001adfc)); break;
  case UINT32_C(0x0001ddb4): /* 24000006 */ D(0u,R(0u)+UINT32_C(0x00000006)); break;
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
#undef BUS
#undef SIF1_EVENT
}

uint32_t nocturneIopSif1DispatchRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopSif1Dispatch *d)
{
 uint64_t start;uint32_t r;if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x0001c9dcu&&m->pc<0x0001cb0cu)||(m->pc>=0x0001adfcu&&m->pc<0x0001ae50u)||(m->pc>=0x0001ddb0u&&m->pc<0x0001ddb8u))r=nocturneIopSif1DispatchResume(m,ram,n,1u,d);
  else r=nocturneIopRpcReceiveRoute(m,ram,n,1u,&d->thread);
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
