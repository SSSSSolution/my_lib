#ifndef REALITY_CHARIZARD_SOFT_RENDERER_H
#define REALITY_CHARIZARD_SOFT_RENDERER_h

#include "r_math/vec2.h"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <assert.h>

namespace reality
{
namespace charizard {

struct PresentImage
{
    char32_t *data;
    int width;
    int height;
};

// basic draw alogrithm

/*
 * implemention of DDA(Digital Differential Analyzer) alogrithm
 */
void draw_line_DDA(PresentImage *image, r_math::Vec2f start, r_math::Vec2f end, char32_t color);

/*
 * implemention of Bresenham alogrithm
 */
void draw_line_Bresenham(PresentImage *image, r_math::Vec2f start, r_math::Vec2f end, char32_t color);

}
}

#endif
