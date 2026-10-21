#include <stdint.h>
#include <string.h>
#include "material_setter_leaves.h"
/* 002B2EC0: no direct native identity established. */
void ps2MatSetWord28(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];memcpy(p+0x28,&value,4);p[6]=(uint8_t)(flags|0x3); }
/* 002B2EF0: no direct native identity established. */
void ps2MatSetWord2C(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];memcpy(p+0x2c,&value,4);p[6]=(uint8_t)(flags|0x3); }
/* 002B3068: no direct native identity established. */
void ps2MatSetWord18(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];memcpy(p+0x18,&value,4);p[6]=(uint8_t)(flags|0x30); }
/* 002B3080: no direct native identity established. */
void ps2MatSetWord34(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];memcpy(p+0x34,&value,4);p[6]=(uint8_t)(flags|0x30); }
/* 002B3098: no direct native identity established. */
void ps2MatSetWord30(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];memcpy(p+0x30,&value,4);p[6]=(uint8_t)(flags|0x30); }
