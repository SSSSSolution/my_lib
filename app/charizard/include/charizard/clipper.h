#ifndef REALITY_CHARIZARD_CLIPPER_H
#define REALITY_CHARIZARD_CLIPPER_H

#include "types.h"
#include <vector>

namespace reality
{
    namespace charizard
    {
    class Clipper
    {
    public:
        Clipper();

        static void ndc_clip(std::vector<Primitive> &src, std::vector<Primitive> &dst);
    };
    }
}


#endif
