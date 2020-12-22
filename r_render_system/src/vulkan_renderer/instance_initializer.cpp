#include "instance_initializer.h"
#include <vector>

namespace reality
{
namespace r_render_system
{
    std::vector<const char *> instance_layers = {
       "VK_LAYER_KHRONOS_validation",

    };
    std::vector<const char *> instance_extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
    };

    InstanceInitializer::InstanceInitializer(std::shared_ptr<VulkanContext> vulkan_context)
    {
        m_vulkan_context = vulkan_context;

        VkApplicationInfo app_info = {};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pNext = nullptr;
        app_info.pApplicationName = "Reality";
        app_info.applicationVersion = 1;
        app_info.pEngineName = "Reality";
        app_info.engineVersion = 1;
        app_info.apiVersion = VK_MAKE_VERSION(1, 2, 0);

        VkInstanceCreateInfo inst_info = {};
        inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        inst_info.pNext = nullptr;
        inst_info.flags = 0;
        inst_info.pApplicationInfo = &app_info;
        inst_info.enabledExtensionCount = instance_extensions.size();
        inst_info.ppEnabledExtensionNames = instance_extensions.data();
        inst_info.enabledLayerCount = instance_layers.size();
        inst_info.ppEnabledLayerNames = instance_layers.data();

        auto res = vkCreateInstance(&inst_info, nullptr, &m_vulkan_context->m_instance);
        if (res == VK_ERROR_INCOMPATIBLE_DRIVER)
        {
            printf("Cannot find a compatible Vulkan ICD\n");
        }
        else if (res != VK_SUCCESS)
        {
            printf("unknow error : %d\n", res);
        }
    }

    InstanceInitializer::~InstanceInitializer()
    {
    }

}
}
