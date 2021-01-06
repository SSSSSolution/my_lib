#include "descriptor_set_layout_initializer.h"

namespace reality
{
namespace r_render_system
{
    DescriptorSetLayoutInitializer::DescriptorSetLayoutInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        printf("descriptor set layout init...\n");
        init_descriptor_set_layout();
    }

    void DescriptorSetLayoutInitializer::init_descriptor_set_layout()
    {
        VkDescriptorSetLayoutBinding ubo_layout_binding = {};
        ubo_layout_binding.binding = 0;
        ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        ubo_layout_binding.descriptorCount = 1;
        ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        ubo_layout_binding.pImmutableSamplers = nullptr;

        VkDescriptorSetLayoutCreateInfo layout_info = {};
        layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layout_info.bindingCount = 1;
        layout_info.pBindings = &ubo_layout_binding;

        auto res = vkCreateDescriptorSetLayout(m_ctx->m_device, &layout_info,
                                               nullptr, &m_ctx->m_descriptor_set_layout);
        assert(res == VK_SUCCESS);
    }
}
}
