"""List and extract files from Nocturne's DDS3.DDT (index) / DDS3.IMG (data) archive.

    python tools/dds3_archive.py list [--filter SUBSTRING]
    python tools/dds3_archive.py extract PATH [PATH ...]
    python tools/dds3_archive.py all [--filter SUBSTRING]

Files are written under game/dds3/ (override with --dest). Existing files are
checked and left alone; a mismatch is an error.

Index format: 12-byte records (name offset, location, count). A negative count
marks a directory of -count child records starting at byte `location`; a
non-negative count is a file of `count` bytes at sector `location` (2048-byte
sectors) in the IMG. The root record has name offset 0.

Names are kept as bytes. A few zero-length placeholder entries have non-ASCII
(Shift-JIS) names even on the US disc; those are listed but never extracted.
"""
import argparse
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SECTOR = 0x800


@dataclass(frozen=True)
class Entry:
    path: bytes
    offset: int
    size: int

    @property
    def name(self) -> str:
        return self.path.decode("ascii") if self.path.isascii() else self.path.decode("shift_jis", "replace")


def read_index(ddt: bytes, img_size: int) -> list[Entry]:
    if len(ddt) < 12:
        raise ValueError("index too small")
    entries, seen, names = [], set(), set()
    pending = [(0, b"", True)]
    while pending:
        position, parent, is_root = pending.pop()
        if position in seen or position + 12 > len(ddt):
            raise ValueError(f"invalid or repeated index record at {position:#x}")
        seen.add(position)
        name_offset, location, count = struct.unpack_from("<IIi", ddt, position)

        if is_root:
            if name_offset or count >= 0:
                raise ValueError("invalid archive root")
            path = b""
        else:
            end = ddt.find(b"\0", name_offset)
            if not 0 < name_offset < len(ddt) or end < 0:
                raise ValueError(f"invalid name at {position:#x}")
            name = ddt[name_offset:end]
            if not name or name in (b".", b"..") or b"/" in name:
                raise ValueError(f"invalid path component {name!r}")
            path = parent + b"/" + name if parent else name
            if path.lower() in names:
                raise ValueError(f"duplicate path {path!r}")
            names.add(path.lower())

        if count < 0:
            children = -count
            if location > len(ddt) or children > (len(ddt) - location) // 12:
                raise ValueError(f"directory {path!r} outside index")
            pending.extend((location + k * 12, path, False) for k in reversed(range(children)))
        else:
            offset = location * SECTOR
            if offset > img_size or count > img_size - offset:
                raise ValueError(f"file {path!r} outside image")
            entries.append(Entry(path, offset, count))

    occupied = sorted((e for e in entries if e.size), key=lambda e: e.offset)
    for a, b in zip(occupied, occupied[1:]):
        if a.offset + a.size > b.offset:
            raise ValueError(f"overlapping files {a.path!r} and {b.path!r}")
    return sorted(entries, key=lambda e: e.path.lower())


def safe_target(destination: Path, entry: Entry) -> Path:
    parts = entry.name.split("/")
    for part in parts:
        if part in ("", ".", "..") or any(c in part for c in '\\:<>|?*"') or part[-1] in " .":
            raise ValueError(f"unsafe output name {entry.name!r}")
    target = destination.joinpath(*parts)
    if not target.resolve().is_relative_to(destination.resolve()):
        raise ValueError(f"{entry.name!r} escapes the destination")
    return target


def extract(entries: list[Entry], img: Path, destination: Path) -> tuple[int, int]:
    written = skipped = 0
    with img.open("rb") as stream:
        for entry in entries:
            if not entry.path.isascii():
                skipped += 1
                continue
            target = safe_target(destination, entry)
            stream.seek(entry.offset)
            data = stream.read(entry.size)
            if len(data) != entry.size:
                raise ValueError(f"short read for {entry.name}")
            if target.exists():
                if target.read_bytes() != data:
                    raise ValueError(f"existing {target} differs from the archive")
                continue
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(data)
            written += 1
    return written, skipped


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--ddt", type=Path, default=ROOT / "game" / "DDS3.DDT")
    parser.add_argument("--img", type=Path, default=ROOT / "game" / "DDS3.IMG")
    parser.add_argument("--dest", type=Path, default=ROOT / "game" / "dds3")
    commands = parser.add_subparsers(dest="command", required=True)
    for name in ("list", "all"):
        sub = commands.add_parser(name)
        sub.add_argument("--filter", default="", help="only paths containing this (case-insensitive)")
    sub = commands.add_parser("extract")
    sub.add_argument("paths", nargs="+")
    args = parser.parse_args()
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    entries = read_index(args.ddt.read_bytes(), args.img.stat().st_size)
    if args.command == "extract":
        wanted = {p.lower() for p in args.paths}
        selected = [e for e in entries if e.name.lower() in wanted]
        missing = wanted - {e.name.lower() for e in selected}
        if missing:
            print("not in archive: " + ", ".join(sorted(missing)), file=sys.stderr)
            return 1
    else:
        selected = [e for e in entries if args.filter.lower() in e.name.lower()]

    if args.command == "list":
        for e in selected:
            print(f"{e.size:>10}  {e.name}")
        print(f"{len(selected)} files", file=sys.stderr)
        return 0

    written, skipped = extract(selected, args.img, args.dest)
    print(f"{written} written, {len(selected) - written - skipped} already present, {skipped} non-ASCII skipped")
    return 0


if __name__ == "__main__":
    sys.exit(main())
