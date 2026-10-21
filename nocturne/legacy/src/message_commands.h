#ifndef NOCTURNE_MESSAGE_COMMANDS_H
#define NOCTURNE_MESSAGE_COMMANDS_H
#include <stdint.h>
uint64_t itfMesMngOpenWindow(void);
uint64_t itfMesMngCloseWindow(void);
void itfMesMngMsgWndCls(uint64_t id);
void itfMesMngMarkBitStat(uint64_t id,uint64_t flag);
void ps2MessageOptionHook(uint64_t option);
uint64_t ps2MessageGetResourceEntry(uint64_t instance,uint64_t index);
uint64_t GetMessagePagePtr(uint64_t resource,uint64_t page);
void CommitVarTable(uint64_t table);
void frSetVariableRequest(uint64_t index,uint64_t value);
uint64_t ps2FontTestGlobalFlags(uint64_t mask);
uint64_t itfMesMngGetVarLocalize(uint64_t id,uint64_t index);
uint64_t GetSpeakerName(uint64_t instance);
uint64_t GetLastLinkFontHandle(uint64_t font);
void GetLastMessagePara(uint64_t font,uint64_t message);
void ChangeZBuffer(uint64_t font,uint64_t z);
void frSetDrawPosition(uint64_t font,uint64_t x,uint64_t y);
void frSetDrawSpeed(uint64_t font,uint64_t speed);
void RaiseMessageSpeedMax(uint64_t font);
#endif
