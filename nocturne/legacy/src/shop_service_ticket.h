#ifndef NOCTURNE_SHOP_SERVICE_TICKET_H
#define NOCTURNE_SHOP_SERVICE_TICKET_H
#include <stdint.h>
void *nocturneResolveShopServiceTicketAddress(uint32_t address);
uint64_t ps2ShopTicketAdjust_002088D0(uint64_t amount);
uint64_t ps2ShopTicketDraw_002088F8(uint64_t box);
void ps2ShopTicketExit_00208A40(void);
void ps2ShopTicketPrizeStart_00209500(void);
void ps2ShopTicketOffer_00209548(void);
void ps2ShopTicketCountUpdate_00209680(void);
void ps2ShopTicketAwardUpdate_002096D8(void);
uint64_t ps2ShopFacilityByteRead_002143F8(uint64_t index);
#endif
