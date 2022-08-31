$ErrorActionPreference = "Stop"
if (Test-Path -Path build){
}
else{
    mkdir -p build 
}
cd build
cmake -S .. -B .
cmake --build .
cd ..
