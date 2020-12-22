#include "swapchain_initializer.h"

#define PREFERRED_SURFACE_FORMAT VK_FORMAT_B8G8R8A8_UNORM

namespace reality
{
namespace r_render_system
{
    SwapchainInitializer::SwapchainInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;
        init_swapchain();
    }

    void SwapchainInitializer::init_swapchain()
    {

    }

}
}




















