#ifndef REALITY_CHARIZARD_MODEL_H
#define REALITY_CHARIZARD_MODEL_H

#include "r_math/vec3.h"
#include "r_math/vec4.h"
#include "r_math/mat4.h"

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
        r_math::Mat4f &transformation();
        void move_to(float x, float y, float z);
        void rotate(float angle, r_math::Vec3f axis);

        std::vector<r_math::Vec4f> &vecs_list();
        std::vector<int> &index_list();


    protected:
        std::string m_id;
        r_math::Mat4f m_transformation;
        r_math::Vec3f m_world_position;
        float m_angle;
        r_math::Vec3f m_axis;

        std::vector<r_math::Vec4f> m_vec_list;
        std::vector<int> m_index_list;

    private:
        void calculate_transformation();
    };

    class UnitCubeModel : public Model
    {
    public:
        UnitCubeModel(std::string id);
    };
    }
}

#endif
