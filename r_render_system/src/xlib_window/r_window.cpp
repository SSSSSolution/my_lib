/* r_window xlib implementation
 * author: wei.huang
 * date: 2020.12.6
 */
#include "r_window.h"
#include "rlog.h"
#include <stdlib.h>
#include <memory>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <iostream>

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

    std::cout << "init successfull!" << std::endl;
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
    std::cout << "XMapWIndow" << std::endl;
    while(1) {
        XNextEvent(m_impl->m_display, &event);
        switch (event.type)
        {
            case ConfigureNotify:
              if (m_impl->m_width != event.xconfigure.width ||
                  m_impl->m_height != event.xconfigure.height)
              {
                  m_impl->m_width = event.xconfigure.width;
                  m_impl->m_height = event.xconfigure.height;
              }
            break;
            case ButtonPress:
              XCloseDisplay(m_impl->m_display);
        }
    }
  }

  void RWindow::hide()
  {

  }
}

}
