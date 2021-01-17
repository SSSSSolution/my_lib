#ifndef REALITY_SNORLAX_FRAME_H
#define REALITY_SNORLAX_FRAME_H

#include <string>
#include <vector>

namespace reality
{
    namespace snorlax
    {
        class Frame
        {
        public:
            Frame();
            std::vector<std::string> &get_frame_content();
        private:
            std::vector<std::string> m_content;
        };
    }
}

#endif
