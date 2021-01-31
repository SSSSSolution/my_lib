#ifndef REALITY_R_MATH_VEC3_H
#define REALITY_R_MATH_VEC3_H

#include <math.h>
namespace reality
{
    namespace r_math
    {
    template <typename T>
    struct Vec3
    {
        Vec3() : x(0), y(0), z(0)
        {}

        Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        T x;
        T y;
        T z;

        void normalize()
        {
            float n = std::sqrt(x*x + y*y + z*z);
            x = x / n;
            y = y / n;
            z = z / n;
        }

        friend Vec3 operator*(T s, const Vec3 &vec3);
    };

    typedef Vec3<float> Vec3f;
    typedef Vec3<int>   Vec3i;

    template <typename T>
    Vec3<T> operator*(T s, const Vec3<T> &vec3)
    {
        Vec3<T> ret;
        ret.x = s * vec3.x;
        ret.y = s * vec3.y;
        ret.z = s * vec3.z;

        return ret;
    }
    }
}

#endif
