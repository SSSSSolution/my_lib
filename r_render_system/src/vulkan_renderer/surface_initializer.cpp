#include "surface_initializer.h"

#define PREFERRED_SURFACE_FORMAT VK_FORMAT_B8G8R8A8_SRGB

namespace reality
{
namespace r_render_system
{
    SurfaceInitializer::SurfaceInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        init_surface();
    }

    void SurfaceInitializer::init_surface()
    {
        VkXlibSurfaceCreateInfoKHR surface_info = {};
        surface_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        surface_info.pNext = nullptr;
        surface_info.dpy = m_ctx->m_window->get_window_info()->display;
        surface_info.window = m_ctx->m_window->get_window_info()->window;

        auto res = vkCreateXlibSurfaceKHR(m_ctx->m_instance,
                                     &surface_info, nullptr, &m_ctx->m_surface);
        assert(res == VK_SUCCESS);
    }


}
}
