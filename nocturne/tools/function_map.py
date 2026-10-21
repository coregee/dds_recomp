"""Build reference/function-map.tsv: every function in SLUS_209.11 and its state.

usage: python tools/function_map.py <ghidra-functions.tsv>

The input comes from tools/ghidra/export-annotations.ps1 (ExportFunctionNames).
For each function the map records:

  status        rewritten  - has a readable implementation under source/
                legacy     - only the instruction-faithful C under legacy/src
                named      - named in Ghidra, no C yet
                unknown    - not yet identified
  rewrite       the source/ function, found by its "@ 0x<address>" comment
  legacy        the legacy/src definition(s)
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def read_functions(path):
    functions = {}
    with open(path, encoding="utf-8") as f:
        next(f)
        for line in f:
            address, size, name, source = line.rstrip("\n").split("\t")
            functions[address.lower()] = (int(size), name, source)
    return functions


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
    '// 0x<address> (unnamed)'; the next definition at column 0 is the rewrite."""
    found = {}
    tag = re.compile(r"^//\s*(?:\w+\s*@\s*)?0x([0-9A-Fa-f]{8})\b")
    definition = re.compile(r"^[A-Za-z_][\w:<>&\* ]*?\b(\w+)\(")
    for path in sorted((ROOT / "source" / "src").rglob("*.cpp")):
        lines = path.read_text(encoding="utf-8").splitlines()
        for i, line in enumerate(lines):
            m = tag.match(line)
            if not m:
                continue
            for following in lines[i + 1:i + 40]:
                d = definition.match(following)
                if d:
                    found[m.group(1).lower()] = f"{path.relative_to(ROOT / 'source').as_posix()}:{d.group(1)}"
                    break
    return found


def main():
    functions = read_functions(sys.argv[1])
    legacy = legacy_definitions(functions)
    rewritten = rewrites()
    counts = {}
    out = ROOT / "reference" / "function-map.tsv"
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write("address\tsize\tname\tname_source\tstatus\trewrite\tlegacy\n")
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
                    f"{';'.join(sorted(legacy.get(address, ())))}\n")
    total = len(functions)
    print(f"{out.relative_to(ROOT)}: {total} functions")
    for status in ("rewritten", "legacy", "named", "unknown"):
        print(f"  {status:<10}{counts.get(status, 0):>6}  ({100 * counts.get(status, 0) / total:.1f}%)")


if __name__ == "__main__":
    main()
