#include "panel_draw.h"
#include "script_construction.h"
#include "deferred_drain.h"
#include "packet_builders.h"
#include "dev_packets.h"
#include "libc_stream.h"
#include <stdlib.h>
#include <string.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t asr(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000u)?(~UINT32_C(0)<<(32-n)):0);}
static uint64_t pair(uint32_t lo,uint32_t hi){return (uint64_t)lo|((uint64_t)hi<<32);}
/* 002ab0d8 / 002ab0e8: adjacent getters retain full register qwords. */
uint64_t ps2TextureGetFilterRegister(uint64_t texture){return quad(word((uint32_t)texture+40)+16);}
uint64_t ps2TextureGetWrapRegister(uint64_t texture){return quad(word((uint32_t)texture+40)+48);}
/* 002b9c18 */
uint64_t ps2PanelTexturePacketSize(void){return 80;}
/* 002b9c20: three AD values, selected GS context, untouched DMA padding. */
uint64_t ps2PanelBuildTexturePacket(uint64_t dst,uint64_t texture,uint64_t context)
{
 uint32_t p=(uint32_t)dst;sd(p+24,14);sh(p,4);sd(p+16,UINT64_C(0x1000000000008003));sw(p+12,0x50000004);sw(p+8,0);
 uint64_t v=ps2TextureGetFilterRegister(texture);sd(p+40,sx((uint32_t)context+20));sd(p+32,v);
 v=ps2TextureGetRegister(texture);sd(p+56,sx((uint32_t)context+6));sd(p+48,v);
 v=ps2TextureGetWrapRegister(texture);sd(p+72,sx((uint32_t)context+8));sd(p+64,v);return dst;
}
/* 002b9cc8 */
uint64_t ps2PanelAppendTexturePacket(uint64_t chain,uint64_t texture,uint64_t context)
{uint32_t p=ps2WorkBufferTake((uint32_t)ps2PanelTexturePacketSize());ps2PanelBuildTexturePacket(sx(p),texture,context);ps2DmaChainAppend((uint32_t)chain,p);return sx(p);}
/* 002b9d38 */
uint64_t ps2PanelBuildInlineBytePacket(uint64_t dst,uint64_t bytes)
{ps2DrawInitializeInlineRegisterPacket((uint32_t)dst,sx(asr((uint32_t)bytes,4)-2));return dst;}
/* 002b9d68 */
uint64_t ps2PanelPackedPacketSize(uint64_t registers,uint64_t loops)
{return sx((((uint32_t)registers*(uint32_t)loops)+2)<<4);}
/* 002b9d78 */
uint64_t ps2PanelPacketPayload(uint64_t packet){return sx((uint32_t)packet+32);}
/* 002b9d80: raw64 tag lanes; only the low DMA count halfword is written. */
uint64_t ps2PanelBuildPackedTag(uint64_t dst,uint64_t primitive,uint64_t registers,uint64_t descriptor,uint64_t loops)
{
 uint32_t p=(uint32_t)dst,n=(uint32_t)registers*(uint32_t)loops+1;
 sd(p+16,(registers<<60)|loops|(primitive<<47)|UINT64_C(0x400000008000));sd(p+24,descriptor);sw(p+12,n|0x50000000);sh(p,(uint16_t)n);sw(p+8,0);return dst;
}
static void coloredVertex(uint32_t out,uint32_t v,uint32_t c,uint32_t vi,uint32_t ci,uint32_t depth)
{
 uint32_t va=v+(*(uint8_t *)at(vi))*8,ca=c+(*(uint8_t *)at(ci))*16;
 uint32_t x=word(va)+0x7000,y=word(va+4)+0x7900,a=word(ca+12),g=word(ca+4),r=word(ca),b=word(ca+8);
 sd(out,pair(r,g));sd(out+8,pair(b,a));sd(out+24,depth);sd(out+16,pair(x,y));
}
/* 001cb250: exactly four vertices, including the native decrement delay slot. */
void ps2PanelDrawColoredFan4(uint64_t v,uint64_t c,uint64_t vi,uint64_t ci,uint64_t depth,uint64_t chain)
{
 uint32_t p=ps2WorkBufferTake((uint32_t)ps2PanelPackedPacketSize(2,4));ps2PanelBuildPackedTag(sx(p),0x4d,2,0x51,4);uint32_t out=(uint32_t)ps2PanelPacketPayload(sx(p));
 for(unsigned i=0;i<4;i++)coloredVertex(out+i*32,(uint32_t)v,(uint32_t)c,(uint32_t)vi+i,(uint32_t)ci+i,(uint32_t)depth);
 ps2DmaChainAppend((uint32_t)chain,p);
}
static void indexed(uint64_t v,uint64_t c,uint64_t vi,uint64_t ci,uint64_t count,uint64_t depth,uint64_t chain,int strip)
{
 uint64_t loops=strip?sx(asr((uint32_t)count,1)):count;uint64_t registers=strip?4:2;
 uint32_t p=ps2WorkBufferTake((uint32_t)ps2PanelPackedPacketSize(registers,loops));ps2PanelBuildPackedTag(sx(p),strip?0x4c:0x14a,registers,strip?0x5151:0x51,loops);
 uint32_t out=(uint32_t)ps2PanelPacketPayload(sx(p));
 if((int64_t)count>0){uint64_t remaining=count;do{remaining=sx((uint32_t)remaining-1);coloredVertex(out,(uint32_t)v,(uint32_t)c,(uint32_t)vi,(uint32_t)ci,(uint32_t)depth);out+=32;vi=sx((uint32_t)vi+1);ci=sx((uint32_t)ci+1);}while(remaining);}
 ps2DmaChainAppend((uint32_t)chain,p);
}
/* 001cb8d8 / 001cba28 */
void ps2PanelDrawColoredStrip(uint64_t v,uint64_t c,uint64_t vi,uint64_t ci,uint64_t n,uint64_t z,uint64_t chain){indexed(v,c,vi,ci,n,z,chain,1);}
void ps2PanelDrawColoredLineStrip(uint64_t v,uint64_t c,uint64_t vi,uint64_t ci,uint64_t n,uint64_t z,uint64_t chain){indexed(v,c,vi,ci,n,z,chain,0);}
/* 001cb4c8: cached coordinates and ordered live UV/color reads before stores. */
void ps2PanelDrawTexturedSprite(uint64_t rect,uint64_t uv,uint64_t color,uint64_t depth,uint64_t texture,uint64_t context,uint64_t chain)
{
 uint32_t p=ps2WorkBufferTake((uint32_t)ps2PanelPackedPacketSize(5,1));ps2PanelBuildPackedTag(sx(p),sx(((uint32_t)context<<9)|0x156),5,0x53531,1);
 uint32_t r=(uint32_t)rect,c=(uint32_t)color,u=(uint32_t)uv;
 uint32_t x0=word(r)+0x7000,y1=word(r+12)+0x7900,y0=word(r+4)+0x7900,x1=word(r+8)+0x7000,out=(uint32_t)ps2PanelPacketPayload(sx(p));
 uint32_t green=word(c+4),alpha=word(c+12),red=word(c);sd(out+72,(uint32_t)depth);uint32_t blue=word(c+8),v1=word(u+12),v0=word(u+4);
 sd(out,pair(red,green));uint32_t u0=word(u),u1=word(u+8);sd(out+8,pair(blue,alpha));sd(out+16,pair(u0,v0));sd(out+32,pair(x0,y0));sd(out+48,pair(u1,v1));sd(out+64,pair(x1,y1));sd(out+40,(uint32_t)depth);
 ps2PanelAppendTexturePacket(sx((uint32_t)chain),sx((uint32_t)texture),sx((uint32_t)context));ps2DmaChainAppend((uint32_t)chain,p);
}
/* 001cb648: the untextured sprite retains UV lanes and its different store order. */
void ps2PanelDrawSprite(uint64_t rect,uint64_t uv,uint64_t color,uint64_t depth,uint64_t context,uint64_t chain)
{
 uint32_t p=ps2WorkBufferTake((uint32_t)ps2PanelPackedPacketSize(5,1));ps2PanelBuildPackedTag(sx(p),sx(((uint32_t)context<<9)|0x15e),5,0x53531,1);
 uint32_t r=(uint32_t)rect,c=(uint32_t)color,u=(uint32_t)uv,x0=word(r)+0x7000,x1=word(r+8)+0x7000,y1=word(r+12)+0x7900,y0=word(r+4)+0x7900,out=(uint32_t)ps2PanelPacketPayload(sx(p));
 uint32_t alpha=word(c+12),v0=word(u+4),v1=word(u+12),green=word(c+4),blue=word(c+8),u0=word(u);sd(out+72,(uint32_t)depth);uint32_t red=word(c),u1=word(u+8);
 sd(out+32,pair(x0,y0));sd(out+64,pair(x1,y1));sd(out+40,(uint32_t)depth);sd(out,pair(red,green));sd(out+8,pair(blue,alpha));sd(out+16,pair(u0,v0));sd(out+48,pair(u1,v1));ps2DmaChainAppend((uint32_t)chain,p);
}
/* 001cbd30 */
void ps2PanelAppendAlphaPacket(uint64_t chain,uint64_t type,uint64_t context)
{uint32_t p=ps2WorkBufferTake(48);ps2PanelBuildInlineBytePacket(sx(p),48);uint64_t v=quad(0x3263c0+((uint32_t)type<<3));sd(p+32,v);sd(p+40,context?0x43:0x42);ps2DmaChainAppend((uint32_t)chain,p);}
/* 001cc9a0 */
void ps2PanelDrawNormal(uint64_t panel,uint64_t chain)
{uint32_t p=(uint32_t)panel,w=word(p+8),c=w+64;sw(c+28,word(p+44));for(unsigned i=0;i<3;i++)ps2PanelDrawColoredFan4(sx(w),sx(c),0x3265f8+i*4,0x326608+i*4,sx(word(p+12)),chain);}
static void window(uint64_t panel,uint64_t chain,int selection)
{
 uint32_t p=(uint32_t)panel,w=word(p+8),alpha=word(p+44),c=w+(selection?256:320);
 for(unsigned i=0;i<(selection?5u:7u);i++)sw(c+28+i*16,alpha);
 for(unsigned i=0;i<3;i++)ps2PanelDrawColoredStrip(sx(w),sx(c),(selection?0x326660:0x326618)+i*8,(selection?0x326678:0x326630)+i*8,8,sx(word(p+12)),chain);
 for(unsigned i=0;i<(selection?2u:6u);i++)ps2PanelDrawColoredLineStrip(sx(w+128+i*32),sx(c),selection?0x54f488:0x54f480,(selection?0x326690:0x326648)+i*4,4,sx(word(p+12)),chain);
}
/* 001cca50 / 001ccb60 */
void ps2PanelDrawMessage(uint64_t p,uint64_t c){window(p,c,0);}
void ps2PanelDrawSelection(uint64_t p,uint64_t c){window(p,c,1);}
/* 001ccc70: layer geometry is indexed from one 96-byte local array. */
void ps2PanelDrawPlain(uint64_t panel,uint64_t chain)
{
 uint32_t p=(uint32_t)panel,w=word(p+8),c=w+32,geometry[24];
 for(unsigned i=0;i<3;i++)for(unsigned j=0;j<8;j++){uint32_t offset=(j&1)?i*8:i*16;int subtract=j==2||j==4||j==5||j==7;geometry[i*8+j]=subtract?word(w+j*4)-offset:word(w+j*4)+offset;}
 uint32_t local=nocturneLibcStreamLocalAddress(geometry,sizeof geometry);ps2PanelDrawColoredFan4(sx(w),sx(c),0x54f490,0x54f498,sx(word(p+12)),chain);
 for(unsigned i=0;i<3;i++)ps2PanelDrawColoredLineStrip(sx(local),sx(c),0x3266a0+i*5,0x3266b0+i*5,5,sx(word(p+12)),chain);
 nocturneLibcStreamEndLocal();
}
/* 001ccdb8 */
void ps2PanelDrawLeftFade(uint64_t panel,uint64_t chain)
{uint32_t p=(uint32_t)panel,w=word(p+8),c=w+32;sw(c+12,word(p+44));ps2PanelDrawColoredFan4(sx(w),sx(c),0x54f4a0,0x54f4a8,sx(word(p+12)),chain);}
/* 001ccdf0 */
void ps2PanelDrawFacility(uint64_t panel,uint64_t chain)
{uint32_t p=(uint32_t)panel,w=word(p+8),c=w+48;sw(c+28,word(p+44));ps2PanelAppendAlphaPacket(chain,2,0);ps2PanelDrawColoredStrip(sx(w),sx(c),0x54f4b0,0x54f4b8,6,sx(word(p+12)),chain);ps2PanelAppendAlphaPacket(chain,0,0);}
static void vertical(uint32_t p,uint32_t w,uint64_t chain,uint32_t cut,uint32_t threshold)
{
 uint32_t y0=word(p+20),y1=word(p+28),a=y0+cut,b=y1-cut;
 if((int32_t)(y1-y0)<(int32_t)threshold){ps2PanelDrawTexturedSprite(sx(p+16),0x3264d0,sx(p+32),sx(word(p+12)),sx(word(w)),0,chain);return;}
 uint32_t rect[4]={word(p+16),y0,word(p+24),a},local=nocturneLibcStreamLocalAddress(rect,sizeof rect);
 ps2PanelDrawTexturedSprite(sx(local),0x3264a0,sx(p+32),sx(word(p+12)),sx(word(w)),0,chain);rect[1]=a;rect[3]=b;
 ps2PanelDrawTexturedSprite(sx(local),0x3264b0,sx(p+32),sx(word(p+12)),sx(word(w)),0,chain);rect[1]=b;rect[3]=word(p+28);
 ps2PanelDrawTexturedSprite(sx(local),0x3264c0,sx(p+32),sx(word(p+12)),sx(word(w)),0,chain);nocturneLibcStreamEndLocal();
}
/* 001cce78 */
void ps2PanelDrawMessage2(uint64_t panel,uint64_t chain){uint32_t p=(uint32_t)panel;vertical(p,word(p+8),chain,0x458,0x8b1);}
/* 001ccfb0: native right-section X endpoints are reversed. */
void ps2PanelDrawSpeaker2(uint64_t panel,uint64_t chain)
{
 uint32_t p=(uint32_t)panel,left=word(p+16)+0x3e0,right=word(p+24)-0x3e0,rect[4]={word(p+16),word(p+20),left,word(p+28)},local=nocturneLibcStreamLocalAddress(rect,sizeof rect);
 ps2PanelDrawTexturedSprite(sx(local),0x3266c0,sx(p+32),sx(word(p+12)),sx(word(word(p+8))),0,chain);
 rect[0]=left;rect[1]=word(p+20);rect[2]=right;rect[3]=word(p+28);ps2PanelDrawSprite(sx(local),0x3266d0,sx(p+32),sx(word(p+12)),0,chain);
 rect[2]=right;rect[0]=word(p+24);rect[1]=word(p+20);rect[3]=word(p+28);ps2PanelDrawSprite(sx(local),0x3266c0,sx(p+32),sx(word(p+12)),0,chain);nocturneLibcStreamEndLocal();
}
/* 001cd0c8 */
void ps2PanelDrawPera(uint64_t panel,uint64_t chain)
{uint32_t p=(uint32_t)panel,w=word(p+8),c=w+68;sw(c+28,asr(word(p+44)<<5,7));for(unsigned i=0;i<3;i++)ps2PanelDrawColoredFan4(sx(w+4),sx(c),0x3266e0+i*4,0x3266f0+i*4,sx(word(p+12)),chain);vertical(p,w,chain,0x2b4,0x569);}
/* 001cc328: select the actual live original callback table. */
void itfPnlDraw(uint64_t panel,uint64_t chain)
{
 uint32_t type=*(uint8_t *)at((uint32_t)panel+48),fn=word(0x326478+type*4);
 switch(fn){case 0x1cc9a0:ps2PanelDrawNormal(panel,chain);break;case 0x1cca50:ps2PanelDrawMessage(panel,chain);break;case 0x1ccb60:ps2PanelDrawSelection(panel,chain);break;case 0x1ccc70:ps2PanelDrawPlain(panel,chain);break;case 0x1ccdb8:ps2PanelDrawLeftFade(panel,chain);break;case 0x1ccdf0:ps2PanelDrawFacility(panel,chain);break;case 0x1cce78:ps2PanelDrawMessage2(panel,chain);break;case 0x1ccfb0:ps2PanelDrawSpeaker2(panel,chain);break;case 0x1cd0c8:ps2PanelDrawPera(panel,chain);break;default:abort();}
}
