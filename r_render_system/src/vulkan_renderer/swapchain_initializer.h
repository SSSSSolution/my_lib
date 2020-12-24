#ifndef REALITY_RENDER_SYSTEM_SWAPCHAIN_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_SWAPCHAIN_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality {
    namespace r_render_system {
    class SwapchainInitializer
    {
    public:
        SwapchainInitializer(std::shared_ptr<VulkanContext> vulkan_context);

        void init_swapchain();
        void init_swapchain_image();

    private:
        std::shared_ptr<VulkanContext> m_vulkan_context;
    };
    }
}






#endif
