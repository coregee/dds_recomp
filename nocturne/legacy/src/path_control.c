/* Native object controls, path lifetime and spline coefficients. */
#include "path_control.h"
#include "event_camera.h"
#include "event_kuti.h"
#include "script_movie.h"
#include "script_construction.h"
#include "libc_printf.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "ps2_memory.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static void half(uint32_t p,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(p),&h,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000u)?INT64_C(4294967296):0));}
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t sub(uint32_t a,uint32_t b){return EE_FPU_SUB_S(a,b);}
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
static uint32_t divide(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static int equal(uint32_t a,uint32_t b){uint32_t am=(a&0x7f800000u)?a&0x7fffffffu:0,bm=(b&0x7f800000u)?b&0x7fffffffu:0;return am==bm&&((a>>31)==(b>>31)||am==0);}
static int less(uint32_t a,uint32_t b){uint32_t am=(a&0x7f800000u)?a&0x7fffffffu:0,bm=(b&0x7f800000u)?b&0x7fffffffu:0;int64_t av=a>>31?-(int64_t)am:am,bv=b>>31?-(int64_t)bm:bm;return av<bv;}
static uint32_t uintFloat(uint32_t v){if(!(v&0x80000000u))return EE_FPU_CVT_S_W(v);uint32_t f=EE_FPU_CVT_S_W((v>>1)|(v&1));return add(f,f);}
/* Six original leaf bodies selected by LBU basic+0F in 001122A0. */
uint64_t dds3CameraObjectBasicGetControlWorkData(uint64_t p){return sx(word(word((uint32_t)p+24)+128));}
uint64_t dds3UnitObjectBasicGetControlWorkData(uint64_t p){return sx(word(word((uint32_t)p+24)+12));}
uint64_t dds3MatterObjectBasicGetControlWorkData(uint64_t p){return sx(word(word((uint32_t)p+24)));}
uint64_t dds3LightObjectBasicGetControlWorkData(uint64_t p){return sx(word(word((uint32_t)p+24)));}
uint64_t dds3EventObjectBasicGetControlWorkData(uint64_t p){return sx(word(word((uint32_t)p+24)));}
uint64_t dds3EffectObjectBasicGetControlWorkData(uint64_t p){return sx(word(word((uint32_t)p+24)+116));}
uint64_t dds3GetBaseControlWorkData(uint64_t p)
{
 switch(*at((uint32_t)p+15)){
 case 4:return dds3CameraObjectBasicGetControlWorkData(p);case 5:return dds3UnitObjectBasicGetControlWorkData(p);
 case 6:return dds3MatterObjectBasicGetControlWorkData(p);case 7:return dds3LightObjectBasicGetControlWorkData(p);
 case 8:return dds3EventObjectBasicGetControlWorkData(p);case 9:return dds3EffectObjectBasicGetControlWorkData(p);default:return 0;
 }
}
uint64_t dds3ObjectBaseGetControlBasic(uint64_t p,uint64_t type){uint64_t c=dds3GetBaseControlWorkData(p);return sx(word((uint32_t)c+16+(uint32_t)type*4));}
void dds3MoverBasicSetPath(uint64_t p,uint64_t path){put(word((uint32_t)p+24)+12,(uint32_t)path);}
uint64_t dds3MoverBasicGetPathControl(uint64_t p){return sx(word(word((uint32_t)p+24)+4));}
uint64_t dds3PathBasicPathControlGetMode(uint64_t p){return sx(word((uint32_t)p));}
float dds3PathBasicControlGetRatio(uint64_t p){uint32_t b=divide(word((uint32_t)p+12),word((uint32_t)p+8));float f;memcpy(&f,&b,4);return f;}
/* 001B0EF8: exact forward elimination and backward substitution order. */
void effSplineSolveTridiagonal(uint64_t out,uint64_t dd,uint64_t count)
{
 uint32_t o=(uint32_t)out,d=(uint32_t)dd,n=(uint32_t)count;
 uint32_t h=ps2MemoryHandleAllocate(si(n*4)),t=ps2MemoryHandleAcquirePointer(h),den=0x40000000u;
 put(o,divide(word(d),den));
 for(uint32_t i=1;si(i)<=si(n-2);i++){
  uint32_t inv=divide(0x3f800000u,den);put(t+i*4,inv);den=sub(0x40800000u,inv);
  put(o+i*4,divide(sub(word(d+i*4),word(o+i*4-4)),den));
 }
 uint32_t inv=divide(0x3f800000u,den);put(t+n*4-4,inv);
 put(o+n*4-4,divide(sub(word(d+n*4-4),word(o+n*4-8)),sub(0x40000000u,inv)));
 for(uint32_t i=n-2;si(i)>=0;i--)put(o+i*4,sub(word(o+i*4),mul(word(t+i*4+4),word(o+i*4+4))));
 ps2MemoryHandleFree(h);
}
/* 001B0D70: three axis arrays; all COP1 parentheses follow original instructions. */
void effSplineMakeDifferential(uint64_t out,uint64_t points,uint64_t count)
{
 uint32_t n=(uint32_t)count,h=ps2MemoryHandleAllocate(si(n*4)),t=ps2MemoryHandleAcquirePointer(h),o=(uint32_t)out,p=(uint32_t)points;
 for(uint32_t axis=0;axis<3;axis++){
  uint32_t a=p+axis*4;put(t,mul(sub(word(a+12),word(a)),0x40400000u));
  put(t+n*4-4,mul(sub(word(a+n*12-12),word(a+n*12-24)),0x40400000u));
  for(uint32_t i=1;si(i)<=si(n-2);i++){
   uint32_t middle=word(a+i*12);
   put(t+i*4,mul(add(sub(middle,word(a+i*12-12)),sub(word(a+i*12+12),middle)),0x40400000u));
  }
  effSplineSolveTridiagonal(o+axis*n*4,t,count);
 }
 ps2MemoryHandleFree(h);
}
static void coefficient(uint64_t spline,uint64_t dd,int flat)
{
 uint32_t s=(uint32_t)spline,n=word(s+8),a=word(s+20),b=word(s+24),c=word(s+28),p=word(s+16),d=(uint32_t)dd;
 for(uint32_t i=0;si(i)<si(n-1);i++)for(uint32_t axis=0;axis<3;axis++){
  uint32_t offset=(i*3+axis)*4,x=word(p+offset),y=word(p+offset+12);
  if(flat&&equal(x,y)){put(a+offset,0);put(b+offset,0);put(c+offset,0);}
  else{
   uint32_t left=word(d+i*4+axis*n*4),right=word(d+i*4+axis*n*4+4);
   uint32_t negative=sub(x,y),positive=sub(y,x),twice=add(left,left),sum=add(left,right);
   uint32_t cub=add(add(negative,negative),sum),quad=sub(mul(positive,0x40400000u),add(twice,right));
   put(a+offset,cub);put(b+offset,quad);put(c+offset,left);
  }
 }
}
void effSplineMakeCoefficient(uint64_t spline,uint64_t dd){coefficient(spline,dd,0);}
void effSplineMakeCoefficient2(uint64_t spline,uint64_t dd){coefficient(spline,dd,1);}
void effSplineMakeCoefficientTable(uint64_t spline,uint64_t bogus)
{
 uint32_t s=(uint32_t)spline,h=ps2MemoryHandleAllocate(si(word(s+8)*12)),d=ps2MemoryHandleAcquirePointer(h);
 effSplineMakeDifferential(d,sx(word(s+16)),sx(word(s+8)));
 if(!bogus)effSplineMakeCoefficient(spline,d);else effSplineMakeCoefficient2(spline,d);
 ps2MemoryHandleFree(h);
}
uint64_t effSplInitialize2(uint64_t points,uint64_t count,uint64_t bogus)
{
 uint32_t h=ps2MemoryHandleAllocate(44),s=ps2MemoryHandleAcquirePointer(h),n=(uint32_t)count,f=word(0x54ca78);
 put(s,h);put(s+8,n);put(s+16,(uint32_t)points);put(s+32,0);put(s+36,0);put(s+40,f);
 if(count<3){put(s+20,0);half(s+12,1);}
 else{
  uint32_t h2=ps2MemoryHandleAllocate(si(n*36)),data=ps2MemoryHandleAcquirePointer(h2);
  put(s,h);put(s+4,h2);put(s+16,(uint32_t)points);put(s+24,data+n*12);put(s+28,data+n*24);put(s+40,f);half(s+12,0);put(s+8,n);put(s+20,data);put(s+32,0);put(s+36,0);
  effSplineMakeCoefficientTable(s,bogus);
 }
 return sx(s);
}
void ps2SplineRelease(uint64_t spline)
{
 if(!spline)return;uint32_t s=(uint32_t)spline;
 if(word(s+20))ps2MemoryHandleFree(word(s+4));ps2MemoryHandleFree(word(s));
}
/* 00116210: mutable channel count and unsigned-last-key maximum remain native. */
uint64_t dds3PathBasicMakeControl(uint64_t path)
{
 uint32_t data=word((uint32_t)path+24);if(!word(data))return 0;
 uint32_t c=ps2PoolAllocate(36);ps2Memset(at(c),0,36);put(c,0);put(c+12,0);put(c+8,0);
 uint32_t count=word(data),record=data+4;
 for(uint32_t i=0;i<count;i++,record+=8){
  uint32_t kind=word(record),channel=word(record+4);
  if(kind==0){put(c+20,channel);put(c+4,word(c+4)|1);put(c+16,(uint32_t)effSplInitialize2(sx(word(channel+4)),sx(word(channel)),1));count=word(data);}
  else if(kind==2||kind==4||kind==5){put(c+(kind==2?24:kind==4?28:32),channel);put(c+4,word(c+4)|(kind==2?2:kind==4?4:16));count=word(data);}
  uint32_t frames=word(word(channel+8)+word(channel)*4-4),f=uintFloat(frames);
  if(less(word(c+8),f))put(c+8,uintFloat(frames));
 }
 return sx(c);
}
void dds3PathBasicFreeControl(uint64_t c){ps2SplineRelease(sx(word((uint32_t)c+16)));ps2PoolRelease((uint32_t)c);}
void dds3MoverBasicMakePath(uint64_t mover)
{
 uint32_t data=word((uint32_t)mover+24),old=word(data+4);if(old)dds3PathBasicFreeControl(sx(old));
 uint64_t c=dds3PathBasicMakeControl(sx(word(data+12)));put(data+4,(uint32_t)c);
}
uint64_t evtPathLinkAndMake(uint64_t path,uint64_t object)
{
 if(!path)return 0;uint64_t control=dds3GetBaseControlWorkData(object);if(!control)return 0;
 uint64_t mover=sx(word((uint32_t)control+20));if(!mover)return 0;
 dds3MoverBasicSetPath(mover,path);dds3MoverBasicMakePath(mover);return 1;
}
uint64_t evtCheckPathStat(uint64_t object)
{
 if(!object)return UINT64_MAX;uint64_t mover=dds3ObjectBaseGetControlBasic(object,1);if(!mover)return UINT64_MAX;
 uint64_t control=dds3MoverBasicGetPathControl(mover);if(!control)return UINT64_MAX;
 uint64_t mode=dds3PathBasicPathControlGetMode(control);uint32_t target=0x3f800000u;
 if(mode){if(mode!=1)return UINT64_MAX;target=0;}
 float f=dds3PathBasicControlGetRatio(control);uint32_t bits;memcpy(&bits,&f,4);return equal(bits,target)?0:1;
}
uint64_t evtCommand_CAM_SEL_FOVY(void)
{
 uint64_t id=scrGetIntPara(0),camera;
 if((int64_t)id<0)camera=fldGetUnitFollowCamera();
 else{camera=evtSearchBasic(4,scrGetIntPara(0));uint32_t data=word((uint32_t)camera+24);put(data+136,word(data+136)|1);}
 if(camera)dds3SetActiveCameraSceneBasic(dds3GetActiveScene(),camera);return 1;
}
uint64_t evtCommand_CAM_PATH_MOVE(void)
{
 uint64_t id=scrGetIntPara(0),camera=(int64_t)id<0?fldGetUnitFollowCamera():evtSearchBasic(4,scrGetIntPara(0));
 if(camera){uint64_t path=evtSearchBasic(16,scrGetIntPara(1));if(path&&evtPathLinkAndMake(path,camera))return 1;}
 ps2LibcPrintf(0x53ad58);return 1;
}
uint64_t evtCommand_CAM_PATH_WAIT(void)
{
 uint64_t id=scrGetIntPara(0),camera=(int64_t)id<0?fldGetUnitFollowCamera():evtSearchBasic(4,scrGetIntPara(0));
 if(!camera)return 1;int64_t stat=(int64_t)evtCheckPathStat(camera);return stat==0||stat==-1?1:0;
}
