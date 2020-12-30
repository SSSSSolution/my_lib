#ifndef REALITY_RENDER_SYSTEM_DESCRIPTOR_SET_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_DESCRIPTOR_SET_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
namespace r_render_system
{
    class DescriptorSetInitializer
    {
    public:
        DescriptorSetInitializer(std::shared_ptr<VulkanContext> ctx);
        void init_descriptor_set();
    private:
        std::shared_ptr<VulkanContext> m_ctx;
        bool m_use_texture;

    };
}
}


#endif
