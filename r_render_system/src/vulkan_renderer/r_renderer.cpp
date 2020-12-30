#include "r_renderer.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>

#include <stdio.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "vulkan_context.h"
#include "instance_initializer.h"
#include "physical_device_initializer.h"
#include "surface_initializer.h"
#include "device_initializer.h"
#include "command_pool_initializer.h"
#include "swapchain_initializer.h"
#include "command_buffer_initializer.h"
#include "depth_buffer_initializer.h"
#include "uniform_buffer_initializer.h"
#include "descriptor_and_pipeline_initializer.h"
#include "renderpass_initializer.h"
#include "shader_initializer.h"
#include "framebuffer_initializer.h"
#include "vertex_buffer_initializer.h"
#include "descriptor_pool_initializer.h"
#include "descriptor_set_initializer.h"
#include "pipeline_initializer.h"
#include "vulkan_helper.h"
#define NUM_DESCRIPTOR_SETS 1
#define FENCE_TIMEOUT 100000000

namespace reality
{
namespace r_render_system
{
  struct Impl
  {
      uint32_t m_current_frame = 0;
      std::shared_ptr<VulkanContext> m_ctx {new VulkanContext()};

      void init()
      {
        printf("init...\n");
        instance_init = std::make_shared<InstanceInitializer>(m_ctx);
        physical_device_init = std::make_shared<PhysicalDeviceInitializer>(m_ctx);
//        surface_init = std::make_shared<SurfaceInitializer>(m_ctx);
        device_init = std::make_shared<DeviceInitializer>(m_ctx);
//        cmd_pool_init = std::make_shared<CommandPoolInitializer>(m_ctx);
//        cmd_buf_init = std::make_shared<CommandBufferInitializer>(m_ctx);
//        VulkanHelper::execute_begin_command_buffer(m_ctx);
//        VulkanHelper::init_device_queue(m_ctx);
//        swapchain_init = std::make_shared<SwapchainInitializer>(m_ctx);
//        depth_buffer_init = std::make_shared<DepthBufferInitializer>(m_ctx);
//        uniform_buffer_init = std::make_shared<UniformBufferInitializer>(m_ctx);
//        descriptor_and_pipeline_init = std::make_shared<DescriptorAndPipelineInitializer>(m_ctx);
//        renderpass_init = std::make_shared<RenderPassInitializer>(m_ctx);
//        shader_init = std::make_shared<ShaderInitializer>(m_ctx);
//        framebuffer_init = std::make_shared<FramebufferInitializer>(m_ctx);
//        vertex_buffer_init = std::make_shared<VertexBufferInitializer>(m_ctx);
//        desc_pool_init = std::make_shared<DescriptorPoolInitializer>(m_ctx);
//        desc_set_init = std::make_shared<DescriptorSetInitializer>(m_ctx);
//        pipeline_init = std::make_shared<PipelineInitializer>(m_ctx);
//        printf("start render...\n");
//        VkClearValue clear_values[2];
//        clear_values[0].color.float32[0] = 0.2f;
//        clear_values[0].color.float32[1] = 0.2f;
//        clear_values[0].color.float32[2] = 0.2f;
//        clear_values[0].color.float32[3] = 0.2f;
//        clear_values[1].depthStencil.depth = 1.0f;
//        clear_values[1].depthStencil.stencil = 0;


      }

      void draw()
      {
      }

  private:
      std::shared_ptr<InstanceInitializer> instance_init;
      std::shared_ptr<PhysicalDeviceInitializer> physical_device_init;
      std::shared_ptr<SurfaceInitializer> surface_init;
      std::shared_ptr<DeviceInitializer> device_init;
      std::shared_ptr<CommandPoolInitializer> cmd_pool_init;
      std::shared_ptr<CommandBufferInitializer> cmd_buf_init;
      std::shared_ptr<SwapchainInitializer> swapchain_init;
      std::shared_ptr<DepthBufferInitializer> depth_buffer_init;
      std::shared_ptr<UniformBufferInitializer> uniform_buffer_init;
      std::shared_ptr<DescriptorAndPipelineInitializer> descriptor_and_pipeline_init;
      std::shared_ptr<RenderPassInitializer> renderpass_init;
      std::shared_ptr<ShaderInitializer> shader_init;
      std::shared_ptr<FramebufferInitializer> framebuffer_init;
      std::shared_ptr<VertexBufferInitializer> vertex_buffer_init;
      std::shared_ptr<DescriptorPoolInitializer> desc_pool_init;
      std::shared_ptr<DescriptorSetInitializer> desc_set_init;
      std::shared_ptr<PipelineInitializer> pipeline_init;
  };

  RRenderer::RRenderer(std::shared_ptr<RWindow> window)
      : m_impl(new Impl())
  {
    m_impl->m_ctx->m_window = window;
  }

  RRenderer::~RRenderer() = default;

  bool RRenderer::init()
  {
     m_impl->init();

     return true;
  }

  void RRenderer::draw()
  {
      m_impl->draw();
  }
}
}

















