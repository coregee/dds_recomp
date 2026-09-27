# Digital Devil Saga disc extractor

Put an ISO in the repository root, then run:

```powershell
python tooling/disc_extract.py
```

The script uses the alphabetically first `.iso` file in the root and extracts its files under `game/`. It compares every file against the USA release hashes in `sha256.json` and logs differences as warnings. Warnings do not stop extraction.

Existing files are checked and left alone. Run `python tooling/disc_extract.py --overwrite` to replace them from the ISO.
