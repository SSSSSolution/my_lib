#include "model.h"


namespace reality
{
    namespace snorlax
    {
    Model::Model()
    {
        m_type = T_Line;

        auto v1 = Vec3(0.5f, 0.5f, 0.0f);
        auto v2 = Vec3(-0.5f, -0.5f, 0.0f);

        m_vec_list.push_back(v1);
        m_vec_list.push_back(v2);

        m_world_pos = Vec3(0.0f, 0.0f, 0.0f);
    }

    Model::ModelType Model::type()
    {
        return m_type;
    }

    std::vector<Vec3> &Model::get_vec_list()
    {
        return m_vec_list;
    }

    }
}
