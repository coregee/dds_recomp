/* Native dependencies of the stock renderer. Original layouts and call order. */
#include "battle_panel_support.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include "script_construction.h"
#include "script_lifetime.h"
#include "font_text.h"
#include "font_parser_support.h"
#include "message_commands.h"
#include "message_frame_draw.h"
#include "panel_draw.h"
#include "deferred_drain.h"
#include "screen_fade.h"
#include "libc_stream.h"
#include "compiler_numeric.h"
#include "nocturne.h"
#include "ps2_memory.h"
#include <string.h>

static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattlePanelSupportAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w64(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int64_t lw(uint32_t a){return (int64_t)(int32_t)r32(a);}
static void submit(uint32_t ot,uint64_t tag){nocturneInvokeMessageDrawOrder(r32(ot+16),sx(ot),tag);}
static uint32_t panelOrder(void){return 0x2f5f18+r32(0x551168)*32u;}

/* 001ABC88: VU channels, truncation and byte packing; no saturation to255. */
uint64_t effColorMultiply(uint64_t first,uint64_t second){
 uint32_t a[4],b[4],v[4];
 for(unsigned k=0;k<4;k++)a[k]=EE_FPU_CVT_S_W((uint8_t)(first>>(k*8)));
 EE_ROT_VU_WRITE(10,a);EE_BATTLE_PANEL_COLOR_QMTC2(0x3c000000);
 for(unsigned k=0;k<4;k++)a[k]=(uint32_t)EE_ROT_VU_MUL(a[k],0x3c000000);
 EE_ROT_VU_WRITE(10,a);EE_ROT_VU_WRITE(11,a);
 for(unsigned k=0;k<4;k++)b[k]=EE_FPU_CVT_S_W((uint8_t)(second>>(k*8)));
 EE_ROT_VU_WRITE(10,b);EE_BATTLE_PANEL_COLOR_QMTC2(0x3c000000);
 for(unsigned k=0;k<4;k++)b[k]=(uint32_t)EE_ROT_VU_MUL(b[k],0x3c000000);
 EE_ROT_VU_WRITE(10,b);
 for(unsigned k=0;k<4;k++)b[k]=(uint32_t)EE_ROT_VU_MUL(b[k],a[k]);
 EE_ROT_VU_WRITE(10,b);EE_BATTLE_PANEL_COLOR_QMTC2(0x43000000);
 for(unsigned k=0;k<4;k++)b[k]=(uint32_t)EE_ROT_VU_MUL(b[k],0x43000000);
 EE_ROT_VU_WRITE(10,b);
 uint64_t result=0;
 for(unsigned k=0;k<4;k++){v[k]=EE_FPU_CVT_W_S(b[k]);result|=(uint64_t)(v[k]&255u)<<(k*8);}
 EE_ROT_VU_WRITE(10,v);return result;
}

/* 001C6160: positivity uses the complete signed64 argument before stores. */
void ps2FontSetSize(uint64_t size){if((int64_t)size<=0)size=20;w32(0x54f410,(uint32_t)size);*at(0x326061)=(uint8_t)(size-5);}
/* 001C7BA8: walk every FRQ and its TEXT list with live link loads. */
void frSetFontColor(uint64_t font,uint64_t color){
 while(font){uint32_t f=(uint32_t)font;uint64_t t=sx(r32(f+28));while(t){w32((uint32_t)t+16,(uint32_t)color);t=sx(r32((uint32_t)t+40));}font=sx(r32(f+36));}
}
/* 001CA298: only FFFF becomes8080; retain mixed single/two-byte traversal. */
uint64_t ps2FontBuildDrawString(uint64_t x,uint64_t y,uint64_t z,uint64_t color,uint64_t text,uint64_t prior){
 uint32_t length=ps2Strlen((const char *)at((uint32_t)text)),i=0;uint8_t bytes[1024];bytes[length]=0;
 if((int32_t)length>0)do{uint8_t a=*at((uint32_t)text+i);if(a<128)bytes[i]=a;else{uint8_t b=*at((uint32_t)text+i+1);bytes[i]=a==255&&b==255?128:a;bytes[i+1]=a==255&&b==255?128:b;i++;}i++;}while((int32_t)i<(int32_t)length);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t local=nocturneLibcStreamLocalAddress(bytes,sizeof(bytes));
#else
 uint32_t local=(uint32_t)(uintptr_t)bytes;
#endif
 (void)frEnableMode(1);uint64_t f=ps2FontAppendStringCombined(sx(local),1,0,0,0);
 (void)frEnableMode(2);(void)frDisableMode(1);frSetDrawPosition(f,x,y);ps2FontSetDepth(f,sx((uint32_t)z<<4));frSetFontColor(f,color);frSetFontSpace(f,3);
 uint64_t result=frCombineFontRequestEx(prior,f,0);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 return result;
}
/* 001CA430: build through the real empty-root and original style2 append. */
uint64_t ps2FontBuildPanelString(uint64_t x,uint64_t y,uint64_t z,uint64_t color,uint64_t text,uint64_t prior){
 uint64_t f=ps2FontAppendStringCombined(0x54f448,0,0,0,prior);(void)frDisableMode(2);
 f=ps2FontAppendString(text,2,0,0,f,0);(void)frEnableMode(2);frSetDrawPosition(f,x,y);ps2FontSetDepth(f,sx((uint32_t)z<<4));frSetFontColor(f,color);return f;
}
/* 00279868: raw64 primitive lane ORs signed shifted32 lanes. */
void ps2BattlePanelSetPrimitive(uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f,uint64_t g,uint64_t h){
 (void)g;uint64_t chain=ps2DrawCreateDmaChain();uint32_t p=ps2WorkBufferTake(48);
 ps2PanelBuildInlineBytePacket(sx(p),48);w64(p+40,0x47);
 w64(p+32,sx((uint32_t)h<<17)|a|sx(((uint32_t)e<<14)|((uint32_t)c<<4))|sx((uint32_t)f<<15)|0x10000|sx(((uint32_t)d<<12)|((uint32_t)b<<1)));
 ps2DmaChainAppend((uint32_t)chain,p);submit(panelOrder(),chain);
}
/* 00279980: native defaults outside the inspected twenty-one selectors. */
void ps2BattlePanelSetAlpha(uint64_t mode){
 uint32_t chain=(uint32_t)ps2DrawCreateDmaChain(),p=ps2WorkBufferTake(48);ps2PanelBuildInlineBytePacket(sx(p),48);
 uint64_t value=0x44;switch((uint32_t)mode){case 1:value=0x48;break;case 2:case 6:value=0x42;break;case 3:value=0x84;break;case 4:value=6;break;case 5:value=0x89;break;case 10:value=0x2a;break;case 20:value=0x4a;break;}
 w64(p+32,value);w64(p+40,0x42);ps2DmaChainAppend(chain,p);submit(panelOrder(),sx(chain));
}
/* 002B9DD0: retain raw64 loop bits in the underlying tag builder. */
uint64_t ps2PanelCreateTexturedSpritePacket(uint64_t loops){uint32_t p=ps2WorkBufferTake((uint32_t)ps2PanelPackedPacketSize(5,loops));ps2PanelBuildPackedTag(sx(p),0x156,5,0x53531,loops);return sx(p);}
/* 00279A88: original payload writes, texture-before-sprite chain ordering. */
void ps2BattlePanelDrawTexturedRect(uint64_t x,uint64_t y,uint64_t width,uint64_t height,uint64_t u,uint64_t v,uint64_t uw,uint64_t vh,uint64_t color,uint64_t texture){
 uint64_t packet=ps2PanelCreateTexturedSpritePacket(1);uint32_t p=(uint32_t)ps2PanelPacketPayload(packet),xx=(uint32_t)x*16u+0x7000,yy=(uint32_t)y*8u+0x7900,c=(uint32_t)color;
 w32(p+4,(c>>8)&255);w32(p+72,0xffffffff);w32(p+20,(uint32_t)v*16u);w32(p+40,0xffffffff);w32(p+8,(c>>16)&255);w32(p+12,c>>24);w32(p,c&255);
 w32(p+48,(uint32_t)(u+uw)*16u);w32(p+52,(uint32_t)(v+vh)*16u);w32(p+64,xx+(uint32_t)width*16u);w32(p+68,yy+(uint32_t)height*8u);w32(p+16,(uint32_t)u*16u);w32(p+32,xx);w32(p+36,yy);w16(p+76,0);w16(p+44,0);
 uint64_t chain=ps2DrawCreateDmaChain();ps2PanelAppendTexturePacket(chain,texture,0);ps2DmaChainAppend((uint32_t)chain,(uint32_t)packet);submit(panelOrder(),chain);
}
/* 00279C00: native ABGR and reverse-byte text color globals. */
void nbPanelBaseColorSet(uint64_t color){uint32_t c=(uint32_t)color;w32(0x551180,c);w32(0x551184,(c>>24)|(c<<24)|((c&0xff00)<<8)|((c>>8)&0xff00));}
void ps2BattlePanelDrawNumber(uint64_t x,uint64_t y,uint64_t layout,uint64_t color,uint64_t text){
 uint64_t c=effColorMultiply(color,sx(r32(0x551184)));uint32_t a=(uint32_t)layout;
 uint64_t f=ps2FontBuildPanelString(sx((r32(a)+(uint32_t)x)<<4),sx((r32(a+4)+(uint32_t)y)<<3),0,c,text,0);
 (void)frDrawFontEx2(f,1,0x47);(void)frDestroyFontRequestAfter(f);
}
void ps2BattlePanelDrawName(uint64_t x,uint64_t y,uint64_t layout,uint64_t color,uint64_t unit){
 uint32_t p=r32(0x54ea20)+(uint32_t)unit*236u+0xa50,a=(uint32_t)layout;uint64_t f;
 if(r32(p+4)&4){f=ps2FontAppendResourceName(0,1,0,0);frSetDrawPosition(f,sx((r32(a)+(uint32_t)x)<<4),sx((r32(a+4)+(uint32_t)y)<<3));frSetFontColor(f,effColorMultiply(color,sx(r32(0x551184))));}
 else{uint64_t c=effColorMultiply(color,sx(r32(0x551184)));f=ps2FontBuildDrawString(sx((r32(a)+(uint32_t)x)<<4),sx((r32(a+4)+(uint32_t)y)<<3),0,c,sx(r32(0x3e7328+r16(p+8)*4u)),0);}
 (void)frDrawFontEx2(f,1,0x47);(void)frDestroyFontRequestAfter(f);
}
static uint64_t ratioColor(uint32_t value,uint32_t maximum){if(!maximum)nocturneCompilerArithmeticTrap(7);uint32_t pct=value*100u/maximum;return sx(pct<25?0x754b3d80:pct<50?0xb4a06480:0xa09dc380);}
uint64_t nbPanelHPColor(uint64_t unit){uint32_t p=(uint32_t)unit;if(datCheckDying((datUnitWork_PS2 *)at(p)))return 0x754b3d80;return ratioColor(r16(p+6),r16(p+8));}
uint64_t nbPanelMPColor(uint64_t unit){uint32_t p=(uint32_t)unit;return ratioColor(r16(p+10),r16(p+12));}
/* 002AF0F8: four RGBA/XYZ pairs, caller z word, no coordinate clamp. */
void ps2DrawBuildColoredQuadPacket(uint64_t dst,uint64_t prim,uint64_t x0,uint64_t y0,uint64_t c0,uint64_t x1,uint64_t y1,uint64_t c1,uint64_t x2,uint64_t y2,uint64_t c2,uint64_t x3,uint64_t y3,uint64_t c3,uint64_t z){
 uint32_t p=(uint32_t)dst;uint64_t zz=(uint64_t)(uint32_t)z<<32;
 w64(p+80,((uint32_t)x3&65535u)|((uint64_t)(uint32_t)((uint32_t)y3<<16))|zz);
 w64(p,UINT64_C(0xa400000000008001));w64(p+8,UINT64_C(0xf515151510));w64(p+16,(uint32_t)prim|0x10c);
 w64(p+24,(uint32_t)c0|UINT64_C(0x3f80000000000000));w64(p+32,((uint32_t)x0&65535u)|((uint64_t)(uint32_t)((uint32_t)y0<<16))|zz);
 w64(p+40,(uint32_t)c1|UINT64_C(0x3f80000000000000));w64(p+48,((uint32_t)x1&65535u)|((uint64_t)(uint32_t)((uint32_t)y1<<16))|zz);
 w64(p+56,(uint32_t)c2|UINT64_C(0x3f80000000000000));w64(p+64,((uint32_t)x2&65535u)|((uint64_t)(uint32_t)((uint32_t)y2<<16))|zz);w64(p+72,(uint32_t)c3|UINT64_C(0x3f80000000000000));
}
void ps2DrawAppendColoredQuadPacket(uint64_t chain,uint64_t prim,uint64_t x0,uint64_t y0,uint64_t c0,uint64_t x1,uint64_t y1,uint64_t c1,uint64_t x2,uint64_t y2,uint64_t c2,uint64_t x3,uint64_t y3,uint64_t c3,uint64_t z,uint64_t allocator){
 uint32_t target=(uint32_t)allocator;uint64_t packet;
#if UINTPTR_MAX > UINT32_MAX
 packet=nocturneBattlePanelAllocate(target?target:0x2acb50,112);
#else
 packet=((uint64_t (*)(uint64_t))(uintptr_t)(target?target:0x2acb50))(112);
#endif
 uint32_t p=(uint32_t)packet;w64(p,0x20000006);w64(p+8,UINT64_C(0x5000000610000000));
 ps2DrawBuildColoredQuadPacket(sx(p+16),prim,x0,y0,c0,x1,y1,c1,sx((uint32_t)x2),sx((uint32_t)y2),sx((uint32_t)c2),sx((uint32_t)x3),sx((uint32_t)y3),sx((uint32_t)c3),sx((uint32_t)z));ps2DmaChainAppend((uint32_t)chain,p);
}
void ps2BattlePanelDrawCursorGradient(uint64_t x,uint64_t y){
 uint32_t left=((uint32_t)x+21u)*16u,top=(uint32_t)y*8u+0x7900,bottom=(uint32_t)y*8u+0x79a0;
 uint64_t chain=ps2DrawCreateDmaChain(),c2=effColorMultiply(0x468cbe1b,sx(r32(0x551180))),c1=effColorMultiply(0x469b4400,sx(r32(0x551180))),c0=effColorMultiply(0x00bf0013,sx(r32(0x551180)));
 uint64_t a=sx(left+0x7000),b=sx(left+0x7828),c=sx(left+0x8050),t=sx(top),bt=sx(bottom);
 ps2DrawAppendColoredQuadPacket(chain,0x14c,a,t,c0,b,t,c1,a,bt,c0,b,bt,c1,UINT64_MAX,0);
 ps2DrawAppendColoredQuadPacket(chain,0x14c,b,t,c1,c,t,c2,b,bt,c1,c,bt,c2,UINT64_MAX,0);submit(0x2f67f8,chain);
}
/* 0027FBA0: original pad priorities and wrap/scroll rules; no HD mouse/sound. */
uint64_t nbPanelStockSelectCtrl(void){
 if(lw(0x55120c)<8)return UINT64_MAX;
 int64_t count=lw(0x551214),cursor=lw(0x551218),start=lw(0x55121c);
 if(*at(0x2f5836)&2){
  if(start<1){if(cursor<1){if(!(*at(0x2f5836)&128)||cursor!=0)return UINT64_MAX;if(count<4){w32(0x551218,(uint32_t)(count-1));w32(0x55121c,0);}else{w32(0x551218,3);w32(0x55121c,(uint32_t)(count-4));}return UINT64_MAX;}}
  else if(cursor==1){w32(0x55121c,(uint32_t)(start-1));return UINT64_MAX;}
  w32(0x551218,(uint32_t)(cursor-1));return UINT64_MAX;
 }
 if(*at(0x2f5837)&2){
  if(start<(int64_t)(int32_t)((uint32_t)count-4u)){if(cursor==2){w32(0x55121c,(uint32_t)(start+1));return UINT64_MAX;}}
  else if((int64_t)(int32_t)((uint32_t)count-1u)<=cursor||cursor>2){if(*at(0x2f5837)&128){w32(0x551218,0);w32(0x55121c,0);}return UINT64_MAX;}
  w32(0x551218,(uint32_t)(cursor+1));return UINT64_MAX;
 }
 if(*at(0x2f5833)&128){*at(0x551201)=0;return UINT64_MAX-1;}
 if(!(*at(0x2f5831)&128))return UINT64_MAX;
 *at(0x551201)=0;return sx(r32(0x575400+((uint32_t)start+(uint32_t)cursor)*4u));
}
/* 002C0060: original range reduction and five-term polynomial order. */
uint32_t sdfSinBits(uint32_t radians){
 uint32_t x=EE_FPU_MUL_S(radians,r32(0x54e758));x=EE_FPU_SUB_S(x,EE_FPU_CVT_S_W(EE_FPU_CVT_W_S(x)));
 if(EE_FPU_COMPARE_S(0x3f000000,x,1))x=EE_FPU_SUB_S(x,0x3f800000);else if(EE_FPU_COMPARE_S(x,0xbf000000,1))x=EE_FPU_ADD_S(x,0x3f800000);
 if(EE_FPU_COMPARE_S(0x3e800000,x,1))x=EE_FPU_SUB_S(0x3f000000,x);else if(EE_FPU_COMPARE_S(x,0xbe800000,1))x=EE_FPU_SUB_S(0xbf000000,x);
 x=EE_FPU_MUL_S(x,r32(0x54e75c));uint32_t sq=EE_FPU_MUL_S(x,x),result=EE_FPU_MUL_S(x,r32(0x54e760));
 x=EE_FPU_MUL_S(sq,x);result=EE_FPU_ADD_S(result,EE_FPU_MUL_S(x,r32(0x54e764)));
 x=EE_FPU_MUL_S(x,sq);result=EE_FPU_ADD_S(result,EE_FPU_MUL_S(x,r32(0x54e768)));
 x=EE_FPU_MUL_S(x,sq);result=EE_FPU_ADD_S(result,EE_FPU_MUL_S(x,r32(0x54e76c)));
 x=EE_FPU_MUL_S(x,sq);return EE_FPU_ADD_S(result,EE_FPU_MUL_S(x,r32(0x54e770)));
}
