#include "swapchain_initializer.h"
#include <vector>
#define PREFERRED_SURFACE_FORMAT VK_FORMAT_B8G8R8A8_UNORM

namespace reality
{
namespace r_render_system
{
    SwapchainInitializer::SwapchainInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;
        init_swapchain();
        init_swapchain_image();
    }

    void SwapchainInitializer::init_swapchain()
    {
        VkSurfaceCapabilitiesKHR surf_capabilities;

        auto res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
                    m_vulkan_context->m_gpu_list[0],
                    m_vulkan_context->m_surface,
                    &surf_capabilities
                );
        assert(res == VK_SUCCESS);

        uint32_t present_mode_count;
        res = vkGetPhysicalDeviceSurfacePresentModesKHR(
                    m_vulkan_context->m_gpu_list[0],
                    m_vulkan_context->m_surface,
                    &present_mode_count, nullptr);
        assert(res == VK_SUCCESS);

        std::vector<VkPresentModeKHR> present_mode_list;
        present_mode_list.resize(present_mode_count);

        res = vkGetPhysicalDeviceSurfacePresentModesKHR(
                    m_vulkan_context->m_gpu_list[0],
                    m_vulkan_context->m_surface,
                    &present_mode_count, present_mode_list.data());
        assert(res == VK_SUCCESS);

        VkExtent2D swapchain_extent;
        if (surf_capabilities.currentExtent.width == 0xFFFFFFFF) {
            swapchain_extent.width = m_vulkan_context->m_window->width();
            swapchain_extent.height = m_vulkan_context->m_window->height();
            if (swapchain_extent.width < surf_capabilities.minImageExtent.width)
            {
                swapchain_extent.width = surf_capabilities.minImageExtent.width;
            } else if (swapchain_extent.width > surf_capabilities.maxImageExtent.width)
            {
                swapchain_extent.width = surf_capabilities.maxImageExtent.width;
            }

            if (swapchain_extent.height < surf_capabilities.minImageExtent.height)
            {
                swapchain_extent.height = surf_capabilities.minImageExtent.height;
            } else if (swapchain_extent.height > surf_capabilities.maxImageExtent.height)
            {
                swapchain_extent.height = surf_capabilities.maxImageExtent.height;
            }
        } else {
            swapchain_extent = surf_capabilities.currentExtent;
        }

        // The FIFO present mode is guranteed by the spec to be supported
        // Also note that current Android driver only supprots FIFO
        VkPresentModeKHR swapchain_present_mode = VK_PRESENT_MODE_FIFO_KHR;

        // Determine the number of VkImage's to use in the swap chain.
        // We need to acquire only 1 presentable image at time.
        // Asking for minImageCount images ensures that we can acquire
        // 1 presenttable image as long as we present it before attempting
        // to acquire another
        uint32_t desire_number_of_swapchain_images = surf_capabilities.minImageCount;
        printf("desire_number_of_swapchain_images = %d\n", desire_number_of_swapchain_images);
        VkSurfaceTransformFlagBitsKHR pre_transform;
        if (surf_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
        {
            pre_transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        } else {
            pre_transform = surf_capabilities.currentTransform;
        }

        // Find a supported composite alpha mode - one of these is guaranteed to be set
        VkCompositeAlphaFlagBitsKHR composite_alpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        VkCompositeAlphaFlagBitsKHR composite_alpha_flags[4] = {
          VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
          VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
          VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
          VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR
        };

        for (uint32_t i = 0; i < sizeof(composite_alpha_flags[0]); ++i)
        {
            if(surf_capabilities.supportedCompositeAlpha & composite_alpha_flags[i])
            {
                composite_alpha = composite_alpha_flags[i];
                break;
            }
        }

        VkSwapchainCreateInfoKHR swapchain_info = {};
        swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchain_info.pNext = nullptr;
        swapchain_info.surface = m_vulkan_context->m_surface;
        swapchain_info.minImageCount = desire_number_of_swapchain_images;
        swapchain_info.imageFormat = m_vulkan_context->m_format;
        swapchain_info.imageExtent.width = swapchain_extent.width;
        swapchain_info.imageExtent.height = swapchain_extent.height;
        swapchain_info.preTransform = pre_transform;
        swapchain_info.compositeAlpha = composite_alpha;
        swapchain_info.imageArrayLayers = 1;
        swapchain_info.presentMode = swapchain_present_mode;
        swapchain_info.oldSwapchain = VK_NULL_HANDLE;
        swapchain_info.clipped = false;
        swapchain_info.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchain_info.queueFamilyIndexCount = 0;
        swapchain_info.pQueueFamilyIndices = nullptr;

        uint32_t queueFamilyIndices[2] = {
            (uint32_t)m_vulkan_context->m_graphics_queue_family_index,
            (uint32_t)m_vulkan_context->m_present_queue_family_index
        };

        if (m_vulkan_context->m_graphics_queue_family_index != m_vulkan_context->m_present_queue_family_index)
        {
            swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swapchain_info.queueFamilyIndexCount = 2;
            swapchain_info.pQueueFamilyIndices = queueFamilyIndices;
        }


        res = vkCreateSwapchainKHR(m_vulkan_context->m_device, &swapchain_info, nullptr, &m_vulkan_context->m_swapchain);
        assert(res == VK_SUCCESS);


    }

    void SwapchainInitializer::init_swapchain_image()
    {
        uint32_t m_swapchain_image_count;
        auto res = vkGetSwapchainImagesKHR(m_vulkan_context->m_device,
                                      m_vulkan_context->m_swapchain,
                                      &m_swapchain_image_count,
                                      nullptr);
        assert(res == VK_SUCCESS);
        printf("m_swapchain image count: %d\n", m_swapchain_image_count);

        m_vulkan_context->m_swapchain_images.resize(m_swapchain_image_count);
        res = vkGetSwapchainImagesKHR(m_vulkan_context->m_device,
                                      m_vulkan_context->m_swapchain,
                                      &m_swapchain_image_count,
                                      m_vulkan_context->m_swapchain_images.data());
        assert(res == VK_SUCCESS);

        for (uint32_t i = 0; i < m_swapchain_image_count; ++i)
        {
            SwapChainBuffer  sc_buf;

            VkImageViewCreateInfo view_info = {};
            view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            view_info.pNext = nullptr;
            view_info.format = m_vulkan_context->m_format;
            view_info.components.r = VK_COMPONENT_SWIZZLE_R;
            view_info.components.g = VK_COMPONENT_SWIZZLE_G;
            view_info.components.b = VK_COMPONENT_SWIZZLE_B;
            view_info.components.a = VK_COMPONENT_SWIZZLE_A;
            view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            view_info.subresourceRange.baseMipLevel = 0;
            view_info.subresourceRange.levelCount = 1;
            view_info.subresourceRange.baseArrayLayer = 0;
            view_info.subresourceRange.layerCount = 1;
            view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
            view_info.flags = 0;

            sc_buf.image = m_vulkan_context->m_swapchain_images[i];
            view_info.image = sc_buf.image;

            res = vkCreateImageView(m_vulkan_context->m_device,
                                    &view_info, nullptr, &sc_buf.view);
            m_vulkan_context->m_swapchain_buffers.push_back(sc_buf);
            assert(res == VK_SUCCESS);
        }

    }

}
}




















