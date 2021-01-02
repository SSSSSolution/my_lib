#ifndef REALITY_RENDER_SYSTEM_RENDERPASS_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_RENDERPASS_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality {
namespace r_render_system
{
class RenderPassInitializer
{
public:
    RenderPassInitializer(std::shared_ptr<VulkanContext> ctx);
    void init_renderpass();
private:
    std::shared_ptr<VulkanContext> m_ctx;
    bool m_include_depth;
};


}
}

#endif
