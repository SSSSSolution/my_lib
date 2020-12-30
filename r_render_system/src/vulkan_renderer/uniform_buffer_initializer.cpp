#include "uniform_buffer_initializer.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "vulkan_helper.h"
#include <string.h>

namespace reality
{
    namespace r_render_system
    {
        UniformBufferInitializer::UniformBufferInitializer(std::shared_ptr<VulkanContext> vulkan_context)
        {
            m_vulkan_context = vulkan_context;
            init_uniform_buffer();
        }

        void UniformBufferInitializer::init_uniform_buffer()
        {
            float fov = glm::radians(45.0f);
            if (m_vulkan_context->m_window->width() >
                m_vulkan_context->m_window->height())
            {
                fov *= static_cast<float>(m_vulkan_context->m_window->height()) /
                       static_cast<float>(m_vulkan_context->m_window->width());
            }

            m_vulkan_context->m_projection = glm::perspective(
                        fov, static_cast<float>(m_vulkan_context->m_window->width())/
                        static_cast<float>(m_vulkan_context->m_window->height()), 0.1f, 100.0f);
            m_vulkan_context->m_view = glm::lookAt(glm::vec3(-5, 3, -10),
                                                   glm::vec3(0, 0, 0),
                                                   glm::vec3(0, -1, 0));
            m_vulkan_context->m_model = glm::mat4(1.0f);
            // vulkan clip space has inverted Y and half Z.
            m_vulkan_context->m_clip = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                                 0.0f,-1.0f, 0.0f, 0.0f,
                                                 0.0f, 0.0f, 0.5f, 0.0f,
                                                 0.0f, 0.0f, 0.5f, 1.0f);

            m_vulkan_context->m_mvp = m_vulkan_context->m_clip * m_vulkan_context->m_projection *
                    m_vulkan_context->m_view * m_vulkan_context->m_model;
            /* Vulkan key start */
            VkBufferCreateInfo buf_info = {};
            buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            buf_info.pNext = nullptr;
            buf_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
            buf_info.size = sizeof(m_vulkan_context->m_mvp);
            buf_info.queueFamilyIndexCount = 0;
            buf_info.pQueueFamilyIndices = nullptr;
            buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            buf_info.flags = 0;
            auto res = vkCreateBuffer(m_vulkan_context->m_device, &buf_info, nullptr, &m_vulkan_context->m_uniform_data.buf);
            assert(res == VK_SUCCESS);

            VkMemoryRequirements mem_reqs;
            vkGetBufferMemoryRequirements(m_vulkan_context->m_device, m_vulkan_context->m_uniform_data.buf, &mem_reqs);

            VkMemoryAllocateInfo alloc_info = {};
            alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            alloc_info.pNext = nullptr;
            alloc_info.memoryTypeIndex = 0;
            alloc_info.allocationSize = mem_reqs.size;
            bool pass = VulkanHelper::memory_type_from_properties(m_vulkan_context,
                                                                  mem_reqs.memoryTypeBits,
                                                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                                                   &alloc_info.memoryTypeIndex);
            assert(pass);

            res = vkAllocateMemory(m_vulkan_context->m_device, &alloc_info, nullptr, &m_vulkan_context->m_uniform_data.mem);
            assert(res == VK_SUCCESS);

            uint8_t *pData;
            res = vkMapMemory(m_vulkan_context->m_device, m_vulkan_context->m_uniform_data.mem, 0,
                              mem_reqs.size, 0, (void **)&pData);
            assert(res == VK_SUCCESS);

            memcpy(pData, &m_vulkan_context->m_mvp, sizeof(m_vulkan_context->m_mvp));

            vkUnmapMemory(m_vulkan_context->m_device, m_vulkan_context->m_uniform_data.mem);

            res = vkBindBufferMemory(m_vulkan_context->m_device, m_vulkan_context->m_uniform_data.buf, m_vulkan_context->m_uniform_data.mem, 0);
            assert(res == VK_SUCCESS);

            m_vulkan_context->m_uniform_data.buffer_info.buffer = m_vulkan_context->m_uniform_data.buf;
            m_vulkan_context->m_uniform_data.buffer_info.offset = 0;
            m_vulkan_context->m_uniform_data.buffer_info.range = sizeof(m_vulkan_context->m_mvp);
        }
    }



















}
