/* Original controller sampling, blend selection and seven-state frame update. */
#include "model_motion_control.h"
#include "model_motion_creation.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelMotionCreationAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t word(uint32_t address){uint32_t result;memcpy(&result,at(address),4);return result;}
static int16_t count(uint32_t address){int16_t result;memcpy(&result,at(address),2);return result;}
static uint16_t half(uint32_t address){uint16_t result;memcpy(&result,at(address),2);return result;}
static void store(uint32_t address,uint32_t value){memcpy(at(address),&value,4);}
static float real(uint32_t value){float result;memcpy(&result,&value,4);return result;}
static uint32_t bits(float value){uint32_t result;memcpy(&result,&value,4);return result;}
static uint64_t sx(uint32_t value){return (uint64_t)(int64_t)(int32_t)value;}
static void sample(uint32_t node,uint32_t frame,uint32_t weight,int blend){
 uint32_t target=word(word(node)+(blend?16u:8u));
#if UINTPTR_MAX > UINT32_MAX
 nocturneCallMotionSample(target,sx(node),frame,weight,blend);
#else
 if(blend)((void(*)(uint64_t,float,float))(uintptr_t)target)(sx(node),real(frame),real(weight));
 else ((void(*)(uint64_t,float))(uintptr_t)target)(sx(node),real(frame));
#endif
}
void ps2MotionChange(uint64_t controller,uint64_t cut,uint64_t type){sdfMotionChangeBlend(controller,cut,type,0.0f,0.0f);}
void ps2MotionSampleFrame(uint64_t controller,float frame){
 uint32_t c=(uint32_t)controller,f=bits(frame);*at(c+0x30)=4;
 uint32_t start=word(c+0x18),duration=word(c+0x14),elapsed=EE_FPU_SUB_S(f,start);
 int blending=EE_FPU_COMPARE_S(elapsed,duration,1);store(c+0x1c,f);
 if(!blending){
  int16_t length=count(word(c+0x10)+4);
  for(int32_t k=0;k<length;k++)sample(word(word(word(c+0x10)+12)+(uint32_t)k*4),f,0,0);
 }else{
  uint32_t weight=0;
  if(!EE_FPU_COMPARE_S(elapsed,0,1))weight=EE_FPU_DIV_S(elapsed,duration);
  if(EE_FPU_COMPARE_S(f,0,1))f=0;
  uint32_t request=word(c+0x10);int32_t k=0;
  if(count(request+4)>0){
   uint32_t data=word(request+12);
   for(;;){sample(word(data+(uint32_t)k*4),f,weight,1);k++;request=word(c+0x10);if(k>=count(request+4))break;data=word(request+12);}
  }
 }
}
uint64_t ps2MotionAdvanceFrame(uint64_t controller){
 uint32_t c=(uint32_t)controller;uint8_t state=*at(c+0x30);
 if(state==1){ps2MotionSampleFrame(controller,real(word(c+0x18)));return 0;}
 if(state!=4)return 0;
 uint32_t step=word(c+0x20),current=word(c+0x1c),length=half(c+0x2e);uint8_t loop=*at(c+0x32);
 uint32_t frame=EE_FPU_ADD_S(current,step),last=EE_FPU_CVT_S_W(length);uint64_t result=0;
 if(!loop){
  if(EE_FPU_COMPARE_S(last,frame,2)){ps2MotionSampleFrame(controller,real(last));*at(c+0x30)=5;return 1;}
 }else if(EE_FPU_COMPARE_S(last,frame,2)){
  store(c+0x14,0);result=2;store(c+0x18,0);
  do{frame=EE_FPU_SUB_S(frame,last);}while(EE_FPU_COMPARE_S(last,frame,2));
 }
 ps2MotionSampleFrame(controller,real(frame));return result;
}
