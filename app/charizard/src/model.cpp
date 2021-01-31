#include "model.h"

namespace reality
{
    namespace charizard
    {
        using namespace reality::r_math;
        Model::Model(std::string id)
            : m_id(id),
              m_world_position(0.0f, 0.0f, 0.0f),
              m_angle(0.0f),
              m_axis(0.0f, 0.0f, 1.0f)
        {
            calculate_transformation();
        }

        std::string &Model::id()
        {
            return m_id;
        }

        Mat4f &Model::transformation()
        {
            return m_transformation;
        }

        void Model::move_to(float x, float y, float z)
        {
            m_world_position.x = x;
            m_world_position.y = y;
            m_world_position.z = z;

            calculate_transformation();
        }

        void Model::rotate(float angle, Vec3f axis)
        {
            m_angle = angle;
            m_axis = axis;

            calculate_transformation();
        }

        std::vector<r_math::Vec4f> &Model::vecs_list()
        {
            return m_vec_list;
        }

        std::vector<int> &Model::index_list()
        {
            return m_index_list;
        }

        void Model::calculate_transformation()
        {
            m_transformation = Mat4f::translate(m_world_position.x,
                                                m_world_position.y,
                                                m_world_position.z) *
                               Mat4f::rotate(m_angle, m_axis);
        }

        UnitCubeModel::UnitCubeModel(std::string id)
            : Model(id)
        {
            m_index_list = {1,3,2,3,4,2,
                            1,5,7,7,3,1,
                            2,6,5,5,1,2,
                            6,2,4,4,8,6,
                            4,3,7,7,8,4,
                            5,6,8,8,7,5};
            Vec4f p1(0.5f, 0.5f, 0.5f, 1.0f);
            Vec4f p2(-0.5f, 0.5f, 0.5f, 1.0f);
            Vec4f p3(0.5f, -0.5f, 0.5f, 1.0f);
            Vec4f p4(-0.5f, -0.5f, 0.5f, 1.0f);
            Vec4f p5(0.5f, 0.5f, -0.5f, 1.0f);
            Vec4f p6(-0.5f, 0.5f, -0.5f, 1.0f);
            Vec4f p7(0.5f, -0.5f, -0.5f, 1.0f);
            Vec4f p8(-0.5f, -0.5f, -0.5f, 1.0f);
            m_vec_list.push_back(p1);
            m_vec_list.push_back(p2);
            m_vec_list.push_back(p3);
            m_vec_list.push_back(p4);
            m_vec_list.push_back(p5);
            m_vec_list.push_back(p6);
            m_vec_list.push_back(p7);
            m_vec_list.push_back(p8);
        }
    }
}
