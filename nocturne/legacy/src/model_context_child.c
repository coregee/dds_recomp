/* Original 001DCF10 child/trail countdown, renewal, colour and placement. */
#include "model_context_child.h"
#include "model_draw_commands.h"
#include "model_state_copy.h"
#include "model_pose_evaluation.h"
#include "model_placement_outer.h"
#include "model_renderer.h"
#include "material_fiveword_pool.h"
#include "ee_vu_rotation.h"
#include "ee_fpu.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
#define NOTE(e) nocturneModelContextChildNoteEntry(e)
static void *at(uint32_t a){return nocturneResolveModelContextChildAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
#define NOTE(e) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void load(unsigned reg,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(reg,v);}
static void store(unsigned reg,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(reg,v);memcpy(at(a),v,16);}
static void scalar(unsigned vf,unsigned gpr,uint32_t bits)
{
    EE_RENDERER_WORD_TO_VU(vf,gpr,bits);
}
static void multiply(unsigned fd,unsigned fs,unsigned ft,int bc)
{
    uint32_t a[4],b[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);
    for(unsigned k=0;k<4;k++)out[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[bc<0?k:(unsigned)bc]);
    EE_ROT_VU_WRITE(fd,out);
}
/* The value profile's fixed-RTZ conversions match VITOF0/VFTOI0. */
static void convert(unsigned reg,int toFloat)
{
    uint32_t v[4];EE_ROT_VU_READ(reg,v);
    for(unsigned k=0;k<4;k++)v[k]=toFloat?EE_FPU_CVT_S_W(v[k]):EE_FPU_CVT_W_S(v[k]);
    EE_ROT_VU_WRITE(reg,v);
}
static void colourAccumulate(void)
{
    uint32_t gain[4],slope[4],v0[4],old[4],acc[4],of[4],out[4];
    EE_ROT_VU_READ(10,gain);EE_ROT_VU_READ(11,slope);EE_ROT_VU_READ(0,v0);EE_ROT_VU_READ(2,old);
    for(unsigned k=0;k<4;k++){uint64_t r=EE_ROT_VU_MUL(gain[k],v0[3]);acc[k]=(uint32_t)r;of[k]=(uint32_t)(r>>32)&1;}
    EE_ROT_ACC_WRITE(acc,of);
    /* VMADDx's broadcast is the old VF2.X, despite VF2 being its destination. */
    for(unsigned k=0;k<4;k++)out[k]=(uint32_t)EE_ROT_VU_MAC(acc[k],slope[k],old[0],of[k],0);
    EE_ROT_VU_WRITE(2,out);
}

void ps2ModelUpdateContextChildren(uint64_t context,uint64_t surfaces)
{
    ENTER(128);
#if UINTPTR_MAX > UINT32_MAX
    uint32_t frame=nocturneModelContextChildFrameAddress();
#else
    uint32_t privateWords[9];uint32_t frame=(uint32_t)(uintptr_t)privateWords;
#endif
    uint32_t c=(uint32_t)context,list=word(c+48),parent=word(c+24);
    uint16_t count=half(list+4);
    if(count){
        uint16_t countdown=(uint16_t)(half(list+10)-1u);sh(list+10,countdown);
        if(!countdown){
            uint16_t interval=half(list+8);sh(list+4,(uint16_t)(count-1u));
            sh(list+10,interval);NOTE(0x2a8af8);uint32_t slot=ps2PoolAllocate(12);
            uint32_t group=word(c+12),definition=word(group+24),textures=word(group+20);
            NOTE(0x2b1588);uint32_t child=(uint32_t)ps2ModelMake(sx(textures),sx(definition));
            uint32_t oldHead=word(list);sw(child+148,0x447a0000);
            sw(slot,oldHead);sw(slot+8,1);sw(list,slot);sw(slot+4,child);
        }
    }
    uint32_t packed=word(parent+28);sw(frame+16,packed);
    uint32_t channels[4];for(unsigned k=0;k<4;k++)channels[k]=(packed>>(k*8))&255u;
#if UINTPTR_MAX > UINT32_MAX
    EE_RENDERER_CPU_QUAD(2,channels);
#endif
    EE_ROT_VU_WRITE(10,channels);convert(10,1);scalar(2,4,0x3c000000);
    multiply(10,10,2,0);store(10,frame);
    uint32_t slot=word(list);
    while(slot){
        uint32_t remaining=word(slot+8),child=word(slot+4);remaining--;
        if(!remaining){
            uint32_t lifetime=word(list+12);NOTE(0x2b2268);ps2ModelCopyState(sx(child),sx(parent));
            remaining=lifetime;sw(slot+8,remaining);
        }else{NOTE(0x2b17e8);sdfModelEvalTm(sx(child));sw(slot+8,remaining);}
        load(10,list+16);load(11,list+32);load(12,frame);
        scalar(2,2,remaining-1u);convert(2,1);colourAccumulate();multiply(10,2,12,-1);
        scalar(2,22,0x43000000);multiply(10,10,2,0);convert(10,0);
        uint32_t values[4];EE_ROT_VU_READ(10,values);packed=0;
        for(unsigned k=0;k<4;k++)packed|=(values[k]&255u)<<(k*8);
#if UINTPTR_MAX > UINT32_MAX
        uint32_t packedQuad[4]={packed,0,0,0};EE_RENDERER_CPU_QUAD(3,packedQuad);
#endif
        sw(frame+32,packed);sw(child+28,packed);
        NOTE(0x2b1db8);ps2ModelPlaceMeshes(surfaces,sx(child));slot=word(slot);
    }
    LEAVE(128);
}
