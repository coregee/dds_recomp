param(
    # A Ghidra project with reference\hd\input\GameAssembly.dll imported under
    # /pc and symbols applied by ImportIL2CppSymbols.java (not kept in the repo).
    [Parameter(Mandatory)] [string]$ProjectFile,
    [string]$Spec = (Join-Path $PSScriptRoot '..\..\reference\hd\ghidra\corpus-spec.json'),
    [string]$Output = (Join-Path $PSScriptRoot '..\..\reference\hd\ghidra\corpus'),
    [int]$Workers = 4,
    [int]$TimeoutSeconds = 20
)
$ErrorActionPreference = 'Stop'
$root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$project = Get-Item -LiteralPath $ProjectFile
New-Item -ItemType Directory -Path $Output -Force | Out-Null
# Save and close the PC project's GUI first; no project copy is created.
$env:GHIDRA_HEADLESS_MAXMEM = '8G'
New-Item -ItemType Directory -Path (Join-Path $root 'build') -Force | Out-Null
$headlessLog = Join-Path $root 'build\hd-corpus-headless.log'
& 'C:\Program Files\Ghidra\support\analyzeHeadless.bat' $project.DirectoryName ($project.BaseName + '/pc') -process 'GameAssembly.dll' -readOnly -noanalysis `
    -scriptPath $PSScriptRoot -postScript ExportHDReferenceCorpus.java $Spec $Output $Workers $TimeoutSeconds 2>&1 | Tee-Object -FilePath $headlessLog
if ($LASTEXITCODE -ne 0 -or (Get-Content -LiteralPath $headlessLog -Raw) -match 'REPORT SCRIPT ERROR|ERROR REPORT') { throw 'HD reference export failed' }
$summary = Get-Content -LiteralPath (Join-Path $Output 'summary.json') -Raw | ConvertFrom-Json
if ($summary.status -ne 'complete') { throw 'HD reference export did not complete' }
$summary | ConvertTo-Json
