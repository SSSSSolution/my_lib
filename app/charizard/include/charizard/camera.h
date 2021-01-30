#ifndef REALITY_CHARIZARD_CAMERA_H
#define REALITY_CHARIZARD_CAMERA_H

#include <string>

#include "r_math/vec3.h"
#include "r_math/mat4.h"

namespace reality
{
    namespace charizard
    {
        class Camera
        {
        public:
            Camera(std::string id, float fov, float aspect, float near, float far);

            std::string &id();
            r_math::Mat4f transformation();
            void move_to(r_math::Vec3f world_pos);

        private:
            void calculate_lookat();

        private:
            std::string m_id;

            r_math::Mat4f m_projection;
            r_math::Mat4f m_lookat;

            r_math::Vec3f m_world_pos;
            float fov;
            float aspect;
            float near;
            float far;

            r_math::Vec3f m_right;
            r_math::Vec3f m_direct;
            r_math::Vec3f m_up;
        };
    }
}

#endif
