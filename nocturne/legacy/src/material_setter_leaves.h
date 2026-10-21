#ifndef NOCTURNE_MATERIAL_SETTER_LEAVES_H
#define NOCTURNE_MATERIAL_SETTER_LEAVES_H
#include <stdint.h>
/* Descriptive PS2 aliases; stable aligned backed ordinary RAM through+0x37.
 * Preserve old flags load before raw32 store and return-delay byte write. */
void ps2MatSetWord28(void *material,uint32_t value);
void ps2MatSetWord2C(void *material,uint32_t value);
void ps2MatSetWord18(void *material,uint32_t value);
void ps2MatSetWord34(void *material,uint32_t value);
void ps2MatSetWord30(void *material,uint32_t value);
#endif
