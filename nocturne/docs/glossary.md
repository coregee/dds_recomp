# Glossary

The original code uses romanized Japanese (often in older Kunrei/Nihon-shiki
spelling, so *syo* not *sho*, *jyo* not *jo*). This list explains the terms
and records the evidence for every value used in the rewrite.

## Prefixes

| Prefix | Meaning |
|---|---|
| `dat` | data: units, devils, items, the save state (`datGlobalWork`) |
| `nb` | "new battle": the battle system |
| `evt` | event flags, moon phase |
| `fcl` | facilities (compendium, shops, the Cathedral of Shadows: `fclCombine*`) |
| `cmb` | "combine": fusion, and the devil stock it manages |
| `cmp` | status / Magatama menus |
| `rst` | the battle results screen (level-ups) |
| `sdf` | system library (RNG, memory) |
| `dds3` | engine core (*Digital Devil Saga 3* = Nocturne's internal name) |

## Words

| Term | Japanese | Meaning |
|---|---|---|
| aisyo | 相性 | affinity (weak/resist/null/repel/drain) |
| baramaki | ばら撒き | scattering (Macca) |
| gensyo | 減少 | reduction |
| hatudo | 発動 | activation (of a passive skill) |
| hensin(mae) | 変身(前) | transformation / evolution (before) |
| hearts | — | Magatama (the HD code's English name) |
| ikenie | 生贄 | sacrifice (sacrificial fusion) |
| hojo | 補助 | support: buffs and debuffs (-kaja/-nda) |
| hougyoku | 宝玉 | Bead (item 4) |
| jyoken | 条件 | condition |
| kuisibari | 食いしばり | gritting one's teeth: Endure / Never Yield |
| buturi | 物理 | physical |
| waza | 技 | skill (power) |
| kaifuku | 回復 | recovery |
| kotowari | 理 | Reason (the three ending philosophies) |
| LND | — | Law / Neutral / Dark alignment |
| kakutoku | 獲得 | earned |
| keisyo | 継承 | inheritance (fusion) |
| kouka | 効果 | effect |
| maka / makka | マッカ | Macca (money) |
| maseki | 魔石 | Life Stone (item 3) |
| manin | 魔人 | Fiend (fused with a Deathstone) |
| mitama | 御魂 | Mitama, a spirit that raises stats when fused |
| nakama | 仲間 | companion (a demon in the stock) |
| renzoku | 連続 | consecutive (encounters) |
| ritu | 率 | rate |
| sake | 避け | evasion |
| sensei | 先制 | first strike / initiative |
| syoji | 所持 | owned / held |
| takara sagasi | 宝探し | treasure hunting (Lucky Find) |
| zokusei (3zokusei) | (三)属性 | alignment class |

## Values and their evidence

### Ailments (`UnitWork::badstat`, low 12 bits)

| Value | Ailment | Evidence |
|---|---|---|
| 0x001 | Shock | `datGetBadStatusAttr` maps it to element 3 (Elec); guaranteed crits |
| 0x002 | Freeze | element 2 (Ice); guaranteed crits; strips physical Null/Repel/Drain |
| 0x004 | Sleep | Lullaby (skill 0xD2) inflicts 0x004; Eternal Rest (program 6) requires it |
| 0x008 | Panic | element 10 (Mind) with Sleep and Charm |
| 0x010 | Bind | element 9 (Nerve) with Stun |
| 0x020 | Mute | blocks magic (`nbCheckSkillUse`: status 0x20 + magic skill) |
| 0x040 | Poison | halves attack power (`datGetNormalAtkPow`) |
| 0x080 | Charm | element 10 (Mind) |
| 0x100 | Stun | element 9 (Nerve); attacker accuracy x0.25 |
| 0x200 | Fly | all stats become 1 except Agility; all affinities 200% |
| 0x400 | Stone | Petradi inflicts it; Physical/Force shatters; whole party stoned = game over |
| 0x800 | Dead | Mudo/Hama inflict it |

Element mapping for Mind/Nerve/Curse matches community skill lists
(Nerve: Bind/Stun; Mind: Sleep/Charm/Panic; Curse: Poison/Mute).
`0x8000` is a separate flag checked by `nbCheckBadCurse`.
Ailments are a value, not a bit set: `datSetBadStat` only replaces the current
ailment with a numerically larger one.

### Elements (`Attribute`)

0 Physical, 1 Fire, 2 Ice, 3 Elec, 4 Force, 5 Almighty, 6 Expel, 7 Death,
8 Curse, 9 Nerve, 10 Mind. Evidence: the passive families
Anti/Void/Drain/Repel *X* are `0x139/0x143/0x14D/0x152 + element` (skipping
Almighty for Expel upward), and the randomizer skill list names them in that
order (Anti Phys 0x139, Anti Fire 0x13A, ...). The Stone affinity row is 10%
Fire/Ice/Elec, 100% Physical/Force — Stone shatters to Physical/Force.

### Affinity word

Low 16 bits = damage percent. Flags: `0x10000` Null, `0x20000` Repel,
`0x40000` Drain, `0x80000000` Weak (every 150% entry in the table has it).
`nbGetVirtualAisyo` ranks them Repel > Drain > Null. Tetrakarn/Makarakarn
(buff counters 13/14) set Repel for physical/magic. `0x100000` occurs in the
data (18 entries) with no known role yet.

### Skill IDs

From the [Nocturne Randomizer](https://github.com/nmarkro/Nocturne-Randomizer)
`data/skill_data.txt` (revision f74e85c), checked against the code's use:
0x09E Holy Melody, 0x09F Evil Melody, 0x128 Fast Retreat, 0x12A Mind's Eye,
0x12B Might, 0x12C Bright Might, 0x12D Dark Might, 0x165 Pierce.

`datSpecialSkill` (0x3DC1E0, indexed from 0x128) holds their numbers: Fast
Retreat 150 (escape x1.5), Mind's Eye 3 (ambush /3), Might 300 (crit x3),
Anti-*X* 50 (half damage).

### Buff counters (Party::count, "hojo")

4 Attack, 5 Magic, 6 Evasion, 7 Defense, 8 Accuracy (range −4..4); 9 Ice,
10 Fire, 11 Death, 12 Expel temporary nulls; 13 Makarakarn, 14 Tetrakarn;
15 Focus; 19 affinity-row override. Evidence: nbGetButuriAttack reads 4 for
the attacker and 7 for the defender, nbGetMagicAttack 5, hit chance 8 (attacker)
and 6 (defender); nbGetAisyo maps Fire→10, Ice→9, Expel→12, Death→11 and
magic/physical skills to 13/14; nbGetHojoRitu multiplies counter 4 by 2.5
when 15 is set.

### Element boosts

`0x134 + element` lands exactly on Fire/Ice/Elec/Force Boost (0x135–0x138),
confirming elements 1–4 independently of the passive resistance families.

### Difficulty

Event bit `0xAF2` is **Normal** difficulty: the US difficulty menu (code at
0x229880) turns it on for the first option and off for the second, and a
new-game path (0x121530) sets it by default. Consistent with Hard mode's known
behaviour ("almost no chance to escape").

### Items

Drop item 3 = Life Stone (`masekipoint`), 4 = Bead (`hougyokupoint`); IDs from
the randomizer's `item_names.txt` (1-based list).

### Debug strings

The executable's `printf` formats (EUC-JP) name the formulas:
物理ヒット率 physical hit rate, 魔法ヒット率 magic hit rate, 石化一撃確率 stone
one-hit chance, バットステータス回復確率 bad-status recovery chance, 先制率
first-strike rate, バックアタック確率 back-attack chance, 逃走率 escape rate.
