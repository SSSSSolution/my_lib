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


}
}

