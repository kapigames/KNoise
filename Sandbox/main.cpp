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



void test_ToSeed() {
    std::cout << "u32string" << std::endl;
    if(86917 != ToSeed(U"ąbć")) {
        exit(3);
    }

    std::cout << "u16string" << std::endl;
    if(ToSeed(u"ąbć") != ToSeed(U"ąbć")) {
        exit(4);
    }

    std::cout << "wstring" << std::endl;
    if(ToSeed(L"ąbć") != ToSeed(U"ąbć")) {
        exit(6);
    }

    std::cout << "string" << std::endl;
    if(ToSeed("ąbć") != ToSeed(U"ąbć")) {
        exit(3);
    }
}



void test_thread(Perlin* Noise) {
    for (size_t i = 0; i < 1000000; i++)
    {
        Noise->Get(Vec1f(i/100.f), 123);
    }
}


void test_threads(Perlin* Noise) {
    std::thread thread1, thread2;
    std::cout << std::endl << "Starting threads..." << std::endl;


    Noise->SetCacheType(Noise->Single);
    thread1 = std::thread(test_thread, Noise);
    thread2 = std::thread(test_thread, Noise);
    
    thread1.join();
    thread2.join();


    Noise->SetCacheType(Noise->Array);
    thread1 = std::thread(test_thread, Noise);
    thread2 = std::thread(test_thread, Noise);

    thread1.join();
    thread2.join();


    Noise->SetCacheType(Noise->Index);
    thread1 = std::thread(test_thread, Noise);
    thread2 = std::thread(test_thread, Noise);
    
    thread1.join();
    thread2.join();
}



void thread_perf_scaleing_thread(Perlin* Noise) {
    for (size_t i = 0; i < 1000000; i++)
    {
        Noise->Get(Vec1f(i/100.f), 123);
    }
}


void thread_perf_scaleing(Perlin* Noise) {
    for (size_t i = 1; i < std::thread::hardware_concurrency()+1; i++)
    {
        std::vector<std::thread> t;
        auto t1 = high_resolution_clock::now();
        for (size_t threads = 0; threads < i; threads++)
        {
            t.push_back(std::thread(thread_perf_scaleing_thread, Noise));
        }

        for (size_t threadss = 0; threadss < i; threadss++)
        {
            t[threadss].join();
        }

        auto t2 = high_resolution_clock::now();

        duration<double, std::milli> ms_double = t2 - t1;
        std::cout << i <<  " threads finished in " << ms_double.count() << "ms, ";
        std::cout << "it took " << ms_double.count()/i << "ms to calculate 1M noise values" << std::endl;
    }
}



int main() {
    std::cout << "Testing StringToSeed..." << std::endl;
    test_ToSeed();
    std::cout << std::endl;


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


    std::cout << std::endl << "Testing if thread save..." << std::endl;
    test_threads(&Noise);

    std::cout << std::endl << "Testing threads overhead..." << std::endl;
    thread_perf_scaleing(&Noise);

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