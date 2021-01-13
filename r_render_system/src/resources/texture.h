#ifndef REALITY_RENDER_SYSTEM_TEXTURE_H
#define REALITY_RENDER_SYSTEM_TEXTURE_H

#include <string>

namespace reality
{
    namespace r_render_system
    {
    enum SamplerType
    {
        // problem:
        // 1.oversampling
        // 2.undersamplig
    };

    class Texture
    {
    public:
        Texture(std::string id, std::string image_path);

    private:
        std::string id;
        std::string image_path;
        int m_width;
        int m_height;

    };
    }
}


#endif
