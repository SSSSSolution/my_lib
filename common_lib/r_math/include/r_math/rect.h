#ifndef REALITY_R_MATH_RECT_H
#define REALITY_R_MATH_RECT_H

#include <vector>

namespace reality {
namespace r_math {
    template <typename T>
    struct Rect
    {
        Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height)
        {}

        T x;
        T y;
        T width;
        T height;
    };

    typedef Rect<int> Recti;
    typedef Rect<float> Rectf;
}
}







#endif
