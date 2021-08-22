#pragma once

#define __KNOISE__ 2.1

#include <iostream>
#include <string>


namespace KNoise {

    unsigned int ToSeed(std::string F_Text);    // Converts string to seed

    struct Vec3f {
        Vec3f(float F_x,float F_y,float F_z) { x=F_x; y=F_y; z=F_z; }
        float x, y, z;
    };

    struct Vec3d {
        Vec3d(double F_x,double F_y,double F_z) { x=F_x; y=F_y; z=F_z; }
        double x, y, z;
    };

}