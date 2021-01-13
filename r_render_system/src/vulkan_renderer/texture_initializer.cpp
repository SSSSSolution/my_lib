#include "texture_initializer.h"
#include "vulkan_helper.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string.h>
#include <iostream>

namespace reality
{
    namespace r_render_system
    {
    TextureInitializer::TextureInitializer(std::shared_ptr<VulkanContext> ctx)
    {
        m_ctx = ctx;
        printf("texture init...\n");
        create_texture_image();
        create_texture_view();
        create_texture_sampler();
    }

    TextureInitializer::~TextureInitializer()
    {
        vkDestroyImageView(m_ctx->m_device, m_ctx->m_texture_image_view, nullptr);
        vkDestroyImage(m_ctx->m_device, m_ctx->m_texture_image, nullptr);
        vkFreeMemory(m_ctx->m_device, m_ctx->m_texture_image_mem, nullptr);


    }

    void TextureInitializer::create_texture_image()
    {
        int width, height, channels;
        stbi_uc * pixels = stbi_load("/home/reality/data/modules/viking_room/texture.png", &width,
                                     &height, &channels, STBI_rgb_alpha);
        VkDeviceSize image_size = width * height * 4;
        assert(pixels != nullptr);
        m_mip_levels = std::floor(std::log2(std::max(width, height))) + 1;

        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;

        VulkanHelper::create_buffer(m_ctx, image_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                    staging_buffer, staging_buffer_memory);
        void *data;
        vkMapMemory(m_ctx->m_device, staging_buffer_memory, 0, image_size, 0, &data);
        memcpy(data, pixels, static_cast<size_t>(image_size));
        vkUnmapMemory(m_ctx->m_device, staging_buffer_memory);

        stbi_image_free(pixels);

        VkImageCreateInfo image_info = {};
        image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_info.imageType = VK_IMAGE_TYPE_2D;
        image_info.extent.width = width;
        image_info.extent.height = height;
        image_info.extent.depth = 1;
        image_info.mipLevels = m_mip_levels;
        image_info.arrayLayers = 1;
        image_info.format = VK_FORMAT_R8G8B8A8_SRGB;
        image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
        image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        image_info.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                           VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                           VK_IMAGE_USAGE_SAMPLED_BIT;
        image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        image_info.samples=VK_SAMPLE_COUNT_1_BIT;
        image_info.flags = 0;

        auto res = vkCreateImage(m_ctx->m_device, &image_info, nullptr, &m_ctx->m_texture_image);
        assert(res == VK_SUCCESS);

        VkMemoryRequirements mem_reqs;
        vkGetImageMemoryRequirements(m_ctx->m_device, m_ctx->m_texture_image,
                                     &mem_reqs);

        VkMemoryAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = mem_reqs.size;
//        alloc_info.memoryTypeIndex = VulkanHelper::
        bool pass = VulkanHelper::memory_type_from_properties(m_ctx, mem_reqs.memoryTypeBits,
                                                  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                                  &alloc_info.memoryTypeIndex);
        assert(pass);

        res = vkAllocateMemory(m_ctx->m_device, &alloc_info, nullptr, &m_ctx->m_texture_image_mem);
        assert(res == VK_SUCCESS);
        vkBindImageMemory(m_ctx->m_device, m_ctx->m_texture_image, m_ctx->m_texture_image_mem, 0);

        VulkanHelper::transition_image_layout(m_ctx, m_ctx->m_texture_image,
                                              VK_FORMAT_R8G8B8A8_SRGB,
                                              VK_IMAGE_LAYOUT_UNDEFINED,
                                              VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_mip_levels);

        VulkanHelper::copy_buffer_to_image(m_ctx, staging_buffer, m_ctx->m_texture_image, width, height);

//        VulkanHelper::transition_image_layout(m_ctx, m_ctx->m_texture_image, VK_FORMAT_R8G8B8A8_SRGB,
//                                              VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
//                                              VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, m_mip_levels);

        VulkanHelper::generate_mip_maps(m_ctx, m_ctx->m_texture_image, VK_FORMAT_R8G8B8A8_SRGB, width, height, m_mip_levels);
    }

    void TextureInitializer::create_texture_view()
    {

        m_ctx->m_texture_image_view =
            VulkanHelper::create_image_view(m_ctx, m_ctx->m_texture_image,
                                            VK_FORMAT_R8G8B8A8_SRGB,
                                            VK_IMAGE_ASPECT_COLOR_BIT, m_mip_levels);



    }

    void TextureInitializer::create_texture_sampler()
    {
        VkSamplerCreateInfo sampler_info = {};
        sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        sampler_info.magFilter = VK_FILTER_LINEAR;
        sampler_info.minFilter = VK_FILTER_LINEAR;
        sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        sampler_info.anisotropyEnable = VK_TRUE;
        sampler_info.maxAnisotropy = m_ctx->m_gpu_properties_list[0].limits.maxSamplerAnisotropy;
        std::cout << "max anisotropy: " << sampler_info.maxAnisotropy << std::endl;
        sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        sampler_info.unnormalizedCoordinates = VK_FALSE;
        sampler_info.compareEnable = VK_FALSE;
        sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
        sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        sampler_info.mipLodBias = 0.0f;
        sampler_info.minLod = 0.0f;
        sampler_info.maxLod = m_mip_levels;

        auto res = vkCreateSampler(m_ctx->m_device, &sampler_info, nullptr, &m_ctx->m_texture_sampler);
        assert(res == VK_SUCCESS);
    }
    }
}














