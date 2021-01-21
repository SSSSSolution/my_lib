#ifndef REALITY_CHARIZARD_EXECTOR_H
#define REALITY_CHARIZARD_EXECTOR_H

#include "soft_renderer.h"
#include "model.h"

namespace reality
{
    namespace charizard
    {
        class Exector
        {
        public:
            Exector() {}
        private:
            std::shared_ptr<SoftRenderer> m_renderer;

        };
    }
}








#endif
