#include "Perlin.hpp"
#include "KNoise.hpp"
#include <iostream>
#include <thread>
#include <chrono>


int main() {
    KNoise::Perlin Noise;

    size_t y = 0;
    size_t seed = 200000;
    while (true)
    {

        for (size_t x = 0; x < 188; x++)
        {
                
            float a = Noise.Get(KNoise::Vec3f(x/60.f, y/60.f, 0.0), seed); // Seed cant be 0 from this release due to changes in code
            int b = round(a * 15.f);
            
            switch (b)
            {
            case 2:
                std::cout << " ";
                break;
            case 3:
                std::cout << ".";
                break;
            case 4:
                std::cout << "-";
                break;
            case 5:
                std::cout << ":";
                break;
            case 6:
                std::cout << "!";
                break;
            case 7:
                std::cout << "*";
                break;
            case 8:
                std::cout << "+";
                break;
            case 9:
                std::cout << "=";
                break;
            case 10:
                std::cout << "%";
                break;
            case 11:
                std::cout << "#";
                break;
            case 12:
                std::cout << "@";
                break;
            
            default:
                break;
            }

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::cout << std::endl;
        y++;
        std::cout << Noise.GetCacheSize() << "   " << Noise.GetCacheType();
    }
    
    
}