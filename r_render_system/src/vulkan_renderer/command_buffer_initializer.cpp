#include "command_buffer_initializer.h"

namespace reality
{
namespace r_render_system {

CommandBufferInitializer::CommandBufferInitializer(std::shared_ptr<VulkanContext> vulkan_context)
{
    m_vulkan_context = vulkan_context;

    VkCommandBufferAllocateInfo cmd_alloc_info = {};
    cmd_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_alloc_info.pNext = nullptr;
    cmd_alloc_info.commandPool = m_vulkan_context->m_cmd_pool;
    cmd_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_alloc_info.commandBufferCount = 2;

    m_vulkan_context->m_cmd_bufs.resize(2);
    auto res = vkAllocateCommandBuffers(m_vulkan_context->m_device, &cmd_alloc_info, m_vulkan_context->m_cmd_bufs.data());
    assert(res == VK_SUCCESS);
    printf("cmd buf created!\n");
}

CommandBufferInitializer::~CommandBufferInitializer()
{

}
}
}
