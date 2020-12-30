#ifndef REALITY_RENDER_SYSTEM_SHADER_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_SHADER_INITIALIZER_H

#include"vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system
    {
    class ShaderInitializer
    {
    public:
        ShaderInitializer(std::shared_ptr<VulkanContext> vulkan_context);
    private:
        void init_shader();
        std::shared_ptr<VulkanContext> m_vulkan_context;
    };
    }
}
















#endif
