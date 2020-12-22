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
#include "command_buffer_initializer.h"
#include "vulkan_helper.h"
#define NUM_DESCRIPTOR_SETS 1
#define FENCE_TIMEOUT 100000000

namespace reality
{
namespace r_render_system
{
  struct Impl
  {
      std::shared_ptr<VulkanContext> m_ctx {new VulkanContext()};

      void init()
      {
        printf("init...\n");
        instance_init = std::make_shared<InstanceInitializer>(m_ctx);
        physical_device_init = std::make_shared<PhysicalDeviceInitializer>(m_ctx);
        surface_init = std::make_shared<SurfaceInitializer>(m_ctx);
        device_init = std::make_shared<DeviceInitializer>(m_ctx);
        cmd_pool_init = std::make_shared<CommandPoolInitializer>(m_ctx);
        cmd_buf_init = std::make_shared<CommandBufferInitializer>(m_ctx);
        VulkanHelper::execute_begin_command_buffer(m_ctx);
        VulkanHelper::init_device_queue(m_ctx);

      }
  private:
      std::shared_ptr<InstanceInitializer> instance_init;
      std::shared_ptr<PhysicalDeviceInitializer> physical_device_init;
      std::shared_ptr<SurfaceInitializer> surface_init;
      std::shared_ptr<DeviceInitializer> device_init;
      std::shared_ptr<CommandPoolInitializer> cmd_pool_init;
      std::shared_ptr<CommandBufferInitializer> cmd_buf_init;
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

}
}
