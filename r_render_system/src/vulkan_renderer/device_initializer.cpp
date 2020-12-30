#include "device_initializer.h"

namespace reality
{
namespace r_render_system
{

std::vector<const char *> device_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};

DeviceInitializer::DeviceInitializer(std::shared_ptr<VulkanContext> ctx)
{
    printf("vk deavice init...\n");
    m_ctx = ctx;
    init_device();
}

DeviceInitializer::~DeviceInitializer() = default;

void DeviceInitializer::init_device()
{
    VkDeviceQueueCreateInfo queue_info = {};

    float queue_priorities[1] = {0.0};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueCount = 1;
    queue_info.pNext = nullptr;
    queue_info.pQueuePriorities = queue_priorities;
    queue_info.queueFamilyIndex = m_ctx->m_graphics_queue_family_index;

    VkPhysicalDeviceFeatures device_features {};

    VkDeviceCreateInfo device_info = {};
    device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.pNext = nullptr;
    device_info.queueCreateInfoCount = 1;
    device_info.pQueueCreateInfos = &queue_info;
    device_info.enabledExtensionCount = device_extensions.size();
    device_info.ppEnabledExtensionNames = device_extensions.data();
    device_info.pEnabledFeatures = &device_features;

    auto res = vkCreateDevice(m_ctx->m_gpu_list[0], &device_info, nullptr, &m_ctx->m_device);
    assert(res == VK_SUCCESS);

}

}
}
















