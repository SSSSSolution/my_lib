#ifndef REALITY_RENDER_SYSTEM_FRAMEBUFFER_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_FRAMEBUFFER_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system
    {
    class FramebufferInitializer
    {
    public:
        FramebufferInitializer(std::shared_ptr<VulkanContext> ctx);
        void init_framebuffers();
    private:
        std::shared_ptr<VulkanContext> m_ctx;
    };
    }
}









#endif
