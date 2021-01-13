#include "vulkan_helper.h"

namespace reality
{
namespace r_render_system
{
    void VulkanHelper::execute_begin_command_buffer(std::shared_ptr<VulkanContext> vulkan_context, int cmd_buf_index)
    {
        VkCommandBufferBeginInfo cmd_begin_info = {};
        cmd_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cmd_begin_info.pNext = nullptr;
        cmd_begin_info.flags = 0;
        cmd_begin_info.pInheritanceInfo = nullptr;

        auto res = vkBeginCommandBuffer(vulkan_context->m_cmd_bufs[cmd_buf_index], &cmd_begin_info);
        assert(res == VK_SUCCESS);
    }

    void VulkanHelper::init_device_queue(std::shared_ptr<VulkanContext> vulkan_context)
    {
        vkGetDeviceQueue(vulkan_context->m_device, vulkan_context->m_graphics_queue_family_index, 0, &vulkan_context->m_graphics_queue);
        if (vulkan_context->m_graphics_queue_family_index == vulkan_context->m_present_queue_family_index)
        {
            vulkan_context->m_present_queue = vulkan_context->m_graphics_queue;
        } else
        {
            vkGetDeviceQueue(vulkan_context->m_device, vulkan_context->m_present_queue_family_index, 0, &vulkan_context->m_present_queue);
        }
    }

    bool VulkanHelper::memory_type_from_properties(std::shared_ptr<VulkanContext> vulkan_context,
                                            uint32_t typeBits, VkFlags requirements_mask,
                                            uint32_t *typeIndex)
    {
        for (uint32_t i = 0; i < vulkan_context->m_gpu_memory_properties_list[0].memoryTypeCount; i++)
        {
            if ((typeBits & 1) == 1) {
                if ((vulkan_context->m_gpu_memory_properties_list[0].memoryTypes[i].propertyFlags &
                     requirements_mask) == requirements_mask)
                {
                    *typeIndex = i;
                    return true;
                }
            }
            typeBits >>= 1;
        }

        return false;
    }

    void VulkanHelper::print_support_instance_extension(std::shared_ptr<VulkanContext> ctx)
    {
        for (uint32_t i = 0; i < ctx->m_support_instance_extensions.size(); i++)
        {
            auto props = ctx->m_support_instance_extensions[i];
            uint32_t version_major = VK_VERSION_MAJOR(props.specVersion);
            uint32_t version_minor = VK_VERSION_MINOR(props.specVersion);
            uint32_t version_patch = VK_VERSION_PATCH(props.specVersion);
            printf("instance extension props:[%s]<%u.%u.%u>\n", props.extensionName,
                   version_major, version_minor, version_patch);
        }

    }

    void VulkanHelper::print_support_device_extension(std::shared_ptr<VulkanContext> ctx)
    {
        for (uint32_t i = 0; i < ctx->m_support_device_extensions.size(); i++)
        {
            auto props = ctx->m_support_device_extensions[i];
            uint32_t version_major = VK_VERSION_MAJOR(props.specVersion);
            uint32_t version_minor = VK_VERSION_MINOR(props.specVersion);
            uint32_t version_patch = VK_VERSION_PATCH(props.specVersion);
            printf("device extension props:[%s]<%u.%u.%u>\n", props.extensionName,
                   version_major, version_minor, version_patch);
        }
    }
    void VulkanHelper::print_physical_devices(std::shared_ptr<VulkanContext> ctx)
    {
        printf("gpu:\n");
        for (uint32_t i = 0; i < ctx->m_gpu_properties_list.size(); i++)
        {
            printf("    gpu: %s\n", ctx->m_gpu_properties_list[i].deviceName);
        }
    }


    /*VK_QUEUE_GRAPHICS_BIT = 0x00000001,
    VK_QUEUE_COMPUTE_BIT = 0x00000002,
    VK_QUEUE_TRANSFER_BIT = 0x00000004,
    VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
    VK_QUEUE_PROTECTED_BIT = 0x00000010,
    */
    void VulkanHelper::print_queue_families(VkQueueFamilyProperties props)
    {
        printf("queue families:\n");
        if (props.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            printf("    graphics queue\n");
        }
        if (props.queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            printf("    compute queue\n");
        }
        if (props.queueFlags & VK_QUEUE_TRANSFER_BIT)
        {
            printf("    transfer queue\n");
        }
        if (props.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
        {
            printf("    sparse binding queue\n");
        }
        if (props.queueFlags & VK_QUEUE_PROTECTED_BIT)
        {
            printf("    protected queue\n");
        }
    }

    void VulkanHelper::create_buffer(std::shared_ptr<VulkanContext> ctx, VkDeviceSize size,
                                     VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                                     VkBuffer &buffer, VkDeviceMemory &buffer_memory)
    {
        VkBufferCreateInfo buffer_info = {};
        buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_info.size = size;
        buffer_info.usage = usage;
        buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        auto res = vkCreateBuffer(ctx->m_device, &buffer_info, nullptr, &buffer);
        assert(res == VK_SUCCESS);

        VkMemoryRequirements mem_reqs;
        vkGetBufferMemoryRequirements(ctx->m_device, buffer, &mem_reqs);

        VkMemoryAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = mem_reqs.size;
        auto pass = memory_type_from_properties(ctx, mem_reqs.memoryTypeBits,
                                                properties, &alloc_info.memoryTypeIndex);

        res = vkAllocateMemory(ctx->m_device, &alloc_info, nullptr, &buffer_memory);
        assert(res == VK_SUCCESS);

        vkBindBufferMemory(ctx->m_device, buffer, buffer_memory, 0);
    }

    void VulkanHelper::copy_buffer(std::shared_ptr<VulkanContext> ctx,
                                   VkBuffer src_buf, VkBuffer dst_buf, VkDeviceSize size)
    {
        VkCommandBufferAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.commandPool = ctx->m_cmd_pool;
        alloc_info.commandBufferCount = 1;

        VkCommandBuffer cmd_buf;
        auto res = vkAllocateCommandBuffers(ctx->m_device, &alloc_info, &cmd_buf);
        assert(res == VK_SUCCESS);

        VkCommandBufferBeginInfo begin_info = {};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(cmd_buf, &begin_info);

        VkBufferCopy copy_region = {};
        copy_region.srcOffset = 0;
        copy_region.dstOffset = 0;
        copy_region.size = size;
        vkCmdCopyBuffer(cmd_buf, src_buf, dst_buf, 1, &copy_region);

        vkEndCommandBuffer(cmd_buf);

        VkSubmitInfo submit_info = {};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &cmd_buf;

        vkQueueSubmit(ctx->m_graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
        vkQueueWaitIdle(ctx->m_graphics_queue);
    }

    VkImageView VulkanHelper::create_image_view(std::shared_ptr<VulkanContext> ctx,
                                         VkImage image, VkFormat format,
                                         VkImageAspectFlags aspect_flag, uint32_t mip_levels)
    {
        VkImageViewCreateInfo view_info = {};
        view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        view_info.image = image;
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.format = format;
        view_info.subresourceRange.aspectMask = aspect_flag;
        view_info.subresourceRange.baseMipLevel = 0;
        view_info.subresourceRange.levelCount = mip_levels;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount = 1;

        VkImageView image_view;
        auto res = vkCreateImageView(ctx->m_device, &view_info, nullptr, &image_view);
        assert(res == VK_SUCCESS);

        return image_view;
    }

    void VulkanHelper::transition_image_layout(std::shared_ptr<VulkanContext> ctx,
                                               VkImage image, VkFormat format,
                                               VkImageLayout old_layout, VkImageLayout new_layout,
                                               uint32_t mip_levels)
    {
        VkCommandBuffer cmd_buf = begin_single_time_commands(ctx);

        VkImageMemoryBarrier barrier = {};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = old_layout;
        barrier.newLayout = new_layout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = mip_levels;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags src_stage_flags;
        VkPipelineStageFlags dst_stage_flags;
        if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
                    barrier.srcAccessMask = 0;
                    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

                    src_stage_flags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                    dst_stage_flags = VK_PIPELINE_STAGE_TRANSFER_BIT;
                } else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
                    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

                    src_stage_flags = VK_PIPELINE_STAGE_TRANSFER_BIT;
                    dst_stage_flags = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
                }
        else {
            printf("transition image layout error\n");
            exit(-1);
        }

        vkCmdPipelineBarrier(cmd_buf, src_stage_flags, dst_stage_flags,
                             0,
                             0, nullptr,
                             0, nullptr,
                             1, &barrier);

        end_single_time_commands(ctx, cmd_buf);
    }

    VkCommandBuffer VulkanHelper::begin_single_time_commands(std::shared_ptr<VulkanContext> ctx)
    {
        VkCommandBufferAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandPool = ctx->m_cmd_pool;
        alloc_info.commandBufferCount = 1;

        VkCommandBuffer cmd_buf;
        vkAllocateCommandBuffers(ctx->m_device, &alloc_info, &cmd_buf);

        VkCommandBufferBeginInfo begin_info = {};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(cmd_buf, &begin_info);

        return cmd_buf;
    }

    void VulkanHelper::end_single_time_commands(std::shared_ptr<VulkanContext> ctx, VkCommandBuffer cmd_buf)
    {
        vkEndCommandBuffer(cmd_buf);

        VkSubmitInfo submit_info = {};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &cmd_buf;

        vkQueueSubmit(ctx->m_graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
        vkQueueWaitIdle(ctx->m_graphics_queue);

        vkFreeCommandBuffers(ctx->m_device, ctx->m_cmd_pool, 1, &cmd_buf);
    }

    void VulkanHelper::copy_buffer_to_image(std::shared_ptr<VulkanContext> ctx, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
    {
        VkCommandBuffer cmd_buf = begin_single_time_commands(ctx);

        VkBufferImageCopy region {};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageOffset = {0, 0, 0};
        region.imageExtent = {
            width,
            height,
            1
        };

        vkCmdCopyBufferToImage(cmd_buf, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        end_single_time_commands(ctx, cmd_buf);
    }

    VkFormat VulkanHelper::find_supported_format(std::shared_ptr<VulkanContext> ctx,
                                             const std::vector<VkFormat> &candidates,
                                             VkImageTiling tiling, VkFormatFeatureFlags features)
    {
        for (auto format : candidates)
        {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(ctx->m_gpu_list[0], format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR &&
                (props.linearTilingFeatures & features) == features)
            {
                return format;
            } else if (tiling == VK_IMAGE_TILING_OPTIMAL &&
                       (props.optimalTilingFeatures & features) == features)
            {
                return format;
            }
        }
        printf("can't find support format\n");
        exit(-1);
    }

    VkFormat VulkanHelper::find_depth_format(std::shared_ptr<VulkanContext> ctx)
    {
        return find_supported_format(ctx,
                                     {VK_FORMAT_D32_SFLOAT,
                                      VK_FORMAT_D32_SFLOAT_S8_UINT,
                                      VK_FORMAT_D24_UNORM_S8_UINT},
                                     VK_IMAGE_TILING_OPTIMAL,
                                     VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    }

    void VulkanHelper::create_image(std::shared_ptr<VulkanContext> ctx,
                                    uint32_t width, uint32_t height, uint32_t mip_levels,
                                    VkSampleCountFlagBits num_samples,
                                    VkFormat format, VkImageTiling tiling,
                                    VkImageUsageFlags usage, VkMemoryPropertyFlags prop_flags, VkImage &image, VkDeviceMemory &image_mem)
    {
        VkImageCreateInfo image_info = {};
        image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_info.imageType = VK_IMAGE_TYPE_2D;
        image_info.extent.width = width;
        image_info.extent.height = height;
        image_info.extent.depth = 1;
        image_info.mipLevels = mip_levels;
        image_info.arrayLayers = 1;
        image_info.format = format;
        image_info.tiling = tiling;
        image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        image_info.usage = usage;
        image_info.samples = num_samples;
        image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        auto res = vkCreateImage(ctx->m_device, &image_info, nullptr, &image);
        assert(res == VK_SUCCESS);

        VkMemoryRequirements mem_reqs;
        vkGetImageMemoryRequirements(ctx->m_device, image, &mem_reqs);

        VkMemoryAllocateInfo alloc_info {};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = mem_reqs.size;

        auto pass = memory_type_from_properties(ctx, mem_reqs.memoryTypeBits, prop_flags, &alloc_info.memoryTypeIndex);
        assert(pass);

        res = vkAllocateMemory(ctx->m_device, &alloc_info, nullptr, &image_mem);
        assert(res == VK_SUCCESS);

        vkBindImageMemory(ctx->m_device, image, image_mem, 0);
    }

    void VulkanHelper::generate_mip_maps(std::shared_ptr<VulkanContext> ctx,
                                          VkImage image, VkFormat image_format,
                                          int32_t tex_width, uint32_t tex_height,
                                          uint32_t mip_levels)
    {
        printf("generate mip mapsa...\n");
        // check if image format supports linear blitting
        VkFormatProperties format_props;
        vkGetPhysicalDeviceFormatProperties(ctx->m_gpu_list[0], image_format, &format_props);
        assert(format_props.optimalTilingFeatures &
               VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT);

        VkCommandBuffer cmd_buf = begin_single_time_commands(ctx);

       VkImageMemoryBarrier barrier {};
       barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
       barrier.image = image;
       barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
       barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
       barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
       barrier.subresourceRange.baseArrayLayer = 0;
       barrier.subresourceRange.layerCount = 1;
       barrier.subresourceRange.levelCount = 1;

       int32_t mip_width = tex_width;
       int32_t mip_height = tex_height;
       for (uint32_t i = 1; i < mip_levels; i++)
       {
           barrier.subresourceRange.baseMipLevel = i - 1;
           barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
           barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
           barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
           barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

           vkCmdPipelineBarrier(cmd_buf,
                                VK_PIPELINE_STAGE_TRANSFER_BIT,
                                VK_PIPELINE_STAGE_TRANSFER_BIT,
                                0, 0, nullptr,
                                0, nullptr,
                                1, &barrier);

           VkImageBlit blit = {};
           blit.srcOffsets[0] = {0, 0, 0};
           blit.srcOffsets[1] = {mip_width, mip_height, 1};
           blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
           blit.srcSubresource.mipLevel = i - 1;
           blit.srcSubresource.baseArrayLayer = 0;
           blit.srcSubresource.layerCount = 1;
           blit.dstOffsets[0] = {0, 0, 0};
           blit.dstOffsets[1] = {mip_width > 1 ? mip_width / 2 : 1,
                                 mip_height > 1 ? mip_height / 2 : 1, 1};
           blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
           blit.dstSubresource.mipLevel = i;
           blit.dstSubresource.baseArrayLayer = 0;
           blit.dstSubresource.layerCount = 1;

           vkCmdBlitImage(cmd_buf,
                          image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                          image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                          1, &blit, VK_FILTER_LINEAR);

           barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
           barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
           barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
           barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

           vkCmdPipelineBarrier(cmd_buf,
               VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
               0, nullptr,
               0, nullptr,
               1, &barrier);

           if (mip_width > 1) mip_width /= 2;
           if (mip_height > 1) mip_height /= 2;
       }

       barrier.subresourceRange.baseMipLevel = mip_levels -1;
       barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
       barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
       barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
       barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

       vkCmdPipelineBarrier(cmd_buf,
                            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
                            0, nullptr,
                            0, nullptr,
                            1, &barrier);

       end_single_time_commands(ctx, cmd_buf);
    }

    VkSampleCountFlagBits VulkanHelper::get_max_usable_sample_count(std::shared_ptr<VulkanContext> ctx)
    {
        VkPhysicalDeviceProperties physical_device_props;
        vkGetPhysicalDeviceProperties(ctx->m_gpu_list[0], &physical_device_props);

        VkSampleCountFlags counts = physical_device_props.limits.framebufferColorSampleCounts &
                                    physical_device_props.limits.framebufferDepthSampleCounts;
        if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
        if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
        if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
        if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
        if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
        if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

        return VK_SAMPLE_COUNT_1_BIT;
   }
}
}



















