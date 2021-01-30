#ifndef REALITY_CHARIZARD_EXECTOR_H
#define REALITY_CHARIZARD_EXECTOR_H

#include <vector>
#include <atomic>
#include <functional>
#include <thread>

namespace reality
{
    namespace charizard
    {
        class Exector
        {
        public:
            Exector();

            void set_exec_callback(std::function<void(void)> cb);

            void exec();
            void stop();

        private:
            std::atomic<bool> m_is_loop;
            std::shared_ptr<std::thread> m_loop_thread;
            std::function<void(void)> m_exec_callback = nullptr;

        };
    }
}

#endif
