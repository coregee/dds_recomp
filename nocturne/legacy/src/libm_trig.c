/* Float libm lineage: Ian Lance Taylor / Cygnus conversion of Sun fdlibm.
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 * ====================================================
 * Reconstructed from original SLUS_209.11 instructions. Upstream Newlib is
 * structural context; native constant encodings, EE operations, no-denormal
 * scaling and exponent-255 handling decide this implementation.
 */
#include "libm_trig.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include "ps2_sdk_neighbors.h"
#include <string.h>

static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint32_t rd(const float *p){uint32_t v;memcpy(&v,p,4);return v;}
static void wr(float *p,uint32_t v){memcpy(p,&v,4);}
static uint32_t original(uint32_t a){uint32_t v;
#if UINTPTR_MAX > UINT32_MAX
 memcpy(&v,nocturneResolveLibmTrigAddress(a),4);
#else
 memcpy(&v,(void *)(uintptr_t)a,4);
#endif
 return v;}
#define A(a,b) EE_FPU_ADD_S((a),(b))
#define S(a,b) EE_FPU_SUB_S((a),(b))
#define M(a,b) EE_FPU_MUL_S((a),(b))
#define I(a) EE_FPU_CVT_W_S(a)
#define F(a) EE_FPU_CVT_S_W((uint32_t)(a))
#define EQ(a,b) EE_FPU_COMPARE_S((a),(b),0)
#define LE(a,b) EE_FPU_COMPARE_S((a),(b),2)
#define NEG(a) ((a)^UINT32_C(0x80000000))

float ps2LibmFloorFloat(float input){
 uint32_t x=bits(input),m=x&0x7fffffff;int32_t exponent=(int32_t)(m>>23)-127;
 if(exponent<23){
  if(exponent<0){
   if(EE_FPU_COMPARE_S(0,A(x,0x7149f2c9),1)){
    if(!(x&0x80000000))x=0;
    else if(m>0x7fffff)x=0xbf800000;
   }
  }else{
   uint32_t mask=0x7fffffu>>exponent;
   if((x&mask)&&EE_FPU_COMPARE_S(0,A(x,0x7149f2c9),1)){
    if(x&0x80000000)x+=0x800000u>>exponent;
    x&=~mask;
   }
  }
 }
 return real(x);
}

float ps2LibmScalbnFloat(float input,uint64_t exponent){
 uint32_t x=bits(input),m=x&0x7fffffff;
 int32_t e=(int32_t)((m>>23)+(uint32_t)exponent);
 if(m<=0x7fffff)return input;
 if(e>0&&e<256)return real((x&0x807fffff)|((uint32_t)e<<23));
 uint32_t scale=e>=256||(int64_t)exponent>50000?0x7149f2c9:0x0da2425f;
 uint32_t signedScale=bits(ps2CopySignFloat(real(scale),input));
 return real(M(signedScale,scale));
}

float ps2LibmKernelCosFloat(float input,float tail){
 uint32_t x=bits(input),y=bits(tail),m=x&0x7fffffff,integer=I(x);
 if(m<0x32000000&&integer==0)return real(0x3f800000);
 uint32_t z=M(x,x),r=M(z,0xad47d74e);
 r=A(r,0x310f74f5);r=M(z,r);r=A(r,0xb493f27b);
 r=M(z,r);r=A(r,0x37d00d00);r=M(z,r);r=A(r,0xbab60b60);
 r=M(z,r);r=A(r,0x3d2aaaaa);r=M(z,r);
 uint32_t zr=M(z,r),xy=M(x,y),hz=M(z,0x3f000000);
 if(m<0x3e99999a)return real(S(0x3f800000,S(hz,S(zr,xy))));
 uint32_t qx=m>0x3f480000?0x3e900000:m-0x01000000;
 return real(S(S(0x3f800000,qx),S(S(hz,qx),S(zr,xy))));
}

float ps2LibmKernelSinFloat(float input,float tail,uint64_t withTail){
 uint32_t x=bits(input),y=bits(tail),m=x&0x7fffffff,integer=I(x);
 if(m<0x32000000&&integer==0)return input;
 uint32_t z=M(x,x),v=M(z,x),r=M(z,0x2f2ec9d2);
 r=A(r,0xb2d72f34);r=M(z,r);r=A(r,0x3638ef1a);
 r=M(z,r);r=A(r,0xb9500d01);r=M(z,r);r=A(r,0x3c088889);
 if(!withTail)return real(A(x,M(v,A(M(z,r),0xbe2aaaaa))));
 uint32_t vr=M(v,r),vs=M(v,0xbe2aaaaa),halfY=M(y,0x3f000000);
 return real(S(x,S(S(M(z,S(halfY,vr)),y),vs)));
}

int32_t ps2LibmKernelRemPio2Float(const float *x,float *y,int32_t e0,int32_t nx,int32_t precision,const int32_t *ipio2){
 int32_t iq[20],jx=nx-1,jv=(e0-3)/8,jk=(int32_t)original(0x54b348+(uint32_t)precision*4),jp=jk;
 uint32_t f[20],fq[20],q[20],z,fw;
 int32_t jz,j,q0,ih,n,carry,k;
 if(jv<0)jv=0;
 q0=e0-8*(jv+1);
 j=jv-jx;
 for(int32_t i=0;i<=jx+jk;i++,j++)f[i]=j<0?0:F(ipio2[j]);
 for(int32_t i=0;i<=jk;i++){
  fw=0;for(j=0;j<=jx;j++)fw=A(fw,M(rd(x+j),f[jx+i-j]));q[i]=fw;
 }
 jz=jk;
recompute:
 z=q[jz];
 for(int32_t i=0,jj=jz;jj>0;i++,jj--){
  fw=F(I(M(z,0x3b800000)));iq[i]=(int32_t)I(S(z,M(fw,0x43800000)));z=A(q[jj-1],fw);
 }
 z=bits(ps2LibmScalbnFloat(real(z),(uint64_t)(int64_t)q0));
 fw=bits(ps2LibmFloorFloat(real(M(z,0x3e000000))));z=S(z,M(fw,0x41000000));
 n=(int32_t)I(z);z=S(z,F(n));ih=0;
 if(q0>0){int32_t i=iq[jz-1]>>(8-q0);n+=i;iq[jz-1]-=i<<(8-q0);ih=iq[jz-1]>>(7-q0);}
 else if(!q0)ih=iq[jz-1]>>8; /* Native SRAV uses 8, unlike upstream 7. */
 else if(LE(0x3f000000,z))ih=2;
 if(ih>0){
  n++;carry=0;
  for(int32_t i=0;i<jz;i++){
   j=iq[i];if(!carry){if(j){carry=1;iq[i]=0x100-j;}}else iq[i]=0xff-j;
  }
  if(q0==1)iq[jz-1]&=0x7f;else if(q0==2)iq[jz-1]&=0x3f;
  if(ih==2){z=S(0x3f800000,z);if(carry)z=S(z,bits(ps2LibmScalbnFloat(real(0x3f800000),(uint64_t)(int64_t)q0)));}
 }
 if(EQ(z,0)){
  j=0;for(int32_t i=jz-1;i>=jk;i--)j|=iq[i];
  if(!j){
   for(k=1;iq[jk-k]==0;k++){}
   for(int32_t i=jz+1;i<=jz+k;i++){
    f[jx+i]=F(ipio2[jv+i]);fw=0;
    for(j=0;j<=jx;j++)fw=A(fw,M(rd(x+j),f[jx+i-j]));q[i]=fw;
   }
   jz+=k;goto recompute;
  }
 }
 if(EQ(z,0)){
  jz--;q0-=8;while(!iq[jz]){jz--;q0-=8;}
 }else{
  z=bits(ps2LibmScalbnFloat(real(z),(uint64_t)(int64_t)-q0));
  if(LE(0x43800000,z)){
   fw=F(I(M(z,0x3b800000)));iq[jz]=(int32_t)I(S(z,M(fw,0x43800000)));jz++;q0+=8;iq[jz]=(int32_t)I(fw);
  }else iq[jz]=(int32_t)I(z);
 }
 fw=bits(ps2LibmScalbnFloat(real(0x3f800000),(uint64_t)(int64_t)q0));
 for(int32_t i=jz;i>=0;i--){q[i]=M(fw,F(iq[i]));fw=M(fw,0x3b800000);}
 for(int32_t i=jz;i>=0;i--){
  fw=0;for(k=0;k<=jp&&k<=jz-i;k++)fw=A(fw,M(original(0x54b358+k*4),q[i+k]));fq[jz-i]=fw;
 }
 if(precision==0||precision==1||precision==2){
  fw=0;for(int32_t i=jz;i>=0;i--)fw=A(fw,fq[i]);wr(y,ih?NEG(fw):fw);
  if(precision){fw=S(fq[0],fw);for(int32_t i=1;i<=jz;i++)fw=A(fw,fq[i]);wr(y+1,ih?NEG(fw):fw);}
 }else if(precision==3){
  for(int32_t i=jz;i>0;i--){fw=A(fq[i-1],fq[i]);fq[i]=A(fq[i],S(fq[i-1],fw));fq[i-1]=fw;}
  for(int32_t i=jz;i>1;i--){fw=A(fq[i-1],fq[i]);fq[i]=A(fq[i],S(fq[i-1],fw));fq[i-1]=fw;}
  fw=0;for(int32_t i=jz;i>=2;i--)fw=A(fw,fq[i]);
  wr(y,ih?NEG(fq[0]):fq[0]);wr(y+1,ih?NEG(fq[1]):fq[1]);wr(y+2,ih?NEG(fw):fw);
 }
 return n&7;
}

int32_t ps2LibmRemPio2Float(float input,float *y){
 uint32_t x=bits(input),ix=x&0x7fffffff,z,w,r,fn,t;
 if(ix<=0x3f490fd8){wr(y,x);wr(y+1,0);return 0;}
 if(ix<0x4016cbe4){
  uint32_t correction=(ix&0xfffffff0)==0x3fc90fd0?0x2e85a308:0x37354442;
  if((int32_t)x>0){z=S(x,0x3fc90f80);if((ix&0xfffffff0)==0x3fc90fd0)z=S(z,0x373543ff);r=S(z,correction);wr(y,r);wr(y+1,S(S(z,r),correction));return 1;}
  z=A(x,0x3fc90f80);if((ix&0xfffffff0)==0x3fc90fd0)z=A(z,0x373543ff);r=A(z,correction);wr(y,r);wr(y+1,A(S(z,r),correction));return -1;
 }
 if(ix<=0x43490f80){
  t=bits(ps2AbsFloat(input));int32_t n=(int32_t)I(A(M(t,0x3f22f984),0x3f000000));fn=F(n);
  r=S(t,M(fn,0x3fc90f80));w=M(fn,0x37354442);z=S(r,w);wr(y,z);
  if(!(n<32&&(ix&0xffffff00)!=original(0x54b274+(uint32_t)n*4))){
   int32_t j=(int32_t)(ix>>23),difference=j-(int32_t)((z>>23)&255);
   if(difference>8){
    t=r;uint32_t part=M(fn,0x373543ff);r=S(t,part);w=S(M(fn,0x2e85a308),S(S(t,r),part));z=S(r,w);wr(y,z);
    if(j-(int32_t)((z>>23)&255)>25){t=r;part=M(fn,0x2e85a300);r=S(t,part);w=S(M(fn,0x248d3131),S(S(t,r),part));z=S(r,w);wr(y,z);}
   }
  }
  w=S(S(r,rd(y)),w);wr(y+1,w);
  if((int32_t)x<0){wr(y,NEG(rd(y)));wr(y+1,NEG(w));return -n;}return n;
 }
 int32_t e0=(int32_t)(ix>>23)-134;z=ix-(uint32_t)e0*0x800000u;float tx[3];
 for(int32_t i=0;i<2;i++){t=F(I(z));wr(tx+i,t);z=M(S(z,t),0x43800000);}wr(tx+2,z);
 int32_t count=3;while(EQ(rd(tx+count-1),0))count--;
 int32_t n;
#if UINTPTR_MAX > UINT32_MAX
 n=ps2LibmKernelRemPio2Float(tx,y,e0,count,2,nocturneResolveLibmTrigAddress(0x54af60));
#else
 n=ps2LibmKernelRemPio2Float(tx,y,e0,count,2,(const int32_t *)(uintptr_t)0x54af60);
#endif
 if((int32_t)x<0){wr(y,NEG(rd(y)));wr(y+1,NEG(rd(y+1)));return -n;}return n;
}

float ps2LibmCosFloat(float x){
 if((bits(x)&0x7fffffff)<=0x3f490fd8)return ps2LibmKernelCosFloat(x,real(0));
 float y[2];int32_t n=ps2LibmRemPio2Float(x,y);
 switch(n&3){case 0:return ps2LibmKernelCosFloat(y[0],y[1]);case 1:return real(NEG(bits(ps2LibmKernelSinFloat(y[0],y[1],1))));case 2:return real(NEG(bits(ps2LibmKernelCosFloat(y[0],y[1]))));default:return ps2LibmKernelSinFloat(y[0],y[1],1);}
}
float ps2LibmSinFloat(float x){
 if((bits(x)&0x7fffffff)<=0x3f490fd8)return ps2LibmKernelSinFloat(x,real(0),0);
 float y[2];int32_t n=ps2LibmRemPio2Float(x,y);
 switch(n&3){case 0:return ps2LibmKernelSinFloat(y[0],y[1],1);case 1:return ps2LibmKernelCosFloat(y[0],y[1]);case 2:return real(NEG(bits(ps2LibmKernelSinFloat(y[0],y[1],1))));default:return real(NEG(bits(ps2LibmKernelCosFloat(y[0],y[1]))));}
}

static void rotation(float angle,unsigned axis){
 uint32_t c=bits(ps2LibmCosFloat(angle)),s=bits(ps2LibmSinFloat(angle)),zero[4],m[16];EE_ROT_VU_READ(0,zero);
 uint32_t initial[16]={zero[3],0,0,0,0,zero[3],0,0,zero[2],0,zero[3],0,zero[0],zero[1],zero[2],zero[3]};memcpy(m,initial,64);
 m[0]=c;
 if(axis==1){m[2]=NEG(s);m[8]=s;m[10]=c;}else{m[1]=s;m[4]=NEG(s);m[5]=c;}
 for(unsigned row=0;row<4;row++)EE_ROT_VU_WRITE(28+row,m+row*4);
}
void sdfRotationYFloat(float angle){rotation(angle,1);}
void sdfRotationZFloat(float angle){rotation(angle,2);}
