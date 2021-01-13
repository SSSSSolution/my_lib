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
        /* device */
        static void print_support_device_extension(std::shared_ptr<VulkanContext> ctx);

        /* physical device */
        static void print_physical_devices(std::shared_ptr<VulkanContext> ctx);
        static void print_queue_families(VkQueueFamilyProperties props);

        static void create_buffer(std::shared_ptr<VulkanContext> ctx, VkDeviceSize size,
                                  VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                                  VkBuffer &buffer, VkDeviceMemory &buffer_memory);
        static void copy_buffer(std::shared_ptr<VulkanContext> ctx,
                                VkBuffer src_buf, VkBuffer dst_buf, VkDeviceSize size);
        static VkImageView create_image_view(std::shared_ptr<VulkanContext> ctx,
                                      VkImage image, VkFormat format,
                                      VkImageAspectFlags aspect_flag, uint32_t mip_levels);
        static void transition_image_layout(std::shared_ptr<VulkanContext> ctx, VkImage image, VkFormat format,
                                            VkImageLayout old_layout, VkImageLayout new_layout, uint32_t mip_levels);

        static VkCommandBuffer begin_single_time_commands(std::shared_ptr<VulkanContext> ctx);
        static void end_single_time_commands(std::shared_ptr<VulkanContext> ctx,
                                             VkCommandBuffer cmd_buf);
        static void copy_buffer_to_image(std::shared_ptr<VulkanContext> ctx,
                                         VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        static VkFormat find_supported_format(std::shared_ptr<VulkanContext> ctx,
                                          const std::vector<VkFormat>& candidates,
                                          VkImageTiling tiling, VkFormatFeatureFlags features);
        static VkFormat find_depth_format(std::shared_ptr<VulkanContext> ctx);

        static void create_image(std::shared_ptr<VulkanContext> ctx,
                                 uint32_t width, uint32_t height, uint32_t mip_levels,
                                 VkSampleCountFlagBits num_samples,
                                 VkFormat format, VkImageTiling tiling,
                                 VkImageUsageFlags usage,
                                 VkMemoryPropertyFlags prop_flags,
                                 VkImage &image, VkDeviceMemory &image_mem);

        static void generate_mip_maps(std::shared_ptr<VulkanContext> ctx,
                                      VkImage image, VkFormat image_format,
                                      int32_t tex_width, uint32_t tex_height,
                                      uint32_t mip_levels);

        static VkSampleCountFlagBits get_max_usable_sample_count(std::shared_ptr<VulkanContext> ctx);
    private:
    };
    }
}



#endif
