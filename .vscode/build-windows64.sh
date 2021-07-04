PLATFORM="windows64"

echo Preparing compile for $PLATFORM...

rmdir --ignore-fail-on-non-empty -p bin/.temp/$PLATFORM

mkdir -p bin/$PLATFORM/KNoise
mkdir -p bin/$PLATFORM/Sandbox
mkdir -p bin/.temp/$PLATFORM


echo KNoise...
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/KNoise.hpp" -o "bin/.temp/$PLATFORM/KNoise.o"
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/KNoise.cpp" -o "bin/.temp/$PLATFORM/KNoise-cpp.o"
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/Perlin.hpp" -o "bin/.temp/$PLATFORM/Perlin.o"
x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 -c "KNoise/Perlin.cpp" -o "bin/.temp/$PLATFORM/Perlin-cpp.o"


echo Creating library...
x86_64-w64-mingw32-ar rcs "bin/$PLATFORM/KNoise/libKNoise.a" "bin/.temp/$PLATFORM/KNoise.o" "bin/.temp/$PLATFORM/KNoise-cpp.o" "bin/.temp/$PLATFORM/Perlin.o" "bin/.temp/$PLATFORM/Perlin-cpp.o"


echo Compiling sandbox...

x86_64-w64-mingw32-g++ -pipe -Wall -std=c++17 "Sandbox/main.cpp" -IKNoise/ -Lbin/$PLATFORM/KNoise/ -lKNoise  -o "bin/$PLATFORM/Sandbox/Sandbox"

echo $PLATFORM compile done.