/* r_window xlib implementation
 * author: wei.huang
 * date: 2020.12.6
 */
#include "r_window.h"
#include "rlog.h"
#include <stdlib.h>
#include <memory>
#include <X11/Xlib.h>
namespace reality {

namespace r_render_system
{
  class RWindowImpl
  {
  public:
      Display *m_display;
      Window m_window;

      int m_width;
      int m_height;
      int m_pos_x;
      int m_pos_y;
      int m_screen_num;
      unsigned long background;
      unsigned long border;
  };

  RWindow::RWindow()
  {

  }

  RWindow::~RWindow()
  {

  }

  void RWindow::init(int width, int height, int pos_x, int pos_y)
  {
    RLOG(INFO, "init RWindow(%d by %d)", width, height);
    m_impl->m_width = width;
    m_impl->m_height = height;
    m_impl->m_pos_x = pos_x;
    m_impl->m_pos_y = pos_y;

    m_impl->m_display = XOpenDisplay(nullptr);
    if (m_impl->m_display == nullptr)
    {
        RLOG(ERROR, "x dislplay init failed!");
        exit(1);
    }
  }

  void RWindow::move(int pos_x, int pos_y)
  {

  }

  void RWindow::resize(int width, int height)
  {

  }

  void RWindow::show()
  {

  }

  void RWindow::hide()
  {

  }
}

}
