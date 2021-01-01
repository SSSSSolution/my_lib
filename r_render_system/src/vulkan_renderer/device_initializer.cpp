#include "device_initializer.h"
#include "vulkan_helper.h"
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
    check_device_extension_support();
    VulkanHelper::print_support_device_extension(m_ctx);
    find_queue_family_index();

    VulkanHelper::print_physical_devices(m_ctx);
    for (int i = 0; i < m_ctx->m_gpu_queue_family_props.size(); i++)
    {
        VulkanHelper::print_queue_families(m_ctx->m_gpu_queue_family_props[i]);
    }

    init_device();
}

DeviceInitializer::~DeviceInitializer() = default;

void DeviceInitializer::check_device_extension_support()
{
    uint32_t extension_count;
    vkEnumerateDeviceExtensionProperties(m_ctx->m_gpu_list[0], nullptr, &extension_count, nullptr);
    m_ctx->m_support_device_extensions.resize(extension_count);
    vkEnumerateDeviceExtensionProperties(m_ctx->m_gpu_list[0], nullptr, &extension_count, m_ctx->m_support_device_extensions.data());
}

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

    vkGetDeviceQueue(m_ctx->m_device, m_ctx->m_graphics_queue_family_index, 0, &m_ctx->m_graphics_queue);
    vkGetDeviceQueue(m_ctx->m_device, m_ctx->m_present_queue_family_index, 0, &m_ctx->m_present_queue);
}

void DeviceInitializer::find_queue_family_index()
{
    uint32_t gpu_queue_family_count;
    vkGetPhysicalDeviceQueueFamilyProperties(m_ctx->m_gpu_list[0],
            &gpu_queue_family_count, nullptr);
    assert(gpu_queue_family_count >= 1);

    m_ctx->m_gpu_queue_family_props.resize(gpu_queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(m_ctx->m_gpu_list[0],
            &gpu_queue_family_count,
            m_ctx->m_gpu_queue_family_props.data());

    for (int i = 0; i < m_ctx->m_gpu_properties_list.size(); ++i)
    {
        if (m_ctx->m_gpu_queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            m_ctx->m_graphics_queue_family_index = i;

            VkBool32 present_support = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(m_ctx->m_gpu_list[0],
                    i, m_ctx->m_surface, &present_support);
            if (present_support == true)
            {
                m_ctx->m_present_queue_family_index = i;
                break;
            }
        }
    }
    assert(m_ctx->m_graphics_queue_family_index == m_ctx->m_present_queue_family_index);
    printf("select graphics queue family index is %d\n", m_ctx->m_graphics_queue_family_index);
}


}
}
















