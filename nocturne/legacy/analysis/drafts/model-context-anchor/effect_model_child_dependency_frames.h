#ifndef NOCTURNE_EFFECT_MODEL_CHILD_DEPENDENCY_FRAMES_H
#define NOCTURNE_EFFECT_MODEL_CHILD_DEPENDENCY_FRAMES_H
#include <stdint.h>
uint64_t ps2EffectModelMake_002B1588(uint64_t textures,uint64_t definition);
uint64_t ps2EffectModelMakeRoot_002B1498(uint64_t textures,uint64_t definition);
void ps2EffectModelNodeSetCommands_002B1260(uint64_t node,uint64_t item);
void ps2EffectModelCopyState_002B2268(uint64_t destination,uint64_t source);
void ps2EffectModelCopyOptionBuffer_002B2238(uint64_t destination,uint64_t source);
void ps2EffectMaterialCopyListParameters_002B3AB0(uint64_t destination,uint64_t source);
void ps2EffectMaterialCopyParameters_002B39A0(uint64_t destination,uint64_t source);
uint64_t ps2EffectMaterialGetFiveWords38_002B2F48(uint64_t material);
uint64_t ps2EffectMaterialGetFiveWords3C_002B30B0(uint64_t material);
uint64_t ps2EffectMaterialCreateFiveWords_002B2F08(void);
uint64_t ps2EffectModelMeasureCommandList_002B0A00(uint64_t list,uint64_t count,uint64_t quadwords);
void ps2EffectModelBuildCommandList_002B0F78(uint64_t node,uint64_t list,uint64_t selector,uint64_t alternate,uint64_t pass);
uint64_t ps2EffectModelEnsureWorkspace_002B0438(uint64_t node);
uint64_t ps2EffectModelPrependCommandNode_002B0F08(uint64_t node,uint64_t selector,uint64_t pass);
uint64_t ps2EffectModelWriteReturnPacket_002B09B8(uint64_t packet);
uint64_t ps2EffectModelRootNew_002B0540(void);
uint64_t ps2EffectModelNodeNew_002B03B0(void);
void ps2EffectModelAllocNodeList_002B06D0(uint64_t root,uint64_t count);
void ps2EffectModelNodeAdd_002B0758(uint64_t root,uint64_t parent,uint64_t node);
void ps2EffectModelMakeMorphList_002B1410(uint64_t root,uint64_t count);
void ps2EffectModelNodeBaseSet_002B11D0(uint64_t node,uint64_t definition);
uint64_t ps2EffectArrayCreate_002BFE58(uint64_t capacity,uint64_t stride,uint64_t growth);
void ps2EffectArrayResize_002BFF98(uint64_t array,uint64_t capacity);
void ps2EffectArrayGrow_002BFF18(uint64_t array);
void ps2EffectModelMakeLocalTm_002B1180(uint64_t node);
void ps2EffectQuatFromEuler_002C0788(float x,float y,float z);
void ps2EffectModelNodeSetParent_002B0850(uint64_t node,uint64_t parent);
void ps2EffectModelNodeUnlink_002B07E8(uint64_t node);
void ps2EffectPoolAdvancePageList_002A89C0(uint64_t pool);
uint64_t ps2EffectPoolAllocateFreedSlot_002A89E0(uint64_t pool,uint64_t page);
uint64_t ps2EffectPoolAllocateBumpSlot_002A8A30(uint64_t pool,uint64_t page);
uint64_t ps2EffectPoolTakePage_002A8AB0(uint64_t pool);
uint64_t ps2EffectPoolAllocate_002A8AF8(uint64_t bytes);
uint64_t ps2EffectPoolAllocateZeroed_002A8BA8(uint64_t bytes);
uint64_t ps2EffectZeroQuadwords_002BFCE8(uint64_t address,uint64_t count);
uint64_t ps2EffectMaterialListMake_002B38A0(uint64_t textures,uint64_t definitions);
uint64_t ps2EffectMaterialListCreate_002B2D28(uint64_t capacity);
#endif
