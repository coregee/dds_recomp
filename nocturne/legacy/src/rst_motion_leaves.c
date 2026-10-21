#include "rst_motion_leaves.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
extern datUnitWork_PS2 *nocturneResolveRstUnitAddress(uint32_t address);
#endif

/* 0021FD40: chosen PS2 alias. Signed byte1 is busy; byte2 is consumed to0.
 * Negative and other values return0 without altering the state. */
int32_t ps2RstConsumeBusyState(void)
{
    if(g_ps2RstBusyState==1u) return 1;
    if(g_ps2RstBusyState==2u) g_ps2RstBusyState=0;
    return 0;
}
/* 0021FD78: chosen PS2 alias. Original54FCE8 nullable pointer; byte0 OR10. */
void ps2RstMarkObjectFlag(void)
{
    if(g_ps2RstFlagObject!=NULL) *g_ps2RstFlagObject|=0x10u;
}
/* 0021FE30 ->182281B70. Original A0,A1 bytes; raw F12/F13 stores.
 * Native extra gift-control reset is absent from this original body. */
void rstSetMotionReq(int8_t number,float before_frame,float after_frame,int8_t mode)
{
    g_rstMotionWork->motion_number=number;
    g_rstMotionWork->motion_mode=mode;
    memcpy(&g_rstMotionWork->before_frame,&before_frame,sizeof before_frame);
    memcpy(&g_rstMotionWork->after_frame,&after_frame,sizeof after_frame);
}
/* 0021FF38 ->18227F820: only byte22E6=2; every other byte is retained. */
void rstCancelMotionReq(void)
{
    g_rstMotionWork->motion_mode=2;
}
/* 0021FF48 ->182281A80: signed type, unsigned ushortID, original21-byte row;
 * signed motion and unsigned frame bytes, then the actual motion setter. */
void rstSetMotionReqFromTbl(int8_t type)
{
    const datUnitWork_PS2 *unit;
#if UINTPTR_MAX > UINT32_MAX
    unit=nocturneResolveRstUnitAddress(g_rstMotionWork->unit_address);
#else
    unit=(const datUnitWork_PS2 *)(uintptr_t)g_rstMotionWork->unit_address;
#endif
    int32_t offset=((int32_t)unit->id*7+(int32_t)type)*3;
    const uint8_t *record=g_rstMotionTable+offset;
    uint8_t raw_number=record[0];
    int8_t number=raw_number<128u ? (int8_t)raw_number : (int8_t)((int32_t)raw_number-256);
    /* All byte values0..255 convert exactly to single precision; no rounding
     * or extended-encoding difference can arise in these two conversions. */
    rstSetMotionReq(number,(float)record[1],(float)record[2],0);
}
