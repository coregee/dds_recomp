"""The source files and include folders of one version of the game.

    python tools/sources.py <version> sources    one "path|object name" per line
    python tools/sources.py <version> includes   one folder per line, searched in order

Every version compiles the same source (source/README.md): source/shared/,
where code that differs by version holds each version's alternative side by
side, chosen by the build's traits (nocturne/build.hpp). What a version adds
is generated from its executable, under source/generated/<version>/:

    src/data/*_table.cpp            its data tables (tools/gen_tables.py); a
                                    version without its own takes US Maniax's
    include/nocturne/version_addresses.hpp
                                    its addresses (tools/version_addresses.py)
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "source"
GENERATED = SOURCE / "generated"
VERSIONS = ("vanilla", "maniax", "chronicle", "maniax-us", "hardtype")
BASE = "maniax-us"   # the tables a version doesn't generate its own of


def sources(version):
    out = [(path, path.stem) for path in sorted((SOURCE / "shared" / "src").rglob("*.cpp"))]
    tables = {}   # file name -> path, the version's own over the base's
    for name in (BASE, version):
        for path in sorted((GENERATED / name / "src" / "data").glob("*.cpp")):
            tables[path.name] = path
    out += [(path, "g_" + path.stem) for _, path in sorted(tables.items())]
    return out


def includes(version):
    folders = [GENERATED / version / "include", SOURCE / "shared" / "include"]
    return [folder for folder in folders if folder.exists()]


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
