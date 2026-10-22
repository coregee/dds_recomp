// Compile-time check that tools/ghidra/nocturne_types.h (the types imported
// into Ghidra) matches the C++ records.
#include <cstddef>
#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/fusion/combine.hpp"
#include "nocturne/fusion/sort.hpp"
#include "nocturne/interface/font.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/kernel/quake.hpp"
#include "nocturne/script/vm.hpp"

namespace ghidra {
#define PTR32(T) uint32_t
#include "nocturne_types.h"
} // namespace ghidra

namespace {

using namespace nocturne;

#define SAME_SIZE(G, R) static_assert(sizeof(ghidra::G) == sizeof(R), #G " size differs from " #R)
#define SAME_OFFSET(G, R, gf, rf) static_assert(offsetof(ghidra::G, gf) == offsetof(R, rf), #G "." #gf " offset differs")

SAME_SIZE(datUnitWork, UnitWork);
SAME_OFFSET(datUnitWork, UnitWork, badstat, badstat);
SAME_OFFSET(datUnitWork, UnitWork, mitamaparam, mitamaparam);
SAME_OFFSET(datUnitWork, UnitWork, hensinmaeexp, hensinmaeexp);
SAME_SIZE(datNormalSkill, NormalSkill);
SAME_OFFSET(datNormalSkill, NormalSkill, program, program);
SAME_OFFSET(datNormalSkill, NormalSkill, magiclimit, magiclimit);
SAME_SIZE(datSpecialSkill, SpecialSkill);
SAME_SIZE(datDevilFormat, DevilFormat);
SAME_OFFSET(datDevilFormat, DevilFormat, specialbit, specialbit);
SAME_OFFSET(datDevilFormat, DevilFormat, reserve1, reserve1);
SAME_SIZE(datEncount, Encount);
SAME_OFFSET(datEncount, Encount, btlsound, btlsound);
SAME_SIZE(datEncountRitu, EncountRitu);
SAME_SIZE(datEncountTbl, EncountTbl);
SAME_SIZE(datEncountPack, EncountPack);
SAME_OFFSET(datEncountPack, EncountPack, enctable, enctable);
SAME_SIZE(datGlobalWork, GlobalWork);
SAME_OFFSET(datGlobalWork, GlobalWork, units, units);
SAME_OFFSET(datGlobalWork, GlobalWork, item_counts, item_counts);
SAME_OFFSET(datGlobalWork, GlobalWork, hearts_owned_count, hearts_owned_count);
SAME_OFFSET(datGlobalWork, GlobalWork, hearts_param_upgrades, hearts_param_upgrades);
SAME_OFFSET(datGlobalWork, GlobalWork, encyc_records, encyc_records);
SAME_SIZE(fclencyceelem, EncycRecord);
SAME_OFFSET(fclencyceelem, EncycRecord, flag, flag);
SAME_SIZE(rstSkillInfo, UpcomingSkills);
SAME_SIZE(datSkill, SkillInfo);
SAME_SIZE(fclSkillEvent, GrowthEvent);
SAME_SIZE(fclSkill, DevilGrowth);
SAME_SIZE(datItem, ItemData);
SAME_SIZE(fclHeartsSkill, MagatamaSkill);
SAME_SIZE(fclHearts, MagatamaData);
SAME_OFFSET(fclHearts, MagatamaData, autoasignparam, autoasignparam);
SAME_OFFSET(fclHearts, MagatamaData, skill, skill);
SAME_SIZE(cmbEvoFlag, EvolutionRequirement);
SAME_SIZE(fclKeisyoSkillLevel, InheritanceLevel);
SAME_SIZE(fclKeisyoScore, InheritanceScores);
SAME_SIZE(cmbPowerUpSkill, SkillPowerUp);
SAME_SIZE(fclKeisyoList, cmb::InheritedSkillList);
SAME_OFFSET(fclKeisyoList, cmb::InheritedSkillList, count, count);
SAME_SIZE(cmbDevilSort, cmb::DevilSortEntry);
SAME_SIZE(fclCombCom, FusionPair);
SAME_SIZE(fclRankTbl, SpiritRankTable);
SAME_SIZE(fclCombSpirit, SpiritParamUp);
SAME_SIZE(fclIkenieExtPattern, SacrificeRacePattern);
SAME_SIZE(fclIkenieExtPatternDev, SacrificeDevilPattern);
SAME_SIZE(fclIkenieExtPatternDev2, SacrificeResultPattern);
SAME_SIZE(fclIkenieExtPatternDevRace, SacrificeDevilRacePattern);
SAME_SIZE(fclEventDevil, EventDevil);
SAME_SIZE(fclMoonRange, MoonRange);
SAME_SIZE(nbFormation, nb::Formation);
SAME_OFFSET(nbFormation, nb::Formation, formindex, formindex);
SAME_SIZE(nbParty, nb::Party);
SAME_OFFSET(nbParty, nb::Party, aisyo, aisyo);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, esccnt, esccnt);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, exp, exp);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, piercedResistance, piercedResistance);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, autoskill, autoskill);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, aiselect, aiselect);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, aisummonid, aisummonid);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, summonallowed, summonallowed);
SAME_OFFSET(nbTarSelProcessData, nb::TargetSelectData, enemyno, enemyno);
SAME_SIZE(datDevilAI, DevilAI);
SAME_SIZE(frRequest, fr::Request);
SAME_OFFSET(frRequest, fr::Request, prev, prev);
SAME_OFFSET(frRequest, fr::Request, head, head);
SAME_SIZE(frText, fr::Text);
SAME_OFFSET(frText, fr::Text, glyph, glyph);
SAME_SIZE(frGlyph, fr::Glyph);
SAME_SIZE(frTextureCell, fr::TextureCell);
SAME_SIZE(frTextureCells, fr::TextureCells);
SAME_SIZE(frFontHeader, fr::FontHeader);
SAME_SIZE(frStyle, fr::Style);
SAME_SIZE(frPoolNode, fr::PoolNode);
SAME_SIZE(frMsgInfo, fr::MessageInfo);
SAME_OFFSET(frSettings, fr::Settings, style, style);
SAME_OFFSET(frText, fr::Text, next, next);
SAME_OFFSET(itfpanel, itf::Panel, type, type);
SAME_SIZE(itfMesBinFileHeader, mes::FileHeader);
SAME_OFFSET(itfMesBinMesHeader, mes::MesHeader, addr, addr);
SAME_OFFSET(itfMesBinSelHeader, mes::SelHeader, ptr, ptr);
SAME_SIZE(Speaker_tag, mes::Speaker);
SAME_SIZE(message_tag, mes::Message);
SAME_SIZE(select_tag, mes::Select);
SAME_SIZE(window_tag, mes::Window);
SAME_SIZE(curctr_tag, mes::CurCtr);
SAME_SIZE(instanceMes_tag, mes::Instance);
SAME_OFFSET(instanceMes_tag, mes::Instance, func_kuti, func_kuti);
SAME_SIZE(itfmisclinkheader, itf::LinkNode);
SAME_SIZE(itfMesManager, mes::Manager);
SAME_SIZE(scrHeader, scr::Header);
SAME_OFFSET(scrHeader, scr::Header, LocalIntCount, LocalIntCount);
SAME_SIZE(scrTypeTable, scr::TypeTable);
SAME_SIZE(scrProcTable, scr::ProcTable);
SAME_SIZE(scrCode, scr::Code);
SAME_SIZE(scrProcessWork, scr::ProcessWork);
SAME_OFFSET(scrProcessWork, scr::ProcessWork, StackData, StackData);
SAME_OFFSET(scrProcessWork, scr::ProcessWork, StartProc, StartProc);
SAME_OFFSET(scrProcessWork, scr::ProcessWork, LocalInt, LocalInt);
SAME_OFFSET(scrProcessWork, scr::ProcessWork, data, data);
SAME_SIZE(scrScriptList, scr::ScriptList);
SAME_SIZE(dds3Quake, dds3::Quake);

} // namespace
