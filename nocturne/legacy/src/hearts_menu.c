/* Future-skill lists and Magatama menu initialization, SLUS_209.11.
 * PS2 table bytes and caller contracts are documented in hearts_menu.h. */
#include "hearts_menu.h"

/* Explicit two's-complement low-byte conversion avoids depending on an
 * out-of-range unsigned-to-signed conversion for the original SB count wrap. */
static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128 ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

static void append_future_skill(rstSkillInfo_PS2 *info, int8_t level, uint16_t skill)
{
    int32_t index = info->skillcnt;
    info->target_level[index] = (uint8_t)level;
    info->skillcnt = signed_byte((uint32_t)(uint8_t)info->skillcnt + 1);
    info->skill[index] = skill;
}

/* 00221ef8: signed8 ID, LBU descriptor flag, mask7. No zero-ID shortcut. */
uint8_t cmbChkHeartsStat(int8_t id)
{
    return (uint8_t)(g_cmbHeartsRecords[id].flag & UINT8_C(7));
}

/* 00220508: only count and appended array slots are written. Player path
 * lists future unowned skills without a level test; demon path requires a
 * future level and event type1/6, with no explicit zero-skill exclusion.
 * The original level-offset argument is signed8; HD widens it to signed16. */
void rstCreateBeforeSkillList(int8_t id, datUnitWork_PS2 *unit,
    int8_t level_offset, rstSkillInfo_PS2 *info)
{
    if (unit == NULL) return;
    info->skillcnt = 0;
    if (unit->id == 0) {
        if (id == 0) return;
        for (int32_t i = cmbGetHeartsAfterSkillNums((uint8_t)id); i < 8; ++i) {
            const cmbHeartsSkillEntry_PS2 *entry = &g_cmbHeartsRecords[id].skills[i];
            if (entry->skill != 0 && cmbChkSkillOwner(entry->skill, unit) < 0)
                append_future_skill(info, entry->level, entry->skill);
        }
    } else {
        const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[unit->id];
        for (uint32_t i = 0; i < 24; ++i) {
            const cmbDemonSkillEntry_PS2 *entry = &row->entries[i];
            if (entry->type == (unit->hensinmae == 0 ? 1 : 6)
                && (int32_t)unit->level + (int32_t)level_offset < (int32_t)entry->level
                && cmbChkSkillOwner(entry->skill, unit) < 0)
                append_future_skill(info, entry->level, entry->skill);
        }
    }
}

/* 00232920: getter called twice per index; first matching physical row wins.
 * Equipped global byte is unsigned; position table IDs are signed bytes. */
void cmpSetEquipHeartsSelectPos(cmpDataDH_PS2 *data)
{
    for (uint32_t i = 0; i < 27; ++i) {
        int8_t index = (int8_t)i;
        (void)cmpGetHeartsFromPos(index);
        int8_t id = cmpGetHeartsFromPos(index);
        if ((int32_t)id == (int32_t)g_datGlobalWork->hearts_equipped) {
            data->select_pos = index;
            return;
        }
    }
    data->select_pos = 0;
}

/* 00232cc8:25 inline icons at menu+1278, stride34. Preserve both padding
 * regions and all other menu bytes. Each icon consumes two default RNG draws,
 * including unowned icons, yielding50 draws in total. */
void cmpInitHeartsIcon(cmpDataDH_PS2 *data)
{
    datUnitWork_PS2 *player = &g_datGlobalWork->units[0];
    rstSkillInfo_PS2 info;
    for (uint32_t i = 0; i < 25; ++i) {
        int8_t index = (int8_t)i;
        int8_t id = cmpGetHeartsFromPos(index);
        int8_t type = -1;
        uint32_t color = 0;
        int8_t move_type = 0;
        if (cmpChkHaveHearts(id) != 0) {
            type = cmpGetHeartsIconTypeFromPos(index);
            color = cmpGetHeartsIconColorFromPos(index);
            rstCreateBeforeSkillList(id, player, 0, &info);
            if (info.skillcnt != 0) {
                uint32_t level = player->level;
                uint32_t target = info.target_level[0];
                if (target <= level + 1) move_type = 2;
                else if (target <= level + 4) move_type = 1;
                if (info.skillcnt == 1 && id == 1 && evtBitCheck(0x8c1) == 0)
                    move_type = 0;
            }
        }
        cmpHeartsIcon_PS2 *icon = &data->hearts_icon[i];
        icon->icon_type = type;
        icon->stat = 0;
        icon->icon_color = color;
        icon->move_type = move_type;
        icon->axis = 0;
        icon->axis_chg = -1;
        icon->wait1st = (int32_t)(sdfGetRand(NULL) & UINT32_C(31));
        uint32_t second_draw = sdfGetRand(NULL);
        /* Store order after the second draw follows the original cursors. */
        icon->angle = 0.0f;
        icon->wait = (int32_t)(second_draw & UINT32_C(31));
        icon->def_cnt = 0;
        icon->def_ang = 0.0f;
        icon->cnt = 0;
        icon->timer = 0;
        icon->timer_spd = 6;
        icon->dist_ang = 0.0f;
    }
}
