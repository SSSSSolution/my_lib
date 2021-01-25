#ifndef REALITY_CHARIZARD_EXECTOR_H
#define REALITY_CHARIZARD_EXECTOR_H

#include "soft_renderer.h"
#include "model.h"
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
            void exec();
            void stop();

        private:
            std::shared_ptr<SoftRenderer> m_renderer;
            std::vector<std::shared_ptr<Model>> m_model_list;

            std::atomic<bool> m_is_loop;
            std::shared_ptr<std::thread> m_loop_thread;
            std::function<void(const PresentImage &)> m_draw_callback;

        };
    }
}








#endif
