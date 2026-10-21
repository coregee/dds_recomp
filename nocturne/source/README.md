# source/ — the readable reconstruction

C++20 code that reads like the game's source while behaving exactly like the
original. Each function is rewritten from the validated legacy C (or from the
original instructions) and proven equivalent by a differential test.

## Layout

```
include/nocturne/
  guest.hpp            PS2 memory: Ptr32<T> for in-structure pointers, table lookup
  ee/float.hpp         ee::Float, PS2 FPU arithmetic behind normal operators
  data/types.hpp       vocabulary: Param, Attribute, Ailment, Affinity, skill IDs
  data/records.hpp     game records: UnitWork, NormalSkill, DevilFormat, Encount ...
  data/tables.hpp      where the fixed tables live in the executable
  battle/process.hpp   battle state: MainProcessData, Party, Formation
  battle/calc.hpp      nbCalc: hit/crit/ailment rolls, initiative, escape, rewards
  external.hpp         functions not rewritten yet (bridged to legacy C)
src/
  battle/calc.cpp      nbCalc, from legacy/src/combat_calculation.c
  platform/legacy_bridge.cpp   external.hpp -> legacy C ABI
tests/differential/    rewrite vs. legacy, on the real game data
```

Modules follow the original translation units where known (the HD remaster
keeps them as classes: `nbCalc`, `datCalc`, `fclEncyc` …), grouped by the
original prefixes: `dat` data, `nb` battle, `evt` events, `fcl` facilities,
`cmp`/`cmb` menus, `sdf` system. See `../docs/glossary.md`.

## Conventions

- **PS2 layout.** Structures keep their exact PS2 size and offsets
  (`static_assert`ed), so they work with the legacy code, save data and the
  executable's tables. Pointers inside game structures are `Ptr32<T>`.
- **Names.** Struct fields use the original developers' names from the HD
  remaster (`reference/hd/il2cpp/dump.cs`): `badstat`, `hitlevel`,
  `dropmakka`. Functions get an English name; the original name and address
  go in a comment directly above the definition, which
  `tools/function_map.py` reads:
  ```cpp
  // nbCheckEscape @ 0x00269E98
  bool rollEscape(MainProcessData& data)
  ```
  Unnamed originals use `// 0x00259658 (unnamed): ...`.
- **Uncertainty is visible.** Unknown fields are `unknown_<offset>`; inferred
  names say *tentative*. Promote a guess only with evidence (symbol, string,
  data table, caller).
- **Floats.** Use `ee::Float` for anything the original did on the FPU: the
  EE rounds toward zero and has no denormals/NaN/inf, so host `float` can be
  off by one after truncation. Constants from the executable must be
  bit-exact (`0.1` there is `0x3dcccccc`, not `0.1f`).
- **Same observable behaviour,** including RNG draw order and count. Keep
  original quirks (dead computations, redundant checks) and explain them in a
  comment instead of fixing them.

## Testing

```
tests\differential\build.cmd [cases-per-function] [seed]
```

Loads `game/SLUS_209.11` into fake PS2 RAM (so all static tables are real
game data), generates random game states, runs the legacy function and the
rewrite on identical copies, and compares return values, traps, RNG draws,
debug prints and every byte of dynamic RAM. Not-yet-rewritten callees are
deterministic fakes shared by both sides (`fake_world.c`).

Status: 34/34 nbCalc functions match over 5,000 states each.
