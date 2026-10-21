/* Complete original 002B1950 nonempty node/group/reference placement loop. */
#include "model_placement_simple.h"
#include "model_material_update.h"
#include "model_draw_prerequisites.h"
#include "model_pose_evaluation.h"
#include "model_draw_commands.h"
#include "movie_draw.h"
#include "deferred_drain.h"
#include "ee_vu_rotation.h"
#include "resource_loader_flow.h"
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
#include "model_renderer.h"
#endif
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolveModelPlacementAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static int32_t signedHalf(uint32_t a){uint32_t v=half(a);return v&0x8000u?(int32_t)v-65536:(int32_t)v;}
static uint8_t byte(uint32_t a){uint8_t v;memcpy(&v,at(a),1);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void matrix(uint32_t a){for(unsigned k=0;k<4;k++)load(28+k,a+k*16);}
void ps2ModelPlaceReferenceMeshes(uint64_t surfaces,uint64_t root){
 ENTER(192);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t f=nocturneModelPlacementFrameAddress();
#else
 uint32_t locals[20];uint32_t f=(uint32_t)(uintptr_t)locals;
#endif
 uint32_t r=(uint32_t)root,mode=byte(0x551842);mode=mode&0x80u?mode|0xffffff00u:mode;sw(f+16,(uint32_t)surfaces);
 uint32_t materialList=word(r+12);sw(f+24,mode);ps2MaterialUpdateList(sx(materialList),sx(mode));
 uint32_t colour=word(r+28),defaultFirst=word(0x5518b0);sw(f+28,colour);uint32_t first=word(r+128),flags=byte(r+25);sw(f+40,first);
 uint32_t defaultSecond=word(0x5518b4),second=word(r+132);first=word(f+40);sw(f+44,second);if(!first)first=defaultFirst;second=word(f+44);sw(f+40,first);
 uint32_t mask=half(r+26);if(!second)second=defaultSecond;sw(f+44,second);sw(f+36,mask);uint32_t byteFlags=byte(0x55189c);
 uint32_t f22,f21;if(flags&2){f22=word(r+136);f21=word(r+140);}else{f22=word(0x5518a8);f21=word(0x5518ac);}
 uint32_t array=word(r);sw(f+20,0);sw(f+48,0);
 if(signedHalf(array+4)>0){
  sw(f+52,byteFlags<<16);
  do{
   uint32_t node=word(word(array+12)+(word(f+20)<<2)),definition=word(node+56);
   if(definition&&half(definition)==1){
    uint32_t groups=word(definition+68);
    if(groups&&!(half(node+20)&0x11)){
     uint32_t tm=node+192;matrix(tm);ps2ModelLoadComposeVuMatrix(0x529710);uint32_t bounds=word(node+52);
     if(bounds&&ps2ModelBoundsClipMask(sx(bounds)))array=word(r);
     else{
      uint32_t row[4],v[4];EE_ROT_VU_READ(31,row);EE_ROT_VU_WRITE(10,row);EE_ROT_VU_READ(2,v);v[0]=(uint32_t)EE_ROT_VU_ADD(0,row[3]);EE_ROT_VU_WRITE(2,v);uint32_t key=v[0];
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
      if(g_modelRendererActive)EE_RENDERER_CPU_QUAD(2,v);
#endif
      sw(f+32,word(f+28));if(half(node+20)&2)sw(f+32,word(node+28));uint32_t nodeMask=half(node+22)&word(f+36);
      for(unsigned k=0;k<4;k++)sw(f+k*4,0);ps2ModelDrawStoreFloat(real(word(r+148)));
      uint32_t group=word(groups);groups+=4;
      if(group){
       uint64_t header=((uint64_t)(nodeMask|word(f+52))<<32)|0x6102c000u;sd(f+56,header);sw(f+64,(uint32_t)((int32_t)word(f+32)<0));
       do{
        uint32_t bucket=word(group)>>16;if(!bucket)bucket=word(f+64)==0;uint32_t slot=f+(bucket<<2),chain=word(slot);group+=4;
        if(!chain){
         chain=(uint32_t)ps2DrawChainCreate(0);sw(chain+12,key);sw(chain+16,word(f+40));sw(slot,chain);sw(chain+20,word(f+44));uint32_t packet=ps2WorkBufferTake(192);
         sd(packet,0x10000008u);sd(packet+8,UINT64_C(0x6c07c00000000000));matrix(tm);ps2ModelWriteLightingPacket(sx(packet+16));
         sw(packet+160,0x6e01c002);sw(packet+168,0x6003c003);sd(packet+144,0x20000002u);sw(packet+164,word(f+32));sw(packet+184,0x04000004);sw(packet+172,word(r+148));sw(packet+188,0x14000000);
         sw(packet+176,f22);uint64_t value;memcpy(&value,at(f+56),8);sd(packet+152,value);sw(packet+180,f21);ps2DmaChainAppendWithTail(chain,packet,packet+144);
        }
        uint32_t command=word(group);group+=4;
        while(command){
         if(byte(command)==1){
          uint32_t packet=ps2WorkBufferTake(48),packed=word(command+4);uint32_t p=(uint32_t)ps2ModelWriteIndexedAssetPacket(root,packed>>16,sx(packet),sx(word(f+24)));
          uint64_t tag=((uint64_t)(word(command+8)&0x0fffffffu)<<32)|(packed&0xffffu)|0x30000000u;sd(p+8,0);sd(p,tag);p+=16;sd(p,0x20000000);sd(p+8,0);ps2DmaChainAppendWithTail(chain,packet,p);
         }
         command=word(group);group+=4;
        }
        group=word(groups);groups+=4;
       }while(group);
      }
      for(unsigned k=0;k<4;k++){
       uint32_t chain=word(f+k*4),table=word(f+16);
       if(chain){
        uint32_t surface=word(table+k*4),callback=word(surface+16);sw(f+48,1);
#if UINTPTR_MAX > UINT32_MAX
        nocturneModelPlacementSubmit(callback,sx(surface),sx(chain));
#else
        ((void (*)(uint64_t,uint64_t))(uintptr_t)callback)(sx(surface),sx(chain));
#endif
       }
       sw(f+k*4,0);
      }
      array=word(r);
     }
    }
   }
   sw(f+20,word(f+20)+1);
  }while((int32_t)word(f+20)<signedHalf(array+4));
 }
 if(word(f+48)){uint8_t flagsOut=byte(r+25)|0x10;memcpy(at(r+25),&flagsOut,1);}LEAVE(192);
}
