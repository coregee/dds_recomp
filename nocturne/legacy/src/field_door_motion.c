/* Complete original WAP door record initialization, start and step owners.
 * The 256 native 100-byte definitions and 84-byte work records are not HD
 * managed objects. Both leaves retain the original asymmetric close policy. */
#include "field_door_motion.h"
#include "scene_lookup.h"
#include "basic_pose.h"
#include "battle_presentation.h"
#include "ee_vu_rotation.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "nocturne.h"
#include "ps2_memory.h"
#include <string.h>
#if defined(NOCTURNE_FIELD_DOOR_PROBE)
void nocturneFieldDoorProbeVuRead(unsigned reg,uint32_t words[4]);
void nocturneFieldDoorProbeVuWrite(unsigned reg,const uint32_t words[4]);
void nocturneFieldDoorProbeAccWrite(const uint32_t words[4],const uint32_t overflow[4]);
#define EE_ROT_VU_READ nocturneFieldDoorProbeVuRead
#define EE_ROT_VU_WRITE nocturneFieldDoorProbeVuWrite
#define EE_ROT_ACC_WRITE nocturneFieldDoorProbeAccWrite
#endif
static uint8_t *at(uint32_t a){return nocturneResolveFieldDoorMotionAddress(a);}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t neg(uint32_t v){return v^0x80000000u;}
static int lt(uint32_t a,uint32_t b){return (int)EE_FPU_COMPARE_S(a,b,1);}
static int le(uint32_t a,uint32_t b){return (int)EE_FPU_COMPARE_S(a,b,2);}
static void loadvu(unsigned r,uint32_t p){uint32_t v[4];memcpy(v,at(p),16);EE_ROT_VU_WRITE(r,v);}
void ps2FieldDoorInit_00142FB0(void)
{
    for(uint32_t i=0;i<256;i++){
        uint32_t p=0x562830u+i*84u;
        for(uint32_t j=0;j<21;j++)if(j!=8)w32(p+j*4u,j==3||j==5?UINT32_MAX:0);
    }
    w32(0x54ee04u,UINT32_MAX);
}
void ps2FieldDoorImport_001430D0(uint64_t source)
{
    /* Native loads an entire32-byte group before its stores. Retain that
     * order for overlapping and unaligned input rather than memmove policy. */
    uint32_t from=(uint32_t)source,to=0x303050u,end=from+0x64a0u;
    do{uint8_t group[32];memcpy(group,at(from),32);memcpy(at(to),group,32);from+=32;to+=32;}while(from!=end);
}
uint32_t ps2FieldDoorAtan2Bits_002C0258(uint32_t x,uint32_t z)
{
    int nz=lt(z,0);if(nz)z=neg(z);
    int nx=lt(x,0);if(nx)x=neg(x);
    uint32_t angle;
    if(lt(x,z))angle=sdfAtanBits(EE_FPU_DIV_S(x,z));
    else angle=EE_FPU_SUB_S(r32(0x54e784u),sdfAtanBits(EE_FPU_DIV_S(z,x)));
    if(nz)angle=EE_FPU_SUB_S(r32(0x54e788u),angle);
    return nx?neg(angle):angle;
}
uint32_t ps2FieldDoorHeadingBits_002C0B60(void)
{
    sdfQuatToMatrix();loadvu(10,0x529620u);
    uint32_t input[4],row[3][4],acc[4],of[4],out[4];
    EE_ROT_VU_READ(10,input);for(unsigned j=0;j<3;j++)EE_ROT_VU_READ(28+j,row[j]);
    for(unsigned i=0;i<4;i++){
        uint64_t v=EE_ROT_VU_MUL(row[0][i],input[0]);acc[i]=(uint32_t)v;of[i]=(uint32_t)(v>>32)&1;
        v=EE_ROT_VU_MAC(acc[i],row[1][i],input[1],of[i],0);acc[i]=(uint32_t)v;of[i]=(uint32_t)(v>>32)&1;
        out[i]=(uint32_t)EE_ROT_VU_MAC(acc[i],row[2][i],input[2],of[i],0);
    }
    EE_ROT_ACC_WRITE(acc,of);EE_ROT_VU_WRITE(10,out);
    return ps2FieldDoorAtan2Bits_002C0258(out[2],out[0]);
}
static uint32_t degrees(uint32_t divisor)
{
    uint32_t angle=EE_FPU_DIV_S(EE_FPU_MUL_S(ps2FieldDoorHeadingBits_002C0B60(),0x43340000u),r32(divisor));
    while(lt(angle,0))angle=EE_FPU_ADD_S(angle,0x43b40000u);
    while(lt(0x43b40000u,angle))angle=EE_FPU_SUB_S(angle,0x43b40000u);
    return angle;
}
static unsigned quadrant(uint32_t angle,uint32_t maximum)
{
    /* Keep native comparison order; every comparison updates FCSR23. */
    if(le(0x42340000u,angle)&&le(angle,0x43070000u))return 1;
    if(le(0x43070000u,angle)&&le(angle,0x43610000u))return 0;
    if(le(0x43610000u,angle)&&le(angle,r32(maximum)))return 3;
    return 2;
}
static void velocity(uint32_t p,int type,unsigned direction)
{
    uint32_t x=0,y=0,z=0;
    switch(type){
    case 1:case 2:case 5:case 6:{
        uint32_t amount=type<5?0x40f00000u:0x40700000u;
        int reverse=type==2||type==6;
        if(direction==0)x=reverse?amount:neg(amount);
        else if(direction==1)z=reverse?neg(amount):amount;
        else if(direction==2)x=reverse?neg(amount):amount;
        else z=reverse?amount:neg(amount);
        break;}
    case 3:y=0xc0f00000u;break;
    case 4:y=0x40f00000u;break;
    case 7:y=0xc0700000u;break;
    case 8:y=0x40700000u;break;
    default:break;
    }
    w32(p,x);w32(p+4,y);w32(p+8,z);
}
static void find_geometry(uint32_t definition,uint32_t work,uint32_t divisor,unsigned *direction,int record_angle)
{
    for(uint32_t k=0;si(k)<si(r32(0x54edb8u));k++){
        uint32_t object=r32(0x2fcda0u+k*4u),name=r32(object+8);
        if(name){
            /* The actual canonical strcmp includes byte-sign/order details;
             * use it instead of a result supplied by this owner. */
            if(ps2Strcmp((const char *)at(name),(const char *)at(definition+6u))==0){
                uint32_t pose=r32(object+16);w32(work+4,r32(object));loadvu(10,pose+16);
                uint32_t angle=degrees(divisor);
                if(record_angle)w32(work+0x24u,angle);else *direction=quadrant(angle,divisor+4u);
            }
        }
    }
}
void ps2FieldDoorAllSet_00143188(void)
{
    uint64_t scene=dds3GetControlScene();unsigned direction[2]={0,0};
    for(uint32_t i=0;i<256;i++){
        uint32_t d=0x3030f0u+i*100u,p=0x562830u+i*84u;
        if(sx((uint32_t)(int32_t)(int16_t)r16(d+4))!=sx(r32(0x2fbf88u)+1u))continue;
        if(*at(d)==2){
            find_geometry(d,p,0x54c484u,&direction[0],1);
            const unsigned offsets[]={0x44,0,0x18,0x1c,0x28,0x2c,0x3c,0x40};
            for(unsigned j=0;j<sizeof(offsets)/sizeof(offsets[0]);j++)w32(p+offsets[j],0);
            continue;
        }
        if(*at(d)!=1)continue;
        int types[2]={(int16_t)r16(d+0x12),(int16_t)r16(d+0x14)};
        w32(p+0xc,UINT32_MAX);
        if(types[0]){
            uint64_t obj=dds3SceneBasicSearchNameAndTypeExact(scene,6,d+0x18u);
            if(obj){w32(p+0xc,r32((uint32_t)obj+4));find_geometry(d,p,0x54c488u,&direction[0],0);}
        }
        w32(p+0x14,UINT32_MAX);
        if(types[1]){
            uint64_t obj=dds3SceneBasicSearchNameAndTypeExact(scene,6,d+0x24u);
            if(obj){w32(p+0x14,r32((uint32_t)obj+4));find_geometry(d,p,0x54c490u,&direction[1],0);}
        }
        w32(p,1);w32(p+0x10,(uint32_t)types[1]);w32(p+8,(uint32_t)types[0]);
        const unsigned offsets[]={0x18,0x1c,0x24,0x28,0x2c,0x3c,0x40,0x44};
        for(unsigned j=0;j<sizeof(offsets)/sizeof(offsets[0]);j++)w32(p+offsets[j],0);
        velocity(p+0x30,r32(p+0xc)==UINT32_MAX?0:types[0],direction[0]);
        velocity(p+0x48,r32(p+0x14)==UINT32_MAX?0:types[1],direction[1]);
    }
}
void ps2FieldDoorStart_00143D50(uint64_t id)
{
    if(!id||id==UINT64_MAX)return;
    for(uint32_t i=0;i<256;i++){
        uint32_t p=0x562830u+i*84u,d=0x3030f0u+i*100u;
        if(r32(p)==1&&sx(r32(p+4))==id){
            int a=(int16_t)r16(d+0x12),b=(int16_t)r16(d+0x14);
            w32(p,2);w32(p+0x18,0);w32(p+0x1c,0);
            w32(p+0x20,(a>=5&&a<=8)||(b>=5&&b<=8)?40:20);
            const unsigned offsets[]={0x24,0x28,0x2c,0x3c,0x40,0x44};
            for(unsigned j=0;j<sizeof(offsets)/sizeof(offsets[0]);j++)w32(p+offsets[j],0);
        }
    }
}
static void add3(uint32_t p,uint32_t velocity_address,uint32_t scale,int scaled,int subtract)
{
    /* Weighted opening stores X,Z,Y. Other native arms store X,Y,Z. */
    const unsigned opening_order[]={0,8,4};
    for(unsigned k=0;k<3;k++){
        unsigned o=scaled?opening_order[k]:k*4;
        uint32_t delta=r32(velocity_address+o);if(scaled)delta=EE_FPU_MUL_S(delta,scale);
        w32(p+o,subtract?EE_FPU_SUB_S(r32(p+o),delta):EE_FPU_ADD_S(r32(p+o),delta));
    }
}
uint64_t ps2FieldDoorStep_00143E20(uint64_t id,uint64_t x,uint64_t y,uint64_t z)
{
    if(si(r32(0x2fbf84u))>=200)return 0;
    for(uint32_t i=0;i<256;i++){
        uint32_t p=0x562830u+i*84u;
        for(unsigned leaf=0;leaf<2;leaf++){
            if(sx(r32(p+(leaf?0x14u:0xcu)))!=id)continue;
            uint32_t state=r32(p),count=p+0x18u+leaf*4u,pos=p+0x24u+leaf*24u,vel=pos+12u;
            if(state==2){
                if(si(r32(count))<si(r32(p+0x20))){
                    if(r32(p+0x20)==40)add3(pos,vel,r32(0x532030u+r32(count)*4u),1,0);
                    else{
                        add3(pos,vel,0,0,0);
                        if(!leaf&&evtBitCheck(0xaf3))add3(pos,vel,0,0,0);
                    }
                    w32(count,r32(count)+1u);
                }else if(evtBitCheck(0xaf3)){
                    if(!leaf)w32(p,3);
                    w32(count,0);
                }
            }else if(state==3){
                if(si(r32(count))<20){
                    if(leaf)w32(count,r32(count)+1u);
                    add3(pos,vel,0,0,1);
                    if(!leaf){if(evtBitCheck(0xaf3))add3(pos,vel,0,0,1);w32(count,r32(count)+1u);}
                }else{w32(count,0);if(!leaf)w32(p,1);}
            }else continue;
            w32((uint32_t)x,r32(pos));w32((uint32_t)y,r32(pos+4));w32((uint32_t)z,r32(pos+8));return 1;
        }
    }
    return 0;
}
