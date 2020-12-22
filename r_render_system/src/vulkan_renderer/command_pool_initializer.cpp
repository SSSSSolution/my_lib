#include "command_pool_initializer.h"

namespace reality {

    namespace r_render_system {
    CommandPoolInitializer::CommandPoolInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;

        VkCommandPoolCreateInfo cmd_pool_info = {};
        cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmd_pool_info.pNext = nullptr;
        cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        cmd_pool_info.queueFamilyIndex = m_vulkan_context->m_graphics_queue_family_index;

        auto res = vkCreateCommandPool(m_vulkan_context->m_device, &cmd_pool_info, nullptr, &vulkan_context->m_cmd_pool);
        assert(res == VK_SUCCESS);
    }

    CommandPoolInitializer::~CommandPoolInitializer()
    {

    }
    }
}
