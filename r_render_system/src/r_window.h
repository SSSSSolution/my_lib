#ifndef R_RENDER_SYSTEM_R_WINDOW_H
#define R_RENDER_SYSTEM_R_WINDOW_H

namespace reality
{
namespace r_render_system
{
  class RWindowImpl;
  class RWindow
  {
  public:
      RWindow();
      ~RWindow();

      void init(int width, int height, int pos_x, int pos_y);
      void move(int pos_x, int pos_y);
      void resize(int width, int height);

      void show();
      void hide();

  private:
      RWindowImpl *m_impl;
  };
}
}

#endif
