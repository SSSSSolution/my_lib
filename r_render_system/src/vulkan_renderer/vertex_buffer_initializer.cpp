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
        init_vertex_buffer();
        printf("vertex buffer inited\n");
    }

    void VertexBufferInitializer::init_vertex_buffer()
    {
        VkBufferCreateInfo buf_info = {};
        buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buf_info.pNext = nullptr;
        buf_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        buf_info.size = sizeof(g_vb_solid_face_colors_Data);
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

        m_ctx->m_vertex_buf.buffer_info.range = mem_reqs.size;
        m_ctx->m_vertex_buf.buffer_info.offset = 0;

        uint8_t *pData;
        res = vkMapMemory(m_ctx->m_device, m_ctx->m_vertex_buf.mem, 0,
                          mem_reqs.size, 0, (void **)&pData);
        assert(res == VK_SUCCESS);

        memcpy(pData, g_vb_solid_face_colors_Data, sizeof(g_vb_solid_face_colors_Data));

        vkUnmapMemory(m_ctx->m_device, m_ctx->m_vertex_buf.mem);
        res = vkBindBufferMemory(m_ctx->m_device, m_ctx->m_vertex_buf.buf, m_ctx->m_vertex_buf.mem, 0);
        assert(res == VK_SUCCESS);

        m_ctx->vi_binding.binding = 0;
        m_ctx->vi_binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        m_ctx->vi_binding.stride = sizeof(g_vb_solid_face_colors_Data);

        m_ctx->vi_attribs[0].binding = 0;
        m_ctx->vi_attribs[0].location = 0;
        m_ctx->vi_attribs[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        m_ctx->vi_attribs[0].offset = 0;
        m_ctx->vi_attribs[1].binding = 0;
        m_ctx->vi_attribs[1].location = 1;
        m_ctx->vi_attribs[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        m_ctx->vi_attribs[1].offset = 16;
    }
}
}






















