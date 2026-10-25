"""Map US Maniax's data addresses to another version's, from the code.

    python tools/match_data.py chronicle

For every function pair tools/match_functions.py matched, the two builds'
instructions line up one to one; wherever US Maniax forms an address (lui
then an add, or, or load / store on that register; or relative to gp), the
other build forms its own at the same place. Each pair of addresses seen is
counted; a US Maniax address with one counterpart (or a clear majority) is
mapped. Functions that differ but sit in the same place (match "gap") add
their addresses in order, when both form as many, for addresses nothing
else forms. Writes reference/versions/<name>-data-map.tsv: US Maniax address,
the version's, how many times seen, and the share that agreed.
"""
import bisect
import os
import struct
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import match_functions as mf  # noqa: E402

ADDRESS_OPS = {0x09, 0x0d} | set(range(0x1a, 0x40))
GP = 28


def global_pointer(path):
    """gp, from the executable's .reginfo segment (its last word)."""
    data = open(os.path.join(mf.ROOT, path), 'rb').read()
    phoff = struct.unpack_from('<I', data, 0x1c)[0]
    for i in range(struct.unpack_from('<H', data, 0x2c)[0]):
        kind, offset = struct.unpack_from('<2I', data, phoff + 32 * i)
        if kind == 0x70000000:
            return struct.unpack_from('<I', data, offset + 0x14)[0]
    return None


def addresses(words, gp):
    """(index, address) for each address the code forms."""
    out = []
    lui = {}
    pending = None   # what a jump or call clears, after its delay slot
    for i, w in enumerate(words):
        clear, pending = pending, None
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        imm = w & 0xffff
        simm = imm - 0x10000 if imm & 0x8000 else imm
        if op == 0x0f:
            lui[rt] = imm << 16
        else:
            if op in ADDRESS_OPS:
                if rs in lui:
                    out.append((i, (lui[rs] + (imm if op == 0x0d else simm)) & 0xffffffff))
                elif rs == GP and gp is not None:
                    out.append((i, (gp + simm) & 0xffffffff))
            # A register written by anything but this lui pattern loses its value.
            if op in (0x09, 0x0d) and rt in lui and rs != rt:
                lui.pop(rt, None)
            elif op in ADDRESS_OPS and op not in (0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x1f, 0x3f, 0x39):
                lui.pop(rt, None)
            elif op == 0:
                rd, funct = (w >> 11) & 31, w & 63
                # lui base + an index (addu, daddu): the base indexed.
                if funct in (0x21, 0x2d) and (rs in lui) != (rt in lui):
                    lui[rd] = lui[rs] if rs in lui else lui[rt]
                else:
                    lui.pop(rd, None)
            if op == 3 or (op == 0 and (w & 63) == 9):
                pending = 'call'
            elif op == 2 or (op == 0 and (w & 63) == 8):
                pending = 'jump'
        if clear == 'call':
            # A call keeps the saved registers (s0..s7, s8).
            for r in [r for r in lui if not (16 <= r <= 23 or r == 30)]:
                del lui[r]
        elif clear == 'jump':
            lui.clear()
    return out


def main():
    name = sys.argv[1] if len(sys.argv) > 1 else 'chronicle'
    base_start, base = mf.code_words(*mf.load(mf.EXECUTABLES['us']))
    other_start, other = mf.code_words(*mf.load(mf.EXECUTABLES[name]))
    gp_base, gp_other = global_pointer(mf.EXECUTABLES['us']), global_pointer(mf.EXECUTABLES[name])
    seen = defaultdict(Counter)
    rows = [line.split('\t') for line in open(os.path.join(mf.ROOT, 'reference/versions/%s-function-map.tsv' % name),
                                             encoding='utf-8').read().splitlines()[1:]]
    # Functions paired by place (gap) differ, so their addresses line up only
    # by order, and only when both form as many: a weaker source, used for
    # addresses no matched function forms.
    weak = defaultdict(Counter)
    ends = sorted(int(row[1], 16) for row in rows if row[1])
    for row in rows:
        if not row[1]:
            continue
        a, b, n = int(row[0], 16), int(row[1], 16), int(row[2]) // 4
        mine = base[(a - base_start) // 4:(a - base_start) // 4 + n]
        if row[3] == 'gap':
            k = bisect.bisect_right(ends, b)
            end = ends[k] if k < len(ends) else other_start + 4 * len(other)
            theirs = other[(b - other_start) // 4:(end - other_start) // 4]
            left, right = addresses(mine, gp_base), addresses(theirs, gp_other)
            if len(left) == len(right):
                for (_, x), (_, y) in zip(left, right):
                    weak[x][y] += 1
            continue
        theirs = other[(b - other_start) // 4:(b - other_start) // 4 + n]
        left, right = dict(addresses(mine, gp_base)), dict(addresses(theirs, gp_other))
        for i, address in left.items():
            if i in right:
                seen[address][right[i]] += 1
    for address, counts in weak.items():
        if address not in seen:
            seen[address] = counts
    # A target two addresses claim belongs to the one seen forming it most
    # (the others were seen where the version formed something else, as a
    # debug print's format it removed); on a tie, to neither.
    claims = defaultdict(list)
    for address, counts in seen.items():
        target, count = counts.most_common(1)[0]
        claims[target].append((count, address))
    for target, owners in claims.items():
        if len(owners) > 1:
            owners.sort(reverse=True)
            losers = owners if owners[0][0] == owners[1][0] else owners[1:]
            for _, address in losers:
                del seen[address]
    out = os.path.join(mf.ROOT, 'reference/versions/%s-data-map.tsv' % name)
    mapped = 0
    with open(out, 'w', encoding='utf-8', newline='\n') as f:
        f.write('maniax\t%s\tseen\tagree\n' % name)
        for address in sorted(seen):
            target, count = seen[address].most_common(1)[0]
            total = sum(seen[address].values())
            f.write('%08x\t%08x\t%d\t%.2f\n' % (address, target, total, count / total))
            mapped += 1
    print('%s: gp %08x -> %08x, %d addresses' % (name, gp_base, gp_other, mapped))


if __name__ == '__main__':
    main()
