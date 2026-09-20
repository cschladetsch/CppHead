# install.ps1
$ErrorActionPreference = "Stop"

Write-Host "==> Triggering build process..." -ForegroundColor Cyan
if (Test-Path ".\build.ps1") {
    & .\build.ps1
} else {
    Write-Error "build.ps1 not found in the current directory."
    exit 1
}

$installDir = "$HOME\bin"
if (!(Test-Path $installDir)) {
    New-Item -ItemType Directory -Force -Path $installDir | Out-Null
}

$binaryName = "head.exe"
$sourcePath = "build\$binaryName"

if (!(Test-Path $sourcePath)) {
    $sourcePath = "build\Release\$binaryName"
}

if (!(Test-Path $sourcePath)) {
    Write-Error "Binary not found at build outputs: $sourcePath"
    exit 1
}

Write-Host "==> Installing $binaryName to $installDir..." -ForegroundColor Cyan
Copy-Item -Force $sourcePath $installDir

Write-Host "==> Installed successfully to $installDir\$binaryName" -ForegroundColor Green

$userPath = [Environment]::GetEnvironmentVariable("PATH", "User")
if ($userPath -notlike "*$installDir*") {
    Write-Host "==> Note: '$installDir' is not currently in your User PATH." -ForegroundColor Yellow
    Write-Host "    You can add it by running: [Environment]::SetEnvironmentVariable('PATH', $userPath + ';$installDir', 'User')" -ForegroundColor Yellow
}
