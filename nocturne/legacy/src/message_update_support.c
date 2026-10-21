#include "message_update_support.h"
#include "message_commands.h"
#include "message_frame_draw.h"
#include "panel_construction.h"
#include "script_construction.h"
#include "script_lifetime.h"
#include <string.h>
#include <stdlib.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static int32_t signedHalf(uint32_t a){int16_t v;memcpy(&v,at(a),2);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 001cc1e8: cached inputs, original table lookup, then ordered native stores. */
void itfPnlSetPositionOffset(uint64_t panel,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t z)
{
 uint32_t p=(uint32_t)panel,type=*(uint8_t *)at(p+48),x0=word(p+16),y0=word(p+20),x1=word(p+24);
 x0+=(uint32_t)a;uint32_t y1=word(p+28);y0+=(uint32_t)b;uint32_t depth=word(p+12);x1+=(uint32_t)c;
 uint32_t fn=word(0x326428+type*4);y1+=(uint32_t)d;depth+=(uint32_t)z;
 sw(p+16,x0);sw(p+12,depth);sw(p+20,y0);sw(p+24,x1);sw(p+28,y1);
 if(!fn)return;
 uint64_t work=sx(word(p+8));a=sx(x0);b=sx(y0);c=sx(x1);d=sx(y1);
 switch(fn){
 case 0x1cc358:ps2PanelVertexNormal(work,a,b,c,d);break;
 case 0x1cc3d0:ps2PanelVertexMessage(work,a,b,c,d);break;
 case 0x1cc540:ps2PanelVertexSelection(work,a,b,c,d);break;
 case 0x1cc688:ps2PanelVertexPlain(work,a,b,c,d);break;
 case 0x1cc6b8:ps2PanelVertexFacility(work,a,b,c,d);break;
 case 0x1cc728:ps2PanelVertexPera(work,a,b,c,d);break;
 default:abort();
 }
}
/* 001cf5f0: recycle all requests outside the selected Y group and repair tails. */
uint64_t ps2MessageUnchainFontUnit(uint64_t font,uint64_t index,uint64_t lines)
{
 uint64_t current=font;uint32_t y=word((uint32_t)current+8),remaining=(uint32_t)lines-(uint32_t)index-1;
 while((int32_t)remaining>0){
  for(;;){
   uint32_t p=(uint32_t)current;uint64_t next=sx(word(p+36));sw(p+40,0);sw(p+44,p);sw(p+36,0);(void)frDestroyFontRequestAfter(current);current=next;
   if(!current)return 0;
   uint32_t nextY=word((uint32_t)current+8);if(nextY!=y){y=nextY;break;}
  }
  --remaining;
 }
 uint64_t first=current,last=current,next;
 for(;;){next=sx(word((uint32_t)last+36));if(!next)break;if(word((uint32_t)next+8)!=y)break;last=next;}
 while(next){uint32_t p=(uint32_t)next;uint64_t following=sx(word(p+36));sw(p+40,0);sw(p+44,p);sw(p+36,0);(void)frDestroyFontRequestAfter(next);next=following;}
 sw((uint32_t)first+40,0);sw((uint32_t)last+36,0);
 for(current=first;current;current=sx(word((uint32_t)current+36)))sw((uint32_t)current+44,(uint32_t)last);
 return first;
}
/* 001cf7a8: both coordinates are read before either store. */
void ps2MessageChangeFontPosition(uint64_t font,uint64_t x,uint64_t y)
{while(font){uint32_t p=(uint32_t)font,a=word(p+4),b=word(p+8);sw(p+4,a+(uint32_t)x);sw(p+8,b+(uint32_t)y);font=sx(word(p+36));}}
/* 001cf8b8 / 001cf910: alpha OR uses the full supplied low word. */
void ps2MessageChangeFontColorAll(uint64_t font,uint64_t color)
{while(font){uint32_t p=(uint32_t)font,t=word(p+28);while(t){*(uint8_t *)at(t+20)=(uint8_t)color;t=word(t+40);}font=sx(word(p+36));}}
void ps2MessageChangeFontAlpha(uint64_t font,uint64_t alpha)
{while(font){uint32_t p=(uint32_t)font,t=word(p+28);while(t){sw(t+16,(word(t+16)&0xffffff00)|(uint32_t)alpha);t=word(t+40);}font=sx(word(p+36));}}
/* 001cf9b0: first zero bit consumes an ADDIU before testing the index. */
uint64_t ps2MessageGetMaskedIndex(uint64_t index,uint64_t mask)
{
 uint32_t i=0,m=(uint32_t)mask;int first=1;
 for(;;){
  if(!(m&1)){index=sx((uint32_t)index-1);if((int64_t)index<0)return sx(i);}
  ++i;m>>=1;if(!first&&i>=32)return sx(i);first=0;
  if(i>=32)return sx(i);
 }
}
/* 001cfa50 / 001cfd78 */
void ps2MessageRaiseSpeedAll(uint64_t font)
{while(font){frSetDrawSpeed(font,128);font=sx(word((uint32_t)font+36));}}
void ps2MessageForceCursor(uint64_t cursor,uint64_t phase,uint64_t alpha,uint64_t expansion)
{uint32_t p=(uint32_t)cursor;sh(p+6,(uint32_t)expansion);sh(p+2,(uint32_t)phase);sh(p+4,(uint32_t)alpha);}
/* 001cffd0: native speaker fades still update alpha and release owned panels. */
void ps2MessageCalcWindow(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,flags=word(p),panel=word(p+160),phase=flags&0x300;
 if(phase==0x100){uint32_t alpha=word(panel+44)+24;sw(panel+44,alpha);uint32_t maximum=word(p+192);if((int32_t)alpha<(int32_t)maximum)flags=word(p);else{sw(panel+44,maximum);flags=(word(p)&0xfffffcf8)|0x203;sw(p,flags);}}
 else if(phase==0x300){uint32_t alpha=word(panel+44)-8;sw(panel+44,alpha);if((int32_t)alpha>0)flags=word(p);else{sw(panel+44,0);flags=word(p)&0xfffffcff;sw(p,flags);}}
 panel=word(p+156);phase=flags&0x3000;
 if(phase==0x1000){uint32_t alpha=word(panel+44)+32;sw(panel+44,alpha);if((int32_t)alpha>=200){sw(panel+44,200);sw(p,(word(p)&0xffffcfff)|0x2000);}}
 else if(phase==0x3000){uint32_t alpha=word(panel+44)-32;sw(panel+44,alpha);if((int32_t)alpha<=0){sw(panel+44,0);sw(p,word(p)&0xffffcfff);itfPnlRelease(sx(panel));sw(p+156,0);}}
}
/* 001d0518: scroll message, both panels and any speaker request. */
void ps2MessageSlide(uint64_t instance,uint64_t y)
{
 uint32_t p=(uint32_t)instance;uint32_t coord=word(p+40),font=word(p+48);sw(p+40,coord+(uint32_t)y);ps2MessageChangeFontPosition(sx(font),0,y);
 uint32_t panel=word(p+160);if(panel)itfPnlSetPositionOffset(sx(panel),0,y,0,0,0);
 panel=word(p+156);if(panel)itfPnlSetPositionOffset(sx(panel),0,y,0,y,0);
 font=word(p+28);if(font){sw(p+24,word(p+24)+(uint32_t)y);ps2MessageChangeFontPosition(sx(font),0,y);}
}
/* 001d07f0: signed trigger bytes, native mask shifts and first eligible key. */
uint64_t ps2MessageSelectDefaultKey(uint64_t selection)
{
 uint32_t p=(uint32_t)selection;int32_t count=signedHalf(p+26);uint32_t key=p+28;
 for(int32_t i=0;i<count;i++,key+=4){int32_t input=signedHalf(key);if(*(int8_t *)at(0x2f5830+(uint32_t)input)>=0)continue;int32_t bit=signedHalf(key+2);uint32_t mask=word(p+12),index=0;while(bit>0){index+=(mask&1)==0;mask>>=1;--bit;}if(!(mask&1))return sx(index);}
 return UINT64_MAX;
}
/* 001d0880: compare sign-extended SH results, including short overflow. */
void ps2MessageCalcCursor(uint64_t instance)
{
 uint32_t p=(uint32_t)instance+452;uint32_t flags=*(uint8_t *)at(p);if(!flags)return;
 if(signedHalf(p+6)>0)sh(p+6,half(p+6)-8);
 int32_t phase=signedHalf(p+2);
 if(!phase){uint32_t a=half(p+4)+8;sh(p+4,a);if((int16_t)a>=255){sh(p+2,1);sh(p+6,128);sh(p+4,255);}}
 else if(phase==1){uint32_t a=half(p+4)-8,minimum=flags&1?32:64;sh(p+4,a);if((int16_t)a<=(int32_t)minimum){sh(p+4,minimum);sh(p+2,0);}}
}
/* 001189d0 / 001d1038: real no-op pause check and native list/counter order. */
uint64_t ps2MessageDrawPauseCheck(void){return 0;}
uint64_t ps2MessageDrawManager(void)
{if(!ps2MessageDrawPauseCheck()){uint32_t n=word(0x56be70);while(n){ps2MessageDrawFlow(sx(word(n+12)));n=word(n+4);}sw(0x56be68,word(0x56be68)+1);}return 0;}
