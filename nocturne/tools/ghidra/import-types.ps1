# Import nocturne_types.h into the Ghidra program, type the data tables and
# apply nocturne_signatures.tsv. Close the project in the Ghidra GUI first.
# Saves the program. Then refresh the text export with export-annotations.ps1.
param(
    [string]$ProjectFile = (Join-Path $PSScriptRoot '..\..\ghidra\Nocturne.gpr'),
    [string]$ProgramName = 'candidate',
    [string]$Headless = 'C:\Program Files\Ghidra\support\analyzeHeadless.bat'
)
$ErrorActionPreference = 'Stop'
$root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$project = Get-Item -LiteralPath $ProjectFile
New-Item -ItemType Directory -Path (Join-Path $root 'build') -Force | Out-Null
$log = Join-Path $root 'build\import-types.log'

& $Headless $project.DirectoryName $project.BaseName -process $ProgramName -noanalysis `
    -scriptPath $PSScriptRoot `
    -postScript ImportTypes.java (Join-Path $PSScriptRoot 'nocturne_types.h') (Join-Path $PSScriptRoot 'nocturne_signatures.tsv') `
    2>&1 | Tee-Object -FilePath $log | Select-String 'ImportTypes.java>|ERROR|Exception' | ForEach-Object Line
if ($LASTEXITCODE -ne 0 -or (Get-Content -LiteralPath $log -Raw) -match 'REPORT SCRIPT ERROR|ERROR REPORT') {
    throw "Type import failed; see $log"
}
