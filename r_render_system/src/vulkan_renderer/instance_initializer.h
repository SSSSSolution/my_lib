#ifndef REALITY_RENDER_SYSTEM_INSTANCE_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_INSTANCE_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
namespace r_render_system
{

class InstanceInitializer
{
public:
    InstanceInitializer(std::shared_ptr<VulkanContext> vulkan_context);
    ~InstanceInitializer();

private:
    std::shared_ptr<VulkanContext> m_vulkan_context;
};

}
}


#endif
