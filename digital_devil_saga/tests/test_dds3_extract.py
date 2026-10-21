"""Focused checks for DDS3 archive bounds and safe extraction."""

import io
import struct
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path

from tooling.dds3_extract import ArchiveFile, archive_files, extract_file, main


def sample_archive():
    names = b"battle\0SKILL.TBL\0MSG.TBL\0"
    name_start = 48
    ddt = b"".join((
        struct.pack("<IIi", 0, 12, -1),
        struct.pack("<IIi", name_start, 24, -2),
        struct.pack("<IIi", name_start + 7, 1, 5),
        struct.pack("<IIi", name_start + 17, 2, 7),
        names,
    ))
    image = b"\0" * 2048 + b"skill" + b"\0" * (2048 - 5) + b"message"
    return ddt, image


class Dds3ExtractTests(unittest.TestCase):
    def test_list_select_skip_and_overwrite(self):
        ddt, image = sample_archive()
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            ddt_path, img_path, output = root / "DDS3.DDT", root / "DDS3.IMG", root / "out"
            ddt_path.write_bytes(ddt)
            img_path.write_bytes(image)
            options = ["--ddt", str(ddt_path), "--img", str(img_path)]

            with redirect_stdout(io.StringIO()) as listing:
                main(["list", *options])
            self.assertIn("battle/SKILL.TBL\t5", listing.getvalue())
            self.assertIn("battle/MSG.TBL\t7", listing.getvalue())

            command = ["extract", "battle/SKILL.TBL", *options, "--dest", str(output)]
            with redirect_stdout(io.StringIO()):
                main(command)
            target = output / "battle" / "SKILL.TBL"
            self.assertEqual(target.read_bytes(), b"skill")
            self.assertFalse((output / "battle" / "MSG.TBL").exists())

            target.write_bytes(b"keep")
            with redirect_stdout(io.StringIO()):
                main(command)
            self.assertEqual(target.read_bytes(), b"keep")
            with redirect_stdout(io.StringIO()):
                main([*command, "--overwrite"])
            self.assertEqual(target.read_bytes(), b"skill")

            with redirect_stdout(io.StringIO()):
                main(["all", *options, "--dest", str(output)])
            self.assertEqual((output / "battle" / "MSG.TBL").read_bytes(), b"message")

    def test_rejects_unsafe_names_and_bad_offsets(self):
        ddt, image = sample_archive()
        unsafe = ddt.replace(b"SKILL.TBL\0", b"..\\xx.TBL\0")
        with self.assertRaisesRegex(ValueError, "Unsafe DDT name"):
            archive_files(unsafe, len(image))
        bad_name = bytearray(ddt)
        struct.pack_into("<I", bad_name, 24, len(ddt) + 1)
        bad_directory = bytearray(ddt)
        struct.pack_into("<I", bad_directory, 16, len(ddt) - 4)
        bad_file = bytearray(ddt)
        struct.pack_into("<I", bad_file, 28, 999)
        for invalid in (bad_name, bad_directory, bad_file):
            with self.subTest(index=invalid[:40]):
                with self.assertRaises(ValueError):
                    archive_files(invalid, len(image))

    def test_incomplete_copy_removes_only_its_new_file(self):
        with tempfile.TemporaryDirectory() as directory:
            destination = Path(directory)
            entry = ArchiveFile("battle/SKILL.TBL", 0, 6)
            with self.assertRaises(ValueError):
                extract_file(io.BytesIO(b"short"), entry, destination, overwrite=False)
            self.assertFalse((destination / "battle" / "SKILL.TBL").exists())

            target = destination / "battle" / "SKILL.TBL"
            target.write_bytes(b"keep")
            self.assertFalse(extract_file(io.BytesIO(b"skill!"), entry, destination, overwrite=False))
            self.assertEqual(target.read_bytes(), b"keep")


if __name__ == "__main__":
    unittest.main()
