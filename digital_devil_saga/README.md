# Digital Devil Saga disc extractor

Put an ISO in the repository root, then run:

```powershell
python tooling/disc_extract.py
```

The script uses the alphabetically first `.iso` file in the root and extracts its files under `game/`. It compares every file against the USA release hashes in `sha256.json` and logs differences as warnings. Warnings do not stop extraction.

Existing files are checked and left alone. Run `python tooling/disc_extract.py --overwrite` to replace them from the ISO.

## DDS3 archive files

The disc extractor leaves `DDS3.DDT` (the index) and `DDS3.IMG` (the archive) in `game/`. To inspect or extract files inside the IMG:

```powershell
python tooling/dds3_extract.py list
python tooling/dds3_extract.py extract battle/SKILL.TBL battle/UNIT.TBL
python tooling/dds3_extract.py all
```

Extraction defaults to `game/dds3/` and skips existing files. Pass `--overwrite` to replace them, or `--dest PATH` for another output directory. The `--ddt` and `--img` options accept alternate input paths. The extractor reads the archive in chunks; extracting all 7,661 files requires space for most of the 1.5 GB IMG. See [the data-table map](analysis/dds3-data-tables.md) for the skill, enemy, encounter, AI, and item records identified so far.

## Ghidra progress

Save the open Ghidra program, then run:

```powershell
.\tooling\ghidra\snapshot.ps1 -ProjectFile 'C:\Projects\Ghidra\DigitalDevilSaga.gpr'
```

This creates a restorable `.gzf` archive in ignored `backups/` and updates the small, Git-friendly `analysis/ghidra-annotations.tsv` export. The text file lists user-named symbols and variables, edited signatures, and comments. The GZF preserves the full Ghidra program, including analysis that the text export does not cover. Import the GZF into Ghidra to restore it. Keep a copy of `backups/` outside this repo for long-term safety.
