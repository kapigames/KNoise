#include "Perlin.hpp"
#include "KNoise.hpp"
#include <iostream>
#include <chrono>
#include <thread>


int main() {
    KNoise::Perlin Noise;

    Noise.SetCacheType(Noise.FastArray);

    for (size_t x = 0; x < 100; x++)
    {
        for (size_t y = 0; y < 100; y++)
        {
                
            float a = Noise.Get(KNoise::Vec3f(x/10.f, y/10.f, 0.0), KNoise::ToSeed("a")); // Seed cant be 0 from this release due to changes in code
            int b = round(a * 10.f);

            switch (b)
            {
            case 0:
                std::cout << " ";
                break;
            case 1:
                std::cout << ".";
                break;
            case 2:
                std::cout << ":";
                break;
            case 3:
                std::cout << "-";
                break;
            case 4:
                std::cout << "!";
                break;
            case 5:
                std::cout << "+";
                break;
            case 6:
                std::cout << "*";
                break;
            case 7:
                std::cout << "#";
                break;
            case 8:
                std::cout << "%";
                break;
            case 9:
                std::cout << "@";
                break;
            case 10:
                std::cout << "▮";
                break;
            
            default:
                break;
            }

        }

        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::cout << std::endl;
         
    }
    
    
}