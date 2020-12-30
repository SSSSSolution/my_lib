#include "instance_initializer.h"
#include <vector>
#include "vulkan_helper.h"
#include <iostream>

namespace reality
{
namespace r_render_system
{
    static  VkBool32 debug_cb(
            VkDebugUtilsMessageSeverityFlagBitsEXT serverity,
            VkDebugUtilsMessageTypeFlagsEXT message_type,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData)
    {
        // color should be use.
        std::cout << "[validation layer]:"
                  <<"\t message: " <<  pCallbackData->pMessage << std::endl
                  << "\t object count: " << pCallbackData->objectCount <<std::endl;

        return VK_FALSE;
    }

    std::vector<const char *> instance_layers = {
       "VK_LAYER_KHRONOS_validation",

    };
    std::vector<const char *> instance_extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    };

    InstanceInitializer::InstanceInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        printf("vulkan instance init...\n");
        m_ctx = ctx;
        check_extension_support();
        init_instance();
        create_debug_messenger();
    }

    void InstanceInitializer::init_instance()
    {
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

        VkDebugUtilsMessengerCreateInfoEXT debug_info{};
        debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debug_info.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debug_info.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debug_info.pfnUserCallback = debug_cb;
        debug_info.pUserData = nullptr;

        inst_info.pNext = &debug_info;
        auto res = vkCreateInstance(&inst_info, nullptr, &m_ctx->m_instance);
        if (res == VK_ERROR_INCOMPATIBLE_DRIVER)
        {
            printf("Cannot find a compatible Vulkan ICD\n");
        }
        assert(res == VK_SUCCESS);
    }

    void InstanceInitializer::check_extension_support()
    {
        uint32_t extension_count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
        m_ctx->m_support_instance_extensions.resize(extension_count);
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, m_ctx->m_support_instance_extensions.data());
        VulkanHelper::print_support_instance_extension(m_ctx);
    }

    void InstanceInitializer::create_debug_messenger()
    {
        VkDebugUtilsMessengerCreateInfoEXT debug_info{};
        debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debug_info.messageSeverity =
//                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//                VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debug_info.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debug_info.pfnUserCallback = debug_cb;
        debug_info.pUserData = nullptr;

        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_ctx->m_instance, "vkCreateDebugUtilsMessengerEXT");
        auto res = func(m_ctx->m_instance, &debug_info, nullptr, &m_debug_messenger);
        assert(res == VK_SUCCESS);
    }

    InstanceInitializer::~InstanceInitializer()
    {
        vkDestroyInstance(m_ctx->m_instance, nullptr);
    }

}
}
























