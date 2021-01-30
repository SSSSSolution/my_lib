#ifndef REALITY_CHARIZARD_MODEL_H
#define REALITY_CHARIZARD_MODEL_H

#include "r_math/vec4.h"

#include <vector>
#include <string>

namespace reality
{
    namespace charizard
    {
    class Model
    {
    public:
        Model(std::string id);

        std::string &id();

        std::vector<r_math::Vec4f> &vecs_list();
        std::vector<int> &index_list();
    protected:
        std::string m_id;

        std::vector<r_math::Vec4f> m_vec_list;
        std::vector<int> m_index_list;
    };

    class UnitCubeModel : public Model
    {
    public:
        UnitCubeModel(std::string id);
    };
    }
}

#endif
