#ifndef REALITY_RENDER_SYSTEM_DEVICE_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_DEVICE_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system
    {
    class DeviceInitializer {
    public:
        DeviceInitializer(std::shared_ptr<VulkanContext> ctx);
        ~DeviceInitializer();

    private:
        void init_device();

        std::shared_ptr<VulkanContext> m_ctx;
    };
    }
}
#endif
