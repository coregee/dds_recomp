/* Native world/scene name lookup and event command 148. */
#include "scene_lookup.h"
#include "script_core.h"
#include "script_movie.h"
#include "script_construction.h"
#include "libc_printf.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveScriptConstructionAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t word(uint32_t address){uint32_t value;memcpy(&value,at(address),4);return value;}
static uint64_t sx(uint32_t value){return value&0x80000000u?UINT64_C(0xffffffff00000000)|value:value;}

/* 0010e588: a missing current world returns zero; inner pointers are unchecked. */
uint64_t dds3GetControlScene(void)
{
    uint32_t world=word(0x54e9c4);
    return world?sx(word(word(world+0x18)+0xc)):0;
}

/* 0010f6e0: 12-byte typed list records; object name +8, next link +20. */
uint64_t dds3SceneBasicSearchNameAndTypeExact(uint64_t scene,uint64_t type,uint64_t name)
{
    if(!scene||!name)return 0;
    uint32_t lists=word(word((uint32_t)scene+0x18)+8);
    uint32_t object=word(lists+(uint32_t)type*12+4);
    while(object){
        uint32_t candidate=word(object+8);
        if(candidate&&*at(candidate)){
            uint32_t index=0;
            for(;;){
                uint8_t query=*at((uint32_t)name+index);
                if(query!=*at(candidate+index))break;
                if(!query)return sx(object);
                ++index;
            }
        }
        object=word(object+0x20);
    }
    return 0;
}

/* 0010f790: first exact match in type order 0..17, with no HD contains pass. */
uint64_t dds3SceneBasicSearchName(uint64_t scene,uint64_t name)
{
    if(!scene||!name)return 0;
    for(uint64_t type=0;type<18;++type){
        uint64_t object=dds3SceneBasicSearchNameAndTypeExact(scene,type,name);
        if(object)return object;
    }
    return 0;
}

/* 001e6d68: both failure diagnostics reload the original string argument. */
uint64_t evtCommand_SEARCH_ID(void)
{
    uint64_t scene=dds3GetControlScene();
    uint64_t object=dds3SceneBasicSearchName(scene,scrGetStrPara(0));
    if(object)scrSetIntReturnValue(sx(word((uint32_t)object+4)));
    else{
        (void)ps2LibcPrintf(0x53ac00,scrGetStrPara(0));
        ps2ScriptDiagnosticDisabled(0x53ac20,scrGetStrPara(0));
        scrSetIntReturnValue(0);
    }
    return 1;
}

/* 001589f0: direct name argument; field failure returns signed -1. */
uint64_t fldCommand_SEARCH_ID(uint64_t name)
{
    uint64_t object=dds3SceneBasicSearchName(dds3GetControlScene(),name);
    if(object)return sx(word((uint32_t)object+4));
    (void)ps2LibcPrintf(0x5329d0,name);
    return UINT64_MAX;
}
