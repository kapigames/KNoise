#include "KNoise.hpp"
#include <iostream>

int main() {
    KNoise::Perlin Noise;

    for (size_t x = 0; x < 100000; x++)
    {
        std::cout << Noise.Get(kstd::vec3f(x/100.f,0,0), 0) << " double: " << Noise.Get(kstd::vec3d(x/100.0,0,0), 0) << std::endl;
    }
    
}