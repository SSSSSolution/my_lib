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
        VkDescriptorSetAllocateInfo alloc_info[1];
        alloc_info[0].sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info[0].pNext = nullptr;
        alloc_info[0].descriptorPool = m_ctx->m_desc_pool;
        alloc_info[0].descriptorSetCount = 1;
        alloc_info[0].pSetLayouts = m_ctx->m_desc_layouts.data();

        m_ctx->m_desc_sets.resize(1);
        auto res = vkAllocateDescriptorSets(m_ctx->m_device, alloc_info, m_ctx->m_desc_sets.data());
        assert(res == VK_SUCCESS);
        VkWriteDescriptorSet writes[2];

        writes[0] = {};
        writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[0].dstSet = m_ctx->m_desc_sets[0];
        writes[0].descriptorCount = 1;
        writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        writes[0].pBufferInfo = &m_ctx->m_uniform_data.buffer_info;
        writes[0].dstArrayElement = 0;
        writes[0].dstBinding = 0;

        if (m_use_texture)
        {
            writes[1] = {};
            writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writes[1].dstSet = m_ctx->m_desc_sets[0];
            writes[1].dstBinding = 1;
            writes[1].descriptorCount = 1;
            writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            writes[1].pImageInfo = &m_ctx->m_texture_data.image_info;
            writes[1].dstArrayElement = 0;
        }
        vkUpdateDescriptorSets(m_ctx->m_device, m_use_texture ? 2 : 1, writes, 0, nullptr);
    }
}
}
