#include "physical_device_initializer.h"

namespace reality
{
namespace r_render_system
{

PhysicalDeviceInitializer::PhysicalDeviceInitializer(std::shared_ptr<VulkanContext> vulkan_context)
{
    m_vulkan_context = vulkan_context;

    enumerate_devices();
    init_queue_family_index();
}

PhysicalDeviceInitializer::~PhysicalDeviceInitializer() = default;

void PhysicalDeviceInitializer::enumerate_devices()
{
    uint32_t gpu_count = 0;
    auto res = vkEnumeratePhysicalDevices(m_vulkan_context->m_instance, &gpu_count, nullptr);
    assert(res == VK_SUCCESS && gpu_count >= 1);

    m_vulkan_context->m_gpu_list.resize(gpu_count);
    res = vkEnumeratePhysicalDevices(m_vulkan_context->m_instance, &gpu_count, m_vulkan_context->m_gpu_list.data());
    assert(res == VK_SUCCESS);



    vkGetPhysicalDeviceProperties(m_vulkan_context->m_gpu_list[0],
            &m_vulkan_context->m_gpu_properties);
    vkGetPhysicalDeviceMemoryProperties(m_vulkan_context->m_gpu_list[0],
            &m_vulkan_context->m_gpu_memory_properties);
}

void PhysicalDeviceInitializer::init_queue_family_index()
{
    vkGetPhysicalDeviceQueueFamilyProperties(m_vulkan_context->m_gpu_list[0],
            &m_vulkan_context->m_gpu_queue_family_count, nullptr);
    assert(m_vulkan_context->m_gpu_queue_family_count >= 1);

    m_vulkan_context->m_gpu_queue_family_props.resize(m_vulkan_context->m_gpu_queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(m_vulkan_context->m_gpu_list[0],
            &m_vulkan_context->m_gpu_queue_family_count,
            m_vulkan_context->m_gpu_queue_family_props.data());
}
}
}

