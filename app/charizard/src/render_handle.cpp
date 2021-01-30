#include "render_handle.h"

#include <sys/time.h>
#include <chrono>
#include <thread>
#include <QDebug>

namespace reality
{
    namespace charizard
    {
    using namespace reality::r_math;

    static void move(Vec2f &P, float d)
    {
        float det = 0.00001;
        if (P.x < 0.1f + det && P.y > 0.1 - det  && P.y < 0.9 + det)
        {
            P.x = 0.1f;
            P.y = P.y - d;
        }
         else if (P.x > 0.9f - det && P.y > 0.1 - det  && P.y < 0.9 + det)
        {
            P.x = 0.9;
            P.y = P.y + d;

        }
        else if (P.y < 0.1f + det  && P.x > 0.1 - det  && P.x < 0.9 + det)
        {
            P.y = 0.1f;
            P.x = P.x + d;
        }
        else if (P.y > 0.9f - det && P.x > 0.1 - det && P.x < 0.9 + det)
        {
            P.y = 0.9f;
            P.x = P.x - d;
        }
    }

    RenderHandle::RenderHandle(NativeRenderWidget *native_widget,
                               QObject *parent)
        : QObject(parent)
    {
        m_renderer = std::make_shared<SoftRenderer>();
        m_exector = std::make_unique<Exector>();
        m_scenes = std::make_shared<Scenes>();
        // init scenes
        auto camera = std::make_shared<Camera>("camera", 3.14159f/3.0f, 1.0f, 0.1f, 10.0f);
        m_scenes->set_cur_camera(camera);
        camera->move_to(Vec3f(1.0f, 0.0f, 0.0f));
        auto cube_model = std::make_shared<UnitCubeModel>("cube");
        m_scenes->add_model(cube_model);
        m_renderer->set_scenes(m_scenes);

        m_native_widget = native_widget;
        A = Vec2f(0.1f, 0.1f);
        B = Vec2f(0.9f, 0.1f);
        C = Vec2f(0.9f, 0.9f);

//        m_exector->set_exec_callback([this](){
//            move(A, 0.001);
//            move(B, 0.002);
//            move(C, 0.003);
//            auto fb = m_native_widget->get_next_framebuffer();
//            memset(fb->data, 0xffffffff, sizeof(char32_t) * fb->height * fb->width);

//            Recti rect(0, 0, fb->width, fb->height);
//            std::cout << "data: " << fb->data << ", width: " << fb->width << ", height: " <<fb->height << std::endl;
//            draw_triangle(fb, rect, A, B, C, Sample_Count_4, 0xffff0000);

//            m_native_widget->show_next_framebuffer();

//            struct timeval time;
//            gettimeofday(&time, nullptr);
//            std::cout << time.tv_sec << "s" << time.tv_usec << "us" << std::endl;
//        });

        m_exector->set_exec_callback([this](){
            auto fb = m_native_widget->get_next_framebuffer();
            memset(fb->data, 0xffffffff, sizeof(char32_t) * fb->height * fb->width);
            m_renderer->draw(fb);

            m_native_widget->show_next_framebuffer();

            struct timeval time;
            gettimeofday(&time, nullptr);
            std::cout << time.tv_sec << "s" << time.tv_usec << "us" << std::endl;
        });

    }

    void RenderHandle::draw_line(const QPointF &start, const QPointF &end)
    {
        auto fb = m_native_widget->get_next_framebuffer();
        memset(fb->data, 0xffffffff, sizeof(char32_t) * fb->height * fb->width);

        draw_line_DDA(fb, Vec2f(start.x(), start.y()), Vec2f(end.x(), end.y()), 0xff000000);

        m_native_widget->show_next_framebuffer();
    }

    void RenderHandle::draw_triangle_(const QPointF &A, const QPointF &B, const QPointF &C, SampleCount sample)
    {
        auto fb = m_native_widget->get_next_framebuffer();
        memset(fb->data, 0xffffffff, sizeof(char32_t) * fb->height * fb->width);

        struct timeval t1, t2;
        double timeuse;
        gettimeofday(&t1, nullptr);
        std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();

        Vec2f a(A.x(), A.y());
        Vec2f b(B.x(), B.y());
        Vec2f c(C.x(), C.y());

        Recti rect(0, 0, fb->width, fb->height);
        draw_triangle(fb, rect, a, b, c, sample, 0xffff0000);

        gettimeofday(&t2, nullptr);
        std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::system_clock::now();

        timeuse = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
        std::cout << (end_time - start_time).count() << "ns" << std::endl;
        std::cout <<  "time use: " << timeuse << "s" << std::endl;

        m_native_widget->show_next_framebuffer();
    }

    void RenderHandle::run()
    {
        m_exector->exec();
    }

    void RenderHandle::stop()
    {
        m_exector->stop();
    }

    void RenderHandle::clear()
    {
        auto fb = m_native_widget->get_next_framebuffer();
        memset(fb->data, 0xffffffff, sizeof(char32_t) * fb->height * fb->width);

        m_native_widget->show_next_framebuffer();
    }


    }
}
