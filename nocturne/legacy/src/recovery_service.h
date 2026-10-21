#ifndef NOCTURNE_RECOVERY_SERVICE_H
#define NOCTURNE_RECOVERY_SERVICE_H
#include <stdint.h>
/* SLUS_209.11 guest-pointer/raw-slot interfaces. Every body defines V0,
 * including application methods described as void by the HD reference.
 * Results retain the original low32-to-low64 sign extension. */
uint64_t ps2RecoveryServicePriceRecover_0020DBF0(uint64_t unit);
uint64_t ps2RecoveryServicePriceStatusRecover_0020DCC0(uint64_t unit);
uint64_t ps2RecoveryServicePriceRevive_0020DCE8(uint64_t unit);
uint64_t ps2RecoveryServicePriceDispel_0020DD00(void);
uint64_t ps2RecoveryServicePriceAllRecover_0020DD08(uint64_t unit);
uint64_t ps2RecoveryServicePrice_0020DD50(uint64_t unit,uint64_t flag);
uint64_t ps2RecoveryServiceAppRecover_0020DDD8(uint64_t unit);
uint64_t ps2RecoveryServiceAppStatusRecover_0020DE10(uint64_t unit);
uint64_t ps2RecoveryServiceAppRevive_0020DE20(uint64_t unit);
uint64_t ps2RecoveryServiceAppDispel_0020DE70(uint64_t unit);
uint64_t ps2RecoveryServiceAppAllRecover_0020DE80(uint64_t unit);
uint64_t ps2RecoveryServiceGetDevilAttr_0020DEB0(uint64_t unit);
/* Host address binding only: resolves the same actual RAM used by the real
 * datGetMaxHp/Mp callees. It supplies no game-function result. */
void *nocturneResolveRecoveryServiceAddress(uint32_t address);
#endif
