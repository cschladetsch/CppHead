# install.ps1
$ErrorActionPreference = "Stop"

$installDir = "$HOME\bin"
if (!(Test-Path $installDir)) {
    New-Item -ItemType Directory -Force -Path $installDir | Out-Null
}

# Determine binary path based on multi-config (MSVC) or single-config (Ninja/Makefiles) generators
$binaryName = "cpphead.exe"
$sourcePath = "build\Release\$binaryName"

if (!(Test-Path $sourcePath)) {
    $sourcePath = "build\$binaryName"
}

if (!(Test-Path $sourcePath)) {
    Write-Error "Binary not found at build outputs. Please run .\build.ps1 first."
    exit 1
}

Write-Host "==> Installing $binaryName to $installDir..." -ForegroundColor Cyan
Copy-Item -Force $sourcePath $installDir

Write-Host "==> Installed successfully to $installDir\$binaryName" -ForegroundColor Green

# Check if install directory is in user PATH
$userPath = [Environment]::GetEnvironmentVariable("PATH", "User")
if ($userPath -notlike "*$installDir*") {
    Write-Host "==> Note: '$installDir' is not currently in your User PATH." -ForegroundColor Yellow
    Write-Host "    You can add it by running: [Environment]::SetEnvironmentVariable('PATH', $userPath + ';$installDir', 'User')" -ForegroundColor Yellow
}
