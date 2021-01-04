#include "vertex_buffer_initializer.h"
#include "cube_data.h"
#include "vulkan_helper.h"
#include <string.h>

namespace reality
{
namespace r_render_system
{
    VertexBufferInitializer::VertexBufferInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        printf("vertex buffer init...\n");
        init_vertex_buffer();
    }

    void VertexBufferInitializer::init_vertex_buffer()
    {
        VkDeviceSize buffer_size = sizeof(vertices[0]) * vertices.size();
//        VulkanHelper::create_buffer(m_ctx, buffer_size,
//                VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
//                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
//                VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
//                m_ctx->m_vertex_buf.buf, m_ctx->m_vertex_buf.mem);

//        uint8_t *data;
//        auto res = vkMapMemory(m_ctx->m_device, m_ctx->m_vertex_buf.mem, 0,
//                          buffer_size, 0, (void **)&data);
//            memcpy(data, vertices.data(), (size_t)buffer_size);
//        vkUnmapMemory(m_ctx->m_device, m_ctx->m_vertex_buf.mem);
//        assert(res == VK_SUCCESS);

        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;
        VulkanHelper::create_buffer(m_ctx, (size_t)buffer_size,
                                    VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                    staging_buffer, staging_buffer_memory);

        void *data;
        auto res = vkMapMemory(m_ctx->m_device, staging_buffer_memory, 0,
                          buffer_size, 0, (void **)&data);
            memcpy(data, vertices.data(), (size_t)buffer_size);
        vkUnmapMemory(m_ctx->m_device, staging_buffer_memory);


        VulkanHelper::create_buffer(m_ctx, (size_t)buffer_size,
                                    VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                    m_ctx->m_vertex_buf.buf, m_ctx->m_vertex_buf.mem);
        VulkanHelper::copy_buffer(m_ctx, staging_buffer,
                                  m_ctx->m_vertex_buf.buf, buffer_size);

    }
}
}






















