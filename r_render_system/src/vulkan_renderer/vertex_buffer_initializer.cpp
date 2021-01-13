#include "vertex_buffer_initializer.h"
#include "cube_data.h"
#include "vulkan_helper.h"
#include <string.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <unordered_map>

namespace reality
{
namespace r_render_system
{
    VertexBufferInitializer::VertexBufferInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        printf("vertex buffer init...\n");
        load_model();
        init_vertex_buffer();
        init_index_buffer();
        init_uniform_buffer();
    }

    void VertexBufferInitializer::load_model()
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        auto res = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                                    "/home/reality/data/modules/viking_room/viking_room.obj");
        assert(res == true);

        std::unordered_map<Vertex, uint32_t> unique_vertexs;
        for (const auto & shape : shapes)
        {
            for (const auto & index : shape.mesh.indices)
            {
                Vertex vertex{};

                vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
                };
                vertex.color = {1.0f, 1.0f, 1.0f};

                if (unique_vertexs.count(vertex) == 0)
                {
                    unique_vertexs[vertex] = vertices.size();
                    vertices.push_back(vertex);
                }
                indices.push_back(unique_vertexs[vertex]);
            }
        }
        printf("vertices size: %d\n", vertices.size());
        printf("index size: %d\n", indices.size());

    }

    void VertexBufferInitializer::init_vertex_buffer()
    {
        VkDeviceSize buffer_size = sizeof(vertices[0]) * vertices.size();

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

    void VertexBufferInitializer::init_index_buffer()
    {
        VkDeviceSize buf_size = sizeof(indices[0]) * indices.size();

        VkBuffer staging_buf;
        VkDeviceMemory staging_buf_mem;
        VulkanHelper::create_buffer(m_ctx, buf_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                    staging_buf, staging_buf_mem);

        void *data;
        vkMapMemory(m_ctx->m_device, staging_buf_mem, 0, buf_size, 0, &data);
        memcpy(data, indices.data(), (size_t)buf_size);
        vkUnmapMemory(m_ctx->m_device, staging_buf_mem);

        VulkanHelper::create_buffer(m_ctx, buf_size,
                                    VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                    VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                    m_ctx->m_index_buf.buf, m_ctx->m_index_buf.mem);
        VulkanHelper::copy_buffer(m_ctx, staging_buf,
                                  m_ctx->m_index_buf.buf, (size_t)buf_size);
    }

    void VertexBufferInitializer::init_uniform_buffer()
    {
        VkDeviceSize buf_size = sizeof(UniformBufferObject);

        m_ctx->m_uniform_bufs.resize(m_ctx->m_swapchain_images.size());
        m_ctx->m_uniform_buffer_mems.resize(m_ctx->m_swapchain_images.size());

        for (size_t i = 0; i < m_ctx->m_swapchain_images.size(); i++)
        {
            VulkanHelper::create_buffer(m_ctx, buf_size,
                                        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                        m_ctx->m_uniform_bufs[i],
                                        m_ctx->m_uniform_buffer_mems[i]);
        }
    }
}
}






















