#include "command_pool_initializer.h"

namespace reality {

    namespace r_render_system {
    CommandPoolInitializer::CommandPoolInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        printf("command pool init...\n");
        init_command_pool();
    }

    CommandPoolInitializer::~CommandPoolInitializer()
    {

    }

    void CommandPoolInitializer::init_command_pool()
    {
        VkCommandPoolCreateInfo cmd_pool_info = {};
        cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmd_pool_info.pNext = nullptr;
        cmd_pool_info.flags = 0;
        cmd_pool_info.queueFamilyIndex = m_ctx->m_graphics_queue_family_index;

        auto res = vkCreateCommandPool(m_ctx->m_device, &cmd_pool_info, nullptr, &m_ctx->m_cmd_pool);
        assert(res == VK_SUCCESS);
    }
    }
}
