#include "panel_construction.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include <string.h>
#include <stdlib.h>
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,nocturneResolvePanelConstructionAddress(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(nocturneResolvePanelConstructionAddress(a),&v,4);}
static uint32_t byte(uint32_t a){return *(uint8_t *)nocturneResolvePanelConstructionAddress(a);}
static int32_t signedHalf(uint32_t a){int16_t v;memcpy(&v,nocturneResolvePanelConstructionAddress(a),2);return v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t asr(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000u)?(~UINT32_C(0)<<(32-n)):0);}
static void xy(uint32_t p,uint32_t x,uint32_t y){put(p+4,y);put(p,x);}
/* 001cc358: include the original three-instruction prefix. */
void ps2PanelVertexNormal(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{
 uint32_t p=(uint32_t)work,x[4]={(uint32_t)a,(uint32_t)a+512,(uint32_t)c-512,(uint32_t)c};
 if((int32_t)x[2]<(int32_t)x[1])x[1]=x[2]=(uint32_t)a+asr((uint32_t)c-(uint32_t)a,1);
 for(unsigned i=0;i<4;i++){xy(p,x[i],(uint32_t)b);p+=8;put(p,x[i]);put(p+4,(uint32_t)d);p+=8;}
}
/* 001cc3d0: integer geometry with live original offset-table reads. */
void ps2PanelVertexMessage(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{
 uint32_t p=(uint32_t)work,x[4]={(uint32_t)a-256,(uint32_t)a+512,(uint32_t)c-512,(uint32_t)c+256};
 uint32_t y[4]={(uint32_t)b-128,(uint32_t)b+128,(uint32_t)d-128,(uint32_t)d+128};
 for(unsigned j=0;j<4;j++)for(unsigned i=0;i<4;i++){xy(p,x[i],y[j]);p+=8;}
 x[1]=(uint32_t)a+1024;x[2]=(uint32_t)c-1024;
 for(unsigned j=0;j<3;j++)for(unsigned i=0;i<4;i++){put(p,x[i]);put(p+4,(uint32_t)b+word(0x326508+j*4));p+=8;}
 for(unsigned j=0;j<3;j++)for(unsigned i=0;i<4;i++){put(p,x[i]);put(p+4,(uint32_t)d-word(0x326508+j*4));p+=8;}
}
/* 001cc540: selection-window coordinates, including its register-copy prefix. */
void ps2PanelVertexSelection(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{
 uint32_t p=(uint32_t)work,x[4]={(uint32_t)a-256,(uint32_t)a+512,(uint32_t)c-512,(uint32_t)c+256};
 uint32_t y[4]={(uint32_t)b-128,(uint32_t)b+128,(uint32_t)d-128,(uint32_t)d+128};
 for(unsigned j=0;j<4;j++)for(unsigned i=0;i<4;i++){xy(p,x[i],y[j]);p+=8;}
 x[1]=(uint32_t)a+1024;x[2]=(uint32_t)c-1024;
 for(unsigned j=0;j<2;j++)for(unsigned i=0;i<4;i++){xy(p,x[i],(uint32_t)b+j*8);p+=8;}
 for(unsigned j=0;j<2;j++)for(unsigned i=0;i<4;i++){xy(p,x[i],(uint32_t)d-j*8);p+=8;}
}
/* 001cc688: type three and four share this actual PS2 callback. */
void ps2PanelVertexPlain(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work;put(p,(uint32_t)a);put(p+4,(uint32_t)b);put(p+12,(uint32_t)b);put(p+8,(uint32_t)c);put(p+16,(uint32_t)c);put(p+20,(uint32_t)d);put(p+28,(uint32_t)d);put(p+24,(uint32_t)a);}
/* 001cc6b8 */
void ps2PanelVertexFacility(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work,x[3]={(uint32_t)a,(uint32_t)c-1440,(uint32_t)c};for(unsigned j=0;j<2;j++)for(unsigned i=0;i<3;i++){xy(p,x[i],j?(uint32_t)d:(uint32_t)b);p+=8;}}
/* 001cc728: fixed X coordinates and adjusted supplied Y coordinates. */
void ps2PanelVertexPera(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work+4,x[4]={416,1152,7024,7760};(void)a;(void)c;for(unsigned i=0;i<4;i++){xy(p,x[i],(uint32_t)b+352);p+=8;put(p,x[i]);put(p+4,(uint32_t)d-320);p+=8;}}
/* 001caf78: native MULT low-word wrap, signed clamp, then SRA16. */
void ps2PanelScaleColors(uint64_t out,uint64_t red,uint64_t green,uint64_t blue,uint64_t alpha,uint64_t ratios,uint64_t count)
{
 uint32_t p=(uint32_t)out,r=(uint32_t)ratios;uint64_t remaining=count;
 while((int64_t)remaining>0){uint32_t a=word(r),b=word(r+4),c=word(r+8);remaining=sx((uint32_t)remaining-1);r+=16;
  a*=(uint32_t)red;b*=(uint32_t)green;c*=(uint32_t)blue;put(p+12,(uint32_t)alpha);
  if((int32_t)a>0xff0000)a=0xff0000;if((int32_t)b>0xff0000)b=0xff0000;if((int32_t)c>0xff0000)c=0xff0000;
  put(p,asr(a,16));put(p+4,asr(b,16));put(p+8,asr(c,16));p+=16;
 }
}
static void rgba(uint32_t p,uint32_t a,uint32_t b,uint32_t c,uint32_t d){put(p+12,d);put(p,a);put(p+4,b);put(p+8,c);}
/* 001cc7a0 */
void ps2PanelColorNormal(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work;rgba(p+64,(uint32_t)a,(uint32_t)b,(uint32_t)c,0);rgba(p+80,(uint32_t)a,(uint32_t)b,(uint32_t)c,(uint32_t)d);}
/* 001cc7d0 */
void ps2PanelColorMessage(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work;rgba(p+320,(uint32_t)a,(uint32_t)b,(uint32_t)c,1);rgba(p+336,(uint32_t)a,(uint32_t)b,(uint32_t)c,(uint32_t)d);ps2PanelScaleColors(sx(p+352),a,b,c,d,0x326518,6);}
/* 001cc830 */
void ps2PanelColorSelection(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work;rgba(p+256,(uint32_t)a,(uint32_t)b,(uint32_t)c,1);rgba(p+272,(uint32_t)a,(uint32_t)b,(uint32_t)c,(uint32_t)d);ps2PanelScaleColors(sx(p+288),a,b,c,d,0x326578,4);}
/* 001cc890: first call's incoming components survive in saved registers. */
void ps2PanelColorPlain(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work;rgba(p+32,(uint32_t)a,(uint32_t)b,(uint32_t)c,(uint32_t)d);ps2PanelScaleColors(sx(p+48),a,b,c,d,0x3265b8,1);ps2PanelScaleColors(sx(p+64),a,b,c,128,0x3265c8,2);}
/* 001cc920 */
void ps2PanelColorLeftFade(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{rgba((uint32_t)work+32,(uint32_t)a,(uint32_t)b,(uint32_t)c,(uint32_t)d);}
/* 001cc938 */
void ps2PanelColorFacility(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)work;rgba(p+48,(uint32_t)a,(uint32_t)b,(uint32_t)c,0);rgba(p+64,(uint32_t)a,(uint32_t)b,(uint32_t)c,(uint32_t)d);}
/* 001cc968: the omitted callback ignores incoming color values. */
void ps2PanelColorPera(uint64_t work,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{(void)a;(void)b;(void)c;(void)d;rgba((uint32_t)work+68,115,135,255,0);put((uint32_t)work+84,115);put((uint32_t)work+88,135);put((uint32_t)work+92,255);put((uint32_t)work+96,0);}
typedef void (*PanelCallback)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static PanelCallback callback(uint32_t address)
{
 switch(address){
 case 0x1cc358:return ps2PanelVertexNormal;case 0x1cc3d0:return ps2PanelVertexMessage;case 0x1cc540:return ps2PanelVertexSelection;
 case 0x1cc688:return ps2PanelVertexPlain;case 0x1cc6b8:return ps2PanelVertexFacility;case 0x1cc728:return ps2PanelVertexPera;
 case 0x1cc7a0:return ps2PanelColorNormal;case 0x1cc7d0:return ps2PanelColorMessage;case 0x1cc830:return ps2PanelColorSelection;
 case 0x1cc890:return ps2PanelColorPlain;case 0x1cc920:return ps2PanelColorLeftFade;case 0x1cc938:return ps2PanelColorFacility;case 0x1cc968:return ps2PanelColorPera;
 default:abort();
 }
}
/* 001cc080: allocation lookup uses the raw low-word type, not its stored byte. */
uint64_t itfPnlRegist2(uint64_t type,uint64_t texture)
{
 uint32_t handle=ps2MemoryHandleAllocate(52);uint64_t result=sx(ps2MemoryHandleAcquirePointer(handle));uint32_t p=(uint32_t)result;
 *(uint8_t *)nocturneResolvePanelConstructionAddress(p+48)=(uint8_t)type;put(p,handle);
 handle=ps2MemoryHandleAllocate((int32_t)word(0x3264e0+((uint32_t)type<<2)));put(p+4,handle);
 uint32_t payload=(uint32_t)ps2MemoryHandleAcquirePointer(handle);put(p+8,payload);
 if(texture&&(type==6||type==7||type==8))put(payload,(uint32_t)texture);return result;
}
/* 001cc1a0: byte type selects the live original callback pointer. */
void itfPnlSetPosition(uint64_t panel,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t z)
{uint32_t p=(uint32_t)panel;put(p+12,(uint32_t)z);uint32_t type=byte(p+48);put(p+16,(uint32_t)a);put(p+20,(uint32_t)b);uint32_t fn=word(0x326428+type*4);put(p+24,(uint32_t)c);put(p+28,(uint32_t)d);if(fn)callback(fn)(sx(word(p+8)),a,b,c,d);}
/* 001cc270 */
void itfPnlSetColor(uint64_t panel,uint64_t a,uint64_t b,uint64_t c,uint64_t d)
{uint32_t p=(uint32_t)panel;put(p+32,(uint32_t)a);uint32_t type=byte(p+48);put(p+36,(uint32_t)b);put(p+40,(uint32_t)c);uint32_t fn=word(0x326450+type*4);put(p+44,(uint32_t)d);if(fn)callback(fn)(sx(word(p+8)),a,b,c,d);}
/* 001cfa90: existing panel is reused; type two creates type eight. */
void ps2MessageOpenPanel(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,s=p+156,m=p+36;uint64_t panel=sx(word(s+4));
 if(!panel){panel=itfPnlRegist2(signedHalf(p+18)==2?8:6,sx(word(0x56be64)));put(s+4,(uint32_t)panel);}
 uint32_t y=word(m+4),x=word(m);uint32_t a=word(s+8),b=word(s+12),c=word(s+16),d=word(s+20);uint64_t z=sx(word(p+12));
 itfPnlSetPosition(panel,sx(x+a),sx(y+b),sx(x+c),sx(y+d),z);
 panel=sx(word(s+4));uint64_t blue=sx(word(s+32)),red=sx(word(s+24)),green=sx(word(s+28));itfPnlSetColor(panel,red,green,blue,0);
 put(p,(word(p)&~UINT32_C(0x300))|0x100);
}
/* 001cfb68: speaker ownership and phase transitions preserve native ordering. */
void ps2MessageOpenSpeakerPanel(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,s=p+20,w=p+156,font=word(s+8),flags;
 if(font){flags=word(p);if(!(flags&0x10000)){
  if(!word(w)){uint32_t width=word(font+12)<<4;uint64_t panel=itfPnlRegist2(7,sx(word(0x56be64)));uint32_t x=word(s),y=word(s+4);width+=x;put(w,(uint32_t)panel);uint64_t z=sx(word(p+12));
   itfPnlSetPosition(panel,sx(x-720),sx(y-104),sx(width+720),sx(y+232),z);itfPnlSetColor(sx(word(w)),127,127,127,0);flags=word(p);
  }put(p,(flags&~UINT32_C(0x3000))|0x1000);return;
 }}
 if(word(w))put(p,word(p)|0x3000);
}
