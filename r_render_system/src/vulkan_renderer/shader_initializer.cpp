#include "shader_initializer.h"
#include "draw_cube.vert.h"
#include "draw_cube.frag.h"
namespace reality
{
namespace r_render_system
{
    ShaderInitializer::ShaderInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;
        init_shader();
        printf("shader inited\n");
    }

    void ShaderInitializer::init_shader()
    {
        VkShaderModuleCreateInfo vert_info = {};
        VkShaderModuleCreateInfo frag_info = {};

        vert_info.sType = frag_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        vert_info.codeSize = sizeof(draw_cube_vert);
        vert_info.pCode = draw_cube_vert;

        frag_info.codeSize = sizeof(draw_cube_frag);
        frag_info.pCode = draw_cube_frag;

        m_vulkan_context->m_shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_vulkan_context->m_shader_stages[0].pNext = nullptr;
        m_vulkan_context->m_shader_stages[0].pSpecializationInfo = nullptr;
        m_vulkan_context->m_shader_stages[0].flags = 0;
        m_vulkan_context->m_shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        m_vulkan_context->m_shader_stages[0].pName = "main";
        auto res = vkCreateShaderModule(m_vulkan_context->m_device, &vert_info, nullptr, &m_vulkan_context->m_shader_stages[0].module);
        assert(res == VK_SUCCESS);

        m_vulkan_context->m_shader_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_vulkan_context->m_shader_stages[1].pNext = nullptr;
        m_vulkan_context->m_shader_stages[1].pSpecializationInfo = nullptr;
        m_vulkan_context->m_shader_stages[1].flags = 0;
        m_vulkan_context->m_shader_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        m_vulkan_context->m_shader_stages[1].pName = "main";
        res = vkCreateShaderModule(m_vulkan_context->m_device, &frag_info, nullptr, &m_vulkan_context->m_shader_stages[1].module);
        assert(res == VK_SUCCESS);

    }
}
}
