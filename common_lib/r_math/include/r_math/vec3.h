#ifndef REALITY_R_MATH_VEC3_H
#define REALITY_R_MATH_VEC3_H

namespace reality
{
    namespace r_math
    {
    template <typename T>
    struct Vec3
    {
        Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        T x;
        T y;
        T z;
    };

    typedef Vec3<float> Vec3f;
    typedef Vec3<int>   Vec3i;
    }
}

#endif
