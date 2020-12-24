#ifndef REALITY_RENDER_SYSTEM_DEPTH_BUFFER_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_DEPTH_BUFFER_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality {
namespace r_render_system
{
    class DepthBufferInitializer
    {
    public:
        DepthBufferInitializer(std::shared_ptr<VulkanContext>);

    private:
        void init_depth_buffer();
        std::shared_ptr<VulkanContext> m_vulkan_context;
    };
}
}









#endif
