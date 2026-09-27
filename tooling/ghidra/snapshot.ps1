param(
    [Parameter(Mandatory = $true)]
    [string]$ProjectFile,
    [string]$ProgramName = 'SLUS_209.74',
    [string]$Headless = 'C:\Program Files\Ghidra\support\analyzeHeadless.bat'
)

$ErrorActionPreference = 'Stop'
$repo = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$backupDir = Join-Path $repo 'backups'
$analysisDir = Join-Path $repo 'analysis'
$scriptDir = $PSScriptRoot
$executable = Join-Path (Join-Path $repo 'game') $ProgramName
$project = Get-Item -LiteralPath $ProjectFile
$projectDir = $project.DirectoryName
$projectName = $project.BaseName
$projectData = Join-Path $projectDir ($projectName + '.rep')

if ($project.Extension -ne '.gpr') { throw 'ProjectFile must be a Ghidra .gpr file' }
if (-not (Test-Path -LiteralPath $projectData -PathType Container)) { throw "Missing project data: $projectData" }
if (-not (Test-Path -LiteralPath $Headless -PathType Leaf)) { throw "Missing Ghidra headless launcher: $Headless" }
if (-not (Test-Path -LiteralPath $executable -PathType Leaf)) { throw "Missing extracted executable: $executable" }

New-Item -ItemType Directory -Path $backupDir, $analysisDir -Force | Out-Null
$stamp = Get-Date -Format 'yyyy-MM-dd-HHmmss'
$archive = Join-Path $backupDir ("$ProgramName-$stamp.gzf")
$stage = Join-Path $backupDir ('stage-' + [guid]::NewGuid().ToString('N'))
$annotationTemp = Join-Path $stage 'annotations.tsv'
$annotationOutput = Join-Path $analysisDir 'ghidra-annotations.tsv'
$exeHash = (Get-FileHash -LiteralPath $executable -Algorithm SHA256).Hash.ToLowerInvariant()

if (Test-Path -LiteralPath $archive) { throw "Archive already exists: $archive" }
New-Item -ItemType Directory -Path $stage | Out-Null
try {
    Copy-Item -LiteralPath $project.FullName -Destination $stage
    Copy-Item -LiteralPath $projectData -Destination $stage -Recurse

    & $Headless $stage $projectName -process $ProgramName -readOnly -noanalysis `
        -scriptPath $scriptDir `
        -postScript 'ExportAnnotations.java' $annotationTemp $exeHash `
        -postScript 'PackProgram.java' $archive
    if ($LASTEXITCODE -ne 0) { throw "Ghidra headless failed with exit code $LASTEXITCODE" }
    if (-not (Test-Path -LiteralPath $annotationTemp -PathType Leaf)) { throw 'Annotation export missing' }
    if (-not (Test-Path -LiteralPath $archive -PathType Leaf)) { throw 'GZF archive missing' }
    if ((Get-Item -LiteralPath $archive).Length -eq 0) { throw 'GZF archive is empty' }
    Copy-Item -LiteralPath $annotationTemp -Destination $annotationOutput -Force
    Write-Output "Archive: $archive"
    Write-Output "Archive SHA256: $((Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash.ToLowerInvariant())"
    Write-Output "Annotations: $annotationOutput"
}
finally {
    # Only remove the uniquely named temporary copy inside this repo's backups folder.
    $resolvedBackupDir = (Resolve-Path -LiteralPath $backupDir).Path.TrimEnd('\')
    $resolvedStage = (Resolve-Path -LiteralPath $stage).Path
    if (-not $resolvedStage.StartsWith($resolvedBackupDir + '\', [StringComparison]::OrdinalIgnoreCase)) {
        throw "Refusing to remove unexpected temporary path: $resolvedStage"
    }
    Remove-Item -LiteralPath $resolvedStage -Recurse -Force
}
