#include <stdint.h>
#include <string.h>
#include "material_fiveword_pool.h"
#include "motion_callback_leaves.h"
#include "material_construction_release.h"
static uint32_t r32(const void *p){uint32_t value;memcpy(&value,p,4);return value;}
static uint32_t r16(const void *p){uint16_t value;memcpy(&value,p,2);return value;}
static void w32(void *p,uint32_t value){memcpy(p,&value,4);}
static void w16(void *p,uint32_t value){uint16_t word=(uint16_t)value;memcpy(p,&word,2);}
static int32_t s16(uint32_t x){return (int32_t)(x&32767)-(int32_t)(x&32768);}
static int32_t s32(uint32_t x){return (int32_t)((int64_t)x-((x&0x80000000)?INT64_C(4294967296):0));}
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
return (uint8_t *)nocturneResolveMotionAddress(address);
#else
return (uint8_t *)(uintptr_t)address;
#endif
}
#define FIVE_SCALARS(role,mask) \
void ps2MatSetFiveScalars##role(void *material,uint32_t a,uint32_t b,uint32_t c,uint32_t d,uint32_t e) \
{uint8_t *m=material,*p=at(ps2MatGetFiveWords##role(m));w32(p+16,e);w32(p,a);w32(p+4,b);w32(p+8,c);w32(p+12,d);m[6]=(uint8_t)(m[6]|mask);}
FIVE_SCALARS(38,0x0c)
FIVE_SCALARS(3C,0x30)
#undef FIVE_SCALARS
void ps2MatSetScalars40And44(void *material,uint32_t a,uint32_t b)
{uint8_t *m=material;uint8_t flag=m[6];w32(m+0x40,a);w32(m+0x44,b);m[6]=(uint8_t)(flag|0xc0);}
void ps2MotionBindMaterialNode(void *node,uint32_t source,uint32_t table,uint32_t index)
{
    uint8_t *n=node;sdfMotionNodeBaseInit(n,source,table);
    uint32_t controller=r32(at(source)+4),owner=r32(at(controller)+12),array=r32(at(owner)+12);
    uint32_t material=r32(at(array+(index<<2)));w32(n+12,material);
}
static uint32_t create_node(uint32_t source,uint32_t index,int32_t size,uint32_t table)
{uint32_t node=ps2PoolAllocate(size);ps2MotionBindMaterialNode(at(node),source,table,index);return node;}
uint32_t ps2MotionCreateMaterialFiveWords38Node(uint32_t source,uint32_t index){return create_node(source,index,36,0x529588);}
uint32_t ps2MotionCreateMaterialFiveWords3CNode(uint32_t source,uint32_t index){return create_node(source,index,36,0x5295a0);}
uint32_t ps2MotionCreateMaterialWord18Node(uint32_t source,uint32_t index){return create_node(source,index,20,0x5295b8);}
/* SQ zero writes four quadwords per loop; the one-to-three remainder runs backwards. */
uint32_t ps2ZeroQuadwords(uint32_t address,int32_t count)
{
    uint32_t next=address;
    while(count>=4){count-=4;memset(at(next),0,16);memset(at(next+16),0,16);memset(at(next+32),0,16);memset(at(next+48),0,16);next+=64;}
    if(count==3)memset(at(next+32),0,16);
    if(count==2||count==3)memset(at(next+16),0,16);
    if(count>=1&&count<=3)memset(at(next),0,16);
    return address;
}
uint32_t ps2PoolAllocateZeroed(int32_t size)
{uint32_t pointer=ps2PoolAllocate(size);int32_t rounded=s32((uint32_t)size+15);int32_t count=rounded>=0?rounded/16:-1-(int32_t)((-(int64_t)rounded-1)/16);return ps2ZeroQuadwords(pointer,count);}
void ps2PoolRelease(uint32_t slot)
{
    if(!slot)return;
    uint32_t arena=r32(at(0x552060)),headers=r32(at(0x552058));
    int32_t difference=s32(slot-arena),page_index=difference/4096;
    uint32_t page=headers+(uint32_t)page_index*24;
    uint8_t *p=at(page);uint32_t owner=r32(p+12),enabled=ps2KernelDisableInterrupts();
    uint8_t *c=at(owner);int32_t used=s16(r16(p+20));uint32_t next_used=(uint32_t)(used-1);w16(p+20,next_used);
    if((next_used&65535)==0){
        if(r32(c)==page)ps2PoolAdvancePageList(c);
        else{
            uint8_t *link=c+4;uint32_t current=r32(link);
            while(current!=page){link=at(current);current=r32(link);}
            w32(link,r32(p));
        }
        uint32_t free_head=r32(at(0x55205c));w32(p+12,0);w32(p,free_head);w32(at(0x55205c),page);
    }else{
        if(used==s16(r16(c+10))){uint32_t available=r32(c+4);w32(p,available);w32(c+4,page);}
        uint32_t freed=r32(p+16);w32(at(slot)+8,freed);w32(p+16,slot);
    }
    if(enabled)ps2KernelEnableInterrupts();
}
/* Strong HD sdfMatNew counterpart lead; name remains descriptive until promotion. */
uint32_t ps2MatCreate(void)
{
    uint8_t *counter=at(0x5518a0);w32(counter,r32(counter)+1);
    uint32_t address=ps2PoolAllocateZeroed(72);uint8_t *m=at(address);m[6]=255;
    for(unsigned i=0;i<2;i++){
        uint32_t packet=ps2PoolAllocate(160);w32(m+8+i*4,packet);uint8_t *p=at(packet);
        w32(p+0x9c,0x14000000);w32(p,0x6e05c000);w32(p+0x18,0x6005c005);w32(p+0x30,0);w32(p+0x34,0x640cc00a);w32(p+0x98,0x0400000c);
    }
    w32(m+0x40,0);w32(m+0x44,0);w32(m+0x18,0x80808080);w32(m+0x10,0x80808080);w32(m+0x14,0x80808080);return address;
}
