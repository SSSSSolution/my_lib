#ifndef REALITY_CHARIZARD_SOFT_RENDERER_H
#define REALITY_CHARIZARD_SOFT_RENDERER_H

#include "scenes.h"
#include "types.h"

#include "r_math/vec2.h"
#include "r_math/vec3.h"
#include "r_math/vec4.h"
#include "r_math/rect.h"

#include <iostream>
#include <algorithm>
#include <math.h>
#include <assert.h>
#include <vector>
#include <memory>
#include <mutex>

namespace reality
{
namespace charizard {

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
void draw_line_DDA(std::shared_ptr<FrameBuffer> fb, r_math::Vec2f start, r_math::Vec2f end, char32_t color);

/*
 * implemention of Bresenham alogrithm
 */
void draw_line_Bresenham(std::shared_ptr<FrameBuffer> fb, r_math::Vec2f start, r_math::Vec2f end, char32_t color);

/*
 *  rasteration triangle
 */
void draw_triangle(std::shared_ptr<FrameBuffer> fb, const r_math::Recti &sub_rect, r_math::Vec2f &p1, r_math::Vec2f &p2, r_math::Vec2f &p3, SampleCount sample, char32_t color);

class SoftRenderer
{
public:
    SoftRenderer();

    void set_scenes(std::shared_ptr<Scenes> scense);
    void draw(std::shared_ptr<FrameBuffer> fb);

private:
    std::shared_ptr<Scenes> m_scenes;
};

}
}

#endif



