#ifndef REALITY_RENDER_SYSTEM_VULKAN_CONTEXT_H
#define REALITY_RENDER_SYSTEM_VULKAN_CONTEXT_H

#include "r_window.h"

// use xlib surface
#define VK_USE_PLATFORM_XLIB_KHR
#include "vulkan/vulkan.h"
#include "assert.h"

#include <vector>

namespace reality {
namespace r_render_system {

struct VulkanContext {
    std::shared_ptr<RWindow> m_window;

    VkInstance m_instance;

    std::vector<VkPhysicalDevice> m_gpu_list;
    uint32_t m_gpu_queue_family_count;
    std::vector<VkQueueFamilyProperties> m_gpu_queue_family_props;
    VkPhysicalDeviceProperties m_gpu_properties;
    VkPhysicalDeviceMemoryProperties m_gpu_memory_properties;

    uint32_t m_graphics_queue_family_index;
    uint32_t m_present_queue_family_index;

    VkSurfaceKHR m_surface;
    VkFormat m_format;

    VkDevice m_device;

    VkCommandPool m_cmd_pool;
    VkCommandBuffer m_cmd_buf;

    VkQueue m_graphics_queue;
    VkQueue m_present_queue;

    VkSwapchainKHR m_swapchain;

};

}
}












#endif
