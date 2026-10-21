# Nocturne model child updates

`001DCF10`, recovered as `ps2ModelUpdateContextChildren`, manages linked child
models used for trails or blur effects. It creates models through the actual
native constructor, renews their snapshots from a parent, advances their pose,
calculates their colour and submits their meshes. The
[compiled source](../src/model_context_child.c) passes
[256 fresh instruction comparisons](model-context-child-validation.json).
The [publication record](model-context-child-publication.json) binds the reopened interface, current exports, affected comparisons and the passing 413-function baseline of 462,684 retained cases.

## State and ordering

The context caches its parent model and child-state pointer before checking the
spawn count. A nonzero count enables a wrapping 16-bit countdown. When that
countdown reaches zero, the routine decrements the spawn count, resets the
countdown from the cached interval, allocates a 12-byte link and constructs a
model. It reads the previous list head before writing the model's range value,
then publishes the new head before writing the link's model pointer.

| Structure | Offset | Meaning |
| --- | --- | --- |
| Context | `0x0C` | Descriptor with texture and model-definition pointers at `0x14` and `0x18` |
| Context | `0x18` | Parent model |
| Context | `0x30` | Child-state pointer |
| Child state | `0x00` | Linked-list head |
| Child state | `0x04` | 16-bit remaining spawn count |
| Child state | `0x08`, `0x0A` | Reset interval and countdown |
| Child state | `0x0C` | 32-bit renewal lifetime |
| Child state | `0x10`, `0x20` | Four-lane colour gain and slope |
| Child link | `0x00`, `0x04`, `0x08` | Next link, model and remaining lifetime |

The parent colour is sampled once, after any new model is constructed. Each
link's lifetime is decremented with 32-bit wrapping. Zero triggers the full
parent-to-child state copy and a cached renewal lifetime; other values trigger
pose evaluation. The gain and slope are read after that call, and the next link
is read after mesh placement. These distinct cache and reload points matter
when backed structures overlap.

The four colour lanes follow `parent / 128 * (gain + slope * (remaining - 1))`,
followed by multiplication by 128 and integer conversion. The recovered code
preserves the original operation order. Conversion truncates and saturates to
the signed integer range; packing then takes each lane's low byte. There is no
separate clamp to the colour range of 0 through 255.

## Verification

All 99 main instruction addresses are reached; 12 delay-slot instructions
execute within their containing steps. Ghidra's reopened interface has two
64-bit arguments and a void return. The
[extent check](model-context-child-extent.json) records 444 recognized bytes
within the 448-byte span; the only excluded word is unowned zero padding at
`001DD034`.

The cases include 128 spawn inputs, with 64 constructing three nodes, a
material, morph storage and active renderer commands. Existing children cover
renewal and pose paths. Comparisons check declared RAM, 36 meaningful frame
bytes, all CPU upper register halves, VF registers, ACC and its overflow bits,
Q, clip history, FCSR, interrupt status, command-count inputs, callbacks and
the renderer device. They include 325 producer batches and 626 surface
submissions. The stopped-VU value model does not establish concurrent pipeline,
MAC/status flag or physical hardware behaviour.

## Transfer to related games

The [independent evidence audit](model-context-child-leads.json) compares the
complete span with DDS `002174C0`. Only the five call words differ; all other
words agree. This supports transfer of the child loop's layout, ordering and
arithmetic while keeping the called constructor, copy, pose and placement
implementations separate.

Unity HD's `mdlLinkBlur` corroborates the interval, remaining lifetime, renewal
and interpolation roles. Its GameObject cloning and managed child behaviour
do not supply the native memory-copy or mesh-submission implementation.
The community `mdl.h` layouts corroborate the context and child-link fields;
the audit retains pinned source references and their search limits.

The next connected work is context `001DD2C8` and anchor dispatch `001DFC28`.
