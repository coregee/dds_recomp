// A devil's AI record (datDevilAI), as US Maniax lays it out: 384 records
// of 0xA4 bytes at 0x3989E0 (records.hpp DevilAI). Three checks of two
// conditions each choose one of three tables of five actions; table 0 when
// none holds. The AI code takes a table by reference: here its index.
//
// Hardtype (NOCTURNE_HARDTYPE):
// A devil's AI record (datDevilAI), as Hardtype lays it out: a table of
// record addresses by devil at 0x3989E0, and records of any length in the
// same space:
//     +0x00  int8   (unknown)
//     +0x01  int8   the number of checks
//     +0x02  int8   the number of action tables
//     +0x08  uint16 the AI script
//     +0x0A  uint16 the target choice level
//     +0x0C  checks: three conditions and the address of their table (16 bytes each)
//     then   the action tables, back to back: int8 count, a byte, count x AiAction;
//            the first is the one used when no check holds
//     ...    the death script and event (the last four bytes before the next record)
// The AI code takes a table by reference: here its address. (The records are
// only 2-byte aligned, so Hardtype's word loads are unaligned, which PCSX2
// tolerates.)
#pragma once

#include "nocturne/build.hpp"

#if NOCTURNE_HARDTYPE

#include <cstdint>
#include <cstring>

#include "nocturne/data/tables.hpp"

namespace nocturne::dat {

class AiRecord {
public:
    explicit AiRecord(int32_t devil) : devil_(devil) {}

    static constexpr int32_t kConditions = 3;   // per check

    uint16_t script() const { return half(base() + 8); }
    uint16_t level() const { return half(base() + 0xa); }
    int32_t checks() const { return byte(base() + 1); }
    int32_t tables() const { return byte(base() + 2); }
    uint32_t condition(int32_t check, int32_t k) const { return word(checkAt(check) + 4u * static_cast<uint32_t>(k)); }
    uint32_t table(int32_t check) const { return word(checkAt(check) + 0xc); }
    uint32_t firstTable() const { return checkAt(checks()); }
    int32_t actions(uint32_t table) const { return byte(table); }
    AiAction action(uint32_t table, int32_t action) const
    {
        AiAction value;
        std::memcpy(&value, guest::table<const uint8_t>(table + 2u + 8u * static_cast<uint32_t>(action)), sizeof value);
        return value;
    }
    // Every action's skill word, walked as GetBadActionSkill does: at least
    // one table, and at least one entry of each (0x28E670..0x28E700).
    template <class F>
    void forEachActionSkill(F&& f) const
    {
        uint32_t at = base() + 0x10 + 16u * static_cast<uint32_t>(checks());   // the first table's first skill
        int32_t t = 0;
        do {
            int32_t remaining = byte(at - 4) - 1;
            do {
                f(half(at));
                at += 8;
            } while (--remaining >= 0);
            at += 2;   // the next table's first skill
        } while (++t < tables());
    }
    uint16_t deathScript() const { return half(next() - 4); }
    uint16_t deathEvent() const { return half(next() - 2); }

    uint32_t base() const { return word(address::DevilAI + 4u * static_cast<uint32_t>(devil_)); }

private:
    uint32_t next() const { return word(address::DevilAI + 4u * static_cast<uint32_t>(devil_ + 1)); }
    uint32_t checkAt(int32_t check) const { return base() + 0xc + 16u * static_cast<uint32_t>(check); }
    static uint32_t word(uint32_t at)
    {
        uint32_t value;
        std::memcpy(&value, guest::table<const uint8_t>(at), sizeof value);
        return value;
    }
    static uint16_t half(uint32_t at)
    {
        uint16_t value;
        std::memcpy(&value, guest::table<const uint8_t>(at), sizeof value);
        return value;
    }
    static int32_t byte(uint32_t at) { return *guest::table<const int8_t>(at); }

    int32_t devil_;
};

inline AiRecord aiRecord(int32_t devil) { return AiRecord(devil); }

} // namespace nocturne::dat

#else

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

#endif
