#include "soft_renderer.h"

namespace reality
{
namespace  charizard{

#define EPSILON 0.00001f
bool compare_float(float a, float b)
{
    float diff = a - b;
    return (diff < EPSILON) && ( -1 * diff < EPSILON);
}

using namespace  reality::r_math;
void draw_line_DDA(PresentImage *image, r_math::Vec2f start, r_math::Vec2f end, char32_t color)
{
    assert(start.x >= 0.0f && start.x <= 1.0f);
    assert(start.y >= 0.0f && start.y <= 1.0f);
    assert(end.x >= 0.0f && end.x <= 1.0f);
    assert(end.y >= 0.0f && end.y <= 1.0f);

    Vec2i start_pix(static_cast<int>(round(start.x * image->width)),
                    static_cast<int>(round(start.y * image->height)));
    Vec2i end_pix(static_cast<int>(round(end.x * image->width)),
                  static_cast<int>(round(end.y * image->height)));
    if (start_pix.x < 0) start_pix.x = 0;
    if (start_pix.x >= image->width) start_pix.x = image->width - 1;
    if (start_pix.y < 0) start_pix.y = 0;
    if (start_pix.y >= image->height) start_pix.y = image->height - 1;
    if (end_pix.x < 0) end_pix.x = 0;
    if (end_pix.x >= image->width) end_pix.x = image->width - 1;
    if (end_pix.y < 0) end_pix.y = 0;
    if (end_pix.y >= image->height) end_pix.y = image->height - 1;

    int x0, x1, y0, y1;
    float k = static_cast<float>(end.y - start.y)/static_cast<float>(end.x - start.x);
    if (std::abs(k) <= 1)
    {
        if (start_pix.x > end_pix.x)
        {
            x0 = end_pix.x;
            y0 = end_pix.y;
            x1 = start_pix.x;
            y1 = start_pix.y;
        } else {
            x0 = start_pix.x;
            y0 = start_pix.y;
            x1 = end_pix.x;
            y1 = end_pix.y;
        }
        float j = y0;
        for (int i = x0; i <= x1; i++)
        {
            image->data[static_cast<int>(round(j)) * image->width + i] = color;
            j += k;
        }
    } else {
        if (start_pix.y > end_pix.y)
        {
            x0 = end_pix.x;
            y0 = end_pix.y;
            x1 = start_pix.x;
            y1 = start_pix.y;
        } else {
            x0 = start_pix.x;
            y0 = start_pix.y;
            x1 = end_pix.x;
            y1 = end_pix.y;
        }
        k = 1.0f / k;
        float j = x0;
        for (int i = y0; i <= y1; i++)
        {
            image->data[i * image->width + (static_cast<int>(j))] = color;
            j += k;
        }
    }
}

void draw_line_Bresenham(PresentImage *image, r_math::Vec2f start, r_math::Vec2f end, char32_t color)
{
    assert(start.x >= 0.0f && start.x <= 1.0f);
    assert(start.y >= 0.0f && start.y <= 1.0f);
    assert(end.x >= 0.0f && end.x <= 1.0f);
    assert(end.y >= 0.0f && end.y <= 1.0f);

    Vec2i start_pix(static_cast<int>(round(start.x * image->width)),
                    static_cast<int>(round(start.y * image->height)));
    Vec2i end_pix(static_cast<int>(round(end.x * image->width)),
                  static_cast<int>(round(end.y * image->height)));
    if (start_pix.x < 0) start_pix.x = 0;
    if (start_pix.x >= image->width) start_pix.x = image->width - 1;
    if (start_pix.y < 0) start_pix.y = 0;
    if (start_pix.y >= image->height) start_pix.y = image->height - 1;
    if (end_pix.x < 0) end_pix.x = 0;
    if (end_pix.x >= image->width) end_pix.x = image->width - 1;
    if (end_pix.y < 0) end_pix.y = 0;
    if (end_pix.y >= image->height) end_pix.y = image->height - 1;

    int x0, x1, y0, y1;
    float k = static_cast<float>(end.y - start.y)/static_cast<float>(end.x - start.x);
    if ((k < 1 && k > 0) || compare_float(k, 1.0f))
    {
        if (start_pix.x > end_pix.x)
        {
            x0 = end_pix.x;
            y0 = end_pix.y;
            x1 = start_pix.x;
            y1 = start_pix.y;
        } else {
            x0 = start_pix.x;
            y0 = start_pix.y;
            x1 = end_pix.x;
            y1 = end_pix.y;
        }
        int dx = x1 - x0;
        int dy = y1 - y0;
        int j = y0;
        int e = -2 * dx;
        for (int i = x0; i < x1; i++)
        {
            image->data[j * image->width + i] = color;
            e += 2 * dy;
            if (e > 0) j++;
            if (e >= dx) e -= 2*dx;
        }
    } else if ((k < 0 && k > -1) || compare_float(k, 0.0f))
    {
        if (start_pix.x > end_pix.x)
        {
            x0 = end_pix.x;
            y0 = end_pix.y;
            x1 = start_pix.x;
            y1 = start_pix.y;
        } else {
            x0 = start_pix.x;
            y0 = start_pix.y;
            x1 = end_pix.x;
            y1 = end_pix.y;
        }
        int dx = x1 - x0;
        int dy = y1 - y0;
        int j = y0;
        int e = -2 * dx;
        for (int i = x0; i < x1; i++)
        {
            image->data[j * image->width + i] = color;
            e -= 2 * dy;
            if (e > 0) j--;
            if (e >= dx) e -= 2*dx;
        }
    }
    else if (k > 1 || compare_float(k, 1.0f))
    {
        if (start_pix.y > end_pix.y)
        {
            x0 = end_pix.x;
            y0 = end_pix.y;
            x1 = start_pix.x;
            y1 = start_pix.y;
        } else {
            x0 = start_pix.x;
            y0 = start_pix.y;
            x1 = end_pix.x;
            y1 = end_pix.y;
        }
        int dx = x1 - x0;
        int dy = y1 - y0;
        int j = x0;
        int e = -2 * dy;
        for (int i = y0; i <= y1; i++)
        {
            image->data[i * image->width + j] = color;
            e += 2 * dx;
            if (e > 0) j++;
            if (e >= dy) e -= 2*dy;
        }
    }
    else if (k < -1 || compare_float(k, -1.0f))
    {
        if (start_pix.y > end_pix.y)
        {
            x0 = end_pix.x;
            y0 = end_pix.y;
            x1 = start_pix.x;
            y1 = start_pix.y;
        } else {
            x0 = start_pix.x;
            y0 = start_pix.y;
            x1 = end_pix.x;
            y1 = end_pix.y;
        }
        int dx = x1 - x0;
        int dy = y1 - y0;
        int j = x0;
        int e = -2 * dy;
        for (int i = y0; i <= y1; i++)
        {
            image->data[i * image->width + j] = color;
            e -= 2 * dx;
            if (e > 0) j--;
            if (e >= dy) e -= 2*dy;
        }
    }
}

void draw_triangle(PresentImage *image, const std::vector<r_math::Vec3f> &vec_list, const std::vector<int> &index_list)
{

}

}
}
























