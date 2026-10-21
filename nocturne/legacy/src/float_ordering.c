/* Original float-key ordering, AVL insertion rotations and packet collection. */
#include "float_ordering.h"
#include "script_compare.h"
#include "resource_loader_flow.h"
#include "deferred_drain.h"
#include "render_chain.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t p){return nocturneResolveFloatOrderingAddress(p);}
#define LOCAL(name,n) uint32_t name=nocturneFloatOrderingFrameAddress()
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t p){return (void *)(uintptr_t)p;}
#define LOCAL(name,n) uint32_t name##Words[n];uint32_t name=(uint32_t)(uintptr_t)name##Words
#endif
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void store(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
uint64_t ps2OrderingRotatePositive(uint64_t child,uint64_t parent){
 uint32_t c=(uint32_t)child,p=(uint32_t)parent;uint64_t result=child;
 if((int32_t)word(c+12)<0){
  uint32_t middle=word(c+4),right=word(middle+4),balance=word(middle+12);result=sx(middle);
  store(p,right);store(c+4,word(middle));store(middle+4,p);store(middle,c);
  if((int32_t)balance>0){store(p+12,0xffffffff);store(c+12,0);}else{store(p+12,0);store(c+12,1);}
  store(middle+12,0);
 }else{uint32_t right=word(c+4);store(p+12,0);store(p,right);store(c+12,0);store(c+4,p);}
 return result;
}
uint64_t ps2OrderingRotateNegative(uint64_t child,uint64_t parent){
 uint32_t c=(uint32_t)child,p=(uint32_t)parent;uint64_t result=child;
 if((int32_t)word(c+12)>0){
  uint32_t middle=word(c),left=word(middle),balance=word(middle+12);result=sx(middle);
  store(p+4,left);store(c,word(middle+4));store(middle,p);store(middle+4,c);
  if((int32_t)balance>0){store(p+12,0xffffffff);store(c+12,0);}else{store(p+12,0);store(c+12,1);}
  store(middle+12,0);
 }else{uint32_t left=word(c);store(p+12,0);store(p+4,left);store(c+12,0);store(c,p);}
 return result;
}
void ps2OrderingRebalanceInsertion(uint64_t ancestors,uint64_t count,uint64_t child,uint64_t rootSlot){
 ENTER(48);uint64_t remaining=count,replacement=0;uint32_t parent=0,base=(uint32_t)ancestors;
 if((int64_t)remaining>0){
  uint32_t cursor=base+((uint32_t)remaining<<2);
  do{
   cursor-=4;parent=word(cursor);
   uint32_t balance=word(parent+12);remaining=sx((uint32_t)remaining-1);
   balance+=child==sx(word(parent))?1u:0xffffffffu;store(parent+12,balance);
   if(balance==0){LEAVE(48);return;}
   if((int32_t)balance>1){replacement=ps2OrderingRotatePositive(child,sx(parent));break;}
   if((int32_t)balance<-1){replacement=ps2OrderingRotateNegative(child,sx(parent));break;}
   child=sx(parent);
  }while((int64_t)remaining>0);
  if((int64_t)remaining>0){
   remaining=sx((uint32_t)remaining-1);uint32_t above=word(base+((uint32_t)remaining<<2));
   if(sx(word(above))==sx(parent))store(above,(uint32_t)replacement);else store(above+4,(uint32_t)replacement);
   LEAVE(48);return;
  }
 }
 if(replacement)store((uint32_t)rootSlot,(uint32_t)replacement);LEAVE(48);
}
void ps2OrderingInsertFloatKey(uint64_t rootSlot,uint64_t tag){
 ENTER(176);LOCAL(path,32);uint32_t root=(uint32_t)rootSlot,t=(uint32_t)tag,slot=root,node=word(root),depth=0,key=word(t+12);
 while(node){
  uint32_t chain=word(node+8),current=word(chain+12);
  if(EE_FPU_COMPARE_S(key,current,0)){store(t,chain);store(node+8,t);LEAVE(176);return;}
  store(path+depth*4,node);depth++;slot=node;
  if(!EE_FPU_COMPARE_S(current,key,1))slot=node+4;
  node=word(slot);
 }
 store(t,0);uint32_t created=ps2WorkBufferTake(16);store(created,0);store(created+4,0);store(created+8,t);store(slot,created);store(created+12,0);
 if(depth)ps2OrderingRebalanceInsertion(sx(path),sx(depth),sx(created),rootSlot);LEAVE(176);
}
void ps2OrderingSubmit(uint64_t surface,uint64_t tag){
 ENTER(16);uint32_t s=(uint32_t)surface,t=(uint32_t)tag;
 if(word(t+4)){
  if(word(t+12)!=0xffff){LEAVE(16);ps2OrderingInsertFloatKey(sx(s+24),tag);return;}
  store(t,word(s+12));store(s+12,t);
 }LEAVE(16);
}
void ps2OrderingCollectList(uint64_t head,uint64_t firstSlot,uint64_t lastSlot){
 ENTER(32);uint32_t tag=(uint32_t)head,last=(uint32_t)lastSlot;
 if(tag){
  uint32_t previous=word(last);if(previous)ps2DrawTagLinkState(previous,tag);else store((uint32_t)firstSlot,tag);
  do{uint32_t next=word(tag);if(!next)break;ps2DrawTagLinkState(tag,next);tag=next;}while(1);
  store(last,tag);
 }LEAVE(32);
}
void ps2OrderingCollectTree(uint64_t root,uint64_t firstSlot,uint64_t lastSlot){
 ENTER(32);uint32_t node=(uint32_t)root;
 do{
  uint32_t child=word(node);if(child)ps2OrderingCollectTree(sx(child),firstSlot,lastSlot);
  ps2OrderingCollectList(sx(word(node+8)),firstSlot,lastSlot);node=word(node+4);
 }while(node);LEAVE(32);
}
void ps2OrderingBuildChain(uint64_t surface){
 ENTER(32);LOCAL(local,2);uint32_t s=(uint32_t)surface;store(local,0);store(local+4,0);
 ps2OrderingCollectList(sx(word(s+12)),sx(local),sx(local+4));uint32_t root=word(s+24);
 if(root)ps2OrderingCollectTree(sx(root),sx(local),sx(local+4));
 uint32_t first=word(local),last=word(local+4);store(s+8,last);store(s+4,first);LEAVE(32);
}
void ps2OrderingApplyMode(uint64_t surface,uint64_t mode,uint64_t tag){
 ENTER(16);
 if(mode==0){LEAVE(16);ps2OrderingBuildChain(surface);return;}
 if(mode==1){uint32_t t=(uint32_t)tag,s=(uint32_t)surface;if(word(t+4)){store(t,word(s+12));store(s+12,t);}}
 LEAVE(16);
}
