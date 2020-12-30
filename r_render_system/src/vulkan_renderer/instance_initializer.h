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
    InstanceInitializer(std::shared_ptr<VulkanContext> ctx);
    void init_instance();
    void create_debug_messenger();
    void check_extension_support();
    ~InstanceInitializer();

private:
    std::shared_ptr<VulkanContext> m_ctx;
    VkDebugUtilsMessengerEXT m_debug_messenger;
};

}
}


#endif
