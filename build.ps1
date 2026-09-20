$ErrorActionPreference = "Stop"

Write-Host "==> Configuring and building CppHead (Release)..." -ForegroundColor Cyan
cmake -B build -S .
cmake --build build --config Release

Write-Host "==> Running performance comparison..." -ForegroundColor Cyan

# Ensure a test file exists with 10,000 lines
$TestFile = "benchmark_temp.txt"
1..10000 | ForEach-Object { "This is benchmark line number $_" } | Set-Content $TestFile

# Dynamically resolve the built executable location across common CMake configurations
$CppHeadBin = "$PSScriptRoot\build\head.exe"
if (-not (Test-Path $CppHeadBin)) {
    $CppHeadBin = "$PSScriptRoot\build\Release\head.exe"
}
if (-not (Test-Path $CppHeadBin)) {
    $CppHeadBin = "$PSScriptRoot\build\Debug\head.exe"
}

if (Test-Path $CppHeadBin) {
    # 1. Benchmark CppHead (First 1,000 lines using Unix -n flag)
    $CppWatch = [System.Diagnostics.Stopwatch]::StartNew()
    & $CppHeadBin -n 1000 $TestFile | Out-Null
    $CppWatch.Stop()
    Write-Host "[Benchmark] CppHead (1,000 lines):       " -NoNewline
    Write-Host "$($CppWatch.ElapsedTicks / [System.Diagnostics.Stopwatch]::Frequency * 1000000) µs" -ForegroundColor Green
} else {
    Write-Error "Could not find compiled head executable. Checked build\, build\Release\, and build\Debug\."
}

# 2. Benchmark PowerShell Get-Content (First 1,000 lines)
$PsWatch = [System.Diagnostics.Stopwatch]::StartNew()
Get-Content $TestFile -TotalCount 1000 | Out-Null
$PsWatch.Stop()
Write-Host "[Benchmark] PowerShell Get-Content:     " -NoNewline
Write-Host "$($PsWatch.ElapsedTicks / [System.Diagnostics.Stopwatch]::Frequency * 1000000) µs" -ForegroundColor Yellow

# Cleanup
Remove-Item $TestFile -ErrorAction SilentlyContinue
