#include "exector.h"

#include <thread>

namespace reality
{
    namespace charizard
    {
    Exector::Exector(std::shared_ptr<SoftRenderer> renderer)
        : m_renderer(renderer)
    {}

    void Exector::exec()
    {
        m_is_loop = true;

        m_loop_thread = std::make_shared<std::thread>([this]() {
            std::cout << "start exec" << std::endl;
            while(m_is_loop)
            {
                m_renderer->draw();
                if (m_draw_callback)
                {
                    m_draw_callback(m_renderer->present_image());
                }
            }
            std::cout << "end exec" << std::endl;
        });
    }

    void Exector::stop()
    {
        m_is_loop = false;
        if (m_loop_thread->joinable())
        {
            m_loop_thread->join();
        }
        m_loop_thread.reset();
    }
    }
}
