#ifndef REALITY_MATH_VEC4_H
#define REALITY_MATH_VEC4_H

#include <iostream>

namespace reality
{
    namespace r_math
    {
    template <typename T>
    struct Vec4
    {
        Vec4() : x(0), y(0), z(0), w(0) {}
        Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        T x;
        T y;
        T z;
        T w;

//        template <typename T>
        friend std::ostream &operator<<(std::ostream &os, const Vec4<T> &vec)
        {
            os << "[ " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " ]" << std::endl;

            return os;
        }
    };

    typedef Vec4<float> Vec4f;
    typedef Vec4<int>   Vec4i;

    }
}







#endif
