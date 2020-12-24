#include "vulkan_helper.h"

namespace reality
{
namespace r_render_system
{
    void VulkanHelper::execute_begin_command_buffer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        VkCommandBufferBeginInfo cmd_begin_info = {};
        cmd_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cmd_begin_info.pNext = nullptr;
        cmd_begin_info.flags = 0;
        cmd_begin_info.pInheritanceInfo = nullptr;

        auto res = vkBeginCommandBuffer(vulkan_context->m_cmd_buf, &cmd_begin_info);
        assert(res == VK_SUCCESS);
    }

    void VulkanHelper::init_device_queue(std::shared_ptr<VulkanContext> vulkan_context)
    {
        vkGetDeviceQueue(vulkan_context->m_device, vulkan_context->m_graphics_queue_family_index, 0, &vulkan_context->m_graphics_queue);
        if (vulkan_context->m_graphics_queue_family_index == vulkan_context->m_present_queue_family_index)
        {
            vulkan_context->m_present_queue = vulkan_context->m_graphics_queue;
        } else
        {
            vkGetDeviceQueue(vulkan_context->m_device, vulkan_context->m_present_queue_family_index, 0, &vulkan_context->m_present_queue);
        }
    }

    bool VulkanHelper::memory_type_from_properties(std::shared_ptr<VulkanContext> vulkan_context,
                                            uint32_t typeBits, VkFlags requirements_mask,
                                            uint32_t *typeIndex)
    {
        for (uint32_t i = 0; i < vulkan_context->m_gpu_memory_properties.memoryTypeCount; i++)
        {
            if ((typeBits & 1) == 1) {
                if ((vulkan_context->m_gpu_memory_properties.memoryTypes[i].propertyFlags &
                     requirements_mask) == requirements_mask)
                {
                    *typeIndex = i;
                    return true;
                }
            }
            typeBits >>= 1;
        }

        return false;
    }
}
}
