#include "surface_initializer.h"

#define PREFERRED_SURFACE_FORMAT VK_FORMAT_B8G8R8A8_SRGB

namespace reality
{
namespace r_render_system
{
    SurfaceInitializer::SurfaceInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;
        init_surface();
    }

    void SurfaceInitializer::init_surface()
    {
        VkXlibSurfaceCreateInfoKHR surface_info = {};
        surface_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        surface_info.pNext = nullptr;
        surface_info.dpy = m_vulkan_context->m_window->get_window_info()->display;
        surface_info.window = m_vulkan_context->m_window->get_window_info()->window;

        auto res = vkCreateXlibSurfaceKHR(m_vulkan_context->m_instance,
                                     &surface_info, nullptr, &m_vulkan_context->m_surface);
        assert(res == VK_SUCCESS);
    }

}
}
