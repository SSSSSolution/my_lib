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

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;
};
const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    {{0.5, 0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

struct VulkanContext {
    std::shared_ptr<RWindow> m_window;

    /* instance */
    VkInstance m_instance;
    std::vector<VkExtensionProperties> m_support_instance_extensions;

    /* surface */
    VkSurfaceKHR m_surface;
    VkSurfaceCapabilitiesKHR m_surface_capabilities;
    std::vector<VkSurfaceFormatKHR> m_surface_formats;
    std::vector<VkPresentModeKHR> m_present_modes;

    /* physical device */
    std::vector<VkPhysicalDevice> m_gpu_list;
    std::vector<VkPhysicalDeviceProperties> m_gpu_properties_list;
    std::vector<VkPhysicalDeviceMemoryProperties> m_gpu_memory_properties_list;

    /* physical device */
    std::vector<VkQueueFamilyProperties> m_gpu_queue_family_props;
    uint32_t m_graphics_queue_family_index;
    uint32_t m_present_queue_family_index;

    /* device */
    std::vector<VkExtensionProperties> m_support_device_extensions;
    VkDevice m_device;
    VkQueue m_graphics_queue;
    VkQueue m_present_queue;

    /* swapchain */
    VkSwapchainKHR m_swapchain;
    std::vector<VkImage> m_swapchain_images;
    std::vector<VkImageView> m_swapchain_views;
    /* swapchain choose */
    VkSurfaceFormatKHR m_swapchain_format;
    VkPresentModeKHR m_swapchain_present_mode;
    VkExtent2D m_swapchain_extent;

    /* render pass */
    VkRenderPass m_renderpass;

    /* pipeline */
    VkShaderModule m_vertex_shader_module;
    VkShaderModule m_frag_shader_module;
    VkPipelineShaderStageCreateInfo m_shader_stages[2];
    VkPipelineLayout m_pipeline_layout;
    VkPipeline m_pipeline;

    /* frame buffer */
    std::vector<VkFramebuffer> m_framebuffers;

    /* vertex buffer */
    VertexBuffer m_vertex_buf;

    /* command buffer */
    VkCommandPool m_cmd_pool;
    std::vector<VkCommandBuffer> m_cmd_bufs;

    /* semaphore */
    std::vector<VkSemaphore> m_image_avaliable_semaphores;
    std::vector<VkSemaphore> m_render_finished_semaphores;
    std::vector<VkFence> m_in_flight_fences;
    std::vector<VkFence> m_image_in_flight_fences;


    VkFormat m_format;
    std::vector<SwapChainBuffer> m_swapchain_buffers;

    Depth m_depth;

    glm::mat4x4 m_projection;
    glm::mat4x4 m_view;
    glm::mat4x4 m_model;
    glm::mat4x4 m_clip;
    glm::mat4x4 m_mvp;

    UniformData m_uniform_data;
    std::vector<VkDescriptorSetLayout> m_desc_layouts;




    VkVertexInputBindingDescription vi_binding;
    VkVertexInputAttributeDescription vi_attribs[2];

    VkDescriptorPool m_desc_pool;
    std::vector<VkDescriptorSet> m_desc_sets;

    TextureData m_texture_data;

    VkPipelineCache m_pipeline_cache;


    uint32_t m_current_buffer;
    uint32_t m_queue_family_count;

    VkViewport m_viewport;
    VkRect2D m_scissor;

};

}
}












#endif
