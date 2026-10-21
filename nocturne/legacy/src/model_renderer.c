/* Complete original002B9178..002B9AB8 renderer, including early shape exits.
 * Existing game helpers execute their actual algorithms. No GPU output supplied.
 * All branches are translated; original unusual unconditional loops retained. */
#include "model_renderer.h"
#include "model_render_context.h"
#include "model_draw_prerequisites.h"
#include "model_micro_skinning.h"
#include "model_render_streams.h"
#include "model_render_clip.h"
#include "model_render_clipping.h"
#include "model_render_packet_support.h"
#include "model_render_dma.h"
#include "resource_loader_flow.h"
#include "ee_vu_rotation.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t p){return nocturneResolveModelRendererAddress(p);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t p){return (void *)(uintptr_t)p;}
#endif
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint16_t half(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static uint8_t byte(uint32_t p){uint8_t v;memcpy(&v,at(p),1);return v;}
static uint64_t dword(uint32_t p){uint64_t v;memcpy(&v,at(p),8);return v;}
static void sw(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint32_t align16(uint32_t p){return (p+15)&~15u;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static void load(unsigned vf,uint32_t p){uint32_t v[4];memcpy(v,at(p),16);EE_ROT_VU_WRITE(vf,v);}
static void store(unsigned vf,uint32_t p){uint32_t v[4];EE_ROT_VU_READ(vf,v);memcpy(at(p),v,16);}
static void quad(uint32_t source,uint32_t destination,unsigned gpr){uint32_t v[4];memcpy(v,at(source),16);EE_RENDERER_CPU_QUAD(gpr,v);memcpy(at(destination),v,16);}
static void lightingQuads(unsigned middleGpr){quad(0x58f030,0x11004e30,2);quad(0x58f040,0x11004e40,middleGpr);quad(0x58f050,0x11004e50,2);}
static void uvMaterial(uint32_t material,unsigned first){
 EE_RENDERER_LD_SQ(first,dword(material+0x68),0x11004e60);
 EE_RENDERER_LD_SQ(first==2?3:2,dword(material+0x70),0x11004e70);
 EE_RENDERER_LD_SQ(first,dword(material+0x78),0x11004e80);
}
static void optionalUV(uint32_t c,uint32_t flags,uint32_t count,uint32_t *cursor){
 if(flags&0x100){uint32_t next=align16(*cursor+(count<<3));sw(c+0xa0,*cursor);*cursor=next;
  if(word(c+0x4c)&0x1000){next=align16(*cursor+(count<<3));sw(c+0xa4,*cursor);*cursor=next;}}
}
uint64_t ps2RenderMesh(uint64_t model,uint64_t mesh,uint64_t mask,uint64_t colour,uint64_t frame,uint64_t reverse,float rangeBias,float phaseBias){
 ENTER(320);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t c=nocturneModelRendererFrameAddress();
#else
 uint32_t locals[80];uint32_t c=(uint32_t)(uintptr_t)locals;
#endif
 uint32_t m=(uint32_t)model,d=(uint32_t)mesh,frameOffset=(uint32_t)frame<<7,v[4]={0x3f800000,0x3f800000,0x3f800000,0};EE_ROT_VU_WRITE(1,v);
 uint32_t matrix=word(m+0x30)+frameOffset;sw(c+0xb8,frameOffset);ps2RenderReadDefinition(sx(c),sx(d+0x10),mask);sw(c+0xac,reverse?0xbf800000:0x3f800000);
 uint32_t parent=word(m+0x10),materialIndex=half(d+6),materialTable=word(word(parent+0xc)+0xc);sw(c+0x58,(uint32_t)colour);uint32_t materialRecordAddress=materialTable+(materialIndex<<2);sw(c+0x5c,bits(rangeBias));uint32_t materialRecord=word(materialRecordAddress),effective=word(c+0x44),materialSlot=materialRecord+((uint32_t)frame<<2);sw(c+0x60,bits(phaseBias));uint32_t material=word(materialSlot+8);sw(c+0xb4,material);sw(c+0x54,material);sw(c+0xb0,effective);
 uint32_t triangles=(uint32_t)(int32_t)(int16_t)half(c+0x40),count=(uint32_t)(int32_t)(int16_t)half(c+0x42),flags=word(c+0x48),output=word(c+0x64);
 ps2RenderUpdateLighting(0x58f030,sx(material),colour,rangeBias,phaseBias);uint32_t kind=byte(d),cursor;
 if(kind==7||kind==8){
  if(kind==7){
   uint32_t source=word(c+0x90),nodes=half(source),indices=source+2,nodeTable=word(word(word(m+0x10))+0xc);
   cursor=align16(indices+nodes*2);sw(c+0x94,cursor);cursor=align16(cursor+triangles*6);
   quad(0x529710,0x11004dc0,2);quad(0x529720,0x11004dd0,3);quad(0x529730,0x11004de0,2);quad(0x529740,0x11004df0,3);
   quad(word(0x5520d8)+0x10,0x11004e00,2);quad(word(0x5520d8)+0x20,0x11004e10,2);quad(word(0x5520d8)+0x30,0x11004e20,2);
   uvMaterial(word(c+0xb4),3);
   uint32_t boneFrameOffset=nodes?word(c+0xb8):0;for(uint32_t k=0;k<nodes;k++){uint32_t node=word(nodeTable+((uint32_t)half(indices)<<2));indices+=2;uint32_t sourceMatrix=word(node+0x30)+boneFrameOffset,target=0x11004c00+k*112;for(unsigned q=0;q<7;q++)quad(sourceMatrix+q*16,target+q*16,q&1?3:2);}
   lightingQuads(3);EE_RENDERER_DMA_SYNC();cursor=(uint32_t)ps2RenderConsumeDmaVertices(sx(output),sx(cursor),sx(count),nodes*12+20,nodes*28+8);
  }else{
   for(unsigned k=0;k<4;k++)load(28+k,matrix+k*16);ps2ModelLoadComposeVuMatrix(0x529710);ps2RenderComposeNormalBasis(sx(matrix));for(unsigned k=0;k<4;k++)store(28+k,c+k*16);
   cursor=align16(word(c+0x90));sw(c+0x94,cursor);cursor=align16(cursor+triangles*6);
   EE_RENDERER_LD_SQ(2,dword(word(c+0xb4)+0x68),0x11004e60);EE_RENDERER_LD_SQ(3,dword(word(c+0xb4)+0x70),0x11004e70);EE_RENDERER_LD_SQ(2,dword(word(c+0xb4)+0x78),0x11004e80);
   lightingQuads(2);EE_RENDERER_DMA_SYNC();cursor=(uint32_t)ps2RenderConsumeDmaVertices(sx(output),sx(cursor),sx(count),28,32);
  }
  EE_RENDERER_DMA_FINISH();if(word(c+0x4c)&0x1000){sw(c+0xa4,cursor);cursor=align16(cursor+(count<<3));}sw(c+0xa8,cursor);ps2RenderBuildPacket(sx(c));
 }else if(flags&0x800){
  uint32_t source=word(c+0x90),nodes=half(source),indices=source+2,nodeTable=word(word(word(m+0x10))+0xc);sw(c+0xbc,nodeTable);cursor=align16(indices+nodes*2);
  if(flags&0x20){sw(c+0x94,cursor);cursor=align16(cursor+triangles*6);}
  if(nodes){sw(c+0xd4,count<<4);sw(c+0xc0,count*12);}
  for(uint32_t k=0;k<nodes;k++){
   uint32_t positions=cursor,node=word(word(c+0xbc)+((uint32_t)half(indices)<<2));indices+=2;cursor=align16(positions+word(c+0xd4));uint32_t normals=cursor,nodeMatrix=word(node+0x30)+word(c+0xb8);
   if(flags&0x80){cursor=align16(normals+word(c+0xc0));if(k==0)ps2RenderTransformWeightedVertices(sx(output),sx(count),sx(nodeMatrix),sx(positions),sx(normals));else ps2RenderAccumulateWeightedVertices(sx(output),sx(count),sx(nodeMatrix),sx(positions),sx(normals));}
   else if(k==0)ps2RenderTransformWeightedPointsOddLoop(sx(output),sx(count),sx(nodeMatrix),sx(positions));else ps2RenderAccumulateWeightedPoints(sx(output),sx(count),sx(nodeMatrix),sx(positions));
  }
  if(flags&0x80)ps2RenderNormalizeNormals(sx(output),sx(count));optionalUV(c,flags,count,&cursor);sw(c+0xa8,cursor);
  for(unsigned k=0;k<4;k++)load(28+k,0x529710+k*16);for(unsigned k=0;k<3;k++)load(24+k,word(0x5520d8)+0x10+k*16);
  if(word(c+0xb0)&0x10)ps2RenderLightClipRecordsUV(sx(output),sx(count),sx(word(c+0xa0)),sx(word(c+0xb4)+0x68));else ps2RenderLightClipRecords(sx(output),sx(count));ps2RenderBuildPacket(sx(c));
 }else if(flags&0x1000){
  uint32_t selector=word(d+8),shape=word(word(m+0x10)+0x10),descriptor=selector>>16,frames=selector&65535;sw(c+0xc8,selector);cursor=align16(word(c+0x90));sw(c+0xc8,frames);
  if(!shape){LEAVE(320);return 0;}
  if(flags&0x20){sw(c+0x94,cursor);cursor=align16(cursor+triangles*6);}
  if((int64_t)descriptor>=(int64_t)(int16_t)half(shape+4)){LEAVE(320);return 0;}
  uint32_t packedBytes=count*12,blockStride=align16(packedBytes),shapeRecord=word(shape+12)+(descriptor<<4);sw(c+0xc4,shapeRecord);
  if(flags&0x80){ps2RenderCopyPackedVectorPairs(sx(output),sx(count),sx(cursor),sx(align16(cursor+packedBytes)));blockStride<<=1;}else ps2RenderCopyPackedVectors(sx(output),sx(count),sx(cursor));
  sw(c+0xcc,packedBytes);sw(c+0xd0,word(c+0xc4)+4);
  uint32_t threshold=word(0x54e74c);for(uint32_t k=0;k<2;k++){
   uint32_t record=word(c+0xd0)+k*8,weight=word(record);
   if(EE_FPU_COMPARE_S(threshold,weight,1)){uint32_t index=word(word(c+0xc4)+k*8),offset=index*blockStride+blockStride;
    if((int32_t)index<(int32_t)word(c+0xc8)){uint32_t positions=cursor+offset;if(flags&0x80)ps2RenderBlendPackedVectorPairs(sx(output),sx(count),sx(positions),sx(align16(positions+word(c+0xcc))),real(weight));else ps2RenderBlendPackedVectors(sx(output),sx(count),sx(positions),real(weight));}}
  }
  cursor+=word(c+0xc8)*blockStride;if(flags&0x80)ps2RenderNormalizeNormals(sx(output),sx(count));optionalUV(c,flags,count,&cursor);sw(c+0xa8,cursor);
  for(unsigned k=0;k<4;k++)load(28+k,matrix+k*16);ps2ModelLoadComposeVuMatrix(0x529710);ps2RenderComposeNormalBasis(sx(matrix));
  if(word(c+0xb0)&0x10)ps2RenderLightClipRecordsUV(sx(output),sx(count),sx(word(c+0xa0)),sx(word(c+0xb4)+0x68));else ps2RenderLightClipRecords(sx(output),sx(count));ps2RenderBuildPacket(sx(c));
 }else{
  cursor=align16(word(c+0x90));if(flags&0x20){sw(c+0x94,cursor);cursor=align16(cursor+triangles*6);}uint32_t positions=cursor,packedBytes=count*12;cursor=align16(positions+packedBytes);
  if(flags&0x80){sw(c+0x9c,cursor);cursor=align16(cursor+packedBytes);}optionalUV(c,flags,count,&cursor);sw(c+0xa8,cursor);
  for(unsigned k=0;k<4;k++)load(28+k,matrix+k*16);ps2ModelLoadComposeVuMatrix(0x529710);ps2RenderComposeNormalBasis(sx(matrix));
  if(word(c+0xb0)&0x10)ps2RenderLightClipPackedUV(sx(output),sx(count),sx(positions),sx(word(c+0x9c)),sx(word(c+0xa0)),sx(word(c+0xb4)+0x68));else ps2RenderLightClipPacked(sx(output),sx(count),sx(positions),sx(word(c+0x9c)));ps2RenderBuildPacket(sx(c));
 }
 uint64_t result=ps2RenderFinalizePacket(sx(c));LEAVE(320);return result;
}
