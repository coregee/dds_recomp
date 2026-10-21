/* Original packed VM stack, variable access and procedure control. */
#include "script_stack.h"
#include "script_core.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveScriptCoreAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sh(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v&0x8000u?0xffff0000u|v:v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static void push(uint32_t w,uint8_t tag,uint32_t value){
 /* Each reload is present in the original, including overlapping layouts. */
 *at(w+0x20+r32(w+0x1c))=tag;
 w32(w+0x3c+r32(w+0x1c)*4,value);
 w32(w+0x1c,r32(w+0x1c)+1);
}
void scrPushInt(uint64_t work,uint64_t value){push((uint32_t)work,0,(uint32_t)value);}
void scrPushFloatBits(uint64_t work,uint32_t bits){push((uint32_t)work,1,bits);}
void scrPushStr(uint64_t work,uint64_t value){push((uint32_t)work,5,(uint32_t)value);}
void scrPushRet(uint64_t work,uint64_t value){push((uint32_t)work,4,(uint32_t)value);}
uint32_t scrPopFloatBits(uint64_t raw){
 uint32_t w=(uint32_t)raw,count=r32(w+0x1c);w32(w+0x1c,count-1);
 uint8_t tag=*at(w+0x1f+count);if(tag>3)return 0;
 uint32_t value=r32(w+0x3c+r32(w+0x1c)*4);
 switch(tag){
 case 0:return EE_FPU_CVT_S_W(value);
 case 1:return value;
 case 2:return EE_FPU_CVT_S_W(r32(r32(0x54ea20)+0x40+value*4));
 case 3:return r32(r32(0x54ea20)+0x440+value*4);
 default:return 0;
 }
}
static uint64_t advance(uint32_t w){w32(w+0x18,r32(w+0x18)+1);return 1;}
static uint32_t operand(uint32_t w){return sh(r32(w+0xbc)+r32(w+0x18)*4+2);}
uint64_t scrCodeFunc_PushI(uint64_t raw){
 uint32_t w=(uint32_t)raw,cp=r32(w+0x18)+1,code=r32(w+0xbc);
 w32(w+0x18,cp);scrPushInt(raw,sx(r32(code+cp*4)));return advance(w);
}
uint64_t scrCodeFunc_PushIS(uint64_t raw){scrPushInt(raw,sx(operand((uint32_t)raw)));return advance((uint32_t)raw);}
uint64_t scrCodeFunc_PushF(uint64_t raw){
 uint32_t w=(uint32_t)raw,cp=r32(w+0x18)+1,code=r32(w+0xbc);
 w32(w+0x18,cp);scrPushFloatBits(raw,r32(code+cp*4));return advance(w);
}
uint64_t scrCodeFunc_PushIX(uint64_t raw){
 uint32_t w=(uint32_t)raw,context=r32(0x54ea20);
 scrPushInt(raw,sx(r32(context+0x40+operand(w)*4)));return advance(w);
}
uint64_t scrCodeFunc_PushFX(uint64_t raw){
 uint32_t w=(uint32_t)raw,context=r32(0x54ea20);
 scrPushFloatBits(raw,r32(context+0x440+operand(w)*4));return advance(w);
}
uint64_t scrCodeFunc_PushLIX(uint64_t raw){
 uint32_t w=(uint32_t)raw,index=operand(w),table=r32(w+0xdc);
 scrPushInt(raw,sx(r32(table+index*4)));return advance(w);
}
uint64_t scrCodeFunc_PushLFX(uint64_t raw){
 uint32_t w=(uint32_t)raw,index=operand(w),table=r32(w+0xe0);
 scrPushFloatBits(raw,r32(table+index*4));return advance(w);
}
uint64_t scrCodeFunc_PushSTR(uint64_t raw){
 uint32_t w=(uint32_t)raw,value=r32(w+0xc4)+operand(w);
 scrPushStr(raw,sx(value));return advance(w);
}
uint64_t scrCodeFunc_PushReg(uint64_t raw){
 uint32_t w=(uint32_t)raw;*at(w+0x20+r32(w+0x1c))=*at(w+0x3b);
 uint32_t count=r32(w+0x1c),value=r32(w+0xa8);w32(w+0x3c+count*4,value);
 count=r32(w+0x1c);uint32_t cp=r32(w+0x18);
 w32(w+0x1c,count+1);w32(w+0x18,cp+1);return 1;
}
uint64_t scrCodeFunc_PopIX(uint64_t raw){
 uint32_t w=(uint32_t)raw,value=(uint32_t)scrPopInt(raw),index=operand(w),context=r32(0x54ea20);
 w32(context+0x40+index*4,value);return advance(w);
}
uint64_t scrCodeFunc_PopFX(uint64_t raw){
 uint32_t w=(uint32_t)raw,value=scrPopFloatBits(raw),cp=r32(w+0x18),code=r32(w+0xbc),context=r32(0x54ea20);
 uint32_t index=sh(code+cp*4+2);w32(w+0x18,cp+1);w32(context+0x440+index*4,value);return 1;
}
uint64_t scrCodeFunc_PopLIX(uint64_t raw){
 uint32_t w=(uint32_t)raw,value=(uint32_t)scrPopInt(raw),index=operand(w),table=r32(w+0xdc);
 w32(table+index*4,value);return advance(w);
}
uint64_t scrCodeFunc_PopLFX(uint64_t raw){
 uint32_t w=(uint32_t)raw,value=scrPopFloatBits(raw),cp=r32(w+0x18),code=r32(w+0xbc),table=r32(w+0xe0);
 uint32_t index=sh(code+cp*4+2);w32(w+0x18,cp+1);w32(table+index*4,value);return 1;
}
uint64_t scrCodeFunc_Proc(uint64_t raw){return advance((uint32_t)raw);}
uint64_t scrCodeFunc_Jump(uint64_t raw){
 uint32_t w=(uint32_t)raw,index=operand(w);w32(w+0x18,r32(r32(w+0xb4)+index*32+0x18));return 1;
}
uint64_t scrCodeFunc_Call(uint64_t raw){
 uint32_t w=(uint32_t)raw;scrPushRet(raw,sx(r32(w+0x18)));
 uint32_t index=operand(w);w32(w+0x18,r32(r32(w+0xb4)+index*32+0x18));return 1;
}
uint64_t scrCodeFunc_Run(uint64_t raw){return advance((uint32_t)raw);}
