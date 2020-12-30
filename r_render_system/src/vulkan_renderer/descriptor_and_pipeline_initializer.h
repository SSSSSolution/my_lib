#ifndef REALITY_RENDER_SYSTEM_DESCRIPTOR_AND_PIPELINE_INITIALIZER
#define REALITY_RENDER_SYSTEM_DESCRIPTOR_AND_PIPELINE_INITIALIZER

#include "vulkan_context.h"
#include <memory>

namespace reality
{
namespace r_render_system
{
    class DescriptorAndPipelineInitializer
    {
    public:
        DescriptorAndPipelineInitializer(std::shared_ptr<VulkanContext> vulkan_context);
        void init_descriptor_and_pipeline();
    private:
        std::shared_ptr<VulkanContext> m_vulkan_context;
        bool m_use_texture;

    };
}
}






#endif
