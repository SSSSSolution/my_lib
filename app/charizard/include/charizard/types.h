#ifndef REALITY_CHARIZARD_TYPES_H
#define REALITY_CHARIZARD_TYPES_H

#include <stdlib.h>
#include "rlog.h"

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
    }
}

#endif
