/* Real live banks/RAM and complete native model/kernel owners. No service,
 * allocation, resource completion or later CPU/RAM state is supplied. */
#include "object_attachment.h"
#include "object_attachment_initializer.h"
#include "object_attachment_transport.h"
#include "field_movement_encounter_transport.h"
#include "native_kernel_router.h"
#include "fusion_core_transport.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
void *nocturneEffectHostAddress(uint32_t);
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void),nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t,uint64_t);
uint64_t nocturneBattleActionFormulaSecondaryLo(void),nocturneBattleActionFormulaSecondaryHi(void);
void nocturneBattleActionFormulaSecondaryWrite(uint64_t,uint64_t);
uint32_t nocturneObjectAttachmentSupportBody(uint32_t);
uint64_t nocturneObjectModel_001DD0D0(uint64_t,uint64_t);
void nocturneObjectModel_001DD220(uint64_t);
void nocturneObjectModel_001DC290(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
void nocturneObjectModel_001DD750(uint64_t);
void ps2EffectPcpModelSetPositionVu_001DD720(uint64_t);
#if defined(NOCTURNE_OBJECT_ATTACHMENT_PROBE)
__declspec(dllimport) extern uint32_t g_pathRotationVu[32][4],g_pathRotationAcc[4],g_pathRotationAccOf[4],g_scriptCoreFcsr,g_nocturnePoolStatus;
#else
extern uint32_t g_pathRotationVu[32][4],g_pathRotationAcc[4],g_pathRotationAccOf[4],g_scriptCoreFcsr,g_nocturnePoolStatus;
#endif
static NocturneWakeupMachine raw;
static NocturneWakeupStop raw_stop;
static NocturneNativeRouteCounts raw_counts;
static uint32_t spans[96][2],span_count,configured,observing;
static uint64_t raw_limit,stopped[4],telemetry[4];
static jmp_buf escape;
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return(uint64_t)q[0]|((uint64_t)q[1]<<32);}
static _Noreturn void boundary(uint32_t why,uint32_t pc,uint64_t selected){if(!observing)abort();stopped[0]=why;stopped[1]=pc;stopped[2]=selected;stopped[3]=cpu(29);longjmp(escape,1);}
void *nocturneResolveObjectAttachmentAddress(uint32_t a){return nocturneEffectHostAddress(a);}
void nocturneObjectAttachmentCpuRead(unsigned r,uint32_t q[4]){nocturneEffectHostCpuRead(r,q);}
void nocturneObjectAttachmentCpuWrite(unsigned r,const uint32_t q[4]){nocturneEffectHostCpuWrite(r,q);}
void nocturneObjectAttachmentVuRead(unsigned r,uint32_t q[4]){if(r>=32u)abort();if(r)memcpy(q,g_pathRotationVu[r],16);else{q[0]=q[1]=q[2]=0;q[3]=0x3f800000u;}}
void nocturneObjectAttachmentVuWrite(unsigned r,const uint32_t q[4]){if(r>=32u)abort();if(r)memcpy(g_pathRotationVu[r],q,16);}
void nocturneObjectAttachmentAccRead(uint32_t q[4],uint32_t of[4]){memcpy(q,g_pathRotationAcc,16);memcpy(of,g_pathRotationAccOf,16);}
void nocturneObjectAttachmentAccWrite(const uint32_t q[4],const uint32_t of[4]){memcpy(g_pathRotationAcc,q,16);memcpy(g_pathRotationAccOf,of,16);}
void nocturneObjectAttachmentMultiplyState(uint64_t p){nocturneEffectHostSetHilo((uint64_t)(int64_t)(int32_t)(uint32_t)p,(uint64_t)(int64_t)(int32_t)(uint32_t)(p>>32));}
uint32_t nocturneObjectAttachmentStackPointer(void){uint32_t sp=nocturneFusionCoreStackPointer();if(cpu(29)!=sp)abort();return sp;}
void nocturneObjectAttachmentSetStackPointer(uint32_t sp){uint32_t q[4];nocturneEffectHostCpuRead(29,q);q[0]=sp;q[1]=0;nocturneEffectHostCpuWrite(29,q);nocturneFusionCoreSetStackPointer(sp);}
static uint32_t physical(uint32_t a){if(a>=0xffff8000u)return 0x78000u+a-0xffff8000u;if(a>=0x20000000u&&a<0x22000000u)return a-0x20000000u;return a>=0x80000000u&&a<0xc0000000u?a&0x1fffffffu:a;}
static int backed(uint32_t a,uint32_t n){a=physical(a);for(uint32_t i=0;i<span_count;i++)if(a>=spans[i][0]&&a-spans[i][0]<=spans[i][1]&&n<=spans[i][1]-(a-spans[i][0]))return 1;return 0;}
static int read_ram(void *v,uint32_t a,void *p,uint32_t n){(void)v;if(!backed(a,n))return 0;a=physical(a);for(uint32_t i=0;i<n;i++)((uint8_t*)p)[i]=*(uint8_t*)nocturneEffectHostAddress(a+i);return 1;}
static int write_ram(void *v,uint32_t a,const void *p,uint32_t n){(void)v;if(!backed(a,n))return 0;a=physical(a);for(uint32_t i=0;i<n;i++)*(uint8_t*)nocturneEffectHostAddress(a+i)=((const uint8_t*)p)[i];return 1;}
static void import_banks(void){for(unsigned i=0;i<32;i++)nocturneEffectHostCpuRead(i,raw.gpr[i]);memcpy(raw.fpr,nocturneEffectHostFpr(),sizeof(raw.fpr));raw.lo=nocturneEffectHostLo();raw.hi=nocturneEffectHostHi();raw.lo1=nocturneBattleActionFormulaSecondaryLo();raw.hi1=nocturneBattleActionFormulaSecondaryHi();raw.status=g_nocturnePoolStatus;raw.fcsr=g_scriptCoreFcsr;}
static void publish_banks(void){for(unsigned i=1;i<32;i++)nocturneEffectHostCpuWrite(i,raw.gpr[i]);memcpy(nocturneEffectHostFpr(),raw.fpr,sizeof(raw.fpr));nocturneEffectHostSetHilo(raw.lo,raw.hi);nocturneBattleActionFormulaSecondaryWrite(raw.lo1,raw.hi1);g_nocturnePoolStatus=raw.status;g_scriptCoreFcsr=raw.fcsr;nocturneFusionCoreSetStackPointer(raw.gpr[29][0]);}
static int owns(void *v,uint32_t pc){(void)v;return nocturneNativeKernelOwns(pc)||(pc>=0x2dbee4u&&pc<0x2dbef0u);}
static uint32_t resume(void *v,NocturneWakeupMachine *m,const NocturneWakeupMemory *mem,uint64_t n,NocturneWakeupStop *s){
 (void)v;if(m->pc==0x2dbee4u){/* 002DBEE4:0000000C SYS;router owns genuine exception entry. */s->outcome=NOCTURNE_NATIVE_SYSCALL;s->pc=m->pc;s->address=s->bytes=0;s->target=0;return s->outcome;}
 if(m->pc==0x2dbee8u){/* 002DBEE8:03E00008 JR RA;002DBEEC:00000000 NOP. */if(n<2u){s->outcome=NOCTURNE_WAKEUP_INSTRUCTION_LIMIT;s->pc=m->pc;return s->outcome;}m->instructions+=2u;m->pc=m->gpr[31][0];s->outcome=NOCTURNE_NATIVE_TRANSFER;s->pc=m->pc;s->address=s->bytes=0;s->target=(uint64_t)(int64_t)(int32_t)m->pc;return s->outcome;}
 return nocturneNativeKernelBody(m,mem,n,s);
}
static void raw_kernel(uint32_t entry){
 const NocturneWakeupMemory mem={0,read_ram,write_ram};const NocturneNativeRouter router={0,owns,resume};uint32_t target=(uint32_t)cpu(31),outcome;
 if(!configured)boundary(6u,entry,0);import_banks();raw.pc=entry;
 outcome=nocturneNativeRouteResume(&raw,&mem,&router,raw.instructions<raw_limit?raw_limit-raw.instructions:0,target,&raw_stop,&raw_counts);publish_banks();++telemetry[0];telemetry[1]=raw_counts.syscalls;telemetry[2]=raw_counts.erets;telemetry[3]=raw.instructions;
 if(outcome!=NOCTURNE_NATIVE_TRANSFER||raw.pc!=target)boundary(13u,raw.pc,((uint64_t)outcome<<32)|target);
}
uint64_t nocturneObjectAttachmentKernel(uint64_t service,uint32_t argc,const uint64_t *args){if(argc!=1u||!args||args[0]!=cpu(4)||cpu(3)!=service||(service!=0x42u&&service!=0x44u))boundary(6u,(uint32_t)cpu(31),service);raw_kernel(service==0x42u?0x2dbec4u:0x2dbee4u);return cpu(2);}
static void field_owner(uint32_t target,uint32_t pc){if(!nocturneFieldMovementRun(target)){const uint64_t *s=nocturneFieldMovementLastStop();boundary((uint32_t)s[0],(uint32_t)s[1],s[2]);}(void)pc;}
uint64_t nocturneObjectAttachmentPoolAllocate(uint64_t bytes){if(bytes!=cpu(4))boundary(6u,(uint32_t)cpu(31),bytes);field_owner(0x2a8af8u,(uint32_t)cpu(31)-8u);return cpu(2);}
uint64_t nocturneObjectAttachmentPoolZeroed(uint64_t bytes){if(bytes!=cpu(4))boundary(6u,(uint32_t)cpu(31),bytes);if(!nocturneObjectAttachmentSupportBody(0x2a8ba8u))abort();return cpu(2);}
uint64_t nocturneObjectAttachmentResourcePump(void){boundary(3u,0x2976c0u,cpu(31));}
void nocturneObjectAttachmentCall(uint32_t target,uint32_t pc){
 (void)nocturneObjectAttachmentStackPointer();if(nocturneObjectAttachmentBody(target)||nocturneObjectAttachmentInitializerBody(target)||nocturneObjectAttachmentSupportBody(target))return;
 switch(target){
 case 0x1dd0d0u:(void)nocturneObjectModel_001DD0D0(cpu(4),cpu(5));return;
 case 0x1dd220u:nocturneObjectModel_001DD220(cpu(4));return;
 case 0x1dc290u:nocturneObjectModel_001DC290(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9));return;
 case 0x1dd750u:nocturneObjectModel_001DD750(cpu(4));return;
 case 0x1dd720u:ps2EffectPcpModelSetPositionVu_001DD720(cpu(4));return;
 default:field_owner(target,pc);return;
 }
}
uint32_t nocturneObjectAttachmentConfigure(const NocturneWakeupMachine *before,const NocturneIndexedCacheConfig *input,const uint32_t *ranges,uint32_t n,uint64_t budget){if(!before||!input||!ranges||!n||n>96u||!budget)return 0;if(!nocturneFieldMovementConfigure(before,input,ranges,n,budget))return 0;raw=*before;raw.instructions=raw.sync_p=0;memcpy(spans,ranges,(size_t)n*8);span_count=n;raw_limit=budget;memset(&raw_stop,0,sizeof(raw_stop));memset(&raw_counts,0,sizeof(raw_counts));memset(telemetry,0,sizeof(telemetry));configured=1;return 1;}
uint32_t nocturneObjectAttachmentRun(uint32_t entry){if(observing)abort();observing=1;memset(stopped,0,sizeof(stopped));if(setjmp(escape)){observing=0;return 0;}nocturneObjectAttachmentCall(entry,entry);observing=0;return 1;}
const uint64_t *nocturneObjectAttachmentLastStop(void){return stopped;}
const NocturneWakeupMachine *nocturneObjectAttachmentRawState(void){return &raw;}
const uint64_t *nocturneObjectAttachmentRouteCounts(void){return telemetry;}
