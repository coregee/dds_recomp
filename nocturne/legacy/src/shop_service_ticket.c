/* Eight complete original service-ticket/prize/phase bodies,SLUS_209.11.
 * Real retail tables,RNG,item/Hearts/script/process/formatter callees remain.
 * HD UI additions and managed guards are not imported. */
#include "shop_service_ticket.h"
#include "shop_transaction.h"
#include "shop_navigation.h"
#include "shop_payment_controller.h"
#include "libc_printf.h"
#include "compiler_numeric.h"
#include "nocturne.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveShopServiceTicketAddress(a);
#else
 return(void *)(uintptr_t)a;
#endif
}
static uint32_t r8(uint32_t a){return*(uint8_t *)at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sb(uint32_t v){return v&128u?(v&255u)|0xffffff00u:v&255u;}
static uint64_t sx(uint32_t v){return v>>31?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t work(void){return r32(0x551f34);}
static uint64_t start(uint32_t procedure){uint32_t s=work();return ps2ShopScriptStart_00213B48(sx(r32(s+0x238c)),procedure,sx(s+0x2390));}
uint64_t ps2ShopTicketAdjust_002088D0(uint64_t amount)
{
 datAddItem(0x3d,si((uint32_t)amount));return r8(r32(0x54ea20)+0x1965);
}
uint64_t ps2ShopTicketDraw_002088F8(uint64_t box)
{
 uint32_t records[8],count=0,total=0,p=0x32fbc8u+((uint32_t)box<<5);
 for(unsigned i=0;i<8;++i,p+=4){
  uint16_t item=(uint16_t)r16(p+2);int8_t heart=fclChkItemHearts(item);
  if(heart&&cmbChkGetHearts(heart))continue;
  if(!item)continue;
  uint32_t record=r32(p);records[count++]=record;total+=record&255u;
 }
 uint32_t value=sdfGetRand(NULL);
 /* Original advances real RNG before the native BEQL/BREAK7. The three
  * unmodified retail boxes have total100;that fact is not a source guard. */
 if(!total)nocturneCompilerArithmeticTrap(7u);
 uint32_t choice=value%total,cumulative=0;
 for(uint32_t i=0;i<count;++i){cumulative+=records[i]&255u;if(choice<cumulative)return records[i]>>16;}
 return 0;
}
uint64_t ps2ShopFacilityByteRead_002143F8(uint64_t index)
{
 uint32_t i=sb((uint32_t)index);if(si(i)>=16)i=15;
 return sx(sb(r8(0x5749a0u+i*4u)));
}
void ps2ShopTicketExit_00208A40(void)
{
 ps2ShopCursorListEnd_00242238(sx(work()+0x2c));w8(work()+5,1);
 uint64_t process=start(10);uint32_t s=work();w8(s+1,4);w32(s+8,(uint32_t)process);
}
void ps2ShopTicketPrizeStart_00209500(void)
{
 w8(work()+5,1);uint64_t process=start(12);uint32_t s=work();w8(s+1,11);w32(s+8,(uint32_t)process);
}
void ps2ShopTicketOffer_00209548(void)
{
 (void)ps2LibcPrintf(0x53d080,sx(r32(work()+0x20)));
 ps2ShopCursorListEnd_00242238(sx(work()+0x2c));ps2ShopSignalClear_00214398(4);ps2ShopSignalClear_00214398(5);
 (void)ps2ShopFacilityValue_002143C8(4,ps2ShopTicketDraw_002088F8(0));
 (void)ps2ShopFacilityValue_002143C8(5,ps2ShopTicketDraw_002088F8(1));
 (void)ps2ShopFacilityValue_002143C8(6,ps2ShopTicketDraw_002088F8(2));
 if(sb(r8(work()+0x19))==1&&!evtBitCheck(0x931)){ps2ShopTicketExit_00208A40();return;}
 if(si(r32(work()+0x20))>=1000){
  (void)ps2ShopTicketAdjust_002088D0(1);w8(work()+5,1);uint64_t process=start(11);
  uint32_t s=work();w8(s+1,10);w32(s+8,(uint32_t)process);
 }else if(ps2ShopTicketAdjust_002088D0(0)>=10)ps2ShopTicketPrizeStart_00209500();
 else ps2ShopTicketExit_00208A40();
}
void ps2ShopTicketCountUpdate_00209680(void)
{
 if(ps2ShopSequenceStatus_002427F8(sx(work()))!=2)return;
 if(ps2ShopTicketAdjust_002088D0(0)>=10)ps2ShopTicketPrizeStart_00209500();else ps2ShopTicketExit_00208A40();
}
void ps2ShopTicketAwardUpdate_002096D8(void)
{
 if(ps2ShopSequenceStatus_002427F8(sx(work()))!=2)return;
 uint64_t flag4=ps2ShopSignalCheck_002143B0(4),flag5=ps2ShopSignalCheck_002143B0(5);
 uint32_t index=flag5?6:flag4?5:4;
 uint16_t item=(uint16_t)ps2ShopFacilityByteRead_002143F8(index);int8_t heart=fclChkItemHearts(item);
 if(heart)(void)datAddHearts(heart);else datAddItem(item,1);
 (void)ps2ShopTicketAdjust_002088D0(UINT64_C(0xfffffffffffffff6));ps2ShopTicketExit_00208A40();
}
