/* Complete native file RPC request/completion/error bodies. */
#include "file_operations.h"
#include "file_rpc.h"
#include "sif_initialization.h"
#include "heap_queue.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveFileOperationsAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
static int signedLess(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint32_t resultAddress(uint32_t frame,uint32_t *result){
#if UINTPTR_MAX > UINT32_MAX
 (void)result;return nocturneFileOperationResultAddress(frame);
#else
 (void)frame;return (uint32_t)(uintptr_t)result;
#endif
}
static uint32_t operationSema(void){uint32_t packet[6];packet[1]=1;packet[2]=0;packet[5]=0;return ps2KernelCreateSema(packet);}
static void requestHeader(uint32_t sem,uint32_t result){w(0x59d4c0,sem);w(0x59d4c4,result);w(0x59d4c8,4);}
static void pending(void){
 (void)ps2KernelWaitSema(r(0x52c34c));
 for(uint32_t k=0;k<32;k++)if(r(0x52c2c0+k*4)==UINT32_MAX){uint32_t sem=r(0x59d4c0);w(0x52c2c0+k*4,sem);w(0x59d4c0,0-sem);break;}
 (void)ps2KernelSignalSema(r(0x52c34c));
}
static uint64_t submit(uint32_t command,uint32_t size){return ps2SifRpcCall(0x59e780,command,0,0x59d4c0,size,0x59e100,4,0,0);}
static uint64_t failed(uint32_t sem){(void)ps2KernelDeleteSema(sx(sem));(void)ps2FileRpcUnlock();return UINT64_C(0xfffffffffffffff5);}
uint64_t ps2FileRpcOpen(uint64_t path_raw,uint64_t flags,uint64_t mode){
 (void)ps2FileRpcLock(0);if(!r(0x52c340))(void)ps2FileRpcInitialize();
 if(ps2FileRpcVersionMismatch()){(void)ps2FileRpcUnlock();return UINT64_C(0xfffffffffffefffc);}
 uint64_t descriptor_raw=ps2FileRpcDescriptorTake();if(!descriptor_raw){(void)ps2FileRpcUnlock();return UINT64_C(0xffffffffffffffed);}
 uint32_t descriptor=(uint32_t)descriptor_raw,path=(uint32_t)path_raw,index=0;
 uint8_t c=*at(path);*at(0x59d4d4)=c;
 if(c)while(++index<1024){c=*at(path+index);*at(0x59d4d4+index)=c;if(!c)break;}
 if(index==1024)*at(0x59d8d3)=0;
 uint32_t id=(descriptor-0x59e580)>>4;w(0x59d4cc,(uint32_t)flags&0x6fffffff);w(0x59d4d0,(uint32_t)mode);w(0x59d8d4,id);
 uint32_t local_result,sem=operationSema(),out=resultAddress(0x150,&local_result);requestHeader(sem,out);
 if(submit(0,0x418)>>63)return failed(sem);
 uint32_t accepted=r(0x2059e100);(void)ps2FileRpcUnlock();
 if(!accepted){(void)ps2KernelDeleteSema(sx(sem));return UINT64_C(0xfffffffffffffff5);}
 (void)ps2KernelWaitSema(sem);(void)ps2KernelDeleteSema(sx(sem));uint32_t value=r(out);
 (void)ps2KernelWaitSema(r(0x52c348));
 if(value&0x80000000)w(descriptor+4,0);
 else{uint32_t state=r(descriptor+4);w(descriptor+4,state|(uint32_t)flags);w(descriptor,value);}
 (void)ps2KernelSignalSema(r(0x52c348));return value&0x80000000?sx(r(out)):id;
}
uint64_t ps2FileRpcClose(uint64_t id){
 uint32_t descriptor=(uint32_t)ps2FileRpcDescriptorLookup(id);(void)ps2FileRpcLock(1);
 if(!r(0x52c340)){(void)ps2FileRpcUnlock();return UINT64_MAX;}
 if(!descriptor||!r(descriptor+4)){(void)ps2FileRpcUnlock();return UINT64_C(0xfffffffffffffff7);}
 w(0x59d4cc,r(descriptor));w(0x59d4d0,(descriptor-0x59e580)>>4);
 uint32_t local_result,sem=operationSema(),out=resultAddress(0xa0,&local_result);requestHeader(sem,out);
 if(submit(1,0x14)>>63)return failed(sem);
 w(descriptor+4,0);uint32_t accepted=r(0x2059e100);(void)ps2FileRpcUnlock();
 if(!accepted){(void)ps2KernelDeleteSema(sx(sem));return UINT64_C(0xfffffffffffffff5);}
 (void)ps2KernelWaitSema(sem);(void)ps2KernelDeleteSema(sx(sem));uint32_t value=r(out);return value&0x80000000?sx(value):0;
}
static uint64_t transfer(uint64_t id,uint64_t operand,uint64_t bytes_or_origin,uint32_t command){
 uint32_t descriptor=(uint32_t)ps2FileRpcDescriptorLookup(id);(void)ps2FileRpcLock(command);
 if(!r(0x52c340)){(void)ps2FileRpcUnlock();return UINT64_MAX;}
 uint32_t flags;if(!descriptor||!(flags=r(descriptor+4))){(void)ps2FileRpcUnlock();return UINT64_C(0xfffffffffffffff7);}
 w(0x59d4cc,r(descriptor));
 if(command==4){w(0x59d4d0,(uint32_t)operand);w(0x59d4d4,(uint32_t)bytes_or_origin);w(0x59d4d8,(descriptor-0x59e580)>>4);}
 else if(command==2){w(0x59d4dc,(descriptor-0x59e580)>>4);w(0x59d4d0,(uint32_t)operand);w(0x59d4d4,(uint32_t)bytes_or_origin);}
 else{w(0x59d4ec,(descriptor-0x59e580)>>4);w(0x59d4d4,(uint32_t)bytes_or_origin);w(0x59d4d0,(uint32_t)operand);}
 uint32_t local_result,sem=operationSema(),out=resultAddress(command==4?0xc0:0xe0,&local_result);requestHeader(sem,out);
 if(flags&0x8000)pending();
 if(command==2){
  if(!(flags&0x20000000))ps2SifSyncDataCache(operand,bytes_or_origin);
  ps2SifSyncDataCache(0x59e140,0xa4);ps2SifSyncDataCache(0x59d4c0,32);
 }else if(command==3){
  uint32_t offset=(uint32_t)operand&15;uint64_t prefix=offset?16-offset:0;
  if(signedLess(bytes_or_origin,prefix))prefix=bytes_or_origin;
  if(!(flags&0x20000000))ps2SifSyncDataCache(operand,bytes_or_origin);
  uint32_t source=(uint32_t)operand|0x20000000;w(0x59d4d8,(uint32_t)prefix);
  if(!(prefix>>63)&&prefix)for(uint32_t k=0;k<(uint32_t)prefix;k++){uint8_t v=*at(source+k);*at(0x59d4dc+k)=v;}
 }
 uint32_t size=command==4?0x1c:command==2?0x20:0x30;
 if(submit(command,size)>>63)return failed(sem);
 uint32_t accepted=r(0x2059e100);(void)ps2FileRpcUnlock();
 if(!accepted){(void)ps2KernelDeleteSema(sx(sem));return UINT64_C(0xfffffffffffffff5);}
 if(flags&0x8000){(void)ps2KernelDeleteSema(sx(sem));return 0;}
 (void)ps2KernelWaitSema(sem);(void)ps2KernelDeleteSema(sx(sem));return sx(r(out));
}
uint64_t ps2FileRpcSeek(uint64_t id,uint64_t offset,uint64_t origin){return transfer(id,offset,origin,4);}
uint64_t ps2FileRpcRead(uint64_t id,uint64_t buffer,uint64_t bytes){return transfer(id,buffer,bytes,2);}
uint64_t ps2FileRpcWrite(uint64_t id,uint64_t buffer,uint64_t bytes){return transfer(id,buffer,bytes,3);}
