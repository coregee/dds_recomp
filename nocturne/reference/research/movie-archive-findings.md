# Movie archive lookup

`ps2MovieLookupArchiveFile` at `002bd9c8` has canonical C in
`src/movie_archive.c`. All 9,713 original-instruction/C comparisons pass:
9,685 shipped file paths, sixteen leading-slash paths and twelve directory,
missing, repeated-slash, case-mismatch and boundary paths. Expected record
addresses come from a separate traversal of the original DDS3 index.

The routine searches 12-byte records containing a name offset, location and
signed count. Negative counts identify directories and their child lists;
file locations contribute to the archive base sector. Each component accepts
one leading slash and uses a case-sensitive binary search. The original stores
are preserved even when output pointers overlap the input, sector flag or
archive base global. File names remain original bytes.

The checks execute 11,013,002 original instruction steps and 34,850 MMI
instructions through actual Memcmp, Memcpy and Strcmp bodies. Complete declared
mutable RAM, raw returns, status and primitives agree. The 247,280-byte original
DDT is shared across the batch and remains unchanged. Thirty-two zero backing
bytes model unused aligned-read padding. No per-case index copies are retained.

Coverage reaches 82 of 90 non-delay root addresses. The eight unreached addresses
are the direct `cdrom` dispatch and over-31-byte fatal component branch. The
longest shipped component is twenty bytes. These paths, the disc readiness,
stream seek/read and disc lookup bodies are outside this archive validation
batch. Readiness and stream seek/read subsequently passed the separate
[movie disc comparison](movie-disc-findings.md); direct lookup remains pending.
Disc lookup's FileRpcOpen call leaves A2 live after SearchFile; its correct
operand still needs investigation. The current host hook rejects that path.
Physical disc operation, compiled private-stack layout and a matching PS2
executable remain unverified.

The DDS executable has no full-span candidate for this lookup under the current
relocation mask. Its fatal and memory/string dependencies do have unique body
candidates. The DDS3 record layout and search behavior are useful transfer
evidence; they do not establish an identical DDS lookup implementation.

See `movie-archive-validation.json`, `movie-archive-transfer.json` and the current
`movie-archive/` capture for the focused evidence. The working Ghidra interface
and whole-program export are updated in place.
