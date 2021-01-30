#ifndef REALITY_R_MATH_VEC2_H
#define REALITY_R_MATH_VEC2_H

namespace reality
{
    namespace r_math
    {
    template <typename T>
    struct Vec2
    {
        Vec2() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
        Vec2(T x, T y) : x(x), y(y) {}

        int cross_product(const Vec2<T> &other)
        {
            return x * other.y - y * other.x;
        }

        T x;
        T y;
    };

    typedef Vec2<float> Vec2f;
    typedef Vec2<int>   Vec2i;
    }
}

#endif
