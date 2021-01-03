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
const int MAX_FRAMES_IN_FLIGHT = 2;
namespace reality
{
namespace r_render_system
{
  struct Impl
  {
      uint32_t m_current_frame = 0;
      std::shared_ptr<VulkanContext> m_ctx {new VulkanContext()};
      uint32_t current_frame = 0;

      void create_semaphores()
      {
          m_ctx->m_image_avaliable_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
          m_ctx->m_render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
          m_ctx->m_in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);
          m_ctx->m_image_in_flight_fences.resize(m_ctx->m_swapchain_images.size(),
                                                 VK_NULL_HANDLE);

          VkSemaphoreCreateInfo semaphore_info = {};
          semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

          VkFenceCreateInfo fence_info = {};
          fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
          fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

          for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
          {
              auto res = vkCreateSemaphore(m_ctx->m_device, &semaphore_info, nullptr,
                                           &m_ctx->m_image_avaliable_semaphores[i]);
              assert(res == VK_SUCCESS);
              res = vkCreateSemaphore(m_ctx->m_device, &semaphore_info, nullptr,
                                           &m_ctx->m_render_finished_semaphores[i]);
              assert(res == VK_SUCCESS);
              res = vkCreateFence(m_ctx->m_device, &fence_info, nullptr,
                                  &m_ctx->m_in_flight_fences[i]);
              assert(res == VK_SUCCESS);
          }


      }

      void init()
      {
        printf("init...\n");
        instance_init = std::make_shared<InstanceInitializer>(m_ctx);
        surface_init = std::make_shared<SurfaceInitializer>(m_ctx);
        physical_device_init = std::make_shared<PhysicalDeviceInitializer>(m_ctx);
        device_init = std::make_shared<DeviceInitializer>(m_ctx);
        swapchain_init = std::make_shared<SwapchainInitializer>(m_ctx);

        /* render */
        renderpass_init = std::make_shared<RenderPassInitializer>(m_ctx);

        /* pipeline */
        shader_init = std::make_shared<ShaderInitializer>(m_ctx);
        pipeline_init = std::make_shared<PipelineInitializer>(m_ctx);

        /* frame buffer */
        framebuffer_init = std::make_shared<FramebufferInitializer>(m_ctx);

        /* command pool */
        cmd_pool_init = std::make_shared<CommandPoolInitializer>(m_ctx);

        /* command buffer */
        cmd_buf_init = std::make_shared<CommandBufferInitializer>(m_ctx);

        /* semaphores */
        create_semaphores();
      }

      void draw()
      {
          vkWaitForFences(m_ctx->m_device, 1, &m_ctx->m_in_flight_fences[current_frame],
                          VK_TRUE, UINT64_MAX);
          vkResetFences(m_ctx->m_device, 1, &m_ctx->m_in_flight_fences[current_frame]);
          // acquire an image from the swap chain
          uint32_t image_index;
          vkAcquireNextImageKHR(m_ctx->m_device, m_ctx->m_swapchain, UINT64_MAX,
                                m_ctx->m_image_avaliable_semaphores[current_frame], VK_NULL_HANDLE, &image_index);
          printf("acquire image index: %d\n", image_index);
          if (m_ctx->m_image_in_flight_fences[image_index] != VK_NULL_HANDLE)
          {
              vkWaitForFences(m_ctx->m_device, 1, &m_ctx->m_image_in_flight_fences[image_index],
                              VK_TRUE, UINT64_MAX);
          }
          m_ctx->m_image_in_flight_fences[image_index] = m_ctx->m_image_in_flight_fences[current_frame];

          // Execute the command buffer with that image as attachment in the framebuffer
          VkSubmitInfo submit_info = {};
          submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

          VkSemaphore wait_semaphores[] = {m_ctx->m_image_avaliable_semaphores[current_frame]};
          VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
          submit_info.waitSemaphoreCount = 1;
          submit_info.pWaitSemaphores = wait_semaphores;
          submit_info.pWaitDstStageMask = wait_stages;
          submit_info.commandBufferCount = 1;
          submit_info.pCommandBuffers = &m_ctx->m_cmd_bufs[image_index];

          VkSemaphore signal_semaphores[] = {m_ctx->m_render_finished_semaphores[current_frame]};
          submit_info.signalSemaphoreCount = 1;
          submit_info.pSignalSemaphores = signal_semaphores;

          vkResetFences(m_ctx->m_device, 1, &m_ctx->m_in_flight_fences[current_frame]);
          auto res = vkQueueSubmit(m_ctx->m_graphics_queue, 1, &submit_info,
                                   m_ctx->m_in_flight_fences[current_frame]);
          assert(res == VK_SUCCESS);
          printf("submit cmd\n");

          // return the image to the swap chain for presentaion
          VkPresentInfoKHR present_info = {};
          present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
          present_info.waitSemaphoreCount = 1;
          present_info.pWaitSemaphores = signal_semaphores;

          VkSwapchainKHR swapchains[] = {m_ctx->m_swapchain};
          present_info.swapchainCount = 1;
          present_info.pSwapchains = swapchains;
          present_info.pImageIndices = &image_index;
          present_info.pResults = nullptr;

          vkQueuePresentKHR(m_ctx->m_present_queue, &present_info);

          vkQueueWaitIdle(m_ctx->m_present_queue);
          current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
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

















