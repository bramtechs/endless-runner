$ErrorActionPreference = "Stop"
if (Test-Path -Path build){
}
else{
    mkdir -p build 
}
cmake --build ./build/
