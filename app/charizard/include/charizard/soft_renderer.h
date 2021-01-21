#ifndef REALITY_CHARIZARD_SOFT_RENDERER_H
#define REALITY_CHARIZARD_SOFT_RENDERER_h

#include "model.h"

#include "r_math/vec2.h"
#include "r_math/vec3.h"
#include "r_math/rect.h"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <assert.h>
#include <vector>
#include <memory>

namespace reality
{
namespace charizard {

struct PresentImage
{
    char32_t *data;
    int width;
    int height;
};

enum SampleCount
{
    Sample_Count_1 = 1,
    Sample_Count_4 = 4,
    Sample_Count_16 = 16,
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

/*
 *  rasteration triangle
 */
void draw_triangle(PresentImage *image, const r_math::Recti &sub_rect, r_math::Vec2f &p1, r_math::Vec2f &p2, r_math::Vec2f &p3, SampleCount sample, char32_t color);

class SoftRenderer
{
public:
    SoftRenderer();


private:
    std::vector<std::shared_ptr<Model>> m_model_list;
};

}
}

#endif



