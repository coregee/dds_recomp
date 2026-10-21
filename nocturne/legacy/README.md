# Legacy recovery (frozen)

`src/` is the first-pass C recovery of about 3,000 functions, produced by an
automated workflow that validated each function against the original MIPS
instructions in an emulator. It is the most reliable statement of what those
functions do, but it is written for the validator, not for people: raw PS2
addresses, 64-bit register images, floats as bit patterns, unnamed fields.

It is kept as reference material for `source/`:

- read it to understand a function's exact behaviour;
- compile individual units into differential tests (see
  `source/tests/differential/`), with the shared fakes standing in for their
  callees.

Do not edit it. Function names follow the earlier conventions
(`ps2<Subsystem><Role>_<ADDRESS>` for functions without a known original
name); `reference/function-map.tsv` maps them to addresses and current
Ghidra names, and `docs/battle-mechanics.md` lists known naming mistakes.

## Supporting files

A few units include files that lived outside `src/`. They are kept here at
the same relative paths so the includes still resolve:
`tests/libc_stream_mode.h`, `tests/battle_panel_color_native_bindings.c`,
`tooling/field_unit_lifetime_probe_bindings.c` and three headers under
`analysis/drafts/model-context-anchor/`. `tests/ee_fpu_values.c` is the host
implementation of the EE FPU primitives (`ee_fpu.h`) on top of
`../third_party/ps2float`.

`build/` holds the response files of the old whole-program test DLL build,
for the record only. That build also linked test bindings tied to emulator
captures that no longer exist, so it does not run as-is.
