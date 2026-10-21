#include "iop_thread_start.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopThreadStartResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopThreadStart *device)
{
 uint64_t start;uint32_t pc,next,old_branch,old_target,old_load,old_value;
 uint32_t wr,wv,nl,nv,address,value;
 if(!m||!ram||!device||m->gpr[0]||m->load_register>31u||m->branch_pending>1u)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
#define R(r) (m->gpr[(r)])
#define D(r,v) do{wr=(r);wv=(v);}while(0)
#define B(v) do{if(old_branch)return NOCTURNE_IOP_DOMAIN;m->branch_pending=1u;m->branch_target=(v);}while(0)
#define IS_INTC(a) ((a)==0xbf801070u||(a)==0xbf801074u||(a)==0xbf801078u)
#define PHYSICAL(a) ((a)>=0x80000000u&&(a)<0xc0000000u?(a)&0x1fffffffu:(a))
#define READ(a) do{address=(a);if(IS_INTC(address)){if(!nocturneIopIrqRead(&device->queue.thread.irq,address,&value))return NOCTURNE_IOP_DOMAIN;}else{address=PHYSICAL(address);if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(&value,ram+address,4u);}}while(0)
#define WRITE(a,v) do{address=(a);value=(v);if(IS_INTC(address)){if(!nocturneIopIrqWrite(&device->queue.thread.irq,address,value))return NOCTURNE_IOP_DOMAIN;}else{address=PHYSICAL(address);if((address&3u)||size<4u||address>size-4u)return NOCTURNE_IOP_MEMORY;memcpy(ram+address,&value,4u);}}while(0)
 for(;;){
  if(m->instructions-start>=limit)return NOCTURNE_IOP_LIMIT;
  pc=m->pc;next=pc+4u;old_branch=m->branch_pending;old_target=m->branch_target;
  old_load=m->load_register;old_value=m->load_value;wr=0u;wv=0u;nl=0u;nv=0u;
  m->branch_pending=0u;
  switch(pc){
  case UINT32_C(0x0000b9a4): /* 3c030001 */ D(3u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000b9a8): /* 8c6325c0 */ READ(R(3u)+UINT32_C(0x000025c0));nl=3u;nv=value; break;
  case UINT32_C(0x0000b9ac): /* 14e00002 */ B((R(7u)!=R(0u))?UINT32_C(0x0000b9b8):pc+8u); break;
  case UINT32_C(0x0000b9b0): /* 24620060 */ D(2u,R(3u)+UINT32_C(0x00000060)); break;
  case UINT32_C(0x0000b9b4): /* 2462005c */ D(2u,R(3u)+UINT32_C(0x0000005c)); break;
  case UINT32_C(0x0000b9b8): /* ac620054 */ WRITE(R(3u)+UINT32_C(0x00000054),R(2u)); break;
  case UINT32_C(0x0000b9bc): /* 24020020 */ D(2u,R(0u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0000b9c0): /* 0000000c */ {NocturneIopIrqContext *q=&device->queue.thread.irq;q->cp0[13]=(q->cp0[13]&~127u)|32u;q->dma.cause=q->cp0[13];q->cp0[14]=old_branch?pc-4u:pc;if(old_branch)q->cp0[13]|=0x80000000u;next=(q->cp0[12]&0x400000u)?0xbfc00180u:0x80000080u;q->cp0[12]=(q->cp0[12]&~63u)|((q->cp0[12]&15u)<<2);old_branch=0u;m->branch_pending=0u;++device->syscalls;if(!nocturneIopCp0Event(q,3u,13u,q->cp0[13])||!nocturneIopCp0Event(q,3u,14u,q->cp0[14])||!nocturneIopCp0Event(q,3u,12u,q->cp0[12]))return NOCTURNE_IOP_DOMAIN;} break;
  case UINT32_C(0x0000b9c4): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000b9c8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000b9cc): /* 27bdffe8 */ D(29u,R(29u)+UINT32_C(0xffffffe8)); break;
  case UINT32_C(0x0000b9d0): /* 00802821 */ D(5u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000b9d4): /* afbf0010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(31u)); break;
  case UINT32_C(0x0000b9d8): /* 84a6000e */ address=R(5u)+UINT32_C(0x0000000e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=6u;nv=(uint32_t)(int32_t)(int16_t)((uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8)); break;
  case UINT32_C(0x0000b9dc): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000b9e0): /* 00062142 */ D(4u,R(6u)>>5u); break;
  case UINT32_C(0x0000b9e4): /* 00042080 */ D(4u,R(4u)<<2u); break;
  case UINT32_C(0x0000b9e8): /* 30c7001f */ D(7u,R(6u)&UINT32_C(0x0000001f)); break;
  case UINT32_C(0x0000b9ec): /* 00e21004 */ D(2u,R(2u)<<(R(7u)&31u)); break;
  case UINT32_C(0x0000b9f0): /* 3c030001 */ D(3u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000b9f4): /* 00641821 */ D(3u,R(3u)+R(4u)); break;
  case UINT32_C(0x0000b9f8): /* 8c6325c8 */ READ(R(3u)+UINT32_C(0x000025c8));nl=3u;nv=value; break;
  case UINT32_C(0x0000b9fc): /* 000630c0 */ D(6u,R(6u)<<3u); break;
  case UINT32_C(0x0000ba00): /* 00621825 */ D(3u,R(3u)|R(2u)); break;
  case UINT32_C(0x0000ba04): /* 3c010001 */ D(1u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000ba08): /* 00240821 */ D(1u,R(1u)+R(4u)); break;
  case UINT32_C(0x0000ba0c): /* ac2325c8 */ WRITE(R(1u)+UINT32_C(0x000025c8),R(3u)); break;
  case UINT32_C(0x0000ba10): /* 3c040001 */ D(4u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000ba14): /* 248425dc */ D(4u,R(4u)+UINT32_C(0x000025dc)); break;
  case UINT32_C(0x0000ba18): /* 0c00470a */ B(UINT32_C(0x00011c28));D(31u,pc+8u); break;
  case UINT32_C(0x0000ba1c): /* 00c42021 */ D(4u,R(6u)+R(4u)); break;
  case UINT32_C(0x0000ba20): /* 8fbf0010 */ READ(R(29u)+UINT32_C(0x00000010));nl=31u;nv=value; break;
  case UINT32_C(0x0000ba24): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000ba28): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000ba2c): /* 27bd0018 */ D(29u,R(29u)+UINT32_C(0x00000018)); break;
  case UINT32_C(0x0000bb08): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x0000bb0c): /* afb00010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(16u)); break;
  case UINT32_C(0x0000bb10): /* 00808021 */ D(16u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000bb14): /* afb10014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(17u)); break;
  case UINT32_C(0x0000bb18): /* 3c110001 */ D(17u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000bb1c): /* 263125c0 */ D(17u,R(17u)+UINT32_C(0x000025c0)); break;
  case UINT32_C(0x0000bb20): /* afbf001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(31u)); break;
  case UINT32_C(0x0000bb24): /* afb20018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(18u)); break;
  case UINT32_C(0x0000bb28): /* 8e240000 */ READ(R(17u)+UINT32_C(0x00000000));nl=4u;nv=value; break;
  case UINT32_C(0x0000bb2c): /* 8602000e */ address=R(16u)+UINT32_C(0x0000000e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=2u;nv=(uint32_t)(int32_t)(int16_t)((uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8)); break;
  case UINT32_C(0x0000bb30): /* 8483000e */ address=R(4u)+UINT32_C(0x0000000e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=3u;nv=(uint32_t)(int32_t)(int16_t)((uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8)); break;
  case UINT32_C(0x0000bb34): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000bb38): /* 0043102a */ D(2u,(int32_t)R(2u)<(int32_t)R(3u)); break;
  case UINT32_C(0x0000bb3c): /* 14400009 */ B((R(2u)!=R(0u))?UINT32_C(0x0000bb64):pc+8u); break;
  case UINT32_C(0x0000bb40): /* 00a09021 */ D(18u,R(5u)+R(0u)); break;
  case UINT32_C(0x0000bb44): /* 24020002 */ D(2u,R(0u)+UINT32_C(0x00000002)); break;
  case UINT32_C(0x0000bb48): /* a202000c */ address=R(16u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u); break;
  case UINT32_C(0x0000bb4c): /* 0c002e73 */ B(UINT32_C(0x0000b9cc));D(31u,pc+8u); break;
  case UINT32_C(0x0000bb50): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x0000bb54): /* 0c00481a */ B(UINT32_C(0x00012068));D(31u,pc+8u); break;
  case UINT32_C(0x0000bb58): /* 02402021 */ D(4u,R(18u)+R(0u)); break;
  case UINT32_C(0x0000bb5c): /* 08002ee4 */ B(UINT32_C(0x0000bb90)); break;
  case UINT32_C(0x0000bb60): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000bb64): /* 24020002 */ D(2u,R(0u)+UINT32_C(0x00000002)); break;
  case UINT32_C(0x0000bb68): /* 0c002e8c */ B(UINT32_C(0x0000ba30));D(31u,pc+8u); break;
  case UINT32_C(0x0000bb6c): /* a082000c */ address=R(4u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u); break;
  case UINT32_C(0x0000bb70): /* 00002021 */ D(4u,R(0u)+R(0u)); break;
  case UINT32_C(0x0000bb74): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000bb78): /* 00802821 */ D(5u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000bb7c): /* 02403021 */ D(6u,R(18u)+R(0u)); break;
  case UINT32_C(0x0000bb80): /* 00803821 */ D(7u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000bb84): /* a202000c */ address=R(16u)+UINT32_C(0x0000000c);if((address&0u)||size<1u||address>size-1u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u); break;
  case UINT32_C(0x0000bb88): /* 0c002e69 */ B(UINT32_C(0x0000b9a4));D(31u,pc+8u); break;
  case UINT32_C(0x0000bb8c): /* ae300004 */ WRITE(R(17u)+UINT32_C(0x00000004),R(16u)); break;
  case UINT32_C(0x0000bb90): /* 8fbf001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=31u;nv=value; break;
  case UINT32_C(0x0000bb94): /* 8fb20018 */ READ(R(29u)+UINT32_C(0x00000018));nl=18u;nv=value; break;
  case UINT32_C(0x0000bb98): /* 8fb10014 */ READ(R(29u)+UINT32_C(0x00000014));nl=17u;nv=value; break;
  case UINT32_C(0x0000bb9c): /* 8fb00010 */ READ(R(29u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x0000bba0): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000bba4): /* 27bd0020 */ D(29u,R(29u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0000c524): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x0000c528): /* afb00010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(16u)); break;
  case UINT32_C(0x0000c52c): /* 00808021 */ D(16u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000c530): /* afbf0018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(31u)); break;
  case UINT32_C(0x0000c534): /* afb10014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(17u)); break;
  case UINT32_C(0x0000c538): /* 9602002e */ address=R(16u)+UINT32_C(0x0000002e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;nl=2u;nv=(uint32_t)ram[address]|((uint32_t)ram[address+1u]<<8); break;
  case UINT32_C(0x0000c53c): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c540): /* a600001c */ address=R(16u)+UINT32_C(0x0000001c);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(0u);ram[address+1u]=(uint8_t)(R(0u)>>8); break;
  case UINT32_C(0x0000c544): /* ae000020 */ WRITE(R(16u)+UINT32_C(0x00000020),R(0u)); break;
  case UINT32_C(0x0000c548): /* a600001e */ address=R(16u)+UINT32_C(0x0000001e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(0u);ram[address+1u]=(uint8_t)(R(0u)>>8); break;
  case UINT32_C(0x0000c54c): /* a602000e */ address=R(16u)+UINT32_C(0x0000000e);if((address&1u)||size<2u||address>size-2u)return NOCTURNE_IOP_MEMORY;ram[address]=(uint8_t)R(2u);ram[address+1u]=(uint8_t)(R(2u)>>8); break;
  case UINT32_C(0x0000c550): /* 2402fffe */ D(2u,R(0u)+UINT32_C(0xfffffffe)); break;
  case UINT32_C(0x0000c554): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0000c558): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c55c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c560): /* 24620098 */ D(2u,R(3u)+UINT32_C(0x00000098)); break;
  case UINT32_C(0x0000c564): /* ac620074 */ WRITE(R(3u)+UINT32_C(0x00000074),R(2u)); break;
  case UINT32_C(0x0000c568): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c56c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c570): /* 8c620074 */ READ(R(3u)+UINT32_C(0x00000074));nl=2u;nv=value; break;
  case UINT32_C(0x0000c574): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000c578): /* ac620078 */ WRITE(R(3u)+UINT32_C(0x00000078),R(2u)); break;
  case UINT32_C(0x0000c57c): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c580): /* 3c020001 */ D(2u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x0000c584): /* 2442c814 */ D(2u,R(2u)+UINT32_C(0xffffc814)); break;
  case UINT32_C(0x0000c588): /* ac62007c */ WRITE(R(3u)+UINT32_C(0x0000007c),R(2u)); break;
  case UINT32_C(0x0000c58c): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c590): /* 8e020044 */ READ(R(16u)+UINT32_C(0x00000044));nl=2u;nv=value; break;
  case UINT32_C(0x0000c594): /* 00a08821 */ D(17u,R(5u)+R(0u)); break;
  case UINT32_C(0x0000c598): /* ac620070 */ WRITE(R(3u)+UINT32_C(0x00000070),R(2u)); break;
  case UINT32_C(0x0000c59c): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c5a0): /* 24020404 */ D(2u,R(0u)+UINT32_C(0x00000404)); break;
  case UINT32_C(0x0000c5a4): /* ac620088 */ WRITE(R(3u)+UINT32_C(0x00000088),R(2u)); break;
  case UINT32_C(0x0000c5a8): /* 8e040010 */ READ(R(16u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x0000c5ac): /* 8e020048 */ READ(R(16u)+UINT32_C(0x00000048));nl=2u;nv=value; break;
  case UINT32_C(0x0000c5b0): /* 8c830088 */ READ(R(4u)+UINT32_C(0x00000088));nl=3u;nv=value; break;
  case UINT32_C(0x0000c5b4): /* 30420008 */ D(2u,R(2u)&UINT32_C(0x00000008)); break;
  case UINT32_C(0x0000c5b8): /* 00621825 */ D(3u,R(3u)|R(2u)); break;
  case UINT32_C(0x0000c5bc): /* ac830088 */ WRITE(R(4u)+UINT32_C(0x00000088),R(3u)); break;
  case UINT32_C(0x0000c5c0): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c5c4): /* 8e020038 */ READ(R(16u)+UINT32_C(0x00000038));nl=2u;nv=value; break;
  case UINT32_C(0x0000c5c8): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x0000c5cc): /* ac62008c */ WRITE(R(3u)+UINT32_C(0x0000008c),R(2u)); break;
  case UINT32_C(0x0000c5d0): /* 8e030010 */ READ(R(16u)+UINT32_C(0x00000010));nl=3u;nv=value; break;
  case UINT32_C(0x0000c5d4): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0000c5d8): /* 0c0046fc */ B(UINT32_C(0x00011bf0));D(31u,pc+8u); break;
  case UINT32_C(0x0000c5dc): /* ac620090 */ WRITE(R(3u)+UINT32_C(0x00000090),R(2u)); break;
  case UINT32_C(0x0000c5e0): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x0000c5e4): /* 0c002ec2 */ B(UINT32_C(0x0000bb08));D(31u,pc+8u); break;
  case UINT32_C(0x0000c5e8): /* 02202821 */ D(5u,R(17u)+R(0u)); break;
  case UINT32_C(0x0000c5ec): /* 8fbf0018 */ READ(R(29u)+UINT32_C(0x00000018));nl=31u;nv=value; break;
  case UINT32_C(0x0000c5f0): /* 8fb10014 */ READ(R(29u)+UINT32_C(0x00000014));nl=17u;nv=value; break;
  case UINT32_C(0x0000c5f4): /* 8fb00010 */ READ(R(29u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x0000c5f8): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000c5fc): /* 27bd0020 */ D(29u,R(29u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x00005138): /* 305a0003 */ D(26u,R(2u)&UINT32_C(0x00000003)); break;
  case UINT32_C(0x0000513c): /* 13400005 */ B((R(26u)==R(0u))?UINT32_C(0x00005154):pc+8u); break;
  case UINT32_C(0x00005140): /* 3c1a0000 */ D(26u,UINT32_C(0x00000000)); break;
  case UINT32_C(0x00005144): /* 8f5a5130 */ READ(R(26u)+UINT32_C(0x00005130));nl=26u;nv=value; break;
  case UINT32_C(0x00005148): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000514c): /* 03400008 */ B(R(26u)); break;
  case UINT32_C(0x00005150): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00005154): /* 3c1a0000 */ D(26u,UINT32_C(0x00000000)); break;
  case UINT32_C(0x00005158): /* 275a53e0 */ D(26u,R(26u)+UINT32_C(0x000053e0)); break;
  case UINT32_C(0x0000515c): /* 0342d021 */ D(26u,R(26u)+R(2u)); break;
  case UINT32_C(0x00005160): /* 8f5a0000 */ READ(R(26u)+UINT32_C(0x00000000));nl=26u;nv=value; break;
  case UINT32_C(0x00005164): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00005168): /* 03400008 */ B(R(26u)); break;
  case UINT32_C(0x0000516c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00004178): /* 3c02bf80 */ D(2u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0000417c): /* 34421078 */ D(2u,R(2u)|UINT32_C(0x00001078)); break;
  case UINT32_C(0x00004180): /* 8c430000 */ READ(R(2u)+UINT32_C(0x00000000));nl=3u;nv=value; break;
  case UINT32_C(0x00004184): /* 10800002 */ B((R(4u)==R(0u))?UINT32_C(0x00004190):pc+8u); break;
  case UINT32_C(0x00004188): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000418c): /* ac830000 */ WRITE(R(4u)+UINT32_C(0x00000000),R(3u)); break;
  case UINT32_C(0x00004190): /* 14600002 */ B((R(3u)!=R(0u))?UINT32_C(0x0000419c):pc+8u); break;
  case UINT32_C(0x00004194): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x00004198): /* 2402ff9a */ D(2u,R(0u)+UINT32_C(0xffffff9a)); break;
  case UINT32_C(0x0000419c): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x000041a0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000041a4): /* 3c02bf80 */ D(2u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x000041a8): /* 34421078 */ D(2u,R(2u)|UINT32_C(0x00001078)); break;
  case UINT32_C(0x000041ac): /* ac440000 */ WRITE(R(2u)+UINT32_C(0x00000000),R(4u)); break;
  case UINT32_C(0x000041b0): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x000041b4): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x00012060): /* 0800105e */ B(UINT32_C(0x00004178)); break;
  case UINT32_C(0x00012064): /* 24000011 */ D(0u,R(0u)+UINT32_C(0x00000011)); break;
  case UINT32_C(0x00012068): /* 08001069 */ B(UINT32_C(0x000041a4)); break;
  case UINT32_C(0x0001206c): /* 24000012 */ D(0u,R(0u)+UINT32_C(0x00000012)); break;
  case UINT32_C(0x00012070): /* 080012e8 */ B(UINT32_C(0x00004ba0)); break;
  case UINT32_C(0x00012074): /* 24000017 */ D(0u,R(0u)+UINT32_C(0x00000017)); break;
  case UINT32_C(0x80000080): /* ac010400 */ WRITE(R(0u)+UINT32_C(0x00000400),R(1u)); break;
  case UINT32_C(0x80000084): /* ac1a0410 */ WRITE(R(0u)+UINT32_C(0x00000410),R(26u)); break;
  case UINT32_C(0x80000088): /* 401a7000 */ nl=26u;nv=device->queue.thread.irq.cp0[14u];if(!nocturneIopCp0Event(&device->queue.thread.irq,0u,14u,nv))return NOCTURNE_IOP_DOMAIN; break;
  case UINT32_C(0x8000008c): /* 40016000 */ nl=1u;nv=device->queue.thread.irq.cp0[12u];if(!nocturneIopCp0Event(&device->queue.thread.irq,0u,12u,nv))return NOCTURNE_IOP_DOMAIN; break;
  case UINT32_C(0x80000090): /* ac1a0404 */ WRITE(R(0u)+UINT32_C(0x00000404),R(26u)); break;
  case UINT32_C(0x80000094): /* ac010408 */ WRITE(R(0u)+UINT32_C(0x00000408),R(1u)); break;
  case UINT32_C(0x80000098): /* 401a6800 */ nl=26u;nv=device->queue.thread.irq.cp0[13u];if(!nocturneIopCp0Event(&device->queue.thread.irq,0u,13u,nv))return NOCTURNE_IOP_DOMAIN; break;
  case UINT32_C(0x8000009c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x800000a0): /* ac1a040c */ WRITE(R(0u)+UINT32_C(0x0000040c),R(26u)); break;
  case UINT32_C(0x800000a4): /* 335a003c */ D(26u,R(26u)&UINT32_C(0x0000003c)); break;
  case UINT32_C(0x800000a8): /* 8f5a0440 */ READ(R(26u)+UINT32_C(0x00000440));nl=26u;nv=value; break;
  case UINT32_C(0x800000ac): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x800000b0): /* 03400008 */ B(R(26u)); break;
  case UINT32_C(0x800000b4): /* 00000000 */ /* nop */ break;
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
#undef PHYSICAL
#undef IS_INTC
}

uint32_t nocturneIopThreadStartRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopThreadStart *d)
{
 uint64_t start;uint32_t r;if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x0000b9a4u&&m->pc<0x0000b9ccu)||(m->pc>=0x0000b9ccu&&m->pc<0x0000ba30u)||(m->pc>=0x0000bb08u&&m->pc<0x0000bba8u)||(m->pc>=0x0000c524u&&m->pc<0x0000c600u)||(m->pc>=0x00005138u&&m->pc<0x00005170u)||(m->pc>=0x00004178u&&m->pc<0x000041a4u)||(m->pc>=0x000041a4u&&m->pc<0x000041b8u)||(m->pc>=0x00012060u&&m->pc<0x00012068u)||(m->pc>=0x00012068u&&m->pc<0x00012070u)||(m->pc>=0x00012070u&&m->pc<0x00012078u)||(m->pc>=0x80000080u&&m->pc<0x800000b8u))r=nocturneIopThreadStartResume(m,ram,n,1u,d);
  else r=nocturneIopReadyQueueRoute(m,ram,n,1u,&d->queue);
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
