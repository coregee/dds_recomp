# Original weighted vertex loops and VU0 programs

The complete bodies at `002B6A70` (132 bytes) and `002B6AF8` (196 bytes) are
recovered as first-influence and accumulated-influence vertex routines in
`src/model_micro_skinning.c`. Their raw64 five-argument interfaces are saved,
checked after reopening the working Ghidra project, and present in current exports.
The two C routines include the actual math of their uploaded VU0 programs.

[Independent render research](model-render-helper-leads.json) locates the
original upload at `002B9B80`: channel0 receives the 1,424-byte stream at
`002F1350..002F18E0`. Its NOP/MPG header uploads 177 instruction pairs to VU0
address0. The complete stream is byte-identical in DDS. Entries0 and9 execute
20 of those pairs; other entries are not claimed recovered by this work.

Entry0 weights the normal, transforms position and normal through the supplied
matrices, and weights position XYZ. Its first paired lower instruction saves the
incoming VF2 in VF6. The E-bit on pair7 still executes pair8. Entry9 weights the
new position, transforms the normal and adds both contributions to the previous
output. The E-bit on pair18 still executes pair19. These operations retain each
VU arithmetic boundary, lane mask and ACC-overflow state.

The EE wrappers load four position-matrix vectors and three normal-matrix vectors.
Position inputs occupy 16 bytes, including weightW; packed normals occupy12 bytes
and the original LW sign-extension supplies their fourth word. Output records
have a96-byte stride with position/normal at+0/+10. First-influence prefetch reads
the next inputs even on the last iteration, before stores. Accumulation prefetches
the next inputs and previous output before writing the current record. It retains
the original count0/1 wrapping loops; comparisons use counts2..5 for accumulation
and1..4 for first influence.

[Validation](model-micro-skinning-validation.json) passes1,024 original cases and
all78 measured main instruction addresses. The captures execute3,520 micro calls
and35,264 instruction pairs. Complete declared RAM and140,288 VU/ACC/overflow/Q
values compare, with6,144 independent dyadic scalar oracles,576 overlapping
layouts and128 consecutive first/added-influence sequences. Status, modeled FCSR
condition and native callee saves are checked. The capture helper verifies the
exact original boot image and three original VCALLMS sites before interpreting
its paired instructions; no game function return is replaced.

[Affected regressions](model-micro-skinning-regressions.json) pass8,960 retained
original cases on the rebuilt host. [MIN/MAX primitive checks](vu-minmax-values-validation.json)
also compare both actual C and Java helpers against unmodified compiled functions
from pinned PCSX2:65,878 operand pairs per helper. Raw signed zero, denormals and
exponent255 encodings retain original words. This processor evidence adds no
function recovery credit. It enables remaining lighting/clip helpers.

The render-helper report attributes pinned community definitions, PCSX2 decoder
and MPG sources, and the inspected Unity limits. Both complete EE spans and the
entire upload stream transfer to DDS. The named HD morph/render shims do not
establish this native implementation. Dynamic microcode replacement, pipeline
scheduling, other VU flags and physical hardware are not verified here.

A separate original helper at`002B6BC0` has an unusual branch on the incremented
output argument and stores through the input pointer minus80 bytes. Those words
also match DDS exactly, and the renderer contains a literal call to it. It remains
pending: no asset census or runtime evidence proves that the path is unused, and
the neighboring count-controlled helper is not an acceptable substitute.

Next recover the remaining lighting, clip, buffer and packet consumers, retaining
that original path, before claiming either complete model placement branch.
