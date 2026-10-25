"""Match US Maniax's functions to another version's executable.

    python tools/match_functions.py chronicle

Reads US Maniax's functions (reference/function-map.tsv: address, size,
name) and finds each in the other executable by its instructions, with the
bits that depend on where things are placed masked out: call and jump
targets, lui immediates, and the immediates of loads, stores and adds that
aren't relative to the stack. A function whose masked instructions occur
once is matched outright; one that occurs several times takes the
candidate in line with its matched neighbours (the order of functions is
kept between builds). Writes reference/versions/<name>-function-map.tsv:
the US Maniax address, the version's address (blank if unmatched), the size,
how it matched (exact: the same bytes, masked, ordered) and the name.
"""
import bisect
import os
import struct
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXECUTABLES = {
    'maniax-us': 'game/SLUS_209.11',
    'hardtype': 'game/hardtype/SLUS_209.11',
    'chronicle': 'game/chronicle/SLPM_666.81',
    'vanilla': 'game/vanilla/SLPM_652.42',
    'maniax': 'game/jpmaniax/SLPM_654.62',
}

# I-type opcodes whose immediate is an address part or a data offset.
MASKED_IMMEDIATE = {0x08, 0x09, 0x0d, 0x0f, 0x1a, 0x1b, 0x1e, 0x1f,
                    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x31,
                    0x37, 0x39, 0x3f}
SP = 29


def load(path):
    data = open(os.path.join(ROOT, path), 'rb').read()
    segments = []
    phoff = struct.unpack_from('<I', data, 0x1c)[0]
    for i in range(struct.unpack_from('<H', data, 0x2c)[0]):
        kind, offset, vaddr, _, filesz, _, flags, _ = struct.unpack_from('<8I', data, phoff + 32 * i)
        if kind == 1:
            segments.append((vaddr, offset, filesz, flags))
    return data, segments


def code_words(data, segments):
    """The executable segment as (start address, list of words)."""
    for vaddr, offset, size, flags in segments:
        if flags & 1:
            return vaddr, list(struct.unpack_from('<%dI' % (size // 4), data, offset))
    raise SystemExit('no code segment')


def mask(word):
    op = word >> 26
    if op in (2, 3):                       # j, jal
        return word & 0xfc000000
    if op in MASKED_IMMEDIATE:
        rs = (word >> 21) & 31
        if op != 0x0f and rs == SP:        # stack offsets stay
            return word
        return word & 0xffff0000
    return word


def function_starts(words, start):
    """Addresses the code calls (jal) or forms (lui, then addiu or ori) in
    its own code segment."""
    end = start + 4 * len(words)
    found = set()
    lui = {}
    for w in words:
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        if op == 3:
            found.add((w & 0x3ffffff) << 2)
        elif op == 0x0f:
            lui[rt] = (w & 0xffff) << 16
            continue
        elif op in (0x09, 0x0d) and rs in lui:
            imm = w & 0xffff
            value = (lui[rs] + (imm - 0x10000 if op == 0x09 and imm & 0x8000 else imm)) & 0xffffffff
            if start <= value < end and value % 4 == 0:
                found.add(value)
        lui.pop(rt, None)
    return found


def data_pointers(data, segments, start, count):
    """Words in the data segments that point into the code (function
    tables, such as the script commands')."""
    end = start + 4 * count
    found = set()
    for vaddr, offset, size, flags in segments:
        if flags & 1:
            continue
        for (value,) in struct.iter_unpack('<I', data[offset:offset + size - size % 4]):
            if start <= value < end and value % 4 == 0:
                found.add(value)
    return found


def main():
    name = sys.argv[1] if len(sys.argv) > 1 else 'chronicle'
    base_start, base = code_words(*load(EXECUTABLES['maniax-us']))
    other_start, other = code_words(*load(EXECUTABLES[name]))
    masked_other = [mask(w) for w in other]

    functions = []
    for line in open(os.path.join(ROOT, 'reference/function-map.tsv'), encoding='utf-8').read().splitlines()[1:]:
        cols = line.split('\t')
        address, size = int(cols[0], 16), int(cols[1])
        index = (address - base_start) // 4
        if size >= 8 and 0 <= index and index + size // 4 <= len(base):
            functions.append((address, size, cols[2], index))

    # Index the other executable by its first masked words (1 to 4 of them,
    # for functions as short as one word).
    KEY = 4
    starts = {k: defaultdict(list) for k in range(1, KEY + 1)}
    for i in range(len(masked_other) - KEY):
        for k in range(1, KEY + 1):
            starts[k][tuple(masked_other[i:i + k])].append(i)

    candidates = {}
    for address, size, fname, index in functions:
        words = base[index:index + size // 4]
        masked = [mask(w) for w in words]
        found = []
        k = min(KEY, len(masked))
        for i in starts[k].get(tuple(masked[:k]), []):
            if masked_other[i:i + len(masked)] == masked:
                found.append(i)
        exact = [i for i in found if other[i:i + len(words)] == words]
        candidates[address] = (found, exact)

    # Unique matches first, then the ambiguous ones by their neighbours.
    matched = {}
    for address, size, fname, index in functions:
        found, _ = candidates[address]
        if len(found) == 1:
            matched[address] = found[0]
    changed = True
    while changed:
        changed = False
        order = sorted(matched)
        for address, size, fname, index in functions:
            found, _ = candidates[address]
            if len(found) > 1 and address not in matched:
                k = bisect.bisect_left(order, address)
                lo = matched[order[k - 1]] if k > 0 else -1
                hi = matched[order[k]] if k < len(order) else len(other)
                inside = [i for i in found if lo < i < hi]
                # Between two neighbours: the only candidate, or the one
                # at the same distance from the lower neighbour.
                if len(inside) > 1 and k > 0:
                    offset = (address - order[k - 1]) // 4
                    inside = [i for i in inside if i - lo == offset] or inside
                if len(inside) == 1:
                    matched[address] = inside[0]
                    changed = True
                    order.insert(k, address)

    # Functions that differ, called from functions that match: a call at the
    # same place in both copies of a caller pairs the callees (match
    # "called"), when the calls agree.
    size_of = {address: size for address, size, fname, index in functions}
    votes = defaultdict(Counter)
    for address, i in list(matched.items()):
        n = size_of[address] // 4
        start = (address - base_start) // 4
        for k in range(n):
            w, v = base[start + k], other[i + k]
            if w >> 26 == 3 and v >> 26 == 3:
                callee, theirs = (w & 0x3ffffff) << 2, (v & 0x3ffffff) << 2
                if callee in size_of and callee not in matched:
                    votes[callee][theirs] += 1
    taken = {other_start + 4 * i for i in matched.values()}
    by_call = set()
    for callee, counter in votes.items():
        theirs, count = counter.most_common(1)[0]
        if count >= 0.9 * sum(counter.values()) and theirs not in taken:
            matched[callee] = (theirs - other_start) // 4
            taken.add(theirs)
            by_call.add(callee)

    # Pairs read off the instructions by hand
    # (reference/versions/<name>-function-pairs.tsv: US Maniax, the version's).
    by_hand = set()
    pairs = os.path.join(ROOT, 'reference/versions/%s-function-pairs.tsv' % name)
    if os.path.exists(pairs):
        for line in open(pairs, encoding='utf-8').read().splitlines():
            if line and not line.startswith('#'):
                a, b = (int(x, 16) for x in line.split()[:2])
                if a in size_of:
                    matched[a] = (b - other_start) // 4
                    by_hand.add(a)

    # Functions that differ, between matched neighbours: paired in order
    # with the other build's function starts in the same gap (called by jal
    # or formed as a code address; else also pointed to by data), when there
    # are as many of each.
    called = function_starts(other, other_start) | {other_start + 4 * i for i in matched.values()}
    pointed = called | data_pointers(*load(EXECUTABLES[name]), other_start, len(other))
    starts_called, starts_pointed = sorted(called), sorted(pointed)
    order = sorted(matched)
    gaps = defaultdict(list)
    for address, size, fname, index in functions:
        if address not in matched:
            k = bisect.bisect_left(order, address)
            gaps[k].append(address)
    gapped = set()
    for k, members in gaps.items():
        lo = other_start + 4 * matched[order[k - 1]] if k > 0 else other_start - 1
        hi = other_start + 4 * matched[order[k]] if k < len(order) else other_start + 4 * len(other)
        inside = [a for a in starts_called if lo < a < hi]
        if len(inside) != len(members):   # functions reached only through tables
            inside = [a for a in starts_pointed if lo < a < hi]
        if len(inside) == len(members):
            for address, start in zip(members, inside):
                matched[address] = (start - other_start) // 4
                gapped.add(address)

    out_dir = os.path.join(ROOT, 'reference/versions')
    os.makedirs(out_dir, exist_ok=True)
    counts = defaultdict(int)
    with open(os.path.join(out_dir, '%s-function-map.tsv' % name), 'w', encoding='utf-8', newline='\n') as out:
        out.write('maniax\t%s\tsize\tmatch\tname\n' % name)
        for address, size, fname, index in functions:
            found, exact = candidates[address]
            if address in matched:
                i = matched[address]
                how = ('hand' if address in by_hand else 'called' if address in by_call else 'gap' if address in gapped else 'exact' if i in exact
                       else 'masked' if len(found) == 1 else 'ordered')
                out.write('%08x\t%08x\t%d\t%s\t%s\n' % (address, other_start + 4 * i, size, how, fname))
            else:
                how = 'none' if not found else 'ambiguous'
                out.write('%08x\t\t%d\t%s\t%s\n' % (address, size, how, fname))
            counts[how] += 1
    total = len(functions)
    print('%s: %d functions;' % (name, total), ', '.join('%s %d' % kv for kv in sorted(counts.items())))


if __name__ == '__main__':
    main()
