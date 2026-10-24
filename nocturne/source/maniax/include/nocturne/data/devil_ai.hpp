// A devil's AI record (datDevilAI), as US Maniax lays it out: 384 records
// of 0xA4 bytes at 0x3989E0 (records.hpp DevilAI). Three checks of two
// conditions each choose one of three tables of five actions; table 0 when
// none holds. The AI code takes a table by reference: here its index.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/data/tables.hpp"

namespace nocturne::dat {

class AiRecord {
public:
    explicit AiRecord(int32_t devil) : devil_(devil) {}

    static constexpr int32_t kConditions = 2;   // per check

    uint16_t script() const { return record().scriptid; }
    uint16_t level() const { return record().ailevel; }
    int32_t checks() const { return 3; }
    int32_t tables() const { return 3; }
    uint32_t condition(int32_t check, int32_t k) const { return record().aichk[check].check[k]; }
    uint32_t table(int32_t check) const { return record().aichk[check].table; }
    uint32_t firstTable() const { return 0; }
    int32_t actions(uint32_t) const { return 5; }
    // An action as the original addresses it (indexes aren't checked).
    AiAction action(uint32_t table, int32_t action) const
    {
        const uint32_t at = address::DevilAI + static_cast<uint32_t>(devil_) * static_cast<uint32_t>(sizeof(DevilAI)) +
                            static_cast<uint32_t>(offsetof(DevilAI, aitable)) + table * 40u + 8u * static_cast<uint32_t>(action);
        return *guest::table<const AiAction>(at);
    }
    // Every action's skill word, in the order GetBadActionSkill reads them.
    template <class F>
    void forEachActionSkill(F&& f) const
    {
        for (const auto& t : record().aitable)
            for (const AiAction& a : t)
                f(a.skill);
    }
    uint16_t deathScript() const { return record().deadscriptid; }
    uint16_t deathEvent() const { return record().deadeventno; }

private:
    const DevilAI& record() const { return devilAI(devil_); }

    int32_t devil_;
};

inline AiRecord aiRecord(int32_t devil) { return AiRecord(devil); }

} // namespace nocturne::dat
