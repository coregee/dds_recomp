# Original D3P loading and compatibility conversion

Six complete bodies are integrated in `src/d3p_loading.c`:

| PS2 entry | Recovered interface | Complete static DDS counterpart |
| --- | --- | --- |
| `0015AAD0` | `dds3EffectCreate` | `0014FA30` |
| `0015ADA0` | `dds3EffectLoad` | `0014FD20` |
| `0015AF88` | `dds3EffectDataRevision` | `0014FF28` |
| `00175998` | `dds3EffectPartCreate` | `00162980` |
| `00175C78` | `ps2EffectPartBillboardNormalCreate` | `00162C60` |
| `00175C98` | `ps2EffectPartBillboardAnimationCreate` | `00162C80` |

The serialized descriptor is sixteen bytes: full-word major at zero, minor at
four, reserved word at eight, and raw-float version at twelve; payload follows.
Compatibility conversion examines complete major/minor words. Creation consumes
their low halfwords and uses the original 48-byte major-table rows. Its live
sixteen-byte wrapper stores major, minor, child, and the native default version
1.03. Conversion leaves the serialized version unchanged.

Descriptors older than 1.03 first print their version through the actual
soft-double conversion, printf and newlib allocator, then run compatibility
conversion. Versions through 1.02 receive an identity matrix at child `+B0`
for major zero/one or `+20` for major two. Other major kinds still print the
identity diagnostic without a matrix write. Native VF0 and three PEXTUW
permutations determine the packed matrix; managed defaults are not substituted.

Version 1.0 writes common template size `AC` or special template size `20`.
For expanded particles it first follows the relative pointer and rebinds the
cursor. The subsequent version-through-1.01 path starts from that cursor and
follows another relative pointer. It preserves the original arithmetic order:
end = end * 0.1 * signed duration + start, using raw EE COP1 operations.

Part creation allocates eight bytes, stores only a halfword type at zero, and
puts the actual child at four; the upper two bytes of the first word remain
dirty. Original 40-byte table rows select the constructor. Part zero recursively
loads another D3P descriptor; one creates an animation billboard and two a
normal textured billboard. Remaining part three through six paths are pending.

## Unity and community evidence

[The reference review](d3p-loading-matches.json) checks Unity's creation, loading
and part-creation bodies and four community files at revision
`bec33411543cdc487bad9debdf758f0090a2242c`, retaining links and content hashes.
Unity's named revision method aliases an empty body and supplies no algorithm.

Community [effect manager source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effManager.c)
independently corroborates the 1.03 conversion and 1.02 identity thresholds.
[Descriptor definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_node_descriptor.h)
distinguish serialized full words from creation halfwords. Live-node and
particle definitions provide ownership and clone-marker context. Native
Nocturne instructions decide cursor scope, widths and actual writes.

[All six complete DDS spans](d3p-loading-transfer.json) resolve. Three previously
checked raw dispatcher bodies anchor the major table; the original part-table
prefix constrains the nested loader and two billboard factories. Decoded ELF
REGINFO GP values, five byte-identical constant references, diagnostic strings
and eleven direct calls agree. This is static transfer evidence, not DDS
execution or a matching executable.

## Validation and remaining scope

[934 passing original-instruction comparisons](d3p-loading-validation.json)
reach all 173 main instruction addresses. They exercise all five major routes,
thirteen common, four special and five Magatuhi families, nested part loading,
legacy full-word tags and boundary versions. Actual execution includes 1,200
major/part callbacks, 149 texture uploads, 298 billboard callbacks, 780 declared
emitter frame words, 144 model-track private words and 42 independently checked
RNG advances. Defined
returns, Status, COP1, defined VU/ACC/Q and complete declared RAM agree, with
no uninitialized reads. The original capture executes 5,356,529 steps and 55,540
vector instructions.

The first memory audit exposed printf's `%f` allocator extending the default
heap at `005A0330`, outside the supplied test regions. The fixture now
independently sets sbrk input `0052C2A8` to backed `00900000`, retaining the
existing kernel heap-limit input and running the real allocator. Original
default-heap retail integration remains untested; no captured game result
provides a dependency return, frame word or heap input.

Modern descriptors exercise shared initializer mode four with independently
declared private inputs. Old diagnostics combined with that mode's private
prefix remain an explicit untested interaction. Other parts, unchanged retail
D3P execution, malformed/cyclic/OOM/trapping inputs, physical scheduling and
rendering, a matching binary and full-program recovery remain incomplete.

All six Ghidra interfaces are saved and independently reopened; exports are
merged. [Another 8,544 affected comparisons](d3p-loading-regressions.json) pass
on the same rebuilt host using existing original captures. Recognized body
credit is 828 bytes; complete compared spans total 840 including alignment.

Recovery is now **1,906 / 8,986 functions (21.211%)**, **325,043 focused cases**
and **787,727 aggregate cases** across **143 reports**. Aggregates combine
registered historical captures and are not a new full run.

Expanding the retail bootstrap audit through seven original part-constructor
slots exposes **172 pending recognized bodies / 25,460 bytes**, with zero
missing exports. The inspected prefix does not add native bounds or prove a
complete table extent. Continue real model-root/resource-array construction and
the remaining model/PCP part factories before unchanged retail D3P loading.
One current capture is retained; temporary probe vectors were removed and no
checkpoints or backup copies were created.
