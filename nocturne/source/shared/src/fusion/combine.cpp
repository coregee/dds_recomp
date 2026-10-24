// Making the fused devil (original unit: fclCombineCalcCore).
#include "nocturne/fusion/combine.hpp"

#include <cstring>

#include "nocturne/data/tables.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/accident.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/fusion/inheritance.hpp"
#include "nocturne/fusion/sort.hpp"
#include "nocturne/fusion/stock.hpp"

namespace nocturne::cmb {

using ee::Float;
using ee::literal;

namespace {

// The inheritance list as the original addresses it: index -1 (a full list)
// and 24 (not found) reach the fields on either side.
uint16_t readInheritedSlot(const UnitWork& unit, int32_t index)
{
    uint16_t value;
    std::memcpy(&value, reinterpret_cast<const uint8_t*>(&unit) + offsetof(UnitWork, inheritedSkills) + 2 * index, 2);
    return value;
}

void writeInheritedSlot(UnitWork& unit, int32_t index, uint16_t skill)
{
    std::memcpy(reinterpret_cast<uint8_t*>(&unit) + offsetof(UnitWork, inheritedSkills) + 2 * index, &skill, 2);
}

} // namespace

// ===========================================================================
// Mitama boosts
// ===========================================================================

// cmbGetPowerUpTableIndex @ 0x001FD498
int8_t mitamaBoostIndex(uint16_t mitama)
{
    for (int i = 0; i < 4; ++i)
        if (dat::kSpiritParamUpTbl[i].devil == mitama)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbCalcParamUpVal @ 0x001FD4E0
int32_t raisedMitamaBonus(int32_t stat, int32_t bonus, int32_t max, uint8_t rate)
{
    int32_t increase = rate * stat / 100 - stat;
    if (increase == 0)
        increase = 1;
    int32_t raised = bonus + increase;
    if (stat * 2 < stat + raised)
        raised = stat;
    return stat + raised <= max ? raised : max - stat;
}

// cmbCalcParamPowerUp @ 0x001FD538: each Mitama raises two stats.
bool applyMitamaBoost(uint16_t mitama, UnitWork& unit)
{
    int8_t index = mitamaBoostIndex(mitama);
    if (index < 0)
        return false;
    const SpiritParamUp& boost = dat::kSpiritParamUpTbl[index];
    for (uint16_t paramtype : boost.paramtype) {
        int8_t stat = static_cast<int8_t>(paramtype & 0xff);   // 1-based
        if (stat > 0 && stat < 7) {
            int lane = stat - 1;
            unit.mitamaparam[lane] = static_cast<int8_t>(raisedMitamaBonus(unit.param[lane], unit.mitamaparam[lane], 40, boost.uprate));
        }
    }
    return true;
}

// ===========================================================================
// Inherited skills
// ===========================================================================

// cmbAddKeisyoSkillFromSkill @ 0x001FEB28: looks at the first 8 skill slots.
// A skill already offered is marked (keiattr bit 0) as offered twice.
void addInheritableSkills(UnitWork& to, const UnitWork& from)
{
    int8_t end = inheritedEnd(to);
    int32_t added = 0;
    for (int i = 0; i < 8; ++i) {
        uint16_t skill = from.skill[i];
        if (!skill || findSkill(skill, to) >= 0 || inheritRate(to, skill) == 0)
            continue;
        int8_t offered = findInherited(skill, to);
        if (offered < 0) {
            if (end + added > 23)
                return;
            writeInheritedSlot(to, end + added, skill);
            ++added;
        } else if (!(to.keiattr[offered] & 1)) {
            to.keiattr[offered] = 1;
        }
    }
}

// cmbDeleteKeisyoSkill @ 0x001FEC40
void removeInherited(UnitWork& unit, uint8_t index)
{
    writeInheritedSlot(unit, index, 0);
    sortInheritedSkills(unit);
}

// cmbMoveKeisyoSkillToSkill @ 0x001FEC68: returns cmbAddSkill's result.
int8_t learnInherited(uint16_t skill, UnitWork& unit)
{
    int32_t index = 0;
    while (index < 24 && unit.inheritedSkills[index] != skill)
        ++index;
    uint16_t found = readInheritedSlot(unit, index);
    removeInherited(unit, static_cast<uint8_t>(index));
    return addSkill(found, unit);
}

// cmbRndGetKeisyoSkill @ 0x001FF428
uint16_t randomInheritedSkill(const UnitWork& unit)
{
    uint32_t total = static_cast<uint32_t>(totalInheritRate(unit));
    if (total == 0)
        return 0;
    int32_t roll = static_cast<int32_t>(sdf::GetRand() % total);
    int32_t cumulative = 0;
    for (int i = 0; i < 24; ++i) {
        cumulative += inheritRate(unit, unit.inheritedSkills[i]);
        if (roll < cumulative)
            return unit.inheritedSkills[i];
    }
    return 0;
}

// cmbRndAddKeisyoSkillToSkill @ 0x001FF4D0. Skill counts are summed as bytes.
void learnRandomInherited(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice,
                          UnitWork& result, InheritedSkillList* learned)
{
    int8_t sources = static_cast<int8_t>(static_cast<int8_t>(devil1.skillcnt) + static_cast<uint8_t>(devil2.skillcnt));
    if (sacrifice)
        sources = static_cast<int8_t>(static_cast<uint8_t>(sacrifice->skillcnt) + sources);
    int8_t count = static_cast<int8_t>(((Float::fromInt(sources) + literal(2.7)) / literal(3.7)).toInt());
    if (learned)
        learned->count = 0;
    if (countInherited(result) == 0)
        return;
    if (result.skillcnt + count > 8)
        count = static_cast<int8_t>(8 - static_cast<uint8_t>(result.skillcnt));
    while (count > 0) {
        uint16_t skill = randomInheritedSkill(result);
        if (skill == 0) {
            --count;
            continue;
        }
        if (learnInherited(skill, result) >= 0) {
            --count;
            if (learned)
                learned->skill[static_cast<int8_t>(learned->count++)] = skill;
        }
    }
}

// ===========================================================================
// Fusion
// ===========================================================================

// cmbCalcIkenieExp @ 0x001FE880. The result's EXP also gains the EXP for its
// current level, and the stat gains don't advance the level-up counters
// (mode 1); a miss (6) raises the byte after the stats.
void addSacrificeExp(UnitWork& result, const UnitWork&, const UnitWork&, const UnitWork& sacrifice)
{
    // Unsigned EXP to float, as the compiler does it, then scaled (x1.5 in US Maniax).
    uint32_t exp = static_cast<uint32_t>(sacrifice.exp);
    Float value;
    if (exp >> 31) {
        Float half = Float::fromInt(static_cast<int32_t>((exp >> 1) | (exp & 1)));
        value = half + half;
    } else {
        value = Float::fromInt(static_cast<int32_t>(exp));
    }
    value = value * sacrificeExpScale() + Float(0.0f);
    const Float kTwo31 = Float(2147483648.0f);
    uint32_t bonus = kTwo31 <= value ? static_cast<uint32_t>((value - kTwo31).toInt()) | 0x80000000u
                                     : static_cast<uint32_t>(value.toInt());

    result.exp = static_cast<int32_t>(static_cast<uint32_t>(result.exp) + expForLevel(result, result.level));
    int32_t gained = levelUpCount(result, static_cast<int32_t>(bonus));
    int32_t level = result.level + gained;
    result.exp = static_cast<int32_t>(static_cast<uint32_t>(result.exp) + bonus);
    if (level >= 256) {
        gained = 255 - result.level;
        level = result.level + gained;
    }
    result.level = static_cast<uint16_t>(level);
    while (gained-- > 0) {
        int8_t lane = rollLevelUpStat(result, 1);
        if (lane >= 0)
            reinterpret_cast<uint8_t*>(result.param)[lane] += 1;   // lane 6: skillparam[0]
    }
    result.flag |= 0x200;
    if (result.level == 255)
        result.exp = static_cast<int32_t>(expForLevel(result, 255));
}

// cmbGetStockDevilInfo @ 0x001FE170
void stockDevilInfo(const UnitWork& unit, uint16_t* id, uint8_t* race)
{
    *id = unit.id;
    *race = static_cast<uint8_t>(dat::devilFormat(unit.id).race);
}

// cmbGetBirthDevil @ 0x001FF790
FusionType fuse(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice, UnitWork* result,
                bool cursed, bool unitLevels, bool accidents, InheritedSkillList* learned)
{
    bool cursedResult = (devil2.flag & 0x1000) || (devil1.flag & 0x1000) || (sacrifice && (sacrifice->flag & 0x1000));
    UnitWork birth{};   // the original leaves all but the ID uninitialised
    birth.id = 0;

    auto fail = [result] {
        if (result)
            result->id = 0;
        return FusionType::None;
    };
    if (involvesDante(devil1, devil2, sacrifice) || devil1.id == devil2.id)
        return fail();
    if (sacrifice && (devil1.id == sacrifice->id || devil2.id == sacrifice->id))
        return fail();

    // ids / races: the higher-level devil first, then the sacrifice.
    uint16_t ids[3];
    uint8_t races[3];
    if (devil2.level < devil1.level) {
        stockDevilInfo(devil1, &ids[0], &races[0]);
        stockDevilInfo(devil2, &ids[1], &races[1]);
    } else {
        stockDevilInfo(devil1, &ids[1], &races[1]);
        stockDevilInfo(devil2, &ids[0], &races[0]);
    }
    if (sacrifice)
        stockDevilInfo(*sacrifice, &ids[2], &races[2]);
    else
        ids[2] = 0;

    uint16_t devil;
    FusionType type;
    if (ids[2] == 0) {
        devil = twoDevilFusion(devil1, devil2, cursed, unitLevels, ids, races, &type);
    } else {
        type = FusionType::SacrificeSpecial;
        devil = sacrificeDevilPattern(devil1, devil2, *sacrifice, cursed, unitLevels);
        if (devil == 0)
            devil = sacrificeDevilRacePattern(ids[0], ids[1], ids[2]);
        if (devil == 0) {
            uint8_t race = sacrificeRacePattern(ids[0], ids[1], ids[2]);
            if (race == 0) {
                devil = sacrificeFusion(devil1, devil2, *sacrifice, cursed, unitLevels, ids, races);
                type = FusionType::Sacrifice;
            } else {
                uint8_t level = static_cast<uint8_t>(averageLevel(devil1, devil2, sacrifice, unitLevels));
                devil = targetDevil(race, level);
            }
        }
    }

    // With a Deathstone, normal fusions of the right races make a Fiend
    // instead (but a Fiend can't be fused into one).
    if (type == FusionType::Normal || type == FusionType::Sacrifice) {
        if (uint16_t fiend = fiendFusion(devil)) {
            constexpr uint8_t kFiend = static_cast<uint8_t>(Race::Fiend);
            if (races[0] == kFiend || races[1] == kFiend) {
                type = FusionType::None;
                devil = 0;
            } else {
                type = FusionType::Fiend;
                devil = fiend;
            }
        }
    }

    // Accidents: not for special pairs, patterns, Mitama boosts or Fiends.
    int8_t accident = 0;
    switch (type) {
    case FusionType::Normal:
    case FusionType::Mitama:
    case FusionType::Element:
    case FusionType::RankUp:
    case FusionType::RankDown:
    case FusionType::Sacrifice:
        if (accidents && rollAccident()) {
            accident = static_cast<int8_t>(rollAccidentType() + 1);
            diag::print(diag::Message::FusionAccident, accident - 1);
        }
        break;
    default:
        break;
    }
    if (accident == 1) {
        devil = randomAccidentDevil(devil);
        type = FusionType::Accident;
    }

    if (devil != 0) {
        if (type == FusionType::MitamaBoost) {
            // The devil keeps everything; the Mitama's skills are offered.
            const UnitWork& kept = devil1.id == devil ? devil1 : devil2;
            const UnitWork& mitama = devil1.id == devil ? devil2 : devil1;
            copyCustomDevil(birth, kept);
            clearInherited(birth);
            addInheritableSkills(birth, mitama);
            applyMitamaBoost(mitama.id, birth);
        } else {
            copyDefaultDevil(devil, birth);
            addInheritableSkills(birth, devil1);
            addInheritableSkills(birth, devil2);
        }
        if (!sacrifice) {
            learnRandomInherited(devil1, devil2, nullptr, birth, learned);
        } else {
            if (accident != 1)
                addSacrificeExp(birth, devil1, devil2, *sacrifice);
            addInheritableSkills(birth, *sacrifice);
            learnRandomInherited(devil1, devil2, sacrifice, birth, learned);
        }
    }
    if (accident == 2) {
        boostAccidentDevil(birth);
        type = FusionType::AccidentBoost;
    }

    if (result) {
        copyCustomDevil(*result, birth);
        result->hp = result->maxhp;
        result->mp = result->maxmp;
        if (cursedResult)
            result->flag |= 0x1000;
    }
    return devil == 0 ? FusionType::None : type;
}

} // namespace nocturne::cmb
