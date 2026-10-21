# EXP / level calculation counterparts and FPU requirements

Reviewed 2026-10-03 from full PS2 ASM/C/JSON, native HD C/JSON and IL2CPP signatures, current EE language sources, installed Ghidra operation sources, existing verifier/source, and read-only executable bytes. Research wrote only this report; a later explicitly authorized step added isolated C/H drafts as recorded below. No canonical source, tests, ledger, Ghidra, emulator settings, or runtime state was changed. The four counterparts are strongly identified; their arithmetic still needs a scoped EE-FPU model before hardware-accurate recovery can be claimed.

The four routines are now integrated in `src/exp.c/.h` and pass 3,584 original-instruction comparisons using the scoped EE value model. The initial research notes below describe the prerequisites at review time. See `exp-and-evolution-findings.md` for current validation and limitations.

## Identities and instruction evidence

| PS2 entry | HD VA / method | Proposed PS2 prototype | Instructions / bytes |
|---|---|---|---:|
| `00223628` | `18227be70` / `rstCalcCore$$cmpCalcLevelUpBaseExp` | `uint32_t cmpCalcLevelUpBaseExp(int32_t level)` | 16 / 64 |
| `00223668` | `182278890` / `rstCalcCore$$cmbCalcLevelUpExp` | `uint32_t cmbCalcLevelUpExp(const datUnitWork_PS2 *unit, int32_t level)` | 48 / 192 |
| `00223728` | `182279850` / `rstCalcCore$$cmbChkLevelUpExp` | `uint32_t cmbChkLevelUpExp(const datUnitWork_PS2 *unit)` | 7 / 28 |
| `00223928` | `18227b460` / `rstCalcCore$$cmbGetLevelUpCount` | `int32_t cmbGetLevelUpCount(const datUnitWork_PS2 *unit, int32_t added_exp)` | 33 / 132 |

All four PS2 JSON exports have completed decompilation. All four HD JSON exports are readable, non-opaque, unique native bodies. Names and signatures are supported by retained behavior, not proximity or fuzzy rank. Note the first method's actual `cmp` spelling. HD's second and fourth declarations use managed unit references (`datUnitWork_t **`); PS2 takes direct inline-unit pointers. Returns are integer V0 values, not F0: HD metadata and unsigned threshold comparisons support UInt32 for the first three, while the count is Int32. PS2 values are low32, sign-extended by MFC1/ADDU in the architectural register; that sign extension must not be confused with a 64-bit return declaration. Base EXP additionally clamps every signed-negative conversion result to zero.

A read-only ELF32 PT_LOAD mapping and independent instruction encoders matched all **104 original instruction words** across these four exports. Original body SHA256s:

| Entry | SHA256 |
|---|---|
| `00223628` | `e0fcebb049e41246a4115d433c3250e2d43eeb7c2ad40e29033aa7ca060317f1` |
| `00223668` | `008ebc66c8fdf40c9e0edb758adddb1f8eb9861b595e9267a4eda0efdc141904` |
| `00223728` | `0aa8336004feb315a774f9504075255656a01722200472ba0cfb1f76d3bef2bb` |
| `00223928` | `fff91423f8518514000f72545da2f5bb21ad454f41d58985f3f6cacdd5eed47e` |

## Exact original constants

At the verifier's established GP `00554170`, the three LWC1 loads select these initialized ELF bytes:

| Address / GP offset | Raw bits | Exact binary32 value | HD field-name lead |
|---|---|---|---|
| `0054e434` / `-5d3c` | `3fb5c28f` | `11911823/8388608` = 1.4199999570846558 | `LEV_UP_NUM_A` |
| `0054e438` / `-5d38` | `3c8b4395` | `9126805/536870912` = 0.016999999061226845 | `LEV_UP_NUM_C` |
| `0054e43c` / `-5d34` | `402ccccc` | `2831155/1048576` = 2.6999998092651367 | `LEV_UP_NUM_B` |

The base routine also constructs exact `c0a00000` (-5.0) with LUI/MTC1. The 2.7 constant is especially easy to mistranscribe: ordinary nearest-rounded `2.7f` is `402ccccd`, one bit higher. Use these original bits or exact hexadecimal values, not approximate decimal literals. The accessor loads A on each base call, and the scaling routine loads B/C once per invocation. Searching all existing ASM exports for these three GP offsets found only these LWC1 reads and no direct stores; this is evidence for the initialized constants, not a proof against arbitrary alias writes elsewhere.

HD's fields are named in `dump.cs`, but its static constructor `182277b70` is an opaque lock/jump body. Their initialized HD values were not established here. The readable scaler's separate multiply-by-100 constant at native VA `1828c74b0` was checked against current GameAssembly disk bytes: `0000c842` = 100.0f. Do not assert that the HD B/C fields have exactly the PS2 bits merely from their names.

## Exact instruction algorithm

Use `I2F`, `MUL`, `ADD`, `SUB`, and `F2I` below to denote individual **original EE operations**, each preserving its register-sized result. They do not denote generic host IEEE expressions. `I2F` consumes signed32 bits; `F2I` produces signed32 bits with the EE conversion rule. `W32` means retain low32 and reinterpret its signed value; unsigned returns preserve those same low32 bits.

`00223628` performs these operations in order:

1. Signed MULT of low32 level with itself; take LO low32.
2. Signed MULT of that low32 result with low32 level; take LO low32 again. There is no saturation or integer-overflow trap; the cube wraps modulo 2^32 before float conversion.
3. MTC1 that signed32 cube into F0, then CVT.S.W into F0.
4. MUL.S F0 by initialized A (`3fb5c28f`).
5. ADD.S the distinct -5.0 operand (`c0a00000`). No fused operation occurs.
6. CVT.W.S, MFC1 into V0, signed test, replace negative V0 with zero in the return delay slot.

Equivalently, while retaining those operation boundaries:

```
cube = W32(W32(level * level) * level)
converted = F2I(ADD(MUL(I2F(cube), A), -5.0))
base(level) = converted < 0 ? 0 : converted
```

No pointers or global work are read by this helper; A is its only memory read. It changes scratch F0/F1/F2 and HI/LO through the arithmetic, and returns a low32 integer.

`00223668` first computes `requested = base(level)`. If `unit->flag & 4` is set, it returns that base unchanged and does not read the descriptor table or hensinmaeexp. Otherwise it obtains unsigned byte D at `003497c0 + 0x3c*unit->id + 5`, using the same established demon descriptor backing. The complete non-flag4 order is:

```
t = MUL(I2F(D), C)
factor = SUB(B, t)                      // held in F20
first = F2I(MUL(I2F(requested), factor)) // first integer truncation
descriptor_base = base(D)
second_product = MUL(I2F(descriptor_base), factor)
difference = SUB(I2F(first), second_product)
second = F2I(difference)                // second integer truncation
return low32(second + unit->hensinmaeexp)
```

The descriptor level remains in A0 across the intervening instructions, so the second call at `002236e0` computes `base(D)` despite having no explicit A0 setup immediately before it. The first converted integer is transformed back to binary32 before subtraction. Thus `F2I(requested*factor - descriptor_base*factor)` is not the same algorithm. D=1 receives no shortcut in PS2: it still performs the baseline arithmetic and adds hensinmaeexp. The final ADDU wraps modulo 2^32 with no sign clamp. The routine explicitly saves/restores F20 through stack+18 and preserves S0/S1/RA. It does not mutate the supplied unit, table or initialized constants.

The relevant fields are `flag` UInt32+0, `id` UInt16+4, and `hensinmaeexp` Int32+d8. The supplied full signed32 level is independent of `unit->level`; it is not narrowed to ushort in this interface. The threshold can return high-bit values after negative-factor arithmetic or final integer wrapping, and its unsigned interface preserves them.

`00223728` loads unsigned16 `unit->level` at+14, adds 1 in the integer register, and tail-calls the scaler. It does **not** store the new level or narrow the addition back to ushort. A stored level FFFF therefore forwards integer level 10000, not 0. It otherwise inherits the scaler's inputs, reads and return semantics.

`00223928` allocates an EC-byte scratch unit inside its 0x110-byte frame and calls the now-recovered `001fef20 cmbCopyCustomDevilToStock(scratch,unit)`. That real dependency copies every EC-byte payload byte, recomputes/clamps scratch resources and ORs scratch flag1. It preserves the original caller's unit. The parent then adds the low32 added_exp to scratch.exp with ADDU, stores the wrapped bits, and executes:

```
count = 0
loop:
    threshold = cmbChkLevelUpExp(&scratch)
    if (uint32(scratch.exp) < uint32(threshold)): return count
    previous_level = scratch.level             // unsigned16
    scratch.level = low16(previous_level + 1)  // happens even at the cap
    if (previous_level >= 255): return count
    count += 1
    goto loop
```

There is no threshold subtraction from EXP, no caller-unit level update, and no last-transition count increment after the cap check. The comparison is SLTU between canonical sign-extended low32 values; its ordering agrees with UInt32 ordering. Starting level254 with enough EXP can count the transition to255, then execute a scratch transition to256 but return1. Starting255 with enough EXP can increment scratch to256 and still return0. Normal starting levels0..255 give count0..255. A negative added_exp is a signed32 interface value whose addition wraps; it must not be replaced by a signed EXP comparison or saturating addition. NULL unit has no checked return path.

The count routine reads the whole source unit through its copy dependency, plus descriptor/constant/skill/global inputs consumed by nested helpers. Its own writes are confined to scratch EXP/level and saved-register stack locations. For validation, compare the complete original unit and accessible global/table buffers; do not claim scratch resource calculation was executed if the copy helper was replaced by a high-level hook.

## Native HD differences

HD's base body uses low32 integer products, unsigned `/100`, subtract5, then signed-negative rejection: `low32(level^3*142)/100 - 5`. PS2 instead wraps the cube before signed float conversion, then multiplies by the original binary32 A. Their rounding and overflow boundaries differ; the HD body is identity evidence, not a substitute for the PS2 formula.

HD's scaler forms an integer percentage `K = trunc((HD_B - D*HD_C)*100)`, multiplies each integer base by K with a widened intermediate, and divides by100. It has no counterpart of the PS2 second float subtraction and conversion. It additionally skips descriptor-baseline subtraction **and the hensinmaeexp addition** when D==1. It uses managed `datDevilFormat.Get(id,true)` instead of the raw PS2 descriptor table, so any edition/event remap belongs to the HD side. Its null checks and `ref` managed parameters are also port differences.

The next-threshold wrapper retains ushort level+1. HD's count retains unsigned EXP comparison, scratch-only changes, cap255 ordering and the same named custom-copy dependency, but inherits the changed threshold calculation and managed field-copy behavior. None of these counterparts prove that EXP numbers are identical between releases.

## Current local arithmetic model and required verification

The workspace `tools/ee-divu-fixed/cop1.sinc` is byte-identical to the installed extension's COP1 file: SHA256 `9f9131405dc937690119daa469659c0b11c35365e89a217d27e7867f510e12a1`. The DIVU fix did not repair FPU semantics. The local definitions at lines112..118,178..180,202..204 map CVT.S.W to generic INT2FLOAT, CVT.W.S to generic FLOAT_TRUNC, and MUL/ADD/SUB to generic FLOAT operations. These arithmetic/conversion definitions neither read FCSR rounding state nor update its flags, flush EE denormals, or implement saturated signed32 conversion.

Installed `SoftwareModeling-src.zip` / `ghidra/pcode/floatformat/FloatFormat.java` establishes what those generic operators currently do: binary32 packing rounds to nearest-even (roundToLeadBit, lines813..862); ADD/SUB/MULT use host-double intermediate operations followed by that packing (989..1038); signed integer conversion also packs nearest-even (1075..1079); FLOAT_TRUNC casts to Java long then masks to the requested output width (1103..1107). Installed `Emulation-src.zip` operation classes delegate to those functions. There is no hidden EE arithmetic override in the current verifier; only two MMI lane user-ops and external diagnostic output are bound.

Existing `ps2_soft_float` comparisons verify explicit bit pack/unpack and encoding conversion routines; they contain no native ADD.S/MUL.S/SUB.S sequence. The double helpers similarly implement compiler-support bit arithmetic, not this native FPU pipeline. `software-float-findings.md` already records that distinction. Therefore those passing checks do not validate the EXP floating operations.

Primary PCSX2 source provides useful requirements, with explicit approximation limits: its default FPU configuration uses toward-zero rounding and flush/denormal settings; its FPU code saturates out-of-range CVT.W, handles EE-specific add/sub operand alignment, and notes multiplication can differ by one mantissa bit even from IEEE toward-zero. This supports a scoped arithmetic audit, not a claim that any single emulator mode establishes console results. [Default FPU settings](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/Pcsx2Config.cpp), [CVT.W and input/underflow handling](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/FPU.cpp), [ADD/SUB alignment and multiplication limits](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/x86/iFPU.cpp), [extended-range and underflow implementation](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/x86/iFPUd.cpp).

For ordinary requested levels0..256 and unsigned descriptor levels0..255, the integer cube stays <=2^24 and is exactly representable at I2F; ordinary intermediates stay finite and far above the underflow range. Flush/exponent255 behavior is therefore not exercised by those original constants. **Rounding and add/sub alignment still matter in this normal domain.** Larger direct Int32 levels can wrap the cube or overflow signed32 CVT.W; expanding the contract requires saturated conversion and exact integer wrapping. No hardware-FPU accuracy should be inferred from a nearest-even P-code comparison merely passing host float C.

Read-only arithmetic demonstrations reproduced the documented generic model and contrasted it with simple IEEE directed-zero rounding; they were not original-instruction executions or console tests:

| Input | Generic nearest-even sequence | Simple directed-zero sequence | HD integer base |
|---|---:|---:|---:|
| base level10 | 1415 | 1414 | 1415 |
| base level100 | 1419995 | 1419994 | 1419995 |
| base level255 | 23545548 | 23545544 | 23545547 |
| base level256 | 23823640 | 23823640 | 23823641 |

For level10, nearest multiplication produces bits44b18000 while directed-zero gives44b17fff, before subtraction. The two simple models differ on72 of levels0..256. Neither directed-zero column includes the EE multiplier's possible additional one-bit error or special add/sub alignment, so it must not be labeled a hardware oracle. Another model-only distinguishing fixture is requested level5 / descriptor level3 / hensinmaeexp0: the preserved first integer conversion gives367, while collapsing the two products into one subtraction gives368 under the current generic nearest model.

## Proposed fixtures and transfer scope

Before comparing recovered EXP C, pin each FPU primitive's rounding/conversion contract with original opcode probes and an independently justified EE model; keep that workspace-only and identify its limits. Preserve operand order for every MUL.S, intermediate binary32 stores, distinct conversion boundaries, the exact 2.7 bits, and F20 restoration. If validation intentionally targets current generic P-code semantics, label it as that scope and keep hardware accuracy separate. A generic float expression with fused/reassociated operations is insufficient.

Suggested original-instruction fixture families after that prerequisite:

- Base: every level0..256; 0/1 negative-result clamps; levels10/20/100/255/256 for rounding boundaries; wider register values with identical low32; negative Int32 inputs; wrapped-cube examples; and a separate positive conversion-overflow case such as level1200, whose float product exceeds INT32_MAX. The last case exposes generic truncation-mask versus saturated EE conversion and is outside the small normal-level contract.
- Scaler: flag4 with a deliberately unbacked descriptor ID proves the descriptor is skipped; non-flag4 backed IDs with D0/1/3/10/99/158/159/255; requested levels0..256; exact initialized coefficient bits; hensinmaeexp0,123,-1,INT32_MIN/MAX and final ADDU wrap; negative factor/negative difference; real base helper calls; complete unit/global/table/constant preservation and F20 sentinel restoration.
- Next threshold: stored levels0/1/98/99/254/255/256/FFFF, with the observed level+1 argument logged; both flag4 branches; unchanged full unit. FFFF forwards10000 before the wrapped cube, so do not narrow this boundary away.
- Count: source EXP one below/equal/one above each next threshold; added_exp0/1/-1 and unsigned wrapping; zero-count and multiple-transition cases; starting levels0/1/254/255; cap ordering above; original-unit/global preservation; execute real custom-copy and threshold helpers. Count loops can exceed the verifier's ordinary20000-step budget because they repeatedly execute the threshold/base calculations, in addition to the initial custom-copy/resource dependency; choose a justified per-entry limit rather than silently cutting the loop short.

The cubic baseline, descriptor-adjusted threshold, custom-copy query and capped transition counter are useful transfer leads across the SMT PS2 library. Reuse the search structure and validation fixture design. For each other executable, independently establish constants, descriptor stride/level offset, flag4 meaning, unit EXP/level/ancestral-EXP offsets, cap ordering, arithmetic instruction sequence and FPU model. Neither the HD numeric port nor matching function names proves shared PS2 addresses, layouts, coefficients or binary equivalence.

## Isolated draft status

Later authorized drafts are `analysis/drafts/exp/exp.c` and `.h`. The four functions reuse current unit/table views and the real custom-copy dependency. The header proposes five raw-bit `EE_FPU_*` primitive declarations with no bodies, and a read-only A/C/B coefficient binding at0054e434; its exact initialized bits and all relevant offsets are asserted/documented. The C preserves unsigned integer wrapping, original COP1 call order, both conversion boundaries, the saved-factor lifetime, unsigned thresholds, aligned scratch-only counting and the cap's increment order. No generic host floating expression or HD percentage formula is supplied. MSVC2022 C11 `/W4 /WX /Zs` passed with canonical src includes. This is syntax validation only: primitive implementation, original-instruction comparisons and integration remain outstanding, with no recovered-routine count increase.

Evidence: `analysis/ps2/whole-program/functions/{00223628,00223668,00223728,00223928}.asm/.c/.json`; native corpus `{18227be70,182278890,182279850,18227b460,182277b70}.c/.json`; `pc/il2cpp/script.json` and `dump.cs` rstCalcCore fields/declarations; original ELF and current GameAssembly disk bytes; workspace/installed `cop1.sinc`; installed Ghidra12.1.2 `SoftwareModeling-src.zip` and `Emulation-src.zip`; current `ExportBehaviorVectors.java`, `src/ps2_soft_float.c`, `software-float-findings.md`; PS2 callers `001fe880`, `0021f788`, `0021f838`, `0021f898`, `002202f8`, `00223258`.
