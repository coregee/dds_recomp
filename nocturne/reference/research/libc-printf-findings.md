# Native printf entry

The complete `002d4748` entry is integrated as `ps2LibcPrintf` in
`src/libc_printf.c`. Its 192 original-instruction/C comparisons pass, including
12 variadic arguments and mixed integer, string, width, double and count
arguments crossing the seven-register boundary. Every one of its 26 non-delay
instruction addresses is reached. The comparisons execute 3,356,587 original
steps and compare complete declared RAM, raw return values, status and ordered
output traces through the recovered formatter and conversion dependencies.

The original 112-byte frame saves a1 through t3 at offsets 0x38 through 0x68.
The argument cursor continues into caller-stack words at offset 0x70. FPR12
through FPR19 are saved at 0x18 through 0x34, before the cursor; randomized
native floating register saves do not supply the consumed formatting words.
The C source uses a real variadic cursor. The Windows host adapter maps its
argument words through a 64 KiB local address window.

The entry publishes the reentrancy context at FILE+84 and calls the actual
stream formatter. DDS has a unique full-span candidate at `003003f0`, with an
agreeing stream-wrapper call and context relocation. This remains static
transfer evidence. Compiled EE stack/FPU layout, physical output and a matching
executable remain unverified.

The Ghidra interface was saved in place, reopened and exported into the rolling
whole-program inventory. See `libc-printf-validation.json` and
`libc-printf-transfer.json` for the current comparison and transfer results.
