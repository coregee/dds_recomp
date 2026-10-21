# Standalone motion callback C recovery

Five complete PS2 leaf bodies have standalone C implementations that compile as C11 with MSVC /W4 /WX /O2 and pass 5,120 comparisons against fresh isolated execution of their actual original instructions. They are not included in the canonical 256-function checkpoint or its 198,684 comparison count.

| PS2 entry | Draft interface | Cases | Original behavior |
|---|---|---:|---|
|002b3b78|sdfMotionNodeBaseInit|1,024|Store raw controller address at node+4, then raw vtable address at node+0.|
|002b4118|sdfMotCLBK_SetCut|1,024|Store the raw cut address at node+8 in the return delay slot.|
|002b4c28|ps2MotionSaveValue60|1,024|Read model address at node+C, copy 16 bytes from model+60 to node+10.|
|002b4c48|ps2MotionSaveValue50|1,024|Read model address at node+C, copy 16 bytes from model+50 to node+10.|
|002b4c68|ps2MotionSaveValue70|1,024|Read model address at node+C, copy 16 bytes from model+70 to node+10.|

The copy interfaces retain provisional offset-based names. The HD position/rotation/scale callback names are leads; their observed copy direction differs. These implementations preserve all 128 bits, including arbitrary raw float encodings and the fourth word. All reads complete before an aliased output is written. Tests include exact source/output alias, adjacent aligned blocks, a source overlapping the node header, disjoint sources, random backed bytes and raw address argument edges.

Every comparison checks the complete 2,048-byte RAM owner, including untouched bytes and guard regions. Eight malformed rows are rejected before native execution. Host allocation and address-translation bindings are restored after every call. Original instruction execution uses the unchanged canonical language; none of these five routines needs the comparison draft or a chosen high-level dependency outcome.

The implementation and compiled library currently live in `drafts/cmp_status_model/`; `motion-leaf-draft-validation.json` pins the source, compiler log, library, capture script, language, original ELF, comparator and vector hash. This is agreement with the isolated instruction model, not a PS2 hardware run, matching binary or complete motion engine. LQ/SQ inputs and outputs are backed and 16-byte aligned; unaligned transfers, MMIO and address wrapping are excluded.

Promotion requires preserving the current 256-function checkpoint, applying the supported entry/boundary repairs on a disposable project, adding canonical types and host interfaces, extending guarded captures, rerunning the complete C regression, reopening the saved ABIs and re-exporting the corpus. The allocator and nonempty seek/blend callbacks remain separate dependencies.

Promoted into the saved261-function checkpoint after canonical capture, combined203,804-case regression, entry repairs and reopened ABI checks. The original standalone results above remain historical evidence; current canonical sources are `src/motion_callback_leaves.c/.h`. See [canonical callback findings](motion-callback-findings.md).
