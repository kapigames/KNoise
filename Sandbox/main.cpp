#include "Perlin.hpp"
#include "KNoise.hpp"
#include <iostream>
#include <thread>
#include <chrono>


using namespace KNoise;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


void test_noise(Perlin* Noise) {
    if(Noise->Get(Vec3f(0,0,0), 0) != 0.5f) {
        exit(1);
    }

    if(Noise->Get(Vec3d(0,0,0), 0) != 0.5) {
        exit(2);
    }
}


void test_perf(Perlin* Noise) {
    Noise->ClearCache();
    auto t1 = high_resolution_clock::now();
    std::cout << "Testing perf using floats..."; 
    for (size_t seed = 0; seed < 10000; seed++)
    {
        for (size_t x = 0; x < 100; x++)
        {
            Noise->Get(Vec3f(x/100.f,0,0), seed);
        }
    }
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << " " << ms_double.count() << "ms";

    Noise->ClearCache();
    std::cout << std::endl << "Testing perf using doubles...";

    auto t3 = high_resolution_clock::now();
    for (size_t seed = 0; seed < 10000; seed++)
    {
        for (size_t x = 0; x < 100; x++)
        {
            Noise->Get(Vec3d(x/100.0,0,0), seed);
        }
    }
    auto t4 = high_resolution_clock::now();

    ms_double = t4 - t3;
    std::cout << " " << ms_double.count() << "ms" << std::endl;
}



void test_real_perf(Perlin* Noise) {
    Noise->ClearCache();
    auto t1 = high_resolution_clock::now();
    std::cout << "Testing perf using floats..."; 
    for (size_t x = 0; x < 1000; x++)
    {
        for (size_t y = 0; y < 1000; y++)
        {
            Noise->Get(Vec3f(x/100.f,y/100.f,0), 12354);
            Noise->Get(Vec3f(x/100.f,y/100.f,0), 54634);
            Noise->Get(Vec3f(x/100.f,y/100.f,0), 86765);
            Noise->Get(Vec3f(x/100.f,y/100.f,0), 23465);
            Noise->Get(Vec3f(x/100.f,y/100.f,0), 85673);
            Noise->Get(Vec3f(x/100.f,y/100.f,0), 45687);
        }
    }
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << " " << ms_double.count() << "ms";

    Noise->ClearCache();
    std::cout << std::endl << "Testing perf using doubles...";

    auto t3 = high_resolution_clock::now();
    for (size_t x = 0; x < 1000; x++)
    {
        for (size_t y = 0; y < 1000; y++)
        {
            Noise->Get(Vec3d(x/100.0,y/100.0,0), 12354);
            Noise->Get(Vec3d(x/100.0,y/100.0,0), 54634);
            Noise->Get(Vec3d(x/100.0,y/100.0,0), 86765);
            Noise->Get(Vec3d(x/100.0,y/100.0,0), 23465);
            Noise->Get(Vec3d(x/100.0,y/100.0,0), 85673);
            Noise->Get(Vec3d(x/100.0,y/100.0,0), 45687);
        }
    }
    auto t4 = high_resolution_clock::now();

    ms_double = t4 - t3;
    std::cout << " " << ms_double.count() << "ms" << std::endl;
}



int main() {
    std::cout << "Testing caches..." << std::endl;

    Perlin Noise;

    std::cout << "Single" << std::endl;
    Noise.SetCacheType(Noise.Single);
    test_noise(&Noise);

    std::cout << "Array" << std::endl;
    Noise.SetCacheType(Noise.Array);
    test_noise(&Noise);

    std::cout << "Index" << std::endl;
    Noise.SetCacheType(Noise.Index);
    test_noise(&Noise);



    std::cout << std::endl << "Testing cache performance..." << std::endl;

    std::cout << "Single" << std::endl;
    Noise.SetCacheType(Noise.Single);
    test_perf(&Noise);

    std::cout << "Array" << std::endl;
    Noise.SetCacheType(Noise.Array);
    test_perf(&Noise);

    std::cout << "Index" << std::endl;
    Noise.SetCacheType(Noise.Index);
    test_perf(&Noise);



    std::cout << std::endl << "Testing real cache performance..." << std::endl;

    std::cout << "Single" << std::endl;
    Noise.SetCacheType(Noise.Single);
    test_real_perf(&Noise);

    std::cout << "Array" << std::endl;
    Noise.SetCacheType(Noise.Array);
    test_real_perf(&Noise);

    std::cout << "Index" << std::endl;
    Noise.SetCacheType(Noise.Index);
    test_real_perf(&Noise);

    std::cout << "All tests ok." << std::endl;
    
    return 0;
}