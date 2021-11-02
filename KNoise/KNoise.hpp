#pragma once

#define __KNOISE__ 2.6
#include "PCH.hpp"


namespace KNoise {
    unsigned int ToSeed(std::string F_Text);        // Converts string to seed
    unsigned int ToSeed(std::wstring F_Text);       // Converts wstring to seed
    unsigned int ToSeed(std::u16string F_Text);     // Converts u16string to seed
    unsigned int ToSeed(std::u32string F_Text);     // Converts u32string to seed


    // Pre declarations
    // Float vectors
    struct V3f {
        float x, y, z;
    };


    // Double vectors
    struct V3d{
        double x, y, z;
    };


    V3f Vec3f(float x, float y, float z);
    V3f Vec2f(float x, float y);
    V3f Vec1f(float x);

    V3d Vec3d(double x, double y, double z);
    V3d Vec2d(double x, double y);
    V3d Vec1d(double x);
}