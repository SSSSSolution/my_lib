#ifndef REALITY_CHARIZARD_CAMERA_H
#define REALITY_CHARIZARD_CAMERA_H

#include "r_math/vec3.h"
#include "r_math/mat4.h"

namespace reality
{
    namespace charizard
    {
        class Camera
        {
        public:
            Camera(float fov, float aspect, float near, float far);

            const r_math::Mat4f &projection();
            void move_to(r_math::Vec3f world_pos);

        private:
            r_math::Vec3f m_world_pos;
            r_math::Mat4f m_projection;

            float fov;
            float aspect;
            float near;
            float far;

            r_math::Vec3f m_look_at;
            r_math::Vec3f m_up;
        };
    }
}

#endif
