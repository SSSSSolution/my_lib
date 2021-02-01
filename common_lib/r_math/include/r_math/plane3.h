#ifndef REALITY_MATH_PLANE3_H
#define REALITY_MATH_PLANE3_H

#include "r_math/vec3.h"

namespace reality
{
    namespace r_math
    {
        class Plane3
        {
        public:
            Plane3(Vec3f &A, Vec3f B, Vec3f C)
                : m_A(A), m_B(B), m_C(C)
            {}

        private:
            Vec3f m_A;
            Vec3f m_B;
            Vec3f m_C;
        };
    }
}

#endif
