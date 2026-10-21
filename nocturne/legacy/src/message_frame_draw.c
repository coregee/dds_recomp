#include "message_frame_draw.h"
#include "panel_draw.h"
#include "script_construction.h"
#include "deferred_drain.h"
#include "libc_stream.h"
#include <string.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t byte(uint32_t a){return *(uint8_t *)at(a);}
static int32_t signedByte(uint32_t a){return *(int8_t *)at(a);}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static int32_t signedHalf(uint32_t a){int16_t v;memcpy(&v,at(a),2);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){memcpy(at(a),&v,1);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t asr(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000u)?(~UINT32_C(0)<<(32-n)):0);}
static uint64_t pair(uint32_t lo,uint32_t hi){return (uint64_t)lo|((uint64_t)hi<<32);}
static void submit(uint64_t ot,uint64_t tag){nocturneInvokeMessageDrawOrder(word((uint32_t)ot+16),ot,tag);}
static uint64_t ordering(uint32_t index){return sx(0x2f5f18+(index<<5));}
/* 001c6338: the final word OR retains its sign-extended high lane. */
uint64_t ps2FontSwapColorBytes(uint64_t value)
{uint32_t v=(uint32_t)value;return sx((v>>24)|((v>>8)&0xff00)|((v&0xff00)<<8)|(v<<24));}
/* 001c6438: first eight register arguments and three signed LW stack words. */
void ps2FontCreateDrawPacket(uint64_t x,uint64_t y,uint64_t width,uint64_t height,uint64_t colorIndex,uint64_t color,uint64_t depth,uint64_t mode,uint64_t uv,uint64_t params,uint64_t ot)
{
 uint32_t x0=(uint32_t)x+0x7000,y0=(uint32_t)y+0x7900,meta=(uint32_t)params,u=(uint32_t)uv;
 uint64_t rgba=ps2FontSwapColorBytes(color);uint32_t p=ps2WorkBufferTake(144);
 sd(p+48,(mode<<5)|(mode<<6));sw(p,0x70000008);sw(p+12,0x50000008);sd(p+16,UINT64_C(0x10af400000000003));sd(p+24,14);sd(p+56,20);sw(p+4,0);sw(p+8,0);
 uint32_t h=word(meta+12),palette=word(0x56bba8+(((uint32_t)colorIndex&255)<<2)),w=word(meta+4),extra=word(meta+20),base=word(meta+16);
 uint64_t tex=(uint64_t)base|UINT64_C(0x8000000000000000)|((uint64_t)w<<26)|UINT64_C(0x400000000)|((uint64_t)extra<<14)|0x1400000|((uint64_t)h<<30)|((uint64_t)palette<<37);
 sd(p+40,6);sd(p+72,8);sd(p+80,UINT64_C(0x3400000000008002));sd(p+88,0x413);sd(p+32,tex);sd(p+64,0);
 uint32_t uvY1=word(u+12),uvX1=word(u+8);uint64_t z=sx((uint32_t)depth)<<32;rgba=(rgba&UINT64_C(0xffffffff))|UINT64_C(0x3f80000000000000);
 uint32_t x1=(x0+((uint32_t)width<<4))&65535,y1=(y0+((uint32_t)height<<4))<<16;
 sd(p+112,(uint64_t)(x1|y1)|z);sd(p+104,rgba);sd(p+96,sx((uvY1<<16)|uvX1));uint32_t uvY0=word(u+4),uvX0=word(u);
 sd(p+128,rgba);sd(p+136,(uint64_t)((x0&65535)|(y0<<16))|z);sd(p+120,sx((uvY0<<16)|uvX0));
 uint32_t tag=ps2WorkBufferTake(32);ps2DmaChainInitialize(tag);ps2DmaChainAppend(tag,p);submit(ordering((uint32_t)ot),sx(tag));
}
/* 001c7cb8: native fade denominator fallback24 and scale22, signed spacing. */
uint64_t frDrawEffect(uint64_t font,uint64_t text,uint64_t alphaDelay,uint64_t drawSpeed)
{
 uint32_t f=(uint32_t)font,t=(uint32_t)text,previous=word(t+36),previousAlpha=128,previousType=0;
 if(!previous){uint32_t next=word(f+36);if(next){previous=word(next+32);if(previous)previousType=byte(previous+22);else{next=word(next+36);if(next){previous=word(next+32);if(previous)previousType=byte(previous+22);}}}}
 if(previous)previousAlpha=byte(previous+16);
 uint32_t speed=(uint32_t)drawSpeed&255;int advance=(previousType==0||previousType==byte(t+22))?previousAlpha>=((uint32_t)alphaDelay&255):previousAlpha==128;
 if(advance){if(speed<128){uint32_t denominator=word(t+12)+(uint32_t)signedByte(f+1);if(!denominator)denominator=24;speed=(uint32_t)((int32_t)(speed*22)/(int32_t)denominator)&255;}
  uint32_t a=word(t+16);if((128-(a&255))<speed)a=(a&0xffffff00)|128;else a+=speed;sw(t+16,a);
 }
 uint32_t bob=0;if(signedByte(t+16)>=0&&byte(t+22)==1)bob=0-(((half(t+2)*2)%5-2)<<4);return sx(bob);
}
/* 001c7e38: follow the display list at root+2C, then FRQ+28/TEXT+28. */
uint64_t frDrawFontEx2(uint64_t font,uint64_t mode,uint64_t ot)
{
 if(!font)return 0;uint32_t f=word((uint32_t)font+44),total=0;int complete=1;
 for(;f;f=word(f+40)){
  uint32_t t=word(f+28),x=word(f+4),y=word(f+8);int32_t spacing=signedByte(f+1);sw(0x54f428,0);
  for(;t;){uint32_t dx=0,dy=0;if((int8_t)mode==0)dx=(uint32_t)frDrawEffect(sx(f),sx(t),28,byte(f));uint32_t code=half(t);
   if(byte(t+21)<2){if(code>=65&&code<91){dx+=word(0x326278+(code-65)*4);dy=word(0x326210+(code-65)*4);}else if(code>=97&&code<123){dx+=word(0x3262e0+(code-97)*4);dy=word(0x326348+(code-97)*4);}}
   uint32_t reference=word(t+32);uint32_t uv=word((reference?reference:word(t+28))+8)+4;
   ps2FontCreateDrawPacket(sx(x+word(t+4)+dx),sx(y+word(t+8)+dy),byte(t+24),byte(t+25)>>1,byte(t+20),sx(word(t+16)),sx(word(f+20)),1,sx(uv),0x56bb90,ot);
   sw(0x54f428,word(0x54f428)+1);uint32_t alpha=byte(t+16);if(alpha)sh(t+2,(uint16_t)(half(t+2)+1));if(alpha<128)complete=0;
   uint32_t advance=(word(t+12)+(uint32_t)spacing)<<4;t=word(t+40);x+=advance;
  }total+=word(f+24);
 }return complete?sx(total):0;
}
/* 001c7e00 / 001c7e18 */
uint64_t frDrawFont(uint64_t font){return frDrawFontEx(font,0);}
uint64_t frDrawFontEx(uint64_t font,uint64_t mode){return frDrawFontEx2(font,sx((uint32_t)(int32_t)(int8_t)mode),sx(word(0x54f420)));}
/* 001cb7b0: no UV lanes, register descriptor551. */
void ps2PanelDrawFlatSprite(uint64_t rect,uint64_t color,uint64_t depth,uint64_t context,uint64_t chain)
{
 uint32_t p=ps2WorkBufferTake((uint32_t)ps2PanelPackedPacketSize(3,1));ps2PanelBuildPackedTag(sx(p),sx(((uint32_t)context<<9)|0x46),3,0x551,1);uint32_t out=(uint32_t)ps2PanelPacketPayload(sx(p)),r=(uint32_t)rect,c=(uint32_t)color;
 uint32_t red=word(c),x0=word(r)+0x7000,alpha=word(c+12),green=word(c+4),y0=word(r+4)+0x7900,blue=word(c+8),x1=word(r+8)+0x7000,y1=word(r+12)+0x7900;
 sd(out+8,pair(blue,alpha));sd(out,pair(red,green));sd(out+16,pair(x0,y0));sd(out+24,(uint32_t)depth);sd(out+40,(uint32_t)depth);sd(out+32,pair(x1,y1));ps2DmaChainAppend((uint32_t)chain,p);
}
/* 001cd270 */
void ps2PanelAppendDrawState(uint64_t chain)
{uint32_t p=ps2WorkBufferTake(64);ps2PanelBuildInlineBytePacket(sx(p),64);sd(p+32,0x5101b);sd(p+40,0x47);sd(p+56,0x42);sd(p+48,0x44);ps2DmaChainAppend((uint32_t)chain,p);}
/* 001cc2b8: the original dispatcher fills a fresh32-byte chain descriptor. */
void ps2PanelSubmitDraw(uint64_t panel,uint64_t ot)
{uint32_t tag=ps2WorkBufferTake(32);ps2DmaChainInitialize(tag);ps2PanelAppendDrawState(sx(tag));itfPnlDraw(panel,sx(tag));submit(ot,sx(tag));}
/* 001cf818: skip distinct Y groups, then mark every text in the chosen group. */
void ps2MessageMarkSelectionText(uint64_t font,uint64_t first,uint64_t last,uint64_t mode)
{
 uint32_t f=(uint32_t)font,y=word(f+8),remaining=(uint32_t)last-(uint32_t)first-1;
 while((int32_t)remaining>0){do{f=word(f+36);if(!f)return;}while(word(f+8)==y);y=word(f+8);remaining--;}
 do{uint32_t t=word(f+28);while(t){sb(t+20,(uint8_t)mode);t=word(t+40);}f=word(f+36);}while(f&&word(f+8)==y);
}
/* 001d1108: four corners and five indexed line-strip vertices. */
void ps2MessageDebugDrawWindow(uint64_t panel)
{
 uint32_t p=(uint32_t)panel,x0=word(p+16),y0=word(p+20),x1=word(p+24),y1=word(p+28),vertices[8]={x0,y0,x1,y0,x1,y1,x0,y1},local=nocturneLibcStreamLocalAddress(vertices,sizeof vertices);
 uint32_t tag=ps2WorkBufferTake(32);ps2DmaChainInitialize(tag);ps2PanelDrawColoredLineStrip(sx(local),0x326798,0x54f500,0x54f508,5,0xffffff,sx(tag));submit(0x2f6938,sx(tag));nocturneLibcStreamEndLocal();
}
/* 001d0ac0 */
void ps2MessageDrawWindow(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,flags=word(p),window=p+156;if(flags&0x80000)return;
 if((flags&0x300)>=0x100){uint64_t ot=ordering((uint32_t)signedHalf(p+16));ps2PanelSubmitDraw(sx(word(window+4)),ot);uint64_t speaker=sx(word(window));sh(0x56be6c,(uint16_t)(half(0x56be6c)|2));if(speaker)ps2PanelSubmitDraw(speaker,ot);}
 uint32_t debug=word(0x326708);if(debug&&sx(word(debug+12))==instance)ps2MessageDebugDrawWindow(sx(word(window+4)));
}
/* 001d0e90 */
void ps2MessageDrawWaitCursor(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,rect[4]={0x1a50,0xca0,0x1b60,0xd28},local=nocturneLibcStreamLocalAddress(rect,sizeof rect);sw(0x326794,(uint32_t)signedHalf(p+456));
 uint32_t tag=ps2WorkBufferTake(32);ps2DmaChainInitialize(tag);ps2PanelDrawTexturedSprite(sx(local),0x326778,0x326788,sx(word(p+12)),sx(word(0x56be64)),0,sx(tag));
 int32_t alpha=signedHalf(p+458);if(alpha>0){uint32_t expand=128-(uint32_t)alpha;rect[0]-=expand<<1;rect[1]-=expand;rect[2]+=expand<<1;rect[3]+=expand;sw(0x326794,(uint32_t)alpha);ps2PanelAppendAlphaPacket(sx(tag),1,0);ps2PanelDrawTexturedSprite(sx(local),0x326778,0x326788,sx(word(p+12)),sx(word(0x56be64)),0,sx(tag));ps2PanelAppendAlphaPacket(sx(tag),0,0);}
 submit(ordering((uint32_t)signedHalf(p+16)),sx(tag));nocturneLibcStreamEndLocal();
}
/* 001d0b90: native mutable shared cursor geometry and private UV/RGBA/rect. */
void ps2MessageDrawSelectionCursor(uint64_t instance)
{
 uint32_t p=(uint32_t)instance;int32_t selected=signedHalf(p+84);if(selected==-1)return;
 uint32_t tag=ps2WorkBufferTake(32);ps2DmaChainInitialize(tag);uint32_t x=word(p+64),line=word(p+68)-((uint32_t)signedHalf(p+86)*160-192)+(uint32_t)selected*168;
 uint32_t top=line-8,bottom=line+168,left=x-240,edge=x-336,words[12]={0};uint32_t local=nocturneLibcStreamLocalAddress(words,sizeof words),uv=local,color=local+16,rect=local+32;
 words[4]=0x57;words[5]=0;words[6]=0x10;words[7]=0x26;words[8]=left;words[9]=top;words[10]=word(0x326728);words[11]=bottom;
 ps2PanelDrawFlatSprite(sx(rect),sx(color),sx(word(p+12)),0,sx(tag));sw(0x326734,top);sw(0x326744,bottom);sw(0x32672c,top);sw(0x32673c,bottom);
 ps2PanelDrawColoredFan4(0x326728,0x326748,0x326768,0x326770,sx(word(p+12)),sx(tag));
 words[0]=0x150;words[1]=0x2f0;words[2]=0x1b0;words[3]=0x3f0;words[4]=128;words[5]=128;words[6]=128;words[7]=0x26;words[8]=edge;words[9]=line+8;words[10]=left;words[11]=line+136;
 ps2PanelDrawTexturedSprite(sx(rect),sx(uv),sx(color),sx(word(p+12)),sx(word(0x56be64)),0,sx(tag));
 words[10]=words[8]+256;words[11]=words[9]+128;words[0]=0x260;words[1]=0x2f0;words[2]=0x360;words[3]=0x3f0;words[7]=(uint32_t)signedHalf(p+456);
 ps2PanelDrawSprite(sx(rect),sx(uv),sx(color),sx(word(p+12)),0,sx(tag));int32_t alpha=signedHalf(p+458);
 if(alpha>0){uint32_t expand=128-(uint32_t)alpha,vertical=asr(expand,1);words[8]-=expand;words[9]-=vertical;words[10]+=expand<<1;words[11]+=vertical;words[7]=(uint32_t)alpha;ps2PanelAppendAlphaPacket(sx(tag),1,0);ps2PanelDrawSprite(sx(rect),sx(uv),sx(color),sx(word(p+12)),0,sx(tag));ps2PanelAppendAlphaPacket(sx(tag),0,0);}
 submit(ordering((uint32_t)signedHalf(p+16)),sx(tag));nocturneLibcStreamEndLocal();
}
/* 001d0930: original cached entry flags, later state reloads, exact phase stores. */
void ps2MessageDrawFlow(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,flags=word(p);sh(0x56be6c,(uint16_t)(half(0x56be6c)&0xfffd));ps2MessageDrawWindow(instance);
 if(!(flags&0x10000)&&word(p+28))frDrawFont(sx(word(p+28)));
 if(!(flags&0x20000)&&(flags&7)>=3&&(int64_t)frDrawFont(sx(word(p+48)))>0){uint32_t live=word(p);if((live&7)!=4){sw(p+460,0);sw(p,(live&0xfffffff8)|4);}}
 uint32_t phase=flags&0x38;
 if(!(flags&0x40000)&&phase>=0x18&&(int64_t)frDrawFontEx(sx(word(p+72)),1)>0&&phase==0x18){if(signedHalf(p+82)==-1){sh(p+82,0);sh(p+84,0);}ps2MessageMarkSelectionText(sx(word(p+72)),sx((uint32_t)signedHalf(p+82)),sx((uint32_t)signedHalf(p+86)),1);sw(p,(word(p)&0xffffffc7)|0x20);sb(p+452,2);}
 if(byte(p+452)&1)ps2MessageDrawWaitCursor(instance);if(byte(p+452)&2)ps2MessageDrawSelectionCursor(instance);
}
