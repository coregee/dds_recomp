/* Complete original Magatama menu selection/equip/icon-state bodies.
 * SLUS_209.11 owns raw widths, inline records, RNG and read/write order.
 * Existing inventory/equip/initializer callees remain genuine dependencies. */
#include "magatama_menu_runtime.h"
#include "nocturne.h"
#include "unit_progression.h"
#include "compiler_numeric.h"
#include "ee_fpu.h"
#include <string.h>

static uint8_t *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMagatamaMenuRuntimeAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r8(uint32_t a){return *at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*at(a)=(uint8_t)v;}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static int32_t sb(uint32_t v){return(v&255u)<128u?(int32_t)(v&255u):(int32_t)(v&255u)-256;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t menu(void){return r32(0x551fb0);}
static uint32_t game(void){return r32(0x54ea20);}
/* These are original COP1 instruction boundaries, not host IEEE operations.
 * Host tests use the existing separately reviewed EE value primitives. */
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t sub(uint32_t a,uint32_t b){return EE_FPU_SUB_S(a,b);}
static uint32_t divide(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static uint32_t remainder(uint32_t v,uint32_t d){if(!d)nocturneCompilerArithmeticTrap(7u);return v%d;}

/* Native hook is an actual empty body. HD merges its metadata address with
 * unrelated empty methods; that shared body authenticates no further role. */
void ps2MagatamaPadActionHook_00232878(uint64_t type){(void)type;}

uint64_t ps2MagatamaTextureLoading_002329F8(void)
{
    uint32_t common=r32(0x54fe78);
    if(!r32(common+0x116c))return 1;
    if(!r32(common+0x1170))return 1;
    return r32(common+0x1174)==0;
}
uint64_t ps2MagatamaTextureReady_00232A28(void)
{
    uint32_t common=r32(0x54fe78);
    if(!r32(common+0x1160))return 0;
    if(!r32(common+0x1164))return 0;
    return r32(common+0x1168)!=0;
}
void ps2MagatamaInfoInitialize_00232E90(uint64_t data)
{
    uint32_t p=(uint32_t)data+0x1f78;
    w8(p+8,32);w32(p+0x10,16);w32(p,0);w32(p+4,0);w8(p+9,0);w8(p+0xa,0);w32(p+0xc,0);
}

void ps2MagatamaCursorMove_00234BF0(uint64_t mode)
{
    uint32_t m=menu();int32_t pos=sb(r8(m+0x31));
    w32(m+0x1178u+(uint32_t)pos*4u,0x80);
    int owned=cmpChkHaveHearts(cmpGetHeartsFromPos(24))!=0;
    if(pos==24){
        if(mode&0x10u)pos=19;
        if(mode&0x20u)pos=3;
        if(mode&0x40u)pos=19;
        if(mode&0x80u)pos=20;
    }else{
        if(mode&0x10u){
            if(pos/8==0&&owned&&(uint32_t)(pos-3)<2u)pos=24;
            else pos=sb((uint32_t)pos+(pos/8==0?16u:UINT32_C(0xfffffff8)));
        }
        if(mode&0x20u){
            /* Native adds7 for a negative signed-byte position before its
             * arithmetic shift, giving the same truncate-to-zero /8. */
            int32_t quotient=pos/8;
            if(quotient==2&&owned&&(((uint32_t)pos-19u)&255u)<2u)pos=24;
            else pos=sb((uint32_t)pos+(quotient==2?UINT32_C(0xfffffff0):8u));
        }
        if(mode&0x40u)pos=sb((uint32_t)pos+(((uint32_t)pos&7u)?UINT32_MAX:7u));
        if(mode&0x80u){int32_t mod=pos-(pos/8)*8;pos=sb((uint32_t)pos+(mod==7?UINT32_C(0xfffffff9):1u));}
    }
    m=menu();w32(m+0x1178u+(uint32_t)pos*4u,0);w8(m+0x31,(uint32_t)pos);w32(m+0x20,0);
    ps2MagatamaPadActionHook_00232878((uint64_t)(int64_t)sb(r8(menu()+0x1280u+(uint32_t)sb(r8(menu()+0x31))*52u)));
}

uint64_t ps2MagatamaAttachStatus_00234DC8(void)
{
    int32_t id=cmpGetHeartsFromPos((int8_t)sb(r8(menu()+0x31)));
    if(!cmpChkHaveHearts((int8_t)id))return 1;
    uint32_t g=game(),equipped=r8(g+0x1cfa);
    if(equipped){
        if(id==(int32_t)equipped)return 2;
        uint32_t count=r8(g+0x1d7b);
        for(int32_t i=0;i<(int32_t)count;i=sb((uint32_t)i+1u))
            if(id==(int32_t)r8(g+0x1cfbu+(uint32_t)i)&&(r16(g+0xa62)&0x8000u))return 4;
        return 0;
    }
    return(r16(g+0xa62)&0x8000u)?0:3;
}

void ps2MagatamaRestoreParameters_00234E98(void)
{
    ps2UnitEquipMagatama_002453E8((uint64_t)(int64_t)sb(r8(menu()+0x32)));
    uint32_t src=menu()+0x34,dst=game()+0xa54,end=menu()+0x114;
    /* Both aligned and LDL/LDR paths load four complete64-bit chunks before
     * writing each32-byte block. Preserve that grouping for any alias. */
    do{uint8_t block[32];memcpy(block,at(src),32);memcpy(at(dst),block,32);src+=32;dst+=32;}while(src!=end);
    uint8_t tail[12];memcpy(tail,at(src),8);memcpy(tail+8,at(src+8),4);
    memcpy(at(dst),tail,8);memcpy(at(dst+8),tail+8,4);
}
void ps2MagatamaEquipSelection_00234F80(void)
{
    ps2UnitEquipMagatama_002453E8((uint64_t)(int64_t)cmpGetHeartsFromPos((int8_t)sb(r8(menu()+0x31))));
    uint32_t g=game();if(!r16(g+0xa5a))w16(g+0xa5a,1);
    if(!r16(g+0xa5e))w16(g+0xa5e,1);
}

void ps2MagatamaTimersUpdate_002356F8(void)
{
    uint32_t m=menu(),v=r32(m+0x1c)+1u;w32(m+0x1c,v);if(si(v)>1023)w32(m+0x1c,0);
    v=r32(m+0x20)+8u;w32(m+0x20,v);if(si(v)>511)w32(m+0x20,0);
    v=r32(m+0x24);w32(m+0x24,v+(si(v)<512?32u:16u));
    if(si(r32(m+0x24))>1023)w32(m+0x24,0);
}
void ps2MagatamaCommandFadeUpdate_00235770(void)
{
    uint32_t m=menu(),v;
    if(!(r8(m)&1u)){v=r32(m+0x2c)+32u;w32(m+0x2c,v);if(si(v)>256)w32(m+0x2c,256);}
    else{v=r32(m+0x2c)-32u;if(si(v)<0)v=0;w32(m+0x2c,v);}
}
void ps2MagatamaBlurTimersUpdate_002357C0(void)
{
    uint32_t m=menu();
    for(unsigned i=0;i<64;++i){uint32_t p=m+0x1178+i*4,v=r32(p);if(si(v)>0)w32(p,v-16u);if(si(r32(p))<0)w32(p,0);}
}

void ps2MagatamaIconSetup_00235820(uint64_t icon)
{
    uint32_t p=(uint32_t)icon;
    if(sb(r8(p))==1){
        uint32_t axis=r32(p+0xc);if(si(axis)>0){--axis;w32(p+0xc,axis);}
        if(!axis){int32_t a=sb(r8(p+9));w32(p+0x1c,a==1?UINT32_C(0xc1200000):a==2?UINT32_C(0x41200000):0);}
        uint32_t delta=sub(r32(p+0x1c),r32(p+0x18));w8(p,0);w32(p+0x20,delta);
        uint32_t n=remainder(sdfGetRand(NULL),5)+1u;w32(p+0x24,n);w32(p+0x28,n);w32(p+0x20,divide(r32(p+0x20),EE_FPU_CVT_S_W(n)));
        return;
    }
    int32_t move=sb(r8(p+8));uint32_t wait;
    if(move==1)wait=(sdfGetRand(NULL)&31u)+20u;
    else if(move==2)wait=sdfGetRand(NULL)&7u;
    else return;
    w32(p+0x14,wait);w8(p,1);w32(p+0x1c,r32(p+0x18));
    w32(p+0x20,sub(EE_FPU_CVT_S_W(remainder(sdfGetRand(NULL),40)),UINT32_C(0x41a00000)));
    uint32_t n=remainder(sdfGetRand(NULL),5)+1u;w32(p+0x24,n);w32(p+0x28,n);w32(p+0x20,divide(r32(p+0x20),EE_FPU_CVT_S_W(n)));
    if(sb(r8(p+8))==2){
        if(si(r32(p+0xc))<=0){w8(p+9,remainder(sdfGetRand(NULL),3));w32(p+0xc,remainder(sdfGetRand(NULL),10));}
    }else w32(p+0xc,UINT32_MAX);
}
void ps2MagatamaIconMove_00235A58(uint64_t icon)
{
    uint32_t p=(uint32_t)icon,v=r32(p+0x14);
    if(si(v)>0){w32(p+0x14,v-1u);return;}
    v=r32(p+0x28);if(!v)ps2MagatamaIconSetup_00235820(icon);
    else{w32(p+0x28,v-1u);w32(p+0x18,add(r32(p+0x18),r32(p+0x20)));}
}
void ps2MagatamaIconsUpdate_00235AB8(void)
{
    for(unsigned i=0;i<25;++i){
        uint32_t p=menu()+0x1278+i*52;
        if(sb(r8(p+1))<0)continue;
        ps2MagatamaIconMove_00235A58(p);
        uint32_t v=r32(p+0x10);
        if(si(v)>0)w32(p+0x10,v-1u);
        else{v=r32(p+0x2c)+r32(p+0x30);w32(p+0x2c,v);if(si(v)>512)w32(p+0x2c,0);}
    }
}
void ps2MagatamaInfoUpdate_00235B50(void)
{
    uint32_t p=menu()+0x1f78;
    if(!ps2MagatamaTextureReady_00232A28())return;
    int32_t id=cmpGetHeartsFromPos((int8_t)sb(r8(menu()+0x31)));
    if(cmpChkHaveHearts((int8_t)id)){w8(p+9,(uint32_t)id);w32(p,1);}else w32(p,0);
    uint32_t v=r32(p+4);
    if(r32(p)){
        if(si(v)<256){v+= (uint32_t)sb(r8(p+8));w32(p+4,v);}
        if(si(v)>256)w32(p+4,256);
    }else{
        if(si(v)>0){v-=(uint32_t)sb(r8(p+8));w32(p+4,v);}
        if(si(v)<0)w32(p+4,0);
    }
    v=r32(p+0xc);if(si(v)<256){v+=r32(p+0x10);w32(p+0xc,v);}
    if(si(v)>256)w32(p+0xc,256);
}
