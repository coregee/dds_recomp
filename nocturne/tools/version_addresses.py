"""The guest addresses the source uses, mapped to another version's.

    python tools/version_addresses.py chronicle

The source writes US Maniax's addresses through nocturne/address.hpp:
addr(0x...) for an address every version has, optionalAddr(0x...) for one a
version may lack (a debug print's format); the JP layers write what only
the JP builds have by JP Maniax's address, jpAddr(0x...). This scans what
the version builds (tools/sources.py) for them and maps each US one:

- code (below US Maniax's data, 0x2F5000): through
  reference/versions/<name>-function-map.tsv (tools/match_functions.py): a
  function's start, or a place inside a function matched instruction for
  instruction;
- data: through reference/versions/<name>-data-map.tsv (tools/match_data.py):
  exactly where the code was seen forming it, else by the delta its nearest
  mapped neighbours below and above agree on, else where the same bytes
  occur once between them.

and each JP Maniax one: itself in JP Maniax, else by the delta that the
JP Maniax addresses nearest it below and above (both mapped from US
Maniax, data maps) agree on in the version, else by its bytes.

Writes source/generated/<name>/include/nocturne/version_addresses.hpp, the tables
addr() and jpAddr() look addresses up in at compile time. An address it
can't place is written as 0: addr() refuses it (a compile error where it's
used), optionalAddr() gives 0 (none). Prints those.
"""
import bisect
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
USE = re.compile(r'\b(addr|optionalAddr|jpAddr)\(0x([0-9a-fA-F]{8})\)')
FIRST_DATA = 0x002f5000   # US Maniax's data segment
EXECUTABLES = {'maniax-us': 'game/SLUS_209.11', 'maniax': 'game/jpmaniax/SLPM_654.62',
               'chronicle': 'game/chronicle/SLPM_666.81', 'vanilla': 'game/vanilla/SLPM_652.42'}


def image(path):
    """The executable's loaded segments as [(address, bytes)]."""
    data = open(os.path.join(ROOT, path), 'rb').read()
    out = []
    phoff = struct.unpack_from('<I', data, 0x1c)[0]
    for i in range(struct.unpack_from('<H', data, 0x2c)[0]):
        kind, offset, vaddr, _, filesz = struct.unpack_from('<5I', data, phoff + 32 * i)
        if kind == 1:
            out.append((vaddr, data[offset:offset + filesz]))
    return out


def read(segments, address, length):
    for vaddr, data in segments:
        if vaddr <= address and address + length <= vaddr + len(data):
            return data[address - vaddr:address - vaddr + length]
    return None


def find_content(maniax, other, address, low, high):
    """Where the bytes at `address` (a C string whole, else 32, 16 or 8
    bytes) occur once in the other version between low and high."""
    lengths = [32, 16, 8]
    head = read(maniax, address, 256)
    if head and b'\0' in head and head.index(b'\0') >= 4:
        lengths.insert(0, head.index(b'\0') + 1)
    for length in lengths:
        needle = read(maniax, address, length)
        if needle is None:
            continue
        hits = []
        for vaddr, data in other:
            start = max(low, vaddr) - vaddr
            end = min(high, vaddr + len(data)) - vaddr
            if start >= end:
                continue
            k = data.find(needle, start, end)
            while k != -1:
                hits.append(vaddr + k)
                k = data.find(needle, k + 1, end)
        if len(hits) == 1:
            return hits[0]
        if len(hits) > 1:
            return None
    return None


def used_addresses(name):
    """{(key kind, address): (kind, first file using it)} over what the
    version builds: its sources (tools/sources.py) and the headers on its
    include path; addr wins over optionalAddr. The key kind is 'us' or 'jp'."""
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import sources
    files = [str(path) for path, _ in sources.sources(name)]
    for folder in sources.includes(name):
        for top, _, names in os.walk(folder):
            files += [os.path.join(top, f) for f in sorted(names) if f.endswith('.hpp')]
    found = {}
    for path in files:
        for line in open(path, encoding='utf-8'):
            for m in USE.finditer(line.split('//')[0]):
                key = ('jp' if m.group(1) == 'jpAddr' else 'us', int(m.group(2), 16))
                old = found.get(key)
                if old is None or (old[0] == 'optionalAddr' and m.group(1) == 'addr'):
                    found[key] = (m.group(1), os.path.relpath(path, ROOT))
    return found


def rows(name, kind):
    path = os.path.join(ROOT, 'reference/versions/%s-%s-map.tsv' % (name, kind))
    return [line.split('\t') for line in open(path, encoding='utf-8').read().splitlines()[1:]]


def code_map(name):
    """(starts, {start: (other start, size, interior ok)})."""
    functions = {}
    for row in rows(name, 'function'):
        if row[1]:
            functions[int(row[0], 16)] = (int(row[1], 16), int(row[2]), row[3] in ('exact', 'masked', 'ordered'))
    return sorted(functions), functions


def map_code(address, starts, functions):
    k = bisect.bisect_right(starts, address) - 1
    if k < 0:
        return None
    start = starts[k]
    other, size, interior = functions[start]
    if address == start:
        return other
    if interior and address < start + size:
        return other + address - start
    return None


def data_map(name):
    """{US Maniax address: the version's}, where the code agreed."""
    return {int(a, 16): int(b, 16) for a, b, _, agree in rows(name, 'data') if float(agree) >= 0.99}


def map_data(address, known, keys, base, other):
    if address in known:
        return known[address]
    k = bisect.bisect_left(keys, address)
    below = keys[k - 1] if k > 0 else None
    above = keys[k] if k < len(keys) else None
    if below is not None and above is not None and known[below] - below == known[above] - above:
        return address + known[below] - below
    low = known[below] if below is not None else 0
    high = known[above] if above is not None else 0xffffffff
    return find_content(base, other, address, low, high)


def main():
    name = sys.argv[1]
    known = data_map(name)
    keys = sorted(k for k in known if k >= FIRST_DATA)
    starts, functions = code_map(name)
    us, other = image(EXECUTABLES['maniax-us']), image(EXECUTABLES[name])
    # JP Maniax addresses, by the JP Maniax addresses both maps reach.
    jp_known = {}
    if name != 'maniax':
        jp_map = data_map('maniax')
        jp_known = {jp_map[a]: known[a] for a in jp_map if a in known and a >= FIRST_DATA}
    jp_keys = sorted(jp_known)
    jp_image = image(EXECUTABLES['maniax'])
    mapped, jp_mapped, unresolved = {}, {}, []
    for (key_kind, address), (kind, where) in sorted(used_addresses(name).items()):
        if key_kind == 'jp':
            hit = address if name == 'maniax' else map_data(address, jp_known, jp_keys, jp_image, other)
            jp_mapped[address] = hit or 0
        elif address < FIRST_DATA:
            hit = map_code(address, starts, functions)
            mapped[address] = hit or 0
        else:
            hit = map_data(address, known, keys, us, other)
            mapped[address] = hit or 0
        if not hit:
            unresolved.append((address, kind, where))
    out = os.path.join(ROOT, 'source/generated/%s/include/nocturne/version_addresses.hpp' % name)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, 'w', encoding='utf-8', newline='\n') as f:
        f.write('// Generated by tools/version_addresses.py: the addresses the source uses\n')
        f.write('// (nocturne/address.hpp) and this version\'s, 0 for none. Do not edit.\n')
        f.write('#pragma once\n\nnamespace nocturne {\n\n')
        f.write('// By US Maniax\'s address (addr, optionalAddr).\n')
        f.write('inline constexpr AddressPair kVersionAddresses[] = {\n')
        for a, b in sorted(mapped.items()):
            f.write('    {0x%08x, 0x%08x},\n' % (a, b))
        f.write('};\n\n// By JP Maniax\'s address (jpAddr).\n')
        f.write('inline constexpr AddressPair kJpAddresses[] = {\n')
        for a, b in sorted(jp_mapped.items()):
            f.write('    {0x%08x, 0x%08x},\n' % (a, b))
        if not jp_mapped:
            f.write('    {0, 0},\n')
        f.write('};\n\n} // namespace nocturne\n')
    print('%s: %d addresses, %d JP-only, %d without a counterpart' % (name, len(mapped), len(jp_mapped), len(unresolved)))
    for address, kind, where in unresolved:
        print('  %08x  %-12s %s' % (address, kind, where))


if __name__ == '__main__':
    main()
