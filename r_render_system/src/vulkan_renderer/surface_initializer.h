#ifndef REALITY_RENDER_SYSTEM_SURFACE_INITIALIZER
#define REALITY_RENDER_SYSTEM_SURFACE_INITIALIZER

#include "vulkan_context.h"
#include <memory>

namespace reality {
    namespace r_render_system {
    class SurfaceInitializer
    {
    public:
        SurfaceInitializer(std::shared_ptr<VulkanContext> vulkan_context);

        void init_surface();

    private:
        std::shared_ptr<VulkanContext> m_vulkan_context;
    };
    }
}

#endif
