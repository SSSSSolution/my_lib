#ifndef REALITY_RENDER_SYSTEM_VULKAN_CONTEXT_H
#define REALITY_RENDER_SYSTEM_VULKAN_CONTEXT_H

#include "r_window.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/hash.hpp"

// use xlib surface
#define VK_USE_PLATFORM_XLIB_KHR
#include "vulkan/vulkan.h"
#include "assert.h"

#include <vector>

namespace reality {
namespace r_render_system {

//struct SwapChainBuffer {
//    VkImage image;
//    VkImageView view;
//};

//struct Depth {
//    VkFormat format = VK_FORMAT_UNDEFINED;
//    VkImage image;
//    VkDeviceMemory mem;
//    VkImageView view;
//};

//struct UniformData {
//    VkBuffer buf;
//    VkDeviceMemory mem;
//    VkDescriptorBufferInfo buffer_info;
//};

struct VertexBuffer {
    VkBuffer buf;
    VkDeviceMemory mem;
//    VkDescriptorBufferInfo buffer_info;
};

//struct TextureData {
//    VkDescriptorImageInfo image_info;
//};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }

    static VkVertexInputBindingDescription get_binding_description()
    {
        VkVertexInputBindingDescription binding_description = {};
        binding_description.binding = 0;
        binding_description.stride = sizeof(Vertex);
        binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return binding_description;
    }

    static std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions()
    {
        std::vector<VkVertexInputAttributeDescription> attribute_descriptions(3);

        attribute_descriptions[0].binding = 0;
        attribute_descriptions[0].location = 0;
        attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attribute_descriptions[0].offset = offsetof(Vertex, pos);

        attribute_descriptions[1].binding = 0;
        attribute_descriptions[1].location = 1;
        attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attribute_descriptions[1].offset = offsetof(Vertex, color);

        attribute_descriptions[2].binding = 0;
        attribute_descriptions[2].location = 2;
        attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attribute_descriptions[2].offset = offsetof(Vertex, texCoord);

        return attribute_descriptions;
    }
};

//template<> struct hash<Vertex> {
//        size_t operator()(Vertex const& vertex) const {
//            return ((hash<glm::vec3>()(vertex.pos) ^
//                   (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
//                   (hash<glm::vec2>()(vertex.texCoord) << 1);
//        }
//};


extern std::vector<Vertex> vertices;
//std::vector<Vertex> vertices = {
//    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
//    {{0.5, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
//    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
//    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}

//    {{0.0f, 1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//    {{1.0f, 1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//    {{0.0f, 0.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//    {{1.0f, 0.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//    {{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//    {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//    {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//    {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//};
extern std::vector<uint32_t> indices;
//std::vector<uint32_t> indices = {
//    0, 1, 2, 2, 3, 1,
//    3, 1, 5, 5, 7, 3,
//    5, 4, 6, 6, 7, 5,
//    1, 0, 4, 4, 5, 1,
//    4, 0, 2, 2, 6, 4,
//    3, 2, 6, 6, 7, 3,
//};

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
    VertexBuffer m_index_buf;

    /* uniform buffer */
    UniformBufferObject m_uniform_buffer_objs;
    std::vector<VkBuffer> m_uniform_bufs;
    std::vector<VkDeviceMemory> m_uniform_buffer_mems;

    /* command buffer */
    VkCommandPool m_cmd_pool;
    std::vector<VkCommandBuffer> m_cmd_bufs;

    /* semaphore */
    std::vector<VkSemaphore> m_image_avaliable_semaphores;
    std::vector<VkSemaphore> m_render_finished_semaphores;
    std::vector<VkFence> m_in_flight_fences;
    std::vector<VkFence> m_image_in_flight_fences;

    /* descriptor set layout */
    VkDescriptorSetLayout m_descriptor_set_layout;

    /* descirptor pool */
    VkDescriptorPool m_desc_pool;

    /* descriptor sets */
    std::vector<VkDescriptorSet> m_descriptor_sets;

    /* texture */
    VkImage m_texture_image;
    VkImageView m_texture_image_view;
    VkDeviceMemory m_texture_image_mem;
    VkSampler m_texture_sampler;

    /* depth */
    VkImage m_depth_image;
    VkDeviceMemory m_depth_image_mem;
    VkImageView m_depth_image_view;

    /* color image */
    VkImage m_color_image;
    VkDeviceMemory m_color_image_mem;
    VkImageView m_color_image_view;

    /* msaa samples */
    VkSampleCountFlagBits m_msaa_samples;

//    VkFormat m_format;
//    std::vector<SwapChainBuffer> m_swapchain_buffers;

//    Depth m_depth;

//    glm::mat4x4 m_projection;
//    glm::mat4x4 m_view;
//    glm::mat4x4 m_model;
//    glm::mat4x4 m_clip;
//    glm::mat4x4 m_mvp;

//    UniformData m_uniform_data;
//    std::vector<VkDescriptorSetLayout> m_desc_layouts;




//    VkVertexInputBindingDescription vi_binding;
//    VkVertexInputAttributeDescription vi_attribs[2];


//    std::vector<VkDescriptorSet> m_desc_sets;

//    TextureData m_texture_data;

//    VkPipelineCache m_pipeline_cache;


//    uint32_t m_current_buffer;
//    uint32_t m_queue_family_count;

//    VkViewport m_viewport;
//    VkRect2D m_scissor;

};

}
}
namespace std {
template<> struct hash<reality::r_render_system::Vertex> {
    size_t operator()(reality::r_render_system::Vertex const& vertex) const {
        return ((hash<glm::vec3>()(vertex.pos) ^
               (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
               (hash<glm::vec2>()(vertex.texCoord) << 1);
    }
};
}












#endif
