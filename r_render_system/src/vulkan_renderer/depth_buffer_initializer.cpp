#include "depth_buffer_initializer.h"
#include "vulkan_helper.h"
#include <iostream>

namespace reality
{
namespace r_render_system {
    DepthBufferInitializer::DepthBufferInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        printf("depth buffer init...\n");
        m_ctx = ctx;
        init_depth_buffer();
        printf("depth buffer init finished\n");
    }

    void DepthBufferInitializer::init_depth_buffer()
    {
        VkFormat depth_format = VulkanHelper::find_depth_format(m_ctx);

        VulkanHelper::create_image(m_ctx,
                                   m_ctx->m_swapchain_extent.width,
                                   m_ctx->m_swapchain_extent.height,
                                   1,
                                   m_ctx->m_msaa_samples,
                                   depth_format,
                                   VK_IMAGE_TILING_OPTIMAL,
                                   VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                                   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                   m_ctx->m_depth_image,
                                   m_ctx->m_depth_image_mem);
        m_ctx->m_depth_image_view = VulkanHelper::create_image_view(m_ctx, m_ctx->m_depth_image,
                                                                    depth_format,
                                                                    VK_IMAGE_ASPECT_DEPTH_BIT, 1);
    }

    DepthBufferInitializer::~DepthBufferInitializer()
    {
        vkDestroyImageView(m_ctx->m_device, m_ctx->m_depth_image_view, nullptr);
        vkDestroyImage(m_ctx->m_device, m_ctx->m_depth_image, nullptr);
        vkFreeMemory(m_ctx->m_device, m_ctx->m_depth_image_mem, nullptr);
    }
}
}


























