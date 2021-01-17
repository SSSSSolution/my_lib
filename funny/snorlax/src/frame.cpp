#include "frame.h"

namespace reality
{
    namespace snorlax
    {
    Frame::Frame()
    {
        std::string str = std::string("abcderghijabcderghijabcderghijabcderghijabcderghijabcderghijabcderghijabcderghij  ");
        for (int i = 0; i < 40; i++)
        {
            m_content.push_back(str);
        }
    }

    std::vector<std::string> &Frame::get_frame_content()
    {
        return m_content;
    }
    }
}
