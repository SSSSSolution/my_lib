#include "exector.h"

#include <iostream>
#include <thread>

namespace reality
{
    namespace charizard
    {

    Exector::Exector()
    {
        m_is_loop = false;
    }

    void Exector::set_exec_callback(std::function<void(void)> cb)
    {
        m_exec_callback = cb;
    }

    void Exector::exec()
    {
        if (m_is_loop)
        {
            return;
        }

        m_is_loop = true;
        m_loop_thread = std::make_shared<std::thread>([this]() {
            std::cout << "start exec" << std::endl;
            while(m_is_loop)
            {
                if (m_exec_callback)
                {
                    m_exec_callback();
                }
            }
            std::cout << "end exec" << std::endl;
        });
    }

    void Exector::stop()
    {
        if (!m_is_loop)
        {
            return;
        }

        m_is_loop = false;
        if (m_loop_thread->joinable())
        {
            m_loop_thread->join();
        }
        m_loop_thread.reset();
    }

    }
}
