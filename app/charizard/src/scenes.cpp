#include "scenes.h"

namespace reality
{
    namespace charizard
    {
    Scenes::Scenes()
    {

    }

    void Scenes::add_model(std::shared_ptr<Model> model)
    {
        m_model_list.push_back(model);
    }

    void Scenes::set_cur_camera(std::shared_ptr<Camera> camera)
    {
        m_cur_camera = camera;
    }

    }
}
