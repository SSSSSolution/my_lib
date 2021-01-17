#include "renderer.h"
#include "model.h"
#include "frame.h"
#include <assert.h>
namespace reality
{
    namespace snorlax
    {
        Renderer::Renderer()
        {

        }

        void Renderer::add_model(std::shared_ptr<Model> model)
        {
            m_model_list.push_back(model);
        }

        Frame Renderer::draw()
        {

        }

        void Renderer::draw_line(unsigned char *data, int width, int height, Vec3 start, Vec3 end)
        {
            assert(0 <= start.x && start.x < width);
            assert(0 <= end.x && end.x < width);
            assert(0 <= start.y && start.y < height);
            assert(0 <= end.y && end.y < height);


        }
    }
}

