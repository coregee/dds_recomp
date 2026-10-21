param(
    [string]$ProjectFile = (Join-Path $PSScriptRoot '..\..\ghidra\Nocturne.gpr'),
    [string]$ProgramName = 'candidate',
    [string]$EntriesFile = '',
    [int]$Workers = 3,
    [int]$TimeoutSeconds = 30,
    [string]$Headless = 'C:\Program Files\Ghidra\support\analyzeHeadless.bat',
    [switch]$OriginalProcessor
)
$ErrorActionPreference = 'Stop'
$root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$project = Get-Item -LiteralPath $ProjectFile
$output = Join-Path $root 'reference\ps2\whole-program'
New-Item -ItemType Directory -Path $output -Force | Out-Null
# Close this project's GUI before headless use. Read-only changes are not saved.
$env:GHIDRA_HEADLESS_MAXMEM = '8G'
$processorArgs = @()
$exportGuard = @('allow-original-divu')
if (!$OriginalProcessor) {
    $language = Join-Path $root 'build\ee-divu-fixed'
    if (!(Test-Path -LiteralPath (Join-Path $language 'r5900.sla'))) {
        throw 'Run tools\ghidra\prepare-ee-divu-fix.ps1 first'
    }
    $processorArgs = @('-postScript', 'UsePatchedEELanguage.java', $language)
    $exportGuard = @('require-unsigned-divu')
}
$selectionArgs = @()
$selectedCount = $null
if ($EntriesFile) {
    $selectionPath = (Resolve-Path -LiteralPath $EntriesFile).Path
    $selectionArgs += $selectionPath
    $selection = Get-Content -LiteralPath $selectionPath -Raw | ConvertFrom-Json
    $selectedCount = if ($selection.entries) { @($selection.entries).Count } else { @($selection).Count }
}
$summaryName = if ($EntriesFile) { 'partial-export-summary.json' } else { 'summary.json' }
$summaryPath = Join-Path $output $summaryName
# Ghidra can return exit code0 after a script error. A prior rolling summary
# must not be mistaken for this run's result.
if (Test-Path -LiteralPath $summaryPath) { Remove-Item -LiteralPath $summaryPath }
& $Headless $project.DirectoryName $project.BaseName -process $ProgramName -readOnly -noanalysis `
    -scriptPath $PSScriptRoot @processorArgs -postScript 'ExportExecutableEvidence.java' $output $Workers $TimeoutSeconds @exportGuard @selectionArgs
if ($LASTEXITCODE -ne 0) { throw "Ghidra export failed with exit code $LASTEXITCODE" }
if (!(Test-Path -LiteralPath $summaryPath)) { throw 'Ghidra did not produce a current export summary' }
$summary = Get-Content -LiteralPath $summaryPath -Raw | ConvertFrom-Json
if ($summary.status -ne 'complete') { throw 'Full-function export did not complete' }
if ($EntriesFile -and ($summary.selected_functions -ne $selectedCount -or $summary.exported -ne $selectedCount)) {
    throw 'Selected export count differs from the requested entries'
}
if ($EntriesFile -and !$summary.inventory_merged) { throw 'Selected export did not merge into the current recognized-function index' }
if (!$OriginalProcessor -and !$summary.divu_unsigned) { throw 'Corrected DIVU export verification failed' }
$summary | ConvertTo-Json
