"""Import smt3-decomp's names as a second name source.

usage: python tools/smt3_decomp_names.py <smt3-decomp clone>

smt3-decomp (https://github.com/Megami-Decomps/smt3-decomp) is a matching
decompilation of SLUS_209.11, US Maniax: the addresses our map is keyed by.
Its config/smt3/symbol_addrs.txt carries names recovered from the HD
remaster's symbols. Only the names are taken (address, name, whether it is a
function), into reference/ps2/identification/smt3-decomp-names.tsv, with the
commit they came from; none of its code. tools/function_map.py reads them.
Like every original name, they are evidence: they go in the map and in the
rewrite's "// name @ 0x..." tags, while the rewrite's own identifiers stay
English names chosen for what the code does.

Also writes smt3-decomp-conflicts.tsv beside it: every function both projects
name, differently, for review. Our name is the rewrite's original-name tag
when there is one (source/), else the map's. Placeholders on either side
(FUN_..., ps2..., names ending in an address) don't count as names.
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "reference" / "ps2" / "identification"
SYMBOL = re.compile(r"\s*([A-Za-z_]\w*)\s*=\s*0x([0-9A-Fa-f]+);(.*)")
TAG = re.compile(r"^\s*//\s*(\w+)\s*@\s*0x([0-9A-Fa-f]{8})\b")


def placeholder(name):
    return (not name or re.match(r"(FUN|func|sub|D|jtbl|code|LAB)_", name) is not None
            or name.startswith(("ps2", "nocturne")) or re.search(r"_[0-9A-Fa-f]{6,8}$", name) is not None)


def same(ours, theirs):
    """The same name, but for a module prefix one side leaves off
    (dds3DeleteProcessList, DeleteProcessList) or the letters' case."""
    a, b = ours.lower(), theirs.lower()
    return a == b or a.endswith(b) or b.endswith(a)


def hd_names():
    """Every method name the HD remaster's assemblies carry."""
    with open(ROOT / "reference" / "hd" / "metadata" / "game-methods.tsv", encoding="utf-8") as f:
        return {cols[3] for cols in (line.split("\t") for line in f) if len(cols) > 3}


def verdict(ours, theirs, hd):
    """Which of the two names the HD remaster has."""
    return {(True, False): "ours", (False, True): "theirs", (True, True): "both"}.get((ours in hd, theirs in hd), "neither")


def read_symbols(clone):
    """{address: (name, is_function)}: the first entry for an address wins, as
    in the file (hand-curated symbols come before the generated block)."""
    symbols = {}
    for line in (clone / "config" / "smt3" / "symbol_addrs.txt").read_text(encoding="utf-8").splitlines():
        m = SYMBOL.match(line)
        if m:
            symbols.setdefault(int(m.group(2), 16), (m.group(1), "type:func" in m.group(3)))
    return symbols


def our_names():
    """{address: (name, where)}: the map's names, overridden by the rewrite's tags."""
    names = {}
    with open(ROOT / "reference" / "function-map.tsv", encoding="utf-8") as f:
        next(f)
        for line in f:
            address, _, name = line.split("\t")[:3]
            names[int(address, 16)] = (name, "function-map.tsv")
    for path in sorted((ROOT / "source").rglob("*.cpp")):
        for i, line in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
            m = TAG.match(line)
            if m:
                names[int(m.group(2), 16)] = (m.group(1), f"{path.relative_to(ROOT).as_posix()}:{i}")
    return names


def main():
    clone = Path(sys.argv[1])
    commit = subprocess.run(["git", "-C", str(clone), "rev-parse", "HEAD"], capture_output=True, text=True,
                            check=True).stdout.strip()
    symbols = read_symbols(clone)
    with open(OUT / "smt3-decomp-names.tsv", "w", encoding="utf-8", newline="\n") as f:
        f.write(f"# Names from smt3-decomp (https://github.com/Megami-Decomps/smt3-decomp) at {commit},\n"
                "# config/smt3/symbol_addrs.txt (recovered from the HD remaster's symbols). Names only.\n"
                "address\tname\tkind\n")
        for address in sorted(symbols):
            name, function = symbols[address]
            f.write(f"{address:08x}\t{name}\t{'function' if function else 'data'}\n")
    ours = our_names()
    hd = hd_names()
    conflicts = []
    for address, (name, where) in sorted(ours.items()):
        theirs = symbols.get(address, ("", False))[0]
        if placeholder(name) or placeholder(theirs) or same(name, theirs):
            continue
        conflicts.append(f"{address:08x}\t{name}\t{theirs}\t{verdict(name, theirs, hd)}\t{where}\n")
    with open(OUT / "smt3-decomp-conflicts.tsv", "w", encoding="utf-8", newline="\n") as f:
        f.write(f"# Functions both projects name, differently (smt3-decomp at {commit}). For review:\n"
                "# neither side is always right. Ours is the rewrite's tag where there is one. hd: which\n"
                "# name the HD remaster's methods have (both: one side names a neighbour; check signatures).\n"
                "address\tours\tsmt3_decomp\thd\twhere\n")
        f.writelines(conflicts)
    print(f"{len(symbols)} names ({sum(1 for _, fn in symbols.values() if fn)} functions), {len(conflicts)} conflicts")


if __name__ == "__main__":
    main()
