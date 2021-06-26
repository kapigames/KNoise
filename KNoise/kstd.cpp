#include "kstd.hpp"


kstd::vec4f::vec4f(float F_x,float F_y,float F_z,float F_w)         { x=F_x; y=F_y; z=F_z; w=F_w;   }
kstd::vec3f::vec3f(float F_x,float F_y,float F_z)                   { x=F_x; y=F_y; z=F_z;          }
kstd::vec2f::vec2f(float F_x,float F_y)                             { x=F_x; y=F_y;                 }

kstd::vec4d::vec4d(double F_x,double F_y,double F_z,double F_w)     { x=F_x; y=F_y; z=F_z; w=F_w;   }
kstd::vec3d::vec3d(double F_x,double F_y,double F_z)                { x=F_x; y=F_y; z=F_z;          }
kstd::vec2d::vec2d(double F_x,double F_y)                           { x=F_x; y=F_y;                 }
