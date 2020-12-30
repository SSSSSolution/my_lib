#ifndef R_RENDER_SYSTEM_R_RENDERER_H
#define R_RENDER_SYSTEM_R_RENDERER_H

#include "r_window.h"
#include <memory>

namespace reality
{
namespace r_render_system
{
  struct Impl;
  class RRenderer
  {  
  public:
      RRenderer(std::shared_ptr<RWindow> window);
      ~RRenderer();
    bool init();
    void draw();

  private:
    std::unique_ptr<Impl> m_impl;

  };
}
}

#endif
