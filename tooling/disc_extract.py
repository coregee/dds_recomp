"""Extract the ISO in the repository root to game/ and check file hashes."""

import argparse
import hashlib
import json
import os
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
GAME = ROOT / "game"
MANIFEST = ROOT / "sha256.json"
SECTOR = 2048
CHUNK = 8 * 1024 * 1024


@dataclass(frozen=True)
class DiscFile:
    path: str
    offset: int
    size: int


def records(image, extent, size):
    image.seek(extent * SECTOR)
    data = image.read(size)
    if len(data) != size:
        raise ValueError("Incomplete ISO directory")
    position = 0
    while position < size:
        length = data[position]
        if not length:
            position = (position // SECTOR + 1) * SECTOR
            continue
        record = data[position : position + length]
        position += length
        if len(record) != length or length < 34:
            raise ValueError("Invalid ISO directory record")
        name = record[33 : 33 + record[32]].decode("ascii")
        if name in ("\x00", "\x01"):
            continue
        name = name.split(";", 1)[0]
        if not name or name in (".", "..") or any(char in name for char in '/\\:<>|?*'):
            raise ValueError(f"Unsafe ISO filename: {name!r}")
        yield name, int.from_bytes(record[2:6], "little"), int.from_bytes(record[10:14], "little"), record[25]


def scan(image):
    image.seek(16 * SECTOR)
    descriptor = image.read(SECTOR)
    if len(descriptor) != SECTOR or descriptor[:6] != b"\x01CD001":
        raise ValueError("ISO 9660 primary volume descriptor not found")
    root = descriptor[156:190]
    queue = [("", int.from_bytes(root[2:6], "little"), int.from_bytes(root[10:14], "little"))]
    files = []
    seen_dirs = set()
    seen_paths = set()
    while queue:
        parent, extent, size = queue.pop(0)
        if (extent, size) in seen_dirs:
            raise ValueError("Repeated ISO directory extent")
        seen_dirs.add((extent, size))
        for name, child_extent, child_size, flags in records(image, extent, size):
            path = f"{parent}/{name}".lstrip("/")
            if path.casefold() in seen_paths:
                raise ValueError(f"Duplicate ISO path: {path}")
            seen_paths.add(path.casefold())
            if flags & 0x80:
                raise ValueError(f"Multi-extent ISO file needs special handling: {path}")
            if flags & 0x02:
                queue.append((path, child_extent, child_size))
            else:
                files.append(DiscFile(path, child_extent * SECTOR, child_size))
    return sorted(files, key=lambda item: item.path)


def hash_file(path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        while chunk := stream.read(CHUNK):
            digest.update(chunk)
    return digest.hexdigest()


def extract_file(image, entry, target):
    digest = hashlib.sha256()
    target.parent.mkdir(parents=True, exist_ok=True)
    temp_name = None
    try:
        with tempfile.NamedTemporaryFile(dir=target.parent, prefix=".extract-", delete=False) as output:
            temp_name = output.name
            image.seek(entry.offset)
            remaining = entry.size
            while remaining:
                chunk = image.read(min(CHUNK, remaining))
                if not chunk:
                    raise ValueError(f"Unexpected end of ISO while extracting {entry.path}")
                output.write(chunk)
                digest.update(chunk)
                remaining -= len(chunk)
        os.replace(temp_name, target)
    finally:
        if temp_name and os.path.exists(temp_name):
            os.unlink(temp_name)
    return digest.hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--overwrite", action="store_true", help="Replace existing extracted files")
    args = parser.parse_args()
    images = sorted(
        (path for path in ROOT.iterdir() if path.is_file() and path.suffix.lower() == ".iso"),
        key=lambda path: path.name.casefold(),
    )
    if not images:
        raise ValueError(f"No ISO found in {ROOT}")
    print(f"ISO: {images[0].name}")
    expected = json.loads(MANIFEST.read_text(encoding="utf-8"))["files"]
    warnings = 0
    extracted = 0
    checked = 0
    with images[0].open("rb") as image:
        files = scan(image)
        actual_paths = {entry.path for entry in files}
        for path in sorted(set(expected) - actual_paths):
            print(f"WARNING: expected file missing from ISO: {path}")
            warnings += 1
        for entry in files:
            if entry.path not in expected:
                print(f"WARNING: no expected hash for {entry.path}")
                warnings += 1
            target = GAME.joinpath(*entry.path.split("/"))
            if not target.resolve().is_relative_to(GAME.resolve()):
                raise ValueError(f"Extraction path leaves game/: {entry.path}")
            if target.exists() and not args.overwrite:
                if not target.is_file():
                    print(f"WARNING: path is not a file: {target}")
                    warnings += 1
                    continue
                digest = hash_file(target)
                checked += 1
            else:
                digest = extract_file(image, entry, target)
                extracted += 1
            if entry.path in expected and digest != expected[entry.path]:
                print(f"WARNING: SHA-256 mismatch: {entry.path}\n  expected {expected[entry.path]}\n  actual   {digest}")
                warnings += 1
            elif entry.path in expected:
                print(f"OK: {entry.path}")
    if GAME.exists():
        for path in sorted(path for path in GAME.rglob("*") if path.is_file()):
            relative = path.relative_to(GAME).as_posix()
            if relative not in actual_paths:
                print(f"WARNING: extra file in game/: {relative}")
                warnings += 1
    print(f"Done: {extracted} extracted, {checked} existing checked, {warnings} warning(s).")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, KeyError, json.JSONDecodeError) as error:
        print(f"Extraction error: {error}", file=sys.stderr)
        sys.exit(1)
