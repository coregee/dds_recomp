# EE FPU value model for the EXP routines

Reviewed 2026-10-03. The four original bodies in `next-exp-leads.md` can use five deterministic raw-word primitives: signed `CVT.S.W`, saturated `CVT.W.S`, ordered `MUL.S`, `ADD.S`, and `SUB.S`. A pinned integer PS2Float reference supplies the missing multiplier behavior; ordinary IEEE directed rounding alone does not. Preserve every original instruction boundary and operand order. The HD integer percentage formulas remain identity evidence, not PS2 arithmetic.

The implemented host provider and Java adaptation now agree on **140,000 primitive probes** and match **172 published PS2 capture cases**, with zero mismatches. These are two distinct evidence classes. No original EXP instruction execution, FCSR equivalence, timing equivalence, or new console measurement is claimed by this report. The subsequent isolated instruction run is still required.

## Pinned primary sources and provenance

| Repository | Examined commit |
|---|---|
| PCSX2/pcsx2 | `81526d4dc7cc70e4ae75abb35a789417456c6d43` |
| libretro/ps2 | `6eabf2242d451ee2e6d52b1e3f10efb77143ed05` |
| TellowKrinkle/PS2Float | `a5b2c0c80312e2582143fa801a25f4c4984fbe08` |
| unknownbrackets/ps2autotests | `97469ffbed8631277b94e28d01dabd702aa97ef3` |

GitHub API metadata was read without repository mutation. The workspace reference C/H exactly matched the pinned libretro bytes, including these SHA256s: C `90f6a70ba391e1ed5d604613c1a2b27200d1bc80dcb6d33e49cfd015aa2f2001`; H `6300850df74363f5b7f488b22743fdac637ac56c9e3290e2aeab522733065cf0`. Cached web views had different line counts; citation anchors below were checked against the pinned raw files.

Libretro's README reports 31.9 million comparisons against a hardware-derived research reference. That is the project's provenance claim, not 31.9 million hardware captures inspected here. Its header and actual API provide integer arithmetic and packed result/exception words, but **no CVT API**. The fork's interpreter still casts for conversion. [Model claim](https://github.com/libretro/ps2/blob/6eabf2242d451ee2e6d52b1e3f10efb77143ed05/README.md#float-accuracy-the-ps2float-work), [actual header](https://github.com/libretro/ps2/blob/6eabf2242d451ee2e6d52b1e3f10efb77143ed05/pcsx2/ps2float.h).

TellowKrinkle's research repository describes itself as a future PCSX2 JIT reference. Its scalar Booth tree matches the libretro correction. Its executable accepts external raw result datasets and contains fixed vectors; the README/main do not identify a complete public hardware dataset for all operand pairs. [Purpose](https://github.com/TellowKrinkle/PS2Float/blob/a5b2c0c80312e2582143fa801a25f4c4984fbe08/README.md), [test harness](https://github.com/TellowKrinkle/PS2Float/blob/a5b2c0c80312e2582143fa801a25f4c4984fbe08/main.cpp#L71-L93).

The separate ps2autotests project explicitly supplies tests run on PS2 and accompanying results. Its `convert.expected`, `arithmetic.expected`, and `muldiv.expected` are the capture oracle used here. `shared.h` resolves every named operand. [Capture provenance](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/README.md), [aliases](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/ee_fpu/shared.h#L7-L17).

The preserved libretro source carries LGPL-3.0-or-later notices; keep it and its license separate from recovered game code. PS2autotests supplies its own permissive notice. A port of the Booth tree retains its reference provenance/license; calling it an independent rewrite would overstate independence. [Reference notices](https://github.com/libretro/ps2/blob/6eabf2242d451ee2e6d52b1e3f10efb77143ed05/pcsx2/ps2float.c#L1-L14), [capture license](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/LICENSE.md).

## Why generic P-code and upstream arithmetic are insufficient

Local `tools/ee-divu-fixed/cop1.sinc` maps ADD/MUL/SUB to generic FLOAT operators at lines45,178,202, and CVT to INT2FLOAT/FLOAT_TRUNC at112/117. Those definitions do not implement directed conversion, saturated conversion, the alignment mask, or the Booth correction. `next-exp-leads.md` documents Ghidra's nearest-even packing and Java truncation/masking. Existing software encoding tests do not execute these native operations.

PCSX2's default FPU control selects chop/zero and flush/denormal handling. Its CVT recompiler uses host conversion with explicit positive saturation. Its ADD/SUB masks the smaller operand according to exponent distance, retaining one guard bit. Its MUL helper performs a host multiply plus one special ordered game fix; the comment says PS2 multiplication can be noncommutative and one mantissa bit lower. [Defaults](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/Pcsx2Config.cpp#L31-L41), [CVT](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/x86/iFPU.cpp#L972-L1027), [alignment and approximate MUL](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/x86/iFPU.cpp#L391-L538).

The double implementation explicitly identifies MUL as inexact. Wider host intermediates recover extended exponent range but cannot recreate discarded carries. Neither upstream interpreter casts nor its ordinary recompiler is an independent exact multiply oracle. [Declared limits](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/x86/iFPUd.cpp#L14-L21), [double conversion](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/x86/iFPUd.cpp#L165-L250), [interpreter conversion](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/FPU.cpp#L250-L258).

## Implementable raw-word algorithms

Let `S=x&80000000`, `E=(x>>23)&255`, `M=(x&7fffff)|800000`; all words below are hexadecimal encodings, not host floats.

**CVT.S.W:** interpret the input as signed32. Form its unsigned absolute magnitude using modular subtraction, which handles INT32_MIN. Zero returns +0. Find top bit `k`; retain the leading24 bits by shifting right `k-23` when positive, otherwise shift left. Pack sign, exponent `k+127`, and low23 retained bits. Discarded bits never cause an increment. **CVT.W.S:** return0 for E<127; saturate to signed INT32_MIN/MAX for E>=158; otherwise shift M by `E-150` and apply sign with modular subtraction. These integer algorithms avoid host casts/fenv. The published conversion captures confirm truncation and the signed limits. [Conversion results](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/ee_fpu/convert.expected#L2-L66).

**ADD/SUB:** SUB first flips the second sign. For finite normal inputs, order by magnitude, retain one guard bit (`M<<1`), align the smaller unsigned mantissa by exponent distance, and conditionally subtract it. Distances>24 contribute zero. Normalize the resulting unsigned magnitude and truncate to24 significant bits. Exact cancellation returns+0; zero operands need the reference's signed-zero rules. This is an integer equivalent of clearing `distance-1` low operand bits before host RTZ addition. Use the full pinned reference for denormals/extended exponent/flags, rather than extrapolating this normal-path description. [Integer adder](https://github.com/TellowKrinkle/PS2Float/blob/a5b2c0c80312e2582143fa801a25f4c4984fbe08/ps2add.cpp#L36-L66).

**MUL:** keep Fs as multiplicand and Ft as recoded multiplier. Compute their full48-bit significand product and the reference's eight Booth recodes/carry-save reduction. The reduced low-word tree determines a bit15 discarded-carry correction: subtract `((tree_low XOR full_product)&8000)` before normalization. Shift23, shift once more if bit24 is set, adjust exponent, and retain low23 fraction bits. Apply XOR sign, exponent-zero signed-zero handling, underflow flush, and signed maximum overflow as specified by the reference. **Do not decrement every result**, swap operands, or remove a multiply by1. [Ordered tree and packing](https://github.com/TellowKrinkle/PS2Float/blob/a5b2c0c80312e2582143fa801a25f4c4984fbe08/ps2mul.cpp#L16-L94), [preserved C implementation](https://github.com/libretro/ps2/blob/6eabf2242d451ee2e6d52b1e3f10efb77143ed05/pcsx2/ps2float.c#L161-L236).

## Concrete EXP scope and ordering

The initialized coefficient words are A=`3fb5c28f`, C=`3c8b4395`, B=`402ccccc`, with distinct -5=`c0a00000`. The following ordered pairs are taken directly from the original ASM:

| Instruction address | Primitive inputs, in Fs/Ft order |
|---|---|
| `22364c` | I2F(wrapped signed cube), A |
| `223650` | preceding product, -5 |
| `2236cc` | I2F(unsigned descriptor D), C |
| `2236d0` | B, preceding product |
| `2236d4` | I2F(requested base), saved factor |
| `2236fc` | I2F(descriptor base), saved factor |
| `223700` | I2F(first converted integer), second product |

All signed32 level inputs first wrap their cube to signed32. Its converted magnitude is <=2^31; the baseline product is below2^32. Saturated base returns are <=INT32_MAX, D is0..255, and factor lies approximately -1.635..2.7; later products remain below2^33. The initialized coefficients and integer inputs therefore keep this pipeline in ordinary finite range, with zero handled explicitly. Exponent255/underflow arithmetic is not needed to explain these routines' values. This bounded inference does **not** eliminate rounding, cancellation, multiplication correction, or integer saturation. Mutated coefficient bindings would expand the scope.

The first F2I followed by I2F must remain before the final subtraction. Keep the saved factor across the second real base call, restore original F20 in instruction emulation, and preserve low32 final ADDU wrap. Count must execute the real custom-copy dependency and retain unsigned threshold comparisons/cap ordering.

For full architectural side effects, arithmetic also changes current/sticky FCSR flags. The current C/Java providers intentionally return only value words. The routines do not read FCSR, so this is a useful value/memory recovery scope; it is not a complete architectural FPU replacement. Any claim about caller-observable FCSR preservation needs additional modeled flags and register-state checks.

## Isolated userops, probes and current evidence

In a new workspace-only language directory, define five raw-word userops and replace only these COP1 constructors: `fd=_ee_cvt_s_w(fs)`, `fd=_ee_cvt_w_s(fs)`, `fd=_ee_mul_s(fs,ft)`, `fd=_ee_add_s(fs,ft)`, `fd=_ee_sub_s(fs,ft)`. Bind callbacks using the current `registerCallOtherCallback` pattern, read4-byte input words unsigned, and write exactly4 bytes. A fresh `ProgramDB`/mapped original ELF prevents live analysis context or language mutation. Inspect the emitted CALLOTHER operands/output to prove order and width; fd aliasing Fs/Ft must consume both inputs before the write.

Probe every original conversion/arithmetic site with destination/source aliases and sentinel FCSR/F20, then execute the four intact bodies with their real nested helpers. Primitive fixtures should include signed zeros, conversion boundaries, alignment distances0/1/23/24/25, both signs, near cancellation, exact/sub-ULP products, and reversed MUL pairs. Published capture anchors include:

| Capture operation | Input words | Expected result |
|---|---|---|
| CVT.S.W | `7fffffff` | `4effffff` |
| CVT.S.W | `80000000` | `cf000000` |
| CVT.W.S | `4f000000` | `7fffffff` |
| CVT.W.S | `cf000000` | `80000000` |
| CVT.W.S | `3fc00000` / `bfc00000` | `00000001` / `ffffffff` |
| MUL | `3fffffff`,`3f800000` | `3fffffff` |
| MUL reversed | `3f800000`,`3fffffff` | `3ffffffe` |
| ADD | `80000000`,`80000000` | `80000000` |
| SUB | `3f800000`,`3f800000` | `00000000` |

The asymmetric MUL cases come from `muldiv.expected` and the CF aliases; they do not rely on the newer research model. [MUL captures](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/ee_fpu/muldiv.expected#L279-L314), [ADD/SUB captures](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/ee_fpu/arithmetic.expected).

`tests/validate_ee_fpu.py` called all five exports from the rebuilt host DLL, checked every named alias against `shared.h`, and passed all172 capture result words: CVT.S.W32, CVT.W.S32, ADD36, SUB36, MUL36. It then passed all140000 Java/C rows: 10000 per conversion/ADD/SUB and100000 ordered MUL. `analysis/ee-fpu-validation.json` separately records both results and SHA256s for captures, notices, reference, backend, Java source/probes, validator and DLL. This run excludes FCSR/exception flags; a zero mismatch count is not an exception-state validation. The Java adaptation is a second implementation of the same research algorithm, so differential agreement establishes implementation consistency, not an independent hardware oracle for unrecorded cases.

Useful next routine fixtures are exhaustive base levels0..256, D0..255 with requested levels around both conversion boundaries, D158/159 factor sign change, full signed32 wrap/saturation examples, flag4 descriptor bypass, ancestral EXP wrap, ushortFFFF forwarding10000, and count thresholds just below/equal/above. Store intermediate raw words in isolated probe logs so numeric differences can be attributed to an original opcode. Keep the recovered-routine promotion evidence tied to that instruction run rather than to primitive model agreement alone.
