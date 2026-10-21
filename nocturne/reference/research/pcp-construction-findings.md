# Original PCP construction and initialization

Twenty-four complete bodies /4,928 recognized bytes are integrated in
[`pcp_construction.c`](../src/pcp_construction.c). All 672 comparisons against
unchanged PS2 instructions pass, and all 1,052 main instruction addresses
execute. Saved Ghidra interfaces were reopened and checked; the 24 current
exports are merged. This covers the seven constructors, their wrapper,
descriptor helpers, ramps, record/pair initialization, single-motion wrapper,
charge reset and model/material clones. Complete executable recovery remains
outstanding.

| PS2 constructor | Checked reference role |
| --- | --- |
| `001762F8` | Thunder sphere/vector cells; count*44+100 allocation |
| `00178430` | Thunder fragments; count*12+104 allocation |
| `00179978` | Thunder radiating cells; count*20+88 allocation |
| `0018A460` | Twin effect: eight pairs and eight shared parts, 188 bytes |
| `0018A9D8` | Staggered effect: eight pairs, 152 bytes |
| `0018AE80` | Cross effect: base plus four groups of three parts, 220 bytes |
| `0018B668` | Charge effect: two parts and retained handle, 0x1354 bytes |

The native wrapper at `00175F08` allocates twelve bytes, preserves signed-word
kind/number getters and uses original table `0031DF90`, stride 40. A zero copy
callback at row+12 selects a constructor argument from `0031DDD0[kind][number]`;
otherwise the original descriptor argument goes directly to the constructor.
No table is patched and no native bounds are added. Selected unchanged presets
are tested. Type2's inspected list contains one preset followed by a zero
terminator; adjacent words belong to other data and are not treated as further
type2 presets.

Native prefix copies retain 76/84/72 bytes and snapshot each 32-byte group before
stores. Record strides and unsigned count loops remain unchanged, including
zero-count skips. Type0 stores default colour; type1 also clears its counter;
type2 leaves its colour field dirty. Five-colour alpha rises then falls through
`third,second,first,second,third`, using signed width/5 then SRA1. Six-colour
alpha decreases through `third,second,first,first,second,third`, using width/6.
The ramps have hardware DIVU/DIVU1 zero values without a data-dependent BREAK.
Their positive constant 5/6 guard delays are independently proved unreachable.

Record initialization advances the actual four-word RNG at `00316FE0`.
Type1 stores an unsigned remainder, a second remainder+1 and colour80808080.
Type2 stores three exactly grouped `(RandFloat-.5)+(RandFloat-.5)` coordinates,
then two **integer words**, not floating counters. Zero range inputs execute
the original BREAK7 exception: eight cases check partial writes, advancement
and exception state. The scoped CPU-value adapter pins all new DIVU/DIVU1
opcodes and their dividend/divisor register fields; it does not replace a game
function or supply a captured return.

Composite creation uses the actual descriptor factory and part-copy dispatcher.
Unchanged `hikari.PB` and `field_a.PB` bytes provide real model parts: PAC parsing,
relocation/registration, model roots, motion construction and defaults execute.
Twin/stagger pairs receive random Y matrices through the recovered libm/VU
path; cross parts choose Y/Z and sign from the raw group value, including the
native raw64 signed conversion branch for their index. Motion is initialized
through the actual context/part handles. Charge initialization retains the
original dirty history storage and explicit reset fields.

Model clones create another context for the original group/id and initialize
its defaults. Material-billboard clones copy the actual child, create and
initialize a material, then write both packed identity matrices. The original
private frame sizes and guest addresses are retained for parser/matrix locals.
Caught record exceptions check the entered frame depth before unwinding only
the host test's guest-local transport.

Five named Unity bodies inform wrapper dispatch, the first three constructor
roles and model cloning. Managed allocations, bounds/type checks and storage
differ; the native instructions decide the recovered implementation. The
earlier HD sparkle-sphere/multi-blur/filter guesses for types3..6 are rejected:
those factories create different objects. See [the match review](pcp-construction-matches.json).

Community review at DDS revision `bec33411543cdc487bad9debdf758f0090a2242c`
includes eight attributed files:

- [`effPCPThunder.c`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effPCPThunder.c)
  and [`effPCPMisc.c`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effPCPMisc.c).
- [`eff_thunder_vector.h`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_thunder_vector.h),
  [`eff_thunder_fragment.h`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_thunder_fragment.h),
  [`eff_pcp_staggered.h`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_pcp_staggered.h),
  [`eff_pcp_cross.h`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_pcp_cross.h)
  and [`eff_pcp_charge.h`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_pcp_charge.h).
- [`DDS symbol addresses`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/config/dds1/symbol_addrs.txt).

Reviewed terms, file hashes and community names are retained in the match
review. The twin/stagger/cross/charge source gives useful construction/layout
context independently of Unity. No upstream implementation is executed or
adopted wholesale.

[Static DDS transfer](pcp-construction-transfer.json) resolves all 24 complete
spans, with 80 direct-call constraints, seven original constructor slots and
three independently decoded, byte-identical GP angle constants. Six missing
wrapper/initialization matches are checked word-by-word: only enumerated table
addresses, RNG-state addresses, GP immediates and constrained calls differ.
Two otherwise generic LW getters are resolved by their original incoming
wrapper calls. Static matching does not establish DDS runtime or a matching
rebuilt binary.

[Focused validation](pcp-construction-validation.json) includes 64 preset
dispatches, 176 actual constructor-entry observations,501 part factories,
1,050 copy/scale callbacks, 6,098 motion callbacks, 6,929 PAC callbacks and 4,816
command-frame input words. All 128 VU words plus ACC 4/overflow 4/Q are compared:
92,064 values and 227,251 original vector instructions. Independent input-based
advancement checks cover 2,182 RNG calls. There are 272 cases containing unchanged
retail PB data, 304 actual caller preludes and 11,728,819 original execution steps.

Every selected main address executes. Four constant-divisor BREAK instructions
are delay instructions excluded from that main-address count, with their
separate proofs retained. [The annotation correction](pcp-construction-coverage-annotation.json)
records this distinction without changing any capture execution input or
rewriting the original capture metadata. The constructor-entry observer now
has its own list, so simultaneous cleanup observations retain their meaning.

The larger composite fixtures use eight backed native reserve-page records;
the actual allocator consumes them. A host reverse-address bridge now follows
the active model/PAC mapping consistently with forward lookup. Temporary abort
and callback diagnostics were removed before the final DLL build and comparison.
[Targeted regressions](pcp-construction-regressions.json) pass another 16,368
retained cases on that ordinary final build: memory 496, matrices 2,048,
libm 3,328, pose 6,144 and polygon prerequisites 4,352.

The captures establish bounded instruction/C agreement, not physical execution,
address-error exceptions for byte-misaligned source fixtures, pipeline timing,
full asynchronous worker scheduling or a matching executable. Original input
tables remain unchanged, unchecked native domains remain unchecked, and no
game outputs are injected into recovered code. Recovery is 2,066/8,992 (22.976%),
305,228 recognized integrated bytes, 154 focused reports and 336,067 focused
/798,751 aggregate comparisons. Continue native worker arrivals, larger retail
model lifecycles and remaining PCP update/copy/release callbacks. The current
constructor bootstrap closure has one pending body /192 bytes (`001DE220`),
with no missing exports;this does not include every effect lifecycle callback. One rolling
capture is retained; no checkpoints or backup copies are created.
