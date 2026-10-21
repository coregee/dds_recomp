#include "iop_sleep_wake.h"
#include "iop_rpc_reply_native.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopSleepWakeResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopThreadStart *device)
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
  case UINT32_C(0x0000d4ac): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000d4b0): /* 8c4225c0 */ READ(R(2u)+UINT32_C(0x000025c0));nl=2u;nv=value; break;
  case UINT32_C(0x0000d4b4): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x0000d4b8): /* afbe0018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(30u)); break;
  case UINT32_C(0x0000d4bc): /* 03a0f021 */ D(30u,R(29u)+R(0u)); break;
  case UINT32_C(0x0000d4c0): /* afbf001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(31u)); break;
  case UINT32_C(0x0000d4c4): /* 8c43003c */ READ(R(2u)+UINT32_C(0x0000003c));nl=3u;nv=value; break;
  case UINT32_C(0x0000d4c8): /* 27c20010 */ D(2u,R(30u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0000d4cc): /* 00431023 */ D(2u,R(2u)-R(3u)); break;
  case UINT32_C(0x0000d4d0): /* afc20010 */ WRITE(R(30u)+UINT32_C(0x00000010),R(2u)); break;
  case UINT32_C(0x0000d4d4): /* 284200a8 */ D(2u,(int32_t)R(2u)<168); break;
  case UINT32_C(0x0000d4d8): /* 1040000d */ B((R(2u)==R(0u))?UINT32_C(0x0000d510):pc+8u); break;
  case UINT32_C(0x0000d4dc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000d4e0): /* 0c004812 */ B(UINT32_C(0x00012048));D(31u,pc+8u); break;
  case UINT32_C(0x0000d4e4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000d4e8): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000d4ec): /* 24842420 */ D(4u,R(4u)+UINT32_C(0x00002420)); break;
  case UINT32_C(0x0000d4f0): /* 0c004805 */ B(UINT32_C(0x00012014));D(31u,pc+8u); break;
  case UINT32_C(0x0000d4f4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000d4f8): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x0000d4fc): /* 00002021 */ D(4u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000d500): /* 00802821 */ D(5u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000d504): /* 00803021 */ D(6u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000d508): /* 0c002e69 */ B(UINT32_C(0x0000b9a4));D(31u,pc+8u); break;
  case UINT32_C(0x0000d50c): /* 00803821 */ D(7u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000d510): /* 8fc20010 */ READ(R(30u)+UINT32_C(0x00000010));nl=2u;nv=value; break;
  case UINT32_C(0x0000d514): /* 03c0e821 */ D(29u,R(30u)+R(0u)); break;
  case UINT32_C(0x0000d518): /* 8fbf001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=31u;nv=value; break;
  case UINT32_C(0x0000d51c): /* 8fbe0018 */ READ(R(29u)+UINT32_C(0x00000018));nl=30u;nv=value; break;
  case UINT32_C(0x0000d520): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000d524): /* 27bd0020 */ D(29u,R(29u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0000dd14): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x0000dd18): /* afbf001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(31u)); break;
  case UINT32_C(0x0000dd1c): /* afb00018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(16u)); break;
  case UINT32_C(0x0000dd20): /* 03e08021 */ D(16u,R(31u)+R(0u)); break;
  case UINT32_C(0x0000dd24): /* 0c00481c */ B(UINT32_C(0x00012070));D(31u,pc+8u); break;
  case UINT32_C(0x0000dd28): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd2c): /* 1440002e */ B((R(2u)!=R(0u))?UINT32_C(0x0000dde8):pc+8u); break;
  case UINT32_C(0x0000dd30): /* 2402ff9c */ D(2u,R(0u)+UINT32_C(0xffffff9c)); break;
  case UINT32_C(0x0000dd34): /* 0c004818 */ B(UINT32_C(0x00012060));D(31u,pc+8u); break;
  case UINT32_C(0x0000dd38): /* 27a40010 */ D(4u,R(29u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0000dd3c): /* 2403ff9a */ D(3u,R(0u)+UINT32_C(0xffffff9a)); break;
  case UINT32_C(0x0000dd40): /* 1443000b */ B((R(2u)!=R(3u))?UINT32_C(0x0000dd70):pc+8u); break;
  case UINT32_C(0x0000dd44): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd48): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000dd4c): /* 8c4225d8 */ READ(R(2u)+UINT32_C(0x000025d8));nl=2u;nv=value; break;
  case UINT32_C(0x0000dd50): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd54): /* 30420008 */ D(2u,R(2u)&UINT32_C(0x00000008)); break;
  case UINT32_C(0x0000dd58): /* 10400005 */ B((R(2u)==R(0u))?UINT32_C(0x0000dd70):pc+8u); break;
  case UINT32_C(0x0000dd5c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd60): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000dd64): /* 24842458 */ D(4u,R(4u)+UINT32_C(0x00002458)); break;
  case UINT32_C(0x0000dd68): /* 0c004805 */ B(UINT32_C(0x00012014));D(31u,pc+8u); break;
  case UINT32_C(0x0000dd6c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd70): /* 0c00352b */ B(UINT32_C(0x0000d4ac));D(31u,pc+8u); break;
  case UINT32_C(0x0000dd74): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd78): /* 3c030001 */ D(3u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000dd7c): /* 246325c0 */ D(3u,R(3u)+UINT32_C(0x000025c0)); break;
  case UINT32_C(0x0000dd80): /* 8c650000 */ READ(R(3u)+UINT32_C(0x00000000));nl=5u;nv=value; break;
  case UINT32_C(0x0000dd84): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd88): /* 94a2001e */ address=R(5u)+UINT32_C(0x0000001e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=2u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000dd8c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dd90): /* 14400011 */ B((R(2u)!=R(0u))?UINT32_C(0x0000ddd8):pc+8u); break;
  case UINT32_C(0x0000dd94): /* 2442ffff */ D(2u,R(2u)+UINT32_C(0xffffffff)); break;
  case UINT32_C(0x0000dd98): /* 24640484 */ D(4u,R(3u)+UINT32_C(0x00000484)); break;
  case UINT32_C(0x0000dd9c): /* 24020004 */ D(2u,R(0u)+UINT32_C(0x00000004)); break;
  case UINT32_C(0x0000dda0): /* a0a2000c */ address=R(5u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u); break;
  case UINT32_C(0x0000dda4): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000dda8): /* a4a2001c */ address=R(5u)+UINT32_C(0x0000001c);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u);ram[address+1u]=(uint8_t)(R(2u)>>8); break;
  case UINT32_C(0x0000ddac): /* aca00020 */ WRITE(R(5u)+UINT32_C(0x00000020),R(0u)); break;
  case UINT32_C(0x0000ddb0): /* acb00050 */ WRITE(R(5u)+UINT32_C(0x00000050),R(16u)); break;
  case UINT32_C(0x0000ddb4): /* 0c00470a */ B(UINT32_C(0x00011c28));D(31u,pc+8u); break;
  case UINT32_C(0x0000ddb8): /* ac600004 */ WRITE(R(3u)+UINT32_C(0x00000004),R(0u)); break;
  case UINT32_C(0x0000ddbc): /* 00002021 */ D(4u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000ddc0): /* 00802821 */ D(5u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000ddc4): /* 8fa60010 */ READ(R(29u)+UINT32_C(0x00000010));nl=6u;nv=value; break;
  case UINT32_C(0x0000ddc8): /* 0c002e69 */ B(UINT32_C(0x0000b9a4));D(31u,pc+8u); break;
  case UINT32_C(0x0000ddcc): /* 24070001 */ D(7u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000ddd0): /* 0800377a */ B(UINT32_C(0x0000dde8)); break;
  case UINT32_C(0x0000ddd4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000ddd8): /* 8fa40010 */ READ(R(29u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x0000dddc): /* 0c00481a */ B(UINT32_C(0x00012068));D(31u,pc+8u); break;
  case UINT32_C(0x0000dde0): /* a4a2001e */ address=R(5u)+UINT32_C(0x0000001e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u);ram[address+1u]=(uint8_t)(R(2u)>>8); break;
  case UINT32_C(0x0000dde4): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000dde8): /* 8fbf001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=31u;nv=value; break;
  case UINT32_C(0x0000ddec): /* 8fb00018 */ READ(R(29u)+UINT32_C(0x00000018));nl=16u;nv=value; break;
  case UINT32_C(0x0000ddf0): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000ddf4): /* 27bd0020 */ D(29u,R(29u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0000ddf8): /* 27bdffd8 */ D(29u,R(29u)+UINT32_C(0xffffffd8)); break;
  case UINT32_C(0x0000ddfc): /* afb1001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(17u)); break;
  case UINT32_C(0x0000de00): /* 00808821 */ D(17u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000de04): /* afbf0020 */ WRITE(R(29u)+UINT32_C(0x00000020),R(31u)); break;
  case UINT32_C(0x0000de08): /* 0c00481c */ B(UINT32_C(0x00012070));D(31u,pc+8u); break;
  case UINT32_C(0x0000de0c): /* afb00018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(16u)); break;
  case UINT32_C(0x0000de10): /* 1440003c */ B((R(2u)!=R(0u))?UINT32_C(0x0000df04):pc+8u); break;
  case UINT32_C(0x0000de14): /* 2402ff9c */ D(2u,R(0u)+UINT32_C(0xffffff9c)); break;
  case UINT32_C(0x0000de18): /* 1220003a */ B((R(17u)==R(0u))?UINT32_C(0x0000df04):pc+8u); break;
  case UINT32_C(0x0000de1c): /* 2402fe6a */ D(2u,R(0u)+UINT32_C(0xfffffe6a)); break;
  case UINT32_C(0x0000de20): /* 0c004818 */ B(UINT32_C(0x00012060));D(31u,pc+8u); break;
  case UINT32_C(0x0000de24): /* 27a40010 */ D(4u,R(29u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0000de28): /* 001111c2 */ D(2u,R(17u)>>7u); break;
  case UINT32_C(0x0000de2c): /* 3c030001 */ D(3u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000de30): /* 8c6325c0 */ READ(R(3u)+UINT32_C(0x000025c0));nl=3u;nv=value; break;
  case UINT32_C(0x0000de34): /* 00028080 */ D(16u,R(2u)<<2u); break;
  case UINT32_C(0x0000de38): /* 16030006 */ B((R(16u)!=R(3u))?UINT32_C(0x0000de54):pc+8u); break;
  case UINT32_C(0x0000de3c): /* 24027f01 */ D(2u,R(0u)+UINT32_C(0x00007f01)); break;
  case UINT32_C(0x0000de40): /* 8fa40010 */ READ(R(29u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x0000de44): /* 0c00481a */ B(UINT32_C(0x00012068));D(31u,pc+8u); break;
  case UINT32_C(0x0000de48): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000de4c): /* 080037c1 */ B(UINT32_C(0x0000df04)); break;
  case UINT32_C(0x0000de50): /* 2402fe6a */ D(2u,R(0u)+UINT32_C(0xfffffe6a)); break;
  case UINT32_C(0x0000de54): /* 96030008 */ address=R(16u)+UINT32_C(0x00000008);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000de58): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000de5c): /* 14620006 */ B((R(3u)!=R(2u))?UINT32_C(0x0000de78):pc+8u); break;
  case UINT32_C(0x0000de60): /* 00111043 */ D(2u,(uint32_t)((int32_t)R(17u)>>1u)); break;
  case UINT32_C(0x0000de64): /* 9603000a */ address=R(16u)+UINT32_C(0x0000000a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000de68): /* 3042003f */ D(2u,R(2u)&UINT32_C(0x0000003f)); break;
  case UINT32_C(0x0000de6c): /* 3063003f */ D(3u,R(3u)&UINT32_C(0x0000003f)); break;
  case UINT32_C(0x0000de70): /* 10620006 */ B((R(3u)==R(2u))?UINT32_C(0x0000de8c):pc+8u); break;
  case UINT32_C(0x0000de74): /* 24020010 */ D(2u,R(0u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0000de78): /* 8fa40010 */ READ(R(29u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x0000de7c): /* 0c00481a */ B(UINT32_C(0x00012068));D(31u,pc+8u); break;
  case UINT32_C(0x0000de80): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000de84): /* 080037c1 */ B(UINT32_C(0x0000df04)); break;
  case UINT32_C(0x0000de88): /* 2402fe69 */ D(2u,R(0u)+UINT32_C(0xfffffe69)); break;
  case UINT32_C(0x0000de8c): /* 8203000c */ address=R(16u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)(int32_t)(int8_t)((uint32_t)ram[address]); break;
  case UINT32_C(0x0000de90): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000de94): /* 14620006 */ B((R(3u)!=R(2u))?UINT32_C(0x0000deb0):pc+8u); break;
  case UINT32_C(0x0000de98): /* 24020004 */ D(2u,R(0u)+UINT32_C(0x00000004)); break;
  case UINT32_C(0x0000de9c): /* 8fa40010 */ READ(R(29u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x0000dea0): /* 0c00481a */ B(UINT32_C(0x00012068));D(31u,pc+8u); break;
  case UINT32_C(0x0000dea4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dea8): /* 080037c1 */ B(UINT32_C(0x0000df04)); break;
  case UINT32_C(0x0000deac): /* 2402fe63 */ D(2u,R(0u)+UINT32_C(0xfffffe63)); break;
  case UINT32_C(0x0000deb0): /* 1462000e */ B((R(3u)!=R(2u))?UINT32_C(0x0000deec):pc+8u); break;
  case UINT32_C(0x0000deb4): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000deb8): /* 8603001c */ address=R(16u)+UINT32_C(0x0000001c);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)(int32_t)(int16_t)((uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8)); break;
  case UINT32_C(0x0000debc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dec0): /* 1462000a */ B((R(3u)!=R(2u))?UINT32_C(0x0000deec):pc+8u); break;
  case UINT32_C(0x0000dec4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dec8): /* 0c0046fc */ B(UINT32_C(0x00011bf0));D(31u,pc+8u); break;
  case UINT32_C(0x0000decc): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x0000ded0): /* 24020002 */ D(2u,R(0u)+UINT32_C(0x00000002)); break;
  case UINT32_C(0x0000ded4): /* a202000c */ address=R(16u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u); break;
  case UINT32_C(0x0000ded8): /* 8fa50010 */ READ(R(29u)+UINT32_C(0x00000010));nl=5u;nv=value; break;
  case UINT32_C(0x0000dedc): /* 0c002ec2 */ B(UINT32_C(0x0000bb08));D(31u,pc+8u); break;
  case UINT32_C(0x0000dee0): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x0000dee4): /* 080037c1 */ B(UINT32_C(0x0000df04)); break;
  case UINT32_C(0x0000dee8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000deec): /* 9602001e */ address=R(16u)+UINT32_C(0x0000001e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=2u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000def0): /* 8fa40010 */ READ(R(29u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x0000def4): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000def8): /* 0c00481a */ B(UINT32_C(0x00012068));D(31u,pc+8u); break;
  case UINT32_C(0x0000defc): /* a602001e */ address=R(16u)+UINT32_C(0x0000001e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u);ram[address+1u]=(uint8_t)(R(2u)>>8); break;
  case UINT32_C(0x0000df00): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000df04): /* 8fbf0020 */ READ(R(29u)+UINT32_C(0x00000020));nl=31u;nv=value; break;
  case UINT32_C(0x0000df08): /* 8fb1001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=17u;nv=value; break;
  case UINT32_C(0x0000df0c): /* 8fb00018 */ READ(R(29u)+UINT32_C(0x00000018));nl=16u;nv=value; break;
  case UINT32_C(0x0000df10): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000df14): /* 27bd0028 */ D(29u,R(29u)+UINT32_C(0x00000028)); break;
  case UINT32_C(0x0000df18): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x0000df1c): /* afb10014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(17u)); break;
  case UINT32_C(0x0000df20): /* 00808821 */ D(17u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000df24): /* afbf0018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(31u)); break;
  case UINT32_C(0x0000df28): /* 0c00481c */ B(UINT32_C(0x00012070));D(31u,pc+8u); break;
  case UINT32_C(0x0000df2c): /* afb00010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(16u)); break;
  case UINT32_C(0x0000df30): /* 1040002a */ B((R(2u)==R(0u))?UINT32_C(0x0000dfdc):pc+8u); break;
  case UINT32_C(0x0000df34): /* 2402ff9c */ D(2u,R(0u)+UINT32_C(0xffffff9c)); break;
  case UINT32_C(0x0000df38): /* 12200028 */ B((R(17u)==R(0u))?UINT32_C(0x0000dfdc):pc+8u); break;
  case UINT32_C(0x0000df3c): /* 2402fe6a */ D(2u,R(0u)+UINT32_C(0xfffffe6a)); break;
  case UINT32_C(0x0000df40): /* 001111c2 */ D(2u,R(17u)>>7u); break;
  case UINT32_C(0x0000df44): /* 00028080 */ D(16u,R(2u)<<2u); break;
  case UINT32_C(0x0000df48): /* 96030008 */ address=R(16u)+UINT32_C(0x00000008);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000df4c): /* 24027f01 */ D(2u,R(0u)+UINT32_C(0x00007f01)); break;
  case UINT32_C(0x0000df50): /* 14620022 */ B((R(3u)!=R(2u))?UINT32_C(0x0000dfdc):pc+8u); break;
  case UINT32_C(0x0000df54): /* 2402fe69 */ D(2u,R(0u)+UINT32_C(0xfffffe69)); break;
  case UINT32_C(0x0000df58): /* 9603000a */ address=R(16u)+UINT32_C(0x0000000a);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000df5c): /* 00111043 */ D(2u,(uint32_t)((int32_t)R(17u)>>1u)); break;
  case UINT32_C(0x0000df60): /* 3042003f */ D(2u,R(2u)&UINT32_C(0x0000003f)); break;
  case UINT32_C(0x0000df64): /* 3063003f */ D(3u,R(3u)&UINT32_C(0x0000003f)); break;
  case UINT32_C(0x0000df68): /* 1462001c */ B((R(3u)!=R(2u))?UINT32_C(0x0000dfdc):pc+8u); break;
  case UINT32_C(0x0000df6c): /* 2402fe69 */ D(2u,R(0u)+UINT32_C(0xfffffe69)); break;
  case UINT32_C(0x0000df70): /* 8203000c */ address=R(16u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)(int32_t)(int8_t)((uint32_t)ram[address]); break;
  case UINT32_C(0x0000df74): /* 24020010 */ D(2u,R(0u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0000df78): /* 14620003 */ B((R(3u)!=R(2u))?UINT32_C(0x0000df88):pc+8u); break;
  case UINT32_C(0x0000df7c): /* 24020004 */ D(2u,R(0u)+UINT32_C(0x00000004)); break;
  case UINT32_C(0x0000df80): /* 080037f7 */ B(UINT32_C(0x0000dfdc)); break;
  case UINT32_C(0x0000df84): /* 2402fe63 */ D(2u,R(0u)+UINT32_C(0xfffffe63)); break;
  case UINT32_C(0x0000df88): /* 1462000f */ B((R(3u)!=R(2u))?UINT32_C(0x0000dfc8):pc+8u); break;
  case UINT32_C(0x0000df8c): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000df90): /* 8603001c */ address=R(16u)+UINT32_C(0x0000001c);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)(int32_t)(int16_t)((uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8)); break;
  case UINT32_C(0x0000df94): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000df98): /* 1462000b */ B((R(3u)!=R(2u))?UINT32_C(0x0000dfc8):pc+8u); break;
  case UINT32_C(0x0000df9c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dfa0): /* 0c0046fc */ B(UINT32_C(0x00011bf0));D(31u,pc+8u); break;
  case UINT32_C(0x0000dfa4): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x0000dfa8): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x0000dfac): /* 24020002 */ D(2u,R(0u)+UINT32_C(0x00000002)); break;
  case UINT32_C(0x0000dfb0): /* 0c002e73 */ B(UINT32_C(0x0000b9cc));D(31u,pc+8u); break;
  case UINT32_C(0x0000dfb4): /* a082000c */ address=R(4u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u); break;
  case UINT32_C(0x0000dfb8): /* 3c010001 */ D(1u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000dfbc): /* ac2025c4 */ WRITE(R(1u)+UINT32_C(0x000025c4),R(0u)); break;
  case UINT32_C(0x0000dfc0): /* 080037f7 */ B(UINT32_C(0x0000dfdc)); break;
  case UINT32_C(0x0000dfc4): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000dfc8): /* 9602001e */ address=R(16u)+UINT32_C(0x0000001e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=2u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000dfcc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000dfd0): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000dfd4): /* a602001e */ address=R(16u)+UINT32_C(0x0000001e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u);ram[address+1u]=(uint8_t)(R(2u)>>8); break;
  case UINT32_C(0x0000dfd8): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000dfdc): /* 8fbf0018 */ READ(R(29u)+UINT32_C(0x00000018));nl=31u;nv=value; break;
  case UINT32_C(0x0000dfe0): /* 8fb10014 */ READ(R(29u)+UINT32_C(0x00000014));nl=17u;nv=value; break;
  case UINT32_C(0x0000dfe4): /* 8fb00010 */ READ(R(29u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x0000dfe8): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000dfec): /* 27bd0020 */ D(29u,R(29u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001de04): /* 08003745 */ B(UINT32_C(0x0000dd14)); break;
  case UINT32_C(0x0001de08): /* 24000018 */ D(0u,R(0u)+UINT32_C(0x00000018)); break;
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

uint32_t nocturneIopSleepWakeRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopThreadStart *d)
{
 uint64_t start,before;uint32_t r;if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;start=m->instructions;
 while(m->instructions-start<limit){
  before=m->instructions;
  if((m->pc>=0x0000d4acu&&m->pc<0x0000d528u)||(m->pc>=0x0000dd14u&&m->pc<0x0000ddf8u)||(m->pc>=0x0000ddf8u&&m->pc<0x0000df18u)||(m->pc>=0x0000df18u&&m->pc<0x0000dff0u)||(m->pc>=0x0001de04u&&m->pc<0x0001de0cu))r=nocturneIopSleepWakeResume(m,ram,n,1u,d);
  else r=nocturneIopThreadStartRoute(m,ram,n,1u,d);
  if(r==NOCTURNE_IOP_TRANSFER&&m->instructions==before)r=nocturneIopRpcReplyResume(m,ram,n,1u,&d->queue.thread.irq.dma.sifman.irq);
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
