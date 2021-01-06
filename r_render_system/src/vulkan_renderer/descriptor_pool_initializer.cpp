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
        VkDescriptorPoolSize pool_size{};
        pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        pool_size.descriptorCount = m_ctx->m_swapchain_images.size();

        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.pNext = nullptr;
        pool_info.maxSets =  m_ctx->m_swapchain_images.size();
        pool_info.poolSizeCount = 1;
        pool_info.pPoolSizes = &pool_size;

        auto res = vkCreateDescriptorPool(m_ctx->m_device, &pool_info, nullptr, &m_ctx->m_desc_pool);
        assert(res == VK_SUCCESS);
    }
}
}
