"""What another version changes in the functions it doesn't match.

    python tools/version_diff.py chronicle [name-or-address ...]

Reads reference/versions/<name>-function-map.tsv (tools/match_functions.py)
and, for each US Maniax function that has no match, finds the code between
its matched neighbours in the other executable and lines the two up
instruction by instruction (with the placement-dependent bits masked, as
the matcher does). Prints the differing stretches, US Maniax's on the left.
With names or addresses, only those functions; without, a summary line
each: how many instructions differ.
"""
import difflib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import match_functions as mf  # noqa: E402
from mips import disassemble  # noqa: E402


def main():
    name = sys.argv[1]
    wanted = set(a.lower() for a in sys.argv[2:])
    base_start, base = mf.code_words(*mf.load(mf.EXECUTABLES['maniax']))
    other_start, other = mf.code_words(*mf.load(mf.EXECUTABLES[name]))
    rows = [line.split('\t') for line in open(os.path.join(mf.ROOT, 'reference/versions/%s-function-map.tsv' % name),
                                             encoding='utf-8').read().splitlines()[1:]]
    for k, row in enumerate(rows):
        if row[1] and row[3] != 'gap':
            continue
        address, size, fname = int(row[0], 16), int(row[2]), row[4]
        if wanted and row[0] not in wanted and fname.lower() not in wanted:
            continue
        # The other version's stretch: after the previous matched function, up to the next.
        prev = next((r for r in reversed(rows[:k]) if r[1]), None)
        nxt = next((r for r in rows[k + 1:] if r[1]), None)
        lo = (int(prev[1], 16) + int(prev[2])) if prev else other_start
        hi = int(nxt[1], 16) if nxt else other_start + 4 * len(other)
        # Skip what lies between the previous function and this one in US Maniax.
        if prev:
            lo += address - (int(prev[0], 16) + int(prev[2]))
        if row[1]:   # paired by place (match "gap")
            lo = int(row[1], 16)
        mine = base[(address - base_start) // 4:(address - base_start) // 4 + size // 4]
        theirs = other[(lo - other_start) // 4:(hi - other_start) // 4]
        theirs = theirs[:len(mine) + 256]
        matcher = difflib.SequenceMatcher(None, [mf.mask(w) for w in mine], [mf.mask(w) for w in theirs], autojunk=False)
        blocks = [b for b in matcher.get_opcodes() if b[0] != 'equal']
        # Trim a trailing insertion that runs into the next function.
        if blocks and blocks[-1][0] == 'insert' and blocks[-1][2] == len(mine):
            blocks.pop()
        changed = sum(max(i2 - i1, j2 - j1) for _, i1, i2, j1, j2 in blocks)
        print('%08x -> %08x %-40s %4d words, %d differ' % (address, lo, fname, size // 4, changed))
        if not wanted:
            continue
        for tag, i1, i2, j1, j2 in blocks:
            for n in range(max(i2 - i1, j2 - j1)):
                left = right = ''
                if i1 + n < i2:
                    left = '%08x: %s' % (address + 4 * (i1 + n), disassemble(mine[i1 + n], address + 4 * (i1 + n)))
                if j1 + n < j2:
                    right = '%08x: %s' % (lo + 4 * (j1 + n), disassemble(theirs[j1 + n], lo + 4 * (j1 + n)))
                print('    %-44s | %s' % (left, right))
            print('    ---')


if __name__ == '__main__':
    main()
