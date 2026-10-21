#include "message_commands.h"
#include "script_core.h"
#include "script_lifetime.h"
#include "script_construction.h"
#include "message_construction.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveScriptConstructionAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t instance(uint64_t id){return word(0x56be8c+(uint32_t)id*20);}
/* 00158940 is actually empty; the HD ChildHD UI implementation is different. */
void ps2MessageOptionHook(uint64_t option){(void)option;}
/* 001ce450: only the high halfword contributes to instance flags. */
void itfMesMngMarkBitStat(uint64_t id,uint64_t flag)
{uint32_t p=instance(id);put(p,word(p)|((uint32_t)flag&0xffff0000u));}
/* 001cd5b0: return one even when the current signed message ID is negative. */
uint64_t itfMesMngOpenWindow(void)
{uint64_t id=scrGetMessageHandle();if(!(id>>63)){itfMesMngMarkBitStat(id,0x200000);ps2MessageOptionHook(2);}return 1;}
/* 001cd670: retain the snapshot for phase tests, then reload after real cleanup. */
void itfMesMngMsgWndCls(uint64_t id)
{
 uint32_t p=instance(id),flags=word(p);
 if(flags&0x300)put(p,flags|0x300);
 if(flags&0x3000)put(p,word(p)|0x3000);
 itfMesMngRequestMessageRelease(id,1);itfMesMngRequestSelectRelease(id);
 put(p,word(p)&0xffdfffffu);
}
/* 001cd5f8: completion is based on the phase observed before cleanup. */
uint64_t itfMesMngCloseWindow(void)
{
 uint64_t id=scrGetMessageHandle();if(id>>63)return 1;
 uint32_t phase=word(instance(id))&0x300;
 if(phase==0x100||phase==0x200){itfMesMngMsgWndCls(id);ps2MessageOptionHook(3);}
 return phase==0;
}
/* 001cf178: eight-byte resource records; HD GetFRQString is a different role. */
uint64_t ps2MessageGetResourceEntry(uint64_t p,uint64_t index)
{return sx(word((uint32_t)p+4)+0x20+((uint32_t)index<<3));}
/* 001cf1a8: LH is read even for a negative page, as in the branch delay slot. */
uint64_t GetMessagePagePtr(uint64_t resource,uint64_t page)
{
 uint32_t p=(uint32_t)resource,h=half(p+0x18);
 int32_t count=(int32_t)(h&32767)-(int32_t)(h&32768);
 if((page>>63)||((int64_t)page>=(int64_t)count))return 0;
 return sx(word(p+0x1c+((uint32_t)page<<2)));
}
/* 001c9230,001cf440: live ascending copies also preserve overlapping tables. */
void frSetVariableRequest(uint64_t index,uint64_t value){put(0x56bbd0+((uint32_t)index<<2),(uint32_t)value);}
void CommitVarTable(uint64_t table)
{uint32_t p=(uint32_t)table;for(uint32_t i=0;i<32;i++,p+=4)frSetVariableRequest(i,sx(word(p)));}
/* 001c9220: signed LW AND a full-width raw mask; high return lanes matter. */
uint64_t ps2FontTestGlobalFlags(uint64_t mask){return sx(word(0x54f404))&mask;}
/* 001ce510: no bounds or null checks in the native slot/local-variable lookup. */
uint64_t itfMesMngGetVarLocalize(uint64_t id,uint64_t index)
{return sx(word(instance(id)+0xc4+((uint32_t)index<<2)));}
/* 001cf490: type-header helper and native speaker pointer array. */
uint64_t GetSpeakerName(uint64_t pointer)
{uint32_t p=(uint32_t)pointer,h=(uint32_t)ps2MessageGetTypeHeader2(sx(word(p+4)));return sx(word(word(h)+(half(p+0x20)<<2)));}
/* 001cf710: preserve raw input lanes when the first request is already last. */
uint64_t GetLastLinkFontHandle(uint64_t font)
{uint32_t next=word((uint32_t)font+0x24);while(next){font=sx(next);next=word((uint32_t)font+0x24);}return font;}
/* 001cf748: source reads stay ordered/live when records overlap. */
void GetLastMessagePara(uint64_t font,uint64_t message)
{uint32_t f=(uint32_t)font,m=(uint32_t)message;uint8_t speed=*at(f);uint32_t layout=word(f+0x20);*at(m+0x15)=speed>>1;*at(m+0x12)=*at(layout+0x15);*at(m+0x13)=*at(layout+0x14);*at(m+0x14)=*at(layout+0x16);}
/* 001cf7e0,001c7b30,001c7a60,001cfa00: native linked font controls. */
void ChangeZBuffer(uint64_t font,uint64_t z)
{while(font){uint32_t f=(uint32_t)font;put(f+0x14,(uint32_t)z);font=sx(word(f+0x24));}}
void frSetDrawPosition(uint64_t font,uint64_t x,uint64_t y)
{uint32_t f=(uint32_t)font;put(f+8,(uint32_t)y);put(f+4,(uint32_t)x);}
void frSetDrawSpeed(uint64_t font,uint64_t speed)
{uint32_t v=((uint32_t)speed&255)*2;*at((uint32_t)font)=(uint8_t)(v>128?128:v);}
void RaiseMessageSpeedMax(uint64_t font)
{while(font){uint32_t f=(uint32_t)font;if(!*at(word(f+0x1c)+0x16))frSetDrawSpeed(font,128);font=sx(word(f+0x24));}}
