@echo off
set PLATFORM=windows
set CPPSTD=c++17

echo Preparing compile for %PLATFORM%...

rmdir /s /q bin\.temp\%PLATFORM%

mkdir bin\%PLATFORM%\KNoise
mkdir bin\%PLATFORM%\Sandbox
mkdir bin\.temp\%PLATFORM%


echo KNoise...
g++ -pipe -Wall -std=%CPPSTD% -c "KNoise/KNoise.cpp" -o "bin/.temp/%PLATFORM%/KNoise.o"
g++ -pipe -Wall -std=%CPPSTD% -c "KNoise/Perlin.cpp" -o "bin/.temp/%PLATFORM%/Perlin.o"


echo Creating library...
ar rcs "bin/%PLATFORM%/KNoise/libKNoise.a" "bin/.temp/%PLATFORM%/KNoise.o" "bin/.temp/%PLATFORM%/Perlin.o"


echo Compiling sandbox...

g++ -pipe -Wall -std=%CPPSTD% "Sandbox/main.cpp" -static -IKNoise/ -Lbin/%PLATFORM%/KNoise/ -lKNoise  -o "bin/%PLATFORM%/Sandbox/Sandbox"

echo %PLATFORM% compile done.