#ifndef REALITY_CHARIZARD_MODEL_H
#define REALITY_CHARIZARD_MODEL_H

#include "r_math/vec3.h"

#include <vector>

namespace reality
{
    namespace charizard
    {
    class Model
    {
    public:
        Model();
        std::vector<r_math::Vec3f> &vecs_list();
        std::vector<int> &index_list();
    protected:
        std::vector<r_math::Vec3f> m_vec_list;
        std::vector<int> m_index_list;
    };

    class UnitCubeModel : public Model
    {
    public:
        UnitCubeModel();
    };
    }
}

#endif
