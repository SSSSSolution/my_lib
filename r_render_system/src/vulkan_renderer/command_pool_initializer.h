#ifndef REALITY_RENDER_SYSTEM_COMMAND_POOL_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_COMMAND_POOL_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality {
    namespace r_render_system
    {
    class CommandPoolInitializer
    {
    public:
        CommandPoolInitializer(std::shared_ptr<VulkanContext> ctx);
        ~CommandPoolInitializer();

        void init_command_pool();

    private:
        std::shared_ptr<VulkanContext> m_ctx;
    };

    }
}

#endif
