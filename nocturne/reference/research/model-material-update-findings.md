# Original material updates and texture-coordinate transforms

Six complete Nocturne bodies are recovered in `src/model_material_update.c`:
836 original bytes, with raw integer interfaces saved and checked after reopening
the working Ghidra project. The current whole-program export includes all six.

| PS2 entry | Recovered role | Bytes |
| --- | --- | ---: |
| 002B3940 | Signed-count material list update | 96 |
| 002B37D0 | Current-frame material packet update | 204 |
| 002B3598 | Base fields and primary texture registers | 132 |
| 002B3708 | Primary texture-coordinate transform wrapper | 32 |
| 002B3728 | Secondary state, texture registers and transform | 144 |
| 002B3620 | Six-word texture-coordinate transform builder | 228 |

The material has a pending-change byte at +6 and two packet pointers at +8/+C.
The selected frame tests flag groups 1/4/10/40 shifted by the frame's low five
bits. All tests and the final preserved flags use the original byte, even when
packet writes overlap the material. Updating frame 0 preserves its frame-1 bits;
updating frame 1 then clears them. The existing scalar-pair copy at 002B37B8
executes directly and adds no new recovery credit.

Base copying preserves the original load/store sequence and the texture pointer
read before the first store. The three real getters fetch full TEX1/TEX0/CLAMP
doublewords through texture+28. Secondary copying reads an original unsigned
halfword at 00529438 + mode*2 and reloads the secondary transform pointer only
after the preceding packet writes. No new range checks or caching are added.

The transform builder calls the recovered native sine and cosine routines with
the negated input angle. It retains each COP1 multiply/add/subtract boundary and
operand order, then writes six raw float words. The null-input branch writes
identity. All five input words have been consumed before the first output store;
overlapping input/output is therefore part of the comparison scope.

[The validation](model-material-update-validation.json) passes 2,048 cases and
all 180 measured non-delay instruction addresses. It covers every flag byte for
each frame, signed empty/list counts, texture-present/absent and null transforms,
raw floating encodings, dirty upper argument words and 683 overlapping layouts.
There are 957 independent scalar oracles and 128 consecutive two-frame/update-
again sequences. Ordinary declared RAM, Status and modeled FCSR condition compare;
incidental returns of 384 void chain calls are explicitly excluded.

[Affected regressions](model-material-update-regressions.json) pass 22,176 retained
original cases on the rebuilt host: panel/texture drawing, battle-panel support,
motion sampling, material/morph callbacks, float ordering and draw prerequisites. This is a focused
regression, not a new full-executable or physical-hardware check.

[Independent leads and peer checks](model-material-update-leads.json) attribute
the pinned Megami-Decomps DDS definitions, symbols and inspected source. Its
0x48-byte asset, 0xA0-byte draw entries and 24-byte subparameter layout guide
interpretation, while original Nocturne instructions decide behavior. Unity's
material vocabulary and inspected return-only setter are incomplete leads.

Five selected roots and six dependencies have complete contiguous DDS span
checks, with direct calls, the lookup literal and independently decoded GP
constants constrained. The 16 original lookup bytes match DDS; this does not
prove a declared table extent or valid mode range.

The base-copy semantic peer at DDS 002DAAE0 differs materially: it reads a DDS
global flag and may store zero at packet+10. Nocturne 002B3598 has no such branch.
The corresponding caller is transferable structurally, but this dependency must
remain game-specific. Both original bodies and their differing words are retained
in the small evidence report; no source-equivalence credit is claimed for it.

Complete model placement, rendering, context children and spawn-once update
remain pending. The next connected target is packet-list consumer 002B0CB0.
