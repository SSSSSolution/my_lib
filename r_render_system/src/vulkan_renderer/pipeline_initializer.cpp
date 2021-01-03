#include "pipeline_initializer.h"
#include <string.h>

namespace reality
{
    namespace r_render_system
    {
    PipelineInitializer::PipelineInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        m_include_depth = true;
        printf("init pipeline...\n");
        init_pipeline_cache();
        init_pipeline();
    }

    PipelineInitializer::~PipelineInitializer()
    {
        vkDestroyPipeline(m_ctx->m_device, m_ctx->m_pipeline, nullptr);
        vkDestroyPipelineLayout(m_ctx->m_device, m_ctx->m_pipeline_layout, nullptr);
    }

    void PipelineInitializer::init_pipeline_cache()
    {

    }

    void PipelineInitializer::init_pipeline()
    {
        VkVertexInputBindingDescription binding_description = {};
        binding_description.binding = 0;
        binding_description.stride = sizeof(Vertex);
        binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        std::vector<VkVertexInputAttributeDescription> attribute_description(2);
        attribute_description[0].binding = 0;
        attribute_description[0].location = 0;
        attribute_description[0].format = VK_FORMAT_R32G32_SFLOAT;
        attribute_description[0].offset = offsetof(Vertex, pos);

        attribute_description[1].binding = 0;
        attribute_description[1].location = 1;
        attribute_description[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attribute_description[1].offset = offsetof(Vertex, color);

        /* vertex input */
        VkPipelineVertexInputStateCreateInfo vi_info = {};
        vi_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vi_info.vertexBindingDescriptionCount = 1;
        vi_info.pVertexBindingDescriptions = &binding_description;
        vi_info.vertexAttributeDescriptionCount = 2;
        vi_info.pVertexAttributeDescriptions = attribute_description.data();

        /* input assembly */
        VkPipelineInputAssemblyStateCreateInfo ia_info = {};
        ia_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ia_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        ia_info.primitiveRestartEnable = VK_FALSE;

        /* view port */
        VkViewport view_port = {};
        view_port.x = 0.0f;
        view_port.y = 0.0f;
        view_port.width = (float)m_ctx->m_swapchain_extent.width;
        view_port.height = (float)m_ctx->m_swapchain_extent.height;
        view_port.minDepth = 0.0f;
        view_port.maxDepth = 1.0f;

        VkRect2D scissor = {};
        scissor.offset = {0, 0};
        scissor.extent = m_ctx->m_swapchain_extent;

        VkPipelineViewportStateCreateInfo vp_info = {};
        vp_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        vp_info.viewportCount = 1;
        vp_info.pViewports = &view_port;
        vp_info.scissorCount = 1;
        vp_info.pScissors = &scissor;

        /* Rasterizer */
        VkPipelineRasterizationStateCreateInfo r_info = {};
        r_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        r_info.depthClampEnable = VK_FALSE;
        r_info.rasterizerDiscardEnable = VK_FALSE;
        r_info.polygonMode = VK_POLYGON_MODE_FILL;
        r_info.lineWidth = 1.0f;
        r_info.cullMode = VK_CULL_MODE_BACK_BIT;
        r_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
        r_info.depthBiasEnable = VK_FALSE;
        r_info.depthBiasConstantFactor = 0.0f;
        r_info.depthBiasClamp = 0.0f;
        r_info.depthBiasSlopeFactor = 0.0f;

        /* Multisampling */
        VkPipelineMultisampleStateCreateInfo ms_info = {};
        ms_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        ms_info.sampleShadingEnable = VK_FALSE;
        ms_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        ms_info.minSampleShading = 1.0f;
        ms_info.pSampleMask = nullptr;
        ms_info.alphaToCoverageEnable = VK_FALSE;
        ms_info.alphaToOneEnable = VK_FALSE;

        /* Color Blending */
        VkPipelineColorBlendAttachmentState color_blend_attachment = {};
        color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
                                                VK_COLOR_COMPONENT_G_BIT |
                                                VK_COLOR_COMPONENT_B_BIT |
                                                VK_COLOR_COMPONENT_A_BIT;
        color_blend_attachment.blendEnable = VK_FALSE;
        color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
        color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

        VkPipelineColorBlendStateCreateInfo color_blend_info = {};
        color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        color_blend_info.logicOpEnable = VK_FALSE;
        color_blend_info.attachmentCount = 1;
        color_blend_info.pAttachments = &color_blend_attachment;
        color_blend_info.blendConstants[0] = 0.0f;
        color_blend_info.blendConstants[1] = 0.0f;
        color_blend_info.blendConstants[2] = 0.0f;
        color_blend_info.blendConstants[3] = 0.0f;

        /* pipeline layout */
        VkPipelineLayoutCreateInfo pipeline_layout_info = {};
        pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_info.setLayoutCount = 0;
        pipeline_layout_info.pSetLayouts = nullptr;
        pipeline_layout_info.pushConstantRangeCount = 0;
        pipeline_layout_info.pPushConstantRanges = nullptr;

        auto res = vkCreatePipelineLayout(m_ctx->m_device, &pipeline_layout_info,
                                          nullptr, &m_ctx->m_pipeline_layout);
        assert(res == VK_SUCCESS);

        /*pipeline */
        VkGraphicsPipelineCreateInfo pipeline_info = {};
        pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_info.stageCount = 2;
        pipeline_info.pStages = m_ctx->m_shader_stages;
        pipeline_info.pVertexInputState = &vi_info;
        pipeline_info.pInputAssemblyState = &ia_info;
        pipeline_info.pViewportState = &vp_info;
        pipeline_info.pRasterizationState = &r_info;
        pipeline_info.pMultisampleState = &ms_info;
        pipeline_info.pDepthStencilState = nullptr;
        pipeline_info.pColorBlendState = &color_blend_info;
        pipeline_info.pDynamicState = nullptr;
        pipeline_info.layout = m_ctx->m_pipeline_layout;
        pipeline_info.renderPass = m_ctx->m_renderpass;
        pipeline_info.subpass = 0;
        pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
        pipeline_info.basePipelineIndex = -1;

        res = vkCreateGraphicsPipelines(m_ctx->m_device,
                                        VK_NULL_HANDLE, 1,
                                        &pipeline_info, nullptr,
                                        &m_ctx->m_pipeline);
        assert(res == VK_SUCCESS);
    }
    }
}


























