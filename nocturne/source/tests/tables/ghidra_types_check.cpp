// Compile-time check that tools/ghidra/nocturne_types.h (the types imported
// into Ghidra) matches the C++ records.
#include <cstddef>
#include <cstdint>

#include "nocturne/battle/comm_select.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/battle/talk.hpp"
#include "nocturne/battle/event_process.hpp"
#include "nocturne/battle/macca_window.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/fusion/combine.hpp"
#include "nocturne/fusion/sort.hpp"
#include "nocturne/interface/font.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/kernel/draw.hpp"
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
SAME_OFFSET(datUnitWork, UnitWork, hensinmaeexp, preEvolutionExp);
SAME_SIZE(datNormalSkill, NormalSkill);
SAME_OFFSET(datNormalSkill, NormalSkill, program, program);
SAME_OFFSET(datNormalSkill, NormalSkill, magiclimit, magiclimit);
SAME_SIZE(datSpecialSkill, SpecialSkill);
SAME_SIZE(datDevilFormat, DevilFormat);
SAME_SIZE(datDevilNegoFormat, DevilTalkFormat);
SAME_OFFSET(datDevilNegoFormat, DevilTalkFormat, mukantype, lastEnemyTalk);
SAME_OFFSET(datDevilFormat, DevilFormat, specialbit, specialbit);
SAME_OFFSET(datDevilFormat, DevilFormat, reserve1, reserve1);
SAME_SIZE(datEncount, Encount);
SAME_OFFSET(datEncount, Encount, btlsound, btlsound);
SAME_SIZE(datEncountRitu, EncounterEntry);
SAME_SIZE(datEncountTbl, EncountTbl);
SAME_SIZE(datEncountPack, EncountPack);
SAME_OFFSET(datEncountPack, EncountPack, enctable, enctable);
SAME_SIZE(datGlobalWork, GlobalWork);
SAME_OFFSET(datGlobalWork, GlobalWork, units, units);
SAME_OFFSET(datGlobalWork, GlobalWork, item_counts, item_counts);
SAME_OFFSET(datGlobalWork, GlobalWork, syakkincnt, loanCounts);
SAME_OFFSET(datGlobalWork, GlobalWork, negoques, questionAnswers);
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
SAME_OFFSET(nbParty, nb::Party, aisyo, affinities);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, esccnt, esccnt);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, exp, exp);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, piercedResistance, piercedResistance);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, autoskill, autoskill);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, seq, seq);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, timelist, timelist);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, hitstopframe, hitstopframe);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, aiselect, aiselect);
SAME_OFFSET(nbActionProcessData, nb::ActionProcessData, aisummonid, aisummonid);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, summonallowed, summonallowed);
SAME_OFFSET(nbTarSelProcessData, nb::TargetCursor, enemyno, enemyno);
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
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, negoresult, talkResult);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, MainProcessID, MainProcessID);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, AiScriptProcessID, AiScriptProcessID);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, jyokyomsgid, statusMessageTable);
SAME_SIZE(nbTarSelProcessData, nb::TargetCursor);
SAME_SIZE(nbHelpProcessData, nb::HelpLine);
SAME_SIZE(nbNegoProcessData, nb::TalkState);
SAME_SIZE(nbMakaProcessData, nb::MaccaWindow);
SAME_OFFSET(nbMakaProcessData, nb::MaccaWindow, offtime, closeframes);
SAME_SIZE(nbEventProcessData, nb::EventProcessData);
SAME_SIZE(nbSound, nb::SoundEntry);
SAME_OFFSET(nbSound, nb::SoundEntry, motse_h, handles);
SAME_OFFSET(nbSound, nb::SoundEntry, negose_h, talkHandle);
SAME_OFFSET(nbEventProcessData, nb::EventProcessData, mem, mem);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, nextkouho, candidates);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, history, history);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, pwork, pwork);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, ppartyindex, ppartyindex);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, prevreqtype, prevreqtype);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, flowmsg, flowmsg);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, infomsg, infomsg);
SAME_OFFSET(nbNegoProcessData, nb::TalkState, selectcur, selectcur);
SAME_SIZE(nbCommSelProcessData, nb::CommandMenu);
SAME_OFFSET(nbCommSelProcessData, nb::CommandMenu, commdisable, unavailable);
SAME_OFFSET(nbCommSelProcessData, nb::CommandMenu, animeflag, animation);
SAME_OFFSET(nbHelpProcessData, nb::HelpLine, textcol, textcol);
SAME_OFFSET(nbHelpProcessData, nb::HelpLine, alpha, alpha);
SAME_SIZE(itfPanelMesWinWork, itf::MesWinWork);
SAME_OFFSET(itfPanelMesWinWork, itf::MesWinWork, shade, shade);
SAME_SIZE(itfPanelSelWinWork, itf::SelWinWork);
SAME_SIZE(itfPanelNormalWork, itf::NormalWork);
SAME_SIZE(itfPanelPlainWork, itf::PlainWork);
SAME_SIZE(itfPanelPera1Work, itf::Pera1Work);
SAME_SIZE(itfPanelLeftFadeWork, itf::LeftFadeWork);
SAME_SIZE(itfPanelFacilityWork, itf::FacilityWork);
SAME_OFFSET(itfPanelFacilityWork, itf::FacilityWork, edge, edge);
SAME_SIZE(itfMesBinFileHeader, mes::FileHeader);
SAME_OFFSET(itfMesBinMesHeader, mes::MesHeader, addr, addr);
SAME_OFFSET(itfMesBinSelHeader, mes::SelHeader, ptr, ptr);
SAME_SIZE(Speaker_tag, mes::Speaker);
SAME_SIZE(message_tag, mes::Message);
SAME_SIZE(select_tag, mes::Select);
SAME_SIZE(window_tag, mes::Window);
SAME_SIZE(curctr_tag, mes::CurCtr);
SAME_SIZE(instanceMes_tag, mes::Instance);
SAME_OFFSET(instanceMes_tag, mes::Instance, func_kuti, mouthCallback);
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
SAME_SIZE(dds3Effect_Blur, eff::Blur);
SAME_SIZE(dds3Effect_PartialMultiBlurParam, eff::PartialMultiBlurParam);
SAME_SIZE(dds3Effect_DistortionBlurParam, eff::DistortionBlurParam);
SAME_OFFSET(dds3Effect_DistortionBlurParam, eff::DistortionBlurParam, width, width);
SAME_SIZE(dds3Effect_RippleBlurParam, eff::RippleBlurParam);
SAME_OFFSET(dds3Effect_RippleBlurParam, eff::RippleBlurParam, area, area);
SAME_SIZE(dds3Effect_Filter, eff::Filter);
SAME_SIZE(dds3Effect_PartialMultiFilterParam, eff::PartialMultiFilterParam);
SAME_SIZE(sdf3DFogParam, dds3::FogParam);
SAME_SIZE(dds3EffectFades, dds3::EffectFades);
SAME_SIZE(dds3SceneFades, dds3::SceneFades);
SAME_SIZE(datBossPress, dat::BossPress);
SAME_SIZE(nbKoukaPacket, nb::EffectPacket);
SAME_OFFSET(nbKoukaPacket, nb::EffectPacket, v, v);
SAME_SIZE(nbKoukaProcessData, nb::EffectQueue);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, press4_p, press4_p);
SAME_OFFSET(nbMainProcessData, nb::MainProcessData, KoukaProcessID, EffectQueueProcessID);
SAME_OFFSET(dds3SceneFades, dds3::SceneFades, fogrgbbase, fogrgbbase);
SAME_OFFSET(dds3SceneFades, dds3::SceneFades, biastarget, biastarget);

} // namespace
