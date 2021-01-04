/* r_window xlib implementation
 * author: wei.huang
 * date: 2020.12.6
 */

#include "r_window.h"
//#include "r_renderer.h"
#include "rlog.h"

#include <memory>
#include <stdlib.h>

extern "C" {
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
}

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
      unsigned long m_background;
      unsigned long m_border;
  };

  RWindow::RWindow()
  {
    m_impl = new RWindowImpl;
//    RRenderer *renderer = new RRenderer();
//    if (renderer->init())
//    {
//        RLOG(INFO, "init vkInstance successfull!");
//    }
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

    m_impl->m_screen_num = DefaultScreen(m_impl->m_display);
    m_impl->m_background = BlackPixel(m_impl->m_display, m_impl->m_screen_num);
    m_impl->m_border = WhitePixel(m_impl->m_display, m_impl->m_screen_num);

    m_impl->m_window = XCreateSimpleWindow(m_impl->m_display, XDefaultRootWindow(m_impl->m_display),
                                           m_impl->m_pos_x, m_impl->m_pos_y,
                                           m_impl->m_width, m_impl->m_height,
                                           2, m_impl->m_border, m_impl->m_background);
    XSelectInput(m_impl->m_display, m_impl->m_window, ButtonPressMask|StructureNotifyMask);

//    std::cout << "init successfull!" << std::endl;
  }

  void RWindow::move(int pos_x, int pos_y)
  {

  }

  void RWindow::resize(int width, int height)
  {

  }

  void RWindow::show()
  {
    XEvent event;
    XMapWindow(m_impl->m_display, m_impl->m_window);
    while(1) {
        if (!XPending(m_impl->m_display))
        {

        } else {
        XNextEvent(m_impl->m_display, &event);
        switch (event.type)
        {
            case ConfigureNotify:
              if (m_impl->m_width != event.xconfigure.width ||
                  m_impl->m_height != event.xconfigure.height)
              {
                  if (m_impl->m_width == event.xconfigure.width &&
                      m_impl->m_height == event.xconfigure.height)
                    break;
                  m_impl->m_width = event.xconfigure.width;
                  m_impl->m_height = event.xconfigure.height;
                  if (m_resize_callback)
                  {
                    m_resize_callback();
                    printf("resize\n");
                  }
              }
            break;
            case ButtonPress:
              XCloseDisplay(m_impl->m_display);
        }

        }
        if (m_draw_func)
        {
            m_draw_func();
        }
    }
  }

  void RWindow::hide()
  {

  }

  int RWindow::width()
  {
      int snum = DefaultScreen(m_impl->m_display);
      return DisplayWidth(m_impl->m_display, snum);
  }

  int RWindow::height()
  {
      int snum = DefaultScreen(m_impl->m_display);
      return DisplayHeight(m_impl->m_display, snum);
  }

  std::shared_ptr<WindowInfo> RWindow::get_window_info()
  {
      std::shared_ptr<WindowInfo> window_info(new WindowInfo());
      window_info->display = m_impl->m_display;
      window_info->window  = m_impl->m_window;
      return window_info;

  }

  void RWindow::set_draw_func(std::function<void()> f)
  {
      m_draw_func = f;
  }

  void RWindow::set_resize_callback(std::function<void ()> f)
  {
      m_resize_callback = f;
  }
}

}
