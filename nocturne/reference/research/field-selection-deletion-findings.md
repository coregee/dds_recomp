# Field selection deletion

Two connected routines are recovered in `src/field_delete.c/.h`: `fldAnahoriSelectDel`
at `00123a30` and `fldCommand_FLD_ANAHORI_DEL` at `0015a688`. Their reviewed Unity
counterparts are `18204ee30` and `182429560`. All 2,048 new original-instruction
comparisons pass, included in the checkpoint of 211 compiled functions and
152,996 cases. `field-selection-deletion-validation.json` records the exact
source, verifier, vector, original-body and saved-project hashes.

The complete original spans contain 58 words / 232 bytes; 57 listed instruction
words re-encode exactly. The omitted NOP at `00123ad4` remains covered by the
full-span hash. Independent review also checked the real removal, event,
list-delete, clear and packing dependencies against their original words.

## Selection and removal are different searches

Selection scans exactly sixteen inline 236-byte unit records at work+A54.
Flag1 must be set, flags4/10/800 absent and unsigned HP nonzero. It selects the
stored signed eligible ordinal, without a stored eligible-count gate. Negative
or stale indices simply fail the bounded scan. The index load occupies the
HP-zero branch's delay slot; the source records that ordering without claiming
physical bus access traces under an optimizing host compiler.

The signed parameter byte at unit+16hex controls event bit504: values 21..127
set it before removal, while byte encodings 80..FF are negative. After setting
the event, the original reloads the work pointer before reading the selected
unsigned ID at+4. The real `evtBitOn` and `datDelDevil` functions execute.

Removal searches the byte stock-list prefix for the first matching ID. It does
not repeat the eligibility predicate. A duplicate ID or ID0 can therefore
remove a different physical record, including an inactive record. Successful
removal performs the actual full-record clear, list deletion and stock packing;
the final vacated list byte remains preserved. A nonpositive count or unlisted
ID returns 0. An event set before a failed removal stays set. Selection index
and count remain unchanged.

The chosen signed 32 source interface retains the original V0 removal result,
0/1. It does not prove the historical declared return type: Unity declares
its selection deletion method void. The script wrapper discards that result
and always returns 1, including when the selection or removal fails.

## Validation scope

There are 1,024 cases per entry: every signed parameter-byte encoding, every
physical selected slot, rejecting flag/HP combinations, signed index/count
edges, zero/duplicate/high IDs, inactive and unlisted records, varied list
positions and orders, actual packing holes, and bounded random states.
Each expected result is captured after original ELF instruction execution;
no recovered-C deletion formula supplies expected values.

Both entries compare all nine existing field storage spaces, seven dedicated
guard pairs, the original work-pointer slot and all nine host pointer bindings.
The adapter retains the exact existing owner/data addresses and restores every
complete owner and binding on success or exception. Work and default RNG have
no separately allocated guards. Generator guards that overlap other guard
intervals are captured only after all initializer writes.

The stock packer's aligned LD/SD branch at `002408f8` is statically present but
unreachable for its adjacent records: source-destination is 236, or 4 modulo 8,
so `(source|destination)&7` cannot be 0. These comparisons execute its real
LDL/LDR/SDL/SDR copy path and vary the real memset alignment paths. They do not
claim execution of that dead aligned-copy branch.

The whole instruction suite measures maximum Ghidra emulator steps 31,664 for
selection deletion and 31,630 for its wrapper on their independently initialized
cases. The independent word model measures 35,968 actual instruction executions
including delay slots; these measures have different step definitions. Both
entries have a bounded 100,000-step harness ceiling. The initial 20,000-step
ceiling stopped a valid packing case; its log is retained separately and no
partial results from that failed run were promoted.

Stable, distinct, aligned and fully backed ordinary RAM is the interface.
Positive stock counts are at most 16, and used stock-list indexes are 0..15;
nonpositive counts take the original no-removal path. Device/concurrent behavior,
PS2 hardware execution and matching binaries remain unverified.
