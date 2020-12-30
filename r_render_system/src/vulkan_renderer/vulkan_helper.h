#ifndef REALITY_RENDER_SYSTEM_VULKAN_HELPER_H
#define REALITY_RENDER_SYSTEM_VULKAN_HELPER_H

#include "vulkan_context.h"
#include <memory>

namespace  reality {
    namespace r_render_system
    {
    class VulkanHelper
    {
    public:
        static void execute_begin_command_buffer(std::shared_ptr<VulkanContext> vulkan_context, int);
        static void init_device_queue(std::shared_ptr<VulkanContext> vulkan_context);
        static bool memory_type_from_properties(std::shared_ptr<VulkanContext> vulkan_context,
                                                uint32_t typeBits, VkFlags requirements_mask,
                                                uint32_t *typeIndex);
        /* instance */
        static void print_support_instance_extension(std::shared_ptr<VulkanContext> ctx);

        /* physical device */
        static void print_physical_devices(std::shared_ptr<VulkanContext> ctx);
        static void print_queue_families(VkQueueFamilyProperties props);
    private:
    };
    }
}



#endif
