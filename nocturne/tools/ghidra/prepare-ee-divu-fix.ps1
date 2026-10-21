param(
    [string]$Ghidra = 'C:\Program Files\Ghidra',
    [string]$Output = (Join-Path $PSScriptRoot '..\..\build\ee-divu-fixed')
)
$ErrorActionPreference = 'Stop'
$source = Join-Path $Ghidra 'Ghidra\Extensions\ghidra-emotionengine-reloaded\data\languages'
$expected = 'E7EE7475FF766814219CC3B653D11A3EA4EF3A7E96E09AC27439A676DF33FD9A'
$hash = (Get-FileHash -LiteralPath (Join-Path $source 'mips.sinc')).Hash
if ($hash -ne $expected) { throw "Unreviewed processor source: $hash" }
New-Item -ItemType Directory -Path $Output -Force | Out-Null
Copy-Item -Path (Join-Path $source '*') -Destination $Output -Recurse -Force
$path = Join-Path $Output 'mips.sinc'
$text = [IO.File]::ReadAllText($path)
$pattern = '(?s)(:divu RS32src, RT32src.*?\{)(.*?)(\})'
$match = [regex]::Match($text, $pattern)
if (!$match.Success) { throw 'Expected DIVU constructor missing' }
$body = $match.Groups[2].Value
if (!$body.Contains('RS32src s/ RT32src') -or !$body.Contains('RS32src s% RT32src')) {
    throw 'Expected signed DIVU operations missing'
}
$body = $body.Replace('RS32src s/ RT32src', 'RS32src / RT32src').Replace('RS32src s% RT32src', 'RS32src % RT32src')
$replacement = $match.Groups[1].Value + $body + $match.Groups[3].Value
$text = $text.Substring(0, $match.Index) + $replacement + $text.Substring($match.Index + $match.Length)
[IO.File]::WriteAllText($path, $text, [Text.UTF8Encoding]::new($false))
& (Join-Path $Ghidra 'support\sleigh.bat') (Join-Path $Output 'r5900.slaspec') (Join-Path $Output 'r5900.sla')
if ($LASTEXITCODE -ne 0) { throw "SLEIGH compile failed: $LASTEXITCODE" }
Get-FileHash -LiteralPath $path, (Join-Path $Output 'r5900.sla')
# The installed extension and open GUI are deliberately untouched.
