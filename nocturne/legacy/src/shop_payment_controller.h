#ifndef NOCTURNE_SHOP_PAYMENT_CONTROLLER_H
#define NOCTURNE_SHOP_PAYMENT_CONTROLLER_H
#include <stdint.h>
void *nocturneResolveShopPaymentAddress(uint32_t address);
uint64_t ps2ShopProcessStatus_00101858(uint64_t process);
uint64_t ps2ShopConfirmPayment_002091E8(uint64_t mode);
void ps2ShopPaymentUpdate_002092E8(void);
void ps2ShopScriptForcedEnd_00213B08(uint64_t process);
uint64_t ps2ShopScriptStart_00213B48(uint64_t data,uint64_t start,uint64_t slot);
void ps2ShopSignalClear_00214398(uint64_t index);
uint64_t ps2ShopSignalCheck_002143B0(uint64_t index);
uint64_t ps2ShopSignalCommand_00214428(void);
void ps2ShopSequenceInitialize_002427D8(uint64_t sequence,uint64_t parent);
uint64_t ps2ShopSequenceStatus_002427F8(uint64_t sequence);
#endif
