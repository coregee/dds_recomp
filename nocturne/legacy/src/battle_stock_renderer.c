/* Original SLUS_209.11 stock/party drawing. HD names denote semantic roles;
 * the packet geometry, original tables and EE operation order are native. */
#include "battle_stock_renderer.h"
#include "battle_panel_support.h"
#include "battle_work_access.h"
#include "font_text.h"
#include "font_parser_support.h"
#include "message_frame_draw.h"
#include "message_commands.h"
#include "script_lifetime.h"
#include "libc_stream.h"
#include "sound_bank_support.h"
#include "compiler_numeric.h"
#include "script_compare.h"
#include "ee_fpu.h"
#include "nocturne.h"
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
static int32_t s32(uint32_t a){return (int32_t)r32(a);}
static int8_t s8(uint32_t a){return (int8_t)*at(a);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t record(uint32_t unit){return r32(0x54ea20)+unit*236u+0xa50;}
static void primitive(void){ps2BattlePanelSetPrimitive(1,0,0x80,3,0,0,1,1);ps2BattlePanelSetAlpha(0);}
static uint64_t base(void){return sx(r32(0x551180));}
static uint64_t textbase(void){return sx(r32(0x551184));}
static void rect(uint64_t x,uint64_t y,uint64_t width,uint64_t height,uint64_t u,uint64_t v,uint64_t uw,uint64_t vh,uint64_t color,uint32_t main,uint32_t texture_offset){
 ps2BattlePanelDrawTexturedRect(x,y,width,height,u,v,uw,vh,color,sx(r32(main+texture_offset)));
}
/* 0027AA40: original A0/A1 retain raw64 lanes until coordinate arithmetic. */
void ps2BattleDrawEmptyPartyRow(uint64_t x,uint64_t y,uint64_t main){
 primitive();rect(x,y,0x36,0x17,0x34,1,0x36,0x17,base(),(uint32_t)main,0x120);
 rect(sx((uint32_t)x+0x36),y,0xe4,0x17,0x69,1,1,0x17,base(),(uint32_t)main,0x120);
}
/* Table rows have X,Y,an unused word,width,height; UV rows are four words. */
static void table(uint64_t x,uint64_t y,uint32_t geometry,uint32_t uv,uint64_t color,uint64_t texture,uint32_t ratio,int scaled){
 uint64_t c=effColorMultiply(color,base());uint32_t width=r32(geometry+12),uw=r32(uv+8);
 if(scaled){uw=EE_FPU_CVT_W_S(EE_FPU_MUL_S(EE_FPU_CVT_S_W(uw),ratio));width=EE_FPU_CVT_W_S(EE_FPU_MUL_S(EE_FPU_CVT_S_W(width),ratio));}
 ps2BattlePanelDrawTexturedRect(sx(r32(geometry)+(uint32_t)x),sx(r32(geometry+4)+(uint32_t)y),sx(width),sx(r32(geometry+16)),sx(r32(uv)),sx(r32(uv+4)),sx(uw),sx(r32(uv+12)),c,texture);
}
static void tab(uint64_t x,uint64_t y,uint32_t g,uint32_t uv,uint64_t color,uint32_t main,uint32_t tex){table(x,y,g,uv,color,sx(r32(main+tex)),0,0);}
static uint32_t unsignedFloat(uint32_t v){if(!(v&0x80000000u))return EE_FPU_CVT_S_W(v);uint32_t f=EE_FPU_CVT_S_W((v>>1)|(v&1));return EE_FPU_ADD_S(f,f);}
static uint32_t pulse(uint32_t angle,uint32_t scale,uint32_t bias){return (EE_FPU_CVT_W_S(EE_FPU_MUL_S(sdfSinBits(angle),scale))+bias)*0x10101u;}
static uint32_t localText(char *buffer,uint32_t size){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneLibcStreamLocalAddress(buffer,size);
#else
 return (uint32_t)(uintptr_t)buffer;
#endif
}
static void endText(void){
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
}
static void drawNumber(uint64_t x,uint64_t y,uint32_t layout,uint32_t unit,int mp){
 char buffer[112];uint32_t text=localText(buffer,sizeof(buffer)),p=record(unit);
 (void)ps2LibcSprintf(sx(text),0x551188,(uint64_t)r16(p+(mp?14:10)));
 uint64_t color=mp?nbPanelMPColor(sx(record(unit)+4)):nbPanelHPColor(sx(record(unit)+4));
 ps2BattlePanelDrawNumber(x,y,layout,color,sx(text));endText();
}
/* 0027B7A8: original compact stock row. HP suppression also selects MP atlas. */
void nbPanelDrawPP(uint64_t x,uint64_t y,uint64_t selected,uint64_t unit,uint64_t mask_arg){
 uint32_t main=(uint32_t)nbGetMainProcessData(),mask=(uint32_t)mask_arg,u=(uint32_t)unit,hp=0,maxhp=0;
 primitive();
 if(!(mask&8)){
  if(!(uint32_t)selected){tab(x,y,0x4efe90,0x4efb00,sx(0x80808080),main,0x120);tab(x,y,0x4efea4,0x4efb10,sx(0x80808080),main,0x120);}
  else{
   tab(x,y,0x4eff80,0x4efb00,sx(0x80808080),main,0x120);tab(x,y,0x4eff94,0x4efb10,sx(0x80808080),main,0x120);
   uint32_t color=pulse(EE_FPU_MUL_S(unsignedFloat(r32(main+0x70)),r32(0x54e5a4)),0x42400000,0xb0)+0x80000000u;
   tab(x,y,0x4effbc,0x4efbe0,sx(color),main,0x12c);tab(x,y,0x4effd0,0x4efbf0,sx(color),main,0x12c);
  }
 }
 if((uint32_t)selected)x=sx((uint32_t)x-16u);
 if(!(mask&16))tab(x,y,0x4effa8,0x4efbd0,sx(0x80808080),main,0x120);
 if(!(mask&2)){
  tab(x,y,0x4eff08,0x4efb20,sx(0x80808080),main,0x128);tab(x,y,0x4efef4,0x4efaf0,sx(0x80808080),main,0x120);
  uint32_t p=record(u);hp=r16(p+10);maxhp=r16(p+12);
  if(hp&&maxhp){uint32_t ratio=EE_FPU_DIV_S(EE_FPU_CVT_S_W(hp),EE_FPU_CVT_S_W(maxhp));table(x,y,0x4efee0,0x4efad0,sx(0x80808080),sx(r32(main+0x120)),ratio,1);}
  drawNumber(x,y,0x4efecc,u,0);
 }
 if(!(mask&4)){
  tab(x,y,0x4eff58,0x4efb30,sx(0x80808080),main,0x128);tab(x,y,0x4eff44,0x4efaf0,sx(0x80808080),main,0x120);
  uint32_t p=record(u),mp=r16(p+14),maximum=r16(p+16);
  if(mp&&maximum){uint32_t ratio=EE_FPU_DIV_S(EE_FPU_CVT_S_W(mp),EE_FPU_CVT_S_W(maximum));int alternate=!hp||!maxhp;table(x,y,0x4eff30,alternate?0x4efe50:0x4efae0,sx(0x80808080),sx(r32(alternate?0x345d88:main+0x120)),ratio,1);}
  drawNumber(x,y,0x4eff1c,u,1);
 }
 if(mask&0x200000){uint32_t color=pulse(EE_FPU_MUL_S(unsignedFloat(r32(main+0x70)),r32(0x54e5a8)),0x42c00000,0xa0)+0x80000000u;tab(x,y,0x4f01a0,0x4efbb0,sx(color),main,0x120);}
 if(!(mask&1))ps2BattlePanelDrawName(x,y,0x4efeb8,sx(mask&0x300000?0x89feff80:0xa09dc380),unit);
 if(!(mask&32)){
  static const uint16_t bits[]={0x800,0x400,0x200,0x100,0x80,0x40,0x10,4,2,1,0x20,8};
  static const uint8_t uv[]={13,19,20,21,22,23,25,27,28,29,24,26};
  uint32_t status=r16(record(u)+18);for(unsigned i=0;i<12;i++)if(status&bits[i]){tab(x,y,0x4effe4,0x4efad0+uv[i]*16u,sx(0x80808080),main,0x120);break;}
 }
}
static void rowBackground(uint64_t x,uint64_t y,uint32_t state,uint32_t main,uint32_t color,int bright){
 uint32_t tex=bright?0x12c:0x120;uint64_t c=effColorMultiply(sx(color),base());rect(x,y,0x36,0x17,bright?0x2d:0x34,1,0x36,0x17,c,main,tex);
 c=effColorMultiply(sx(color),base());rect(sx((uint32_t)x+0x36),y,sx(r32(state+4)+0xe4),0x17,bright?0x62:0x69,1,1,0x17,c,main,tex);
}
static void partyNumber(uint64_t x,uint64_t y,uint32_t unit,int mp){
 uint64_t color=mp?nbPanelMPColor(sx(record(unit)+4)):nbPanelHPColor(sx(record(unit)+4));
 char buffer[112];uint32_t text=localText(buffer,sizeof(buffer));(void)ps2LibcSprintf(sx(text),0x551188,(uint64_t)r16(record(unit)+(mp?14:10)));
 color=effColorMultiply(color,textbase());uint64_t font=ps2FontBuildPanelString(x,y,0,color,sx(text),0);w32(0x551fdc,(uint32_t)font);
 (void)frDrawFontEx2(font,1,0x47);(void)frDestroyFontRequestAfter(sx(r32(0x551fdc)));endText();
}
static void gauge(uint64_t x,uint64_t y,uint32_t form,uint32_t unit,int mp,uint32_t main){
 uint32_t p=record(unit),state=0x5753a0+form*24u,offset=mp?0xda:0xa4;
 rect(sx((uint32_t)x+offset),sx((uint32_t)y+15),50,6,1,0x14,50,6,base(),main,0x120);
 uint32_t value=r16(record(unit)+(mp?14:10)),width=0;
 if(value){uint32_t maximum=r16(record(unit)+(mp?16:12));if(!maximum)nocturneCompilerArithmeticTrap(7);width=value*50u/maximum;if(!width)width=1;rect(sx((uint32_t)x+offset),sx((uint32_t)y+15),sx(width),6,1,mp?0x1b:13,sx(width),6,base(),main,0x120);}
 p=record(unit);int32_t previous=s32(state+(mp?12:8));
 if((int32_t)r16(p+(mp?14:10))<previous){uint32_t maximum=r16(p+(mp?16:12));if(!maximum)nocturneCompilerArithmeticTrap(7);uint32_t gray=(uint32_t)((int32_t)((uint32_t)previous*50u)/(int32_t)maximum)-width;
  ps2BattlePanelSetAlpha(1);uint64_t color=effColorMultiply(sx((r32(state+(mp?20:16))<<28)|0xffffffu),base());
  rect(sx((uint32_t)x+width+offset),sx((uint32_t)y+15),sx(gray),6,sx(width+1),mp?0x1b:13,sx(gray),6,color,main,0x120);
 }
}
/* 0027AB10: native seven-register ABI, local copies of both icon UV tables. */
void nbPanelDrawPP1(uint64_t x,uint64_t y,uint64_t form_arg,uint64_t unit_arg,uint64_t ordinal,uint64_t selected,uint64_t main_arg){
 uint32_t form=(uint32_t)form_arg,unit=(uint32_t)unit_arg,main=(uint32_t)main_arg,state=0x5753a0+form*24u,icons[8],status_uv[24];
 memcpy(icons,at(0x545300),sizeof(icons));memcpy(status_uv,at(0x545320),sizeof(status_uv));primitive();int32_t shift=s32(state+4);x=sx((uint32_t)x-(uint32_t)shift);
 uint32_t shade=selected?pulse(r32(0x551170),0x42400000,0xb0):0x808080;
 if(selected&&shift>=16)rowBackground(x,y,state,main,shade|0x80000000u,1);
 else if(!selected&&!shift)rowBackground(x,y,state,main,0x80808080,0);
 else{rowBackground(x,y,state,main,shade|((uint32_t)shift<<27),1);rowBackground(x,y,state,main,(shade&0xffffffu)|((128u-(uint32_t)shift*8u)<<24),0);}
 rect(sx((uint32_t)x+21),sx((uint32_t)y+2),26,19,0x6c,1,25,19,base(),main,0x120);
 if(ordinal<4)rect(sx((uint32_t)x+28),sx((uint32_t)y+8),11,11,sx(icons[(uint32_t)ordinal*2]),sx(icons[(uint32_t)ordinal*2+1]),11,11,base(),main,0x120);
 ps2BattlePanelSetAlpha(0);gauge(x,y,form,unit,0,main);partyNumber(sx(((uint32_t)x+0xb9)<<4),sx(((uint32_t)y+2)<<3),unit,0);
 ps2BattlePanelSetAlpha(0);gauge(x,y,form,unit,1,main);ps2BattlePanelSetAlpha(0);
 rect(sx((uint32_t)x+0xa8),sx((uint32_t)y+7),16,7,0xe4,1,16,7,base(),main,0x128);rect(sx((uint32_t)x+0xde),sx((uint32_t)y+7),16,7,0xe4,9,16,7,base(),main,0x128);
 partyNumber(sx(((uint32_t)x+0xef)<<4),sx(((uint32_t)y+2)<<3),unit,1);ps2FontSetSize(19);
 uint64_t font,tx=sx(((uint32_t)x+45)<<4),ty=sx(((uint32_t)y+4)<<3);uint32_t p=record(unit);
 if(r32(p+4)&4){font=ps2FontAppendResourceName(0,1,0,0);w32(0x551fdc,(uint32_t)font);frSetDrawPosition(font,tx,ty);uint64_t c=effColorMultiply(sx(0xa09dc380),textbase());frSetFontColor(sx(r32(0x551fdc)),c);font=sx(r32(0x551fdc));}
 else{uint64_t c=effColorMultiply(sx(0xa09dc380),textbase());font=ps2FontBuildDrawString(tx,ty,0,c,sx(r32(0x3e7328+r16(record(unit)+8)*4u)),0);w32(0x551fdc,(uint32_t)font);}
 (void)frDrawFontEx2(font,1,0x47);(void)frDestroyFontRequestAfter(sx(r32(0x551fdc)));ps2FontSetSize(UINT64_MAX);ps2BattlePanelSetAlpha(0);
 uint32_t status=r16(record(unit)+18);int chosen=-1;for(int i=0;i<12;i++)if(status&(0x800u>>i))chosen=i;
 if(chosen>=0)rect(sx((uint32_t)x+8),y,20,21,sx(status_uv[chosen*2]),sx(status_uv[chosen*2+1]),20,21,base(),main,0x120);
}
/* 00282270: turn-queue order, original interpolation and real shake RNG. */
void nbPanelPartyDraw(void){
 if(!s8(0x55123d))return;uint64_t main_arg=nbGetMainProcessData();if(!main_arg)return;uint32_t main=(uint32_t)main_arg;
 int32_t slots[4],units[4],shake[4],ordinal[4];uint32_t slot=r32(main);
 for(unsigned i=0;i<4;i++,slot+=240){slots[i]=units[i]=shake[i]=ordinal[i]=-1;if((r32(slot+0x78)&0x41)==0x41){slots[i]=(int16_t)r16(slot+0x90);units[i]=(int16_t)r16(r32(main+16)+(uint32_t)slots[i]*128u+4);if(r32(slot+0x70)==1)shake[i]=1;}}
 if(!(r32(main+0x60)&8)){int32_t pos=s8(main+0x54),next=0;if(pos!=-1)for(unsigned k=0;k<12;k++){int32_t id=s8(main+0x48+(uint32_t)pos);if(id!=-1)for(unsigned i=0;i<4;i++)if(id==slots[i])ordinal[i]=next++;pos++;if(pos>11)pos=0;}}
 uint32_t y=339;
 for(unsigned i=0;i<4;i++,y+=23){uint64_t xx=230,yy=sx(y);if(shake[i]!=-1){xx=sx(sdfGetRandInt(NULL,6)+227u);yy=sx(y+sdfGetRandInt(NULL,6)-3u);}uint32_t state=0x5753a0+i*24u;
  if(slots[i]==-1){ps2BattleDrawEmptyPartyRow(xx,yy,main_arg);w32(state,0);w32(state+4,0);w32(state+8,UINT32_MAX);w32(state+12,UINT32_MAX);w32(state+16,0);w32(state+20,0);continue;}
  int32_t shift=s32(state+4);if(s8(main+0x48+(uint32_t)(int32_t)s8(main+0x54))==slots[i]&&ordinal[i]!=-1){w32(state,1);int32_t delta=(int32_t)(16u-(uint32_t)shift)/3;if(delta<1)delta=1;shift=(int32_t)((uint32_t)shift+(uint32_t)delta);if(shift>16)shift=16;}
  else{w32(state,0);int32_t delta=shift/3;if(delta<1)delta=1;shift=(int32_t)((uint32_t)shift-(uint32_t)delta);if(shift<0)shift=0;}w32(state+4,(uint32_t)shift);
  uint32_t unit=(uint32_t)units[i];if(r32(state+8)==UINT32_MAX)w32(state+8,r16(record(unit)+10));
  if(shake[i]==-1){if(s32(state+16)<1)w32(state+8,r16(record(unit)+10));else w32(state+16,r32(state+16)-1);}else w32(state+16,8);
  if(r32(state+12)==UINT32_MAX)w32(state+12,r16(record(unit)+14));
  if(s32(state+20)<1){if((int32_t)r16(record(unit)+14)<s32(state+12))w32(state+20,8);}else{w32(state+20,r32(state+20)-1);if(s32(state+20)<1)w32(state+12,r16(record(unit)+14));}
  nbPanelDrawPP1(xx,yy,sx(i),sx(unit),sx((uint32_t)ordinal[i]),sx(r32(state)),main_arg);
 }
 ps2BattlePanelSetAlpha(0);rect(259,335,253,3,1,115,253,3,base(),main,0x124);rect(259,430,253,3,1,115,253,3,base(),main,0x124);
}
static uint32_t fadeColor(uint32_t fraction){uint32_t value=EE_FPU_MUL_S(fraction,0x43000000);int high=EE_FPU_COMPARE_S(0x4f000000,value,2);uint32_t n=EE_FPU_CVT_W_S(value);if(high)n=EE_FPU_CVT_W_S(EE_FPU_SUB_S(value,0x4f000000))|0x80000000u;return (n<<24)|0x808080u;}
/* 0027FD18: original four visible rows, pad selection, two fades and party draw. */
uint64_t nbPanelStockSelect(uint64_t main_arg,uint64_t allow_input){
 uint32_t main=(uint32_t)main_arg,result=UINT32_MAX;if(allow_input&&s8(0x551201))result=(uint32_t)nbPanelStockSelectCtrl();uint64_t x=sx(r32(0x551210)+230u);
 if(s32(0x55120c)>0){uint32_t phase=r32(0x55120c)-1,fraction=(int32_t)phase<5?EE_FPU_DIV_S(EE_FPU_CVT_S_W(phase),0x40a00000):0x3f800000,color=fadeColor(fraction);nbPanelBaseColorSet(sx(color));w32(0x551210,(uint32_t)(s32(0x551210)>>1));if(s8(0x551208)){if(r32(0x551204)&0xff000000u)w32(0x551204,r32(0x551204)+0xe0000000u);(void)effColorMultiply(sx(color),sx(r32(0x551204)));nbPanelBaseColorSet(sx(r32(0x551204)));}}
 for(unsigned i=0;i<4;i++){tab(x,339+i*23,0x4efe90,0x4efb00,sx(0x80808080),main,0x120);tab(x,339+i*23,0x4efea4,0x4efb10,sx(0x80808080),main,0x120);}
 static const uint32_t g[]={0x4f01c8,0x4f01dc,0x4f0240,0x4f0254,0x4f01f0,0x4f0204},uv[]={0x4efb60,0x4efb70,0x4efb40,0x4efb40,0x4efb50,0x4efb50};
 for(unsigned i=0;i<6;i++)tab(x,339,g[i],uv[i],sx(0x80808080),main,i<4?0x124:0x120);
 int blink=r32(main+0x70)%25u>13;tab(x,339,0x4f0218,blink||!r32(0x55121c)?0x4efb80:0x4efb90,sx(0x80808080),main,0x120);
 tab(x,339,0x4f022c,blink||s32(0x55121c)>=(int32_t)(r32(0x551214)-4)?0x4efb80:0x4efb90,sx(0x80808080),main,0x120);
 ps2BattlePanelDrawCursorGradient(230,sx(r32(0x551218)*23u+339u));
 if(s32(0x551214)>0){uint32_t index=r32(0x55121c),list=0x575400+index*4u,y=339;for(unsigned i=0;i<4;i++,y+=23){nbPanelDrawPP(x,sx(y),0,sx(r32(list)),i==r32(0x551218)?0x200038:0x38);uint32_t unit=r32(list);list+=4;if(r16(record(unit)+18)&0x800)tab(x,sx(y),0x4eff6c,0x4efba0,sx(0x80808080),main,0x120);index++;if(s32(0x551214)<=(int32_t)index)break;}}
 uint32_t fraction=s32(0x55120c)<5?EE_FPU_SUB_S(0x3f800000,EE_FPU_DIV_S(EE_FPU_CVT_S_W(r32(0x55120c)),0x40a00000)):0;
 nbPanelBaseColorSet(sx(fadeColor(fraction)));nbPanelPartyDraw();nbPanelBaseColorSet(sx(0x80808080));w32(0x55120c,r32(0x55120c)+1);return sx(result);
}
