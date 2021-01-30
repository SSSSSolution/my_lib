#include "camera.h"

using namespace reality::r_math;

namespace reality
{
    namespace charizard
    {
        Camera::Camera(std::string id, float fov, float aspect, float near, float far)
            : m_id(id), m_world_pos(0.0f, 0.0f, 0.0f), fov(fov), aspect(aspect),
              near(near), far(far),
              m_right(1.0f, 0.0f, 0.0f),
              m_direct(0.0f, 0.0f, -1.0f),
              m_up(0.0f, 1.0f, 0.0f)
        {
            m_projection = Mat4f::projection(fov, aspect, near, far);
            calculate_lookat();
        }

        std::string &Camera::id()
        {
            return m_id;
        }

        Mat4f Camera::transformation()
        {
            return m_projection * m_lookat;
        }

        void Camera::move_to(r_math::Vec3f world_pos)
        {
            m_world_pos = world_pos;
            calculate_lookat();
        }

        void Camera::calculate_lookat()
        {
            m_lookat = Mat4f(Vec4f(m_right.x, m_up.x, -m_direct.x, 0.0f),
                             Vec4f(m_right.y, m_up.y, -m_direct.y, 0.0f),
                             Vec4f(m_right.z, m_up.z, -m_direct.z, 0.0f),
                             Vec4f(0.0f, 0.0f, 0.0f, 1.0f)) *
                       Mat4f(Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
                             Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
                             Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
                             Vec4f(-1.0f * m_world_pos.x, -1.0f * m_world_pos.y, -1.0f * m_world_pos.z, 1.0f));
        }

    }
}
