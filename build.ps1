# build.ps1
$ErrorActionPreference = "Stop"

Write-Host "==> Ensuring required directories exist..." -ForegroundColor Cyan
if (!(Test-Path "tests")) { New-Item -ItemType Directory -Path "tests" | Out-Null }

Write-Host "==> Creating build directory..." -ForegroundColor Cyan
if (!(Test-Path "build")) {
    New-Item -ItemType Directory -Name "build" | Out-Null
}

Write-Host "==> Configuring CMake with Clang..." -ForegroundColor Cyan
cmake -B build -S . `
    -DCMAKE_C_COMPILER=clang `
    -DCMAKE_CXX_COMPILER=clang++ `
    -DCMAKE_BUILD_TYPE=Release `
    -DBUILD_TESTING=ON

Write-Host "==> Building CppHead, tests, and benchmarks..." -ForegroundColor Cyan
cmake --build build --config Release

Write-Host "==> Running unit tests..." -ForegroundColor Cyan
ctest --test-dir build --output-on-failure -C Release

Write-Host "==> Running performance benchmark..." -ForegroundColor Cyan
$benchmarkExe = "build\cpphead_benchmark.exe"
if (!(Test-Path $benchmarkExe)) {$benchmarkExe = "build\Release\cpphead_benchmark.exe"
}

if (Test-Path $benchmarkExe) {
    & $benchmarkExe
} else {
    Write-Warning "Benchmark executable not found."
}

Write-Host "==> Build, test, and benchmark completed successfully!" -ForegroundColor Green
