$ErrorActionPreference = "Stop"
if (Test-Path -Path build){
}
else{
    mkdir -p build 
}
cd build
cmake -S .. -B .
cmake --build .
cp ../libs/SDL2/lib/x64/SDL2.dll ./Debug/SDL2.dll
./Debug/SDL2Game.exe
cd ..

