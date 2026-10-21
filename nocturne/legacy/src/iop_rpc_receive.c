#include "iop_rpc_receive.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopRpcReceiveResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopThreadStart *device)
{
 uint64_t start;uint32_t pc,next,old_branch,old_target,old_load,old_value;
 uint32_t wr,wv,nl,nv,address,value;
 if(!m||!ram||!device||m->gpr[0]||m->load_register>31u||m->branch_pending>1u)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
#define R(r) (m->gpr[(r)])
#define D(r,v) do{wr=(r);wv=(v);}while(0)
#define B(v) do{if(old_branch)return NOCTURNE_IOP_DOMAIN;m->branch_pending=1u;m->branch_target=(v);}while(0)
#define READ(a) do{address=(a);if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(&value,ram+address,4u);}while(0)
#define WRITE(a,v) do{address=(a);value=(v);if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(ram+address,&value,4u);}while(0)
 for(;;){
  if(m->instructions-start>=limit)return NOCTURNE_IOP_LIMIT;
  pc=m->pc;next=pc+4u;old_branch=m->branch_pending;old_target=m->branch_target;
  old_load=m->load_register;old_value=m->load_value;wr=0u;wv=0u;nl=0u;nv=0u;
  m->branch_pending=0u;
  switch(pc){
  case UINT32_C(0x0001d444): /* 27bdffe8 */ D(29u,R(29u)+UINT32_C(0xffffffe8)); break;
  case UINT32_C(0x0001d448): /* afbf0010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(31u)); break;
  case UINT32_C(0x0001d44c): /* 8c830034 */ READ(R(4u)+UINT32_C(0x00000034));nl=3u;nv=value; break;
  case UINT32_C(0x0001d450): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d454): /* 8c650040 */ READ(R(3u)+UINT32_C(0x00000040));nl=5u;nv=value; break;
  case UINT32_C(0x0001d458): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d45c): /* 8ca2000c */ READ(R(5u)+UINT32_C(0x0000000c));nl=2u;nv=value; break;
  case UINT32_C(0x0001d460): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d464): /* 14400003 */ B((R(2u)!=R(0u))?UINT32_C(0x0001d474):pc+8u); break;
  case UINT32_C(0x0001d468): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d46c): /* 08007520 */ B(UINT32_C(0x0001d480)); break;
  case UINT32_C(0x0001d470): /* aca3000c */ WRITE(R(5u)+UINT32_C(0x0000000c),R(3u)); break;
  case UINT32_C(0x0001d474): /* 8ca20010 */ READ(R(5u)+UINT32_C(0x00000010));nl=2u;nv=value; break;
  case UINT32_C(0x0001d478): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d47c): /* ac43003c */ WRITE(R(2u)+UINT32_C(0x0000003c),R(3u)); break;
  case UINT32_C(0x0001d480): /* aca30010 */ WRITE(R(5u)+UINT32_C(0x00000010),R(3u)); break;
  case UINT32_C(0x0001d484): /* 8c820014 */ READ(R(4u)+UINT32_C(0x00000014));nl=2u;nv=value; break;
  case UINT32_C(0x0001d488): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d48c): /* ac620020 */ WRITE(R(3u)+UINT32_C(0x00000020),R(2u)); break;
  case UINT32_C(0x0001d490): /* 8c82001c */ READ(R(4u)+UINT32_C(0x0000001c));nl=2u;nv=value; break;
  case UINT32_C(0x0001d494): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d498): /* ac62001c */ WRITE(R(3u)+UINT32_C(0x0000001c),R(2u)); break;
  case UINT32_C(0x0001d49c): /* 8c820020 */ READ(R(4u)+UINT32_C(0x00000020));nl=2u;nv=value; break;
  case UINT32_C(0x0001d4a0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4a4): /* ac620024 */ WRITE(R(3u)+UINT32_C(0x00000024),R(2u)); break;
  case UINT32_C(0x0001d4a8): /* 8c820024 */ READ(R(4u)+UINT32_C(0x00000024));nl=2u;nv=value; break;
  case UINT32_C(0x0001d4ac): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4b0): /* ac62000c */ WRITE(R(3u)+UINT32_C(0x0000000c),R(2u)); break;
  case UINT32_C(0x0001d4b4): /* 8c820028 */ READ(R(4u)+UINT32_C(0x00000028));nl=2u;nv=value; break;
  case UINT32_C(0x0001d4b8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4bc): /* ac620028 */ WRITE(R(3u)+UINT32_C(0x00000028),R(2u)); break;
  case UINT32_C(0x0001d4c0): /* 8c82002c */ READ(R(4u)+UINT32_C(0x0000002c));nl=2u;nv=value; break;
  case UINT32_C(0x0001d4c4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4c8): /* ac62002c */ WRITE(R(3u)+UINT32_C(0x0000002c),R(2u)); break;
  case UINT32_C(0x0001d4cc): /* 8c820030 */ READ(R(4u)+UINT32_C(0x00000030));nl=2u;nv=value; break;
  case UINT32_C(0x0001d4d0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4d4): /* ac620030 */ WRITE(R(3u)+UINT32_C(0x00000030),R(2u)); break;
  case UINT32_C(0x0001d4d8): /* 8c820010 */ READ(R(4u)+UINT32_C(0x00000010));nl=2u;nv=value; break;
  case UINT32_C(0x0001d4dc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4e0): /* ac620034 */ WRITE(R(3u)+UINT32_C(0x00000034),R(2u)); break;
  case UINT32_C(0x0001d4e4): /* 8ca40000 */ READ(R(5u)+UINT32_C(0x00000000));nl=4u;nv=value; break;
  case UINT32_C(0x0001d4e8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4ec): /* 04800007 */ B(((int32_t)R(4u)<0)?UINT32_C(0x0001d50c):pc+8u); break;
  case UINT32_C(0x0001d4f0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4f4): /* 8ca20004 */ READ(R(5u)+UINT32_C(0x00000004));nl=2u;nv=value; break;
  case UINT32_C(0x0001d4f8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d4fc): /* 14400003 */ B((R(2u)!=R(0u))?UINT32_C(0x0001d50c):pc+8u); break;
  case UINT32_C(0x0001d500): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d504): /* 0c007783 */ B(UINT32_C(0x0001de0c));D(31u,pc+8u); break;
  case UINT32_C(0x0001d508): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d50c): /* 8fbf0010 */ READ(R(29u)+UINT32_C(0x00000010));nl=31u;nv=value; break;
  case UINT32_C(0x0001d510): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001d514): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001d518): /* 27bd0018 */ D(29u,R(29u)+UINT32_C(0x00000018)); break;
  case UINT32_C(0x0001de0c): /* 080037c6 */ B(UINT32_C(0x0000df18)); break;
  case UINT32_C(0x0001de10): /* 2400001a */ D(0u,R(0u)+UINT32_C(0x0000001a)); break;
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
}

uint32_t nocturneIopRpcReceiveRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopThreadStart *d)
{
 uint64_t start;uint32_t r;if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x0001d444u&&m->pc<0x0001d51cu)||(m->pc>=0x0001de0cu&&m->pc<0x0001de14u))r=nocturneIopRpcReceiveResume(m,ram,n,1u,d);
  else r=nocturneIopSleepWakeRoute(m,ram,n,1u,d);
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
