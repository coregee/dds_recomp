# Original motion controller recovery

Three complete PS2 routines /568 recognized body bytes are integrated. Current
recovery is **1,790 /8,982 functions (19.929%)**, covering 261,640 recognized body
bytes. The 131 focused reports contribute 298,435 cases; with the earlier full
run, the aggregate is 761,119. These totals include repeated dependency checks.

## References and native behavior

The pinned community DDS [motion source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfMotion.c)
and [state definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_motion.h)
provide independent controller/state leads. Nocturne's original assembly decides
load order, widths, callback selection and arithmetic. Upstream source is read
as reference, not copied, linked or executed. The [reference review](model-motion-control-matches.json)
retains revision, direct URLs and content hashes. Unity names
`ModelViewer$$sdfMotionChange` and `nbUnitProcess$$sdfMotionSeek` both alias the
empty shared body at `1810D6760`; neither supplies an algorithm counterpart.

| PS2 entry | Recovered behavior |
|---|---|
| `002B3E70` | Forward raw controller/cut/type to cut initialization with zero lead and duration |
| `002B3E90` | Store sampling state/current frame, then select actual sample or blend callbacks |
| `002B3FB8` | Apply initialized/running states, advance frames, report completion or repeated loop wrapping |

Sampling compares `frame-start` with duration. It stores the incoming frame
before invoking callbacks. Negative elapsed time supplies blend weight zero;
negative blend callback frames clamp to zero while stored currentFrame retains
the incoming value. Ordinary sampling snapshots the signed request count once;
blending reloads request count and its data pointer after each callback.

Update state1 samples the start frame. State4 adds frameStep to currentFrame and
converts the unsigned frame-count halfword. Nonloop completion samples the last
frame, sets state5 and returns1. Loop wrapping clears blend start/duration,
repeatedly subtracts frame count and returns2. Other seven-state slots and invalid
states return0. Zero-frame looping can remain nonreturning; the source preserves
that path. Returning loop fixtures use positive counts.

## Verification

- [Fresh native capture](model-motion-control/vectors.jsonl.capture.json):
  2,048 cases /949,506 original instruction steps, checked declared RAM writes
  and a clean capture log.
- [C comparison](model-motion-control-validation.json): all 118 selected main
  addresses reached. Full declared RAM, raw returns, Status, callee saves,
  processor primitives, COP1 conditions and ordered callback operands agree.
- All sixteen inspected model/material/morph kinds execute real canonical
  callbacks. The capture contains 5,452 sample/blend calls, 1,619 creation/bind/
  capture callbacks, 160 actual construction/cut-change preludes and 768
  consecutive frame updates. Original factory/vtable/state bytes are unchanged.
- Defined VU/ACC-overflow/Q values are checked across 87,935 vector instructions.
  The colour provider models original VF2..5/ACC clobbers using actual canonical
  MAC operands/results, without supplying game results or memory. Three VF3
  scratch lanes are excluded only when their final writer is the previously
  checked quaternion/Euler helper with implicit CPU-upper-lane transport; all
  remaining vector values stay checked.
- [Affected regressions](model-motion-control-regressions.json): 11,776 existing
  material/morph, creation and basic sampling cases pass on the same rebuilt host
  with current source/verifier/input/vector/DLL hashes.
- [Reopened Ghidra interfaces](model-motion-control-abi.json) pass for all three
  routines, including A0/F12 float sampling. The corrected unsigned-DIVU export
  decompiles three functions and merges the 8,982-entry inventory with zero
  failures. Its temporary language fixup emits the known `rom0` block warning;
  the final export summary is complete. No routine checkpoints are created.

## Transfer and retail assets

The [full-span DDS comparison](model-motion-control-transfer.json) resolves
`002DB518`, `002DB538` and `002DB660`. Four direct/tail-call links agree and all
seven original internal update targets have equal offsets relative to their
respective update bodies. The sample dispatcher's entire296-byte contiguous
span is byte-identical. This is static correspondence, not DDS execution.

The inspected [motion dependency graph](model-motion-creation-frontier.json)
now has zero pending recognized routines and zero missing exports. This covers
the inspected factory/vtable/control prefixes and direct descendants, not the
whole motion system or complete table extents. The overlapping action frontier
still contains377 pending bodies /90,724 bytes; hit effects retain21 /3,692 bytes,
and part/PCP prefixes retain308 /51,192 bytes with seven missing exports.

The new [retail motion census](retail-motion-assets.json) reads the original
DDS3 image in place. Across688 selected model PB/AB files,742 uncompressed MT00
books have checked PAC framing, relocation deltas and motion/key geometry.
They contain6,818 nonempty cuts and978,745 distinct track offsets within books,
using eleven of the sixteen inspected command kinds. No selected record has
unresolved geometry. Seventy-four tracks have nonmonotonic unsigned key times;
their original book/track offsets remain explicit follow-up leads. All74 become
ordered if interpreted as signed halfwords, but the original search uses LHU;
the audit retains unsigned words and records the alternative only as a lead.
No keys are sorted or repaired. These are static findings, not runtime or
comparison credit.

Next, execute selected unchanged retail tracks through real relocation, binding
and frame sampling; investigate those time anomalies and target/model index
associations. Then continue actual hit/model construction and outer scheduling.
Full executable recovery, physical runtime and a matching executable remain
outstanding.
