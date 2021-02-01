#ifndef REALITY_CHARIZARD_TYPES_H
#define REALITY_CHARIZARD_TYPES_H

#include <stdlib.h>
#include "rlog.h"
#include <vector>
#include "r_math/vec2.h"
#include "r_math/vec4.h"
#include "r_math/mat4.h"

namespace reality
{
    namespace charizard
    {
        struct FrameBuffer
        {
            char32_t *data;
            unsigned int width;
            unsigned int height;

            FrameBuffer(unsigned int width , unsigned int height)
                : width(width), height(height)
            {
                data = static_cast<char32_t *>(malloc(sizeof(char32_t) * width * height));
            }

            ~FrameBuffer()
            {
                free(data);
                RLOG(INFO, "frame buffer destroyed");
            }
        };

        struct Primitive
        {
            Primitive(std::vector<r_math::Vec4f> &vecs);

//            void transform(r_math::Mat4f mat4);

            std::vector<r_math::Vec4f> m_vecs;
//            std::vector<r_math::Vec2f> m_project_vecs;
        };

        struct TrianglePrimitvie : public Primitive
        {
            TrianglePrimitvie(std::vector<r_math::Vec4f> &vecs);

        };
    }
}

#endif
