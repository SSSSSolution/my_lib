#include "soft_renderer.h"
#include "model.h"
#include "rlog.h"

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
void draw_line_DDA(std::shared_ptr<FrameBuffer> image, r_math::Vec2f start, r_math::Vec2f end, char32_t color)
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

void draw_line_Bresenham(std::shared_ptr<FrameBuffer>image, r_math::Vec2f start, r_math::Vec2f end, char32_t color)
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

static std::vector<Recti> get_4_sub_rects(const  Recti &rect, int min_size)
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

static void draw_triangle_help(std::shared_ptr<FrameBuffer> image, const Recti &sub_rect, r_math::Vec2f &p1, r_math::Vec2f &p2, r_math::Vec2f &p3, SampleCount sample, char32_t color)
{
    std::vector<Recti> sub_rects = get_4_sub_rects(sub_rect, MIN_SUB_RECT_SIZE);
    if (sub_rects.size()  == 4)
    {
        for (auto rect : sub_rects)
        {
            if (is_intersect(rect, p1, p2, p3))
            {
                // test
//                int start_x = rect.x;
//                int end_x = rect.x + rect.width -1;
//                int start_y = rect.y;
//                int end_y = rect.y + rect.height -1;
//                for (int i = start_y; i < end_y; i++)
//                {
//                    for (int j = start_x; j < end_x; j++)
//                    {
//                        if (i == start_y || i == end_y -1 || j == start_x || j== end_x -1)
//                        {
//                            image->data[i * image->width + j] = 0xff00ff00;
//                        }
//                    }
//                }
                // continue sub rect
                draw_triangle_help(image, rect, p1, p2, p3, sample, color);
            }
        }
    }
    else {
        assert(sub_rects.size() == 0);
        // rasterization triangle in this sub_rect
            int start_x = sub_rect.x;
            int end_x = sub_rect.x+sub_rect.width;
            if (start_x < 0) start_x = 0;
            if (end_x > image->width - 1) end_x  = image->width -1;

            int start_y = sub_rect.y;
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

void draw_triangle(std::shared_ptr<FrameBuffer> image, const Recti &sub_rect, r_math::Vec2f &p1, r_math::Vec2f &p2, r_math::Vec2f &p3, SampleCount sample, char32_t color)
{
//    Vec2f A(p1.x * image->width , p1.y * image->height);
//    Vec2f B(p2.x * image->width, p2.y * image->height);
//    Vec2f C(p3.x * image->width, p3.y * image->height);
    draw_triangle_help(image, sub_rect, p1, p2, p3, sample, color);
}

// primitive
Primitive::Primitive(std::vector<Vec4f> &vecs)
    : m_vecs(vecs)
{}

void Primitive::transform(Mat4f mat4)
{
    for (auto vec4 : m_vecs)
    {
        auto t_vec4 = mat4 * vec4;
        m_project_vecs.push_back(Vec2f(t_vec4.x, t_vec4.y));
    }
}

// triangle primitive
TrianglePrimitvie::TrianglePrimitvie(std::vector<Vec4f> &vecs)
    : Primitive(vecs)
{
    assert(m_vecs.size() == 3);
}

// soft renderer
SoftRenderer::SoftRenderer()
{

}

void SoftRenderer::set_scenes(std::shared_ptr<Scenes> scense)
{
    m_scenes = scense;
}

void SoftRenderer::draw(std::shared_ptr<FrameBuffer> fb)
{
    if (m_scenes == nullptr)
    {
        RLOG(ERROR, "SoftRenderer draw failed: not specific scenes to draw");
        return;
    }

    // todo draw scenes
    // get camera transform
    Mat4f camera_transform = m_scenes->m_cur_camera->transformation();
    // draw models
    std::vector<Primitive> primitives;
    for (const auto &model : m_scenes->m_model_list)
    {
        std::vector<Vec4f> model_vecs = model->vecs_list();
        std::vector<int> model_indexs = model->index_list();
        for (unsigned int i = 0; i < model->index_list().size(); i += 3)
//        for (unsigned int i = 0; i < 3; i += 3)
        {
            std::vector<Vec4f> vecs;
            vecs.push_back(camera_transform * model_vecs.at(model_indexs.at(i) - 1));
            vecs.push_back(camera_transform * model_vecs.at(model_indexs.at(i+1) - 1));
            vecs.push_back(camera_transform * model_vecs.at(model_indexs.at(i+2) - 1));

//            std::cout << vecs[0].x << ", " << vecs[0].y  << ", "
//                      << vecs[0].z  << ", " << vecs[0].w << std::endl;
//            std::cout << vecs[1].x << ", " << vecs[1].y  << ", "
//                      << vecs[1].z  << ", " << vecs[1].w << std::endl;
//            std::cout << vecs[2].x << ", " << vecs[2].y << ", "
//                      << vecs[2].z << ", " << vecs[2].w << std::endl;

            primitives.push_back(Primitive(vecs));
        }
    }
    // clip
    // 1. NDC
    for (auto &p : primitives)
    {
        for (auto &v : p.m_vecs)
        {
            v.x = v.x / v.w;
            v.y = v.y / v.w;
            v.z = v.z / v.w;
            v.w = v.w / v.w;
        }
        std::cout << p.m_vecs[0].x<< ", " << p.m_vecs[0].y<< ", "
                  << p.m_vecs[0].z << ", " << p.m_vecs[0].w<< std::endl;
        std::cout << p.m_vecs[1].x<< ", " << p.m_vecs[1].y<< ", "
                  << p.m_vecs[1].z<< ", " << p.m_vecs[1].w << std::endl;
        std::cout << p.m_vecs[2].x<< ", " << p.m_vecs[2].y << ", "
                  << p.m_vecs[2].z << ", " << p.m_vecs[2].w<< std::endl;
    }

    // NDC -> screen
    Mat4f ndc2scr = Mat4f::scale(fb->width / 2.0f, fb->height / 2.0f, 1.0f) *
                    Mat4f::translate(1.0f, 1.0f, 0.0f) *
                    Mat4f::reflect_x();
    Recti sub_rect = Recti(0, 0, fb->width, fb->height);

    for (auto &p : primitives)
    {
        for ( auto &v : p.m_vecs)
        {
            v = ndc2scr * v;
        }
        Vec2f A(p.m_vecs[0].x , p.m_vecs[0].y);
        Vec2f B(p.m_vecs[1].x, p.m_vecs[1].y);
        Vec2f C(p.m_vecs[2].x, p.m_vecs[2].y);
        draw_triangle(fb, sub_rect, A, B, C, Sample_Count_1, 0xff00ff00);
//        std::cout << p.m_vecs[0].x<< ", " << p.m_vecs[0].y<< ", "
//                  << p.m_vecs[0].z << ", " << p.m_vecs[0].w<< std::endl;
//        std::cout << p.m_vecs[1].x<< ", " << p.m_vecs[1].y<< ", "
//                  << p.m_vecs[1].z<< ", " << p.m_vecs[1].w << std::endl;
//        std::cout << p.m_vecs[2].x<< ", " << p.m_vecs[2].y << ", "
//                  << p.m_vecs[2].z << ", " << p.m_vecs[2].w<< std::endl;
//        std::cout << p.m_vecs[0].x / p.m_vecs[0].w << ", " << p.m_vecs[0].y / p.m_vecs[0].w << ", "
//                  << p.m_vecs[0].z / p.m_vecs[0].w << ", " << p.m_vecs[0].w / p.m_vecs[0].w << std::endl;
//        std::cout << p.m_vecs[1].x / p.m_vecs[1].w << ", " << p.m_vecs[1].y / p.m_vecs[1].w << ", "
//                  << p.m_vecs[1].z / p.m_vecs[1].w << ", " << p.m_vecs[1].w / p.m_vecs[1].w << std::endl;
//        std::cout << p.m_vecs[2].x / p.m_vecs[2].w << ", " << p.m_vecs[2].y / p.m_vecs[2].w << ", "
//                  << p.m_vecs[2].z / p.m_vecs[2].w << ", " << p.m_vecs[2].w / p.m_vecs[2].w << std::endl;
    }




}

}
}
























