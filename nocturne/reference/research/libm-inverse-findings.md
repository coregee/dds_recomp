# Native tangent, inverse trigonometry and software square root

Eight complete PS2 bodies are reconstructed: tangent `002CF6B8`, the acos and
atan2 wrappers `002CF730`/`002CF748`, their cores `002CF760`/`002CFB88`, software
square root `002D0118`, tangent kernel `002D0CA8` and atan `002D0F30`. Together
they cover 790 instructions, 3,160 recognized bytes and 3,200 span bytes.
Both strict compilation profiles and independent source review pass.

The [original instruction capture](libm-inverse-original.json) passes all
4,864 authored cases over 737,125 steps. The actual probe and 542-unit main
C each pass all 4,864 cases, comparing every raw F0 result and 6,537,216
declared RAM bytes. Eight native interfaces are saved, freshly reopened and
scoped-exported. The [publication](libm-inverse-publication.json) adds eight
identities: 2,693/9,062 functions and 458,068 recognized bytes. All 540 earlier
objects are unchanged, and all 3,328 retained libm/rotation cases pass.

The first C attempt exposed a harness cleanup error: a fresh shared SP was
zero, which its reset API rejects. Initializing the owned replay stack before
per-case snapshots fixed it. Source, fixtures and comparison assertions stayed
unchanged; the [observation](libm-inverse-stack-initialization-gap.json) and
independent adapter review retain the boundary.

## Native behavior and references

The [HD/community study](libm-inverse-HD-community-study.json) binds eight
primary Newlib sources to revision `1b7c72fdcc4bde7520407d2d3364146f04fb8312`.
They explain the fdlibm lineage and algorithm structure. Original PS2 words
decide the reconstruction: several coefficients differ, and desktop IEEE
special-value handling cannot replace R5900 behavior. The Sun permission
notice is retained in the reconstructed source.

Unity exposes the corresponding Mathf APIs, but the retained HD corpus does
not provide these native SDK implementations. Those names supply context;
they are not eight independently matched Unity function bodies.

The software square root returns the input's raw word for signed zero and
subnormal encodings, before its negative-input test. Positive normal and
extended-exponent inputs execute the original integer bit-restoration loop
and native rounding. It is a separate algorithm from the hardware SQRT
primitive. Acos preserves its native immediate coefficients and exact
arithmetic order. Atan2 takes F12(y) and F13(x), with word-based quadrant and
exponent-difference branches.

The tangent kernel mixes F12/F13 floats with a full 64-bit A0 mode. Its tiny
zero test uses a word increment of the mode, while later comparisons with
one use the full register. Collapsing this argument to an int or float changes
behavior. The source preserves the original private-frame addresses, branch
delay operations and real typed dependencies.

## Validation scope

The [inputs](libm-inverse-inputs.json) are authored without reading captured
outputs. They cover signed zero, both subnormal boundaries, normal and
extended-exponent words, branch-threshold neighbors, raw random words,
signed-axis Cartesian products, equal-mantissa exponent differences around
the native atan2 shortcuts, and 96 tiny-input/full-mode combinations.
There are five unary cohorts of 512 cases, two atan2 cohorts of 768, and
768 tangent-kernel cases.

The original runner executes all selected bodies and their six registered
dependencies. Only reviewed processor primitives supply arithmetic values;
no math function is intercepted or supplied a captured return. The runner
checks saved registers, stack balance and writes outside declared RAM. The
comparison checks raw F0, all declared ordinary RAM and original tables,
Status, FCSR value/condition, primitive counts and restoration of bindings.
Private saved-register frame bytes, complete volatile state, arithmetic
FCSR flags, exhaustive inputs and physical gameplay are separate obligations.

The independent audit observes 702 of 704 non-delay instruction addresses.
The remaining sites are `002CFCD4`, excluded by the preceding two-bit quadrant
dispatch, and `002D0FE0`, whose tiny-atan branch is excluded by the admitted EE
value model. Thirteen COP1 operations occur in folded delay slots and are not
separately visible as step addresses; this includes `002D0FE4` on the excluded
path. All selected non-delay COP1 sites are reached. These are address and
model-specific observations, not exhaustive path or physical-processor proof.

## Transfer to DDS

The [static transfer study](libm-inverse-transfer.json) resolves eight
complete-span counterparts using original code, twelve consistent directed
call relationships and narrowly checked table references. The 52-byte tangent
and 76-byte atan tables are byte-identical across the two executables. Their
surrounding layout is reordered, so the entire 132-byte neighborhood is not
claimed identical. Five-instruction wrappers require call constraints rather
than shape alone. This is static transfer evidence; DDS execution and
recovered DDS source admission have not been performed.
