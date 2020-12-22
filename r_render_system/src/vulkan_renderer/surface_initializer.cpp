#include "surface_initializer.h"

#define PREFERRED_SURFACE_FORMAT VK_FORMAT_B8G8R8A8_UNORM

namespace reality
{
namespace r_render_system
{
    SurfaceInitializer::SurfaceInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;
        init_surface();
        choice_graphic_and_present_queue_family();
        choice_format();
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

    void SurfaceInitializer::choice_graphic_and_present_queue_family()
    {
        // Iterate over each queue to learn whether it supports presenting:
        VkBool32 *pSupportsPresent = (VkBool32 *)malloc(m_vulkan_context->m_gpu_queue_family_count * sizeof(VkBool32));
        for (uint32_t i = 0; i < m_vulkan_context->m_gpu_queue_family_count; ++i)
        {
            vkGetPhysicalDeviceSurfaceSupportKHR(m_vulkan_context->m_gpu_list[0], i, m_vulkan_context->m_surface,
                    &pSupportsPresent[i]);
        }

        // Search for a graphics and a present queue in the array of queue
        // families, try to find one that supports both
        m_vulkan_context->m_graphics_queue_family_index = UINT32_MAX;
        m_vulkan_context->m_present_queue_family_index = UINT32_MAX;
        for (uint32_t i = 0; i < m_vulkan_context->m_gpu_queue_family_count; ++i)
        {
            if ((m_vulkan_context->m_gpu_queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
            {
                if (m_vulkan_context->m_graphics_queue_family_index == UINT32_MAX)
                {
                    m_vulkan_context->m_graphics_queue_family_index = i;
                }

                if (pSupportsPresent[i] == VK_TRUE) {
                    m_vulkan_context->m_graphics_queue_family_index = i;
                    m_vulkan_context->m_present_queue_family_index = i;
                    break;
                }
            }
        }

        // Generate error if could not find queues support graphics and present
        if (m_vulkan_context->m_graphics_queue_family_index == UINT32_MAX ||
            m_vulkan_context->m_present_queue_family_index == UINT32_MAX)
        {
            printf("Could not find a queue for both graphics and present\n");
            exit(-1);
        }
    }

    void SurfaceInitializer::choice_format()
    {
        // Get the list of VkFormat that we supported:
        uint32_t format_count;
        auto res = vkGetPhysicalDeviceSurfaceFormatsKHR(m_vulkan_context->m_gpu_list[0],
                m_vulkan_context->m_surface, &format_count, nullptr);
        std::vector<VkSurfaceFormatKHR> surface_formats;
        surface_formats.resize(format_count);
        res = vkGetPhysicalDeviceSurfaceFormatsKHR(m_vulkan_context->m_gpu_list[0],
                m_vulkan_context->m_surface, &format_count, surface_formats.data());
        assert(res == VK_SUCCESS);

        // If the device supports our preferred surface format, use it.
        // Otherwise, use whatever the device's first reported surface format is.
        assert(format_count >= 1);
        m_vulkan_context->m_format = surface_formats[0].format;
        for (size_t i = 0; i < format_count; ++i)
        {
            if (surface_formats[i].format == PREFERRED_SURFACE_FORMAT)
            {
                m_vulkan_context->m_format = PREFERRED_SURFACE_FORMAT;
                break;
            }
        }
    }

}
}
