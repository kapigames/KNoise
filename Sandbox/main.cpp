#include "KNoise.hpp"
#include <iostream>

int main() {
    KNoise::Perlin Noise;

    int x = 0;

    while (true)
    {

        for (size_t y = 0; y < 100; y++)
        {
            
            float a = Noise.Get(KNoise::Vec3f(x/20.f, y/20.f, 0.0), 0);
            int b = int(a * 10.f);

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

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << std::endl;
        x++;
        
    }
    
    
}