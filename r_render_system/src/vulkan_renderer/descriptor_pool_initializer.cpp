#include "descriptor_pool_initializer.h"

namespace reality
{
namespace r_render_system
{
    DescriptorPoolInitializer::DescriptorPoolInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        m_use_texture = false;
        init_descriptor_pool();
        printf("descriptor pool inited\n");
    }

    void DescriptorPoolInitializer::init_descriptor_pool()
    {
        VkDescriptorPoolSize type_count[2];
        type_count[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        type_count[0].descriptorCount = 1;

        if (m_use_texture)
        {
            type_count[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            type_count[1].descriptorCount = 1;
        }

        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.pNext = nullptr;
        pool_info.maxSets = 1;
        pool_info.poolSizeCount = m_use_texture ? 2 : 1;
        pool_info.pPoolSizes = type_count;

        auto res = vkCreateDescriptorPool(m_ctx->m_device, &pool_info, nullptr, &m_ctx->m_desc_pool);
        assert(res == VK_SUCCESS);
    }
}
}
