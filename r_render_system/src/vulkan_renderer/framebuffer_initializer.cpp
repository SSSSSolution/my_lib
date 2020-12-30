#include "framebuffer_initializer.h"

namespace reality
{
namespace  r_render_system
{
    FramebufferInitializer::FramebufferInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        init_framebuffers();
        printf("frame buffer inited\n");
    }

    void FramebufferInitializer::init_framebuffers()
    {

        m_ctx->m_framebuffers.resize(m_ctx->m_swapchain_images.size());
        for (uint32_t i = 0; i < m_ctx->m_swapchain_images.size(); i++)
        {
            VkImageView attachments[2];
            attachments[0] = m_ctx->m_swapchain_buffers[i].view;
            attachments[1] = m_ctx->m_depth.view;

            VkFramebufferCreateInfo fb_info = {};;
            fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            fb_info.pNext = nullptr;
            fb_info.renderPass = m_ctx->m_renderpass;
            fb_info.attachmentCount = 2;
            fb_info.pAttachments = attachments;
            fb_info.width = m_ctx->m_window->width();
            fb_info.height = m_ctx->m_window->height();
            fb_info.layers = 1;

           auto res = vkCreateFramebuffer(m_ctx->m_device, &fb_info, nullptr,
                                         &m_ctx->m_framebuffers[i]);
            assert(res == VK_SUCCESS);
        }
    }

}
}
