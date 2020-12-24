#include "depth_buffer_initializer.h"
#include "vulkan_helper.h"
#include <iostream>

namespace reality
{
namespace r_render_system {
    DepthBufferInitializer::DepthBufferInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;
        init_depth_buffer();
        std::cout << "depth buffer init!" << std::endl;
    }

    void DepthBufferInitializer::init_depth_buffer()
    {
        VkImageCreateInfo image_info = {};
        VkFormatProperties format_prop;

        if (m_vulkan_context->m_depth.format == VK_FORMAT_UNDEFINED)
        {
            m_vulkan_context->m_depth.format = VK_FORMAT_D16_UNORM;
        }

        const VkFormat depth_format = m_vulkan_context->m_depth.format;
        vkGetPhysicalDeviceFormatProperties(m_vulkan_context->m_gpu_list[0],
                depth_format, &format_prop);

        if (format_prop.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
        {
            image_info.tiling = VK_IMAGE_TILING_LINEAR;
        } else if (format_prop.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
        {
            image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
        } else
        {
            std::cout << "depth_format " << depth_format << "Unsupported.\n";
            exit(-1);
        }

        image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_info.pNext = nullptr;
        image_info.imageType =VK_IMAGE_TYPE_2D;
        image_info.format = depth_format;
        image_info.extent.width = m_vulkan_context->m_window->width();
        image_info.extent.height = m_vulkan_context->m_window->height();
        image_info.extent.depth = 1;
        image_info.mipLevels = 1;
        image_info.arrayLayers = 1;
        image_info.samples = VK_SAMPLE_COUNT_1_BIT;
        image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        image_info.queueFamilyIndexCount = 0;
        image_info.pQueueFamilyIndices = nullptr;
        image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        image_info.flags = 0;

        VkMemoryAllocateInfo mem_alloc = {};
        mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mem_alloc.pNext = nullptr;
        mem_alloc.allocationSize = 0;
        mem_alloc.memoryTypeIndex = 0;

        VkImageViewCreateInfo view_info = {};
        view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        view_info.pNext = nullptr;
        view_info.image = VK_NULL_HANDLE;
        view_info.format = depth_format;
        view_info.components.r = VK_COMPONENT_SWIZZLE_R;
        view_info.components.g = VK_COMPONENT_SWIZZLE_G;
        view_info.components.b = VK_COMPONENT_SWIZZLE_B;
        view_info.components.a = VK_COMPONENT_SWIZZLE_A;
        view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        view_info.subresourceRange.baseMipLevel = 0;
        view_info.subresourceRange.levelCount = 1;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount = 1;
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.flags = 0;

        if (depth_format == VK_FORMAT_D16_UNORM_S8_UINT ||
                depth_format == VK_FORMAT_D24_UNORM_S8_UINT ||
                depth_format == VK_FORMAT_D32_SFLOAT_S8_UINT)
        {
            view_info.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
        }

        VkMemoryRequirements mem_reqs;

        /* Create image */
        auto res = vkCreateImage(m_vulkan_context->m_device, &image_info, nullptr,
                                 &m_vulkan_context->m_depth.image);
        assert(res == VK_SUCCESS);

        vkGetImageMemoryRequirements(m_vulkan_context->m_device,
                                     m_vulkan_context->m_depth.image,
                                     &mem_reqs);
        mem_alloc.allocationSize = mem_reqs.size;

        bool pass = VulkanHelper::memory_type_from_properties(
                    m_vulkan_context, mem_reqs.memoryTypeBits,
                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                    &mem_alloc.memoryTypeIndex);
        assert(pass);

        /* Allocate memory */
        res = vkAllocateMemory(m_vulkan_context->m_device,
                               &mem_alloc, nullptr, &m_vulkan_context->m_depth.mem);
        assert(res == VK_SUCCESS);

        /* Bind memory */
        res = vkBindImageMemory(m_vulkan_context->m_device, m_vulkan_context->m_depth.image, m_vulkan_context->m_depth.mem, 0);
        assert(res == VK_SUCCESS);

        /* Create image view */
        view_info.image = m_vulkan_context->m_depth.image;
        res = vkCreateImageView(m_vulkan_context->m_device, &view_info, nullptr,
                                &m_vulkan_context->m_depth.view);
        assert(res == VK_SUCCESS);
    }
}
}


























