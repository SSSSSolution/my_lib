#ifndef REALITY_RENDER_SYSTEM_VERTEX_BUFFER_INITIALIZER_H
#define REALITY_RENDER_SYSTEM_VERTEX_BUFFER_INITIALIZER_H

#include "vulkan_context.h"
#include <memory>

namespace reality
{
    namespace r_render_system
    {
        class VertexBufferInitializer
        {
        public:
            VertexBufferInitializer(std::shared_ptr<VulkanContext> ctx);
            void load_model();
            void init_vertex_buffer();
            void init_index_buffer();
            void init_uniform_buffer();

        private:
            std::shared_ptr<VulkanContext> m_ctx;
        };
    }
}

#endif
