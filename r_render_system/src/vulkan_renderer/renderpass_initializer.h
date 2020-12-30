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
    RenderPassInitializer(std::shared_ptr<VulkanContext> vulkan_context);
    void init_renderpass();
private:
    std::shared_ptr<VulkanContext> m_vulkan_context;
    bool m_include_depth;
};


}
}

#endif
