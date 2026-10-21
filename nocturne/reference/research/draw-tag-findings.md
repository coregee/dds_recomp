# Named Unity draw-tag counterparts

Two existing recovered PS2 routines now have reviewed HD counterparts:

| PS2 entry and canonical alias | Named HD method and native address |
| --- | --- |
| 002acb90 `ps2DmaChainInitialize` | `sdfDraw$$sdfDrawTagInit`,1825e4a20 |
| 002acbb8 `ps2DmaChainAppend` | `sdfDraw$$sdfDrawTagLink`,1825e4bb0 |

The names identify the logical port counterparts. They do not establish original
PS2 symbol spelling or identical representation. The existing C is unchanged;
each routine passed256 original-instruction cases in the last full validation.
Its raw32 custom interface was saved, independently reopened and re-exported.

Initialization resets the same distinctive field cohort and65535 sort value.
The PS2 record is32 raw bytes: next/head/tail at0/4/8, sort storage atchex,
light/fog at10/14hex and two texture slots at18/1chex. The managed declarations
name next/head/tail at10/18/20hex, float z at28hex, light/fog objects at30/38hex
and an object array at40hex. These are storage-role mappings; the original PS2
sort field's source type is still unproved. HD stores65535.0 as477FFF00 and
constructs boxed integer-zero packet values. PS2 writes0000FFFF and raw zeros
in the exact order28/12/0/4/8/16/20/24.

Linking reads the old tail and selects the head when it is empty. Otherwise it
turns the old tail's DMA tag into NEXT and sets its address to the incoming
packet. Both replace the tail with that same packet. HD calls
`sdfPkt$$SDF_DMA_ID(0,2,0)`; its native helper computes20hex, agreeing with the
PS2 byte written at previous+3. The PS2 link address at previous+4 is masked
to28 bits. HD uses a managed packet's dmatag object, type/null checks and64-bit
object references. The explicit-tail variant002acbf0 and packet-plus16/48
variants remain separate, preventing a generic head/tail similarity from being
treated as a unique identity.

The HD ordering-link method1825e4b90 is still a lead. Its three-byte entry routes
through delegate invocation code, including multicast/runtime dispatch, while
the PS2 ordering records carry separate append and mode-sensitive prepend
callbacks. Its metadata name alone does not identify one PS2 body.

This raises reviewed HD counterparts to258 and replaces two PS2-only alias
rows; canonical source remains454 routines. There are193 remaining descriptive
PS2 aliases,46 library identities and137 shared SMT patterns. No fresh full-suite
run, cross-runtime equivalence, physical DMA or matching executable is claimed.

Evidence: `draw-tag-matches.json`, `draw-tag-interfaces.json`, `draw-tag-abi.json`,
the current native corpus and type declarations, and `function-matches.tsv`.
