/* Complete original shop list/price/quantity bodies, SLUS_209.11.
 * Native words, raw64 Index sign, low8 modes and unchecked inline lists prevail.
 * Payment/script/sound scheduling and the full facility initializer are separate. */
#include "shop_transaction.h"
#include "nocturne.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveShopTransactionAddress(a);
#else
 return(void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w8(uint32_t a,uint8_t v){*(uint8_t *)at(a)=v;}
static uint32_t sb(uint32_t v){return v&0x80u?(v&255u)|0xffffff00u:v&255u;}
static uint32_t sh(uint32_t v){return v&0x8000u?(v&65535u)|0xffff0000u:v&65535u;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t work(void){return r32(0x551f2c);}
static uint32_t cursor(void){uint32_t c=work();return sh(r16(c+0x11e6))+r8(c+0x11e8);}
uint64_t ps2ShopItemId_002071E0(uint64_t index,uint64_t mode){return r16(work()+((uint32_t)index<<1)+((uint8_t)mode?0x2244u:0x2200u));}
uint64_t ps2ShopPackId_00207210(uint64_t place){
 uint32_t p=0x32f650u+(uint32_t)place*6u,event=sh(r16(p+2)),selected=0;
 if(!(event&0x80000000u))selected=evtBitCheck(si(event))!=0;
 return r8(p+4+selected);
}
uint64_t ps2ShopItemCount_00207290(uint64_t place){
 uint32_t p=0x32f682u+(uint32_t)ps2ShopPackId_00207210(place)*130u,count=0;
 for(uint32_t i=0;i<32;i++,p+=4)if(r16(p))count++;
 return sx(count);
}
uint64_t ps2ShopFacilityValue_002143C8(uint64_t index,uint64_t value){
 uint32_t i=sb((uint32_t)index);if(si(i)>=16)return 0;
 w32(0x5749a0u+i*4u,(uint32_t)value);return 1;
}
uint64_t ps2ShopCreateBuyList_002072F8(uint64_t raw){
 uint32_t c=(uint32_t)raw,p=0x32f682u+(uint32_t)ps2ShopPackId_00207210(sx(sb(r8(c+0x19))))*130u;
 w8(c+0x2240,0);w8(c+0x2241,0);
 for(uint32_t i=0;i<(uint32_t)ps2ShopItemCount_00207290(sx(sb(r8(c+0x19))));i++,p+=4){
  uint16_t item=(uint16_t)r16(p);int8_t heart=fclChkItemHearts(item);
  if(heart){if(cmbChkGetHearts(heart))continue;w8(c+0x2241,1);}
  uint32_t n=r8(c+0x2240);w8(c+0x2240,(uint8_t)(n+1));w16(c+0x2200+sb(n)*2u,item);
 }
 /* Original tailcall inherits the setter's actual raw V0 (1 for index4).
  * The HD VOID role does not establish the original source return typedef. */
 return ps2ShopFacilityValue_002143C8(4,sx(sb(r8(c+0x2241))));
}
uint64_t ps2ShopItemPrice_002073D8(uint64_t index,uint64_t mode){
 uint32_t item=(uint32_t)ps2ShopItemId_002071E0(index,mode),base=r32(0x3dc4a4u+item*8u);
 if((uint8_t)mode)return base>>1;
 uint32_t p=0x32f680u+(uint32_t)ps2ShopPackId_00207210(sx(sb(r8(work()+0x19))))*130u;
 uint32_t rate=r16(p+4u+(uint32_t)index*4u);if(!rate)rate=r16(p);
 uint32_t price=(base*rate)/100u;
 /* MFLO1 after DIVU1 transports its unsigned low32 lane; the later
  * word ADDU in the times3 branch sign-extends the wrapped word. */
 return evtBitCheck(0xaf2)?price:sx(price*3u);
}
uint64_t ps2ShopAffordableQuantity_002074C0(uint64_t index,uint64_t mode){
 uint32_t selected=index>>63?cursor():(uint32_t)index;
 uint64_t price=ps2ShopItemPrice_002073D8(sx(selected),mode);uint32_t quantity=0xffffffffu;
 if(index>>63)w32(work()+0x1c,sb(r8(work()+0x24))*(uint32_t)price);
 if(!(uint8_t)mode&&price&&!(price>>63)){
  uint32_t money=r32(r32(0x54ea20)+0xa48);int32_t a=si(money),b=si((uint32_t)price);
  /* The native A3==0 BREAK7 slot is excluded by the preceding BLEZ.
   * ItemPrice returns a word lane, so a positive nonzero A3 has b!=0. */
  quantity=a==INT32_MIN&&b==-1?0x80000000u:(uint32_t)(a/b);
  if(si(quantity)>=100)quantity=99;
  uint32_t item=(uint32_t)ps2ShopItemId_002071E0(sx(selected),0),sum=r8(r32(0x54ea20)+0x1928+item)+quantity;
  if(si(sum)>=100)quantity=quantity-sum+99u;
 }
 return sx(sb(quantity));
}
uint64_t ps2ShopChoiceMaximum_002075B8(uint64_t index,uint64_t mode,uint64_t preserve){
 uint32_t old=r32(work()+0x1c);uint64_t quantity;
 if(!(uint8_t)mode){
  uint16_t item=(uint16_t)ps2ShopItemId_002071E0(sx(cursor()),0);int8_t heart=fclChkItemHearts(item);
  quantity=ps2ShopAffordableQuantity_002074C0(index,0);if(heart&&!(quantity>>63)&&quantity>1)quantity=1;
 }else{
  (void)ps2ShopAffordableQuantity_002074C0(index,1);
  uint32_t item=(uint32_t)ps2ShopItemId_002071E0(sx(cursor()),1);quantity=r8(r32(0x54ea20)+0x1928+item);
 }
 if((uint8_t)preserve)w32(work()+0x1c,old);return sx(sb((uint32_t)quantity));
}
uint64_t ps2ShopItemEligible_00242A18(uint64_t item,uint64_t mode){
 uint32_t p=0x3dc4a0u+((uint32_t)item&65535u)*8u;
 return(uint8_t)mode?(r8(p+1)&2u)==0:(r8(p)&1u)!=0;
}
void ps2ShopCreateInventoryList_00213C10(uint64_t raw,uint64_t mode){
 uint32_t list=(uint32_t)raw;w8(list,0);
 for(uint32_t item=1;item<160;item++)if(r8(r32(0x54ea20)+0x1928+item)&&ps2ShopItemEligible_00242A18(item,mode)){
  uint32_t n=r8(list);w8(list,(uint8_t)(n+1));w16(list+2+n*2u,(uint16_t)item);
 }
}
