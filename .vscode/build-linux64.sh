PLATFORM="linux64"

echo Preparing compile for $PLATFORM...

rmdir --ignore-fail-on-non-empty -p bin/.temp/$PLATFORM

mkdir -p bin/$PLATFORM/KNoise
mkdir -p bin/$PLATFORM/Sandbox
mkdir -p bin/.temp/$PLATFORM


echo KNoise...
g++ -pipe -Wall -std=c++17 -c "KNoise/KNoise.cpp" -o "bin/.temp/$PLATFORM/KNoise.o"
g++ -pipe -Wall -std=c++17 -c "KNoise/Perlin.cpp" -o "bin/.temp/$PLATFORM/Perlin.o"


echo Creating library...
ar rcs "bin/$PLATFORM/KNoise/libKNoise.a" "bin/.temp/$PLATFORM/KNoise.o" "bin/.temp/$PLATFORM/Perlin.o"


echo Compiling sandbox...

g++ -pipe -Wall -std=c++17 "Sandbox/main.cpp" -IKNoise/ -Lbin/$PLATFORM/KNoise/ -lKNoise  -o "bin/$PLATFORM/Sandbox/Sandbox"
chmod +x "bin/$PLATFORM/Sandbox/Sandbox"

echo $PLATFORM compile done.