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

    RenderHandle::RenderHandle(QObject *parent)
        : QObject(parent)
    {
        m_unit_cube_model = std::make_unique<UnitCubeModel>();
        m_renderer = std::make_shared<SoftRenderer>();
        m_exector = std::make_unique<Exector>(m_renderer);
    }

    void RenderHandle::set_image(std::shared_ptr<PresentImage> image)
    {
        present_image = image;
        m_renderer->set_present_image(present_image);

        emit draw();
    }

    void RenderHandle::draw_line(const QPointF &start, const QPointF &end)
    {
        assert(present_image->data != nullptr);
        // to do
        draw_line_DDA(present_image, Vec2f(start.x(), start.y()), Vec2f(end.x(), end.y()), 0xff000000);
#if 0
        // test draw_line
        struct timeval t1, t2;
        double timeuse;
        gettimeofday(&t1, nullptr);
        std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();
        for (int i = 0; i < 10000; i++)
        {
        draw_line_DDA(&present_image, Vec2f(0.0f, 0.0f), Vec2f(1.0f, 1.0f), 0xffff0000);
        draw_line_DDA(&present_image, Vec2f(0.0f, 1.0f), Vec2f(1.0f, 0.0f), 0xff00ff00);
        draw_line_DDA(&present_image, Vec2f(0.0f, 0.5f), Vec2f(1.0f, 0.5f), 0xff0000ff);
        draw_line_DDA(&present_image, Vec2f(0.5f, 0.0f), Vec2f(0.5f, 1.0f), 0xff000000);
        draw_line_Bresenham(&present_image, Vec2f(0.0f, 0.0f), Vec2f(1.0f, 1.0f), 0xffff0000);
        draw_line_Bresenham(&present_image, Vec2f(0.0f, 1.0f), Vec2f(1.0f, 0.0f), 0xff00ff00);
        draw_line_Bresenham(&present_image, Vec2f(0.0f, 0.5f), Vec2f(1.0f, 0.5f), 0xff0000ff);
        draw_line_Bresenham(&present_image, Vec2f(0.5f, 0.0f), Vec2f(0.5f, 1.0f), 0xff000000);
        }
        gettimeofday(&t2, nullptr);
        std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::system_clock::now();

        timeuse = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
        std::cout << (end_time - start_time).count() << "ns" << std::endl;
        std::cout <<  "time use: " << timeuse << "s" << std::endl;
#endif

        emit draw();
    }

    void RenderHandle::draw_triangle_(const QPointF &A, const QPointF &B, const QPointF &C, SampleCount sample)
    {
        struct timeval t1, t2;
        double timeuse;
        gettimeofday(&t1, nullptr);
        std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();

        Vec2f a(A.x(), A.y());
        Vec2f b(B.x(), B.y());
        Vec2f c(C.x(), C.y());

        Recti rect(0, 0, present_image->width, present_image->height);
        draw_triangle(present_image, rect, a, b, c, sample, 0xffff0000);

        gettimeofday(&t2, nullptr);
        std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::system_clock::now();

        timeuse = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
        std::cout << (end_time - start_time).count() << "ns" << std::endl;
        std::cout <<  "time use: " << timeuse << "s" << std::endl;

        emit draw();
    }

    void RenderHandle::draw_unit_cube()
    {
        std::vector<int> index_list = m_unit_cube_model->index_list();
        std::vector<Vec3f> vec_list = m_unit_cube_model->vecs_list();
        for (int i = 0; i < index_list.size(); i+=3)
        {
//            draw_line_DDA(&present_image, vec_list[i+0], vec_list[i+1], 0xff000000);
        }
        std::cout << std::endl;
        qDebug() << "draw unit cube";
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
        memset(present_image->data, 0xffffffff, present_image->width * present_image->height * sizeof(char32_t));

        emit draw();
    }



    }
}
