# Digital Devil Saga disc extractor

Put an ISO in the repository root, then run:

```powershell
python tooling/disc_extract.py
```

The script uses the alphabetically first `.iso` file in the root and extracts its files under `game/`. It compares every file against the USA release hashes in `sha256.json` and logs differences as warnings. Warnings do not stop extraction.

Existing files are checked and left alone. Run `python tooling/disc_extract.py --overwrite` to replace them from the ISO.

## Ghidra progress

Save the open Ghidra program, then run:

```powershell
.\tooling\ghidra\snapshot.ps1 -ProjectFile 'C:\Projects\Ghidra\DigitalDevilSaga.gpr'
```

This creates a restorable `.gzf` archive in ignored `backups/` and updates the small, Git-friendly `analysis/ghidra-annotations.tsv` export. The text file lists user-named symbols and variables, edited signatures, and comments. The GZF preserves the full Ghidra program, including analysis that the text export does not cover. Import the GZF into Ghidra to restore it. Keep a copy of `backups/` outside this repo for long-term safety.
