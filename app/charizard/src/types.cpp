#include "types.h"
#include <assert.h>

namespace reality
{
    namespace charizard
    {
    using namespace r_math;

    // primitive
    Primitive::Primitive(std::vector<Vec4f> &vecs)
        : m_vecs(vecs)
    {}

//    void Primitive::transform(Mat4f mat4)
//    {
//        for (auto vec4 : m_vecs)
//        {
//            auto t_vec4 = mat4 * vec4;
//            m_project_vecs.push_back(Vec2f(t_vec4.x, t_vec4.y));
//        }
//    }

    // triangle primitive
    TrianglePrimitvie::TrianglePrimitvie(std::vector<Vec4f> &vecs)
        : Primitive(vecs)
    {
        assert(m_vecs.size() == 3);
    }
    }
}
