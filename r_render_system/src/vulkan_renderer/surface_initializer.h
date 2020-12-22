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
        void choice_graphic_and_present_queue_family();
        void choice_format();

    private:
        std::shared_ptr<VulkanContext> m_vulkan_context;
    };
    }
}

#endif
