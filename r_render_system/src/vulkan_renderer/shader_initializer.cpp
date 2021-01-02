#include "shader_initializer.h"
#include "triangle.frag.h"
#include "triangle.vert.h"
namespace reality
{
namespace r_render_system
{
    ShaderInitializer::ShaderInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        init_shader();
        printf("shader inited\n");
    }

    void ShaderInitializer::init_shader()
    {
        VkShaderModuleCreateInfo vert_info = {};
        VkShaderModuleCreateInfo frag_info = {};

        vert_info.sType = frag_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        vert_info.codeSize = sizeof(triangle_vert);
        vert_info.pCode = triangle_vert;
        auto res = vkCreateShaderModule(m_ctx->m_device, &vert_info, nullptr, &m_ctx->m_vertex_shader_module);
        assert(res == VK_SUCCESS);

        frag_info.codeSize = sizeof(triangle_frag);
        frag_info.pCode = triangle_frag;
        res = vkCreateShaderModule(m_ctx->m_device, &frag_info, nullptr, &m_ctx->m_frag_shader_module);
        assert(res == VK_SUCCESS);

        m_ctx->m_shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_ctx->m_shader_stages[0].pNext = nullptr;
        m_ctx->m_shader_stages[0].pSpecializationInfo = nullptr;
        m_ctx->m_shader_stages[0].flags = 0;
        m_ctx->m_shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        m_ctx->m_shader_stages[0].pName = "main";
        m_ctx->m_shader_stages[0].module = m_ctx->m_vertex_shader_module;
        res = vkCreateShaderModule(m_ctx->m_device, &vert_info, nullptr, &m_ctx->m_shader_stages[0].module);
        assert(res == VK_SUCCESS);

        m_ctx->m_shader_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_ctx->m_shader_stages[1].pNext = nullptr;
        m_ctx->m_shader_stages[1].pSpecializationInfo = nullptr;
        m_ctx->m_shader_stages[1].flags = 0;
        m_ctx->m_shader_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        m_ctx->m_shader_stages[1].pName = "main";
        m_ctx->m_shader_stages[1].module = m_ctx->m_frag_shader_module;
        res = vkCreateShaderModule(m_ctx->m_device, &frag_info, nullptr, &m_ctx->m_shader_stages[1].module);
        assert(res == VK_SUCCESS);

    }
}
}
