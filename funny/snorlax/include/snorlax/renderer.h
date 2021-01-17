#ifndef REALITY_SNORLAX_RENDERER_H
#define REALITY_SNORLAX_RENDERER_H

#include <string>
#include <memory>
#include <vector>
#include "frame.h"
#include "math.h"
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
            Frame draw();

        private:
            void draw_line(unsigned char *data, int width, int height, Vec3 start, Vec3 end);

        private:
            std::vector<std::shared_ptr<Model>> m_model_list;
        };
    }
}

#endif
