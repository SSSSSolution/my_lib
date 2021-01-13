#include "renderpass_initializer.h"
#include "vulkan_helper.h"

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

    RenderPassInitializer::~RenderPassInitializer()
    {
        vkDestroyRenderPass(m_ctx->m_device, m_ctx->m_renderpass, nullptr);
    }

    void RenderPassInitializer::init_renderpass()
    {
        VkAttachmentDescription color_attachment;
        color_attachment.format = m_ctx->m_swapchain_format.format;
        color_attachment.samples = m_ctx->m_msaa_samples;
        color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color_attachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        color_attachment.flags = 0;

        VkAttachmentReference color_attachment_ref = {};
        color_attachment_ref.attachment  = 0;
        color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentDescription color_attachment_resolve = {};
        color_attachment_resolve.format = m_ctx->m_swapchain_format.format;
        color_attachment_resolve.samples = VK_SAMPLE_COUNT_1_BIT;
        color_attachment_resolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment_resolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment_resolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment_resolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color_attachment_resolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color_attachment_resolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference color_attachment_resolve_ref = {};
        color_attachment_resolve_ref.attachment = 2;
        color_attachment_resolve_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


        VkAttachmentDescription depth_attachment = {};
        depth_attachment.format = VulkanHelper::find_depth_format(m_ctx);
        depth_attachment.samples = m_ctx->m_msaa_samples;
        depth_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depth_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depth_attachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depth_attachment_ref = {};
        depth_attachment_ref.attachment = 1;
        depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


        VkSubpassDescription subpass_description = {};
        subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass_description.colorAttachmentCount = 1;
        subpass_description.pColorAttachments = &color_attachment_ref;
        subpass_description.pDepthStencilAttachment = &depth_attachment_ref;
        subpass_description.pResolveAttachments = &color_attachment_resolve_ref;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                                  VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                                  VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                                   VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        std::vector<VkAttachmentDescription> attahments = {color_attachment, depth_attachment,
                                                          color_attachment_resolve};
        VkRenderPassCreateInfo renderpass_info = {};
        renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderpass_info.attachmentCount = attahments.size();
        renderpass_info.pAttachments = attahments.data();
        renderpass_info.subpassCount = 1;
        renderpass_info.pSubpasses = &subpass_description;
        renderpass_info.dependencyCount = 1;
        renderpass_info.pDependencies = &dependency;

        auto res = vkCreateRenderPass(m_ctx->m_device, &renderpass_info, nullptr, &m_ctx->m_renderpass);
        assert(res == VK_SUCCESS);
    }


}
}




















