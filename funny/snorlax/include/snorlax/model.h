#ifndef REALITY_SNORLAX_MODEL_H
#define REALITY_SNORLAX_MODEL_H

#include <string>
#include <vector>

#include "math.h"

namespace reality
{
    namespace snorlax
    {
        class Model
        {
        public:
            Model();

            enum ModelType
            {
                T_Line,
                T_Triangle,
            };
            ModelType type();

            std::vector<Vec3> &get_vec_list();

        private:
            std::string m_mode_path;

            ModelType m_type;
            std::vector<Vec3> m_vec_list;

            Vec3 m_world_pos;
        };
    }
}

#endif
