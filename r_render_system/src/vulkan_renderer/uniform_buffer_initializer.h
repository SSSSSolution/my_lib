#ifndef REALITY_RENDER_UNIFORM_BUFFER_INITIALIZER_H
#define REALITY_RENDER_UNIFORM_BUFFER_INITIALIZER_H

#include <memory>
#include "vulkan_context.h"

namespace reality
{
namespace r_render_system
{
    class UniformBufferInitializer
    {
    public:
        UniformBufferInitializer(std::shared_ptr<VulkanContext> vulkan_context);
        void init_uniform_buffer();

    private:
        std::shared_ptr<VulkanContext> m_vulkan_context;
    };
}
}
#endif
