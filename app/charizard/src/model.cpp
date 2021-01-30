#include "model.h"

namespace reality
{
    namespace charizard
    {
        using namespace reality::r_math;
        Model::Model(std::string id)
            : m_id(id)
        {
        }

        std::string &Model::id()
        {
            return m_id;
        }

        std::vector<r_math::Vec4f> &Model::vecs_list()
        {
            return m_vec_list;
        }

        std::vector<int> &Model::index_list()
        {
            return m_index_list;
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
