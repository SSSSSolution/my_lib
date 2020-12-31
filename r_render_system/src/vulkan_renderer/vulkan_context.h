#ifndef REALITY_RENDER_SYSTEM_VULKAN_CONTEXT_H
#define REALITY_RENDER_SYSTEM_VULKAN_CONTEXT_H

#include "r_window.h"
#include "glm.hpp"

// use xlib surface
#define VK_USE_PLATFORM_XLIB_KHR
#include "vulkan/vulkan.h"
#include "assert.h"

#include <vector>

namespace reality {
namespace r_render_system {

struct SwapChainBuffer {
    VkImage image;
    VkImageView view;
};

struct Depth {
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkImage image;
    VkDeviceMemory mem;
    VkImageView view;
};

struct UniformData {
    VkBuffer buf;
    VkDeviceMemory mem;
    VkDescriptorBufferInfo buffer_info;
};

struct VertexBuffer {
    VkBuffer buf;
    VkDeviceMemory mem;
    VkDescriptorBufferInfo buffer_info;
};

struct TextureData {
    VkDescriptorImageInfo image_info;
};

struct VulkanContext {
    std::shared_ptr<RWindow> m_window;

    /* instance */
    VkInstance m_instance;
    std::vector<VkExtensionProperties> m_support_instance_extensions;

    /* surface */
    VkSurfaceKHR m_surface;

    /* physical device */
    std::vector<VkPhysicalDevice> m_gpu_list;
    std::vector<VkPhysicalDeviceProperties> m_gpu_properties_list;
    std::vector<VkPhysicalDeviceMemoryProperties> m_gpu_memory_properties_list;

    /* physical device */
    std::vector<VkQueueFamilyProperties> m_gpu_queue_family_props;
    uint32_t m_graphics_queue_family_index;
    uint32_t m_present_queue_family_index;

    /* device */
    VkDevice m_device;
    VkQueue m_graphics_queue;
    VkQueue m_present_queue;


    VkFormat m_format;



    VkCommandPool m_cmd_pool;
    std::vector<VkCommandBuffer> m_cmd_bufs;



    VkSwapchainKHR m_swapchain;
    std::vector<VkImage> m_swapchain_images;
    std::vector<SwapChainBuffer> m_swapchain_buffers;

    Depth m_depth;

    glm::mat4x4 m_projection;
    glm::mat4x4 m_view;
    glm::mat4x4 m_model;
    glm::mat4x4 m_clip;
    glm::mat4x4 m_mvp;

    UniformData m_uniform_data;

    VkPipelineLayout m_pipeline_layout;
    std::vector<VkDescriptorSetLayout> m_desc_layouts;

    VkRenderPass m_renderpass;

    VkPipelineShaderStageCreateInfo m_shader_stages[2];

    std::vector<VkFramebuffer> m_framebuffers;

    VertexBuffer m_vertex_buf;
    VkVertexInputBindingDescription vi_binding;
    VkVertexInputAttributeDescription vi_attribs[2];

    VkDescriptorPool m_desc_pool;
    std::vector<VkDescriptorSet> m_desc_sets;

    TextureData m_texture_data;

    VkPipelineCache m_pipeline_cache;
    VkPipeline m_pipeline;

    uint32_t m_current_buffer;
    uint32_t m_queue_family_count;

    VkViewport m_viewport;
    VkRect2D m_scissor;

    std::vector<VkSemaphore> m_image_available_semaphores;
    std::vector<VkSemaphore> m_render_finished_semaphores;
    std::vector<VkFence> m_draw_fences;
    std::vector<VkFence> m_images_in_flight_fences;
};

}
}












#endif
