#ifndef REALITY_MATH_MAT4_H
#define REALITY_MATH_MAT4_H

#include "r_math/vec4.h"
#include <iostream>

namespace reality
{
    namespace r_math
    {
        struct Mat4f
        {
            Mat4f();
            Mat4f(const Vec4f &v1, const Vec4f &v2,
                  const Vec4f &v3, const Vec4f &v4);

            Mat4f operator*(const Mat4f &other);
            Vec4f operator*(const Vec4f &vec4f);

            float data[4][4] = {0.0f};

            static Mat4f projection(float fov, float aspect, float near, float far);
            static Mat4f translate(float x, float y, float z);
            static Mat4f scale(float x, float y, float z);
            static Mat4f reflect_x();

            friend std::ostream &operator<<(std::ostream &os, const Mat4f &mat);
        };
    }
}

#endif
