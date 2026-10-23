// The FlowScript commands on the save game: items, Magatama, Macca, the
// party and stock, the Demi-fiend's stats, boss refights (original unit:
// scrParameterCommand).
#include "nocturne/data/field_skill.hpp"
#include "nocturne/data/magatama.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/script/commands.hpp"
#include "nocturne/script/vm.hpp"

namespace nocturne::scr {

namespace {

int32_t para(int32_t index) { return scrGetIntPara(index); }

int32_t answer(bool value)
{
    scrSetIntReturnValue(value ? 1 : 0);
    return 1;
}

int32_t answerInt(int32_t value)
{
    scrSetIntReturnValue(value);
    return 1;
}

Param stat(int32_t index) { return static_cast<Param>(index); }

// A demon in units 1..15 matching `match`, or null.
template <class Match> UnitWork* findCompanion(Match match)
{
    for (int i = 1; i < 16; ++i) {
        UnitWork& unit = dat::globalWork().units[i];
        if ((unit.flag & UnitFlag::Valid) && match(unit))
            return &unit;
    }
    return nullptr;
}

} // namespace

// prm_ITEM_PLUS @ 0x0010CF38: ITEM_PLUS(item, count)
int32_t prm_ITEM_PLUS()
{
    const int32_t item = para(0);
    dat::addItem(item, para(1));
    return 1;
}

// prm_DH_PLUS @ 0x0010CF78: DH_PLUS(Magatama), one more Magatama ("DH": devil hearts).
int32_t prm_DH_PLUS()
{
    magatama::add(para(0));
    return 1;
}

// prm_DH_EQUIP @ 0x0010CFA0: DH_EQUIP(Magatama), 0 to remove it.
int32_t prm_DH_EQUIP()
{
    const int32_t id = para(0);
    if (id == 0)
        dat::removeMagatama();
    else
        dat::equipMagatama(static_cast<uint8_t>(id));
    return 1;
}

// prm_MAKA_PLUS @ 0x0010CFE0: MAKA_PLUS(Macca)
int32_t prm_MAKA_PLUS()
{
    dat::addMacca(para(0));
    return 1;
}

// prm_MAKA_PLUS_PER @ 0x0010D008: MAKA_PLUS_PER(percent)
int32_t prm_MAKA_PLUS_PER()
{
    dat::addMaccaPercent(para(0));
    return 1;
}

// prm_MAKA_CHECK @ 0x0010D030: MAKA_CHECK(Macca), whether there is that much.
int32_t prm_MAKA_CHECK() { return answer(dat::hasMacca(para(0))); }

// prm_PARTY_DAMAGE @ 0x0010D078: PARTY_DAMAGE(mode), see dat::partyDamage.
int32_t prm_PARTY_DAMAGE()
{
    dat::partyDamage(para(0));
    return 1;
}

// prm_PARTY_KAIFUKU @ 0x0010D0A0: the whole stock healed, with the healing sound.
int32_t prm_PARTY_KAIFUKU()
{
    dat::partyRecover();
    snd::Play(0x10, 0x7f, 0x3f);
    return 1;
}

// prm_PARTY_KAIFUKU2 @ 0x0010D0D0: the same, silently.
int32_t prm_PARTY_KAIFUKU2()
{
    dat::partyRecover();
    return 1;
}

// prm_DV_PLUS @ 0x0010D0F0: DV_PLUS(devil, join, unique ID)
// A demon joins unless one of its kind is already there (join: 1 into the
// party, 2 into the party without a compendium entry); with a unique ID it
// joins regardless, as a story demon.
int32_t prm_DV_PLUS()
{
    const int32_t uniqueId = para(2);
    const int32_t join = para(1);
    if (uniqueId != 0) {
        dat::addUniqueDevil(para(0), join != 0, uniqueId);
        return 1;
    }
    const int32_t devil = para(0);
    if (dat::findDevil(devil) != -1)
        return 1;
    if (join == 2)
        dat::addDevil(static_cast<int32_t>(static_cast<uint32_t>(devil) | 0x80000000u), true);
    else
        dat::addDevil(devil, join != 0);
    return 1;
}

// prm_DV_CHECK @ 0x0010D1A0: DV_CHECK(devil), whether one is in the stock.
int32_t prm_DV_CHECK() { return answer(dat::findDevil(para(0)) != -1); }

// prm_UDV_LEAVE @ 0x0010D1F0: UDV_LEAVE(unique ID), the story demon leaves.
int32_t prm_UDV_LEAVE()
{
    const int32_t index = dat::findUniqueDevil(para(0));
    if (index != -1)
        dat::removeDevil(dat::globalWork().units[index].id);
    return 1;
}

// prm_UDV_CHECK @ 0x0010D248
int32_t prm_UDV_CHECK() { return answer(dat::findUniqueDevil(para(0)) != -1); }

// prm_UDV_GETID @ 0x0010D298: its devil ID (it may have evolved), or -1.
int32_t prm_UDV_GETID() { return answerInt(dat::uniqueDevilId(para(0))); }

// prm_UDV_DELETE_OK @ 0x0010D2C8 / prm_UDV_DELETE_NG @ 0x0010D330: whether
// the story demon can be dismissed.
int32_t prm_UDV_DELETE_OK()
{
    const int32_t index = dat::findUniqueDevil(para(0));
    if (index != -1)
        dat::globalWork().units[index].flag &= ~UnitFlag::KeepInStock;
    return 1;
}

// prm_UDV_DELETE_NG @ 0x0010D330
int32_t prm_UDV_DELETE_NG()
{
    const int32_t index = dat::findUniqueDevil(para(0));
    if (index != -1)
        dat::globalWork().units[index].flag |= UnitFlag::KeepInStock;
    return 1;
}

// prm_STOCK_PLUS @ 0x0010D390: STOCK_PLUS(n), a bigger stock (at most 12).
int32_t prm_STOCK_PLUS()
{
    int32_t& capacity = dat::globalWork().stock_capacity;
    const int32_t grown = capacity + para(0);
    capacity = grown > 12 ? 12 : grown;
    return 1;
}

// prm_STOCK_FULL_CHECK @ 0x0010D3D0
int32_t prm_STOCK_FULL_CHECK() { return answer(dat::isStockFull()); }

// prm_PLAYER_GET_PARAM @ 0x0010D410: PLAYER_GET_PARAM(stat)
int32_t prm_PLAYER_GET_PARAM() { return answerInt(dat::playerParam(stat(para(0)))); }

// prm_PLAYER_ADD_PARAM @ 0x0010D440: PLAYER_ADD_PARAM(stat, amount)
int32_t prm_PLAYER_ADD_PARAM()
{
    const int32_t index = para(0);
    dat::addPlayerParam(stat(index), para(1));
    return 1;
}

// prm_NAKAMA_GET_PARAM @ 0x0010D480: NAKAMA_GET_PARAM(devil, stat)
int32_t prm_NAKAMA_GET_PARAM()
{
    const int32_t devil = para(0);
    return answerInt(dat::companionParam(static_cast<uint16_t>(devil), stat(para(1))));
}

// prm_PLAYER_GET_LND @ 0x0010D4C8: the Demi-fiend's alignment.
int32_t prm_PLAYER_GET_LND() { return answerInt(dat::playerAlignment()); }

// prm_PLAYER_GET_LEVEL @ 0x0010D4F0
int32_t prm_PLAYER_GET_LEVEL() { return answerInt(dat::playerLevel()); }

// prm_NAKAMA_DEAD @ 0x0010D518: NAKAMA_DEAD(devil), it dies and leaves the party.
int32_t prm_NAKAMA_DEAD()
{
    dat::killCompanion(static_cast<uint16_t>(para(0)));
    return 1;
}

// prm_NAKAMA_CHK_PIKUKO @ 0x0010D540: NAKAMA_CHK_PIKUKO(devil), whether the
// first Pixie is in the stock as that species.
int32_t prm_NAKAMA_CHK_PIKUKO()
{
    return answer(findCompanion([](const UnitWork& unit) {
                      return unit.id == para(0) && (unit.flag & UnitFlag::Pixie);
                  }) != nullptr);
}

// prm_PIKUKO_GETID @ 0x0010D5E8: the first Pixie's devil ID now, or 0.
int32_t prm_PIKUKO_GETID()
{
    const UnitWork* pixie = findCompanion([](const UnitWork& unit) { return (unit.flag & UnitFlag::Pixie) != 0; });
    return answerInt(pixie ? pixie->id : 0);
}

// prm_BOSS_PRESS_REC @ 0x0010D658: BOSS_PRESS_REC(encounter, type), see dat::bossPressRecord.
int32_t prm_BOSS_PRESS_REC()
{
    const int32_t encounter = para(0);
    return answerInt(dat::bossPressRecord(encounter, para(1)));
}

// prm_DV_COPY_PARAM @ 0x0010D6A0: DV_COPY_PARAM(devil, as), the stock's first
// demon of that species reset to another's level, stats and skills.
int32_t prm_DV_COPY_PARAM()
{
    const int32_t devil = para(0);
    const int32_t as = para(1);
    if (UnitWork* unit = findCompanion([&](const UnitWork& u) { return u.id == devil; }))
        dat::resetToSpecies(static_cast<uint16_t>(as), *unit);
    return 1;
}

} // namespace nocturne::scr
