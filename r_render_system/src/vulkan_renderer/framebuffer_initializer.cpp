#include "framebuffer_initializer.h"
#include "vulkan_helper.h"
namespace reality
{
namespace  r_render_system
{
    FramebufferInitializer::FramebufferInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        printf("frame buffer init ...\n");
        create_color_image();
        init_framebuffers();

    }

    void FramebufferInitializer::init_framebuffers()
    {
        m_ctx->m_framebuffers.resize(m_ctx->m_swapchain_views.size());
        for (uint32_t i = 0; i < m_ctx->m_swapchain_views.size(); i++)
        {
            std::vector<VkImageView> attachments = {
                m_ctx->m_color_image_view,
                m_ctx->m_depth_image_view,
                m_ctx->m_swapchain_views[i],

            };

            VkFramebufferCreateInfo fb_info = {};;
            fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            fb_info.pNext = nullptr;
            fb_info.renderPass = m_ctx->m_renderpass;
            fb_info.attachmentCount = attachments.size();
            fb_info.pAttachments = attachments.data();
            fb_info.width = m_ctx->m_swapchain_extent.width;
            fb_info.height = m_ctx->m_swapchain_extent.height;
            fb_info.layers = 1;

           auto res = vkCreateFramebuffer(m_ctx->m_device, &fb_info, nullptr,
                                         &m_ctx->m_framebuffers[i]);
            assert(res == VK_SUCCESS);
        }
    }

    void FramebufferInitializer::create_color_image()
    {
        VkFormat color_format = m_ctx->m_swapchain_format.format;
        VulkanHelper::create_image(m_ctx,
                                   m_ctx->m_swapchain_extent.width,
                                   m_ctx->m_swapchain_extent.height,
                                   1,
                                   m_ctx->m_msaa_samples,
                                   color_format,
                                   VK_IMAGE_TILING_OPTIMAL,
                                   VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT |
                                   VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                                   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                   m_ctx->m_color_image,
                                   m_ctx->m_color_image_mem);
        m_ctx->m_color_image_view = VulkanHelper::create_image_view(m_ctx,
                                                                    m_ctx->m_color_image,
                                                                    color_format,
                                                                    VK_IMAGE_ASPECT_COLOR_BIT,
                                                                    1);
    }

    FramebufferInitializer::~FramebufferInitializer()
    {
        for (int i = 0; i < m_ctx->m_framebuffers.size(); i++)
        {
            vkDestroyFramebuffer(m_ctx->m_device, m_ctx->m_framebuffers[i], nullptr);
        }
        vkDestroyImageView(m_ctx->m_device, m_ctx->m_color_image_view, nullptr);
        vkDestroyImage(m_ctx->m_device, m_ctx->m_color_image, nullptr);
        vkFreeMemory(m_ctx->m_device, m_ctx->m_color_image_mem, nullptr);
    }

}
}
