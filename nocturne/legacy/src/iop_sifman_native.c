#include "iop_sifman_native.h"
#include <string.h>
/* Fixed original words only; no instruction fetch/decode, allocator reply,
 * system call or scheduler emulation. Pending loads commit after the next
 * instruction reads its operands, before that instruction's explicit write. */
uint32_t nocturneIopSifmanResume(NocturneIopMachine *m,uint8_t *ram,uint32_t size,uint64_t limit,NocturneIopSifmanDevice *device)
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
  case UINT32_C(0x0001b074): /* 3c0800ff */ D(8u,UINT32_C(0x00ff0000)); break;
  case UINT32_C(0x0001b078): /* 3508ffff */ D(8u,R(8u)|UINT32_C(0x0000ffff)); break;
  case UINT32_C(0x0001b07c): /* 3c030002 */ D(3u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b080): /* 2463bc18 */ D(3u,R(3u)+UINT32_C(0xffffbc18)); break;
  case UINT32_C(0x0001b084): /* 8c62fffc */ READ(R(3u)+UINT32_C(0xfffffffc));nl=2u;nv=value; break;
  case UINT32_C(0x0001b088): /* 8c630000 */ READ(R(3u)+UINT32_C(0x00000000));nl=3u;nv=value; break;
  case UINT32_C(0x0001b08c): /* 00021100 */ D(2u,R(2u)<<4u); break;
  case UINT32_C(0x0001b090): /* 00622821 */ D(5u,R(3u)+R(2u)); break;
  case UINT32_C(0x0001b094): /* 8c820000 */ READ(R(4u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001b098): /* 8c830008 */ READ(R(4u)+UINT32_C(0x00000008));nl=3u;nv=value; break;
  case UINT32_C(0x0001b09c): /* 00483824 */ D(7u,R(2u)&R(8u)); break;
  case UINT32_C(0x0001b0a0): /* 24630003 */ D(3u,R(3u)+UINT32_C(0x00000003)); break;
  case UINT32_C(0x0001b0a4): /* aca70000 */ WRITE(R(5u)+UINT32_C(0x00000000),R(7u)); break;
  case UINT32_C(0x0001b0a8): /* 8c82000c */ READ(R(4u)+UINT32_C(0x0000000c));nl=2u;nv=value; break;
  case UINT32_C(0x0001b0ac): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b0b0): /* 30420002 */ D(2u,R(2u)&UINT32_C(0x00000002)); break;
  case UINT32_C(0x0001b0b4): /* 10400004 */ B((R(2u)==R(0u))?UINT32_C(0x0001b0c8):pc+8u); break;
  case UINT32_C(0x0001b0b8): /* 00033082 */ D(6u,R(3u)>>2u); break;
  case UINT32_C(0x0001b0bc): /* 3c024000 */ D(2u,UINT32_C(0x40000000)); break;
  case UINT32_C(0x0001b0c0): /* 00e21025 */ D(2u,R(7u)|R(2u)); break;
  case UINT32_C(0x0001b0c4): /* aca20000 */ WRITE(R(5u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001b0c8): /* 00c81024 */ D(2u,R(6u)&R(8u)); break;
  case UINT32_C(0x0001b0cc): /* aca20004 */ WRITE(R(5u)+UINT32_C(0x00000004),R(2u)); break;
  case UINT32_C(0x0001b0d0): /* 30c20003 */ D(2u,R(6u)&UINT32_C(0x00000003)); break;
  case UINT32_C(0x0001b0d4): /* 10400002 */ B((R(2u)==R(0u))?UINT32_C(0x0001b0e0):pc+8u); break;
  case UINT32_C(0x0001b0d8): /* 00031102 */ D(2u,R(3u)>>4u); break;
  case UINT32_C(0x0001b0dc): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001b0e0): /* 3c031000 */ D(3u,UINT32_C(0x10000000)); break;
  case UINT32_C(0x0001b0e4): /* 00431025 */ D(2u,R(2u)|R(3u)); break;
  case UINT32_C(0x0001b0e8): /* aca20008 */ WRITE(R(5u)+UINT32_C(0x00000008),R(2u)); break;
  case UINT32_C(0x0001b0ec): /* 8c82000c */ READ(R(4u)+UINT32_C(0x0000000c));nl=2u;nv=value; break;
  case UINT32_C(0x0001b0f0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b0f4): /* 30420004 */ D(2u,R(2u)&UINT32_C(0x00000004)); break;
  case UINT32_C(0x0001b0f8): /* 10400005 */ B((R(2u)==R(0u))?UINT32_C(0x0001b110):pc+8u); break;
  case UINT32_C(0x0001b0fc): /* 3c038000 */ D(3u,UINT32_C(0x80000000)); break;
  case UINT32_C(0x0001b100): /* 8ca20008 */ READ(R(5u)+UINT32_C(0x00000008));nl=2u;nv=value; break;
  case UINT32_C(0x0001b104): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b108): /* 00431025 */ D(2u,R(2u)|R(3u)); break;
  case UINT32_C(0x0001b10c): /* aca20008 */ WRITE(R(5u)+UINT32_C(0x00000008),R(2u)); break;
  case UINT32_C(0x0001b110): /* 3c031fff */ D(3u,UINT32_C(0x1fff0000)); break;
  case UINT32_C(0x0001b114): /* 8c820004 */ READ(R(4u)+UINT32_C(0x00000004));nl=2u;nv=value; break;
  case UINT32_C(0x0001b118): /* 3463ffff */ D(3u,R(3u)|UINT32_C(0x0000ffff)); break;
  case UINT32_C(0x0001b11c): /* 00431024 */ D(2u,R(2u)&R(3u)); break;
  case UINT32_C(0x0001b120): /* 3c030002 */ D(3u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b124): /* 2463bc14 */ D(3u,R(3u)+UINT32_C(0xffffbc14)); break;
  case UINT32_C(0x0001b128): /* aca2000c */ WRITE(R(5u)+UINT32_C(0x0000000c),R(2u)); break;
  case UINT32_C(0x0001b12c): /* 8c620000 */ READ(R(3u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001b130): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b134): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001b138): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001b13c): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001b140): /* 27bdffc8 */ D(29u,R(29u)+UINT32_C(0xffffffc8)); break;
  case UINT32_C(0x0001b144): /* afb1001c */ WRITE(R(29u)+UINT32_C(0x0000001c),R(17u)); break;
  case UINT32_C(0x0001b148): /* 00808821 */ D(17u,R(4u)+R(0u)); break;
  case UINT32_C(0x0001b14c): /* afb20020 */ WRITE(R(29u)+UINT32_C(0x00000020),R(18u)); break;
  case UINT32_C(0x0001b150): /* 00a09021 */ D(18u,R(5u)+R(0u)); break;
  case UINT32_C(0x0001b154): /* afb30024 */ WRITE(R(29u)+UINT32_C(0x00000024),R(19u)); break;
  case UINT32_C(0x0001b158): /* 00c09821 */ D(19u,R(6u)+R(0u)); break;
  case UINT32_C(0x0001b15c): /* afb5002c */ WRITE(R(29u)+UINT32_C(0x0000002c),R(21u)); break;
  case UINT32_C(0x0001b160): /* 3c040002 */ D(4u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b164): /* 2484bc14 */ D(4u,R(4u)+UINT32_C(0xffffbc14)); break;
  case UINT32_C(0x0001b168): /* afbf0034 */ WRITE(R(29u)+UINT32_C(0x00000034),R(31u)); break;
  case UINT32_C(0x0001b16c): /* afb60030 */ WRITE(R(29u)+UINT32_C(0x00000030),R(22u)); break;
  case UINT32_C(0x0001b170): /* afb40028 */ WRITE(R(29u)+UINT32_C(0x00000028),R(20u)); break;
  case UINT32_C(0x0001b174): /* afb00018 */ WRITE(R(29u)+UINT32_C(0x00000018),R(16u)); break;
  case UINT32_C(0x0001b178): /* 8c830000 */ READ(R(4u)+UINT32_C(0x00000000));nl=3u;nv=value; break;
  case UINT32_C(0x0001b17c): /* 24020020 */ D(2u,R(0u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001b180): /* 00431023 */ D(2u,R(2u)-R(3u)); break;
  case UINT32_C(0x0001b184): /* 0052102a */ D(2u,(int32_t)R(2u)<(int32_t)R(18u)); break;
  case UINT32_C(0x0001b188): /* 10400003 */ B((R(2u)==R(0u))?UINT32_C(0x0001b198):pc+8u); break;
  case UINT32_C(0x0001b18c): /* 00e0a821 */ D(21u,R(7u)+R(0u)); break;
  case UINT32_C(0x0001b190): /* 08006cda */ B(UINT32_C(0x0001b368)); break;
  case UINT32_C(0x0001b194): /* 00001021 */ D(2u,R(0u)+R(0u)); break;
  case UINT32_C(0x0001b198): /* 0060a021 */ D(20u,R(3u)+R(0u)); break;
  case UINT32_C(0x0001b19c): /* 9496fffc */ READ16(R(4u)+UINT32_C(0xfffffffc));nl=22u;nv=value16; break;
  case UINT32_C(0x0001b1a0): /* 1280000b */ B((R(20u)==R(0u))?UINT32_C(0x0001b1d0):pc+8u); break;
  case UINT32_C(0x0001b1a4): /* 3c047fff */ D(4u,UINT32_C(0x7fff0000)); break;
  case UINT32_C(0x0001b1a8): /* 3c030002 */ D(3u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b1ac): /* 8c63bc14 */ READ(R(3u)+UINT32_C(0xffffbc14));nl=3u;nv=value; break;
  case UINT32_C(0x0001b1b0): /* 3c020002 */ D(2u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b1b4): /* 8c42bc18 */ READ(R(2u)+UINT32_C(0xffffbc18));nl=2u;nv=value; break;
  case UINT32_C(0x0001b1b8): /* 00031900 */ D(3u,R(3u)<<4u); break;
  case UINT32_C(0x0001b1bc): /* 00621821 */ D(3u,R(3u)+R(2u)); break;
  case UINT32_C(0x0001b1c0): /* 8c62fff0 */ READ(R(3u)+UINT32_C(0xfffffff0));nl=2u;nv=value; break;
  case UINT32_C(0x0001b1c4): /* 3484ffff */ D(4u,R(4u)|UINT32_C(0x0000ffff)); break;
  case UINT32_C(0x0001b1c8): /* 00441024 */ D(2u,R(2u)&R(4u)); break;
  case UINT32_C(0x0001b1cc): /* ac62fff0 */ WRITE(R(3u)+UINT32_C(0xfffffff0),R(2u)); break;
  case UINT32_C(0x0001b1d0): /* 1a400007 */ B(((int32_t)R(18u)<=0)?UINT32_C(0x0001b1f0):pc+8u); break;
  case UINT32_C(0x0001b1d4): /* 00008021 */ D(16u,R(0u)+R(0u)); break;
  case UINT32_C(0x0001b1d8): /* 0c006c1d */ B(UINT32_C(0x0001b074));D(31u,pc+8u); break;
  case UINT32_C(0x0001b1dc): /* 02202021 */ D(4u,R(17u)+R(0u)); break;
  case UINT32_C(0x0001b1e0): /* 26100001 */ D(16u,R(16u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001b1e4): /* 0212102a */ D(2u,(int32_t)R(16u)<(int32_t)R(18u)); break;
  case UINT32_C(0x0001b1e8): /* 1440fffb */ B((R(2u)!=R(0u))?UINT32_C(0x0001b1d8):pc+8u); break;
  case UINT32_C(0x0001b1ec): /* 26310010 */ D(17u,R(17u)+UINT32_C(0x00000010)); break;
  case UINT32_C(0x0001b1f0): /* 3c030002 */ D(3u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b1f4): /* 8c63bc14 */ READ(R(3u)+UINT32_C(0xffffbc14));nl=3u;nv=value; break;
  case UINT32_C(0x0001b1f8): /* 3c020002 */ D(2u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b1fc): /* 8c42bc18 */ READ(R(2u)+UINT32_C(0xffffbc18));nl=2u;nv=value; break;
  case UINT32_C(0x0001b200): /* 00031900 */ D(3u,R(3u)<<4u); break;
  case UINT32_C(0x0001b204): /* 00621821 */ D(3u,R(3u)+R(2u)); break;
  case UINT32_C(0x0001b208): /* 8c62fff0 */ READ(R(3u)+UINT32_C(0xfffffff0));nl=2u;nv=value; break;
  case UINT32_C(0x0001b20c): /* 3c048000 */ D(4u,UINT32_C(0x80000000)); break;
  case UINT32_C(0x0001b210): /* 00441025 */ D(2u,R(2u)|R(4u)); break;
  case UINT32_C(0x0001b214): /* 12600018 */ B((R(19u)==R(0u))?UINT32_C(0x0001b278):pc+8u); break;
  case UINT32_C(0x0001b218): /* ac62fff0 */ WRITE(R(3u)+UINT32_C(0xfffffff0),R(2u)); break;
  case UINT32_C(0x0001b21c): /* 3c030002 */ D(3u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b220): /* 8c63c020 */ READ(R(3u)+UINT32_C(0xffffc020));nl=3u;nv=value; break;
  case UINT32_C(0x0001b224): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b228): /* 8c620100 */ READ(R(3u)+UINT32_C(0x00000100));nl=2u;nv=value; break;
  case UINT32_C(0x0001b22c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b230): /* 000210c0 */ D(2u,R(2u)<<3u); break;
  case UINT32_C(0x0001b234): /* 00621821 */ D(3u,R(3u)+R(2u)); break;
  case UINT32_C(0x0001b238): /* ac730000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(19u)); break;
  case UINT32_C(0x0001b23c): /* 3c030002 */ D(3u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b240): /* 8c63c020 */ READ(R(3u)+UINT32_C(0xffffc020));nl=3u;nv=value; break;
  case UINT32_C(0x0001b244): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b248): /* 8c620100 */ READ(R(3u)+UINT32_C(0x00000100));nl=2u;nv=value; break;
  case UINT32_C(0x0001b24c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b250): /* 000210c0 */ D(2u,R(2u)<<3u); break;
  case UINT32_C(0x0001b254): /* 00621821 */ D(3u,R(3u)+R(2u)); break;
  case UINT32_C(0x0001b258): /* ac750004 */ WRITE(R(3u)+UINT32_C(0x00000004),R(21u)); break;
  case UINT32_C(0x0001b25c): /* 3c030002 */ D(3u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b260): /* 8c63c020 */ READ(R(3u)+UINT32_C(0xffffc020));nl=3u;nv=value; break;
  case UINT32_C(0x0001b264): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b268): /* 8c620100 */ READ(R(3u)+UINT32_C(0x00000100));nl=2u;nv=value; break;
  case UINT32_C(0x0001b26c): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b270): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001b274): /* ac620100 */ WRITE(R(3u)+UINT32_C(0x00000100),R(2u)); break;
  case UINT32_C(0x0001b278): /* 3c05bf80 */ D(5u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001b27c): /* 34a51528 */ D(5u,R(5u)|UINT32_C(0x00001528)); break;
  case UINT32_C(0x0001b280): /* 8ca20000 */ READ(R(5u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001b284): /* 3c030100 */ D(3u,UINT32_C(0x01000000)); break;
  case UINT32_C(0x0001b288): /* 00431024 */ D(2u,R(2u)&R(3u)); break;
  case UINT32_C(0x0001b28c): /* 14400031 */ B((R(2u)!=R(0u))?UINT32_C(0x0001b354):pc+8u); break;
  case UINT32_C(0x0001b290): /* 00161400 */ D(2u,R(22u)<<16u); break;
  case UINT32_C(0x0001b294): /* 3c02bf80 */ D(2u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001b298): /* 3442152c */ D(2u,R(2u)|UINT32_C(0x0000152c)); break;
  case UINT32_C(0x0001b29c): /* 3c03bd00 */ D(3u,UINT32_C(0xbd000000)); break;
  case UINT32_C(0x0001b2a0): /* 3c040002 */ D(4u,UINT32_C(0x00020000)); break;
  case UINT32_C(0x0001b2a4): /* 2484bc18 */ D(4u,R(4u)+UINT32_C(0xffffbc18)); break;
  case UINT32_C(0x0001b2a8): /* 8c860000 */ READ(R(4u)+UINT32_C(0x00000000));nl=6u;nv=value; break;
  case UINT32_C(0x0001b2ac): /* 34630040 */ D(3u,R(3u)|UINT32_C(0x00000040)); break;
  case UINT32_C(0x0001b2b0): /* aca00000 */ WRITE(R(5u)+UINT32_C(0x00000000),R(0u)); break;
  case UINT32_C(0x0001b2b4): /* ac460000 */ WRITE(R(2u)+UINT32_C(0x00000000),R(6u)); break;
  case UINT32_C(0x0001b2b8): /* 8c620000 */ READ(R(3u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001b2bc): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b2c0): /* 30420020 */ D(2u,R(2u)&UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001b2c4): /* 14400004 */ B((R(2u)!=R(0u))?UINT32_C(0x0001b2d8):pc+8u); break;
  case UINT32_C(0x0001b2c8): /* 3c02bf80 */ D(2u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001b2cc): /* 24020020 */ D(2u,R(0u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001b2d0): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001b2d4): /* 3c02bf80 */ D(2u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001b2d8): /* 34421524 */ D(2u,R(2u)|UINT32_C(0x00001524)); break;
  case UINT32_C(0x0001b2dc): /* 24030020 */ D(3u,R(0u)+UINT32_C(0x00000020)); break;
  case UINT32_C(0x0001b2e0): /* a4430000 */ WRITE16(R(2u)+UINT32_C(0x00000000),(uint16_t)R(3u)); break;
  case UINT32_C(0x0001b2e4): /* 9482fff8 */ READ16(R(4u)+UINT32_C(0xfffffff8));nl=2u;nv=value16; break;
  case UINT32_C(0x0001b2e8): /* 2483fff8 */ D(3u,R(4u)+UINT32_C(0xfffffff8)); break;
  case UINT32_C(0x0001b2ec): /* ac600004 */ WRITE(R(3u)+UINT32_C(0x00000004),R(0u)); break;
  case UINT32_C(0x0001b2f0): /* 24420001 */ D(2u,R(2u)+UINT32_C(0x00000001)); break;
  case UINT32_C(0x0001b2f4): /* a482fff8 */ WRITE16(R(4u)+UINT32_C(0xfffffff8),(uint16_t)R(2u)); break;
  case UINT32_C(0x0001b2f8): /* 24820004 */ D(2u,R(4u)+UINT32_C(0x00000004)); break;
  case UINT32_C(0x0001b2fc): /* 14c20007 */ B((R(6u)!=R(2u))?UINT32_C(0x0001b31c):pc+8u); break;
  case UINT32_C(0x0001b300): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b304): /* 24820204 */ D(2u,R(4u)+UINT32_C(0x00000204)); break;
  case UINT32_C(0x0001b308): /* ac820000 */ WRITE(R(4u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001b30c): /* 24820510 */ D(2u,R(4u)+UINT32_C(0x00000510)); break;
  case UINT32_C(0x0001b310): /* ac620410 */ WRITE(R(3u)+UINT32_C(0x00000410),R(2u)); break;
  case UINT32_C(0x0001b314): /* 08006ccb */ B(UINT32_C(0x0001b32c)); break;
  case UINT32_C(0x0001b318): /* 2482040c */ D(2u,R(4u)+UINT32_C(0x0000040c)); break;
  case UINT32_C(0x0001b31c): /* ac820000 */ WRITE(R(4u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001b320): /* 2482040c */ D(2u,R(4u)+UINT32_C(0x0000040c)); break;
  case UINT32_C(0x0001b324): /* ac620410 */ WRITE(R(3u)+UINT32_C(0x00000410),R(2u)); break;
  case UINT32_C(0x0001b328): /* 24820510 */ D(2u,R(4u)+UINT32_C(0x00000510)); break;
  case UINT32_C(0x0001b32c): /* ac62040c */ WRITE(R(3u)+UINT32_C(0x0000040c),R(2u)); break;
  case UINT32_C(0x0001b330): /* 3c03bf80 */ D(3u,UINT32_C(0xbf800000)); break;
  case UINT32_C(0x0001b334): /* 34631528 */ D(3u,R(3u)|UINT32_C(0x00001528)); break;
  case UINT32_C(0x0001b338): /* 3c020100 */ D(2u,UINT32_C(0x01000000)); break;
  case UINT32_C(0x0001b33c): /* 34420701 */ D(2u,R(2u)|UINT32_C(0x00000701)); break;
  case UINT32_C(0x0001b340): /* ac620000 */ WRITE(R(3u)+UINT32_C(0x00000000),R(2u)); break;
  case UINT32_C(0x0001b344): /* 8c620000 */ READ(R(3u)+UINT32_C(0x00000000));nl=2u;nv=value; break;
  case UINT32_C(0x0001b348): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b34c): /* afa20010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(2u)); break;
  case UINT32_C(0x0001b350): /* 00161400 */ D(2u,R(22u)<<16u); break;
  case UINT32_C(0x0001b354): /* 328300ff */ D(3u,R(20u)&UINT32_C(0x000000ff)); break;
  case UINT32_C(0x0001b358): /* 00031a00 */ D(3u,R(3u)<<8u); break;
  case UINT32_C(0x0001b35c): /* 00431025 */ D(2u,R(2u)|R(3u)); break;
  case UINT32_C(0x0001b360): /* 324300ff */ D(3u,R(18u)&UINT32_C(0x000000ff)); break;
  case UINT32_C(0x0001b364): /* 00431025 */ D(2u,R(2u)|R(3u)); break;
  case UINT32_C(0x0001b368): /* 8fbf0034 */ READ(R(29u)+UINT32_C(0x00000034));nl=31u;nv=value; break;
  case UINT32_C(0x0001b36c): /* 8fb60030 */ READ(R(29u)+UINT32_C(0x00000030));nl=22u;nv=value; break;
  case UINT32_C(0x0001b370): /* 8fb5002c */ READ(R(29u)+UINT32_C(0x0000002c));nl=21u;nv=value; break;
  case UINT32_C(0x0001b374): /* 8fb40028 */ READ(R(29u)+UINT32_C(0x00000028));nl=20u;nv=value; break;
  case UINT32_C(0x0001b378): /* 8fb30024 */ READ(R(29u)+UINT32_C(0x00000024));nl=19u;nv=value; break;
  case UINT32_C(0x0001b37c): /* 8fb20020 */ READ(R(29u)+UINT32_C(0x00000020));nl=18u;nv=value; break;
  case UINT32_C(0x0001b380): /* 8fb1001c */ READ(R(29u)+UINT32_C(0x0000001c));nl=17u;nv=value; break;
  case UINT32_C(0x0001b384): /* 8fb00018 */ READ(R(29u)+UINT32_C(0x00000018));nl=16u;nv=value; break;
  case UINT32_C(0x0001b388): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001b38c): /* 27bd0038 */ D(29u,R(29u)+UINT32_C(0x00000038)); break;
  case UINT32_C(0x0001b390): /* 27bdffe8 */ D(29u,R(29u)+UINT32_C(0xffffffe8)); break;
  case UINT32_C(0x0001b394): /* 00003021 */ D(6u,R(0u)+R(0u)); break;
  case UINT32_C(0x0001b398): /* afbf0010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(31u)); break;
  case UINT32_C(0x0001b39c): /* 0c006c50 */ B(UINT32_C(0x0001b140));D(31u,pc+8u); break;
  case UINT32_C(0x0001b3a0): /* 00c03821 */ D(7u,R(6u)+R(0u)); break;
  case UINT32_C(0x0001b3a4): /* 8fbf0010 */ READ(R(29u)+UINT32_C(0x00000010));nl=31u;nv=value; break;
  case UINT32_C(0x0001b3a8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b3ac): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001b3b0): /* 27bd0018 */ D(29u,R(29u)+UINT32_C(0x00000018)); break;
  case UINT32_C(0x0001b3b4): /* 27bdffe8 */ D(29u,R(29u)+UINT32_C(0xffffffe8)); break;
  case UINT32_C(0x0001b3b8): /* afbf0010 */ WRITE(R(29u)+UINT32_C(0x00000010),R(31u)); break;
  case UINT32_C(0x0001b3bc): /* 0c006c50 */ B(UINT32_C(0x0001b140));D(31u,pc+8u); break;
  case UINT32_C(0x0001b3c0): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b3c4): /* 8fbf0010 */ READ(R(29u)+UINT32_C(0x00000010));nl=31u;nv=value; break;
  case UINT32_C(0x0001b3c8): /* 00000000 */ /* nop */ break;
  case UINT32_C(0x0001b3cc): /* 03e00008 */ B(R(31u)); break;
  case UINT32_C(0x0001b3d0): /* 27bd0018 */ D(29u,R(29u)+UINT32_C(0x00000018)); break;
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
