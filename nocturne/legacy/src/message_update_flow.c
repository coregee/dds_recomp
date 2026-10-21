#include "message_update_flow.h"
#include "message_update_support.h"
#include "message_frame_draw.h"
#include "message_commands.h"
#include "message_construction.h"
#include "message_request.h"
#include "font_parser_support.h"
#include "panel_construction.h"
#include "sound_bank_flow.h"
#include "script_construction.h"
#include <string.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static int32_t signedHalf(uint32_t a){int16_t v;memcpy(&v,at(a),2);return v;}
static int32_t signedByte(uint32_t a){return *(int8_t *)at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 001cff98: the four native updates run in this order. */
void ps2MessageCalcFlow(uint64_t instance)
{
 ps2MessageCalcWindow(instance);
 ps2MessageCalcMessage(instance);
 ps2MessageCalcSelect(instance);
 ps2MessageCalcCursor(instance);
}
/* 001d0118: native page completion, input gating and real page reconstruction. */
void ps2MessageCalcMessage(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,m=p+0x24;
 if(signedByte(m+0x10)!=1)return;
 uint32_t flags=word(p);
 if((flags&7)==4){
  uint32_t count=word(p+0x1cc)+1;sw(p+0x1cc,count);
  if(flags&0x800000){*(uint8_t *)at(m+0x10)=255;return;}
  if(!(flags&0x100000))*(uint8_t *)at(p+0x1c4)=1;
  uint32_t result=*(uint8_t *)at(m+0x11);
  if(signedByte(0x2f5831)>=0&&signedByte(0x2f5833)>=0&&
     (signedByte(0x2f5832)==0||count<5)&&result)return;
  if(result)(void)ps2SoundPlay(9,127,63);
  itfMesInitializeCurCtr(sx(p+0x1c4),0);
  uint32_t next=(half(m+0x18)+1)&65535;sh(m+0x18,next);
  int32_t signedNext=next&32768?(int32_t)next-65536:(int32_t)next;
  if(signedNext>=signedHalf(m+0x1a)){*(uint8_t *)at(m+0x10)=255;return;}
  CommitVarTable(sx(p+0xc4));
  uint32_t binding=word(p+8);if(binding)ps2FontBindMessageStyle(sx(binding));
  ps2MessageReady(instance);ps2MessageOpenSpeakerPanel(instance);
  sw(p,(word(p)&~UINT32_C(7))|3);
 }else if((signedByte(0x2f5831)<0||signedByte(0x2f5833)<0||signedByte(0x2f5832)!=0)&&!(flags&0x400000)){
  ps2MessageRaiseSpeedAll(sx(word(m+0xc)));
  uint32_t font=word(p+0x1c);if(font)frSetDrawSpeed(sx(font),128);
 }
}
/* 001d02c0: retain entry flags across selection callbacks; reload live flags for stores. */
void ps2MessageCalcSelect(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,s=p+0x40,m=p+0x24,flags=word(p);
 switch(signedHalf(s+0x10)){
 case 1:{
  uint32_t top=word(s+4)-((uint32_t)signedHalf(s+0x16)*160-160);
  uint32_t bottom=word(m+4)+(uint32_t)signedHalf(m+0x16)*160;
  uint32_t font=word(m+0xc);
  if(font&&(int32_t)top<(int32_t)bottom){ps2MessageSlide(instance,sx((uint32_t)-64));return;}
  if((flags&0xc00)==0x400)return;
  if(font){ps2MessageChangeFontColorAll(sx(font),3);flags=word(p);}
  sh(s+0x10,2);sw(p,(flags&~UINT32_C(0x38))|0x18);return;
 }
 case 2:
  if((flags&0x38)!=0x20||ps2MessageSelectItem(instance)!=1)return;
  sw(s+8,(uint32_t)ps2MessageUnchainFontUnit(sx(word(s+8)),sx((uint32_t)signedHalf(s+0x12)),sx((uint32_t)signedHalf(s+0x16))));
  if((flags&0xc00)==0x800)sw(p,word(p)|0xc00);
  sh(s+0x12,(uint32_t)ps2MessageGetMaskedIndex(sx((uint32_t)signedHalf(s+0x12)),sx(word(s+0xc))));
  sh(s+0x1a,0);ps2MessageForceCursor(sx(p+0x1c4),1,127,0);
  sh(s+0x10,3);sw(p,(word(p)&~UINT32_C(0x38))|0x28);sh(s+0x18,128);return;
 case 3:{
  uint32_t alpha=(half(s+0x18)-16)&65535;sh(s+0x18,alpha);
  if(!alpha||(alpha&32768)){sh(s+0x18,0);sh(s+0x10,4);itfMesInitializeCurCtr(sx(p+0x1c4),0);}
  ps2MessageChangeFontAlpha(sx(word(s+8)),sx((uint32_t)signedHalf(s+0x18)));return;
 }
 case 4:
  if(!word(m+0xc)||(int32_t)word(m+4)>=0xa88){sh(s+0x10,65535);return;}
  ps2MessageSlide(instance,64);return;
 default:return;
 }
}
/* 001d05f0: up consumes the direction test, then confirm precedes default keys. */
uint64_t ps2MessageSelectItem(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,s=p+0x40,up=*(uint8_t *)at(0x2f5836);int32_t direction=0;
 if(up&2){if(signedHalf(s+0x12)!=0||(up&128))direction=-1;}
 else{uint32_t down=*(uint8_t *)at(0x2f5837);if((down&2)&&(signedHalf(s+0x12)!=signedHalf(s+0x16)-1||(down&128)))direction=1;}
 if(direction){ps2MessageSelectItemMove(sx(s),sx((uint32_t)direction));itfMesInitializeCurCtr(sx(p+0x1c4),1);}
 if(signedByte(0x2f5831)<0){(void)ps2SoundPlay(8,127,63);return 1;}
 if(signedHalf(s+0x1a)<=0)return 0;
 uint64_t key=ps2MessageSelectDefaultKey(sx(s));if(key&UINT64_C(0x8000000000000000))return 0;
 (void)ps2SoundPlay(8,127,63);
 uint64_t index=sx((uint32_t)signedHalf(s+0x12));if(key==index)return 1;
 ps2MessageMarkSelectionText(sx(word(s+8)),index,sx((uint32_t)signedHalf(s+0x16)),0);
 ps2MessageMarkSelectionText(sx(word(s+8)),key,sx((uint32_t)signedHalf(s+0x16)),1);
 sh(s+0x12,(uint32_t)key);sh(s+0x14,(uint32_t)key);return 1;
}
/* 001d0740: direction is signed in the full original 64-bit register. */
void ps2MessageSelectItemMove(uint64_t selection,uint64_t direction)
{
 uint32_t s=(uint32_t)selection,index=(uint32_t)signedHalf(s+0x12);
 ps2MessageMarkSelectionText(sx(word(s+8)),sx(index),sx((uint32_t)signedHalf(s+0x16)),0);
 if(direction&UINT64_C(0x8000000000000000)){
  --index;if((int32_t)index<0)index=(uint32_t)signedHalf(s+0x16)-1;
 }else{++index;if((int32_t)index>=signedHalf(s+0x16))index=0;}
 ps2MessageMarkSelectionText(sx(word(s+8)),sx(index),sx((uint32_t)signedHalf(s+0x16)),1);
 sh(s+0x14,index);sh(s+0x12,index);(void)ps2SoundPlay(1,127,63);
}
/* 001d0ff8: next is loaded after the complete update of each node payload. */
uint64_t ps2MessageCalcManager(void)
{
 uint32_t node=word(0x56be70);
 while(node){ps2MessageCalcFlow(sx(word(node+0xc)));node=word(node+4);}
 return 0;
}
