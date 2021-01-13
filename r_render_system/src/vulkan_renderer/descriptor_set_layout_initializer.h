#ifndef REALITY_RENDER_SYSTEM_DESCRIPTOR_SET_LAYOUT_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_DESCRIPTOR_SET_LAYOUT_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system
    {
    class DescriptorSetLayoutInitializer
    {
    public:
        DescriptorSetLayoutInitializer(std::shared_ptr<VulkanContext> ctx);
        void init_descriptor_set_layout();
    private:
        std::shared_ptr<VulkanContext> m_ctx;
    };
    }
}









#endif
