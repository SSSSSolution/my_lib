#include "soft_renderer.h"
#include "model.h"

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

static std::vector<Recti> get_4_sub_rects(const Recti &rect, int min_size)
{
    std::vector<Recti> sub_rects;
    if (rect.width < min_size * 2 || rect.height < min_size *2)
    {
        return sub_rects;
    }

    int sub_width = rect.width / 2 + 1;
    int sub_height = rect.height / 2 + 1;
    Recti top_left_sub(rect.x, rect.y, sub_width, sub_height);
    Recti top_right_sub(rect.x + sub_width, rect.y, sub_width, sub_height);
    Recti bottom_left_sub(rect.x, rect.y + sub_height, sub_width, sub_height);
    Recti bottom_right_sub(rect.x + sub_width, rect.y + sub_height, sub_width, sub_height);

    sub_rects.push_back(top_left_sub);
    sub_rects.push_back(top_right_sub);
    sub_rects.push_back(bottom_left_sub);
    sub_rects.push_back(bottom_right_sub);

    return sub_rects;
}

static bool is_intersect(const Recti &r1, const Recti &r2)
{
    return !( ((r1.x + r1.width - 1 < r2.x) || (r1.y + r1.height - 1 < r2.y)) ||
              ((r2.x + r2.width - 1 < r1.x) || (r2.y + r2.height - 1 < r1.y)) );
}

static bool is_intersect(const Recti &rect, const r_math::Vec2f &A, const r_math::Vec2f &B, const r_math::Vec2f &C)
{
    int left, right, top, bottom;
    left = static_cast<int>(std::floor(std::min(std::min(A.x, B.x), C.x)));
    right = static_cast<int>(std::ceil(std::max(std::max(A.x, B.x), C.x)));
    top = static_cast<int>(std::floor(std::min(std::min(A.y, B.y), C.y)));
    bottom = static_cast<int>(std::ceil(std::max(std::max(A.y, B.y), C.y)));

    Recti tri_rect(left, top, right - left + 1, bottom - top + 1);
//    std::cout << "is_intersect: " << tri_rect.x << "," << tri_rect.y << "," << tri_rect.width <<", " << tri_rect.height << std::endl
//                                  <<  rect.x << "," << rect.y << "," << rect.width <<", " << rect.height << std::endl;
    return is_intersect(tri_rect, rect);
}

static bool is_point_in_triangle(const Vec2f &p, const Vec2f &A, const Vec2f &B, const Vec2f &C)
{
    Vec2f pa(A.x - p.x, A.y - p.y);
    Vec2f pb(B.x - p.x, B.y - p.y);
    Vec2f pc(C.x - p.x, C.y - p.y);

    auto t1 = pa.cross_product(pb);
    auto t2 = pb.cross_product(pc);
    auto t3 = pc.cross_product(pa);

    return ((t1 > 0 && t2 > 0 && t3 > 0) ||
            (t1 < 0 && t2 < 0 && t3 < 0));
}

static bool is_rect_in_triangle(const Recti &rect, const Vec2f &A, const Vec2f &B, const Vec2f &C)
{
    Vec2f top_left(rect.x, rect.y);
    Vec2f top_right(rect.x + rect.width -1, rect.y);
    Vec2f bottom_left(rect.x, rect.y + rect.height  -1);
    Vec2f bottom_right(rect.x + rect.width - 1, rect.y + rect.height - 1);

    if (is_point_in_triangle(top_left, A, B,C) &&
        is_point_in_triangle(top_right, A, B,C) &&
        is_point_in_triangle(bottom_left, A, B,C) &&
        is_point_in_triangle(bottom_right, A, B,C))
    {
        return true;
    }
    return false;
}

#define MIN_SUB_RECT_SIZE 10

static void draw_triangle_help(PresentImage *image, const Recti &sub_rect, r_math::Vec2f &p1, r_math::Vec2f &p2, r_math::Vec2f &p3, SampleCount sample, char32_t color)
{
    std::vector<Recti> sub_rects = get_4_sub_rects(sub_rect, MIN_SUB_RECT_SIZE);
//    std::cout << "sub_rects.size: " << sub_rects.size() << std::endl;
    if (sub_rects.size()  == 4)
    {
        for (auto rect : sub_rects)
        {
            if (is_intersect(rect, p1, p2, p3))
            {
                // test
                int start_x = rect.x;
                int end_x = rect.x + rect.width -1;
                int start_y = rect.y;
                int end_y = rect.y + rect.height -1;
                for (int i = start_y; i < end_y; i++)
                {
                    for (int j = start_x; j < end_x; j++)
                    {
                        if (i == start_y || i == end_y -1 || j == start_x || j== end_x -1)
                        {
                            image->data[i * image->width + j] = 0xff00ff00;
                        }
                    }
                }
                // continue sub rect
                draw_triangle_help(image, rect, p1, p2, p3, sample, color);
            }
        }
    }
    else {
        assert(sub_rects.size() == 0);
        // rasterization triangle in this sub_rect
            int start_x = sub_rect.x + 1;
            int end_x = sub_rect.x+sub_rect.width;
            if (start_x < 0) start_x = 0;
            if (end_x > image->width - 1) end_x  = image->width -1;

            int start_y = sub_rect.y + 1;
            int end_y = sub_rect.y+sub_rect.height;
            if (start_y < 0) start_y = 0;
            if (end_y > image->height - 1) end_y  = image->height -1;

            if (is_rect_in_triangle(sub_rect, p1, p2, p3))
            {
                for (int i = start_x; i < end_x; i++)
                {
                    for (int j = start_y; j < end_y; j++)
                    {
                        image->data[j * image->width + i] = color;
                    }
                }
            } else {
                for (int i = start_x; i < end_x; i++)
                {
                    for (int j = start_y; j < end_y; j++)
                    {
                        switch (sample)
                        {
                        case Sample_Count_1:
                            if (is_point_in_triangle(Vec2f(i + 0.5f, j + 0.5f), p1, p2, p3))
                            {
                                image->data[j * image->width + i] = color;
                            }
                            break;
                        case Sample_Count_4:
                            for (int k = 0; k < 2; k++)
                            {
                                for (int l = 0; l < 2; l++)
                                {
                                    if (is_point_in_triangle(Vec2f(i + 0.25f + k * 0.5f, j + 0.25f + l * 0.5f), p1, p2, p3))
                                    {
                                        image->data[j * image->width + i]  += 0.25f * color;
                                    }
                                }
                            }
                            break;
                        case Sample_Count_16:
                            for (int k = 0; k < 4; k++)
                            {
                                for (int l = 0; l < 4; l++)
                                {
                                    if (is_point_in_triangle(Vec2f(i + 0.125f + k * 0.25f, j + 0.125f + l * 0.25f), p1, p2, p3))
                                    {
                                        image->data[j * image->width + i]  += 0.0625f * color;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
}
void draw_triangle(PresentImage *image, const Recti &sub_rect, r_math::Vec2f &p1, r_math::Vec2f &p2, r_math::Vec2f &p3, SampleCount sample, char32_t color)
{
    Vec2f A(p1.x * image->width , p1.y * image->height);
    Vec2f B(p2.x * image->width, p2.y * image->height);
    Vec2f C(p3.x * image->width, p3.y * image->height);
    draw_triangle_help(image, sub_rect, A, B, C, sample, color);
}

SoftRenderer::SoftRenderer()
{
    auto cube_model = std::make_shared<Model>();
    m_model_list.push_back(cube_model);
}

}
}
























