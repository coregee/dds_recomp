# EE arithmetic test reference

These files support instruction-value validation. They are third-party test
tools and are excluded from recovered ELF-function counts.

- `ps2float.c/.h`: libretro/ps2 commit
  `6eabf2242d451ee2e6d52b1e3f10efb77143ed05`, `pcsx2/ps2float.*`.
  PCSX2 copyright notice and LGPL-3.0-or-later terms are retained. See
  `COPYING.LESSER` and `COPYING`.
- `convert`, `arithmetic`, `muldiv` test sources/results and `shared.h`:
  unknownbrackets/ps2autotests commit
  `97469ffbed8631277b94e28d01dabd702aa97ef3`, `tests/cpu/ee_fpu/`.
  See `ps2autotests-LICENSE.md` for its ISC-style notice.
- `revisions.json` records the fetched revisions. The Java value adaptation
  in `tooling/ghidra/EEFpuValueModel.java` retains the arithmetic reference's
  LGPL terms.

The host provider uses only ADD/SUB/MUL result words, plus separately written
integer conversions. The Java/C comparison is consistency testing of the same
research algorithm; published PS2 test captures are reported separately.
Neither check establishes FCSR exception-state, timing, traps or whole-game
runtime behavior. See `analysis/ee-fpu-exp-model.md` and the generated
`analysis/ee-fpu-validation.json` for source hashes and results.
