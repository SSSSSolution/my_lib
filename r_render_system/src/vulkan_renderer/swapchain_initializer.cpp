#include "swapchain_initializer.h"
#include <vector>

namespace reality
{
namespace r_render_system
{
    SwapchainInitializer::SwapchainInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        get_surface_support();
        choose_swapchain_fromat();
        choose_swapchain_present_mode();
        printf("choose swapchain format: %d, colorspace: %d\n", m_ctx->m_swapchain_format.format,
               m_ctx->m_swapchain_format.colorSpace);
        printf("choose swapchain present mode: %d\n", m_ctx->m_swapchain_present_mode);
        choose_swapchain_extent();
        printf("choose swapchain extent w: %d, h: %d\n", m_ctx->m_swapchain_extent.width,
               m_ctx->m_swapchain_extent.height);

        init_swapchain();
        get_swapchain_images();
        create_image_view();
    }

    SwapchainInitializer::~SwapchainInitializer()
    {
        for (int i = 0; i < m_ctx->m_swapchain_views.size(); i++)
        {
            vkDestroyImageView(m_ctx->m_device, m_ctx->m_swapchain_views[i], nullptr);
        }
        vkDestroySwapchainKHR(m_ctx->m_device, m_ctx->m_swapchain, nullptr);
    }

    void SwapchainInitializer::get_surface_support()
    {
        /* surface capabilities */
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_ctx->m_gpu_list[0],
                m_ctx->m_surface, &m_ctx->m_surface_capabilities);

        /* surface formats */
        uint32_t format_count;
        vkGetPhysicalDeviceSurfaceFormatsKHR(m_ctx->m_gpu_list[0],
                m_ctx->m_surface, &format_count, nullptr);
        m_ctx->m_surface_formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(m_ctx->m_gpu_list[0],
                m_ctx->m_surface, &format_count, m_ctx->m_surface_formats.data());

        printf("surface formats: \n");
        for (auto f : m_ctx->m_surface_formats)
        {
            printf("format: %d, colorspace: %d\n", f.format, f.colorSpace);
        }

        /* present modes */
        uint32_t present_mode_count;
        vkGetPhysicalDeviceSurfacePresentModesKHR(m_ctx->m_gpu_list[0], m_ctx->m_surface,
                &present_mode_count, nullptr);
        m_ctx->m_present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(m_ctx->m_gpu_list[0], m_ctx->m_surface,
                &present_mode_count, m_ctx->m_present_modes.data());
        printf("surface present mode: \n");
        for (auto p : m_ctx->m_present_modes)
        {
            printf("present mode: %d\n", p);
        }

        assert(!m_ctx->m_surface_formats.empty() && !m_ctx->m_present_modes.empty());
    }

    void SwapchainInitializer::choose_swapchain_fromat()
    {
        for (auto f : m_ctx->m_surface_formats)
        {
            if (f.format == VK_FORMAT_B8G8R8A8_SRGB &&
                f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                m_ctx->m_swapchain_format = f;
                return;
            }
        }
        m_ctx->m_swapchain_format = m_ctx->m_surface_formats[0];
    }

    void SwapchainInitializer::choose_swapchain_present_mode()
    {
        for (auto pm : m_ctx->m_present_modes)
        {
            if (pm == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                m_ctx->m_swapchain_present_mode = pm;
                return;
            }
        }
        m_ctx->m_swapchain_present_mode = VK_PRESENT_MODE_FIFO_KHR;
    }

    void SwapchainInitializer::choose_swapchain_extent()
    {
        if (m_ctx->m_surface_capabilities.currentExtent.width != UINT32_MAX)
        {
            m_ctx->m_swapchain_extent = m_ctx->m_surface_capabilities.currentExtent;
        } else {
            m_ctx->m_swapchain_extent.width = m_ctx->m_window->width();
            m_ctx->m_swapchain_extent.height = m_ctx->m_window->height();
            m_ctx->m_swapchain_extent.width = std::max(m_ctx->m_surface_capabilities.minImageExtent.width,
                std::min(m_ctx->m_surface_capabilities.maxImageExtent.width, m_ctx->m_swapchain_extent.width));
            m_ctx->m_swapchain_extent.height = std::max(m_ctx->m_surface_capabilities.minImageExtent.height,
                std::min(m_ctx->m_surface_capabilities.maxImageExtent.height, m_ctx->m_swapchain_extent.height));
        }
    }

    void SwapchainInitializer::init_swapchain()
    {
        uint32_t image_count = m_ctx->m_surface_capabilities.minImageCount + 1;
        if (m_ctx->m_surface_capabilities.maxImageCount > 0 &&
            image_count > m_ctx->m_surface_capabilities.maxImageCount)
        {
            image_count = m_ctx->m_surface_capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR swapchain_info = {};
        swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchain_info.surface = m_ctx->m_surface;
        swapchain_info.minImageCount = image_count;
        swapchain_info.imageFormat = m_ctx->m_swapchain_format.format;
        swapchain_info.imageColorSpace = m_ctx->m_swapchain_format.colorSpace;
        swapchain_info.imageExtent = m_ctx->m_swapchain_extent;
        swapchain_info.imageArrayLayers = 1;
        swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        uint32_t queue_family_indeices[] = {m_ctx->m_graphics_queue_family_index,
                                           m_ctx->m_present_queue_family_index};
        if (m_ctx->m_graphics_queue_family_index ==
            m_ctx->m_present_queue_family_index)
        {
            swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            swapchain_info.queueFamilyIndexCount = sizeof(queue_family_indeices);
            swapchain_info.pQueueFamilyIndices = queue_family_indeices;
        } else
        {
            printf("not implementaion...\n");
            exit(-1);
        }
        swapchain_info.preTransform = m_ctx->m_surface_capabilities.currentTransform;
        swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchain_info.presentMode = m_ctx->m_swapchain_present_mode;
        swapchain_info.clipped = VK_TRUE;
        swapchain_info.oldSwapchain = VK_NULL_HANDLE;

        auto res = vkCreateSwapchainKHR(m_ctx->m_device, &swapchain_info, nullptr, &m_ctx->m_swapchain);
        assert(res == VK_SUCCESS);
    }

    void SwapchainInitializer::get_swapchain_images()
    {
        uint32_t image_count;
        vkGetSwapchainImagesKHR(m_ctx->m_device, m_ctx->m_swapchain, &image_count, nullptr);
        m_ctx->m_swapchain_images.resize(image_count);
        vkGetSwapchainImagesKHR(m_ctx->m_device, m_ctx->m_swapchain, &image_count, m_ctx->m_swapchain_images.data());
        printf("swapchain images count: %d\n", image_count);
    }

    void SwapchainInitializer::create_image_view()
    {
        m_ctx->m_swapchain_views.resize(m_ctx->m_swapchain_images.size());
        for ( int i = 0; i < m_ctx->m_swapchain_views.size(); i++)
        {
            VkImageViewCreateInfo view_info = {};
            view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            view_info.image = m_ctx->m_swapchain_images[i];
            view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
            view_info.format = m_ctx->m_swapchain_format.format;
            view_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            view_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            view_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            view_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            view_info.subresourceRange.baseMipLevel = 0;
            view_info.subresourceRange.levelCount = 1;
            view_info.subresourceRange.baseArrayLayer = 0;
            view_info.subresourceRange.layerCount = 1;

            auto res = vkCreateImageView(m_ctx->m_device, &view_info, nullptr, &m_ctx->m_swapchain_views[i]);
            assert(res == VK_SUCCESS);
        }
    }

}



}




















