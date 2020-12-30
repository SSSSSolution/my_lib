#ifndef REALITY_RENDER_SYSTEM_PHYSICAL_DEVICE_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_PHYSICAL_DEVICE_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system
    {
    class PhysicalDeviceInitializer {
    public:
        PhysicalDeviceInitializer(std::shared_ptr<VulkanContext> ctx);
        ~PhysicalDeviceInitializer();

    private:
        void enumerate_devices();
        void init_queue_family_index();

        std::shared_ptr<VulkanContext> m_ctx;
    };
    }
}
#endif
