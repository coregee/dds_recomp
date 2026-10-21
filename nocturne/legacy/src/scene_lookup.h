#ifndef NOCTURNE_SCENE_LOOKUP_H
#define NOCTURNE_SCENE_LOOKUP_H
#include <stdint.h>
uint64_t dds3GetControlScene(void);
uint64_t dds3SceneBasicSearchNameAndTypeExact(uint64_t scene,uint64_t type,uint64_t name);
uint64_t dds3SceneBasicSearchName(uint64_t scene,uint64_t name);
uint64_t evtCommand_SEARCH_ID(void);
uint64_t fldCommand_SEARCH_ID(uint64_t name);
#endif
