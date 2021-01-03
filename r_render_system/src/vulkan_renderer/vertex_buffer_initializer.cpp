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
        VkBufferCreateInfo buf_info = {};
        buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buf_info.pNext = nullptr;
        buf_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        buf_info.size = sizeof(vertices[0]) * vertices.size();
        buf_info.queueFamilyIndexCount = 0;
        buf_info.pQueueFamilyIndices = nullptr;
        buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        buf_info.flags = 0;
        auto res = vkCreateBuffer(m_ctx->m_device, &buf_info, nullptr, &m_ctx->m_vertex_buf.buf);
        assert(res == VK_SUCCESS);

        VkMemoryRequirements mem_reqs;
        vkGetBufferMemoryRequirements(m_ctx->m_device, m_ctx->m_vertex_buf.buf, &mem_reqs);

        VkMemoryAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.pNext = nullptr;
        alloc_info.memoryTypeIndex = 0;
        alloc_info.allocationSize = mem_reqs.size;

        bool pass = VulkanHelper::memory_type_from_properties(m_ctx,
                    mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &alloc_info.memoryTypeIndex);
        assert(pass);

        res = vkAllocateMemory(m_ctx->m_device, &alloc_info, nullptr, &(m_ctx->m_vertex_buf.mem));
        assert(res == VK_SUCCESS);
//        printf("vertex buffer size: %d\n", mem_reqs.size);

        res = vkBindBufferMemory(m_ctx->m_device, m_ctx->m_vertex_buf.buf, m_ctx->m_vertex_buf.mem, 0);
        assert(res == VK_SUCCESS);

        uint8_t *data;
        res = vkMapMemory(m_ctx->m_device, m_ctx->m_vertex_buf.mem, 0,
                          mem_reqs.size, 0, (void **)&data);
            memcpy(data, vertices.data(), (size_t)buf_info.size);
        vkUnmapMemory(m_ctx->m_device, m_ctx->m_vertex_buf.mem);
        assert(res == VK_SUCCESS);
    }
}
}






















