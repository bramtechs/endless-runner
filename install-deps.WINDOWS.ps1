
if (Test-Path -Path "./libs/SDL2"){
    Write-Host "SDL2 already installed"
    return
}

$OutFile = ".\SDL2.zip";

if (-Not (Test-Path -Path "SDL2.zip")){
    Write-Host "SDL2 not installed. Downloading..."
    Invoke-RestMethod -Uri "https://github.com/libsdl-org/SDL/releases/download/release-2.24.0/SDL2-devel-2.24.0-VC.zip" -OutFile $OutFile 
}
Write-Host "Extracting zip..."
Expand-Archive $OutFile -DestinationPath "./libs/"
Rename-Item -Path "./libs/SDL2-2.24.0" -NewName "SDL2"

Write-Host "You will need to copy SDL2.dll to the build directory for each build target!"
