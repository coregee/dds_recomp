/* Complete original 002B9048 consumer; bounded instruction comparisons pass.
 * Device providers must process real packets/programs, not inject vertices. */
#include "model_render_dma.h"
#include "resource_loader_flow.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveRenderDmaAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int64_t signed64(uint64_t v){return v>>63?-1-(int64_t)~v:(int64_t)v;}
static void store(unsigned vf,uint32_t a){uint32_t v[4];EE_RENDER_DMA_VU_READ(vf,v);memcpy(at(a),v,16);}
static void classification(uint32_t a,uint32_t bits){
 uint64_t clip=sx((uint32_t)((int32_t)bits>>6)),side=bits&3;uint32_t out[4]={0,0,0,0};
 for(unsigned k=0;k<8;k++){unsigned lane=k/2,shift=(k%2)*16;out[lane]|=(uint32_t)((side>>(k*8))&255)<<shift;out[lane]|=(uint32_t)((clip>>(k*8))&255)<<(shift+8);}
 EE_RENDER_DMA_CPU_QUAD(2,out);memcpy(at(a),out,4);
}
uint64_t ps2RenderConsumeDmaVertices(uint64_t output,uint64_t stream,uint64_t count,uint64_t overhead,uint64_t stride){
#if UINTPTR_MAX > UINT32_MAX
 nocturneResourceFrameEnter(32);
#endif
 uint32_t p=(uint32_t)output,processed=0;
 if(signed64(count)>0){
  uint32_t remaining=(uint32_t)count;
  do{
   uint32_t address=(uint32_t)stream&0x0fffffff,batch=(int32_t)remaining<25?remaining:24,bytes=(uint32_t)stride*batch,qwords=(uint32_t)((int32_t)(bytes+(uint32_t)overhead+15)>>4);
   processed+=batch;EE_RENDER_DMA_WRITE32(0x10008020,qwords);EE_RENDER_DMA_WRITE32(0x10008010,address);stream=sx((uint32_t)stream+(qwords<<4));EE_RENDER_DMA_WRITE32(0x10008000,0x101);
   for(;;){while(EE_RENDER_DMA_READ32(0x10008000)&0x100){}if(!(EE_RENDER_DMA_READ32(0x10003800)&0x0f000003))break;}
   EE_RENDER_DMA_CTC2I(2,0x60);
   do{
    EE_RENDER_DMA_LQI(4,2);EE_RENDER_DMA_LQI(5,2);EE_RENDER_DMA_ILWR(10,2,3);EE_RENDER_DMA_LQI(6,2);EE_RENDER_DMA_LQI(7,2);
    store(4,p);store(5,p+16);store(6,p+48);uint32_t bits=EE_RENDER_DMA_CFC2(10);store(7,p+32);--batch;classification(p+80,bits);p+=96;
   }while(batch);
   remaining=(uint32_t)count-processed;
  }while(signed64(sx(processed))<signed64(count));
 }
#if UINTPTR_MAX > UINT32_MAX
 nocturneResourceFrameLeave(32);
#endif
 return stream;
}
