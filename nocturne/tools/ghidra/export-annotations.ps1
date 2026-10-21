# Refresh the text exports of the Ghidra project:
#   reference/ps2/ghidra-annotations.tsv  every user name, signature, variable and comment
#   reference/function-map.tsv            every function and how far it is recovered
# Close the project in the Ghidra GUI first. The project is opened read-only.
param(
    [string]$ProjectFile = (Join-Path $PSScriptRoot '..\..\ghidra\Nocturne.gpr'),
    [string]$ProgramName = 'candidate',
    [string]$Headless = 'C:\Program Files\Ghidra\support\analyzeHeadless.bat'
)
$ErrorActionPreference = 'Stop'
$root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$project = Get-Item -LiteralPath $ProjectFile
$build = Join-Path $root 'build'
New-Item -ItemType Directory -Path $build -Force | Out-Null
$sha = (Get-FileHash -LiteralPath (Join-Path $root 'game\SLUS_209.11') -Algorithm SHA256).Hash.ToLower()
$annotations = Join-Path $root 'reference\ps2\ghidra-annotations.tsv'
$functions = Join-Path $build 'ghidra-functions.tsv'
$log = Join-Path $build 'export-annotations.log'

& $Headless $project.DirectoryName $project.BaseName -process $ProgramName -readOnly -noanalysis `
    -scriptPath $PSScriptRoot `
    -postScript ExportAnnotations.java $annotations $sha `
    -postScript ExportFunctionNames.java $functions 2>&1 | Tee-Object -FilePath $log | Out-Null
if ($LASTEXITCODE -ne 0 -or (Get-Content -LiteralPath $log -Raw) -match 'REPORT SCRIPT ERROR|ERROR REPORT') {
    throw "Ghidra export failed; see $log"
}
python -I (Join-Path $root 'tools\function_map.py') $functions
