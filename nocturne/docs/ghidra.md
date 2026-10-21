# Ghidra project

`ghidra/Nocturne.gpr`, program `candidate` (`SLUS_209.11`, language
`r5900:LE:32:default` from the
[ghidra-emotionengine-reloaded](https://github.com/chaoticgd/ghidra-emotionengine-reloaded)
extension). It is the single working database; earlier copies, candidate
projects and GZF checkpoints were deleted in the October 2026 cleanup.

The text backup is `reference/ps2/ghidra-annotations.tsv` (names, signatures,
variables, comments). Refresh it with `tools/ghidra/export-annotations.ps1`
after every session of Ghidra work; that also refreshes
`reference/function-map.tsv`.

## State (2026-10-21)

- 9,065 functions; 3,133 have names, 5,932 are still `FUN_xxxxxxxx`.
- About 840 names are original (`dat*`, `nb*`, `evt*`, `fcl*`, `cmb*`,
  `sdf*`, `dds3*` …), mostly from HD-remaster matches.
- About 2,180 names are placeholders starting with `ps2`, many with an
  address suffix (`ps2FusionCore_001FDCA0`). They describe the role but are
  not original names. Replace them as original names are found (see
  `reference/ps2/identification/hd-name-leads-unverified.tsv` for leads).
- Most signatures were set for the legacy C ABI (`ulonglong` register
  images). The 96 functions in `tools/ghidra/nocturne_signatures.tsv` (the
  rewritten ones and the core accessors they call) now have typed prototypes
  with the original parameter names.
- The records (`datUnitWork`, `datNormalSkill`, `datSkill`,
  `datDevilFormat`, `datEncount*`, `nbMainProcessData`, `nbParty`,
  `nbFormation` …) are in the `/nocturne` category, from
  `tools/ghidra/nocturne_types.h`, and the data tables are typed and labelled
  (`datDevilFormat_tbl`, `datNormalSkill_tbl`, `datEncount_tbl`, …). Re-run
  `tools/ghidra/import-types.ps1` after changing either file.
- The VU microprograms are loaded as `.DVP.overlay..*` overlay spaces.

## Known problem: DIVU is decoded as signed

The extension's SLEIGH for the R5900 `DIVU` uses signed division (`s/`,
`s%`). The decompiler therefore shows unsigned divisions as signed. Exports
(`tools/ghidra/export-executable.ps1`) use a patched copy of the language built
by `tools/ghidra/prepare-ee-divu-fix.ps1` (into `build/ee-divu-fixed/`); the
installed extension is left untouched. When reading divisions in the GUI,
check the instruction.

## Naming policy

1. Original name when proven by the HD remaster (matching body/role) or by a
   string in the executable.
2. Otherwise a descriptive English name, no address suffix, and a plate
   comment saying how sure it is.
3. Keep `FUN_` for functions you haven't looked at; don't name from a single
   guess.
