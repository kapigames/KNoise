KNoise is lightweight, fast and open source library for generating noise using perlin algorithm and possibly other algorithms in the future.

Usage:
    Include KNoise.hpp header in your program and create KNoise::Perlin class
    You can get noise value in range from 0.0 to 1.0 using Get(Vec3f, seed) function eg:
    KNoise::Perlin Noise;
    float a = Noise.Get(Vec3f( 4, 2, 0 ), 69);