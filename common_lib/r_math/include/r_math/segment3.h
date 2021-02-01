#ifndef REALITY_MATH_SEGMENT_H
#define REALITY_MATH_SEGMENT_H

#include "vec3.h"
#include "r_math/plane3.h"

namespace reality
{
    namespace r_math
    {
        class Segment3
        {
        public:
            Segment3(Vec3f start, Vec3f end)
                : m_start(start), m_end(end)
            {}

            bool find_intersection(const Plane3 &other, Vec3f &inter_point);

        private:
            Vec3f m_start;
            Vec3f m_end;
        };
    }
}

#endif
