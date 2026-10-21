"""List or extract files from the DDS3.DDT / DDS3.IMG archive in game/."""

import argparse
import os
import struct
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
GAME = ROOT / "game"
SECTOR = 0x800
ENTRY_SIZE = 12
CHUNK = 1024 * 1024
INVALID_NAME_CHARS = set('/\\:<>|?*"')
WINDOWS_RESERVED = {"CON", "PRN", "AUX", "NUL"} | {
    f"{prefix}{number}" for prefix in ("COM", "LPT") for number in range(1, 10)
}


@dataclass(frozen=True)
class ArchiveFile:
    path: str
    offset: int
    size: int


def archive_files(ddt: bytes, img_size: int) -> list[ArchiveFile]:
    """Validate the DDT tree and return its files with byte offsets in the IMG."""
    if len(ddt) < ENTRY_SIZE or img_size < 0:
        raise ValueError("Invalid DDS3 archive size")

    visited_entries: set[int] = set()
    visited_paths: set[str] = set()
    files: list[ArchiveFile] = []
    pending = [(0, "", True)]

    while pending:
        position, parent, root = pending.pop()
        if position in visited_entries:
            raise ValueError(f"Repeated DDT entry at 0x{position:X}")
        if position < 0 or position + ENTRY_SIZE > len(ddt):
            raise ValueError(f"DDT entry outside index at 0x{position:X}")
        visited_entries.add(position)

        name_offset, location, count = struct.unpack_from("<IIi", ddt, position)
        if root:
            if name_offset != 0 or count >= 0:
                raise ValueError("Invalid DDT root directory")
            path = ""
        else:
            if name_offset == 0 or name_offset >= len(ddt):
                raise ValueError(f"Invalid DDT name offset at 0x{position:X}")
            end = ddt.find(b"\0", name_offset)
            if end < 0:
                raise ValueError(f"Unterminated DDT name at 0x{position:X}")
            try:
                name = ddt[name_offset:end].decode("ascii")
            except UnicodeDecodeError as error:
                raise ValueError(f"Non-ASCII DDT name at 0x{position:X}") from error
            if (not name or name in (".", "..") or len(name) > 255
                    or name[-1] in (" ", ".")
                    or any(ord(char) < 32 or ord(char) == 127 or char in INVALID_NAME_CHARS
                           for char in name)
                    or name.split(".", 1)[0].upper() in WINDOWS_RESERVED):
                raise ValueError(f"Unsafe DDT name: {name!r}")
            path = f"{parent}/{name}" if parent else name
            if path.casefold() in visited_paths:
                raise ValueError(f"Duplicate DDT path: {path}")
            visited_paths.add(path.casefold())

        if count < 0:
            children = -count
            if location > len(ddt) or children > (len(ddt) - location) // ENTRY_SIZE:
                raise ValueError(f"DDT directory outside index: {path or '/'}")
            for index in reversed(range(children)):
                pending.append((location + ENTRY_SIZE * index, path, False))
        else:
            offset = location * SECTOR
            if offset > img_size or count > img_size - offset:
                raise ValueError(f"DDT file outside IMG: {path}")
            files.append(ArchiveFile(path, offset, count))

    # Zero-size entries can share a sector; nonempty file data must not overlap.
    occupied = sorted((entry for entry in files if entry.size), key=lambda entry: entry.offset)
    for previous, current in zip(occupied, occupied[1:]):
        if previous.offset + previous.size > current.offset:
            raise ValueError(f"Overlapping DDS3 files: {previous.path}, {current.path}")
    return sorted(files, key=lambda entry: entry.path.casefold())


def _copy_file(image, entry: ArchiveFile, output) -> None:
    image.seek(entry.offset)
    remaining = entry.size
    while remaining:
        data = image.read(min(CHUNK, remaining))
        if not data:
            raise ValueError(f"Unexpected end of IMG while reading {entry.path}")
        output.write(data)
        remaining -= len(data)


def extract_file(image, entry: ArchiveFile, destination: Path, overwrite: bool) -> bool:
    """Extract one entry. Return False when an existing file was skipped."""
    target = destination.joinpath(*entry.path.split("/"))
    target.parent.mkdir(parents=True, exist_ok=True)
    if not target.parent.resolve().is_relative_to(destination):
        raise ValueError(f"Extraction path leaves destination: {entry.path}")
    if target.is_dir():
        raise ValueError(f"Output path is a directory: {target}")
    if os.path.lexists(target) and not overwrite:
        return False

    if not overwrite:
        # Exclusive creation also protects against a file appearing after the existence check.
        created = False
        try:
            with target.open("xb") as output:
                created = True
                _copy_file(image, entry, output)
        except BaseException:
            if created:
                target.unlink(missing_ok=True)
            raise
        return True

    temporary = None
    try:
        with tempfile.NamedTemporaryFile(dir=target.parent, prefix=".dds3-", delete=False) as output:
            temporary = Path(output.name)
            _copy_file(image, entry, output)
        os.replace(temporary, target)
        return True
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)


def main(argv: list[str] | None = None) -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    source_options = argparse.ArgumentParser(add_help=False)
    source_options.add_argument("--ddt", type=Path, default=GAME / "DDS3.DDT")
    source_options.add_argument("--img", type=Path, default=GAME / "DDS3.IMG")
    output_options = argparse.ArgumentParser(add_help=False, parents=[source_options])
    output_options.add_argument("--dest", type=Path, default=GAME / "dds3")
    output_options.add_argument("--overwrite", action="store_true")
    commands.add_parser("list", parents=[source_options], help="List archive paths and sizes")
    selected = commands.add_parser("extract", parents=[output_options], help="Extract named files")
    selected.add_argument("paths", nargs="+", metavar="ARCHIVE_PATH")
    commands.add_parser("all", parents=[output_options], help="Extract every file")
    args = parser.parse_args(argv)

    ddt = args.ddt.read_bytes()
    with args.img.open("rb") as image:
        entries = archive_files(ddt, os.fstat(image.fileno()).st_size)
        if args.command == "list":
            for entry in entries:
                print(f"{entry.path}\t{entry.size}")
            print(f"{len(entries)} files")
            return

        by_path = {entry.path: entry for entry in entries}
        if args.command == "extract":
            paths = list(dict.fromkeys(args.paths))
            missing = [path for path in paths if path not in by_path]
            if missing:
                raise ValueError(f"Archive path not found: {', '.join(missing)}")
            chosen = [by_path[path] for path in paths]
        else:
            chosen = entries

        destination = args.dest.resolve()
        extracted = skipped = 0
        for entry in chosen:
            if extract_file(image, entry, destination, args.overwrite):
                extracted += 1
                if args.command == "extract":
                    print(f"Extracted {entry.path} ({entry.size} bytes)")
            else:
                skipped += 1
                if args.command == "extract":
                    print(f"Skipped existing {entry.path}")
        print(f"Done: {extracted} extracted, {skipped} existing skipped.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError) as error:
        print(f"DDS3 extraction error: {error}", file=sys.stderr)
        sys.exit(1)
