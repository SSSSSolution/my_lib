#include "renderer.h"
#include "model.h"

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

        void Renderer::draw()
        {

        }
    }
}

