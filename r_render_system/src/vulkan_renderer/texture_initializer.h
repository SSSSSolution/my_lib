#ifndef REALITY_RENDER_SYSTEM_TEXTURE_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_TEXTURE_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system
    {
    class TextureInitializer
    {
    public:
        TextureInitializer(std::shared_ptr<VulkanContext> ctx);
        ~TextureInitializer();

        void create_texture_image();
        void create_texture_view();
        void create_texture_sampler();

    private:
        std::shared_ptr<VulkanContext> m_ctx;
        uint32_t m_mip_levels;
    };
    }
}
#endif
