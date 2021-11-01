# What is KNoise?
KNoise is lightweight, fast and open source library for generating noise using perlin algorithm and possibly other algorithms in the future.

## Fast tutorial
To use KNoise in your program you need to create `KNoise::Perlin` class,
this class handles cacheing and some other stuff for you to speed up noise generation.
To get noise values use `Get();` funtion and pass position as `KNoise::Vec3f` or `KNoise::Vec3d` struct and seed eg: `Noise.Get(KNoise::Vec3f(123, 456, 789), 12);`, this will return float with value from 0.0 to 1.0. When you pass Vec3f return value will be float and if Vec3d it will be double, theres no cost of using doubles or floats at least on my PC.
Also if you're getting some warnings in visual studio you can ignore them everything should work fine.

## Compiling
Run build tast (ctrl+shift+b) in vs code or create build directory and from there run `cmake ../` and after `cmake --build .` this will build sandbox which curently contains some tests to test if everything works fine and performance, probably will add some examples later.