// Part of my unreleased library
// This library maybe released later :)
// Used for vectors


#ifndef _KSTD_
#define _KSTD_


namespace kstd {


    // -------
    // Vectors
    // -------

    struct vec4f {
        vec4f(float F_x,float F_y,float F_z,float F_w) { x=F_x; y=F_y; z=F_z; w=F_w; }
        float x, y, z, w;
    };

    struct vec3f {
        vec3f(float F_x,float F_y,float F_z) { x=F_x; y=F_y; z=F_z; }
        float x, y, z;
    };

    struct vec2f {
        vec2f(float F_x,float F_y) { x=F_x; y=F_y; }
        float x, y;
    };


    // -------
    // Double vectors
    // -------

    struct vec4d {
        vec4d(double F_x,double F_y,double F_z,double F_w) { x=F_x; y=F_y; z=F_z; w=F_w; }
        double x, y, z, w;
    };

    struct vec3d {
        vec3d(double F_x,double F_y,double F_z) { x=F_x; y=F_y; z=F_z; }
        double x, y, z;
    };

    struct vec2d {
        vec2d(double F_x,double F_y) { x=F_x; y=F_y; }
        double x, y;
    };
}


#endif