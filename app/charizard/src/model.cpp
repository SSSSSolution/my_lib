#include "model.h"

namespace reality
{
    namespace charizard
    {
        using namespace reality::r_math;
        Model::Model()
        {
        }

        std::vector<r_math::Vec3f> &Model::vecs_list()
        {
            return m_vec_list;
        }

        std::vector<int> &Model::index_list()
        {
            return m_index_list;
        }

        UnitCubeModel::UnitCubeModel()
            : Model()
        {
            m_index_list = {1,3,2,3,4,2,
                            1,5,7,7,3,1,
                            2,6,5,5,1,2,
                            6,2,4,4,8,6,
                            4,3,7,7,8,4,
                            5,6,8,8,7,5};
            Vec3f p1(0.5f, 0.5f, 0.5f);
            Vec3f p2(-0.5f, 0.5f, 0.5f);
            Vec3f p3(0.5f, -0.5f, 0.5f);
            Vec3f p4(-0.5f, -0.5f, 0.5f);
            Vec3f p5(0.5f, 0.5f, -0.5f);
            Vec3f p6(-0.5f, 0.5f, -0.5f);
            Vec3f p7(0.5f, -0.5f, -0.5f);
            Vec3f p8(-0.5f, -0.5f, -0.5f);
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
