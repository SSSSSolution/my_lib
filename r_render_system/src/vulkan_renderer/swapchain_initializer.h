#ifndef REALITY_RENDER_SYSTEM_SWAPCHAIN_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_SWAPCHAIN_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality {
    namespace r_render_system {
    class SwapchainInitializer
    {
    public:
        SwapchainInitializer(std::shared_ptr<VulkanContext> ctx);

        void get_surface_support();
        void choose_swapchain_fromat();
        void choose_swapchain_present_mode();
        void choose_swapchain_extent();
        void init_swapchain();
        void get_swapchain_images();
        void create_image_view();

    private:
        std::shared_ptr<VulkanContext> m_ctx;
    };
    }
}






#endif
