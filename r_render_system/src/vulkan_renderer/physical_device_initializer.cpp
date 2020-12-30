#include "physical_device_initializer.h"
#include "vulkan_helper.h"
namespace reality
{
namespace r_render_system
{

PhysicalDeviceInitializer::PhysicalDeviceInitializer(std::shared_ptr<VulkanContext> ctx)
{
    printf("gpu init...\n");
    m_ctx = ctx;

    enumerate_devices();
    init_queue_family_index();
    VulkanHelper::print_physical_devices(m_ctx);
    for (int i = 0; i < m_ctx->m_gpu_queue_family_props.size(); i++)
    {
        VulkanHelper::print_queue_families(m_ctx->m_gpu_queue_family_props[i]);
    }
}

PhysicalDeviceInitializer::~PhysicalDeviceInitializer() = default;

void PhysicalDeviceInitializer::enumerate_devices()
{
    uint32_t gpu_count = 0;
    auto res = vkEnumeratePhysicalDevices(m_ctx->m_instance, &gpu_count, nullptr);
    assert(res == VK_SUCCESS && gpu_count >= 1);

    m_ctx->m_gpu_list.resize(gpu_count);
    res = vkEnumeratePhysicalDevices(m_ctx->m_instance, &gpu_count, m_ctx->m_gpu_list.data());
    assert(res == VK_SUCCESS);

    m_ctx->m_gpu_properties_list.resize(gpu_count);
    m_ctx->m_gpu_memory_properties_list.resize(gpu_count);
    for (int i = 0; i < m_ctx->m_gpu_list.size(); i++)
    {
        vkGetPhysicalDeviceProperties(m_ctx->m_gpu_list[i],
                &m_ctx->m_gpu_properties_list[i]);
        vkGetPhysicalDeviceMemoryProperties(m_ctx->m_gpu_list[i],
                &m_ctx->m_gpu_memory_properties_list[i]);
    }
}

void PhysicalDeviceInitializer::init_queue_family_index()
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
            break;
        }
    }
    printf("select graphics queue family index is %d\n", m_ctx->m_graphics_queue_family_index);
}
}
}

