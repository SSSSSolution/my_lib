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
        init_pipeline_cache();
        init_pipeline();
        printf("pipeline inted\n");
    }

    void PipelineInitializer::init_pipeline_cache()
    {
        VkPipelineCacheCreateInfo cache_info = {};
        cache_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
        cache_info.pNext = nullptr;
        cache_info.initialDataSize = 0;
        cache_info.pInitialData = nullptr;
        cache_info.flags = 0;
        auto res = vkCreatePipelineCache(m_ctx->m_device, &cache_info, nullptr, &m_ctx->m_pipeline_cache);
        assert(res == VK_SUCCESS);
    }

    void PipelineInitializer::init_pipeline()
    {
        VkDynamicState dynamicStateEnables[2];// viewport + scissor
        VkPipelineDynamicStateCreateInfo dynamic_state_info = {};
        memset(dynamicStateEnables, 0, sizeof(dynamicStateEnables));
        dynamic_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic_state_info.pNext = nullptr;
        dynamic_state_info.pDynamicStates = dynamicStateEnables;
        dynamic_state_info.dynamicStateCount = 0;

        VkPipelineVertexInputStateCreateInfo vi = {};
        memset(&vi, 0, sizeof(vi));
        vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        vi.pNext = nullptr;
        vi.flags = 0;
        vi.vertexBindingDescriptionCount  = 0;
//        vi.pVertexBindingDescriptions = &m_ctx->vi_binding;
        vi.vertexAttributeDescriptionCount = 0;
//        vi.pVertexAttributeDescriptions = m_ctx->vi_attribs;

        VkPipelineInputAssemblyStateCreateInfo ia;
        ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ia.pNext = nullptr;
        ia.flags = 0;
        ia.primitiveRestartEnable = VK_FALSE;
        ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        VkPipelineRasterizationStateCreateInfo rs;
        rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rs.pNext = nullptr;
        rs.flags = 0;
        rs.polygonMode = VK_POLYGON_MODE_FILL;
        rs.cullMode = VK_CULL_MODE_BACK_BIT;
        rs.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rs.depthClampEnable = VK_FALSE;
        rs.rasterizerDiscardEnable = VK_FALSE;
        rs.depthBiasConstantFactor = 0;
        rs.depthBiasClamp = 0;
        rs.depthBiasSlopeFactor = 0;
        rs.lineWidth = 1.0f;

        VkPipelineColorBlendStateCreateInfo cb;
        cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        cb.flags = 0;
        cb.pNext = nullptr;
        VkPipelineColorBlendAttachmentState att_state[1];
        att_state[0].colorWriteMask = 0xf;
        att_state[0].blendEnable = VK_FALSE;
        att_state[0].alphaBlendOp = VK_BLEND_OP_ADD;
        att_state[0].colorBlendOp = VK_BLEND_OP_ADD;
        att_state[0].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        att_state[0].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        att_state[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        att_state[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        cb.attachmentCount = 1;
        cb.pAttachments = att_state;
        cb.logicOpEnable = VK_FALSE;
        cb.logicOp = VK_LOGIC_OP_NO_OP;
        cb.blendConstants[0] = 1.0f;
        cb.blendConstants[1] = 1.0f;
        cb.blendConstants[2] = 1.0f;
        cb.blendConstants[3] = 1.0f;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)m_ctx->m_window->width();
        viewport.height = (float)m_ctx->m_window->height();
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent.width = (float)m_ctx->m_window->width();
        scissor.extent.height = (float)m_ctx->m_window->height();

        VkPipelineViewportStateCreateInfo vp = {};
        vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        vp.pNext = NULL;
        vp.flags = 0;
        vp.viewportCount = 1;
        vp.scissorCount = 1;
        vp.pViewports = &viewport;
        vp.pScissors = &scissor;

        VkPipelineDepthStencilStateCreateInfo ds;
        ds.sType =                                                           VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        ds.pNext = NULL;
        ds.flags = 0;
        ds.depthTestEnable = m_include_depth;
        ds.depthWriteEnable = m_include_depth;
        ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        ds.depthBoundsTestEnable = VK_FALSE;
        ds.stencilTestEnable = VK_FALSE;
        ds.back.failOp = VK_STENCIL_OP_KEEP;
        ds.back.passOp = VK_STENCIL_OP_KEEP;
        ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
        ds.back.compareMask = 0;
        ds.back.reference = 0;
        ds.back.depthFailOp = VK_STENCIL_OP_KEEP;
        ds.back.writeMask = 0;
        ds.minDepthBounds = 0;
        ds.maxDepthBounds = 0;
        ds.stencilTestEnable = VK_FALSE;
        ds.front = ds.back;

        VkPipelineMultisampleStateCreateInfo ms;
        ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        ms.pNext = NULL;
        ms.flags = 0;
        ms.pSampleMask = NULL;
        ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        ms.sampleShadingEnable = VK_FALSE;
        ms.alphaToCoverageEnable = VK_FALSE;
        ms.alphaToOneEnable = VK_FALSE;
        ms.minSampleShading = 0.0;

        VkGraphicsPipelineCreateInfo pipeline;
        pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline.pNext = NULL;
        pipeline.layout = m_ctx->m_pipeline_layout;
        pipeline.basePipelineHandle = VK_NULL_HANDLE;
        pipeline.basePipelineIndex = 0;
        pipeline.flags = 0;
        pipeline.pVertexInputState = &vi;
        pipeline.pInputAssemblyState = &ia;
        pipeline.pRasterizationState = &rs;
        pipeline.pColorBlendState = &cb;
        pipeline.pTessellationState = NULL;
        pipeline.pMultisampleState = &ms;
        pipeline.pDynamicState = &dynamic_state_info;
        pipeline.pViewportState = &vp;
        pipeline.pDepthStencilState = &ds;
        pipeline.pStages = m_ctx->m_shader_stages;
        pipeline.stageCount = 2;
        pipeline.renderPass = m_ctx->m_renderpass;
        pipeline.subpass = 0;

        auto res = vkCreateGraphicsPipelines(m_ctx->m_device, m_ctx->m_pipeline_cache, 1,
                                             &pipeline, NULL, &m_ctx->m_pipeline);
        assert(res == VK_SUCCESS);
    }
    }
}


























