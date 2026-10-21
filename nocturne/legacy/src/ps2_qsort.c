/* Complete original 002D4860 qsort algorithm, fixed original-PC statements.
 * Real guest arrays and finite real comparator bodies; no host sort or decoder.
 * Local semantic values/private spill storage are not an emulated CPU bank or
 * a promise of native guest-frame/volatile/HI-LO equality. Private aliases are
 * excluded. All comparison calls and their exact ordering remain observable.
 */
#include "ps2_qsort.h"
#include "fusion_sort.h"
#include "nocturne.h"
#include <stdlib.h>
#include <string.h>
extern uint64_t nocturneCompendiumRecordsCompare(uint64_t target,uint64_t left,uint64_t right);
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveQsortAddress(a);}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t fp64(const uint8_t *p,unsigned o){uint64_t v;memcpy(&v,p+o,8);return v;}
static uint32_t fp32(const uint8_t *p,unsigned o){uint32_t v;memcpy(&v,p+o,4);return v;}
static void fs64(uint8_t *p,unsigned o,uint64_t v){memcpy(p+o,&v,8);}
static void fs32(uint8_t *p,unsigned o,uint32_t v){memcpy(p+o,&v,4);}
static uint64_t compare(uint32_t pc,uint64_t target,uint64_t left,uint64_t right){
 uint64_t result;
 switch((uint32_t)target){
 case UINT32_C(0x002131e0):result=ps2FusionSortCompareSkill_002131E0(left,right);break;
 case UINT32_C(0x00213230):result=ps2FusionSortCompareDescriptor_00213230(left,right);break;
 default:result=nocturneCompendiumRecordsCompare(target,left,right);break;
 }
 nocturneQsortNoteCompare(pc,target,left,right,result);
 return result;
}
static void body(uint64_t r[32]);

static void body(uint64_t r[32]){
uint8_t frame[192]={0};uint64_t lo=0;
/* 002d4860: addiu sp,sp,-0xc0 */ r[29]=sx((uint32_t)r[29]+UINT32_C(0xffffff40));
/* 002d4864: sd s0,0x70(sp) */ fs64(frame,112u,r[16]);
/* 002d4868: sd s1,0x78(sp) */ fs64(frame,120u,r[17]);
/* 002d486c: sd s2,0x80(sp) */ fs64(frame,128u,r[18]);
/* 002d4870: sd s3,0x88(sp) */ fs64(frame,136u,r[19]);
/* 002d4874: sd s5,0x98(sp) */ fs64(frame,152u,r[21]);
/* 002d4878: sd s7,0xa8(sp) */ fs64(frame,168u,r[23]);
/* 002d487c: sd ra,0xb8(sp) */ fs64(frame,184u,r[31]);
/* 002d4880: sw a1,0x0(sp) */ fs32(frame,0u,(uint32_t)r[5]);
/* 002d4884: sd s4,0x90(sp) */ fs64(frame,144u,r[20]);
/* 002d4888: move s4,a2 */ r[20]=r[6];
/* 002d488c: sd s6,0xa0(sp) */ fs64(frame,160u,r[22]);
/* 002d4890: move s6,a0 */ r[22]=r[4];
/* 002d4894: sd s8,0xb0(sp) */ fs64(frame,176u,r[30]);
/* 002d4898: move s8,a3 */ r[30]=r[7];
L_002d489c:;
/* 002d489c: andi v0,s6,0x7 */ r[2]=r[22]&UINT64_C(0x7);
/* 002d48a0: bne v0,zero,0x002d48bc */ {int taken=(r[2]!=r[0]);/* delay 002d48a4 */ r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_002d48bc;}}
/* 002d48a8: andi v0,s4,0x7 */ r[2]=r[20]&UINT64_C(0x7);
/* 002d48ac: bnel v0,zero,0x002d48bc */ {int taken=(r[2]!=r[0]);if(taken){/* delay 002d48b0 */ r[2]=sx(UINT32_C(0x00000002));goto L_002d48bc;}}
/* 002d48b4: xori v0,s4,0x8 */ r[2]=r[20]^UINT64_C(0x8);
/* 002d48b8: sltu v0,zero,v0 */ r[2]=(r[0]<r[2]);
L_002d48bc:;
/* 002d48bc: sw v0,0x4(sp) */ fs32(frame,4u,(uint32_t)r[2]);
/* 002d48c0: lw v1,0x0(sp) */ r[3]=sx(fp32(frame,0u));
/* 002d48c4: sltiu v0,v1,0x7 */ r[2]=(r[3]<sx(UINT32_C(0x00000007)));
/* 002d48c8: beq v0,zero,0x002d49d0 */ {int taken=(r[2]==r[0]);/* delay 002d48cc */ fs32(frame,8u,(uint32_t)r[0]);if(taken){goto L_002d49d0;}}
/* 002d48d0: mult v0,v1,s4 */ {int64_t product=(int64_t)(int32_t)(uint32_t)r[3]*(int64_t)(int32_t)(uint32_t)r[20];r[2]=sx((uint32_t)(uint64_t)product);}
/* 002d48d4: addu s3,s6,s4 */ r[19]=sx((uint32_t)r[22]+(uint32_t)r[20]);
/* 002d48d8: addu v1,v0,s6 */ r[3]=sx((uint32_t)r[2]+(uint32_t)r[22]);
/* 002d48dc: sltu v0,s3,v1 */ r[2]=(r[19]<r[3]);
/* 002d48e0: beql v0,zero,0x002d5220 */ {int taken=(r[2]==r[0]);if(taken){/* delay 002d48e4 */ r[16]=fp64(frame,112u);goto L_002d5220;}}
/* 002d48e8: sw v1,0xc(sp) */ fs32(frame,12u,(uint32_t)r[3]);
/* 002d48ec: srl v0,s4,0x3 */ r[2]=sx((uint32_t)r[20]>>3u);
/* 002d48f0: lw v1,0x4(sp) */ r[3]=sx(fp32(frame,4u));
/* 002d48f4: dsll32 s7,v0,0x0 */ r[23]=r[2]<<32u;
/* 002d48f8: dsll32 s2,s4,0x0 */ r[18]=r[20]<<32u;
/* 002d48fc: slti s5,v1,0x2 */ r[21]=less(r[3],sx(UINT32_C(0x00000002)));
/* 002d4900: b 0x002d498c */ /* delay 002d4904 */ r[16]=r[19];goto L_002d498c;
L_002d4908:;
/* 002d4908: bne a0,zero,0x002d4928 */ {int taken=(r[4]!=r[0]);/* delay 002d490c */ (void)0;if(taken){goto L_002d4928;}}
/* 002d4910: ld v1,0x0(s0) */ r[3]=quad((uint32_t)r[16]+UINT32_C(0x00000000));
/* 002d4914: ld v0,0x0(s1) */ r[2]=quad((uint32_t)r[17]+UINT32_C(0x00000000));
/* 002d4918: sd v0,0x0(s0) */ sd((uint32_t)r[16]+UINT32_C(0x00000000),r[2]);
/* 002d491c: b 0x002d4988 */ /* delay 002d4920 */ sd((uint32_t)r[17]+UINT32_C(0x00000000),r[3]);goto L_002d4988;
L_002d4928:;
/* 002d4928: beq s5,zero,0x002d4960 */ {int taken=(r[21]==r[0]);/* delay 002d492c */ r[4]=r[16];if(taken){goto L_002d4960;}}
/* 002d4930: dsrl32 a1,s7,0x0 */ r[5]=r[23]>>32u;
/* 002d4934: move a2,s1 */ r[6]=r[17];
L_002d4938:;
/* 002d4938: ld v1,0x0(a0) */ r[3]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d493c: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d4940: ld v0,0x0(a2) */ r[2]=quad((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d4944: sd v0,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[2]);
/* 002d4948: addiu a0,a0,0x8 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));
/* 002d494c: sd v1,0x0(a2) */ sd((uint32_t)r[6]+UINT32_C(0x00000000),r[3]);
/* 002d4950: bgtz a1,0x002d4938 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d4954 */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000008));if(taken){goto L_002d4938;}}
/* 002d4958: b 0x002d498c */ /* delay 002d495c */ r[16]=r[17];goto L_002d498c;
L_002d4960:;
/* 002d4960: dsrl32 a1,s2,0x0 */ r[5]=r[18]>>32u;
/* 002d4964: move a2,s1 */ r[6]=r[17];
L_002d4968:;
/* 002d4968: lb v1,0x0(a0) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[4]+UINT32_C(0x00000000)));
/* 002d496c: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d4970: lbu v0,0x0(a2) */ r[2]=*at((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d4974: sb v0,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d4978: addiu a0,a0,0x1 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));
/* 002d497c: sb v1,0x0(a2) */ *at((uint32_t)r[6]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d4980: bgtz a1,0x002d4968 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d4984 */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000001));if(taken){goto L_002d4968;}}
L_002d4988:;
/* 002d4988: move s0,s1 */ r[16]=r[17];
L_002d498c:;
/* 002d498c: sltu v0,s6,s0 */ r[2]=(r[22]<r[16]);
/* 002d4990: beq v0,zero,0x002d49b4 */ {int taken=(r[2]==r[0]);/* delay 002d4994 */ r[3]=sx(fp32(frame,12u));if(taken){goto L_002d49b4;}}
/* 002d4998: subu s1,s0,s4 */ r[17]=sx((uint32_t)r[16]-(uint32_t)r[20]);
/* 002d499c: move a1,s0 */ r[5]=r[16];
/* 002d49a0: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d49a8);/* delay 002d49a4 */ r[4]=r[17];r[2]=compare(0x002d49a0u,target,r[4],r[5]);}
/* 002d49a8: bgtzl v0,0x002d4908 */ {int taken=((!neg(r[2])&&r[2]));if(taken){/* delay 002d49ac */ r[4]=sx(fp32(frame,4u));goto L_002d4908;}}
/* 002d49b0: lw v1,0xc(sp) */ r[3]=sx(fp32(frame,12u));
L_002d49b4:;
/* 002d49b4: addu s3,s3,s4 */ r[19]=sx((uint32_t)r[19]+(uint32_t)r[20]);
/* 002d49b8: sltu v0,s3,v1 */ r[2]=(r[19]<r[3]);
/* 002d49bc: bnel v0,zero,0x002d498c */ {int taken=(r[2]!=r[0]);if(taken){/* delay 002d49c0 */ r[16]=r[19];goto L_002d498c;}}
/* 002d49c4: b 0x002d5220 */ /* delay 002d49c8 */ r[16]=fp64(frame,112u);goto L_002d5220;
L_002d49d0:;
/* 002d49d0: lw a0,0x0(sp) */ r[4]=sx(fp32(frame,0u));
/* 002d49d4: srl v0,a0,0x1 */ r[2]=sx((uint32_t)r[4]>>1u);
/* 002d49d8: sltiu v1,a0,0x8 */ r[3]=(r[4]<sx(UINT32_C(0x00000008)));
/* 002d49dc: mult a0,v0,s4 */ {int64_t product=(int64_t)(int32_t)(uint32_t)r[2]*(int64_t)(int32_t)(uint32_t)r[20];r[4]=sx((uint32_t)(uint64_t)product);}
/* 002d49e0: bne v1,zero,0x002d4c20 */ {int taken=(r[3]!=r[0]);/* delay 002d49e4 */ r[19]=sx((uint32_t)r[4]+(uint32_t)r[22]);if(taken){goto L_002d4c20;}}
/* 002d49e8: lw v0,0x0(sp) */ r[2]=sx(fp32(frame,0u));
/* 002d49ec: move s0,s6 */ r[16]=r[22];
/* 002d49f0: lw v1,0x0(sp) */ r[3]=sx(fp32(frame,0u));
/* 002d49f4: addiu v0,v0,-0x1 */ r[2]=sx((uint32_t)r[2]+UINT32_C(0xffffffff));
/* 002d49f8: sw v0,0x18(sp) */ fs32(frame,24u,(uint32_t)r[2]);
/* 002d49fc: sltiu v0,v1,0x29 */ r[2]=(r[3]<sx(UINT32_C(0x00000029)));
/* 002d4a00: lw v1,0x18(sp) */ r[3]=sx(fp32(frame,24u));
/* 002d4a04: mult v1,v1,s4 */ {int64_t product=(int64_t)(int32_t)(uint32_t)r[3]*(int64_t)(int32_t)(uint32_t)r[20];r[3]=sx((uint32_t)(uint64_t)product);}
/* 002d4a08: bne v0,zero,0x002d4ba0 */ {int taken=(r[2]!=r[0]);/* delay 002d4a0c */ r[21]=sx((uint32_t)r[3]+(uint32_t)r[22]);if(taken){goto L_002d4ba0;}}
/* 002d4a10: lw a0,0x0(sp) */ r[4]=sx(fp32(frame,0u));
/* 002d4a14: srl v0,a0,0x3 */ r[2]=sx((uint32_t)r[4]>>3u);
/* 002d4a18: move a0,s6 */ r[4]=r[22];
/* 002d4a1c: mult s7,v0,s4 */ {int64_t product=(int64_t)(int32_t)(uint32_t)r[2]*(int64_t)(int32_t)(uint32_t)r[20];r[23]=sx((uint32_t)(uint64_t)product);}
/* 002d4a20: sll v0,s7,0x1 */ r[2]=sx((uint32_t)r[23]<<1u);
/* 002d4a24: addu s0,s6,s7 */ r[16]=sx((uint32_t)r[22]+(uint32_t)r[23]);
/* 002d4a28: sw v0,0x10(sp) */ fs32(frame,16u,(uint32_t)r[2]);
/* 002d4a2c: move a1,s0 */ r[5]=r[16];
/* 002d4a30: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4a38);/* delay 002d4a34 */ r[17]=sx((uint32_t)r[2]+(uint32_t)r[22]);r[2]=compare(0x002d4a30u,target,r[4],r[5]);}
/* 002d4a38: bgez v0,0x002d4a68 */ {int taken=(!neg(r[2]));/* delay 002d4a3c */ r[4]=r[16];if(taken){goto L_002d4a68;}}
/* 002d4a40: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4a48);/* delay 002d4a44 */ r[5]=r[17];r[2]=compare(0x002d4a40u,target,r[4],r[5]);}
/* 002d4a48: bltz v0,0x002d4a98 */ {int taken=(neg(r[2]));/* delay 002d4a4c */ r[4]=r[22];if(taken){goto L_002d4a98;}}
/* 002d4a50: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4a58);/* delay 002d4a54 */ r[5]=r[17];r[2]=compare(0x002d4a50u,target,r[4],r[5]);}
/* 002d4a58: move v1,s1 */ r[3]=r[17];
/* 002d4a5c: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4a60: b 0x002d4a9c */ /* delay 002d4a64 */ if(r[2]==0){r[3]=r[22];}goto L_002d4a9c;
L_002d4a68:;
/* 002d4a68: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4a70);/* delay 002d4a6c */ r[5]=r[17];r[2]=compare(0x002d4a68u,target,r[4],r[5]);}
/* 002d4a70: bgtz v0,0x002d4a9c */ {int taken=((!neg(r[2])&&r[2]));/* delay 002d4a74 */ r[3]=r[16];if(taken){goto L_002d4a9c;}}
/* 002d4a78: move a0,s6 */ r[4]=r[22];
/* 002d4a7c: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4a84);/* delay 002d4a80 */ r[5]=r[17];r[2]=compare(0x002d4a7cu,target,r[4],r[5]);}
/* 002d4a84: move v1,s6 */ r[3]=r[22];
/* 002d4a88: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4a8c: b 0x002d4a9c */ /* delay 002d4a90 */ if(r[2]==0){r[3]=r[17];}goto L_002d4a9c;
L_002d4a98:;
/* 002d4a98: move v1,s0 */ r[3]=r[16];
L_002d4a9c:;
/* 002d4a9c: subu s2,s3,s7 */ r[18]=sx((uint32_t)r[19]-(uint32_t)r[23]);
/* 002d4aa0: move a1,s3 */ r[5]=r[19];
/* 002d4aa4: move a0,s2 */ r[4]=r[18];
/* 002d4aa8: move s0,v1 */ r[16]=r[3];
/* 002d4aac: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4ab4);/* delay 002d4ab0 */ r[17]=sx((uint32_t)r[19]+(uint32_t)r[23]);r[2]=compare(0x002d4aacu,target,r[4],r[5]);}
/* 002d4ab4: bgez v0,0x002d4ae8 */ {int taken=(!neg(r[2]));/* delay 002d4ab8 */ r[4]=r[19];if(taken){goto L_002d4ae8;}}
/* 002d4abc: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4ac4);/* delay 002d4ac0 */ r[5]=r[17];r[2]=compare(0x002d4abcu,target,r[4],r[5]);}
/* 002d4ac4: bltz v0,0x002d4b18 */ {int taken=(neg(r[2]));/* delay 002d4ac8 */ r[5]=r[17];if(taken){goto L_002d4b18;}}
/* 002d4acc: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4ad4);/* delay 002d4ad0 */ r[4]=r[18];r[2]=compare(0x002d4accu,target,r[4],r[5]);}
/* 002d4ad4: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4ad8: movz s1,s2,v0 */ if(r[2]==0){r[17]=r[18];}
/* 002d4adc: b 0x002d4b1c */ /* delay 002d4ae0 */ r[2]=r[17];goto L_002d4b1c;
L_002d4ae8:;
/* 002d4ae8: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4af0);/* delay 002d4aec */ r[5]=r[17];r[2]=compare(0x002d4ae8u,target,r[4],r[5]);}
/* 002d4af0: bgtzl v0,0x002d4b1c */ {int taken=((!neg(r[2])&&r[2]));if(taken){/* delay 002d4af4 */ r[2]=r[19];goto L_002d4b1c;}}
/* 002d4af8: move a0,s2 */ r[4]=r[18];
/* 002d4afc: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4b04);/* delay 002d4b00 */ r[5]=r[17];r[2]=compare(0x002d4afcu,target,r[4],r[5]);}
/* 002d4b04: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4b08: movz s2,s1,v0 */ if(r[2]==0){r[18]=r[17];}
/* 002d4b0c: b 0x002d4b1c */ /* delay 002d4b10 */ r[2]=r[18];goto L_002d4b1c;
L_002d4b18:;
/* 002d4b18: move v0,s3 */ r[2]=r[19];
L_002d4b1c:;
/* 002d4b1c: lw v1,0x10(sp) */ r[3]=sx(fp32(frame,16u));
/* 002d4b20: subu s1,s5,s7 */ r[17]=sx((uint32_t)r[21]-(uint32_t)r[23]);
/* 002d4b24: move a1,s1 */ r[5]=r[17];
/* 002d4b28: move s3,v0 */ r[19]=r[2];
/* 002d4b2c: subu s2,s5,v1 */ r[18]=sx((uint32_t)r[21]-(uint32_t)r[3]);
/* 002d4b30: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4b38);/* delay 002d4b34 */ r[4]=r[18];r[2]=compare(0x002d4b30u,target,r[4],r[5]);}
/* 002d4b38: bgez v0,0x002d4b68 */ {int taken=(!neg(r[2]));/* delay 002d4b3c */ r[4]=r[17];if(taken){goto L_002d4b68;}}
/* 002d4b40: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4b48);/* delay 002d4b44 */ r[5]=r[21];r[2]=compare(0x002d4b40u,target,r[4],r[5]);}
/* 002d4b48: bltz v0,0x002d4b98 */ {int taken=(neg(r[2]));/* delay 002d4b4c */ r[4]=r[18];if(taken){goto L_002d4b98;}}
/* 002d4b50: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4b58);/* delay 002d4b54 */ r[5]=r[21];r[2]=compare(0x002d4b50u,target,r[4],r[5]);}
/* 002d4b58: move a0,s5 */ r[4]=r[21];
/* 002d4b5c: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4b60: b 0x002d4b9c */ /* delay 002d4b64 */ if(r[2]==0){r[4]=r[18];}goto L_002d4b9c;
L_002d4b68:;
/* 002d4b68: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4b70);/* delay 002d4b6c */ r[5]=r[21];r[2]=compare(0x002d4b68u,target,r[4],r[5]);}
/* 002d4b70: bgtz v0,0x002d4b9c */ {int taken=((!neg(r[2])&&r[2]));/* delay 002d4b74 */ r[4]=r[17];if(taken){goto L_002d4b9c;}}
/* 002d4b78: move a0,s2 */ r[4]=r[18];
/* 002d4b7c: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4b84);/* delay 002d4b80 */ r[5]=r[21];r[2]=compare(0x002d4b7cu,target,r[4],r[5]);}
/* 002d4b84: move a0,s2 */ r[4]=r[18];
/* 002d4b88: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4b8c: b 0x002d4b9c */ /* delay 002d4b90 */ if(r[2]==0){r[4]=r[21];}goto L_002d4b9c;
L_002d4b98:;
/* 002d4b98: move a0,s1 */ r[4]=r[17];
L_002d4b9c:;
/* 002d4b9c: move s5,a0 */ r[21]=r[4];
L_002d4ba0:;
/* 002d4ba0: move a0,s0 */ r[4]=r[16];
/* 002d4ba4: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4bac);/* delay 002d4ba8 */ r[5]=r[19];r[2]=compare(0x002d4ba4u,target,r[4],r[5]);}
/* 002d4bac: bgez v0,0x002d4be0 */ {int taken=(!neg(r[2]));/* delay 002d4bb0 */ r[4]=r[19];if(taken){goto L_002d4be0;}}
/* 002d4bb4: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4bbc);/* delay 002d4bb8 */ r[5]=r[21];r[2]=compare(0x002d4bb4u,target,r[4],r[5]);}
/* 002d4bbc: bltz v0,0x002d4c10 */ {int taken=(neg(r[2]));/* delay 002d4bc0 */ r[4]=r[16];if(taken){goto L_002d4c10;}}
/* 002d4bc4: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4bcc);/* delay 002d4bc8 */ r[5]=r[21];r[2]=compare(0x002d4bc4u,target,r[4],r[5]);}
/* 002d4bcc: move a0,s5 */ r[4]=r[21];
/* 002d4bd0: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4bd4: b 0x002d4c14 */ /* delay 002d4bd8 */ if(r[2]==0){r[4]=r[16];}goto L_002d4c14;
L_002d4be0:;
/* 002d4be0: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4be8);/* delay 002d4be4 */ r[5]=r[21];r[2]=compare(0x002d4be0u,target,r[4],r[5]);}
/* 002d4be8: bgtz v0,0x002d4c14 */ {int taken=((!neg(r[2])&&r[2]));/* delay 002d4bec */ r[4]=r[19];if(taken){goto L_002d4c14;}}
/* 002d4bf0: move a0,s0 */ r[4]=r[16];
/* 002d4bf4: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4bfc);/* delay 002d4bf8 */ r[5]=r[21];r[2]=compare(0x002d4bf4u,target,r[4],r[5]);}
/* 002d4bfc: move a0,s0 */ r[4]=r[16];
/* 002d4c00: slti v0,v0,0x0 */ r[2]=less(r[2],sx(UINT32_C(0x00000000)));
/* 002d4c04: b 0x002d4c14 */ /* delay 002d4c08 */ if(r[2]==0){r[4]=r[21];}goto L_002d4c14;
L_002d4c10:;
/* 002d4c10: move a0,s3 */ r[4]=r[19];
L_002d4c14:;
/* 002d4c14: b 0x002d4c2c */ /* delay 002d4c18 */ r[19]=r[4];goto L_002d4c2c;
L_002d4c20:;
/* 002d4c20: lw a0,0x0(sp) */ r[4]=sx(fp32(frame,0u));
/* 002d4c24: addiu a0,a0,-0x1 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0xffffffff));
/* 002d4c28: sw a0,0x18(sp) */ fs32(frame,24u,(uint32_t)r[4]);
L_002d4c2c:;
/* 002d4c2c: lw v0,0x4(sp) */ r[2]=sx(fp32(frame,4u));
/* 002d4c30: bne v0,zero,0x002d4c50 */ {int taken=(r[2]!=r[0]);/* delay 002d4c34 */ r[3]=sx(fp32(frame,4u));if(taken){goto L_002d4c50;}}
/* 002d4c38: ld v1,0x0(s6) */ r[3]=quad((uint32_t)r[22]+UINT32_C(0x00000000));
/* 002d4c3c: ld v0,0x0(s3) */ r[2]=quad((uint32_t)r[19]+UINT32_C(0x00000000));
/* 002d4c40: sd v0,0x0(s6) */ sd((uint32_t)r[22]+UINT32_C(0x00000000),r[2]);
/* 002d4c44: b 0x002d4cc8 */ /* delay 002d4c48 */ sd((uint32_t)r[19]+UINT32_C(0x00000000),r[3]);goto L_002d4cc8;
L_002d4c50:;
/* 002d4c50: slti v0,v1,0x2 */ r[2]=less(r[3],sx(UINT32_C(0x00000002)));
/* 002d4c54: beq v0,zero,0x002d4c98 */ {int taken=(r[2]==r[0]);/* delay 002d4c58 */ r[2]=r[20]<<32u;if(taken){goto L_002d4c98;}}
/* 002d4c5c: srl v0,s4,0x3 */ r[2]=sx((uint32_t)r[20]>>3u);
/* 002d4c60: move a0,s3 */ r[4]=r[19];
/* 002d4c64: dsll32 v0,v0,0x0 */ r[2]=r[2]<<32u;
/* 002d4c68: move a2,s6 */ r[6]=r[22];
/* 002d4c6c: dsrl32 a3,v0,0x0 */ r[7]=r[2]>>32u;
L_002d4c70:;
/* 002d4c70: ld v1,0x0(a2) */ r[3]=quad((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d4c74: daddiu a3,a3,-0x1 */ r[7]=r[7]+sx(UINT32_C(0xffffffff));
/* 002d4c78: ld v0,0x0(a0) */ r[2]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4c7c: sd v0,0x0(a2) */ sd((uint32_t)r[6]+UINT32_C(0x00000000),r[2]);
/* 002d4c80: addiu a2,a2,0x8 */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000008));
/* 002d4c84: sd v1,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[3]);
/* 002d4c88: bgtz a3,0x002d4c70 */ {int taken=((!neg(r[7])&&r[7]));/* delay 002d4c8c */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));if(taken){goto L_002d4c70;}}
/* 002d4c90: b 0x002d4ccc */ /* delay 002d4c94 */ r[2]=sx(fp32(frame,24u));goto L_002d4ccc;
L_002d4c98:;
/* 002d4c98: move a0,s3 */ r[4]=r[19];
/* 002d4c9c: dsrl32 a1,v0,0x0 */ r[5]=r[2]>>32u;
/* 002d4ca0: move a2,s6 */ r[6]=r[22];
/* 002d4ca4: nop  */ (void)0;
L_002d4ca8:;
/* 002d4ca8: lb v1,0x0(a2) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[6]+UINT32_C(0x00000000)));
/* 002d4cac: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d4cb0: lbu v0,0x0(a0) */ r[2]=*at((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4cb4: sb v0,0x0(a2) */ *at((uint32_t)r[6]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d4cb8: addiu a2,a2,0x1 */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000001));
/* 002d4cbc: sb v1,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d4cc0: bgtz a1,0x002d4ca8 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d4cc4 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));if(taken){goto L_002d4ca8;}}
L_002d4cc8:;
/* 002d4cc8: lw v0,0x18(sp) */ r[2]=sx(fp32(frame,24u));
L_002d4ccc:;
/* 002d4ccc: addu s1,s6,s4 */ r[17]=sx((uint32_t)r[22]+(uint32_t)r[20]);
/* 002d4cd0: lw v1,0x4(sp) */ r[3]=sx(fp32(frame,4u));
/* 002d4cd4: move s5,s1 */ r[21]=r[17];
/* 002d4cd8: mult v0,v0,s4 */ {int64_t product=(int64_t)(int32_t)(uint32_t)r[2]*(int64_t)(int32_t)(uint32_t)r[20];r[2]=sx((uint32_t)(uint64_t)product);}
/* 002d4cdc: dsll32 t1,s4,0x0 */ r[9]=r[20]<<32u;
/* 002d4ce0: slti t2,v1,0x2 */ r[10]=less(r[3],sx(UINT32_C(0x00000002)));
/* 002d4ce4: sw s1,0x1c(sp) */ fs32(frame,28u,(uint32_t)r[17]);
/* 002d4ce8: addu s3,v0,s6 */ r[19]=sx((uint32_t)r[2]+(uint32_t)r[22]);
/* 002d4cec: srl v0,s4,0x3 */ r[2]=sx((uint32_t)r[20]>>3u);
/* 002d4cf0: dsll32 t3,v0,0x0 */ r[11]=r[2]<<32u;
/* 002d4cf4: b 0x002d4da0 */ /* delay 002d4cf8 */ r[18]=r[19];goto L_002d4da0;
L_002d4d00:;
/* 002d4d00: bnel a1,zero,0x002d4da0 */ {int taken=(r[5]!=r[0]);if(taken){/* delay 002d4d04 */ r[17]=sx((uint32_t)r[17]+(uint32_t)r[20]);goto L_002d4da0;}}
/* 002d4d08: lw v0,0x4(sp) */ r[2]=sx(fp32(frame,4u));
/* 002d4d0c: li a0,0x1 */ r[4]=sx(UINT32_C(0x00000001));
/* 002d4d10: bne v0,zero,0x002d4d30 */ {int taken=(r[2]!=r[0]);/* delay 002d4d14 */ fs32(frame,8u,(uint32_t)r[4]);if(taken){goto L_002d4d30;}}
/* 002d4d18: ld v1,0x0(s5) */ r[3]=quad((uint32_t)r[21]+UINT32_C(0x00000000));
/* 002d4d1c: ld v0,0x0(s1) */ r[2]=quad((uint32_t)r[17]+UINT32_C(0x00000000));
/* 002d4d20: sd v0,0x0(s5) */ sd((uint32_t)r[21]+UINT32_C(0x00000000),r[2]);
/* 002d4d24: b 0x002d4d98 */ /* delay 002d4d28 */ sd((uint32_t)r[17]+UINT32_C(0x00000000),r[3]);goto L_002d4d98;
L_002d4d30:;
/* 002d4d30: beq t2,zero,0x002d4d68 */ {int taken=(r[10]==r[0]);/* delay 002d4d34 */ r[6]=r[11]>>32u;if(taken){goto L_002d4d68;}}
/* 002d4d38: move a1,s5 */ r[5]=r[21];
/* 002d4d3c: move a0,s1 */ r[4]=r[17];
L_002d4d40:;
/* 002d4d40: ld v1,0x0(a1) */ r[3]=quad((uint32_t)r[5]+UINT32_C(0x00000000));
/* 002d4d44: daddiu a2,a2,-0x1 */ r[6]=r[6]+sx(UINT32_C(0xffffffff));
/* 002d4d48: ld v0,0x0(a0) */ r[2]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4d4c: sd v0,0x0(a1) */ sd((uint32_t)r[5]+UINT32_C(0x00000000),r[2]);
/* 002d4d50: addiu a1,a1,0x8 */ r[5]=sx((uint32_t)r[5]+UINT32_C(0x00000008));
/* 002d4d54: sd v1,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[3]);
/* 002d4d58: bgtz a2,0x002d4d40 */ {int taken=((!neg(r[6])&&r[6]));/* delay 002d4d5c */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));if(taken){goto L_002d4d40;}}
/* 002d4d60: b 0x002d4d9c */ /* delay 002d4d64 */ r[21]=sx((uint32_t)r[21]+(uint32_t)r[20]);goto L_002d4d9c;
L_002d4d68:;
/* 002d4d68: dsrl32 a2,t1,0x0 */ r[6]=r[9]>>32u;
/* 002d4d6c: move a1,s5 */ r[5]=r[21];
/* 002d4d70: move a0,s1 */ r[4]=r[17];
/* 002d4d74: nop  */ (void)0;
L_002d4d78:;
/* 002d4d78: lb v1,0x0(a1) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[5]+UINT32_C(0x00000000)));
/* 002d4d7c: daddiu a2,a2,-0x1 */ r[6]=r[6]+sx(UINT32_C(0xffffffff));
/* 002d4d80: lbu v0,0x0(a0) */ r[2]=*at((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4d84: sb v0,0x0(a1) */ *at((uint32_t)r[5]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d4d88: addiu a1,a1,0x1 */ r[5]=sx((uint32_t)r[5]+UINT32_C(0x00000001));
/* 002d4d8c: sb v1,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d4d90: bgtz a2,0x002d4d78 */ {int taken=((!neg(r[6])&&r[6]));/* delay 002d4d94 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));if(taken){goto L_002d4d78;}}
L_002d4d98:;
/* 002d4d98: addu s5,s5,s4 */ r[21]=sx((uint32_t)r[21]+(uint32_t)r[20]);
L_002d4d9c:;
/* 002d4d9c: addu s1,s1,s4 */ r[17]=sx((uint32_t)r[17]+(uint32_t)r[20]);
L_002d4da0:;
/* 002d4da0: sltu s0,s2,s1 */ r[16]=(r[18]<r[17]);
/* 002d4da4: bne s0,zero,0x002d4ddc */ {int taken=(r[16]!=r[0]);/* delay 002d4da8 */ r[3]=sx(fp32(frame,4u));if(taken){goto L_002d4ddc;}}
/* 002d4dac: sq t1,0x40(sp) */ fs64(frame,64u,r[9]);
/* 002d4db0: move a1,s6 */ r[5]=r[22];
/* 002d4db4: sq t2,0x50(sp) */ fs64(frame,80u,r[10]);
/* 002d4db8: move a0,s1 */ r[4]=r[17];
/* 002d4dbc: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4dc4);/* delay 002d4dc0 */ fs64(frame,96u,r[11]);r[2]=compare(0x002d4dbcu,target,r[4],r[5]);}
/* 002d4dc4: move a1,v0 */ r[5]=r[2];
/* 002d4dc8: lq t1,0x40(sp) */ r[9]=fp64(frame,64u);
/* 002d4dcc: lq t2,0x50(sp) */ r[10]=fp64(frame,80u);
/* 002d4dd0: blez a1,0x002d4d00 */ {int taken=((neg(r[5])||!r[5]));/* delay 002d4dd4 */ r[11]=fp64(frame,96u);if(taken){goto L_002d4d00;}}
/* 002d4dd8: lw v1,0x4(sp) */ r[3]=sx(fp32(frame,4u));
L_002d4ddc:;
/* 002d4ddc: srl v0,s4,0x3 */ r[2]=sx((uint32_t)r[20]>>3u);
/* 002d4de0: dsll32 a3,v0,0x0 */ r[7]=r[2]<<32u;
/* 002d4de4: dsll32 s7,s4,0x0 */ r[23]=r[20]<<32u;
/* 002d4de8: b 0x002d4e94 */ /* delay 002d4dec */ r[8]=less(r[3],sx(UINT32_C(0x00000002)));goto L_002d4e94;
L_002d4df0:;
/* 002d4df0: bnel a1,zero,0x002d4e90 */ {int taken=(r[5]!=r[0]);if(taken){/* delay 002d4df4 */ r[18]=sx((uint32_t)r[18]-(uint32_t)r[20]);goto L_002d4e90;}}
/* 002d4df8: lw v0,0x4(sp) */ r[2]=sx(fp32(frame,4u));
/* 002d4dfc: li a0,0x1 */ r[4]=sx(UINT32_C(0x00000001));
/* 002d4e00: bne v0,zero,0x002d4e20 */ {int taken=(r[2]!=r[0]);/* delay 002d4e04 */ fs32(frame,8u,(uint32_t)r[4]);if(taken){goto L_002d4e20;}}
/* 002d4e08: ld v1,0x0(s2) */ r[3]=quad((uint32_t)r[18]+UINT32_C(0x00000000));
/* 002d4e0c: ld v0,0x0(s3) */ r[2]=quad((uint32_t)r[19]+UINT32_C(0x00000000));
/* 002d4e10: sd v0,0x0(s2) */ sd((uint32_t)r[18]+UINT32_C(0x00000000),r[2]);
/* 002d4e14: b 0x002d4e88 */ /* delay 002d4e18 */ sd((uint32_t)r[19]+UINT32_C(0x00000000),r[3]);goto L_002d4e88;
L_002d4e20:;
/* 002d4e20: beq t0,zero,0x002d4e58 */ {int taken=(r[8]==r[0]);/* delay 002d4e24 */ r[6]=r[7]>>32u;if(taken){goto L_002d4e58;}}
/* 002d4e28: move a1,s2 */ r[5]=r[18];
/* 002d4e2c: move a0,s3 */ r[4]=r[19];
L_002d4e30:;
/* 002d4e30: ld v1,0x0(a1) */ r[3]=quad((uint32_t)r[5]+UINT32_C(0x00000000));
/* 002d4e34: daddiu a2,a2,-0x1 */ r[6]=r[6]+sx(UINT32_C(0xffffffff));
/* 002d4e38: ld v0,0x0(a0) */ r[2]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4e3c: sd v0,0x0(a1) */ sd((uint32_t)r[5]+UINT32_C(0x00000000),r[2]);
/* 002d4e40: addiu a1,a1,0x8 */ r[5]=sx((uint32_t)r[5]+UINT32_C(0x00000008));
/* 002d4e44: sd v1,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[3]);
/* 002d4e48: bgtz a2,0x002d4e30 */ {int taken=((!neg(r[6])&&r[6]));/* delay 002d4e4c */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));if(taken){goto L_002d4e30;}}
/* 002d4e50: b 0x002d4e8c */ /* delay 002d4e54 */ r[19]=sx((uint32_t)r[19]-(uint32_t)r[20]);goto L_002d4e8c;
L_002d4e58:;
/* 002d4e58: dsrl32 a2,s7,0x0 */ r[6]=r[23]>>32u;
/* 002d4e5c: move a1,s2 */ r[5]=r[18];
/* 002d4e60: move a0,s3 */ r[4]=r[19];
/* 002d4e64: nop  */ (void)0;
L_002d4e68:;
/* 002d4e68: lb v1,0x0(a1) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[5]+UINT32_C(0x00000000)));
/* 002d4e6c: daddiu a2,a2,-0x1 */ r[6]=r[6]+sx(UINT32_C(0xffffffff));
/* 002d4e70: lbu v0,0x0(a0) */ r[2]=*at((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4e74: sb v0,0x0(a1) */ *at((uint32_t)r[5]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d4e78: addiu a1,a1,0x1 */ r[5]=sx((uint32_t)r[5]+UINT32_C(0x00000001));
/* 002d4e7c: sb v1,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d4e80: bgtz a2,0x002d4e68 */ {int taken=((!neg(r[6])&&r[6]));/* delay 002d4e84 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));if(taken){goto L_002d4e68;}}
L_002d4e88:;
/* 002d4e88: subu s3,s3,s4 */ r[19]=sx((uint32_t)r[19]-(uint32_t)r[20]);
L_002d4e8c:;
/* 002d4e8c: subu s2,s2,s4 */ r[18]=sx((uint32_t)r[18]-(uint32_t)r[20]);
L_002d4e90:;
/* 002d4e90: sltu s0,s2,s1 */ r[16]=(r[18]<r[17]);
L_002d4e94:;
/* 002d4e94: bne s0,zero,0x002d4f78 */ {int taken=(r[16]!=r[0]);/* delay 002d4e98 */ r[2]=sx(fp32(frame,8u));if(taken){goto L_002d4f78;}}
/* 002d4e9c: sq a3,0x20(sp) */ fs64(frame,32u,r[7]);
/* 002d4ea0: move a1,s6 */ r[5]=r[22];
/* 002d4ea4: sq t0,0x30(sp) */ fs64(frame,48u,r[8]);
/* 002d4ea8: move a0,s2 */ r[4]=r[18];
/* 002d4eac: sq t1,0x40(sp) */ fs64(frame,64u,r[9]);
/* 002d4eb0: sq t2,0x50(sp) */ fs64(frame,80u,r[10]);
/* 002d4eb4: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d4ebc);/* delay 002d4eb8 */ fs64(frame,96u,r[11]);r[2]=compare(0x002d4eb4u,target,r[4],r[5]);}
/* 002d4ebc: move a1,v0 */ r[5]=r[2];
/* 002d4ec0: lq a3,0x20(sp) */ r[7]=fp64(frame,32u);
/* 002d4ec4: lq t0,0x30(sp) */ r[8]=fp64(frame,48u);
/* 002d4ec8: lq t1,0x40(sp) */ r[9]=fp64(frame,64u);
/* 002d4ecc: lq t2,0x50(sp) */ r[10]=fp64(frame,80u);
/* 002d4ed0: bgez a1,0x002d4df0 */ {int taken=(!neg(r[5]));/* delay 002d4ed4 */ r[11]=fp64(frame,96u);if(taken){goto L_002d4df0;}}
/* 002d4ed8: lw v1,0x4(sp) */ r[3]=sx(fp32(frame,4u));
/* 002d4edc: bne v1,zero,0x002d4ef8 */ {int taken=(r[3]!=r[0]);/* delay 002d4ee0 */ (void)0;if(taken){goto L_002d4ef8;}}
/* 002d4ee4: ld v1,0x0(s1) */ r[3]=quad((uint32_t)r[17]+UINT32_C(0x00000000));
/* 002d4ee8: ld v0,0x0(s2) */ r[2]=quad((uint32_t)r[18]+UINT32_C(0x00000000));
/* 002d4eec: sd v0,0x0(s1) */ sd((uint32_t)r[17]+UINT32_C(0x00000000),r[2]);
/* 002d4ef0: b 0x002d4f60 */ /* delay 002d4ef4 */ sd((uint32_t)r[18]+UINT32_C(0x00000000),r[3]);goto L_002d4f60;
L_002d4ef8:;
/* 002d4ef8: beq t2,zero,0x002d4f30 */ {int taken=(r[10]==r[0]);/* delay 002d4efc */ r[6]=r[11]>>32u;if(taken){goto L_002d4f30;}}
/* 002d4f00: move a1,s1 */ r[5]=r[17];
/* 002d4f04: move a0,s2 */ r[4]=r[18];
L_002d4f08:;
/* 002d4f08: ld v1,0x0(a1) */ r[3]=quad((uint32_t)r[5]+UINT32_C(0x00000000));
/* 002d4f0c: daddiu a2,a2,-0x1 */ r[6]=r[6]+sx(UINT32_C(0xffffffff));
/* 002d4f10: ld v0,0x0(a0) */ r[2]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4f14: sd v0,0x0(a1) */ sd((uint32_t)r[5]+UINT32_C(0x00000000),r[2]);
/* 002d4f18: addiu a1,a1,0x8 */ r[5]=sx((uint32_t)r[5]+UINT32_C(0x00000008));
/* 002d4f1c: sd v1,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[3]);
/* 002d4f20: bgtz a2,0x002d4f08 */ {int taken=((!neg(r[6])&&r[6]));/* delay 002d4f24 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));if(taken){goto L_002d4f08;}}
/* 002d4f28: b 0x002d4f64 */ /* delay 002d4f2c */ r[4]=sx(UINT32_C(0x00000001));goto L_002d4f64;
L_002d4f30:;
/* 002d4f30: dsrl32 a2,t1,0x0 */ r[6]=r[9]>>32u;
/* 002d4f34: move a1,s1 */ r[5]=r[17];
/* 002d4f38: move a0,s2 */ r[4]=r[18];
/* 002d4f3c: nop  */ (void)0;
L_002d4f40:;
/* 002d4f40: lb v1,0x0(a1) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[5]+UINT32_C(0x00000000)));
/* 002d4f44: daddiu a2,a2,-0x1 */ r[6]=r[6]+sx(UINT32_C(0xffffffff));
/* 002d4f48: lbu v0,0x0(a0) */ r[2]=*at((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4f4c: sb v0,0x0(a1) */ *at((uint32_t)r[5]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d4f50: addiu a1,a1,0x1 */ r[5]=sx((uint32_t)r[5]+UINT32_C(0x00000001));
/* 002d4f54: sb v1,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d4f58: bgtz a2,0x002d4f40 */ {int taken=((!neg(r[6])&&r[6]));/* delay 002d4f5c */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));if(taken){goto L_002d4f40;}}
L_002d4f60:;
/* 002d4f60: li a0,0x1 */ r[4]=sx(UINT32_C(0x00000001));
L_002d4f64:;
/* 002d4f64: addu s1,s1,s4 */ r[17]=sx((uint32_t)r[17]+(uint32_t)r[20]);
/* 002d4f68: sw a0,0x8(sp) */ fs32(frame,8u,(uint32_t)r[4]);
/* 002d4f6c: b 0x002d4da0 */ /* delay 002d4f70 */ r[18]=sx((uint32_t)r[18]-(uint32_t)r[20]);goto L_002d4da0;
L_002d4f78:;
/* 002d4f78: bne v0,zero,0x002d5088 */ {int taken=(r[2]!=r[0]);/* delay 002d4f7c */ r[5]=sx((uint32_t)r[17]-(uint32_t)r[21]);if(taken){goto L_002d5088;}}
/* 002d4f80: lw v0,0x0(sp) */ r[2]=sx(fp32(frame,0u));
/* 002d4f84: lw s3,0x1c(sp) */ r[19]=sx(fp32(frame,28u));
/* 002d4f88: mult v0,v0,s4 */ {int64_t product=(int64_t)(int32_t)(uint32_t)r[2]*(int64_t)(int32_t)(uint32_t)r[20];r[2]=sx((uint32_t)(uint64_t)product);}
/* 002d4f8c: addu v1,v0,s6 */ r[3]=sx((uint32_t)r[2]+(uint32_t)r[22]);
/* 002d4f90: sltu v0,s3,v1 */ r[2]=(r[19]<r[3]);
/* 002d4f94: beql v0,zero,0x002d5220 */ {int taken=(r[2]==r[0]);if(taken){/* delay 002d4f98 */ r[16]=fp64(frame,112u);goto L_002d5220;}}
/* 002d4f9c: sw v1,0x14(sp) */ fs32(frame,20u,(uint32_t)r[3]);
/* 002d4fa0: srl v0,s4,0x3 */ r[2]=sx((uint32_t)r[20]>>3u);
/* 002d4fa4: lw v1,0x4(sp) */ r[3]=sx(fp32(frame,4u));
/* 002d4fa8: dsll32 s7,v0,0x0 */ r[23]=r[2]<<32u;
/* 002d4fac: dsll32 s2,s4,0x0 */ r[18]=r[20]<<32u;
/* 002d4fb0: slti s5,v1,0x2 */ r[21]=less(r[3],sx(UINT32_C(0x00000002)));
/* 002d4fb4: b 0x002d5044 */ /* delay 002d4fb8 */ r[16]=r[19];goto L_002d5044;
L_002d4fc0:;
/* 002d4fc0: bne a0,zero,0x002d4fe0 */ {int taken=(r[4]!=r[0]);/* delay 002d4fc4 */ (void)0;if(taken){goto L_002d4fe0;}}
/* 002d4fc8: ld v1,0x0(s0) */ r[3]=quad((uint32_t)r[16]+UINT32_C(0x00000000));
/* 002d4fcc: ld v0,0x0(s1) */ r[2]=quad((uint32_t)r[17]+UINT32_C(0x00000000));
/* 002d4fd0: sd v0,0x0(s0) */ sd((uint32_t)r[16]+UINT32_C(0x00000000),r[2]);
/* 002d4fd4: b 0x002d5040 */ /* delay 002d4fd8 */ sd((uint32_t)r[17]+UINT32_C(0x00000000),r[3]);goto L_002d5040;
L_002d4fe0:;
/* 002d4fe0: beq s5,zero,0x002d5018 */ {int taken=(r[21]==r[0]);/* delay 002d4fe4 */ r[4]=r[16];if(taken){goto L_002d5018;}}
/* 002d4fe8: dsrl32 a1,s7,0x0 */ r[5]=r[23]>>32u;
/* 002d4fec: move a2,s1 */ r[6]=r[17];
L_002d4ff0:;
/* 002d4ff0: ld v1,0x0(a0) */ r[3]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d4ff4: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d4ff8: ld v0,0x0(a2) */ r[2]=quad((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d4ffc: sd v0,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[2]);
/* 002d5000: addiu a0,a0,0x8 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));
/* 002d5004: sd v1,0x0(a2) */ sd((uint32_t)r[6]+UINT32_C(0x00000000),r[3]);
/* 002d5008: bgtz a1,0x002d4ff0 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d500c */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000008));if(taken){goto L_002d4ff0;}}
/* 002d5010: b 0x002d5044 */ /* delay 002d5014 */ r[16]=r[17];goto L_002d5044;
L_002d5018:;
/* 002d5018: dsrl32 a1,s2,0x0 */ r[5]=r[18]>>32u;
/* 002d501c: move a2,s1 */ r[6]=r[17];
L_002d5020:;
/* 002d5020: lb v1,0x0(a0) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[4]+UINT32_C(0x00000000)));
/* 002d5024: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d5028: lbu v0,0x0(a2) */ r[2]=*at((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d502c: sb v0,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d5030: addiu a0,a0,0x1 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));
/* 002d5034: sb v1,0x0(a2) */ *at((uint32_t)r[6]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d5038: bgtz a1,0x002d5020 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d503c */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000001));if(taken){goto L_002d5020;}}
L_002d5040:;
/* 002d5040: move s0,s1 */ r[16]=r[17];
L_002d5044:;
/* 002d5044: sltu v0,s6,s0 */ r[2]=(r[22]<r[16]);
/* 002d5048: beq v0,zero,0x002d506c */ {int taken=(r[2]==r[0]);/* delay 002d504c */ r[3]=sx(fp32(frame,20u));if(taken){goto L_002d506c;}}
/* 002d5050: subu s1,s0,s4 */ r[17]=sx((uint32_t)r[16]-(uint32_t)r[20]);
/* 002d5054: move a1,s0 */ r[5]=r[16];
/* 002d5058: jalr s8 */ {uint64_t target=r[30];r[31]=UINT64_C(0x002d5060);/* delay 002d505c */ r[4]=r[17];r[2]=compare(0x002d5058u,target,r[4],r[5]);}
/* 002d5060: bgtzl v0,0x002d4fc0 */ {int taken=((!neg(r[2])&&r[2]));if(taken){/* delay 002d5064 */ r[4]=sx(fp32(frame,4u));goto L_002d4fc0;}}
/* 002d5068: lw v1,0x14(sp) */ r[3]=sx(fp32(frame,20u));
L_002d506c:;
/* 002d506c: addu s3,s3,s4 */ r[19]=sx((uint32_t)r[19]+(uint32_t)r[20]);
/* 002d5070: sltu v0,s3,v1 */ r[2]=(r[19]<r[3]);
/* 002d5074: bnel v0,zero,0x002d5044 */ {int taken=(r[2]!=r[0]);if(taken){/* delay 002d5078 */ r[16]=r[19];goto L_002d5044;}}
/* 002d507c: b 0x002d5220 */ /* delay 002d5080 */ r[16]=fp64(frame,112u);goto L_002d5220;
L_002d5088:;
/* 002d5088: subu v0,s5,s6 */ r[2]=sx((uint32_t)r[21]-(uint32_t)r[22]);
/* 002d508c: slt v1,v0,a1 */ r[3]=less(r[2],r[5]);
/* 002d5090: move a3,a1 */ r[7]=r[5];
/* 002d5094: movn a1,v0,v1 */ if(r[3]!=0){r[5]=r[2];}
/* 002d5098: lw v0,0x0(sp) */ r[2]=sx(fp32(frame,0u));
/* 002d509c: mult v0,v0,s4 */ {int64_t product=(int64_t)(int32_t)(uint32_t)r[2]*(int64_t)(int32_t)(uint32_t)r[20];r[2]=sx((uint32_t)(uint64_t)product);}
/* 002d50a0: blez a1,0x002d5128 */ {int taken=((neg(r[5])||!r[5]));/* delay 002d50a4 */ r[21]=sx((uint32_t)r[2]+(uint32_t)r[22]);if(taken){goto L_002d5128;}}
/* 002d50a8: lw v1,0x4(sp) */ r[3]=sx(fp32(frame,4u));
/* 002d50ac: slti v0,v1,0x2 */ r[2]=less(r[3],sx(UINT32_C(0x00000002)));
/* 002d50b0: beq v0,zero,0x002d50f8 */ {int taken=(r[2]==r[0]);/* delay 002d50b4 */ r[3]=sx((uint32_t)r[17]-(uint32_t)r[5]);if(taken){goto L_002d50f8;}}
/* 002d50b8: srl v0,a1,0x3 */ r[2]=sx((uint32_t)r[5]>>3u);
/* 002d50bc: move a2,v1 */ r[6]=r[3];
/* 002d50c0: dsll32 v0,v0,0x0 */ r[2]=r[2]<<32u;
/* 002d50c4: move a0,s6 */ r[4]=r[22];
/* 002d50c8: dsrl32 a1,v0,0x0 */ r[5]=r[2]>>32u;
/* 002d50cc: nop  */ (void)0;
L_002d50d0:;
/* 002d50d0: ld v1,0x0(a0) */ r[3]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d50d4: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d50d8: ld v0,0x0(a2) */ r[2]=quad((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d50dc: sd v0,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[2]);
/* 002d50e0: addiu a0,a0,0x8 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));
/* 002d50e4: sd v1,0x0(a2) */ sd((uint32_t)r[6]+UINT32_C(0x00000000),r[3]);
/* 002d50e8: bgtz a1,0x002d50d0 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d50ec */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000008));if(taken){goto L_002d50d0;}}
/* 002d50f0: b 0x002d512c */ /* delay 002d50f4 */ r[3]=sx((uint32_t)r[21]-(uint32_t)r[19]);goto L_002d512c;
L_002d50f8:;
/* 002d50f8: dsll32 v0,a1,0x0 */ r[2]=r[5]<<32u;
/* 002d50fc: move a2,v1 */ r[6]=r[3];
/* 002d5100: dsrl32 a1,v0,0x0 */ r[5]=r[2]>>32u;
/* 002d5104: move a0,s6 */ r[4]=r[22];
L_002d5108:;
/* 002d5108: lb v1,0x0(a0) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[4]+UINT32_C(0x00000000)));
/* 002d510c: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d5110: lbu v0,0x0(a2) */ r[2]=*at((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d5114: sb v0,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d5118: addiu a0,a0,0x1 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));
/* 002d511c: sb v1,0x0(a2) */ *at((uint32_t)r[6]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d5120: bgtz a1,0x002d5108 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d5124 */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000001));if(taken){goto L_002d5108;}}
L_002d5128:;
/* 002d5128: subu v1,s5,s3 */ r[3]=sx((uint32_t)r[21]-(uint32_t)r[19]);
L_002d512c:;
/* 002d512c: subu s0,s3,s2 */ r[16]=sx((uint32_t)r[19]-(uint32_t)r[18]);
/* 002d5130: subu a1,v1,s4 */ r[5]=sx((uint32_t)r[3]-(uint32_t)r[20]);
/* 002d5134: sltu v0,s0,a1 */ r[2]=(r[16]<r[5]);
/* 002d5138: movn a1,s0,v0 */ if(r[2]!=0){r[5]=r[16];}
/* 002d513c: blezl a1,0x002d51c4 */ {int taken=((neg(r[5])||!r[5]));if(taken){/* delay 002d5140 */ r[5]=r[7];goto L_002d51c4;}}
/* 002d5144: lw a0,0x4(sp) */ r[4]=sx(fp32(frame,4u));
/* 002d5148: slti v0,a0,0x2 */ r[2]=less(r[4],sx(UINT32_C(0x00000002)));
/* 002d514c: beq v0,zero,0x002d5190 */ {int taken=(r[2]==r[0]);/* delay 002d5150 */ r[3]=sx((uint32_t)r[21]-(uint32_t)r[5]);if(taken){goto L_002d5190;}}
/* 002d5154: srl v0,a1,0x3 */ r[2]=sx((uint32_t)r[5]>>3u);
/* 002d5158: move a0,s1 */ r[4]=r[17];
/* 002d515c: dsll32 v0,v0,0x0 */ r[2]=r[2]<<32u;
/* 002d5160: move a2,v1 */ r[6]=r[3];
/* 002d5164: dsrl32 a1,v0,0x0 */ r[5]=r[2]>>32u;
L_002d5168:;
/* 002d5168: ld v1,0x0(a0) */ r[3]=quad((uint32_t)r[4]+UINT32_C(0x00000000));
/* 002d516c: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d5170: ld v0,0x0(a2) */ r[2]=quad((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d5174: sd v0,0x0(a0) */ sd((uint32_t)r[4]+UINT32_C(0x00000000),r[2]);
/* 002d5178: addiu a0,a0,0x8 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000008));
/* 002d517c: sd v1,0x0(a2) */ sd((uint32_t)r[6]+UINT32_C(0x00000000),r[3]);
/* 002d5180: bgtz a1,0x002d5168 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d5184 */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000008));if(taken){goto L_002d5168;}}
/* 002d5188: b 0x002d51c4 */ /* delay 002d518c */ r[5]=r[7];goto L_002d51c4;
L_002d5190:;
/* 002d5190: dsll32 v0,a1,0x0 */ r[2]=r[5]<<32u;
/* 002d5194: move a0,s1 */ r[4]=r[17];
/* 002d5198: dsrl32 a1,v0,0x0 */ r[5]=r[2]>>32u;
/* 002d519c: move a2,v1 */ r[6]=r[3];
L_002d51a0:;
/* 002d51a0: lb v1,0x0(a0) */ r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)r[4]+UINT32_C(0x00000000)));
/* 002d51a4: daddiu a1,a1,-0x1 */ r[5]=r[5]+sx(UINT32_C(0xffffffff));
/* 002d51a8: lbu v0,0x0(a2) */ r[2]=*at((uint32_t)r[6]+UINT32_C(0x00000000));
/* 002d51ac: sb v0,0x0(a0) */ *at((uint32_t)r[4]+UINT32_C(0x00000000))=(uint8_t)r[2];
/* 002d51b0: addiu a0,a0,0x1 */ r[4]=sx((uint32_t)r[4]+UINT32_C(0x00000001));
/* 002d51b4: sb v1,0x0(a2) */ *at((uint32_t)r[6]+UINT32_C(0x00000000))=(uint8_t)r[3];
/* 002d51b8: bgtz a1,0x002d51a0 */ {int taken=((!neg(r[5])&&r[5]));/* delay 002d51bc */ r[6]=sx((uint32_t)r[6]+UINT32_C(0x00000001));if(taken){goto L_002d51a0;}}
/* 002d51c0: move a1,a3 */ r[5]=r[7];
L_002d51c4:;
/* 002d51c4: sltu v0,s4,a1 */ r[2]=(r[20]<r[5]);
/* 002d51c8: beql v0,zero,0x002d51f8 */ {int taken=(r[2]==r[0]);if(taken){/* delay 002d51cc */ r[5]=r[16];goto L_002d51f8;}}
/* 002d51d0: divu a1,s4 */ {uint32_t dividend=(uint32_t)r[5],divisor=(uint32_t)r[20];lo=divisor?sx(dividend/divisor):UINT64_MAX;}
/* 002d51d4: move a0,s6 */ r[4]=r[22];
/* 002d51d8: move a2,s4 */ r[6]=r[20];
/* 002d51dc: move a3,s8 */ r[7]=r[30];
/* 002d51e0: beql s4,zero,0x002d51e8 */ {int taken=(r[20]==r[0]);if(taken){/* delay 002d51e4 */ nocturne_break(7);goto L_002d51e8;}}
L_002d51e8:;
/* 002d51e8: mflo a1 */ r[5]=lo;
/* 002d51ec: jal 0x002d4860 */ r[31]=UINT64_C(0x002d51f4);/* delay 002d51f0 */ (void)0;body(r);
/* 002d51f4: move a1,s0 */ r[5]=r[16];
L_002d51f8:;
/* 002d51f8: sltu v0,s4,a1 */ r[2]=(r[20]<r[5]);
/* 002d51fc: beq v0,zero,0x002d5220 */ {int taken=(r[2]==r[0]);/* delay 002d5200 */ r[16]=fp64(frame,112u);if(taken){goto L_002d5220;}}
/* 002d5204: divu a1,s4 */ {uint32_t dividend=(uint32_t)r[5],divisor=(uint32_t)r[20];lo=divisor?sx(dividend/divisor):UINT64_MAX;}
/* 002d5208: beql s4,zero,0x002d5210 */ {int taken=(r[20]==r[0]);if(taken){/* delay 002d520c */ nocturne_break(7);goto L_002d5210;}}
L_002d5210:;
/* 002d5210: subu s6,s5,a1 */ r[22]=sx((uint32_t)r[21]-(uint32_t)r[5]);
/* 002d5214: mflo v0 */ r[2]=lo;
/* 002d5218: b 0x002d489c */ /* delay 002d521c */ fs32(frame,0u,(uint32_t)r[2]);goto L_002d489c;
L_002d5220:;
/* 002d5220: ld s1,0x78(sp) */ r[17]=fp64(frame,120u);
/* 002d5224: ld s2,0x80(sp) */ r[18]=fp64(frame,128u);
/* 002d5228: ld s3,0x88(sp) */ r[19]=fp64(frame,136u);
/* 002d522c: ld s4,0x90(sp) */ r[20]=fp64(frame,144u);
/* 002d5230: ld s5,0x98(sp) */ r[21]=fp64(frame,152u);
/* 002d5234: ld s6,0xa0(sp) */ r[22]=fp64(frame,160u);
/* 002d5238: ld s7,0xa8(sp) */ r[23]=fp64(frame,168u);
/* 002d523c: ld s8,0xb0(sp) */ r[30]=fp64(frame,176u);
/* 002d5240: ld ra,0xb8(sp) */ r[31]=fp64(frame,184u);
/* 002d5244: jr ra */ /* delay 002d5248 */ r[29]=sx((uint32_t)r[29]+UINT32_C(0x000000c0));return;
}
void ps2Qsort_002D4860(uint64_t base,uint64_t count,uint64_t size,uint64_t callback){
uint64_t r[32]={0};r[4]=base;r[5]=count;r[6]=size;r[7]=callback;body(r);
}
