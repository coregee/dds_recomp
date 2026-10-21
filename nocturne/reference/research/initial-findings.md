# Initial Nocturne analysis

## Inputs and results

- PS2 ISO: `Shin Megami Tensei - Nocturne.iso`, SHA-256 `74ade045146efebd2956a096d3c77ea2ad0b5d6b51c67c75bf0f7d390199bdb3`.
- Boot identity: `SYSTEM.CNF` specifies `SLUS_209.11`, version 1.01, NTSC.
- ELF SHA-256: `a26e86e59cab447d9b1839ec11ab82b1557230bcc99746b78e3b5d4359dcc6ff`.
- 70 disc files extracted and independently rehashed against the ISO-derived manifest: zero discrepancies.
- Ghidra: `r5900:LE:32:default`, base `0x00100000`, 8,484 detected functions, 475,328 instructions. Auto-analysis completed without timeout; sample functions decompiled successfully.
- PC installation: `C:\Program Files (x86)\Steam\steamapps\common\smt3hd`. The asset header identifies Unity 2019.4.10f1. No PDB files were found in the installation.
- `GameAssembly.dll` SHA-256: `59adbb5b18aaedc7df6c1672790ca48be99b5e8559c81db27132c436fb0a9fc4`; preferred base `0x180000000`.
- `global-metadata.dat` SHA-256: `f911dd1f750c563313e061df5e7f2d8d2b6e6ab173a2b05f2f8ba398073753b3`.

The metadata has 42 managed modules, 5,378 types, 32,343 method definitions, and 35,171 string literals. `Assembly-CSharp.dll` contributes 2,103 types, 13,083 methods, and 18,380 fields. 13,028 of its method-pointer slots are nonzero and map into the disk image. These counts include remaster code and generated wrappers; they are not a count of original PS2 functions.

## Recovering the native names

Il2CppDumper's automatic registration search failed. Direct PE inspection found the `Assembly-CSharp.dll` string at VA `0x182B61C58`, its code-generation module at `0x182B61C00`, and its 13,083-entry method-pointer table at `0x182DC4430`.

Following module pointers located the 42-module array at `0x182E208D0`, code registration at `0x182C100E0`, and metadata registration at `0x182C10630`. The metadata uses layout 24.2; native registration uses 24.3. The disk-only wrapper in `tooling/il2cpp/` successfully generated the declarations, type header, dummy assemblies, and symbol JSON using these addresses.

50,122 method labels, including generic instantiations and aliases, were applied to `/pc/GameAssembly.dll` with zero rejected or unmapped labels. Nine selected functions were disassembled and decompiled. Full PC auto-analysis was not run.

Useful original-style names include `dds3*`, `datCalc`, `datGetSkillKouka`, `nbCalc`, `nbActionProcess`, `fld*`, and `fcl*`. This is substantial evidence that recognizable game logic survived the Unity port. It does not establish that every PS2 function survived or that there is a one-to-one correspondence.

## First static matches

| Name from HD metadata | PS2 function | HD native VA | Evidence |
| --- | --- | --- | --- |
| `datCalc.datAddHp` | `0x00243E28` | `0x181CC9810` | Signed addition, lower clamp at zero, upper clamp at stored maximum, halfword write. |
| `datCalc.datAddMp` | `0x00243E50` | `0x181CC9DB0` | Same operation on MP, immediately adjacent to the HP helper on PS2. |
| `datCalc.datGetMaxHp` | `0x00243C28` | `0x181CCD0C0` | Skill IDs `0x122`, `0x123`, `0x124`; bonuses 10%, 20%, 30%; cap 999 unless flag bit `0x20`. |
| `datCalc.datGetMaxMp` | `0x00243D28` | `0x181CCD200` | Skill IDs `0x125`, `0x126`, `0x127`; same bonuses and conditional cap. Base-MP calculation is inlined in the PC version. |

The HP/MP PS2 helpers leave the result in `v0` and store it in the return delay slot. They are typed as returning `uint`, consistent with the HD metadata. Names, signatures, comments, and a partial PS2 work structure are saved in Ghidra. The structure records only the compared flag and HP/MP fields; unexamined bytes remain undefined.

| Field | PS2 offset | HD managed-object offset |
| --- | --- | --- |
| flag | `0x00` | `0x10` |
| HP | `0x06` | `0x16` |
| maximum HP | `0x08` | `0x18` |
| MP | `0x0A` | `0x1A` |
| maximum MP | `0x0C` | `0x1C` |

The HD object has a 16-byte managed header. This offset relationship holds for the compared prefix; later fields use managed arrays and references and cannot be copied into a PS2 structure by subtracting 16.

These are strong static semantic matches, not live gameplay validation. Raw comparison output is in `analysis/ps2/leads.c` and `pc/ghidra/samples.c`. `RecordPS2Matches.java` reproduces the four annotations and checks the ELF hash before applying them.

## Next leads and limits

The strongest next target is HD `datCalc.datGetSkillKouka` at `0x181CCE1E0`. Its switch cases, skill fields, affinity handling, and calls to `GetButuriAttack`/`GetMagicAttack` give several independent fingerprints for the PS2 damage/effect logic. Grow the matched call graph outward from the four stat helpers and validate larger candidates using multiple constants, data accesses, and callers.

The original `DDS3.DDT`/`DDS3.IMG` archive is present. An initial index walk counted 9,685 entries. The DDS extractor's ASCII-only filename check rejects a Nocturne index name at `0x98C`; the inner archive was not extracted. Its name encoding needs inspecting before adapting that tool.

Cross-architecture byte matching is unsuitable for MIPS versus x86-64. Compare normalized operations, constants, call relationships, and table contents while accounting for inlining and IL2CPP initialization/null/bounds checks. The original renderer, VU code, PS2 libraries, overlays, and remaster changes need separate work. Ghidra also logged warnings about uninitialized data reads and non-byte-mapped DVP overlays during PS2 analysis. Successful auto-analysis is an initial inventory, not proof of complete or correct code recovery.

Compiler output loses source details, and `dump.cs` contains declarations without recovered bodies. A behaviorally equivalent decompilation is a plausible project; reconstructing the entire exact original source from fuzzy matching is not guaranteed. [Unity's IL2CPP overview](https://docs.unity3d.com/Manual/scripting-backends-il2cpp.html) and [Il2CppDumper's output documentation](https://github.com/Perfare/Il2CppDumper) describe the native compilation and declaration-recovery stages.
