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
        CommandBufferInitializer(std::shared_ptr<VulkanContext> ctx);
        ~CommandBufferInitializer();

        void init_command_buffer();
    private:
        std::shared_ptr<VulkanContext> m_ctx;
    };
    }
}
#endif
