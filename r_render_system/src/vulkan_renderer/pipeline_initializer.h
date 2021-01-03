#ifndef REALITY_RENDER_SYSTEM_PIPELINE_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_PIPELINE_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>


namespace reality
{
    namespace r_render_system
    {
    class PipelineInitializer
    {
    public:
        PipelineInitializer(std::shared_ptr<VulkanContext> ctx);
        ~PipelineInitializer();

        void init_pipeline_cache();
        void init_pipeline();

    private:
        std::shared_ptr<VulkanContext> m_ctx;
        bool m_include_depth;
    };
    }
}


#endif
