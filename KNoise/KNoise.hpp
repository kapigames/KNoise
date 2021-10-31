#pragma once

#define __KNOISE__ 2.5
#include "PCH.hpp"


namespace KNoise {
    unsigned int ToSeed(std::string F_Text);        // Converts string to seed
    unsigned int ToSeed(std::wstring F_Text);       // Converts wstring to seed
    unsigned int ToSeed(std::u16string F_Text);     // Converts u16string to seed
    unsigned int ToSeed(std::u32string F_Text);     // Converts u32string to seed


    struct Vec3f {
        Vec3f(float F_x,float F_y,float F_z) { x=F_x; y=F_y; z=F_z; }
        float x, y, z;
    };

    struct Vec3d {
        Vec3d(double F_x,double F_y,double F_z) { x=F_x; y=F_y; z=F_z; }
        double x, y, z;
    };
}