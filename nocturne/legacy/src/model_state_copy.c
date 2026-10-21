/* Complete original 002B2268 model-state copy, including its terminal delay. */
#include "model_state_copy.h"
#include "model_copy_helpers.h"
#include "ee_vu_rotation.h"
#include "resource_loader_flow.h"
#include <string.h>

static void *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveModelStateCopyAddress(address);
#else
    return (void *)(uintptr_t)address;
#endif
}
static uint32_t word(uint32_t address)
{ uint32_t value;memcpy(&value,at(address),4);return value; }
static uint16_t half(uint32_t address)
{ uint16_t value;memcpy(&value,at(address),2);return value; }
static uint8_t byte(uint32_t address)
{ uint8_t value;memcpy(&value,at(address),1);return value; }
static int32_t signedHalf(uint32_t address)
{ uint32_t value=half(address);return value&0x8000u?(int32_t)value-65536:(int32_t)value; }
static void sw(uint32_t address,uint32_t value)
{ memcpy(at(address),&value,4); }
static void sh(uint32_t address,uint16_t value)
{ memcpy(at(address),&value,2); }
static uint64_t sx(uint32_t value)
{ return (uint64_t)(int64_t)(int32_t)value; }

/* Each LQ/SQ pair completes before the next source quad is loaded. */
static void copyQuad(uint32_t output,uint32_t input)
{
    uint32_t words[4];memcpy(words,at(input),16);
#if UINTPTR_MAX > UINT32_MAX
    EE_MODEL_COPY_CPU_QUAD(2,words);
#endif
    memcpy(at(output),words,16);
}

/* LQC2 snapshots all four rows before any SQC2; VF28..31 remain observable. */
static void copyMatrix(uint32_t output,uint32_t input)
{
    uint32_t words[4];
    for(unsigned row=0;row<4;row++){
        memcpy(words,at(input+row*16u),16);EE_ROT_VU_WRITE(28+row,words);
    }
    for(unsigned row=0;row<4;row++){
        EE_ROT_VU_READ(28+row,words);memcpy(at(output+row*16u),words,16);
    }
}

/* Both native LD/SD and LDL/LDR/SDL/SDR paths make four 32-byte snapshots.
 * Later blocks see earlier stores when ranges overlap; this is not memmove. */
static void copyWorkspace(uint32_t output,uint32_t input)
{
    for(unsigned block=0;block<4;block++){
        uint64_t values[4];
        for(unsigned k=0;k<4;k++)memcpy(&values[k],at(input+k*8u),8);
        for(unsigned k=0;k<4;k++)memcpy(at(output+k*8u),&values[k],8);
        input+=32;output+=32;
    }
}

void ps2ModelCopyState(uint64_t destination,uint64_t source)
{
#if UINTPTR_MAX > UINT32_MAX
    nocturneResourceFrameEnter(32);
#endif
    uint32_t d=(uint32_t)destination,s=(uint32_t)source;
    uint32_t target=word(d+12),origin=word(s+12);
    ps2MaterialCopyListParameters(sx(target),sx(origin));
    target=word(d+16);origin=word(s+16);
#if UINTPTR_MAX > UINT32_MAX
    /* Processor transport observes the final block actually written by the
     * real memcpy. It neither supplies nor changes the game's copied bytes. */
    uint32_t observedBytes=0;
    uint32_t observedOutput=nocturneModelStateCopyOptionOutput(target,origin,&observedBytes);
#endif
    ps2ModelCopyOptionBuffer(sx(target),sx(origin));
#if UINTPTR_MAX > UINT32_MAX
    nocturneModelStateCopyObserveOption(observedOutput,observedBytes);
#endif

    uint8_t flags=byte(s+25);memcpy(at(d+25),&flags,1);
    uint16_t mask=half(s+26);uint32_t colour=word(s+28);
    sh(d+26,mask);sw(d+28,colour);
    copyMatrix(d+32,s+32);
    copyQuad(d+96,s+96);copyQuad(d+112,s+112);

    uint32_t frameByte=byte(0x551842);
    int32_t frame=frameByte&0x80u?(int32_t)frameByte-256:(int32_t)frameByte;
    uint32_t value=word(s+128),scalar=word(s+136);
    uint32_t destinationContainer=word(d);
    sw(d+128,value);sw(d+136,scalar);
    /* Source container is live after these two stores. Destination container
     * and its signed count have their distinct original cache points. */
    uint32_t sourceContainer=word(s);
    value=word(s+132);scalar=word(s+140);
    int32_t count=signedHalf(destinationContainer+4);
    sw(d+132,value);sw(d+140,scalar);
    uint32_t outputArray=word(destinationContainer+12);
    uint32_t inputArray=word(sourceContainer+12);
    uint32_t frameOffset=(uint32_t)frame<<7;

    for(int32_t index=0;index<count;index++){
        uint32_t input=word(inputArray+((uint32_t)index<<2));
        uint32_t output=word(outputArray+((uint32_t)index<<2));
        mask=half(input+20);colour=word(input+28);
        sh(output+20,mask);sw(output+28,colour);
        mask=half(input+22);sh(output+22,mask);
        copyQuad(output+80,input+80);
        copyQuad(output+96,input+96);
        copyQuad(output+112,input+112);
        copyMatrix(output+128,input+128);
        copyMatrix(output+192,input+192);
        uint32_t outputWorkspace=word(output+48);
        if(outputWorkspace){
            uint32_t inputWorkspace=word(input+48);
            copyWorkspace(outputWorkspace+frameOffset,inputWorkspace+frameOffset);
        }
    }
    /* Root+94 (the child's 1000.0f field) is deliberately not copied. */
#if UINTPTR_MAX > UINT32_MAX
    nocturneResourceFrameLeave(32);
#endif
}
