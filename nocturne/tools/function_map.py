"""Build reference/function-map.tsv: every function in SLUS_209.11 and its state.

usage: python tools/function_map.py [ghidra-functions.tsv]

The input comes from tools/ghidra/export-annotations.ps1 (ExportFunctionNames);
without it, the map's own address, size and name columns are kept and the
rest recomputed. For each function the map records:

  status        rewritten  - has a readable implementation under source/
                legacy     - only the instruction-faithful C under legacy/src
                named      - named in Ghidra, no C yet
                unknown    - not yet identified
  rewrite       the source/ function, found by its "@ 0x<address>" comment
  legacy        the legacy/src definition(s)
  <build>       per build (docs/versions.md), what its differential tests of
                the function show, from reference/verification/<build>.tsv
                (written by the test with DIFF_RESULTS set):
                ok       proven against that build's instructions or legacy C
                differ   a test of it fails there
                pending  its test doesn't run there yet (still to port)
                legacy   only tested against US Maniax's legacy C, which
                         says nothing about that build
                (empty)  no test of it by name, or the build has no results
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILDS = ("maniax-us", "hardtype", "chronicle", "maniax", "vanilla")
# When a function has several tests, the worst outcome stands.
RANK = {"differ": 3, "ok": 2, "pending": 1, "legacy": 0}


def read_functions(path):
    functions = {}
    with open(path, encoding="utf-8") as f:
        next(f)
        for line in f:
            address, size, name, source = line.rstrip("\n").split("\t")
            functions[address.lower()] = (int(size), name, source)
    return functions


def read_map():
    """The current map's address, size and name columns (to rebuild without
    the Ghidra export)."""
    functions = {}
    with open(ROOT / "reference" / "function-map.tsv", encoding="utf-8") as f:
        next(f)
        for line in f:
            address, size, name, source = line.rstrip("\n").split("\t")[:4]
            functions[address] = (int(size), name, source)
    return functions


def verification(functions):
    """{build: {address: outcome}} from each build's recorded test outcomes.
    A test is named after the original function it proves; a suffix in
    parentheses names the kind of test ("nbGetHitType (instructions)")."""
    by_name = {}
    for address, (_, name, _) in functions.items():
        by_name.setdefault(name, address)
    out = {}
    for build in BUILDS:
        path = ROOT / "reference" / "verification" / f"{build}.tsv"
        if not path.exists():
            continue
        outcomes = out[build] = {}
        for line in path.read_text(encoding="utf-8").splitlines():
            test, _, outcome = line.partition("\t")
            if outcome not in RANK:   # (a run cut short)
                continue
            address = by_name.get(re.sub(r" \(.*\)$", "", test))
            if address and RANK[outcome] >= RANK.get(outcomes.get(address), -1):
                outcomes[address] = outcome
    return out


def definitions(text):
    """Names of functions defined (with a body) in a C/C++ file."""
    pattern = re.compile(r"^[A-Za-z_][\w \*:&<>,]*?\b(\w+)\s*\([^;{]*\)\s*(?:const\s*)?\{", re.M)
    return [m.group(1) for m in pattern.finditer(text)]


def legacy_definitions(functions):
    by_name = {name: address for address, (_, name, _) in functions.items() if not name.startswith("FUN_")}
    found = {}
    for path in sorted((ROOT / "legacy" / "src").glob("*.c")):
        text = path.read_text(encoding="utf-8", errors="replace")
        for fn in definitions(text):
            suffix = re.search(r"_([0-9A-Fa-f]{8})$", fn)
            address = suffix.group(1).lower() if suffix and suffix.group(1).lower() in functions else by_name.get(fn)
            if address:
                found.setdefault(address, set()).add(f"{path.name}:{fn}")
    return found


def rewrites():
    """source/ functions are preceded by '// <original> @ 0x<address>' or
    '// 0x<address> (unnamed)'; the next definition at column 0 is the rewrite.
    A unit's "By version" section holds what differs by version: often a step
    of a function defined above it, tagged with the function's address, so a
    definition outside the section is the rewrite when there is one."""
    found, in_section = {}, set()
    tag = re.compile(r"^//\s*(?:\w+\s*@\s*)?0x([0-9A-Fa-f]{8})\b")
    definition = re.compile(r"^[A-Za-z_][\w:<>&\* ]*?\b(\w+)\(")
    # (US Maniax's build: tools/sources.py)
    import sources
    paths = [path for path, _ in sources.sources("maniax-us")]
    for path in sorted(paths):
        lines = path.read_text(encoding="utf-8").splitlines()
        section = False
        for i, line in enumerate(lines):
            section = section or line.startswith("// By version (nocturne/build.hpp)")
            m = tag.match(line)
            if not m:
                continue
            address = m.group(1).lower()
            if section and address in found and address not in in_section:
                continue
            for following in lines[i + 1:i + 40]:
                d = definition.match(following)
                if d:
                    found[address] = f"{path.relative_to(ROOT / 'source').as_posix()}:{d.group(1)}"
                    if section:
                        in_section.add(address)
                    else:
                        in_section.discard(address)
                    break
    return found


def main():
    functions = read_functions(sys.argv[1]) if len(sys.argv) > 1 else read_map()
    legacy = legacy_definitions(functions)
    rewritten = rewrites()
    verified = verification(functions)
    counts = {}
    out = ROOT / "reference" / "function-map.tsv"
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write("address\tsize\tname\tname_source\tstatus\trewrite\tlegacy\t" + "\t".join(BUILDS) + "\n")
        for address in sorted(functions):
            size, name, source = functions[address]
            if address in rewritten:
                status = "rewritten"
            elif address in legacy:
                status = "legacy"
            elif not name.startswith("FUN_"):
                status = "named"
            else:
                status = "unknown"
            counts[status] = counts.get(status, 0) + 1
            f.write(f"{address}\t{size}\t{name}\t{source}\t{status}\t{rewritten.get(address, '')}\t"
                    f"{';'.join(sorted(legacy.get(address, ())))}\t"
                    + "\t".join(verified.get(build, {}).get(address, "") for build in BUILDS) + "\n")
    total = len(functions)
    print(f"{out.relative_to(ROOT)}: {total} functions")
    for status in ("rewritten", "legacy", "named", "unknown"):
        print(f"  {status:<10}{counts.get(status, 0):>6}  ({100 * counts.get(status, 0) / total:.1f}%)")
    for build, outcomes in verified.items():
        tally = {o: sum(1 for v in outcomes.values() if v == o) for o in RANK}
        print(f"  {build:<10} " + ", ".join(f"{n} {o}" for o, n in tally.items() if n))


if __name__ == "__main__":
    main()
