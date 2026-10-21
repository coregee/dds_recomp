// Checks that the data tables in src/data compile to exactly the bytes in
// SLUS_209.11.
//
// usage: tables <path to SLUS_209.11>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <vector>

#include "nocturne/data/tables.hpp"

using namespace nocturne;

namespace {

constexpr uint32_t kDataSegmentDelta = 0xff000; // RAM address - file offset

struct Table {
    const char* name;
    uint32_t address;
    const void* data;
    size_t size;
};

} // namespace

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::fprintf(stderr, "usage: %s <SLUS_209.11>\n", argv[0]);
        return 2;
    }
    std::ifstream file(argv[1], std::ios::binary);
    std::vector<uint8_t> elf((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if (elf.empty()) {
        std::fprintf(stderr, "cannot read %s\n", argv[1]);
        return 2;
    }

    const Table tables[] = {
        {"datSkill", dat::address::SkillInfo, dat::kSkillInfo, sizeof dat::kSkillInfo},
        {"datDevilFormat", dat::address::DevilFormat, dat::kDevilFormat, sizeof dat::kDevilFormat},
        {"datNormalSkill", dat::address::NormalSkill, dat::kNormalSkill, sizeof dat::kNormalSkill},
        {"datSpecialSkill", dat::address::SpecialSkill, dat::kSpecialSkill, sizeof dat::kSpecialSkill},
        {"datEncount", dat::address::Encount, dat::kEncount, sizeof dat::kEncount},
        {"datEncountPack", dat::address::EncountPack, dat::kEncountPack, sizeof dat::kEncountPack},
        {"affinity", dat::address::Affinity, dat::kAffinity, sizeof dat::kAffinity},
        {"fclSkillTbl", dat::address::DevilGrowth, dat::kDevilGrowth, sizeof dat::kDevilGrowth},
        {"datItem", dat::address::Item, dat::kItem, sizeof dat::kItem},
        {"fclHeartsTbl", dat::address::Magatama, dat::kMagatama, sizeof dat::kMagatama},
        {"datDevilAI", dat::address::DevilAI, dat::kDevilAI, sizeof dat::kDevilAI},
        {"fclCombineTbl", dat::address::CombineTbl, dat::kCombineTbl, sizeof dat::kCombineTbl},
        {"fclCombineCurseTbl", dat::address::CombineCurseTbl, dat::kCombineCurseTbl, sizeof dat::kCombineCurseTbl},
        {"fclRankUpDownTbl", dat::address::RankUpDownTbl, dat::kRankUpDownTbl, sizeof dat::kRankUpDownTbl},
        {"fclExtPatternTbl", dat::address::ExtPatternTbl, dat::kExtPatternTbl, sizeof dat::kExtPatternTbl},
        {"fclBirthSpiritTbl", dat::address::BirthSpiritTbl, dat::kBirthSpiritTbl, sizeof dat::kBirthSpiritTbl},
        {"fclSpiritParamUpTbl", dat::address::SpiritParamUpTbl, dat::kSpiritParamUpTbl, sizeof dat::kSpiritParamUpTbl},
        {"fclIkenieExtPattern", dat::address::IkenieExtPatternTbl, dat::kIkenieExtPatternTbl, sizeof dat::kIkenieExtPatternTbl},
        {"fclIkenieExtPatDev", dat::address::IkenieExtPatternDevTbl, dat::kIkenieExtPatternDevTbl, sizeof dat::kIkenieExtPatternDevTbl},
        {"fclIkenieExtPatDev2", dat::address::IkenieExtPatternDev2Tbl, dat::kIkenieExtPatternDev2Tbl, sizeof dat::kIkenieExtPatternDev2Tbl},
        {"fclIkenieExtPatRace", dat::address::IkenieExtPatternDevRaceTbl, dat::kIkenieExtPatternDevRaceTbl, sizeof dat::kIkenieExtPatternDevRaceTbl},
        {"fclAccidentFailTbl", dat::address::AccidentFailTbl, dat::kAccidentFailTbl, sizeof dat::kAccidentFailTbl},
        {"fclEventDevilTbl", dat::address::EventDevilTbl, dat::kEventDevilTbl, sizeof dat::kEventDevilTbl},
        {"fclManinKagTbl", dat::address::CombineManinKagTbl, dat::kCombineManinKagTbl, sizeof dat::kCombineManinKagTbl},
        {"fclManinRaceTbl", dat::address::CombineManinRaceTbl, dat::kCombineManinRaceTbl, sizeof dat::kCombineManinRaceTbl},
        {"fclManinTbl", dat::address::CombineManinTbl, dat::kCombineManinTbl, sizeof dat::kCombineManinTbl},
        {"evolutionReq", dat::address::EvolutionRequirement, dat::kEvolutionRequirement, sizeof dat::kEvolutionRequirement},
        {"inheritLevel", dat::address::InheritanceLevel, dat::kInheritanceLevel, sizeof dat::kInheritanceLevel},
        {"inheritScores", dat::address::InheritanceScores, &dat::kInheritanceScores, sizeof dat::kInheritanceScores},
        {"darkDevil", dat::address::DarkDevil, dat::kDarkDevil, sizeof dat::kDarkDevil},
        {"skillPowerUp", dat::address::SkillPowerUp, dat::kSkillPowerUp, sizeof dat::kSkillPowerUp},
    };

    int failures = 0;
    for (const Table& t : tables) {
        const uint8_t* original = elf.data() + (t.address - kDataSegmentDelta);
        const uint8_t* source = static_cast<const uint8_t*>(t.data);
        size_t mismatch = t.size;
        for (size_t i = 0; i < t.size; ++i) {
            if (original[i] != source[i]) { mismatch = i; break; }
        }
        if (mismatch == t.size) {
            std::printf("%-16s ok    %6zu bytes at 0x%08X\n", t.name, t.size, t.address);
        } else {
            ++failures;
            std::printf("%-16s FAIL  first difference at 0x%08zX (+0x%zX): %02X in executable, %02X in source\n",
                        t.name, t.address + mismatch, mismatch, original[mismatch], source[mismatch]);
        }
    }
    std::printf("%s\n", failures ? "FAILED" : "PASSED");
    return failures ? 1 : 0;
}
