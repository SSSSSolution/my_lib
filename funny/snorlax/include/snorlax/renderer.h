#ifndef REALITY_SNORLAX_RENDERER_H
#define REALITY_SNORLAX_RENDERER_H

#include <string>
#include <memory>
#include <vector>
#include "frame.h"

namespace reality
{
    namespace snorlax
    {
        class Model;
        class Renderer
        {
        public:
            Renderer();

            void add_model(std::shared_ptr<Model> model);
            void draw();

        private:
            std::vector<std::shared_ptr<Model>> m_model_list;
        };
    }
}

#endif
