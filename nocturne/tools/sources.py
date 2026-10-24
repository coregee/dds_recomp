"""The source files and include folders of one version of the game.

    python tools/sources.py <version> sources    one "path|object name" per line
    python tools/sources.py <version> includes   one folder per line, searched in order

The source tree (source/README.md):

    source/shared/     code every version shares
    source/maniax/     US Maniax's own code and data: what differs between versions
    source/<version>/  another version's replacements (hardtype, chronicle, vanilla)

A version compiles shared/, then each file of maniax/src/ unless it has its
own at the same path, then the files only it has. Headers are searched in
the version's include/ first, then maniax/include/, then shared/include/.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "source"
VERSIONS = ("maniax", "hardtype", "chronicle", "vanilla")


def sources(version):
    out = [(path, path.stem) for path in sorted((SOURCE / "shared" / "src").rglob("*.cpp"))]
    base, own = SOURCE / "maniax" / "src", SOURCE / version / "src"
    seen = set()
    for path in sorted(base.rglob("*.cpp")):
        relative = path.relative_to(base)
        replacement = own / relative
        out.append((replacement if replacement.exists() else path, "v_" + path.stem))
        seen.add(relative)
    if version != "maniax" and own.exists():
        for path in sorted(own.rglob("*.cpp")):
            if path.relative_to(own) not in seen:
                out.append((path, "v_" + path.stem))
    return out


def includes(version):
    folders = [SOURCE / version / "include", SOURCE / "maniax" / "include", SOURCE / "shared" / "include"]
    return list(dict.fromkeys(folder for folder in folders if folder.exists()))


if __name__ == "__main__":
    version, what = sys.argv[1], sys.argv[2]
    if version not in VERSIONS:
        sys.exit(f"unknown version {version}: one of {', '.join(VERSIONS)}")
    if what == "sources":
        for path, name in sources(version):
            print(f"{path}|{name}")
    else:
        for folder in includes(version):
            print(folder)
