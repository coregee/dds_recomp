# File-loader prerequisites

Five complete original PS2 routines are now canonical C: `002a9288`
`ps2MemoryHandleTryAllocate`, `002bf328` `ps2FileJobCreate`, `002be6a8`
`ps2FileJobRelease`, `002bf688` `ps2FileJobReleaseIfTerminal`, and `002bfd60`
`ps2FilePathClone`. They cover 660 recognized body bytes (668 contiguous bytes
including two unrecognized NOP/delay positions).

The fallible allocator is the low-end forward allocator, starting at `577f1c`.
It rounds with wrapped 32-bit addition and signed comparisons, splits through
the actual pool allocator, and returns zero immediately at state 2. Unlike
the ordinary allocator, it never invokes the memory-pressure callback.

File jobs are 64-byte pool records with two doubly linked list pairs, path at
`10`, device/command/status bytes at `14/15/16`, descriptor at `28`, callback
at `38` and payload at `3c`. Construction returns the actual zeroed record,
despite the original default decompiler having inferred a void return.
Release unlinks the completed-job list, wraps its 16-bit count, restores
interrupt state, then releases both path and job. Terminal cleanup tests a
signed byte and only releases states 7 and 8. Path cloning tests full 64-bit
null and calls the actual length, pool, and copy implementations.

All 1,792 original-instruction/C comparisons passed with all 320,924 declared
RAM bytes, defined results, interrupt status and primitive traces compared.
The group uses actual pool allocation/release, strlen, memcpy and interrupt
callees. The string body needed PSUBB/PCPYUD/PAND instruction value callbacks
already used in the full executable comparison; no library or game function
was intercepted. Reviewed outputs include 348 allocation successes, 164
failures, 256 exact job records, 240 path copies, 16 null paths, 96 terminal
frees and 288 terminal rejections. Fixtures cover signed request boundaries,
raw high argument lanes, count wrap, all four list-neighbor combinations,
pool page release versus free-slot insertion and path lengths through 1,023.

The five routines each have one complete DDS instruction-span match. Seven
actual dependency anchors give a 12-body cohort with 18 agreeing call links.
Only explicitly listed call targets and address/GP displacements relocate;
the release count/head/tail triplet is separately constrained. See the current
`file-loader-support-transfer.json` for addresses and exact word indices.
Unity retains the corresponding `libsdf_H.sdfFileCmdHandle_t` fields, supporting
the native record roles. This does not establish an equivalent Unity method
body; no new HD function identity has been promoted.

The remaining loader chain needs device/path resolution (`002bf208` and
`002befc0`), worker initialization (`002bf8f0`), enqueue (`002be5b8`), the
real scheduler (`00297460`) and pump (`002976c0`). These prerequisites do not
yet prove asynchronous file loading or the complete moon initializer. Arbitrary
aliases, malformed unbounded descriptor lists, physical PS2 execution and a
matching rebuilt executable remain unproved. All work updates the current
source, project and rolling evidence in place; no checkpoint was created.
