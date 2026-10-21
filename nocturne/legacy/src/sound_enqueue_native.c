#include "sound_enqueue_native.h"
#include <string.h>
/* Original Nocturne ELF source-bound fixed statements. RAM and all MMIO are delegated
 * to the initialized memory owner; no INTC acknowledgement is synthesized.
 * The caller owns actual interrupt/SYSCALL entry, Cause/EPC/Status and clocks. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneSoundEnqueueResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
{
 uint64_t target,value64=0,started;uint32_t value32=0,address=0;uint16_t value16=0;
 if(!m||!ram||!ram->read||!ram->write||!s)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
 memset(s,0,sizeof(*s));
 if(m->gpr[0][0]||m->gpr[0][1]||m->gpr[0][2]||m->gpr[0][3])return stop(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN,0,0,0);
 if(!limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);
 started=m->instructions;target=sx(m->pc);
#define STEP(p) do{m->pc=(p);if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);++m->instructions;}while(0)
#define READ(a,p,n) do{address=(a);if((address&((n)-1u))||!ram->read(ram->owner,address,(p),(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);}while(0)
#define WRITE(a,p,n) do{address=(a);if((address&((n)-1u))||!ram->write(ram->owner,address,(p),(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);}while(0)
dispatch:
 m->pc=(uint32_t)target;
 switch(m->pc){
 case UINT32_C(0x002c10e8):goto L_002c10e8;
 case UINT32_C(0x002c10ec):goto L_002c10ec;
 case UINT32_C(0x002c10f0):goto L_002c10f0;
 case UINT32_C(0x002c10f4):goto L_002c10f4;
 case UINT32_C(0x002c10f8):goto L_002c10f8;
 case UINT32_C(0x002c10fc):goto L_002c10fc;
 case UINT32_C(0x002c1100):goto L_002c1100;
 case UINT32_C(0x002c1104):goto L_002c1104;
 case UINT32_C(0x002c1108):goto L_002c1108;
 case UINT32_C(0x002c110c):goto L_002c110c;
 case UINT32_C(0x002c1110):goto L_002c1110;
 case UINT32_C(0x002c1114):goto L_002c1114;
 case UINT32_C(0x002c1118):goto L_002c1118;
 case UINT32_C(0x002c111c):goto L_002c111c;
 case UINT32_C(0x002c1120):goto L_002c1120;
 case UINT32_C(0x002c1124):goto L_002c1124;
 case UINT32_C(0x002c1128):goto L_002c1128;
 case UINT32_C(0x002c112c):goto L_002c112c;
 case UINT32_C(0x002c1130):goto L_002c1130;
 case UINT32_C(0x002c1134):goto L_002c1134;
 case UINT32_C(0x002c1138):goto L_002c1138;
 case UINT32_C(0x002c113c):goto L_002c113c;
 case UINT32_C(0x002c1140):goto L_002c1140;
 case UINT32_C(0x002c1144):goto L_002c1144;
 case UINT32_C(0x002c1148):goto L_002c1148;
 case UINT32_C(0x002c114c):goto L_002c114c;
 case UINT32_C(0x002c1150):goto L_002c1150;
 case UINT32_C(0x002c1154):goto L_002c1154;
 case UINT32_C(0x002c1158):goto L_002c1158;
 case UINT32_C(0x002c115c):goto L_002c115c;
 case UINT32_C(0x002c1160):goto L_002c1160;
 case UINT32_C(0x002c1164):goto L_002c1164;
 case UINT32_C(0x002c1168):goto L_002c1168;
 case UINT32_C(0x002c116c):goto L_002c116c;
 case UINT32_C(0x002c1170):goto L_002c1170;
 case UINT32_C(0x002c1174):goto L_002c1174;
 case UINT32_C(0x002c1178):goto L_002c1178;
 case UINT32_C(0x002c117c):goto L_002c117c;
 case UINT32_C(0x002c1180):goto L_002c1180;
 case UINT32_C(0x002c1184):goto L_002c1184;
 case UINT32_C(0x002c1188):goto L_002c1188;
 case UINT32_C(0x002c118c):goto L_002c118c;
 case UINT32_C(0x002c1190):goto L_002c1190;
 case UINT32_C(0x002c1194):goto L_002c1194;
 case UINT32_C(0x002c1198):goto L_002c1198;
 case UINT32_C(0x002c119c):goto L_002c119c;
 case UINT32_C(0x002c11a0):goto L_002c11a0;
 case UINT32_C(0x002c11a4):goto L_002c11a4;
 case UINT32_C(0x002c11a8):goto L_002c11a8;
 case UINT32_C(0x002c11ac):goto L_002c11ac;
 case UINT32_C(0x002c11b0):goto L_002c11b0;
 case UINT32_C(0x002c11b4):goto L_002c11b4;
 case UINT32_C(0x002c11b8):goto L_002c11b8;
 case UINT32_C(0x002c11bc):goto L_002c11bc;
 case UINT32_C(0x002c11c0):goto L_002c11c0;
 case UINT32_C(0x002c11c4):goto L_002c11c4;
 case UINT32_C(0x002c11c8):goto L_002c11c8;
 case UINT32_C(0x002c11cc):goto L_002c11cc;
 case UINT32_C(0x002c11d0):goto L_002c11d0;
 case UINT32_C(0x002c11d4):goto L_002c11d4;
 case UINT32_C(0x002c11d8):goto L_002c11d8;
 case UINT32_C(0x002c11dc):goto L_002c11dc;
 case UINT32_C(0x002c11e0):goto L_002c11e0;
 case UINT32_C(0x002c11e4):goto L_002c11e4;
 case UINT32_C(0x002c11e8):goto L_002c11e8;
 case UINT32_C(0x002c11ec):goto L_002c11ec;
 case UINT32_C(0x002c11f0):goto L_002c11f0;
 case UINT32_C(0x002c11f4):goto L_002c11f4;
 case UINT32_C(0x002c11f8):goto L_002c11f8;
 case UINT32_C(0x002c11fc):goto L_002c11fc;
 case UINT32_C(0x002c1200):goto L_002c1200;
 case UINT32_C(0x002c1204):goto L_002c1204;
 case UINT32_C(0x002c1208):goto L_002c1208;
 case UINT32_C(0x002c120c):goto L_002c120c;
 case UINT32_C(0x002c1210):goto L_002c1210;
 case UINT32_C(0x002c1214):goto L_002c1214;
 case UINT32_C(0x002c1218):goto L_002c1218;
 case UINT32_C(0x002c121c):goto L_002c121c;
 case UINT32_C(0x002c1220):goto L_002c1220;
 case UINT32_C(0x002c1224):goto L_002c1224;
 case UINT32_C(0x002c1228):goto L_002c1228;
 case UINT32_C(0x002c122c):goto L_002c122c;
 case UINT32_C(0x002c1230):goto L_002c1230;
 case UINT32_C(0x002d43a4):goto L_002d43a4;
 case UINT32_C(0x002d43a8):goto L_002d43a8;
 case UINT32_C(0x002d43ac):goto L_002d43ac;
 case UINT32_C(0x002d43b0):goto L_002d43b0;
 case UINT32_C(0x002d43b4):goto L_002d43b4;
 case UINT32_C(0x002d43b8):goto L_002d43b8;
 case UINT32_C(0x002d43bc):goto L_002d43bc;
 case UINT32_C(0x002d43c0):goto L_002d43c0;
 case UINT32_C(0x002d43c4):goto L_002d43c4;
 case UINT32_C(0x002d43c8):goto L_002d43c8;
 case UINT32_C(0x002d43cc):goto L_002d43cc;
 case UINT32_C(0x002d43d0):goto L_002d43d0;
 case UINT32_C(0x002d43d4):goto L_002d43d4;
 case UINT32_C(0x002d43d8):goto L_002d43d8;
 case UINT32_C(0x002d43dc):goto L_002d43dc;
 case UINT32_C(0x002d43e0):goto L_002d43e0;
 case UINT32_C(0x002d43e4):goto L_002d43e4;
 case UINT32_C(0x002d43e8):goto L_002d43e8;
 case UINT32_C(0x002d43ec):goto L_002d43ec;
 case UINT32_C(0x002d43f0):goto L_002d43f0;
 case UINT32_C(0x002d43f4):goto L_002d43f4;
 case UINT32_C(0x002d43f8):goto L_002d43f8;
 case UINT32_C(0x002d43fc):goto L_002d43fc;
 case UINT32_C(0x002d4400):goto L_002d4400;
 case UINT32_C(0x002d4404):goto L_002d4404;
 case UINT32_C(0x002d4408):goto L_002d4408;
 case UINT32_C(0x002d440c):goto L_002d440c;
 case UINT32_C(0x002d4410):goto L_002d4410;
 case UINT32_C(0x002d4414):goto L_002d4414;
 case UINT32_C(0x002d4418):goto L_002d4418;
 case UINT32_C(0x002d441c):goto L_002d441c;
 case UINT32_C(0x002d4420):goto L_002d4420;
 case UINT32_C(0x002d4424):goto L_002d4424;
 case UINT32_C(0x002d4428):goto L_002d4428;
 case UINT32_C(0x002d442c):goto L_002d442c;
 case UINT32_C(0x002d4430):goto L_002d4430;
 case UINT32_C(0x002d4434):goto L_002d4434;
 case UINT32_C(0x002d4438):goto L_002d4438;
 case UINT32_C(0x002d443c):goto L_002d443c;
 case UINT32_C(0x002d4440):goto L_002d4440;
 case UINT32_C(0x002d4444):goto L_002d4444;
 case UINT32_C(0x002d4448):goto L_002d4448;
 case UINT32_C(0x002d444c):goto L_002d444c;
 case UINT32_C(0x002d4450):goto L_002d4450;
 case UINT32_C(0x002dbdd0):goto L_002dbdd0;
 case UINT32_C(0x002dbdd4):goto L_002dbdd4;
 case UINT32_C(0x002dbdd8):goto L_002dbdd8;
 case UINT32_C(0x002dbddc):goto L_002dbddc;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002c10e8:
 STEP(UINT32_C(0x002c10e8)); /* 8f82d860 lw v0,-0x27a0(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002c10ec));goto dispatch;
L_002c10ec:
 STEP(UINT32_C(0x002c10ec)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002c10f0));goto dispatch;
L_002c10f0:
 STEP(UINT32_C(0x002c10f0)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002c10f4));goto dispatch;
L_002c10f4:
 STEP(UINT32_C(0x002c10f4)); /* 00e0902d daddu s2,a3,zero */
 set(m,18u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002c10f8));goto dispatch;
L_002c10f8:
 STEP(UINT32_C(0x002c10f8)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c10fc));goto dispatch;
L_002c10fc:
 STEP(UINT32_C(0x002c10fc)); /* ffb30018 sd s3,0x18(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002c1100));goto dispatch;
L_002c1100:
 STEP(UINT32_C(0x002c1100)); /* ffb40020 sd s4,0x20(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002c1104));goto dispatch;
L_002c1104:
 STEP(UINT32_C(0x002c1104)); /* 00a0a02d daddu s4,a1,zero */
 set(m,20u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002c1108));goto dispatch;
L_002c1108:
 STEP(UINT32_C(0x002c1108)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c110c));goto dispatch;
L_002c110c:
 STEP(UINT32_C(0x002c110c)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002c1110));goto dispatch;
L_002c1110:
 STEP(UINT32_C(0x002c1110)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c1114));goto dispatch;
L_002c1114:
 STEP(UINT32_C(0x002c1114)); /* 00c0282d daddu a1,a2,zero */
 set(m,5u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002c1118));goto dispatch;
L_002c1118:
 STEP(UINT32_C(0x002c1118)); /* ffbf0028 sd ra,0x28(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002c111c));goto dispatch;
L_002c111c:
 STEP(UINT32_C(0x002c111c)); /* 14400004 bne v0,zero,002c1130 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002c1120));set(m,3u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002c1130):UINT32_C(0x002c1124));goto dispatch;}
L_002c1120:
 STEP(UINT32_C(0x002c1120)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c1124));goto dispatch;
L_002c1124:
 STEP(UINT32_C(0x002c1124)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1128));goto dispatch;
L_002c1128:
 STEP(UINT32_C(0x002c1128)); /* 10000002 beq zero,zero,002c1134 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c112c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);target=sx(taken?UINT32_C(0x002c1134):UINT32_C(0x002c1130));goto dispatch;}
L_002c112c:
 STEP(UINT32_C(0x002c112c)); /* af82d860 sw v0,-0x27a0(gp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);target=sx(UINT32_C(0x002c1130));goto dispatch;
L_002c1130:
 STEP(UINT32_C(0x002c1130)); /* af83d860 sw v1,-0x27a0(gp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);target=sx(UINT32_C(0x002c1134));goto dispatch;
L_002c1134:
 STEP(UINT32_C(0x002c1134)); /* 9782dfc4 lhu v0,-0x203c(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc4),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002c1138));goto dispatch;
L_002c1138:
 STEP(UINT32_C(0x002c1138)); /* 9783dfc2 lhu v1,-0x203e(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc2),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002c113c));goto dispatch;
L_002c113c:
 STEP(UINT32_C(0x002c113c)); /* 00021400 sll v0,v0,16 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<16u));target=sx(UINT32_C(0x002c1140));goto dispatch;
L_002c1140:
 STEP(UINT32_C(0x002c1140)); /* 00021403 sra v0,v0,16 */
 set(m,2u,sx((uint32_t)((int32_t)lo(m,2u)>>16u)));target=sx(UINT32_C(0x002c1144));goto dispatch;
L_002c1144:
 STEP(UINT32_C(0x002c1144)); /* 00031c00 sll v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<16u));target=sx(UINT32_C(0x002c1148));goto dispatch;
L_002c1148:
 STEP(UINT32_C(0x002c1148)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c114c));goto dispatch;
L_002c114c:
 STEP(UINT32_C(0x002c114c)); /* 00031c03 sra v1,v1,16 */
 set(m,3u,sx((uint32_t)((int32_t)lo(m,3u)>>16u)));target=sx(UINT32_C(0x002c1150));goto dispatch;
L_002c1150:
 STEP(UINT32_C(0x002c1150)); /* 3051001f andi s1,v0,0x1f */
 set(m,17u,lo(m,2u) & UINT64_C(0x1f));target=sx(UINT32_C(0x002c1154));goto dispatch;
L_002c1154:
 STEP(UINT32_C(0x002c1154)); /* 1623000e bne s1,v1,002c1190 */
 {int taken=(lo(m,17u)!=lo(m,3u));STEP(UINT32_C(0x002c1158));set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002c1190):UINT32_C(0x002c115c));goto dispatch;}
L_002c1158:
 STEP(UINT32_C(0x002c1158)); /* 24100008 addiu s0,zero,8 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002c115c));goto dispatch;
L_002c115c:
 STEP(UINT32_C(0x002c115c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1160));goto dispatch;
L_002c1160:
 STEP(UINT32_C(0x002c1160)); /* 0c0b6f74 jal 002dbdd0 */
 set(m,31u,UINT64_C(0x002c1168));STEP(UINT32_C(0x002c1164));READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbdd0));goto dispatch;
L_002c1164:
 STEP(UINT32_C(0x002c1164)); /* 8f84dfc8 lw a0,-0x2038(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002c1168));goto dispatch;
L_002c1168:
 STEP(UINT32_C(0x002c1168)); /* 9783dfc2 lhu v1,-0x203e(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc2),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002c116c));goto dispatch;
L_002c116c:
 STEP(UINT32_C(0x002c116c)); /* 00031c00 sll v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<16u));target=sx(UINT32_C(0x002c1170));goto dispatch;
L_002c1170:
 STEP(UINT32_C(0x002c1170)); /* 00031c03 sra v1,v1,16 */
 set(m,3u,sx((uint32_t)((int32_t)lo(m,3u)>>16u)));target=sx(UINT32_C(0x002c1174));goto dispatch;
L_002c1174:
 STEP(UINT32_C(0x002c1174)); /* 1471fffa bne v1,s1,002c1160 */
 {int taken=(lo(m,3u)!=lo(m,17u));STEP(UINT32_C(0x002c1178));/* nop */target=sx(taken?UINT32_C(0x002c1160):UINT32_C(0x002c117c));goto dispatch;}
L_002c1178:
 STEP(UINT32_C(0x002c1178)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c117c));goto dispatch;
L_002c117c:
 STEP(UINT32_C(0x002c117c)); /* 2610ffff addiu s0,s0,-1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002c1180));goto dispatch;
L_002c1180:
 STEP(UINT32_C(0x002c1180)); /* 1600fff7 bne s0,zero,002c1160 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002c1184));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002c1160):UINT32_C(0x002c1188));goto dispatch;}
L_002c1184:
 STEP(UINT32_C(0x002c1184)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1188));goto dispatch;
L_002c1188:
 STEP(UINT32_C(0x002c1188)); /* 10000023 beq zero,zero,002c1218 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c118c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002c1218):UINT32_C(0x002c1190));goto dispatch;}
L_002c118c:
 STEP(UINT32_C(0x002c118c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1190));goto dispatch;
L_002c1190:
 STEP(UINT32_C(0x002c1190)); /* 9782dfc4 lhu v0,-0x203c(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc4),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002c1194));goto dispatch;
L_002c1194:
 STEP(UINT32_C(0x002c1194)); /* 8f83d860 lw v1,-0x27a0(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002c1198));goto dispatch;
L_002c1198:
 STEP(UINT32_C(0x002c1198)); /* 00021400 sll v0,v0,16 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<16u));target=sx(UINT32_C(0x002c119c));goto dispatch;
L_002c119c:
 STEP(UINT32_C(0x002c119c)); /* 00021243 sra v0,v0,9 */
 set(m,2u,sx((uint32_t)((int32_t)lo(m,2u)>>9u)));target=sx(UINT32_C(0x002c11a0));goto dispatch;
L_002c11a0:
 STEP(UINT32_C(0x002c11a0)); /* 3c100059 lui s0,zero,0x59 */
 set(m,16u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c11a4));goto dispatch;
L_002c11a4:
 STEP(UINT32_C(0x002c11a4)); /* 26100840 addiu s0,s0,2112 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000840)));target=sx(UINT32_C(0x002c11a8));goto dispatch;
L_002c11a8:
 STEP(UINT32_C(0x002c11a8)); /* 02028021 addu s0,s0,v0 */
 set(m,16u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002c11ac));goto dispatch;
L_002c11ac:
 STEP(UINT32_C(0x002c11ac)); /* 12400004 beq s2,zero,002c11c0 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002c11b0));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(taken?UINT32_C(0x002c11c0):UINT32_C(0x002c11b4));goto dispatch;}
L_002c11b0:
 STEP(UINT32_C(0x002c11b0)); /* ae030010 sw v1,0x10(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002c11b4));goto dispatch;
L_002c11b4:
 STEP(UINT32_C(0x002c11b4)); /* 26040014 addiu a0,s0,20 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002c11b8));goto dispatch;
L_002c11b8:
 STEP(UINT32_C(0x002c11b8)); /* 0c0b50e9 jal 002d43a4 */
 set(m,31u,UINT64_C(0x002c11c0));STEP(UINT32_C(0x002c11bc));set(m,6u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d43a4));goto dispatch;
L_002c11bc:
 STEP(UINT32_C(0x002c11bc)); /* 0240302d daddu a2,s2,zero */
 set(m,6u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002c11c0));goto dispatch;
L_002c11c0:
 STEP(UINT32_C(0x002c11c0)); /* 26430023 addiu v1,s2,35 */
 set(m,3u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000023)));target=sx(UINT32_C(0x002c11c4));goto dispatch;
L_002c11c4:
 STEP(UINT32_C(0x002c11c4)); /* 3282ffff andi v0,s4,0xffff */
 set(m,2u,lo(m,20u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002c11c8));goto dispatch;
L_002c11c8:
 STEP(UINT32_C(0x002c11c8)); /* 00132400 sll a0,s3,16 */
 set(m,4u,sx((uint32_t)lo(m,19u)<<16u));target=sx(UINT32_C(0x002c11cc));goto dispatch;
L_002c11cc:
 STEP(UINT32_C(0x002c11cc)); /* 00031903 sra v1,v1,4 */
 set(m,3u,sx((uint32_t)((int32_t)lo(m,3u)>>4u)));target=sx(UINT32_C(0x002c11d0));goto dispatch;
L_002c11d0:
 STEP(UINT32_C(0x002c11d0)); /* 00822025 or a0,a0,v0 */
 set(m,4u,lo(m,4u)|lo(m,2u));target=sx(UINT32_C(0x002c11d4));goto dispatch;
L_002c11d4:
 STEP(UINT32_C(0x002c11d4)); /* 8382dfc0 lb v0,-0x2040(gp) */
 {uint8_t byte;READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc0),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002c11d8));goto dispatch;
L_002c11d8:
 STEP(UINT32_C(0x002c11d8)); /* 00031f00 sll v1,v1,28 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<28u));target=sx(UINT32_C(0x002c11dc));goto dispatch;
L_002c11dc:
 STEP(UINT32_C(0x002c11dc)); /* 00832025 or a0,a0,v1 */
 set(m,4u,lo(m,4u)|lo(m,3u));target=sx(UINT32_C(0x002c11e0));goto dispatch;
L_002c11e0:
 STEP(UINT32_C(0x002c11e0)); /* ae04000c sw a0,0xc(s0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002c11e4));goto dispatch;
L_002c11e4:
 STEP(UINT32_C(0x002c11e4)); /* a791dfc4 sh s1,-0x203c(gp) */
 value16=(uint16_t)lo(m,17u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc4),&value16,2u);target=sx(UINT32_C(0x002c11e8));goto dispatch;
L_002c11e8:
 STEP(UINT32_C(0x002c11e8)); /* 10400007 beq v0,zero,002c1208 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002c11ec));/* nop */target=sx(taken?UINT32_C(0x002c1208):UINT32_C(0x002c11f0));goto dispatch;}
L_002c11ec:
 STEP(UINT32_C(0x002c11ec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c11f0));goto dispatch;
L_002c11f0:
 STEP(UINT32_C(0x002c11f0)); /* 0c0b03ca jal 002c0f28 */
 set(m,31u,UINT64_C(0x002c11f8));STEP(UINT32_C(0x002c11f4));/* nop */target=sx(UINT32_C(0x002c0f28));goto dispatch;
L_002c11f4:
 STEP(UINT32_C(0x002c11f4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c11f8));goto dispatch;
L_002c11f8:
 STEP(UINT32_C(0x002c11f8)); /* 1440fffd bne v0,zero,002c11f0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002c11fc));READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002c11f0):UINT32_C(0x002c1200));goto dispatch;}
L_002c11fc:
 STEP(UINT32_C(0x002c11fc)); /* 8f82d860 lw v0,-0x27a0(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002c1200));goto dispatch;
L_002c1200:
 STEP(UINT32_C(0x002c1200)); /* 10000005 beq zero,zero,002c1218 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c1204));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002c1218):UINT32_C(0x002c1208));goto dispatch;}
L_002c1204:
 STEP(UINT32_C(0x002c1204)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1208));goto dispatch;
L_002c1208:
 STEP(UINT32_C(0x002c1208)); /* 0c0b6f74 jal 002dbdd0 */
 set(m,31u,UINT64_C(0x002c1210));STEP(UINT32_C(0x002c120c));READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbdd0));goto dispatch;
L_002c120c:
 STEP(UINT32_C(0x002c120c)); /* 8f84dfc8 lw a0,-0x2038(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002c1210));goto dispatch;
L_002c1210:
 STEP(UINT32_C(0x002c1210)); /* 8f82d860 lw v0,-0x27a0(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd860),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002c1214));goto dispatch;
L_002c1214:
 STEP(UINT32_C(0x002c1214)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1218));goto dispatch;
L_002c1218:
 STEP(UINT32_C(0x002c1218)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c121c));goto dispatch;
L_002c121c:
 STEP(UINT32_C(0x002c121c)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002c1220));goto dispatch;
L_002c1220:
 STEP(UINT32_C(0x002c1220)); /* dfb30018 ld s3,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002c1224));goto dispatch;
L_002c1224:
 STEP(UINT32_C(0x002c1224)); /* dfb40020 ld s4,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002c1228));goto dispatch;
L_002c1228:
 STEP(UINT32_C(0x002c1228)); /* dfbf0028 ld ra,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c122c));goto dispatch;
L_002c122c:
 STEP(UINT32_C(0x002c122c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1230));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002c1230:
 STEP(UINT32_C(0x002c1230)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002c1234));goto dispatch;
L_002d43a4:
 STEP(UINT32_C(0x002d43a4)); /* 0080402d daddu t0,a0,zero */
 set(m,8u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d43a8));goto dispatch;
L_002d43a8:
 STEP(UINT32_C(0x002d43a8)); /* 2cc20020 sltiu v0,a2,32 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x20)));target=sx(UINT32_C(0x002d43ac));goto dispatch;
L_002d43ac:
 STEP(UINT32_C(0x002d43ac)); /* 1440001c bne v0,zero,002d4420 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d43b0));set(m,3u,lo(m,8u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d4420):UINT32_C(0x002d43b4));goto dispatch;}
L_002d43b0:
 STEP(UINT32_C(0x002d43b0)); /* 0100182d daddu v1,t0,zero */
 set(m,3u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d43b4));goto dispatch;
L_002d43b4:
 STEP(UINT32_C(0x002d43b4)); /* 00a81025 or v0,a1,t0 */
 set(m,2u,lo(m,5u)|lo(m,8u));target=sx(UINT32_C(0x002d43b8));goto dispatch;
L_002d43b8:
 STEP(UINT32_C(0x002d43b8)); /* 3042000f andi v0,v0,0xf */
 set(m,2u,lo(m,2u) & UINT64_C(0xf));target=sx(UINT32_C(0x002d43bc));goto dispatch;
L_002d43bc:
 STEP(UINT32_C(0x002d43bc)); /* 54400019 bnel v0,zero,002d4424 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d43c0));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4424));}else target=sx(UINT32_C(0x002d43c4));goto dispatch;
L_002d43c0:
 STEP(UINT32_C(0x002d43c0)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d43c4));goto dispatch;
L_002d43c4:
 STEP(UINT32_C(0x002d43c4)); /* 0100382d daddu a3,t0,zero */
 set(m,7u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d43c8));goto dispatch;
L_002d43c8:
 STEP(UINT32_C(0x002d43c8)); /* 78a30000 lq v1,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d43cc));goto dispatch;
L_002d43cc:
 STEP(UINT32_C(0x002d43cc)); /* 24c6ffe0 addiu a2,a2,-32 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d43d0));goto dispatch;
L_002d43d0:
 STEP(UINT32_C(0x002d43d0)); /* 24a50010 addiu a1,a1,16 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d43d4));goto dispatch;
L_002d43d4:
 STEP(UINT32_C(0x002d43d4)); /* 2cc40020 sltiu a0,a2,32 */
 set(m,4u,(lo(m,6u)<UINT64_C(0x20)));target=sx(UINT32_C(0x002d43d8));goto dispatch;
L_002d43d8:
 STEP(UINT32_C(0x002d43d8)); /* 7ce30000 sq v1,0x0(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),m->gpr[3],16u);target=sx(UINT32_C(0x002d43dc));goto dispatch;
L_002d43dc:
 STEP(UINT32_C(0x002d43dc)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d43e0));goto dispatch;
L_002d43e0:
 STEP(UINT32_C(0x002d43e0)); /* 78a20000 lq v0,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x002d43e4));goto dispatch;
L_002d43e4:
 STEP(UINT32_C(0x002d43e4)); /* 24a50010 addiu a1,a1,16 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d43e8));goto dispatch;
L_002d43e8:
 STEP(UINT32_C(0x002d43e8)); /* 7ce20000 sq v0,0x0(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),m->gpr[2],16u);target=sx(UINT32_C(0x002d43ec));goto dispatch;
L_002d43ec:
 STEP(UINT32_C(0x002d43ec)); /* 1080fff6 beq a0,zero,002d43c8 */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x002d43f0));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x002d43c8):UINT32_C(0x002d43f4));goto dispatch;}
L_002d43f0:
 STEP(UINT32_C(0x002d43f0)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d43f4));goto dispatch;
L_002d43f4:
 STEP(UINT32_C(0x002d43f4)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d43f8));goto dispatch;
L_002d43f8:
 STEP(UINT32_C(0x002d43f8)); /* 14400009 bne v0,zero,002d4420 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d43fc));set(m,3u,lo(m,7u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d4420):UINT32_C(0x002d4400));goto dispatch;}
L_002d43fc:
 STEP(UINT32_C(0x002d43fc)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d4400));goto dispatch;
L_002d4400:
 STEP(UINT32_C(0x002d4400)); /* dca30000 ld v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d4404));goto dispatch;
L_002d4404:
 STEP(UINT32_C(0x002d4404)); /* 24c6fff8 addiu a2,a2,-8 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d4408));goto dispatch;
L_002d4408:
 STEP(UINT32_C(0x002d4408)); /* 24a50008 addiu a1,a1,8 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d440c));goto dispatch;
L_002d440c:
 STEP(UINT32_C(0x002d440c)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d4410));goto dispatch;
L_002d4410:
 STEP(UINT32_C(0x002d4410)); /* fce30000 sd v1,0x0(a3) */
 value64=lo(m,3u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d4414));goto dispatch;
L_002d4414:
 STEP(UINT32_C(0x002d4414)); /* 1040fffa beq v0,zero,002d4400 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d4418));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d4400):UINT32_C(0x002d441c));goto dispatch;}
L_002d4418:
 STEP(UINT32_C(0x002d4418)); /* 24e70008 addiu a3,a3,8 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d441c));goto dispatch;
L_002d441c:
 STEP(UINT32_C(0x002d441c)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d4420));goto dispatch;
L_002d4420:
 STEP(UINT32_C(0x002d4420)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4424));goto dispatch;
L_002d4424:
 STEP(UINT32_C(0x002d4424)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4428));goto dispatch;
L_002d4428:
 STEP(UINT32_C(0x002d4428)); /* 10c20008 beq a2,v0,002d444c */
 {int taken=(lo(m,6u)==lo(m,2u));STEP(UINT32_C(0x002d442c));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d444c):UINT32_C(0x002d4430));goto dispatch;}
L_002d442c:
 STEP(UINT32_C(0x002d442c)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d4430));goto dispatch;
L_002d4430:
 STEP(UINT32_C(0x002d4430)); /* 90a20000 lbu v0,0x0(a1) */
 {uint8_t byte;READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002d4434));goto dispatch;
L_002d4434:
 STEP(UINT32_C(0x002d4434)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4438));goto dispatch;
L_002d4438:
 STEP(UINT32_C(0x002d4438)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d443c));goto dispatch;
L_002d443c:
 STEP(UINT32_C(0x002d443c)); /* a0620000 sb v0,0x0(v1) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d4440));goto dispatch;
L_002d4440:
 STEP(UINT32_C(0x002d4440)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4444));goto dispatch;
L_002d4444:
 STEP(UINT32_C(0x002d4444)); /* 14c4fffa bne a2,a0,002d4430 */
 {int taken=(lo(m,6u)!=lo(m,4u));STEP(UINT32_C(0x002d4448));/* nop */target=sx(taken?UINT32_C(0x002d4430):UINT32_C(0x002d444c));goto dispatch;}
L_002d4448:
 STEP(UINT32_C(0x002d4448)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d444c));goto dispatch;
L_002d444c:
 STEP(UINT32_C(0x002d444c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d4450));set(m,2u,lo(m,8u)+lo(m,0u));goto dispatch;
L_002d4450:
 STEP(UINT32_C(0x002d4450)); /* 0100102d daddu v0,t0,zero */
 set(m,2u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d4454));goto dispatch;
L_002dbdd0:
 STEP(UINT32_C(0x002dbdd0)); /* 24030033 addiu v1,zero,51 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000033)));target=sx(UINT32_C(0x002dbdd4));goto dispatch;
L_002dbdd4:
 m->pc=UINT32_C(0x002dbdd4); /* Unexecuted SYS, counted only by router. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbdd8:
 STEP(UINT32_C(0x002dbdd8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbddc));/* nop */goto dispatch;
L_002dbddc:
 STEP(UINT32_C(0x002dbddc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbde0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}
