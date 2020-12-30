#include "descriptor_and_pipeline_initializer.h"

namespace reality
{
namespace r_render_system
{
    DescriptorAndPipelineInitializer::DescriptorAndPipelineInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;
        m_use_texture = false;
        init_descriptor_and_pipeline();
        printf("descriptor and pipeline inited!\n");
    }

    void DescriptorAndPipelineInitializer::init_descriptor_and_pipeline()
    {
        VkDescriptorSetLayoutBinding layout_bindings[2];
        layout_bindings[0].binding = 0;
        layout_bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        layout_bindings[0].descriptorCount = 1;
        layout_bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        layout_bindings[0].pImmutableSamplers = nullptr;

        if (m_use_texture)
        {
            layout_bindings[1].binding = 1;
            layout_bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            layout_bindings[1].descriptorCount = 1;
            layout_bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
            layout_bindings[1].pImmutableSamplers = nullptr;
        }

        /* Next take layout bindings and use them to create a descriptor set layout */
        VkDescriptorSetLayoutCreateInfo descriptor_layout = {};
        descriptor_layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptor_layout.pNext = nullptr;
        descriptor_layout.flags = 0;
        descriptor_layout.bindingCount = m_use_texture  ? 2 : 1;
        descriptor_layout.pBindings = layout_bindings;

        m_vulkan_context->m_desc_layouts.resize(1);
        auto res = vkCreateDescriptorSetLayout(m_vulkan_context->m_device, &descriptor_layout, nullptr, m_vulkan_context->m_desc_layouts.data());
        assert(res == VK_SUCCESS);

        /* Now use the descriptor  layout to create a pipeline layout */
        VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {};
        pPipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pPipelineLayoutCreateInfo.pNext = nullptr;
        pPipelineLayoutCreateInfo.pushConstantRangeCount = 0;
        pPipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
        pPipelineLayoutCreateInfo.setLayoutCount = 1;
        pPipelineLayoutCreateInfo.pSetLayouts = m_vulkan_context->m_desc_layouts.data();

        res = vkCreatePipelineLayout(m_vulkan_context->m_device, &pPipelineLayoutCreateInfo, nullptr, &m_vulkan_context->m_pipeline_layout);
        assert(res == VK_SUCCESS);
    }
}
}





















