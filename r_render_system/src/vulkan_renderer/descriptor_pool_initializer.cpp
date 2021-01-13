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
        printf("descriptor pool init...\n");
    }

    void DescriptorPoolInitializer::init_descriptor_pool()
    {
        std::vector<VkDescriptorPoolSize> pool_sizes(2);
        pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        pool_sizes[0].descriptorCount = m_ctx->m_swapchain_images.size();
        pool_sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        pool_sizes[1].descriptorCount = m_ctx->m_swapchain_images.size();

        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.pNext = nullptr;
        pool_info.maxSets =  m_ctx->m_swapchain_images.size();
        pool_info.poolSizeCount = pool_sizes.size();
        pool_info.pPoolSizes = pool_sizes.data();

        auto res = vkCreateDescriptorPool(m_ctx->m_device, &pool_info, nullptr, &m_ctx->m_desc_pool);
        assert(res == VK_SUCCESS);
    }
}
}
