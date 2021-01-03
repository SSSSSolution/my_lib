#include "vulkan_helper.h"

namespace reality
{
namespace r_render_system
{
    void VulkanHelper::execute_begin_command_buffer(std::shared_ptr<VulkanContext> vulkan_context, int cmd_buf_index)
    {
        VkCommandBufferBeginInfo cmd_begin_info = {};
        cmd_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cmd_begin_info.pNext = nullptr;
        cmd_begin_info.flags = 0;
        cmd_begin_info.pInheritanceInfo = nullptr;

        auto res = vkBeginCommandBuffer(vulkan_context->m_cmd_bufs[cmd_buf_index], &cmd_begin_info);
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
        for (uint32_t i = 0; i < vulkan_context->m_gpu_memory_properties_list[0].memoryTypeCount; i++)
        {
            if ((typeBits & 1) == 1) {
                if ((vulkan_context->m_gpu_memory_properties_list[0].memoryTypes[i].propertyFlags &
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

    void VulkanHelper::print_support_instance_extension(std::shared_ptr<VulkanContext> ctx)
    {
        for (uint32_t i = 0; i < ctx->m_support_instance_extensions.size(); i++)
        {
            auto props = ctx->m_support_instance_extensions[i];
            uint32_t version_major = VK_VERSION_MAJOR(props.specVersion);
            uint32_t version_minor = VK_VERSION_MINOR(props.specVersion);
            uint32_t version_patch = VK_VERSION_PATCH(props.specVersion);
            printf("instance extension props:[%s]<%u.%u.%u>\n", props.extensionName,
                   version_major, version_minor, version_patch);
        }

    }

    void VulkanHelper::print_support_device_extension(std::shared_ptr<VulkanContext> ctx)
    {
        for (uint32_t i = 0; i < ctx->m_support_device_extensions.size(); i++)
        {
            auto props = ctx->m_support_device_extensions[i];
            uint32_t version_major = VK_VERSION_MAJOR(props.specVersion);
            uint32_t version_minor = VK_VERSION_MINOR(props.specVersion);
            uint32_t version_patch = VK_VERSION_PATCH(props.specVersion);
            printf("device extension props:[%s]<%u.%u.%u>\n", props.extensionName,
                   version_major, version_minor, version_patch);
        }
    }
    void VulkanHelper::print_physical_devices(std::shared_ptr<VulkanContext> ctx)
    {
        printf("gpu:\n");
        for (uint32_t i = 0; i < ctx->m_gpu_properties_list.size(); i++)
        {
            printf("    gpu: %s\n", ctx->m_gpu_properties_list[i].deviceName);
        }
    }


    /*VK_QUEUE_GRAPHICS_BIT = 0x00000001,
    VK_QUEUE_COMPUTE_BIT = 0x00000002,
    VK_QUEUE_TRANSFER_BIT = 0x00000004,
    VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
    VK_QUEUE_PROTECTED_BIT = 0x00000010,
    */
    void VulkanHelper::print_queue_families(VkQueueFamilyProperties props)
    {
        printf("queue families:\n");
        if (props.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            printf("    graphics queue\n");
        }
        if (props.queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            printf("    compute queue\n");
        }
        if (props.queueFlags & VK_QUEUE_TRANSFER_BIT)
        {
            printf("    transfer queue\n");
        }
        if (props.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
        {
            printf("    sparse binding queue\n");
        }
        if (props.queueFlags & VK_QUEUE_PROTECTED_BIT)
        {
            printf("    protected queue\n");
        }
    }

    void VulkanHelper::create_buffer(std::shared_ptr<VulkanContext> ctx, VkDeviceSize size,
                                     VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                                     VkBuffer &buffer, VkDeviceMemory &buffer_memory)
    {
        VkBufferCreateInfo buffer_info = {};
        buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_info.size = size;
        buffer_info.usage = usage;
        buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        auto res = vkCreateBuffer(ctx->m_device, &buffer_info, nullptr, &buffer);
        assert(res == VK_SUCCESS);

        VkMemoryRequirements mem_reqs;
        vkGetBufferMemoryRequirements(ctx->m_device, buffer, &mem_reqs);

        VkMemoryAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = mem_reqs.size;
        auto pass = memory_type_from_properties(ctx, mem_reqs.memoryTypeBits,
                                                properties, &alloc_info.memoryTypeIndex);

        res = vkAllocateMemory(ctx->m_device, &alloc_info, nullptr, &buffer_memory);
        assert(res == VK_SUCCESS);

        vkBindBufferMemory(ctx->m_device, buffer, buffer_memory, 0);
    }
}
}



















