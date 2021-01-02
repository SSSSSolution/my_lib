#include "renderpass_initializer.h"

namespace reality
{
namespace r_render_system
{
    RenderPassInitializer::RenderPassInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        m_include_depth = true;
        printf("render pass init...\n");
        init_renderpass();
    }

    void RenderPassInitializer::init_renderpass()
    {
        VkAttachmentDescription color_attachment;
        color_attachment.format = m_ctx->m_swapchain_format.format;
        color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        color_attachment.flags = 0;

        VkAttachmentReference color_attachment_ref = {};
        color_attachment_ref.attachment  = 0;
        color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass_description = {};
        subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass_description.colorAttachmentCount = 1;
        subpass_description.pColorAttachments = &color_attachment_ref;

        VkRenderPassCreateInfo renderpass_info = {};
        renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderpass_info.attachmentCount = 1;
        renderpass_info.pAttachments = &color_attachment;
        renderpass_info.subpassCount = 1;
        renderpass_info.pSubpasses = &subpass_description;

        auto res = vkCreateRenderPass(m_ctx->m_device, &renderpass_info, nullptr, &m_ctx->m_renderpass);
        assert(res == VK_SUCCESS);
    }


}
}




















