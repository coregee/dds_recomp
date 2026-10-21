#include "iop_libsd_dma_callback.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopLibSdDmaCallbackResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopLibSdEffect *device)
{
 uint64_t start;uint32_t pc,next,old_branch,old_target,old_load,old_value;
 uint32_t wr,wv,nl,nv,address,value;
 if(!m||!ram||!device||m->gpr[0]||m->load_register>31u||m->branch_pending>1u)return NOCTURNE_IOP_DOMAIN;
 start=m->instructions;
#define R(r) (m->gpr[(r)])
#define D(r,v) do{wr=(r);wv=(v);}while(0)
#define B(v) do{if(old_branch)return NOCTURNE_IOP_DOMAIN;m->branch_pending=1u;m->branch_target=(v);}while(0)
#define PHYSICAL(a) ((a)>=0x80000000u&&(a)<0xc0000000u?(a)&0x1fffffffu:(a))
#define GET(a,width) do{uint32_t bus_a=(a),bus_n=(width);if(bus_a>=0xbf800000u){if(!nocturneIopLibSdEffectIo(device,0u,bus_a,bus_n,&value))return NOCTURNE_IOP_DOMAIN;}else{address=PHYSICAL(bus_a);if((address&(bus_n-1u))||size<bus_n||address>size-bus_n)return NOCTURNE_IOP_MEMORY;value=0u;memcpy(&value,ram+address,bus_n);}}while(0)
#define PUT(a,width,v) do{uint32_t bus_a=(a),bus_n=(width);value=(v);if(bus_a>=0xbf800000u){if(!nocturneIopLibSdEffectIo(device,1u,bus_a,bus_n,&value))return NOCTURNE_IOP_DOMAIN;}else{address=PHYSICAL(bus_a);if((address&(bus_n-1u))||size<bus_n||address>size-bus_n)return NOCTURNE_IOP_MEMORY;memcpy(ram+address,&value,bus_n);}}while(0)
#define READ(a) GET(a,4u)
#define WRITE(a,v) PUT(a,4u,v)
 for(;;){
  if(m->instructions-start>=limit)return NOCTURNE_IOP_LIMIT;
  pc=m->pc;next=pc+4u;old_branch=m->branch_pending;old_target=m->branch_target;
  old_load=m->load_register;old_value=m->load_value;wr=0u;wv=0u;nl=0u;nv=0u;
  m->branch_pending=0u;
  switch(pc){
  case UINT32_C(0x000b62f8): /* 27bdffd8 */ D(29u,R(29u)+UINT32_C(0xffffffd8)); break;
  case UINT32_C(0x000b62fc): /* afb20020 */ WRITE(R(29u)+UINT32_C(0x00000020),R(18u)); break;
  case UINT32_C(0x000b6300): /* 00809021 */ D(18u,R(4u)+R(0u)); break;
  case UINT32_C(0x000b6304): /* afbf0024 */ WRITE(R(29u)+UINT32_C(0x00000024),R(31u)); break;
  case UINT32_C(0x000b6308): /* afb1001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(17u)); break;
  case UINT32_C(0x000b630c): /* afb00018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(16u)); break;
  case UINT32_C(0x000b6310): /* 8e420000 */ READ(R(18u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x000b6314): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6318): /* 30430c00 */ D(3u,R(2u)&UINT32_C(0x00000c00)); break;
  case UINT32_C(0x000b631c): /* 24020400 */ D(2u,R(0u)+UINT32_C(0x00000400)); break;
  case UINT32_C(0x000b6320): /* 14620003 */ B((R(3u)!=R(2u))?UINT32_C(0x000b6330):pc+8u); break;
  case UINT32_C(0x000b6324): /* 24020800 */ D(2u,R(0u)+UINT32_C(0x00000800)); break;
  case UINT32_C(0x000b6328): /* 0802d8cf */ B(UINT32_C(0x000b633c)); break;
  case UINT32_C(0x000b632c): /* 24090001 */ D(9u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6330): /* 146200db */ B((R(3u)!=R(2u))?UINT32_C(0x000b66a0):pc+8u); break;
  case UINT32_C(0x000b6334): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6338): /* 00004821 */ D(9u,R(0u)+R(0u)); break;
  case UINT32_C(0x000b633c): /* 8c830000 */ READ(R(4u)+UINT32_C(0x00000000));nl=3u;nv=value; break;
  case UINT32_C(0x000b6340): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6344): /* 307100ff */ D(17u,R(3u)&UINT32_C(0x000000ff)); break;
  case UINT32_C(0x000b6348): /* 00113240 */ D(6u,R(17u)<<9u); break;
  case UINT32_C(0x000b634c): /* 00111100 */ D(2u,R(17u)<<4u); break;
  case UINT32_C(0x000b6350): /* 00512821 */ D(5u,R(2u)+R(17u)); break;
  case UINT32_C(0x000b6354): /* 30640300 */ D(4u,R(3u)&UINT32_C(0x00000300)); break;
  case UINT32_C(0x000b6358): /* 24020100 */ D(2u,R(0u)+UINT32_C(0x00000100)); break;
  case UINT32_C(0x000b635c): /* 14820065 */ B((R(4u)!=R(2u))?UINT32_C(0x000b64f4):pc+8u); break;
  case UINT32_C(0x000b6360): /* 00055940 */ D(11u,R(5u)<<5u); break;
  case UINT32_C(0x000b6364): /* 3c03bf90 */ D(3u,UINT32_C(0xbf900000)); break;
  case UINT32_C(0x000b6368): /* 34630344 */ D(3u,R(3u)|UINT32_C(0x00000344)); break;
  case UINT32_C(0x000b636c): /* 00111280 */ D(2u,R(17u)<<10u); break;
  case UINT32_C(0x000b6370): /* 00432021 */ D(4u,R(2u)+R(3u)); break;
  case UINT32_C(0x000b6374): /* 94820000 */ address=R(4u)+UINT32_C(0x00000000);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000b6378): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b637c): /* 30420080 */ D(2u,R(2u)&UINT32_C(0x00000080)); break;
  case UINT32_C(0x000b6380): /* 1440000c */ B((R(2u)!=R(0u))?UINT32_C(0x000b63b4):pc+8u); break;
  case UINT32_C(0x000b6384): /* 00001821 */ D(3u,R(0u)+R(0u)); break;
  case UINT32_C(0x000b6388): /* 3c050100 */ D(5u,UINT32_C(0x01000000)); break;
  case UINT32_C(0x000b638c): /* 24630001 */ D(3u,R(3u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6390): /* 00a3102a */ D(2u,(int32_t)R(5u)<(int32_t)R(3u)); break;
  case UINT32_C(0x000b6394): /* 14400007 */ B((R(2u)!=R(0u))?UINT32_C(0x000b63b4):pc+8u); break;
  case UINT32_C(0x000b6398): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b639c): /* 94820000 */ address=R(4u)+UINT32_C(0x00000000);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000b63a0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b63a4): /* 30420080 */ D(2u,R(2u)&UINT32_C(0x00000080)); break;
  case UINT32_C(0x000b63a8): /* 1040fff9 */ B((R(2u)==R(0u))?UINT32_C(0x000b6390):pc+8u); break;
  case UINT32_C(0x000b63ac): /* 24630001 */ D(3u,R(3u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b63b0): /* 2463ffff */ D(3u,R(3u)+UINT32_C(0xffffffff)); break;
  case UINT32_C(0x000b63b4): /* 3c03bf90 */ D(3u,UINT32_C(0xbf900000)); break;
  case UINT32_C(0x000b63b8): /* 3463019a */ D(3u,R(3u)|UINT32_C(0x0000019a)); break;
  case UINT32_C(0x000b63bc): /* 00061040 */ D(2u,R(6u)<<1u); break;
  case UINT32_C(0x000b63c0): /* 00432021 */ D(4u,R(2u)+R(3u)); break;
  case UINT32_C(0x000b63c4): /* 94820000 */ address=R(4u)+UINT32_C(0x00000000);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000b63c8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b63cc): /* 3042ffcf */ D(2u,R(2u)&UINT32_C(0x0000ffcf)); break;
  case UINT32_C(0x000b63d0): /* a4820000 */ PUT(R(4u)+UINT32_C(0x00000000),2u,R(2u)); break;
  case UINT32_C(0x000b63d4): /* 94820000 */ address=R(4u)+UINT32_C(0x00000000);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000b63d8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b63dc): /* 30420030 */ D(2u,R(2u)&UINT32_C(0x00000030)); break;
  case UINT32_C(0x000b63e0): /* 1040000b */ B((R(2u)==R(0u))?UINT32_C(0x000b6410):pc+8u); break;
  case UINT32_C(0x000b63e4): /* 00001821 */ D(3u,R(0u)+R(0u)); break;
  case UINT32_C(0x000b63e8): /* 24630001 */ D(3u,R(3u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b63ec): /* 2c620f01 */ D(2u,R(3u)<UINT32_C(0x00000f01)); break;
  case UINT32_C(0x000b63f0): /* 10400007 */ B((R(2u)==R(0u))?UINT32_C(0x000b6410):pc+8u); break;
  case UINT32_C(0x000b63f4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b63f8): /* 94820000 */ address=R(4u)+UINT32_C(0x00000000);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000b63fc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6400): /* 30420030 */ D(2u,R(2u)&UINT32_C(0x00000030)); break;
  case UINT32_C(0x000b6404): /* 1440fff9 */ B((R(2u)!=R(0u))?UINT32_C(0x000b63ec):pc+8u); break;
  case UINT32_C(0x000b6408): /* 24630001 */ D(3u,R(3u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b640c): /* 2463ffff */ D(3u,R(3u)+UINT32_C(0xffffffff)); break;
  case UINT32_C(0x000b6410): /* 15200003 */ B((R(9u)!=R(0u))?UINT32_C(0x000b6420):pc+8u); break;
  case UINT32_C(0x000b6414): /* 00118080 */ D(16u,R(17u)<<2u); break;
  case UINT32_C(0x000b6418): /* 0c02e0aa */ B(UINT32_C(0x000b82a8));D(31u,pc+8u); break;
  case UINT32_C(0x000b641c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6420): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6424): /* 00501021 */ D(2u,R(2u)+R(16u)); break;
  case UINT32_C(0x000b6428): /* 8c428e00 */ READ(R(2u)+UINT32_C(0xffff8e00));nl=2u;nv=value; break;
  case UINT32_C(0x000b642c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6430): /* 10400009 */ B((R(2u)==R(0u))?UINT32_C(0x000b6458):pc+8u); break;
  case UINT32_C(0x000b6434): /* 02202021 */ D(4u,R(17u)+R(0u)); break;
  case UINT32_C(0x000b6438): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b643c): /* 00501021 */ D(2u,R(2u)+R(16u)); break;
  case UINT32_C(0x000b6440): /* 8c428e00 */ READ(R(2u)+UINT32_C(0xffff8e00));nl=2u;nv=value; break;
  case UINT32_C(0x000b6444): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6448): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x000b644c): /* 00002821 */ D(5u,R(0u)+R(0u)); break;
  case UINT32_C(0x000b6450): /* 0802d9a8 */ B(UINT32_C(0x000b66a0)); break;
  case UINT32_C(0x000b6454): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6458): /* 3c04000c */ D(4u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b645c): /* 00902021 */ D(4u,R(4u)+R(16u)); break;
  case UINT32_C(0x000b6460): /* 8c848de0 */ READ(R(4u)+UINT32_C(0xffff8de0));nl=4u;nv=value; break;
  case UINT32_C(0x000b6464): /* 0c02e0cf */ B(UINT32_C(0x000b833c));D(31u,pc+8u); break;
  case UINT32_C(0x000b6468): /* 24050001 */ D(5u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b646c): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6470): /* 00501021 */ D(2u,R(2u)+R(16u)); break;
  case UINT32_C(0x000b6474): /* 8c428df8 */ READ(R(2u)+UINT32_C(0xffff8df8));nl=2u;nv=value; break;
  case UINT32_C(0x000b6478): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b647c): /* 1040000a */ B((R(2u)==R(0u))?UINT32_C(0x000b64a8):pc+8u); break;
  case UINT32_C(0x000b6480): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6484): /* 3c01000c */ D(1u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6488): /* 00300821 */ D(1u,R(1u)+R(16u)); break;
  case UINT32_C(0x000b648c): /* ac228c6c */ WRITE(R(1u)+UINT32_C(0xffff8c6c),R(2u)); break;
  case UINT32_C(0x000b6490): /* 8e450004 */ READ(R(18u)+UINT32_C(0x00000004));nl=5u;nv=value; break;
  case UINT32_C(0x000b6494): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6498): /* 00501021 */ D(2u,R(2u)+R(16u)); break;
  case UINT32_C(0x000b649c): /* 8c428df8 */ READ(R(2u)+UINT32_C(0xffff8df8));nl=2u;nv=value; break;
  case UINT32_C(0x000b64a0): /* 0802d997 */ B(UINT32_C(0x000b665c)); break;
  case UINT32_C(0x000b64a4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b64a8): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b64ac): /* 00501021 */ D(2u,R(2u)+R(16u)); break;
  case UINT32_C(0x000b64b0): /* 8c429480 */ READ(R(2u)+UINT32_C(0xffff9480));nl=2u;nv=value; break;
  case UINT32_C(0x000b64b4): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b64b8): /* 10400009 */ B((R(2u)==R(0u))?UINT32_C(0x000b64e0):pc+8u); break;
  case UINT32_C(0x000b64bc): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b64c0): /* 3c01000c */ D(1u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b64c4): /* 00300821 */ D(1u,R(1u)+R(16u)); break;
  case UINT32_C(0x000b64c8): /* ac228c6c */ WRITE(R(1u)+UINT32_C(0xffff8c6c),R(2u)); break;
  case UINT32_C(0x000b64cc): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b64d0): /* 00501021 */ D(2u,R(2u)+R(16u)); break;
  case UINT32_C(0x000b64d4): /* 8c429480 */ READ(R(2u)+UINT32_C(0xffff9480));nl=2u;nv=value; break;
  case UINT32_C(0x000b64d8): /* 0802d9a5 */ B(UINT32_C(0x000b6694)); break;
  case UINT32_C(0x000b64dc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b64e0): /* 3c01000c */ D(1u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b64e4): /* 00300821 */ D(1u,R(1u)+R(16u)); break;
  case UINT32_C(0x000b64e8): /* ac228dd8 */ WRITE(R(1u)+UINT32_C(0xffff8dd8),R(2u)); break;
  case UINT32_C(0x000b64ec): /* 0802d9a8 */ B(UINT32_C(0x000b66a0)); break;
  case UINT32_C(0x000b64f0): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b64f4): /* 24020200 */ D(2u,R(0u)+UINT32_C(0x00000200)); break;
  case UINT32_C(0x000b64f8): /* 14820069 */ B((R(4u)!=R(2u))?UINT32_C(0x000b66a0):pc+8u); break;
  case UINT32_C(0x000b64fc): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6500): /* 30621000 */ D(2u,R(3u)&UINT32_C(0x00001000)); break;
  case UINT32_C(0x000b6504): /* 1440000f */ B((R(2u)!=R(0u))?UINT32_C(0x000b6544):pc+8u); break;
  case UINT32_C(0x000b6508): /* 00113080 */ D(6u,R(17u)<<2u); break;
  case UINT32_C(0x000b650c): /* 3c04bf90 */ D(4u,UINT32_C(0xbf900000)); break;
  case UINT32_C(0x000b6510): /* 3484019a */ D(4u,R(4u)|UINT32_C(0x0000019a)); break;
  case UINT32_C(0x000b6514): /* 3c05bf90 */ D(5u,UINT32_C(0xbf900000)); break;
  case UINT32_C(0x000b6518): /* 00111a80 */ D(3u,R(17u)<<10u); break;
  case UINT32_C(0x000b651c): /* 00642021 */ D(4u,R(3u)+R(4u)); break;
  case UINT32_C(0x000b6520): /* 34a501b0 */ D(5u,R(5u)|UINT32_C(0x000001b0)); break;
  case UINT32_C(0x000b6524): /* 94820000 */ address=R(4u)+UINT32_C(0x00000000);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000b6528): /* 00651821 */ D(3u,R(3u)+R(5u)); break;
  case UINT32_C(0x000b652c): /* 3042ffcf */ D(2u,R(2u)&UINT32_C(0x0000ffcf)); break;
  case UINT32_C(0x000b6530): /* a4820000 */ PUT(R(4u)+UINT32_C(0x00000000),2u,R(2u)); break;
  case UINT32_C(0x000b6534): /* a4600000 */ PUT(R(3u)+UINT32_C(0x00000000),2u,R(0u)); break;
  case UINT32_C(0x000b6538): /* 94620000 */ address=R(3u)+UINT32_C(0x00000000);GET(address,2u);nl=2u;nv=value; break;
  case UINT32_C(0x000b653c): /* 0802d986 */ B(UINT32_C(0x000b6618)); break;
  case UINT32_C(0x000b6540): /* 3042ffff */ D(2u,R(2u)&UINT32_C(0x0000ffff)); break;
  case UINT32_C(0x000b6544): /* 24040001 */ D(4u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6548): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b654c): /* 00461021 */ D(2u,R(2u)+R(6u)); break;
  case UINT32_C(0x000b6550): /* 8c429450 */ READ(R(2u)+UINT32_C(0xffff9450));nl=2u;nv=value; break;
  case UINT32_C(0x000b6554): /* 3c03000c */ D(3u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6558): /* 00661821 */ D(3u,R(3u)+R(6u)); break;
  case UINT32_C(0x000b655c): /* 8c639460 */ READ(R(3u)+UINT32_C(0xffff9460));nl=3u;nv=value; break;
  case UINT32_C(0x000b6560): /* 00823823 */ D(7u,R(4u)-R(2u)); break;
  case UINT32_C(0x000b6564): /* 00e30018 */ {int64_t product=(int64_t)(int32_t)R(7u)*(int64_t)(int32_t)R(3u);m->hi=(uint32_t)((uint64_t)product>>32);m->lo=(uint32_t)product;} break;
  case UINT32_C(0x000b6568): /* 3c03bf80 */ D(3u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x000b656c): /* 346310c6 */ D(3u,R(3u)|UINT32_C(0x000010c6)); break;
  case UINT32_C(0x000b6570): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6574): /* 00461021 */ D(2u,R(2u)+R(6u)); break;
  case UINT32_C(0x000b6578): /* 8c429458 */ READ(R(2u)+UINT32_C(0xffff9458));nl=2u;nv=value; break;
  case UINT32_C(0x000b657c): /* 3c04000c */ D(4u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6580): /* 00862021 */ D(4u,R(4u)+R(6u)); break;
  case UINT32_C(0x000b6584): /* 8c849460 */ READ(R(4u)+UINT32_C(0xffff9460));nl=4u;nv=value; break;
  case UINT32_C(0x000b6588): /* 00006012 */ D(12u,m->lo); break;
  case UINT32_C(0x000b658c): /* 004c5021 */ D(10u,R(2u)+R(12u)); break;
  case UINT32_C(0x000b6590): /* 00051180 */ D(2u,R(5u)<<6u); break;
  case UINT32_C(0x000b6594): /* 04810002 */ B(((int32_t)R(4u)>=0)?UINT32_C(0x000b65a0):pc+8u); break;
  case UINT32_C(0x000b6598): /* 00434021 */ D(8u,R(2u)+R(3u)); break;
  case UINT32_C(0x000b659c): /* 2484003f */ D(4u,R(4u)+UINT32_C(0x0000003f)); break;
  case UINT32_C(0x000b65a0): /* 3c03000c */ D(3u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b65a4): /* 00661821 */ D(3u,R(3u)+R(6u)); break;
  case UINT32_C(0x000b65a8): /* 8c639460 */ READ(R(3u)+UINT32_C(0xffff9460));nl=3u;nv=value; break;
  case UINT32_C(0x000b65ac): /* 00042183 */ D(4u,(uint32_t)((int32_t)R(4u)>>6u)); break;
  case UINT32_C(0x000b65b0): /* 04610002 */ B(((int32_t)R(3u)>=0)?UINT32_C(0x000b65bc):pc+8u); break;
  case UINT32_C(0x000b65b4): /* 00601021 */ D(2u,R(3u)+R(0u)); break;
  case UINT32_C(0x000b65b8): /* 2462003f */ D(2u,R(3u)+UINT32_C(0x0000003f)); break;
  case UINT32_C(0x000b65bc): /* 00021183 */ D(2u,(uint32_t)((int32_t)R(2u)>>6u)); break;
  case UINT32_C(0x000b65c0): /* 00021180 */ D(2u,R(2u)<<6u); break;
  case UINT32_C(0x000b65c4): /* 00621023 */ D(2u,R(3u)-R(2u)); break;
  case UINT32_C(0x000b65c8): /* 0002102a */ D(2u,(int32_t)R(0u)<(int32_t)R(2u)); break;
  case UINT32_C(0x000b65cc): /* 00821021 */ D(2u,R(4u)+R(2u)); break;
  case UINT32_C(0x000b65d0): /* 3c04bf80 */ D(4u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x000b65d4): /* 348410c0 */ D(4u,R(4u)|UINT32_C(0x000010c0)); break;
  case UINT32_C(0x000b65d8): /* 3c05bf80 */ D(5u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x000b65dc): /* 34a510c8 */ D(5u,R(5u)|UINT32_C(0x000010c8)); break;
  case UINT32_C(0x000b65e0): /* 3c030100 */ D(3u,UINT32_C(0x01000000)); break;
  case UINT32_C(0x000b65e4): /* 34630200 */ D(3u,R(3u)|UINT32_C(0x00000200)); break;
  case UINT32_C(0x000b65e8): /* a5020000 */ PUT(R(8u)+UINT32_C(0x00000000),2u,R(2u)); break;
  case UINT32_C(0x000b65ec): /* 000b1040 */ D(2u,R(11u)<<1u); break;
  case UINT32_C(0x000b65f0): /* 00442021 */ D(4u,R(2u)+R(4u)); break;
  case UINT32_C(0x000b65f4): /* 00451021 */ D(2u,R(2u)+R(5u)); break;
  case UINT32_C(0x000b65f8): /* 01231825 */ D(3u,R(9u)|R(3u)); break;
  case UINT32_C(0x000b65fc): /* 3c01000c */ D(1u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6600): /* 00260821 */ D(1u,R(1u)+R(6u)); break;
  case UINT32_C(0x000b6604): /* ac279450 */ WRITE(R(1u)+UINT32_C(0xffff9450),R(7u)); break;
  case UINT32_C(0x000b6608): /* ac8a0000 */ WRITE(R(4u)+UINT32_C(0x00000000),R(10u)); break;
  case UINT32_C(0x000b660c): /* ac430000 */ WRITE(R(2u)+UINT32_C(0x00000000),R(3u)); break;
  case UINT32_C(0x000b6610): /* 8c420000 */ READ(R(2u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x000b6614): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6618): /* afa20010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(2u)); break;
  case UINT32_C(0x000b661c): /* 15200004 */ B((R(9u)!=R(0u))?UINT32_C(0x000b6630):pc+8u); break;
  case UINT32_C(0x000b6620): /* 00111880 */ D(3u,R(17u)<<2u); break;
  case UINT32_C(0x000b6624): /* 0c02e0aa */ B(UINT32_C(0x000b82a8));D(31u,pc+8u); break;
  case UINT32_C(0x000b6628): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b662c): /* 00111880 */ D(3u,R(17u)<<2u); break;
  case UINT32_C(0x000b6630): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6634): /* 00431021 */ D(2u,R(2u)+R(3u)); break;
  case UINT32_C(0x000b6638): /* 8c428df8 */ READ(R(2u)+UINT32_C(0xffff8df8));nl=2u;nv=value; break;
  case UINT32_C(0x000b663c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6640): /* 1040000a */ B((R(2u)==R(0u))?UINT32_C(0x000b666c):pc+8u); break;
  case UINT32_C(0x000b6644): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6648): /* 8e450004 */ READ(R(18u)+UINT32_C(0x00000004));nl=5u;nv=value; break;
  case UINT32_C(0x000b664c): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6650): /* 00431021 */ D(2u,R(2u)+R(3u)); break;
  case UINT32_C(0x000b6654): /* 8c428df8 */ READ(R(2u)+UINT32_C(0xffff8df8));nl=2u;nv=value; break;
  case UINT32_C(0x000b6658): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b665c): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x000b6660): /* 02202021 */ D(4u,R(17u)+R(0u)); break;
  case UINT32_C(0x000b6664): /* 0802d9a8 */ B(UINT32_C(0x000b66a0)); break;
  case UINT32_C(0x000b6668): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b666c): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6670): /* 00431021 */ D(2u,R(2u)+R(3u)); break;
  case UINT32_C(0x000b6674): /* 8c429480 */ READ(R(2u)+UINT32_C(0xffff9480));nl=2u;nv=value; break;
  case UINT32_C(0x000b6678): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b667c): /* 10400008 */ B((R(2u)==R(0u))?UINT32_C(0x000b66a0):pc+8u); break;
  case UINT32_C(0x000b6680): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b6684): /* 3c02000c */ D(2u,UINT32_C(0x000c0000)); break;
  case UINT32_C(0x000b6688): /* 00431021 */ D(2u,R(2u)+R(3u)); break;
  case UINT32_C(0x000b668c): /* 8c429480 */ READ(R(2u)+UINT32_C(0xffff9480));nl=2u;nv=value; break;
  case UINT32_C(0x000b6690): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b6694): /* 0040f809 */ B(R(2u));D(31u,pc+8u); break;
  case UINT32_C(0x000b6698): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x000b669c): /* 24020001 */ D(2u,R(0u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x000b66a0): /* 8fbf0024 */ READ(R(29u)+UINT32_C(0x00000024));nl=31u;nv=value; break;
  case UINT32_C(0x000b66a4): /* 8fb20020 */ READ(R(29u)+UINT32_C(0x00000020));nl=18u;nv=value; break;
  case UINT32_C(0x000b66a8): /* 8fb1001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=17u;nv=value; break;
  case UINT32_C(0x000b66ac): /* 8fb00018 */ READ(R(29u)+UINT32_C(0x00000018));nl=16u;nv=value; break;
  case UINT32_C(0x000b66b0): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x000b66b4): /* 27bd0028 */ D(29u,R(29u)+UINT32_C(0x00000028)); break;
  case UINT32_C(0x000b82a8): /* 08000c4d */ B(UINT32_C(0x00003134)); break;
  case UINT32_C(0x000b82ac): /* 24000005 */ D(0u,R(0u)+UINT32_C(0x00000005)); break;
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

uint32_t nocturneIopLibSdDmaCallbackRoute(NocturneIopMachine *m,uint8_t *ram,uint32_t n,uint64_t limit,NocturneIopLibSdEffect *d)
{
 uint64_t start;uint32_t r;if(!m||!ram||!d)return NOCTURNE_IOP_DOMAIN;start=m->instructions;
 while(m->instructions-start<limit){
  if((m->pc>=0x000b62f8u&&m->pc<0x000b66b8u)||(m->pc>=0x000b82a8u&&m->pc<0x000b82b0u))r=nocturneIopLibSdDmaCallbackResume(m,ram,n,1u,d);
  else r=nocturneIopLibSdEffectRoute(m,ram,n,1u,d);
  if(r!=NOCTURNE_IOP_LIMIT)return r;
 }
 return NOCTURNE_IOP_LIMIT;
}
