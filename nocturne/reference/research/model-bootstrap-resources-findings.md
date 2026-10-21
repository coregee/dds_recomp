# Texture cloning and model resource ownership

Twelve complete native bodies are integrated in `src/model_bootstrap_resources.c`:

| PS2 entry | Recovered interface | Complete DDS counterpart |
| --- | --- | --- |
| `002B2BD0` | `ps2ModelTextureListClone` | `002DA118` |
| `002AB448` | `ps2TextureDescriptorClone` | Distinct variant, `002D2800` |
| `002AB308` | `ps2TextureRefreshPalette` | `002D26A8` |
| `001DC158` | `ps2ModelFindRegisteredResource` | Unresolved |
| `001DC188` | `ps2ModelIsPending` | Unresolved |
| `001DC1D8` | `ps2ModelMarkPending` | Unresolved |
| `001DF460` | `ps2ModelResourceListCreate` | `00219CC8` |
| `001DF290` | `ps2ModelResourceAppendBillboard` | `00219AF8` |
| `001DF2E8` | `ps2ModelResourceAppendEffect` | `00219B50` |
| `001DF348` | `ps2ModelResourceAppendMovie` | `00219BB0` |
| `001DF3D0` | `ps2ModelMovieResourceRelease` | `00219C38` |
| `001DF480` | `ps2ModelResourceListRelease` | `00219CE8` |

Texture cloning copies the descriptor in two staged 32-byte groups, retains its
primary resource, and keeps source `+8` or substitutes the original descriptor
address. It clears the cache, retained-palette and intensity-map pointers,
registers the new descriptor, and, when a palette exists, allocates fresh VRAM
and staging storage, copies the referenced source palette, and sets colour
`80808080`. A real register cache and DMA palette upload are built. List cloning
uses the signed halfword count at `+4`, four-byte elements and growth four.

Registered-resource heads are at Nocturne RAM `0032C458`; pending heads are at
`0032C478`, each indexed by major times four. Registered lookup compares an
unsigned halfword at node `+A` with the full incoming minor register. Pending
lookup compares a sign-extended word at `+4` with that register. Prepending an
eight-byte pending node permits duplicates. Raw upper register words remain
observable and are tested.

The typed resource list has sixteen-byte records and growth four. Kind zero
creates an animated billboard through `dds3BillboardCreate(1, source)`; its
source argument is the incoming A1 retained by the native appender. Kind one
loads a real D3P object. Kind three allocates a zeroed `AC`-byte movie owner,
storing its first word, memory handle and callback at `+0/+4/+10`. Appenders
use a signed count to locate the record and an unsigned halfword to increment
the count. Release reloads that signed count after each child, dispatches kinds
zero/one/three, skips unknown kinds and frees the actual array allocation.
Movie byte `+9` controls cleanup of the decoder at `+20`. Slots are not cleared.

## Ownership and private inputs

The generic particle initializer skips cached-billboard construction when input
`+28` is minus one, retaining the copied billboard pointer at `+F4`. That borrowed
input from earlier construction-only tests cannot be treated as an owned
allocation during release. Mixed-release tests select the real cache-clone
path; a live shared cache reference remains after the new owned billboard is
destroyed. Animated billboards use an actual P2A resource rather than a null
resource. This validates the allocation/release path without substituting game
returns or inventing allocated input pointers.

The palette upload's handle word is unassigned on the pool path. Both palette
wrappers restore their frames before tail calls, so a standalone image frame
places this word at incoming SP minus `5C`. Those words are supplied explicitly
before execution. In selected clone cases, the earlier VRAM-split path reaches
an allocator frame at SP minus `90`; its saved RA at `+10` supplies the high
word at SP minus `7C`. The later clone/image frame reuses that location for its
header, so the retained word is zero. Later staging/copy/cache calls preserve
it. All **214 actual original upload-word observations** agree with these
independent inputs. Captured observations are not fed back as expectations.

Constructor returns and derived object fields bind later test calls using each
execution's own runtime values. The original memset routine initializes caller
flags and an unknown record tag through a guest-address adapter. Thirty-two
resource-list cases construct, append a movie owner and release the list in
one connected sequence; mixed-release tests also execute real billboard/D3P
allocation and destruction. Inactive decoder cleanup is exercised with an
initialized empty decoder registry; active IPU destruction is not claimed.

## Community and Unity references

[Five pinned community files and Unity type context](model-bootstrap-resources-matches.json)
are reviewed with hashes and inspected revision. Community
[texture code](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfTex.c)
and [SDF definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf.h)
provide palette/cache and reference context. The
[model manager](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/model/mdlManager.c),
[model types](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/mdl.h)
and [resource-entry API](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/mdl_resource_entries.h)
connect resource cloning to model-context ownership. Unity's loading-tag and
resource-list types provide context; no named HD routine equivalence is claimed
for these twelve native bodies.

[Eight complete DDS spans](model-bootstrap-resources-transfer.json) match with
twelve agreeing call constraints. The matching list-clone caller independently
points to DDS `002D2800`, a 336-byte texture-clone variant versus Nocturne's
312-byte body. DDS additionally allocates a zeroed eight-byte reference object,
stores reference count one at its `+4`, and installs its pointer at texture
`+8`. Nocturne makes no such allocation. This explains why the reviewed
community reference-object type must not be imported directly into Nocturne's
clone. The variant remains separate from resolved equivalent spans. Three
registry helpers have no selected full-body match; DDS execution is unproved.

## Validation and next work

[864 original-instruction comparisons](model-bootstrap-resources-validation.json)
pass, reaching all **292 main addresses** over **468,586 original steps**.
There are 224 real allocation/initialization preludes, 214 palette uploads,
80 effect constructors, 96 billboard factory callbacks, 640 vector instructions
and 240 COP1 arithmetic comparisons. All declared RAM, defined returns,
Status, COP1, defined VU/ACC/Q and allocator primitives agree. No uninitialized
reads or undeclared writes are reported. The selected inputs include null/empty
lists, bounded positive counts, source-reference forms, both palette formats,
raw lookup operands, duplicates, unknown tags and owned mixed release.

All twelve interfaces are saved in Ghidra and independently reopened; exports
are merged. [7,686 affected regressions](model-bootstrap-resources-regressions.json)
pass on the same host using retained draw, D3P, particle-release and emitter
captures. The shared emitter check now locates its fixed descriptor-table range
by address rather than mistaking a newly appended mutable registry range for
that table. Recognized body credit is **1,384 bytes**; full spans total **1,392
bytes**. No new full-suite run is claimed.

Recovery is **1,947 /8,986 functions (21.667%)**, **327,859 focused cases**,
**790,543 aggregate cases**, and **147 reports**. The inspected bootstrap has
**48 pending bodies /5,896 bytes** with zero missing exports. Continue full model
acquisition `001DCAB8`, its blocking wrapper `001DCCE8`, outer construction
`001DD0D0`, remaining model/PCP factories and unchanged retail relocation and
execution. Negative clone allocations, malformed ownership, exhaustion,
complete asynchronous/retail lifecycle, physical rendering/timing and a matching
executable remain unproved. Rolling outputs are saved without checkpoints.
