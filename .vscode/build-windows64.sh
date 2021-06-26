PLATFORM="windows64"

echo Preparing compile for $PLATFORM...

rmdir --ignore-fail-on-non-empty -p bin/.temp/$PLATFORM

mkdir -p bin/$PLATFORM/KNoise
mkdir -p bin/$PLATFORM/Sandbox
mkdir -p bin/.temp/$PLATFORM


echo Compiling kstd...
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/kstd.hpp" -o "bin/.temp/$PLATFORM/kstd.o"
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/kstd.cpp" -o "bin/.temp/$PLATFORM/kstd-cpp.o"

echo KNoise...
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/KNoise.hpp" -o "bin/.temp/$PLATFORM/KNoise.o"
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/KNoise.cpp" -o "bin/.temp/$PLATFORM/KNoise-cpp.o"


echo Creating library...
x86_64-w64-mingw32-ar rcs "bin/$PLATFORM/KNoise/libKNoise.a" "bin/.temp/$PLATFORM/kstd.o" "bin/.temp/$PLATFORM/kstd-cpp.o" "bin/.temp/$PLATFORM/KNoise.o" "bin/.temp/$PLATFORM/KNoise-cpp.o"


echo Compiling sandbox...

x86_64-w64-mingw32-g++ -pipe -Wall -static -std=c++17 "Sandbox/main.cpp" -IKNoise/ -Lbin/$PLATFORM/KNoise/ -lKNoise  -o "bin/$PLATFORM/Sandbox/Sandbox.exe"

echo $PLATFORM compile done.