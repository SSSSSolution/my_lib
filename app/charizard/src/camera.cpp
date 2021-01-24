#include "camera.h"

using namespace reality::r_math;

namespace reality
{
    namespace charizard
    {
        Camera::Camera(float fov, float aspect, float near, float far)
            : m_world_pos(0.0f, 0.0f, 0.0f), fov(fov), aspect(aspect),
              near(near), far(far), m_look_at(0.0f, 0.0f, -1.0f),
              m_up(1.0f, 0.0f, 0.0f)
        {
            m_projection = Mat4f::projection(fov, aspect, near, far);
        }

        const Mat4f& Camera::projection()
        {
            return m_projection;
        }

        void Camera::move_to(r_math::Vec3f world_pos)
        {
            m_world_pos = world_pos;
        }

    }
}
