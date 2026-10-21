#include "iop_timer_wake.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopTimerWakeResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopTimerWake *device)
{
 uint64_t start;uint32_t pc,next,old_branch,old_target,old_load,old_value;
 uint32_t wr,wv,nl,nv,address,value;
 if(!m||!ram||!device||m->gpr[0]||m->load_register>31u||m->branch_pending>1u)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
#define R(r) (m->gpr[(r)])
#define D(r,v) do{wr=(r);wv=(v);}while(0)
#define B(v) do{if(old_branch)return NOCTURNE_IOP_DOMAIN;m->branch_pending=1u;m->branch_target=(v);}while(0)
#define PHYSICAL(a) ((a)>=0x80000000u&&(a)<0xc0000000u?(a)&0x1fffffffu:(a))
#define GET(a,width) do{uint32_t bus_a=(a),bus_n=(width);if(bus_a>=0xbf800000u){if(!nocturneIopTimerWakeIo(device,0u,bus_a,bus_n,&value))return NOCTURNE_IOP_DOMAIN;}else{address=PHYSICAL(bus_a);if((address&(bus_n-1u))||size<bus_n||address>size-bus_n)return NOCTURNE_IOP_MEMORY;value=0u;memcpy(&value,ram+address,bus_n);}}while(0)
#define PUT(a,width,v) do{uint32_t bus_a=(a),bus_n=(width);value=(v);if(bus_a>=0xbf800000u){if(!nocturneIopTimerWakeIo(device,1u,bus_a,bus_n,&value))return NOCTURNE_IOP_DOMAIN;}else{address=PHYSICAL(bus_a);if((address&(bus_n-1u))||size<bus_n||address>size-bus_n)return NOCTURNE_IOP_MEMORY;memcpy(ram+address,&value,bus_n);}}while(0)
#define READ(a) GET(a,4u)
#define WRITE(a,v) PUT(a,4u,v)
 for(;;){
  if(m->instructions-start>=limit)return NOCTURNE_IOP_LIMIT;
  pc=m->pc;next=pc+4u;old_branch=m->branch_pending;old_target=m->branch_target;
  old_load=m->load_register;old_value=m->load_value;wr=0u;wv=0u;nl=0u;nv=0u;
  m->branch_pending=0u;
  switch(pc){
  case UINT32_C(0x000cd4b0): /* 27bdffe8 */ D(29u,R(29u)+UINT32_C(0xffffffe8)); break;
  case UINT32_C(0x000cd4b4): /* afb00010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(16u)); break;
  case UINT32_C(0x000cd4b8): /* 00808021 */ D(16u,R(4u)+R(0u)); break;
  case UINT32_C(0x000cd4bc): /* afbf0014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(31u)); break;
  case UINT32_C(0x000cd4c0): /* 8e040004 */ READ(R(16u)+UINT32_C(0x00000004));nl=4u;nv=value; break;
  case UINT32_C(0x000cd4c4): /* 0c0348b9 */ B(UINT32_C(0x000d22e4));D(31u,pc+8u); break;
  case UINT32_C(0x000cd4c8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000cd4cc): /* 10400007 */ B((R(2u)==R(0u))?UINT32_C(0x000cd4ec):pc+8u); break;
  case UINT32_C(0x000cd4d0): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x000cd4d4): /* 8e050004 */ READ(R(16u)+UINT32_C(0x00000004));nl=5u;nv=value; break;
  case UINT32_C(0x000cd4d8): /* 3c04000d */ D(4u,UINT32_C(0x000d0000)); break;
  case UINT32_C(0x000cd4dc): /* 2484247c */ D(4u,R(4u)+UINT32_C(0x0000247c)); break;
  case UINT32_C(0x000cd4e0): /* 0c034877 */ B(UINT32_C(0x000d21dc));D(31u,pc+8u); break;
  case UINT32_C(0x000cd4e4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000cd4e8): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000cd4ec): /* 8fbf0014 */ READ(R(29u)+UINT32_C(0x00000014));nl=31u;nv=value; break;
  case UINT32_C(0x000cd4f0): /* 8fb00010 */ READ(R(29u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x000cd4f4): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x000cd4f8): /* 27bd0018 */ D(29u,R(29u)+UINT32_C(0x00000018)); break;
  case UINT32_C(0x000cd358): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x000cd35c): /* afb10014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(17u)); break;
  case UINT32_C(0x000cd360): /* 00808821 */ D(17u,R(4u)+R(0u)); break;
  case UINT32_C(0x000cd364): /* afbf0018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(31u)); break;
  case UINT32_C(0x000cd368): /* afb00010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(16u)); break;
  case UINT32_C(0x000cd36c): /* 8e300000 */ READ(R(17u)+UINT32_C(0x00000000));nl=16u;nv=value; break;
  case UINT32_C(0x000cd370): /* 0c034893 */ B(UINT32_C(0x000d224c));D(31u,pc+8u); break;
  case UINT32_C(0x000cd374): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x000cd378): /* 0c034891 */ B(UINT32_C(0x000d2244));D(31u,pc+8u); break;
  case UINT32_C(0x000cd37c): /* 02002021 */ D(4u,R(16u)+R(0u)); break;
  case UINT32_C(0x000cd380): /* 8e220008 */ READ(R(17u)+UINT32_C(0x00000008));nl=2u;nv=value; break;
  case UINT32_C(0x000cd384): /* 8fbf0018 */ READ(R(29u)+UINT32_C(0x00000018));nl=31u;nv=value; break;
  case UINT32_C(0x000cd388): /* 8fb10014 */ READ(R(29u)+UINT32_C(0x00000014));nl=17u;nv=value; break;
  case UINT32_C(0x000cd38c): /* 8fb00010 */ READ(R(29u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x000cd390): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x000cd394): /* 27bd0020 */ D(29u,R(29u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x000089dc): /* 27bdffd8 */ D(29u,R(29u)+UINT32_C(0xffffffd8)); break;
  case UINT32_C(0x000089e0): /* 00042702 */ D(4u,R(4u)>>28u); break;
  case UINT32_C(0x000089e4): /* afb00018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(16u)); break;
  case UINT32_C(0x000089e8): /* 2490ffff */ D(16u,R(4u)+UINT32_C(0xffffffff)); break;
  case UINT32_C(0x000089ec): /* 2e020006 */ D(2u,R(16u)<UINT32_C(0x00000006)); break;
  case UINT32_C(0x000089f0): /* afbf0020 */ WRITE(R(29u)+UINT32_C(0x00000020),R(31u)); break;
  case UINT32_C(0x000089f4): /* 14400003 */ B((R(2u)!=R(0u))?UINT32_C(0x00008a04):pc+8u); break;
  case UINT32_C(0x000089f8): /* afb1001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(17u)); break;
  case UINT32_C(0x000089fc): /* 080022c0 */ B(UINT32_C(0x00008b00)); break;
  case UINT32_C(0x00008a00): /* 2402ff69 */ D(2u,R(0u)+UINT32_C(0xffffff69)); break;
  case UINT32_C(0x00008a04): /* 27a40010 */ D(4u,R(29u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x00008a08): /* 00101040 */ D(2u,R(16u)<<1u); break;
  case UINT32_C(0x00008a0c): /* 00501021 */ D(2u,R(2u)+R(16u)); break;
  case UINT32_C(0x00008a10): /* 00021080 */ D(2u,R(2u)<<2u); break;
  case UINT32_C(0x00008a14): /* 00501023 */ D(2u,R(2u)-R(16u)); break;
  case UINT32_C(0x00008a18): /* 00021080 */ D(2u,R(2u)<<2u); break;
  case UINT32_C(0x00008a1c): /* 3c030001 */ D(3u,UINT32_C(0x00010000)); break;
  case UINT32_C(0x00008a20): /* 24638d28 */ D(3u,R(3u)+UINT32_C(0xffff8d28)); break;
  case UINT32_C(0x00008a24): /* 0c00232e */ B(UINT32_C(0x00008cb8));D(31u,pc+8u); break;
  case UINT32_C(0x00008a28): /* 00438821 */ D(17u,R(2u)+R(3u)); break;
  case UINT32_C(0x00008a2c): /* 8e22000c */ READ(R(17u)+UINT32_C(0x0000000c));nl=2u;nv=value; break;
  case UINT32_C(0x00008a30): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a34): /* 10400003 */ B((R(2u)==R(0u))?UINT32_C(0x00008a44):pc+8u); break;
  case UINT32_C(0x00008a38): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a3c): /* 080022bc */ B(UINT32_C(0x00008af0)); break;
  case UINT32_C(0x00008a40): /* 2410ff66 */ D(16u,R(0u)+UINT32_C(0xffffff66)); break;
  case UINT32_C(0x00008a44): /* 8e220010 */ READ(R(17u)+UINT32_C(0x00000010));nl=2u;nv=value; break;
  case UINT32_C(0x00008a48): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a4c): /* 14400003 */ B((R(2u)!=R(0u))?UINT32_C(0x00008a5c):pc+8u); break;
  case UINT32_C(0x00008a50): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a54): /* 080022bc */ B(UINT32_C(0x00008af0)); break;
  case UINT32_C(0x00008a58): /* 2410ff65 */ D(16u,R(0u)+UINT32_C(0xffffff65)); break;
  case UINT32_C(0x00008a5c): /* 8e220000 */ READ(R(17u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x00008a60): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a64): /* a4400004 */ PUT(R(2u)+UINT32_C(0x00000004),2u,R(0u)); break;
  case UINT32_C(0x00008a68): /* 8e240000 */ READ(R(17u)+UINT32_C(0x00000000));nl=4u;nv=value; break;
  case UINT32_C(0x00008a6c): /* 96220014 */ address=R(17u)+UINT32_C(0x00000014);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x00008a70): /* 94830004 */ address=R(4u)+UINT32_C(0x00000004);GET(address,2u);nl=3u;nv=value; break;
  case UINT32_C(0x00008a74): /* 1040000b */ B((R(2u)==R(0u))?UINT32_C(0x00008aa4):pc+8u); break;
  case UINT32_C(0x00008a78): /* 2a020003 */ D(2u,(int32_t)R(16u)<3); break;
  case UINT32_C(0x00008a7c): /* 10400006 */ B((R(2u)==R(0u))?UINT32_C(0x00008a98):pc+8u); break;
  case UINT32_C(0x00008a80): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a84): /* 96220018 */ address=R(17u)+UINT32_C(0x00000018);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x00008a88): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a8c): /* a4820008 */ PUT(R(4u)+UINT32_C(0x00000008),2u,R(2u)); break;
  case UINT32_C(0x00008a90): /* 080022a9 */ B(UINT32_C(0x00008aa4)); break;
  case UINT32_C(0x00008a94): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008a98): /* 8e220018 */ READ(R(17u)+UINT32_C(0x00000018));nl=2u;nv=value; break;
  case UINT32_C(0x00008a9c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008aa0): /* ac820008 */ WRITE(R(4u)+UINT32_C(0x00000008),R(2u)); break;
  case UINT32_C(0x00008aa4): /* 8fa40010 */ READ(R(29u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x00008aa8): /* 96230014 */ address=R(17u)+UINT32_C(0x00000014);GET(address,2u);nl=3u;nv=value; break;
  case UINT32_C(0x00008aac): /* 8e300010 */ READ(R(17u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x00008ab0): /* 96220016 */ address=R(17u)+UINT32_C(0x00000016);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x00008ab4): /* 02038025 */ D(16u,R(16u)|R(3u)); break;
  case UINT32_C(0x00008ab8): /* 02028025 */ D(16u,R(16u)|R(2u)); break;
  case UINT32_C(0x00008abc): /* 0c002330 */ B(UINT32_C(0x00008cc0));D(31u,pc+8u); break;
  case UINT32_C(0x00008ac0): /* ae30000c */ WRITE(R(17u)+UINT32_C(0x0000000c),R(16u)); break;
  case UINT32_C(0x00008ac4): /* 8e220000 */ READ(R(17u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x00008ac8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008acc): /* a4500004 */ PUT(R(2u)+UINT32_C(0x00000004),2u,R(16u)); break;
  case UINT32_C(0x00008ad0): /* 32100030 */ D(16u,R(16u)&UINT32_C(0x00000030)); break;
  case UINT32_C(0x00008ad4): /* 1200000a */ B((R(16u)==R(0u))?UINT32_C(0x00008b00):pc+8u); break;
  case UINT32_C(0x00008ad8): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x00008adc): /* 82240008 */ address=R(17u)+UINT32_C(0x00000008);GET(address,1u);nl=4u;nv=(uint32_t)(int32_t)(int8_t)value; break;
  case UINT32_C(0x00008ae0): /* 0c00232a */ B(UINT32_C(0x00008ca8));D(31u,pc+8u); break;
  case UINT32_C(0x00008ae4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008ae8): /* 080022c0 */ B(UINT32_C(0x00008b00)); break;
  case UINT32_C(0x00008aec): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x00008af0): /* 8fa40010 */ READ(R(29u)+UINT32_C(0x00000010));nl=4u;nv=value; break;
  case UINT32_C(0x00008af4): /* 0c002330 */ B(UINT32_C(0x00008cc0));D(31u,pc+8u); break;
  case UINT32_C(0x00008af8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008afc): /* 02001021 */ D(2u,R(16u)+R(0u)); break;
  case UINT32_C(0x00008b00): /* 8fbf0020 */ READ(R(29u)+UINT32_C(0x00000020));nl=31u;nv=value; break;
  case UINT32_C(0x00008b04): /* 8fb1001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=17u;nv=value; break;
  case UINT32_C(0x00008b08): /* 8fb00018 */ READ(R(29u)+UINT32_C(0x00000018));nl=16u;nv=value; break;
  case UINT32_C(0x00008b0c): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x00008b10): /* 27bd0028 */ D(29u,R(29u)+UINT32_C(0x00000028)); break;
  case UINT32_C(0x000086a8): /* 27bdffe0 */ D(29u,R(29u)+UINT32_C(0xffffffe0)); break;
  case UINT32_C(0x000086ac): /* afb00010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(16u)); break;
  case UINT32_C(0x000086b0): /* 00808021 */ D(16u,R(4u)+R(0u)); break;
  case UINT32_C(0x000086b4): /* afbf001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(31u)); break;
  case UINT32_C(0x000086b8): /* afb20018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(18u)); break;
  case UINT32_C(0x000086bc): /* afb10014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(17u)); break;
  case UINT32_C(0x000086c0): /* 8e020000 */ READ(R(16u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x000086c4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000086c8): /* 94420004 */ address=R(2u)+UINT32_C(0x00000004);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000086cc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000086d0): /* 3052ffff */ D(18u,R(2u)&UINT32_C(0x0000ffff)); break;
  case UINT32_C(0x000086d4): /* 32421000 */ D(2u,R(18u)&UINT32_C(0x00001000)); break;
  case UINT32_C(0x000086d8): /* 1040000c */ B((R(2u)==R(0u))?UINT32_C(0x0000870c):pc+8u); break;
  case UINT32_C(0x000086dc): /* 00008821 */ D(17u,R(0u)+R(0u)); break;
  case UINT32_C(0x000086e0): /* 96020016 */ address=R(16u)+UINT32_C(0x00000016);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000086e4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000086e8): /* 10400009 */ B((R(2u)==R(0u))?UINT32_C(0x00008710):pc+8u); break;
  case UINT32_C(0x000086ec): /* 32420800 */ D(2u,R(18u)&UINT32_C(0x00000800)); break;
  case UINT32_C(0x000086f0): /* 8e040028 */ READ(R(16u)+UINT32_C(0x00000028));nl=4u;nv=value; break;
  case UINT32_C(0x000086f4): /* 8e020024 */ READ(R(16u)+UINT32_C(0x00000024));nl=2u;nv=value; break;
  case UINT32_C(0x000086f8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000086fc): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x00008700): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008704): /* 2c420001 */ D(2u,R(2u)<UINT32_C(0x00000001)); break;
  case UINT32_C(0x00008708): /* 00028940 */ D(17u,R(2u)<<5u); break;
  case UINT32_C(0x0000870c): /* 32420800 */ D(2u,R(18u)&UINT32_C(0x00000800)); break;
  case UINT32_C(0x00008710): /* 1040001b */ B((R(2u)==R(0u))?UINT32_C(0x00008780):pc+8u); break;
  case UINT32_C(0x00008714): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008718): /* 96020014 */ address=R(16u)+UINT32_C(0x00000014);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x0000871c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008720): /* 10400017 */ B((R(2u)==R(0u))?UINT32_C(0x00008780):pc+8u); break;
  case UINT32_C(0x00008724): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008728): /* 8e040020 */ READ(R(16u)+UINT32_C(0x00000020));nl=4u;nv=value; break;
  case UINT32_C(0x0000872c): /* 8e02001c */ READ(R(16u)+UINT32_C(0x0000001c));nl=2u;nv=value; break;
  case UINT32_C(0x00008730): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008734): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x00008738): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000873c): /* 00402021 */ D(4u,R(2u)+R(0u)); break;
  case UINT32_C(0x00008740): /* 14800003 */ B((R(4u)!=R(0u))?UINT32_C(0x00008750):pc+8u); break;
  case UINT32_C(0x00008744): /* 24020010 */ D(2u,R(0u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x00008748): /* 080021e0 */ B(UINT32_C(0x00008780)); break;
  case UINT32_C(0x0000874c): /* 36310010 */ D(17u,R(17u)|UINT32_C(0x00000010)); break;
  case UINT32_C(0x00008750): /* 82030005 */ address=R(16u)+UINT32_C(0x00000005);GET(address,1u);nl=3u;nv=(uint32_t)(int32_t)(int8_t)value; break;
  case UINT32_C(0x00008754): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008758): /* 14620006 */ B((R(3u)!=R(2u))?UINT32_C(0x00008774):pc+8u); break;
  case UINT32_C(0x0000875c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008760): /* 8e020000 */ READ(R(16u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x00008764): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008768): /* a4440008 */ PUT(R(2u)+UINT32_C(0x00000008),2u,R(4u)); break;
  case UINT32_C(0x0000876c): /* 080021e0 */ B(UINT32_C(0x00008780)); break;
  case UINT32_C(0x00008770): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008774): /* 8e020000 */ READ(R(16u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x00008778): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0000877c): /* ac440008 */ WRITE(R(2u)+UINT32_C(0x00000008),R(4u)); break;
  case UINT32_C(0x00008780): /* 16200005 */ B((R(17u)!=R(0u))?UINT32_C(0x00008798):pc+8u); break;
  case UINT32_C(0x00008784): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008788): /* 8e02000c */ READ(R(16u)+UINT32_C(0x0000000c));nl=2u;nv=value; break;
  case UINT32_C(0x0000878c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x00008790): /* 14400005 */ B((R(2u)!=R(0u))?UINT32_C(0x000087a8):pc+8u); break;
  case UINT32_C(0x00008794): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x00008798): /* 8e030000 */ READ(R(16u)+UINT32_C(0x00000000));nl=3u;nv=value; break;
  case UINT32_C(0x0000879c): /* ae00000c */ WRITE(R(16u)+UINT32_C(0x0000000c),R(0u)); break;
  case UINT32_C(0x000087a0): /* a4600004 */ PUT(R(3u)+UINT32_C(0x00000004),2u,R(0u)); break;
  case UINT32_C(0x000087a4): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x000087a8): /* 8fbf001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=31u;nv=value; break;
  case UINT32_C(0x000087ac): /* 8fb20018 */ READ(R(29u)+UINT32_C(0x00000018));nl=18u;nv=value; break;
  case UINT32_C(0x000087b0): /* 8fb10014 */ READ(R(29u)+UINT32_C(0x00000014));nl=17u;nv=value; break;
  case UINT32_C(0x000087b4): /* 8fb00010 */ READ(R(29u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x000087b8): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x000087bc): /* 27bd0020 */ D(29u,R(29u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0000e08c): /* 27bdffe8 */ D(29u,R(29u)+UINT32_C(0xffffffe8)); break;
  case UINT32_C(0x0000e090): /* afb00010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(16u)); break;
  case UINT32_C(0x0000e094): /* afbf0014 */ WRITE(R(29u)+UINT32_C(0x00000014),R(31u)); break;
  case UINT32_C(0x0000e098): /* 0c00481c */ B(UINT32_C(0x00012070));D(31u,pc+8u); break;
  case UINT32_C(0x0000e09c): /* 00808021 */ D(16u,R(4u)+R(0u)); break;
  case UINT32_C(0x0000e0a0): /* 10400011 */ B((R(2u)==R(0u))?UINT32_C(0x0000e0e8):pc+8u); break;
  case UINT32_C(0x0000e0a4): /* 2402ff9c */ D(2u,R(0u)+UINT32_C(0xffffff9c)); break;
  case UINT32_C(0x0000e0a8): /* 1200000f */ B((R(16u)==R(0u))?UINT32_C(0x0000e0e8):pc+8u); break;
  case UINT32_C(0x0000e0ac): /* 2402fe6a */ D(2u,R(0u)+UINT32_C(0xfffffe6a)); break;
  case UINT32_C(0x0000e0b0): /* 001011c2 */ D(2u,R(16u)>>7u); break;
  case UINT32_C(0x0000e0b4): /* 00022080 */ D(4u,R(2u)<<2u); break;
  case UINT32_C(0x0000e0b8): /* 94830008 */ address=R(4u)+UINT32_C(0x00000008);GET(address,2u);nl=3u;nv=value; break;
  case UINT32_C(0x0000e0bc): /* 24027f01 */ D(2u,R(0u)+UINT32_C(0x00007f01)); break;
  case UINT32_C(0x0000e0c0): /* 14620009 */ B((R(3u)!=R(2u))?UINT32_C(0x0000e0e8):pc+8u); break;
  case UINT32_C(0x0000e0c4): /* 2402fe69 */ D(2u,R(0u)+UINT32_C(0xfffffe69)); break;
  case UINT32_C(0x0000e0c8): /* 9483000a */ address=R(4u)+UINT32_C(0x0000000a);GET(address,2u);nl=3u;nv=value; break;
  case UINT32_C(0x0000e0cc): /* 00101043 */ D(2u,(uint32_t)((int32_t)R(16u)>>1u)); break;
  case UINT32_C(0x0000e0d0): /* 3042003f */ D(2u,R(2u)&UINT32_C(0x0000003f)); break;
  case UINT32_C(0x0000e0d4): /* 3063003f */ D(3u,R(3u)&UINT32_C(0x0000003f)); break;
  case UINT32_C(0x0000e0d8): /* 14620003 */ B((R(3u)!=R(2u))?UINT32_C(0x0000e0e8):pc+8u); break;
  case UINT32_C(0x0000e0dc): /* 2402fe69 */ D(2u,R(0u)+UINT32_C(0xfffffe69)); break;
  case UINT32_C(0x0000e0e0): /* 9482001e */ address=R(4u)+UINT32_C(0x0000001e);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x0000e0e4): /* a480001e */ PUT(R(4u)+UINT32_C(0x0000001e),2u,R(0u)); break;
  case UINT32_C(0x0000e0e8): /* 8fbf0014 */ READ(R(29u)+UINT32_C(0x00000014));nl=31u;nv=value; break;
  case UINT32_C(0x0000e0ec): /* 8fb00010 */ READ(R(29u)+UINT32_C(0x00000010));nl=16u;nv=value; break;
  case UINT32_C(0x0000e0f0): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0000e0f4): /* 27bd0018 */ D(29u,R(29u)+UINT32_C(0x00000018)); break;
  case UINT32_C(0x000d2244): /* 080037c6 */ B(UINT32_C(0x0000df18)); break;
  case UINT32_C(0x000d2248): /* 2400001a */ D(0u,R(0u)+UINT32_C(0x0000001a)); break;
  case UINT32_C(0x000d224c): /* 08003823 */ B(UINT32_C(0x0000e08c)); break;
  case UINT32_C(0x000d2250): /* 2400001c */ D(0u,R(0u)+UINT32_C(0x0000001c)); break;
  case UINT32_C(0x000d22e4): /* 08002277 */ B(UINT32_C(0x000089dc)); break;
  case UINT32_C(0x000d22e8): /* 24000017 */ D(0u,R(0u)+UINT32_C(0x00000017)); break;
  case UINT32_C(0x00008ca8): /* 080010a2 */ B(UINT32_C(0x00004288)); break;
  case UINT32_C(0x00008cac): /* 24000006 */ D(0u,R(0u)+UINT32_C(0x00000006)); break;
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

uint32_t nocturneIopTimerWakeRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopTimerWake *d)
{
 uint64_t start;uint32_t r;if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x000cd4b0u&&m->pc<0x000cd4fcu)||(m->pc>=0x000cd358u&&m->pc<0x000cd398u)||(m->pc>=0x000089dcu&&m->pc<0x00008b14u)||(m->pc>=0x000086a8u&&m->pc<0x000087c0u)||(m->pc>=0x0000e08cu&&m->pc<0x0000e0f8u)||(m->pc>=0x000d2244u&&m->pc<0x000d224cu)||(m->pc>=0x000d224cu&&m->pc<0x000d2254u)||(m->pc>=0x000d22e4u&&m->pc<0x000d22ecu)||(m->pc>=0x00008ca8u&&m->pc<0x00008cb0u))r=nocturneIopTimerWakeResume(m,ram,n,1u,d);
  else r=nocturneIopComponentSoundRoute(m,ram,n,1u,&d->prior);
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
