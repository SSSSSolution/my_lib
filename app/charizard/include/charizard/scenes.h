#ifndef REALITY_CHARIZARD_SCENES_H
#define REALITY_CHARIZARD_SCENES_H

#include "model.h"
#include "camera.h"

#include <memory>
#include <vector>

namespace reality
{
    namespace charizard
    {
        class SoftRenderer;
        class Scenes
        {
        public:
            Scenes();

            void add_model(std::shared_ptr<Model> model);
            void set_cur_camera(std::shared_ptr<Camera> camera);

        private:
            std::vector<std::shared_ptr<Model>> m_model_list;
            std::vector<std::shared_ptr<Camera>> m_camera_list;
            std::shared_ptr<Camera> m_cur_camera;
        friend class SoftRenderer;
        };
    }
}

#endif
