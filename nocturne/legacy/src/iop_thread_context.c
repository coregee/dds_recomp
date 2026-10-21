#include "iop_thread_context.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopThreadContextResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopThreadContext *device)
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
  case UINT32_C(0x00005230): /* 27bdff68 */ D(29u,R(29u)+UINT32_C(0xffffff68)); break;
  case UINT32_C(0x00005234): /* afa60090 */ WRITE(R(29u)+UINT32_C(0x00000090),R(6u)); break;
  case UINT32_C(0x00005238): /* 8c080408 */ READ(R(0u)+UINT32_C(0x00000408));nl=8u;nv=value; break;
  case UINT32_C(0x0000523c): /* 8c090404 */ READ(R(0u)+UINT32_C(0x00000404));nl=9u;nv=value; break;
  case UINT32_C(0x00005240): /* afa80088 */ WRITE(R(29u)+UINT32_C(0x00000088),R(8u)); break;
  case UINT32_C(0x00005244): /* 25290004 */ D(9u,R(9u)+UINT32_C(0x00000004)); break;
  case UINT32_C(0x00005248): /* afa9008c */ WRITE(R(29u)+UINT32_C(0x0000008c),R(9u)); break;
  case UINT32_C(0x0000524c): /* afb00040 */ WRITE(R(29u)+UINT32_C(0x00000040),R(16u)); break;
  case UINT32_C(0x00005250): /* afb10044 */ WRITE(R(29u)+UINT32_C(0x00000044),R(17u)); break;
  case UINT32_C(0x00005254): /* afb20048 */ WRITE(R(29u)+UINT32_C(0x00000048),R(18u)); break;
  case UINT32_C(0x00005258): /* afb3004c */ WRITE(R(29u)+UINT32_C(0x0000004c),R(19u)); break;
  case UINT32_C(0x0000525c): /* afb40050 */ WRITE(R(29u)+UINT32_C(0x00000050),R(20u)); break;
  case UINT32_C(0x00005260): /* afb50054 */ WRITE(R(29u)+UINT32_C(0x00000054),R(21u)); break;
  case UINT32_C(0x00005264): /* afb60058 */ WRITE(R(29u)+UINT32_C(0x00000058),R(22u)); break;
  case UINT32_C(0x00005268): /* afb7005c */ WRITE(R(29u)+UINT32_C(0x0000005c),R(23u)); break;
  case UINT32_C(0x0000526c): /* afa40008 */ WRITE(R(29u)+UINT32_C(0x00000008),R(4u)); break;
  case UINT32_C(0x00005270): /* afa5000c */ WRITE(R(29u)+UINT32_C(0x0000000c),R(5u)); break;
  case UINT32_C(0x00005274): /* afbc0070 */ WRITE(R(29u)+UINT32_C(0x00000070),R(28u)); break;
  case UINT32_C(0x00005278): /* afbe0078 */ WRITE(R(29u)+UINT32_C(0x00000078),R(30u)); break;
  case UINT32_C(0x0000527c): /* afbf007c */ WRITE(R(29u)+UINT32_C(0x0000007c),R(31u)); break;
  case UINT32_C(0x00005280): /* 27a80098 */ D(8u,R(29u)+UINT32_C(0x00000098)); break;
  case UINT32_C(0x00005284): /* afa80074 */ WRITE(R(29u)+UINT32_C(0x00000074),R(8u)); break;
  case UINT32_C(0x00005288): /* 3c08f0ff */ D(8u,UINT32_C(0xf0ff0000)); break;
  case UINT32_C(0x0000528c): /* 3508000c */ D(8u,R(8u)|UINT32_C(0x0000000c)); break;
  case UINT32_C(0x00005290): /* afa80000 */ WRITE(R(29u)+UINT32_C(0x00000000),R(8u)); break;
  case UINT32_C(0x00005294): /* 03a02021 */ D(4u,R(29u)+R(0u)); break;
  case UINT32_C(0x00005298): /* 27bdfff0 */ D(29u,R(29u)+UINT32_C(0xfffffff0)); break;
  case UINT32_C(0x0000529c): /* 080013e7 */ B(UINT32_C(0x00004f9c)); break;
  case UINT32_C(0x000052a0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000be90): /* 27bdffd0 */ D(29u,R(29u)+UINT32_C(0xffffffd0)); break;
  case UINT32_C(0x0000be94): /* afb00020 */ WRITE(R(29u)+UINT32_C(0x00000020),R(16u)); break;
  case UINT32_C(0x0000be98): /* 3c100001 */ D(16u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000be9c): /* 261025d8 */ D(16u,R(16u)+UINT32_C(0x000025d8)); break;
  case UINT32_C(0x0000bea0): /* afbf0028 */ WRITE(R(29u)+UINT32_C(0x00000028),R(31u)); break;
  case UINT32_C(0x0000bea4): /* afb10024 */ WRITE(R(29u)+UINT32_C(0x00000024),R(17u)); break;
  case UINT32_C(0x0000bea8): /* 8e020000 */ READ(R(16u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0000beac): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000beb0): /* 30430003 */ D(3u,R(2u)&UINT32_C(0x00000003)); break;
  case UINT32_C(0x0000beb4): /* 10600020 */ B((R(3u)==R(0u))?UINT32_C(0x0000bf38):pc+8u); break;
  case UINT32_C(0x0000beb8): /* 00808821 */ D(17u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000bebc): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000bec0): /* 14620009 */ B((R(3u)!=R(2u))?UINT32_C(0x0000bee8):pc+8u); break;
  case UINT32_C(0x0000bec4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bec8): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000becc): /* 8c4225c0 */ READ(R(2u)+UINT32_C(0x000025c0));nl=2u;nv=value; break;
  case UINT32_C(0x0000bed0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bed4): /* 9445000a */ address=R(2u)+UINT32_C(0x0000000a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8);nl=5u; break;
  case UINT32_C(0x0000bed8): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bedc): /* 24842374 */ D(4u,R(4u)+UINT32_C(0x00002374)); break;
  case UINT32_C(0x0000bee0): /* 0c004805 */ B(UINT32_C(0x00012014));D(31u,pc+8u); break;
  case UINT32_C(0x0000bee4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bee8): /* 8e020000 */ READ(R(16u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0000beec): /* 24030002 */ D(3u,R(0u)+UINT32_C(0x00000002)); break;
  case UINT32_C(0x0000bef0): /* 30420003 */ D(2u,R(2u)&UINT32_C(0x00000003)); break;
  case UINT32_C(0x0000bef4): /* 14430010 */ B((R(2u)!=R(3u))?UINT32_C(0x0000bf38):pc+8u); break;
  case UINT32_C(0x0000bef8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000befc): /* 8e220090 */ READ(R(17u)+UINT32_C(0x00000090));nl=2u;nv=value; break;
  case UINT32_C(0x0000bf00): /* 8e03ffe8 */ READ(R(16u)+UINT32_C(0xffffffe8));nl=3u;nv=value; break;
  case UINT32_C(0x0000bf04): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bf08): /* 8c8425c0 */ READ(R(4u)+UINT32_C(0x000025c0));nl=4u;nv=value; break;
  case UINT32_C(0x0000bf0c): /* afa20010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(2u)); break;
  case UINT32_C(0x0000bf10): /* afa30014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(3u)); break;
  case UINT32_C(0x0000bf14): /* 9482000a */ address=R(4u)+UINT32_C(0x0000000a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8);nl=2u; break;
  case UINT32_C(0x0000bf18): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf1c): /* afa20018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(2u)); break;
  case UINT32_C(0x0000bf20): /* 8e260000 */ READ(R(17u)+UINT32_C(0x00000000));nl=6u;nv=value; break;
  case UINT32_C(0x0000bf24): /* 8e27008c */ READ(R(17u)+UINT32_C(0x0000008c));nl=7u;nv=value; break;
  case UINT32_C(0x0000bf28): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bf2c): /* 2484237c */ D(4u,R(4u)+UINT32_C(0x0000237c)); break;
  case UINT32_C(0x0000bf30): /* 0c004805 */ B(UINT32_C(0x00012014));D(31u,pc+8u); break;
  case UINT32_C(0x0000bf34): /* 02202821 */ D(5u,R(17u)+R(0u)); break;
  case UINT32_C(0x0000bf38): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bf3c): /* 8c4225c0 */ READ(R(2u)+UINT32_C(0x000025c0));nl=2u;nv=value; break;
  case UINT32_C(0x0000bf40): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf44): /* ac510010 */ WRITE(R(2u)+UINT32_C(0x00000010),R(17u)); break;
  case UINT32_C(0x0000bf48): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bf4c): /* 8c4225c0 */ READ(R(2u)+UINT32_C(0x000025c0));nl=2u;nv=value; break;
  case UINT32_C(0x0000bf50): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf54): /* 8c42003c */ READ(R(2u)+UINT32_C(0x0000003c));nl=2u;nv=value; break;
  case UINT32_C(0x0000bf58): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf5c): /* 0222102b */ D(2u,R(17u)<R(2u)); break;
  case UINT32_C(0x0000bf60): /* 10400005 */ B((R(2u)==R(0u))?UINT32_C(0x0000bf78):pc+8u); break;
  case UINT32_C(0x0000bf64): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf68): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bf6c): /* 8c8425c0 */ READ(R(4u)+UINT32_C(0x000025c0));nl=4u;nv=value; break;
  case UINT32_C(0x0000bf70): /* 0c002f7f */ B(UINT32_C(0x0000bdfc));D(31u,pc+8u); break;
  case UINT32_C(0x0000bf74): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf78): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bf7c): /* 248425c4 */ D(4u,R(4u)+UINT32_C(0x000025c4)); break;
  case UINT32_C(0x0000bf80): /* 8c820000 */ READ(R(4u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0000bf84): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf88): /* 14400009 */ B((R(2u)!=R(0u))?UINT32_C(0x0000bfb0):pc+8u); break;
  case UINT32_C(0x0000bf8c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bf90): /* 0c0046f7 */ B(UINT32_C(0x00011bdc));D(31u,pc+8u); break;
  case UINT32_C(0x0000bf94): /* 248404a8 */ D(4u,R(4u)+UINT32_C(0x000004a8)); break;
  case UINT32_C(0x0000bf98): /* 14400003 */ B((R(2u)!=R(0u))?UINT32_C(0x0000bfa8):pc+8u); break;
  case UINT32_C(0x0000bf9c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bfa0): /* 0c00324f */ B(UINT32_C(0x0000c93c));D(31u,pc+8u); break;
  case UINT32_C(0x0000bfa4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bfa8): /* 0c002f03 */ B(UINT32_C(0x0000bc0c));D(31u,pc+8u); break;
  case UINT32_C(0x0000bfac): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bfb0): /* 3c110001 */ D(17u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bfb4): /* 263125c0 */ D(17u,R(17u)+UINT32_C(0x000025c0)); break;
  case UINT32_C(0x0000bfb8): /* 8e230000 */ READ(R(17u)+UINT32_C(0x00000000));nl=3u;nv=value; break;
  case UINT32_C(0x0000bfbc): /* 8e220004 */ READ(R(17u)+UINT32_C(0x00000004));nl=2u;nv=value; break;
  case UINT32_C(0x0000bfc0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bfc4): /* 10620024 */ B((R(3u)==R(2u))?UINT32_C(0x0000c058):pc+8u); break;
  case UINT32_C(0x0000bfc8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bfcc): /* 8e220420 */ READ(R(17u)+UINT32_C(0x00000420));nl=2u;nv=value; break;
  case UINT32_C(0x0000bfd0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bfd4): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x0000bfd8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bfdc): /* 00002021 */ D(4u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000bfe0): /* 00408021 */ D(16u,R(2u)+R(0u)); break;
  case UINT32_C(0x0000bfe4): /* 3c030001 */ D(3u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bfe8): /* 8c6325c0 */ READ(R(3u)+UINT32_C(0x000025c0));nl=3u;nv=value; break;
  case UINT32_C(0x0000bfec): /* 8e25042c */ READ(R(17u)+UINT32_C(0x0000042c));nl=5u;nv=value; break;
  case UINT32_C(0x0000bff0): /* 8c660030 */ READ(R(3u)+UINT32_C(0x00000030));nl=6u;nv=value; break;
  case UINT32_C(0x0000bff4): /* 8c670034 */ READ(R(3u)+UINT32_C(0x00000034));nl=7u;nv=value; break;
  case UINT32_C(0x0000bff8): /* 0c0046e6 */ B(UINT32_C(0x00011b98));D(31u,pc+8u); break;
  case UINT32_C(0x0000bffc): /* 02052823 */ D(5u,R(16u)-R(5u)); break;
  case UINT32_C(0x0000c000): /* ae30042c */ WRITE(R(17u)+UINT32_C(0x0000042c),R(16u)); break;
  case UINT32_C(0x0000c004): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c008): /* 8c8425c0 */ READ(R(4u)+UINT32_C(0x000025c0));nl=4u;nv=value; break;
  case UINT32_C(0x0000c00c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c010): /* ac820034 */ WRITE(R(4u)+UINT32_C(0x00000034),R(2u)); break;
  case UINT32_C(0x0000c014): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c018): /* 8c8425c0 */ READ(R(4u)+UINT32_C(0x000025c0));nl=4u;nv=value; break;
  case UINT32_C(0x0000c01c): /* 00031003 */ D(2u,(uint32_t)((int32_t)R(3u)>>0u)); break;
  case UINT32_C(0x0000c020): /* 00031fc3 */ D(3u,(uint32_t)((int32_t)R(3u)>>31u)); break;
  case UINT32_C(0x0000c024): /* ac820030 */ WRITE(R(4u)+UINT32_C(0x00000030),R(2u)); break;
  case UINT32_C(0x0000c028): /* 8e2204bc */ READ(R(17u)+UINT32_C(0x000004bc));nl=2u;nv=value; break;
  case UINT32_C(0x0000c02c): /* 3c030001 */ D(3u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c030): /* 8c6325c0 */ READ(R(3u)+UINT32_C(0x000025c0));nl=3u;nv=value; break;
  case UINT32_C(0x0000c034): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000c038): /* ae2204bc */ WRITE(R(17u)+UINT32_C(0x000004bc),R(2u)); break;
  case UINT32_C(0x0000c03c): /* 8c630054 */ READ(R(3u)+UINT32_C(0x00000054));nl=3u;nv=value; break;
  case UINT32_C(0x0000c040): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c044): /* 8c620000 */ READ(R(3u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0000c048): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c04c): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000c050): /* 0800301a */ B(UINT32_C(0x0000c068)); break;
  case UINT32_C(0x0000c054): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0000c058): /* 8e2204c0 */ READ(R(17u)+UINT32_C(0x000004c0));nl=2u;nv=value; break;
  case UINT32_C(0x0000c05c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c060): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000c064): /* ae2204c0 */ WRITE(R(17u)+UINT32_C(0x000004c0),R(2u)); break;
  case UINT32_C(0x0000c068): /* 3c100001 */ D(16u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c06c): /* 261025c0 */ D(16u,R(16u)+UINT32_C(0x000025c0)); break;
  case UINT32_C(0x0000c070): /* 8e030018 */ READ(R(16u)+UINT32_C(0x00000018));nl=3u;nv=value; break;
  case UINT32_C(0x0000c074): /* 8e020004 */ READ(R(16u)+UINT32_C(0x00000004));nl=2u;nv=value; break;
  case UINT32_C(0x0000c078): /* 30630003 */ D(3u,R(3u)&UINT32_C(0x00000003)); break;
  case UINT32_C(0x0000c07c): /* 10600024 */ B((R(3u)==R(0u))?UINT32_C(0x0000c110):pc+8u); break;
  case UINT32_C(0x0000c080): /* ae020000 */ WRITE(R(16u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0000c084): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000c088): /* 14620009 */ B((R(3u)!=R(2u))?UINT32_C(0x0000c0b0):pc+8u); break;
  case UINT32_C(0x0000c08c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c090): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c094): /* 8c4225c4 */ READ(R(2u)+UINT32_C(0x000025c4));nl=2u;nv=value; break;
  case UINT32_C(0x0000c098): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c09c): /* 9445000a */ address=R(2u)+UINT32_C(0x0000000a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8);nl=5u; break;
  case UINT32_C(0x0000c0a0): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c0a4): /* 248423a8 */ D(4u,R(4u)+UINT32_C(0x000023a8)); break;
  case UINT32_C(0x0000c0a8): /* 0c004805 */ B(UINT32_C(0x00012014));D(31u,pc+8u); break;
  case UINT32_C(0x0000c0ac): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c0b0): /* 8e020018 */ READ(R(16u)+UINT32_C(0x00000018));nl=2u;nv=value; break;
  case UINT32_C(0x0000c0b4): /* 24030002 */ D(3u,R(0u)+UINT32_C(0x00000002)); break;
  case UINT32_C(0x0000c0b8): /* 30420003 */ D(2u,R(2u)&UINT32_C(0x00000003)); break;
  case UINT32_C(0x0000c0bc): /* 14430014 */ B((R(2u)!=R(3u))?UINT32_C(0x0000c110):pc+8u); break;
  case UINT32_C(0x0000c0c0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c0c4): /* 3c060001 */ D(6u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c0c8): /* 8cc625c4 */ READ(R(6u)+UINT32_C(0x000025c4));nl=6u;nv=value; break;
  case UINT32_C(0x0000c0cc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c0d0): /* 8cc30010 */ READ(R(6u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c0d4): /* 8e020004 */ READ(R(16u)+UINT32_C(0x00000004));nl=2u;nv=value; break;
  case UINT32_C(0x0000c0d8): /* 8c640090 */ READ(R(3u)+UINT32_C(0x00000090));nl=4u;nv=value; break;
  case UINT32_C(0x0000c0dc): /* 00c02821 */ D(5u,R(6u)+R(0u)); break;
  case UINT32_C(0x0000c0e0): /* afa20014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(2u)); break;
  case UINT32_C(0x0000c0e4): /* afa40010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(4u)); break;
  case UINT32_C(0x0000c0e8): /* 94a2000a */ address=R(5u)+UINT32_C(0x0000000a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8);nl=2u; break;
  case UINT32_C(0x0000c0ec): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c0f0): /* afa20018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(2u)); break;
  case UINT32_C(0x0000c0f4): /* 8cc50010 */ READ(R(6u)+UINT32_C(0x00000010));nl=5u;nv=value; break;
  case UINT32_C(0x0000c0f8): /* 8c660000 */ READ(R(3u)+UINT32_C(0x00000000));nl=6u;nv=value; break;
  case UINT32_C(0x0000c0fc): /* 8c67008c */ READ(R(3u)+UINT32_C(0x0000008c));nl=7u;nv=value; break;
  case UINT32_C(0x0000c100): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c104): /* 248423b0 */ D(4u,R(4u)+UINT32_C(0x000023b0)); break;
  case UINT32_C(0x0000c108): /* 0c004805 */ B(UINT32_C(0x00012014));D(31u,pc+8u); break;
  case UINT32_C(0x0000c10c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c110): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c114): /* 8c4225d8 */ READ(R(2u)+UINT32_C(0x000025d8));nl=2u;nv=value; break;
  case UINT32_C(0x0000c118): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c11c): /* 30420020 */ D(2u,R(2u)&UINT32_C(0x00000020)); break;
  case UINT32_C(0x0000c120): /* 1040000b */ B((R(2u)==R(0u))?UINT32_C(0x0000c150):pc+8u); break;
  case UINT32_C(0x0000c124): /* 3c04bf80 */ D(4u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0000c128): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c12c): /* 8c4225c4 */ READ(R(2u)+UINT32_C(0x000025c4));nl=2u;nv=value; break;
  case UINT32_C(0x0000c130): /* 34842070 */ D(4u,R(4u)|UINT32_C(0x00002070)); break;
  case UINT32_C(0x0000c134): /* 9443000a */ address=R(2u)+UINT32_C(0x0000000a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8);nl=3u; break;
  case UINT32_C(0x0000c138): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000c13c): /* 2463ffff */ D(3u,R(3u)+UINT32_C(0xffffffff)); break;
  case UINT32_C(0x0000c140): /* 30630007 */ D(3u,R(3u)&UINT32_C(0x00000007)); break;
  case UINT32_C(0x0000c144): /* 00621004 */ D(2u,R(2u)<<(R(3u)&31u)); break;
  case UINT32_C(0x0000c148): /* 00021027 */ D(2u,~(R(0u)|R(2u))); break;
  case UINT32_C(0x0000c14c): /* a0820000 */ address=R(4u)+UINT32_C(0x00000000);if(address==0xbf802070u){device->debug_port70=R(2u)&255u;++device->debug_port70_writes;}else{if(address>=size)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u);} break;
  case UINT32_C(0x0000c150): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c154): /* 8c4225c4 */ READ(R(2u)+UINT32_C(0x000025c4));nl=2u;nv=value; break;
  case UINT32_C(0x0000c158): /* 8fbf0028 */ READ(R(29u)+UINT32_C(0x00000028));nl=31u;nv=value; break;
  case UINT32_C(0x0000c15c): /* 8fb10024 */ READ(R(29u)+UINT32_C(0x00000024));nl=17u;nv=value; break;
  case UINT32_C(0x0000c160): /* 8fb00020 */ READ(R(29u)+UINT32_C(0x00000020));nl=16u;nv=value; break;
  case UINT32_C(0x0000c164): /* 8c420010 */ READ(R(2u)+UINT32_C(0x00000010));nl=2u;nv=value; break;
  case UINT32_C(0x0000c168): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000c16c): /* 27bd0030 */ D(29u,R(29u)+UINT32_C(0x00000030)); break;
  case UINT32_C(0x00011b98): /* 00a01021 */ D(2u,R(5u)+R(0u)); break;
  case UINT32_C(0x00011b9c): /* 00801821 */ D(3u,R(4u)+R(0u)); break;
  case UINT32_C(0x00011ba0): /* 00e04021 */ D(8u,R(7u)+R(0u)); break;
  case UINT32_C(0x00011ba4): /* 00c04821 */ D(9u,R(6u)+R(0u)); break;
  case UINT32_C(0x00011ba8): /* 00481021 */ D(2u,R(2u)+R(8u)); break;
  case UINT32_C(0x00011bac): /* 0048202b */ D(4u,R(2u)<R(8u)); break;
  case UINT32_C(0x00011bb0): /* 00691821 */ D(3u,R(3u)+R(9u)); break;
  case UINT32_C(0x00011bb4): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x00011bb8): /* 00641821 */ D(3u,R(3u)+R(4u)); break;
  case UINT32_C(0x00011bdc): /* 8c820000 */ READ(R(4u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x00011be0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00011be4): /* 00441026 */ D(2u,R(2u)^R(4u)); break;
  case UINT32_C(0x00011be8): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x00011bec): /* 2c420001 */ D(2u,R(2u)<UINT32_C(0x00000001)); break;
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

uint32_t nocturneIopThreadContextRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopThreadContext *d)
{
 uint64_t start;uint32_t r;if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x00005230u&&m->pc<0x000052a4u)||(m->pc>=0x0000be90u&&m->pc<0x0000c170u)||(m->pc>=0x00011b98u&&m->pc<0x00011bbcu)||(m->pc>=0x00011bdcu&&m->pc<0x00011bf0u))r=nocturneIopThreadContextResume(m,ram,n,1u,d);
  else r=nocturneIopIrqContextRoute(m,ram,n,1u,&d->irq);
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
