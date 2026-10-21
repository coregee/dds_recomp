#include "nocturne.h"

/* PS2 0x00245e60. Table and work records are separate arrays. */
int32_t datBossRashGetRec(int32_t eid, int32_t type)
{
    for (int32_t i = 0; i < 40; ++i) {
        const datBossRashEntry_PS2 *entry = &g_datBossRashTable[i];
        if (entry->enemy_id != eid) continue;
        if (type == 0) {
            int32_t best = g_datGlobalWork->boss_records[i][0];
            return best > 0 ? best : 999;
        }
        if (type != 1) return entry->initial_press;
        if (evtBitCheck(entry->available_bit)) {
            int32_t last = g_datGlobalWork->boss_records[i][1];
            return last == 0 ? 1 : last;
        }
    }
    return 0;
}

/* PS2 0x00245f68. Signed 16-bit record writes are a PS2-specific detail. */
void datBossRashUpdRec(int32_t eid, int32_t press)
{
    if (eid == 0x3e1) eid = 0x1d8;
    if (eid == 0x3e0) eid = 0x14e;
    if (press == 0) press = 1;
    for (int32_t i = 0; i < 40; ++i) {
        const datBossRashEntry_PS2 *entry = &g_datBossRashTable[i];
        if (entry->enemy_id != eid) continue;
        if (!evtBitCheck(entry->available_bit)) return;
        g_datGlobalWork->boss_records[i][1] = (int16_t)press;
        if (datBossRashGetRec(eid, 0) > press) {
            g_datGlobalWork->boss_records[i][0] = (int16_t)press;
            evtBitOn(entry->record_bit);
        }
        return;
    }
}

/* PS2 0x00246038. */
int32_t datBossRashChk(int32_t eid)
{
    for (int32_t i = 0; i < 40; ++i)
        if (g_datBossRashTable[i].enemy_id == eid &&
            evtBitCheck(g_datBossRashTable[i].available_bit)) return 1;
    return 0;
}
