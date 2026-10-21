# Native float libm and effect rotation dependencies

The later [context/effect investigation](model-context-anchor-findings.md)
adds frame-aware working replacements for all ten selected math bodies.
Their original private frames affect inputs that overlap saved stack slots,
which this earlier value/declared-RAM proof did not compare. All 1,280
axis/direct cases pass, including each case's entire actual used stack window
(290,720 bytes total). Another 2,816 retained cases pass across eight libm
bodies. The published canonical library remains unchanged. Full volatile
processor state, unexercised paths and broader context integration remain open.

Ten complete source bodies /4,736 original bytes are integrated:
cosine, sine, their polynomial kernels, both pi/2 reducers, floor, power-of-two
scaling and Y/Z rotation matrices. [Recovered source](../src/libm_trig.c),
[interfaces](libm-trig-interfaces.json) and [validation](libm-trig-validation.json)
retain the original float registers and the native instruction/value contract.
The ten saved Ghidra interfaces were reopened and checked; all ten exports were
merged into the working inventory.

The constructors at `0018A460`, `0018A9D8` and `0018AE80` depend on these matrix
builders. Their scalar sine/cosine dependencies were unresolved, so this work
addresses that prerequisite before recovering the composite effects. None of
the seven PCP constructors receives credit from this library work.

## Source lineage and native differences

Eight files from the [Newlib mirror](https://github.com/mirror/newlib-cygwin/tree/1b7c72fdcc4bde7520407d2d3364146f04fb8312/newlib/libm)
were inspected at revision `1b7c72fdcc4bde7520407d2d3364146f04fb8312`: float
sine/cosine wrappers, both polynomial kernels, both pi/2 reducers, floor and
scalbn. The Sun Microsystems permission notice is preserved in the adapted
source. [The reference review](libm-trig-matches.json) retains links, revision,
hashes and representative original instruction checks.

The float algorithm structure agrees, but the original executable decides
constants and operations. Several native coefficients differ by one bit from
upstream, including cosine C1, sine S1/S6 and the split pi/2 corrections. Native
`Q0 == 0` reduction shifts by eight rather than upstream seven. Native scalbn
preserves zero/denormal encodings on its early return, treats exponent 255 as a
normal exponent and uses the original huge/tiny multiply paths. No IEEE-only
special case, host trigonometric result or managed Unity behaviour is imported.
Unity's Mathf/transform APIs provide context without an exact native identity.

All arithmetic uses the existing reviewed EE instruction primitives in native
operand order. Host wrappers only transport float register encodings to the
actual recovered functions. No libm/game function is intercepted, replaced by
a lookup of captured outputs or supplied an original return value.

## Validation and remaining paths

The current capture and C comparison pass 3,328 cases through 2,401,557 original
steps. Cases include signed zero, denormals, extended exponent encodings,
polynomial thresholds, small/special/medium/large reductions, carry and
recomputation, selected precision routes, floor/scalbn boundaries and actual
Y/Z matrices. A directed EE-primitive search around pi/2 multiples found inputs
that execute the rare third reduction pass; those raw input words are retained
in the fixture generation.

The comparison checks declared RAM and defined returns, Status, the FCSR
condition bit, all 32 VU registers, ACC/overflow and Q. That is 455,936 defined
vector/ACC/Q values, including VF28..31 matrix outputs, and 4,096 original
vector instructions. FCSR exception flags, hardware timing and physical
execution are outside this value-model verification.

There are 972 executed main addresses out of 1,001. Three intrinsic dispatch
addresses have independently checked dead-path proofs: two quadrant fallbacks
after `ANDI 3` and the tiny-sine fallthrough after fixed-RTZ conversion to zero.
**Twenty-six reducer addresses remain unvisited**, explicitly listed in the
report and interface specification. They include extended-precision compaction
loops and out-of-domain dispatch paths. Their source is preserved; the finite
capture is not presented as an absolute unreachability proof or complete path
coverage. The only currently recognized direct caller supplies precision 2;
the original defined JK choices are 4/7/9, with zero in the adjacent precision-3
word. No table values were changed to force coverage.

Only the actual libm constant block and backed input/output arrays are declared
for this capture. The write guard permits the ordinary private stack and rejects
other RAM writes. This replaces the unnecessary inherited model RAM capture
with a roughly 30 MiB rolling vector file. There are no duplicate assets,
checkpoint copies or retained versions of the discarded larger capture.

## Shared SMT evidence and current boundary

[All ten complete DDS counterparts](libm-trig-transfer.json) resolve through
24 call constraints. Four original constant tables are independently identical
across both executables: 198 eight-bit 2/pi words, 32 pi/2 high words, JK plus
the adjacent precision-3 word, and eleven split-pi/2 words, totalling 980 bytes.
These are complete static code/data comparisons, not DDS execution or a
matching-executable build.

Another 6,640 retained original cases pass on the same current DLL: 496 model
memory/colour cases and 6,144 pose/VU cases. [The regression record](libm-trig-regressions.json)
keeps those report hashes and their validation scope. No unchanged broad/full
capture was repeated.

Recovery is 2,029/8,992 functions (22.565%): 333,347 focused /796,031 aggregate
cases across 152 reports. The inspected model bootstrap now has 24 pending
bodies /4,892 bytes, no missing exports. Continue the seven actual PCP
constructors and their prerequisite gradients, part descriptors, initialization
and matrix dispatch, then larger retail bundles and external-worker delivery.
The reducer's recorded path gaps, whole-program execution, physical runtime and
a matching executable remain outstanding. Work stays in place without backups
or checkpoints.
