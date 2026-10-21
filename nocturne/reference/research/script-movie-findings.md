# Script VM values and movie commands

Six complete routines now compile and pass 768 original-instruction/C comparisons:

| PS2 entry | Recovered function | Recognized bytes |
| --- | --- | ---: |
| 0010b5c8 | scrGetIntPara | 188 |
| 0010b790 | scrSetIntReturnValue | 20 |
| 0022b880 | mviScrCmd_MOVIE_PLAY | 40 |
| 0022b8a8 | mviScrCmd_MOVIE_STOP | 32 |
| 0022b8c8 | mviScrCmd_MOVIE_CHK | 40 |
| 0022b8f0 | mviScrCmd_MOVIE_CHKDRAW | 36 |

The current VM work pointer is 00551c78. The integer getter subtracts the
low argument word from the count at work+1c, reads the signed type byte at
work+1f+cursor, and addresses the value at work+3c+4*(cursor-1). All address
arithmetic wraps at 32 bits. Tags 0 and 4 return a sign-extended integer;
tag 1 converts a raw float word; tags 2 and 3 index the global integer and
float tables at context+40 and context+440, with context read from 0054ea20.
Unknown tags, including negative signed-byte tags, return zero. The five
original jump-table targets at 0052f550 are checked directly against the ELF.

The setter writes zero to work+3b, reloads the current work pointer, then
stores the low result word at work+a8. Sixteen alias cases make the first
store change the work pointer itself; they confirm that the second access
uses the reloaded pointer. Getter cases independently check expected integer
values, including wrapped count/index arithmetic, signed returns, float
truncation, saturation, infinities, NaNs and subnormals.

PLAY calls the actual getter with argument zero and the actual indexed movie
manager, then returns one. STOP executes the actual close/process shutdown
path and returns one. CHK stores the inverse of the actual movie-end predicate
into the VM return slot and returns one. CHKDRAW returns whether the actual
draw-state byte at 00343e74 equals two; it does not write the VM return slot.
The independent end predicate covers endbyte+33 and pendingbyte+3e combinations.

All 71 non-delay root instruction addresses execute across the six routines.
The comparison executes 503,446 original steps and compares full declared RAM,
defined raw64 results, Status and 36,546 ordered event words. Movie initialization,
close, pool allocation/free, process construction/list operations, callbacks and
diagnostic formatting execute through recovered dependencies. Finite external
IOP/MMIO inputs remain explicit.

COP1 CVT.W.S uses the existing independently reviewed EE raw-value provider in
both test environments. Its value model uses truncation and signed saturation;
FCSR flags and exceptions are outside this evidence. Game routines and library
returns are not replaced by callbacks. Actual PS2 playback/runtime and a matching
executable remain unverified.

Five named Unity counterparts are reviewed in script-movie-matches.json. The
port retains the type dispatch, result slot and movie call chains, while replacing
packed PS2 storage with managed arrays and adding bounds/null exceptions and an
unknown-tag abort. Its PLAY command also calls DofOff, handles index five specially,
and conditions completion on playback state. The CHKDRAW symbol at 181d7d4d0 is
a protected lock stub, so it remains a symbol lead without reviewed body semantics.
The exported HD entry-body segmentation does not establish complete native byte
equivalence.

The DDS scan finds one complete 36-byte CHKDRAW wrapper at 00270218 after masking
only its JAL destination. It calls 00270088. That callee has the same LUI/JR/LBU
form as the Nocturne draw-state getter, but its data address is 0037b8bc rather
than 00343e74. This is an anchored structural lead; the current transfer report
does not promote the relocated getter to a complete body match. PLAY and STOP
have 29 and 27 unconstrained generic-wrapper candidates, respectively, and are
unresolved. No complete-span candidate resolves the two VM helpers or CHK under
the current mask. Static DDS evidence does not establish execution equivalence.

Source: src/script_movie.c and src/script_movie.h. Current evidence:
script-movie-validation.json, script-movie-abi.json, script-movie-matches.json and
script-movie-transfer.json. Annotations are saved directly to
ghidra/working/Nocturne.gpr and the rolling whole-program exports are updated.
Continue with the adjacent float/string/label VM helpers and script dispatch.
