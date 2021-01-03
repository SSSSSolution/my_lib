#include "command_buffer_initializer.h"

namespace reality
{
namespace r_render_system {

CommandBufferInitializer::CommandBufferInitializer(std::shared_ptr<VulkanContext> ctx)
{
    m_ctx = ctx;
    printf("command buffer allocate...\n");
    init_command_buffer();
}

CommandBufferInitializer::~CommandBufferInitializer()
{

}

void CommandBufferInitializer::init_command_buffer()
{
    m_ctx->m_cmd_bufs.resize(m_ctx->m_framebuffers.size());
    VkCommandBufferAllocateInfo cmd_alloc_info = {};
    cmd_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_alloc_info.pNext = nullptr;
    cmd_alloc_info.commandPool = m_ctx->m_cmd_pool;
    cmd_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_alloc_info.commandBufferCount = m_ctx->m_cmd_bufs.size();

    auto res = vkAllocateCommandBuffers(m_ctx->m_device, &cmd_alloc_info, m_ctx->m_cmd_bufs.data());
    assert(res == VK_SUCCESS);

    for (int i = 0; i < m_ctx->m_cmd_bufs.size(); i++)
    {
        VkCommandBufferBeginInfo cmd_begin_info = {};
        cmd_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        res = vkBeginCommandBuffer(m_ctx->m_cmd_bufs[i], &cmd_begin_info);
        assert(res == VK_SUCCESS);

        VkRenderPassBeginInfo render_begin_info = {};
        render_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_begin_info.renderPass = m_ctx->m_renderpass;
        render_begin_info.framebuffer = m_ctx->m_framebuffers[i];
        render_begin_info.renderArea.offset = {0, 0};
        render_begin_info.renderArea.extent = m_ctx->m_swapchain_extent;

        VkClearValue clear_color = { 0.0f, 0.0f, 0.0f, 1.0f};
        render_begin_info.clearValueCount = 1;
        render_begin_info.pClearValues = &clear_color;

        vkCmdBeginRenderPass(m_ctx->m_cmd_bufs[i], &render_begin_info, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(m_ctx->m_cmd_bufs[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_ctx->m_pipeline);
        vkCmdDraw(m_ctx->m_cmd_bufs[i], 3, 1, 0, 0);
        vkCmdEndRenderPass(m_ctx->m_cmd_bufs[i]);

        res = vkEndCommandBuffer(m_ctx->m_cmd_bufs[i]);
        assert(res == VK_SUCCESS);
    }
}
}
}




















