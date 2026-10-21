/* Complete native successful-negotiation phases and their actual20-target
 * dispatcher. Host transport maps original nonnull table pointers to real C
 * bodies; unsupported/null targets abort, never return an invented result. */
#include "negotiation_ok.h"
#include "negotiation_flow.h"
#include "negotiation_fullmoon.h"
#include "nocturne.h"
#include "libc_printf.h"
#include <stdlib.h>
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveNegotiationOkAddress(a);
#else
 return(void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t i32(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static int less(uint32_t a,uint32_t b){return(a^0x80000000u)<(b^0x80000000u);}
static uint32_t race(uint32_t c){return(uint32_t)datGetRace((datUnitWork_PS2 *)at(r32(c+0x15c)));}
static void queue(uint64_t c,uint32_t id){(void)ps2NegotiationFlowQueue_0026A8A0(c,id);}
static uint32_t window(uint32_t c){return r32(c+0x1b0+r32(c+0x184)*4u);}
static void message(uint64_t c,uint32_t w,uint32_t id,uint32_t phase){(void)ps2NegotiationFlowMessage_0026A998(c,sx(w),id,phase);}
static void parent_flag(uint32_t c){uint32_t p=r32(c+4)+4;w32(p,r32(p)|8u);}
uint64_t ps2NegotiationOkFlow9_1_00272718(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x90002);queue(raw,0x9000b);queue(raw,0x90013);queue(raw,0x6004a);w32(c+0x74,0x60015);
 if(race(c)!=0x17&&race(c)!=0x16&&race(c)!=0x15)w32(c+0x90,r32(c+0x90)+1u);
 if(r32(c+0x12c)==0&&less(1,r32(c+0x8c))&&r32(c+0x90)==1&&evtBitCheck(8)&&
    r16(r32(c+0x15c)+4)!=0x5c&&r16(r32(c+0x15c)+4)!=0x61&&sdfGetRandInt(NULL,10)<8){w32(c+0x1c,r32(c+0x30));return 0;}
 ps2NegoCameraTarget_001B1810(sx(r32(c+0x16c)));uint32_t mode=r32(c+0x12c),offset;
 if(less(mode,6)){if(less(mode,1)){if(mode)return 0;offset=0x24;}else offset=0x28;}
 else{if(mode!=6)return 0;offset=0x2c;}w32(c+0x1c,r32(c+offset));return 0;
}
uint64_t ps2NegotiationOkFlow9_2_00272888(uint64_t raw){uint32_t c=(uint32_t)raw,p=r32(c+0x18);
 if(p==0)w32(c+0x10,(uint32_t)ps2NegoYesMotion_0026BE40(raw,sx(r32(c+0x16c))));
 else if(p==1){queue(raw,0x90003);message(raw,window(c),0xa7,0);}return 0;}
uint64_t ps2NegotiationOkFlow9_3_00272908(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x90004);queue(raw,0x90006);int full=datCheckStockFull();w32(c+0x1c,r32(c+(full?0x28u:0x24u)));return 0;}
uint64_t ps2NegotiationOkFlow9_4_00272960(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x90005);queue(raw,0x90009);
 (void)ps2LibcPrintf(0x5450e0,sx((uint32_t)datGetPlayerLevel()),(uint64_t)r16(r32(c+0x15c)+0x14));
 uint32_t level=(uint32_t)datGetPlayerLevel();w32(c+0x1c,r32(c+(less(level,r16(r32(c+0x15c)+0x14))?0x28u:0x24u)));return 0;}
uint64_t ps2NegotiationOkFlow9_5_002729E8(uint64_t raw){uint32_t c=(uint32_t)raw;parent_flag(c);queue(raw,0x90007);message(raw,r32(c+0x328),2,0);return 0;}
uint64_t ps2NegotiationOkFlow9_6_00272A40(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x9000a);message(raw,window(c),0xab,0);return 0;}
uint64_t ps2NegotiationOkFlow9_7_00272A90(void){return 9;}
uint64_t ps2NegotiationOkFlow9_9_00272A98(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x9000a);message(raw,window(c),0xac,0);return 0;}
uint64_t ps2NegotiationOkFlow9_10_00272AE8(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0xa001d);message(raw,window(c),0xad,0);return 0;}
uint64_t ps2NegotiationOkFlow9_11_00272B38(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x9000d);queue(raw,0x90010);
 uint32_t mode=r32(c+0x12c),offset;
 switch(mode){case 1:case 5:offset=0x24;break;case 2:offset=0x24+sdfGetRandInt(NULL,2)*4u;break;case 3:case 4:offset=0x28;break;default:w32(c+0x12c,1);return 0;}
 w32(c+0x1c,r32(c+offset));return 0;}
uint64_t ps2NegotiationOkFlow9_13_00272BE8(uint64_t raw){uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
 if(phase==0)w32(c+0x10,(uint32_t)ps2NegoYesMotion_0026BE40(raw,sx(r32(c+0x16c))));
 else if(phase==1){queue(raw,0x9000e);uint32_t amount=(uint32_t)ps2NegotiationOkMoneyReward_0026AB80(raw,sx(r32(c+0x158)),sx(r32(c+0x15c)));w32(c+0x1a0,amount);
  if(r32(c+0x130)==0x191)w32(c+0x1a0,(uint32_t)(i32(amount*3u)/2));
  ps2NegoSetMoneyVariable_0026A918(sx(window(c)),sx(r32(c+0x1a0)));message(raw,window(c),0xa8,0);}return 0;}
uint64_t ps2NegotiationOkFlow9_14_00272CB8(uint64_t raw){uint32_t c=(uint32_t)raw;parent_flag(c);queue(raw,0x9000f);ps2NegoSetMoneyVariable_0026A918(sx(r32(c+0x328)),sx(r32(c+0x1a0)));message(raw,r32(c+0x328),3,0);return 0;}
uint64_t ps2NegotiationOkFlow9_15_00272D18(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0xa001c);datAddMaka(i32(r32(c+0x1a0)));
 if(r32(c+0x130)==0x191){uint32_t p=r32(0x54ea20)+0x1ca8+*(uint8_t *)at(0x3497c4u+r16(r32(c+0x15c)+4)*60u);uint8_t v=*(uint8_t *)at(p);if(v!=255)*(uint8_t *)at(p)=(uint8_t)(v+1u);}return 0;}
uint64_t ps2NegotiationOkFlow9_16_00272DA0(uint64_t raw){uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
 if(phase==1){w32(c+0x10,(uint32_t)ps2NegoYesMotion_0026BE40(raw,sx(r32(c+0x16c))));return 0;}
 if(phase==2){queue(raw,0x90011);ps2NegotiationOkItemVariable_0026A938(sx(window(c)),sx(r32(c+0x1a4)));message(raw,window(c),0xa9,0);return 0;}
 if(phase)return 0;
 uint32_t special=r32(c+0x12c)==3,item=(uint32_t)(special?ps2NegotiationOkItemRewardB_0026BB48(sx(r32(c+0x15c))):ps2NegotiationOkItemRewardA_0026BA28(sx(r32(c+0x15c))));
 w32(c+0x1a4,item?item:(special?0x6au:6u));
 if(datCheckItemFull((int32_t)r32(c+0x1a4))){ps2NegotiationOkItemVariable_0026A938(sx(window(c)),sx(r32(c+0x1a4)));message(raw,window(c),0x97,0);
  w32(c+0x1a0,(uint32_t)ps2NegotiationOkMoneyReward_0026AB80(raw,sx(r32(c+0x158)),sx(r32(c+0x15c))));queue(raw,0x9000e);}return 0;}
uint64_t ps2NegotiationOkFlow9_17_00272F08(uint64_t raw){uint32_t c=(uint32_t)raw;parent_flag(c);queue(raw,0x90012);ps2NegotiationOkItemVariable_0026A938(sx(r32(c+0x328)),sx(r32(c+0x1a4)));message(raw,r32(c+0x328),5,0);return 0;}
uint64_t ps2NegotiationOkFlow9_18_00272F68(uint64_t raw){queue(raw,0xa001c);datAddItem((int32_t)r32((uint32_t)raw+0x1a4),1);return 0;}
uint64_t ps2NegotiationOkFlow9_19_00272FA8(uint64_t raw){uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
 if(phase==0)w32(c+0x10,(uint32_t)ps2NegoYesMotion_0026BE40(raw,sx(r32(c+0x16c))));
 else if(phase==1){queue(raw,0x90014);message(raw,window(c),0xaa,0);}return 0;}
uint64_t ps2NegotiationOkFlow9_20_00273028(uint64_t raw){uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
 if(phase==0||phase==1)message(raw,window(c),phase?0x113u:0x112u,phase);
 else if(phase==2){w32(c+0x1a8,r32(c+0x58)?2u:0u);queue(raw,0x90015);}return 0;}
uint64_t ps2NegotiationOkFlow9_21_002730D8(uint64_t raw){uint32_t c=(uint32_t)raw;parent_flag(c);queue(raw,0x90016);w32(c+0x1ac,(uint32_t)ps2NegotiationOkInfoSelect_0026BBD8(sx(r32(c+0x1a8))));return 0;}
uint64_t ps2NegotiationOkFlow9_22_00273128(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0xa001c);message(raw,r32(c+0x2ac+r32(c+0x184)*4u),r32(c+0x1ac),0);return 0;}
uint64_t ps2NegotiationOkDispatch_00273178(uint64_t raw){
 uint32_t target=r32(0x4ef698u+r16((uint32_t)raw+0x14)*4u);
#if UINTPTR_MAX > UINT32_MAX
 switch(target){
#define CASE(A,N) case A:return N(raw)
 CASE(0x272718,ps2NegotiationOkFlow9_1_00272718);CASE(0x272888,ps2NegotiationOkFlow9_2_00272888);
 CASE(0x272908,ps2NegotiationOkFlow9_3_00272908);CASE(0x272960,ps2NegotiationOkFlow9_4_00272960);
 CASE(0x2729e8,ps2NegotiationOkFlow9_5_002729E8);CASE(0x272a40,ps2NegotiationOkFlow9_6_00272A40);
 case 0x272a90:return ps2NegotiationOkFlow9_7_00272A90();CASE(0x272a98,ps2NegotiationOkFlow9_9_00272A98);
 CASE(0x272ae8,ps2NegotiationOkFlow9_10_00272AE8);CASE(0x272b38,ps2NegotiationOkFlow9_11_00272B38);
 CASE(0x272be8,ps2NegotiationOkFlow9_13_00272BE8);CASE(0x272cb8,ps2NegotiationOkFlow9_14_00272CB8);
 CASE(0x272d18,ps2NegotiationOkFlow9_15_00272D18);CASE(0x272da0,ps2NegotiationOkFlow9_16_00272DA0);
 CASE(0x272f08,ps2NegotiationOkFlow9_17_00272F08);CASE(0x272f68,ps2NegotiationOkFlow9_18_00272F68);
 CASE(0x272fa8,ps2NegotiationOkFlow9_19_00272FA8);CASE(0x273028,ps2NegotiationOkFlow9_20_00273028);
 CASE(0x2730d8,ps2NegotiationOkFlow9_21_002730D8);CASE(0x273128,ps2NegotiationOkFlow9_22_00273128);
#undef CASE
 default:abort();}
#else
 return((uint64_t(*)(uint64_t))(uintptr_t)target)(raw);
#endif
}
