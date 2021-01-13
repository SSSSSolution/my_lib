#include "descriptor_set_initializer.h"

namespace reality
{
namespace r_render_system
{
    DescriptorSetInitializer::DescriptorSetInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        m_use_texture = false;
        init_descriptor_set();
        printf("descriptor set inited\n");
    }

    void DescriptorSetInitializer::init_descriptor_set()
    {
        std::vector<VkDescriptorSetLayout> layouts(m_ctx->m_swapchain_images.size(), m_ctx->m_descriptor_set_layout);

        VkDescriptorSetAllocateInfo alloc_info[1];
        alloc_info[0].sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info[0].pNext = nullptr;
        alloc_info[0].descriptorPool = m_ctx->m_desc_pool;
        alloc_info[0].descriptorSetCount = m_ctx->m_swapchain_images.size();
        alloc_info[0].pSetLayouts = layouts.data();

        m_ctx->m_descriptor_sets.resize(m_ctx->m_swapchain_images.size());
        auto res = vkAllocateDescriptorSets(m_ctx->m_device, alloc_info, m_ctx->m_descriptor_sets.data());
        assert(res == VK_SUCCESS);

        for (size_t i = 0; i < m_ctx->m_swapchain_images.size(); i++)
        {
            VkDescriptorBufferInfo buffer_info = {};
            buffer_info.buffer = m_ctx->m_uniform_bufs[i];
            buffer_info.offset = 0;
            buffer_info.range = sizeof(UniformBufferObject);

            VkDescriptorImageInfo image_info = {};
            image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            image_info.imageView = m_ctx->m_texture_image_view;
            image_info.sampler = m_ctx->m_texture_sampler;

            std::vector<VkWriteDescriptorSet> descriptor_writes(2);
            descriptor_writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptor_writes[0].dstSet = m_ctx->m_descriptor_sets[i];
            descriptor_writes[0].dstBinding = 0;
            descriptor_writes[0].dstArrayElement = 0;
            descriptor_writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptor_writes[0].descriptorCount = 1;
            descriptor_writes[0].pBufferInfo = &buffer_info;
            descriptor_writes[0].pImageInfo = nullptr;
            descriptor_writes[0].pTexelBufferView = nullptr;

            descriptor_writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptor_writes[1].dstSet = m_ctx->m_descriptor_sets[i];
            descriptor_writes[1].dstBinding = 1;
            descriptor_writes[1].dstArrayElement = 0;
            descriptor_writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptor_writes[1].descriptorCount = 1;
            descriptor_writes[1].pBufferInfo = nullptr;
            descriptor_writes[1].pImageInfo = &image_info;
            descriptor_writes[1].pTexelBufferView = nullptr;

            vkUpdateDescriptorSets(m_ctx->m_device, descriptor_writes.size(),
                                   descriptor_writes.data(), 0, nullptr);
        }
    }
}
}
