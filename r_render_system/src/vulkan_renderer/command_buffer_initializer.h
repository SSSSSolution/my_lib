#ifndef REALITY_RENDER_SYSTEM_COMMAND_BUFFER_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_COMMAND_BUFFER_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system {
    class CommandBufferInitializer
    {
    public:
        CommandBufferInitializer(std::shared_ptr<VulkanContext> vulkan_context);
        ~CommandBufferInitializer();
    private:
        std::shared_ptr<VulkanContext> m_vulkan_context;
    };
    }
}
#endif
