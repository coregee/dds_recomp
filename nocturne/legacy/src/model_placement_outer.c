/* Complete 002B1DB8 node/command dispatch, with actual renderer and callbacks. */
#include "model_placement_outer.h"
#include "model_placement_simple.h"
#include "model_material_update.h"
#include "model_draw_prerequisites.h"
#include "model_packet_list.h"
#include "model_renderer.h"
#include "movie_draw.h"
#include "render_chain.h"
#include "deferred_drain.h"
#include "ee_vu_rotation.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolveModelPlacementOuterAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){uint8_t v;memcpy(&v,at(a),1);return v;}
static int32_t signedHalf(uint32_t a){uint32_t v=half(a);return v&0x8000u?(int32_t)v-65536:(int32_t)v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static void sb(uint32_t a,uint8_t v){memcpy(at(a),&v,1);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static void matrix(uint32_t a){for(unsigned k=0;k<4;k++){uint32_t v[4];memcpy(v,at(a+k*16),16);EE_ROT_VU_WRITE(28+k,v);}}
void ps2ModelPlaceMeshes(uint64_t surfaces,uint64_t root){
 ENTER(176);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t f=nocturneModelPlacementOuterFrameAddress();
#else
 uint32_t locals[16];uint32_t f=(uint32_t)(uintptr_t)locals;
#endif
 uint32_t r=(uint32_t)root;sw(f+16,(uint32_t)surfaces);uint8_t flags=byte(r+25)&0xefu;sb(r+25,flags);
 if(flags&4)ps2ModelPlaceReferenceMeshes(surfaces,root);
 uint32_t mode=byte(0x551842);if(mode&0x80u)mode|=0xffffff00u;
 ps2MaterialUpdateList(sx(word(r+12)),sx(mode));sw(f+24,word(r+28));
 uint32_t defaultSecond=word(0x5518b4),first=word(r+128);flags=byte(r+25);sw(f+36,first);
 uint32_t defaultFirst=word(0x5518b0),second=word(r+132);first=word(f+36);if(!first)first=defaultFirst;if(!second)second=defaultSecond;sw(f+36,first);
 uint32_t byteFlags=byte(0x55189c);sw(f+28,half(r+26));uint32_t range,phase;
 if(flags&2){range=word(r+136);phase=word(r+140);}else{range=word(0x5518a8);phase=word(0x5518ac);}
 uint32_t array=word(r),reverse=(flags&8)!=0;sw(f+20,0);sw(f+40,0);
 if(signedHalf(array+4)>0){
  sw(f+44,byteFlags<<16);sw(f+60,mode<<2);
  do{
   uint32_t node=word(word(array+12)+(word(f+20)<<2)),command=word(node+40+word(f+60));
   if(command&&!(half(node+20)&0x11u)){
    matrix(node+192);ps2ModelLoadComposeVuMatrix(0x529710);uint32_t bounds=word(node+52);
    if(bounds&&ps2ModelBoundsClipMask(sx(bounds)))array=word(r);
    else{
     uint32_t row[4],v[4];EE_ROT_VU_READ(31,row);EE_ROT_VU_WRITE(10,row);EE_ROT_VU_READ(2,v);v[0]=(uint32_t)EE_ROT_VU_ADD(0,row[3]);EE_ROT_VU_WRITE(2,v);
#if UINTPTR_MAX > UINT32_MAX
     EE_RENDERER_CPU_QUAD(2,v);
#endif
     uint32_t depth=v[0],colour=word(f+24);if(half(node+20)&2u)colour=word(node+28);sw(f+32,half(node+22)&word(f+28));
     for(unsigned k=0;k<4;k++)sw(f+k*4,0);ps2ModelDrawStoreFloat(real(word(r+148)));sw(f+56,(uint32_t)((int32_t)colour<0));
     sd(f+48,((uint64_t)(word(f+32)|word(f+44))<<32)|0x6102c000u);
     do{
      uint32_t bucket=byte(command+5);if(!bucket)bucket=word(f+56)==0;uint32_t slot=f+(bucket<<2),chain=word(slot);
      if(!chain){
       chain=(uint32_t)ps2DrawChainCreate(0);sw(chain+12,depth);uint32_t firstState=word(f+36);sw(slot,chain);sw(chain+16,firstState);sw(chain+20,second);
       uint32_t packet=ps2WorkBufferTake(64);ps2ModelWriteNodeMatrixReference(sx(node),sx(packet),sx(mode));
       sw(packet+40,0x6003c003);sw(packet+32,0x6e01c002);sw(packet+36,colour);sd(packet+16,0x20000002);uint32_t value=word(r+148);
       sw(packet+56,0x04000004);sw(packet+44,value);sw(packet+60,0x14000000);uint64_t header;memcpy(&header,at(f+48),8);sw(packet+48,range);sd(packet+24,header);sw(packet+52,phase);
       ps2DrawTagAppendReference(chain,packet);
      }
      uint32_t kind=byte(command+4);
      if(kind==1){
       if(!reverse){
        uint32_t packet=ps2WorkBufferTake(32),zero[4]={0,0,0,0};
#if UINTPTR_MAX > UINT32_MAX
        EE_RENDERER_CPU_QUAD(5,zero);
#endif
        memcpy(at(packet+16),zero,16);
        uint16_t count=0;memcpy(at(packet),&count,2);sw(packet+4,(command+16)&0x0fffffffu);sd(packet+8,0);ps2DrawTagAppendCall(chain,packet);
       }
      }else if(kind==2){if(!reverse)ps2ModelAppendWeightedMeshPackets(sx(node),sx(word(command+8)),sx(chain),sx(mode));}
      else if(kind==3){
       ps2ModelDrawStoreWord(sx(word(f+36)));ps2ModelDrawCacheVector(sx(second));
       uint64_t packet=ps2RenderMesh(sx(node),sx(word(command+8)),sx(word(f+32)),sx(colour),sx(mode),reverse,real(range),real(phase));if(packet)ps2DmaChainAppend(chain,(uint32_t)packet);
      }
      command=word(command);
     }while(command);
     for(unsigned k=0;k<4;k++){
      uint32_t chain=word(f+k*4),table=word(f+16);
      if(chain){uint32_t surface=word(table+k*4);sw(f+40,1);uint32_t callback=word(surface+16);
#if UINTPTR_MAX > UINT32_MAX
       nocturneModelPlacementOuterSubmit(callback,sx(surface),sx(chain));
#else
       ((void (*)(uint64_t,uint64_t))(uintptr_t)callback)(sx(surface),sx(chain));
#endif
      }
      sw(f+k*4,0);
     }
     array=word(r);
    }
   }
   sw(f+20,word(f+20)+1);
  }while((int32_t)word(f+20)<signedHalf(array+4));
 }
 if(word(f+40))sb(r+25,byte(r+25)|0x10u);LEAVE(176);
}
