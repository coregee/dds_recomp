/* Original packed VM arithmetic, boolean and conditional opcode bodies. */
#include "script_ops.h"
#include "script_core.h"
#include "script_stack.h"
#include "script_compare.h"
#include "compiler_numeric.h"
#include "nocturne.h"
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
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int64_t si(uint32_t v){return (int64_t)sx(v);}
static uint32_t tagword(uint8_t v){return v&0x80u?0xffffff00u|v:v;}
static uint32_t sh(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v&0x8000u?0xffff0000u|v:v;}
static unsigned truth(uint32_t bits){float value;memcpy(&value,&bits,4);return ps2SoftDoubleCompare(ps2SoftDoubleFromFloat(value),0)!=0;}
void scrCodeFunc_2Operation(uint64_t raw,uint64_t op){
 uint32_t w=(uint32_t)raw,count=r32(w+0x1c);uint8_t below=*at(w+0x1e+count),top=*at(w+0x1f+count);
 w32(0x551c74,tagword(below));w32(0x551c70,tagword(top));
 if((top==0||top==2)&&(below==0||below==2)){
  w32(0x551c58,(uint32_t)scrPopInt(raw));w32(0x551c5c,(uint32_t)scrPopInt(raw));
  if(op<12){
   uint32_t a=r32(0x551c58),b=r32(0x551c5c),value=0;
   switch(op){
   case 0:value=a+b;break;case 1:value=a-b;break;case 2:value=(uint32_t)((uint64_t)a*b);break;
   case 3:if(!b)nocturneCompilerArithmeticTrap(7);value=(uint32_t)(si(a)/si(b));break;
   case 4:value=a!=0||b!=0;break;case 5:value=a!=0&&b!=0;break;
   case 6:value=a==b;break;case 7:value=a!=b;break;case 8:value=si(a)<si(b);break;
   case 9:value=si(b)<si(a);break;case 10:value=si(a)<=si(b);break;case 11:value=si(b)<=si(a);break;
   }
   w32(0x551c60,value);
  }
  scrPushInt(raw,sx(r32(0x551c60)));return;
 }
 w32(0x551c64,scrPopFloatBits(raw));w32(0x551c68,scrPopFloatBits(raw));
 if(op<12){
  uint32_t a=r32(0x551c64),b=r32(0x551c68),value=0;
  switch(op){
  case 0:value=EE_FPU_ADD_S(a,b);break;case 1:value=EE_FPU_SUB_S(a,b);break;
  case 2:value=EE_FPU_MUL_S(a,b);break;case 3:value=EE_FPU_DIV_S(a,b);break;
  case 4:value=truth(a)||truth(r32(0x551c68));break;case 5:value=truth(a)&&truth(r32(0x551c68));break;
  case 6:value=EE_FPU_COMPARE_S(a,b,0);break;case 7:value=!EE_FPU_COMPARE_S(a,b,0);break;
  case 8:value=EE_FPU_COMPARE_S(a,b,1);break;case 9:value=EE_FPU_COMPARE_S(b,a,1);break;
  case 10:value=EE_FPU_COMPARE_S(a,b,2);break;case 11:value=EE_FPU_COMPARE_S(b,a,2);break;
  }
  if(op>=4){w32(0x551c60,value);scrPushInt(raw,sx(r32(0x551c60)));return;}
  w32(0x551c6c,value);
 }
 scrPushFloatBits(raw,r32(0x551c6c));
}
#define BINARY(name,operation) uint64_t name(uint64_t raw){scrCodeFunc_2Operation(raw,operation);uint32_t w=(uint32_t)raw;w32(w+0x18,r32(w+0x18)+1);return 1;}
BINARY(scrCodeFunc_Add,0)
BINARY(scrCodeFunc_Sub,1)
BINARY(scrCodeFunc_Mul,2)
BINARY(scrCodeFunc_Div,3)
BINARY(scrCodeFunc_Or,4)
BINARY(scrCodeFunc_And,5)
BINARY(scrCodeFunc_EQ,6)
BINARY(scrCodeFunc_NEQ,7)
BINARY(scrCodeFunc_S,8)
BINARY(scrCodeFunc_L,9)
BINARY(scrCodeFunc_SE,10)
BINARY(scrCodeFunc_LE,11)
#undef BINARY
uint64_t scrCodeFunc_Not(uint64_t raw){
 uint32_t w=(uint32_t)raw;uint8_t tag=*at(w+0x1f+r32(w+0x1c));
 if(tag==0||tag==2)scrPushInt(raw,scrPopInt(raw)==0);
 else if(tag==1||tag==3){uint32_t bits=scrPopFloatBits(raw);scrPushInt(raw,EE_FPU_COMPARE_S(bits,0,0));}
 w32(w+0x18,r32(w+0x18)+1);return 1;
}
uint64_t scrCodeFunc_If(uint64_t raw){
 uint32_t w=(uint32_t)raw;uint8_t tag=*at(w+0x1f+r32(w+0x1c));unsigned predicate=0;
 if(tag==0||tag==2)predicate=scrPopInt(raw)!=0;
 else if(tag==1||tag==3)predicate=!EE_FPU_COMPARE_S(scrPopFloatBits(raw),0,0);
 if(predicate)w32(w+0x18,r32(w+0x18)+1);
 else{uint32_t label=sh(r32(w+0xbc)+r32(w+0x18)*4+2);w32(w+0x18,r32(r32(w+0xb8)+label*32+0x18));}
 return 1;
}
