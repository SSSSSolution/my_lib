/*
 * native widget xlib implemetation
 */

#include <QWindow>
#include <QVBoxLayout>
#include <X11/Xlib.h>
#include <rlog.h>
#include <iostream>
#include "native_widget.h"

namespace reality
{
namespace charizard {

    struct NativeWidgetImpl
    {
        // xlib struct:
        Display *display;
        Window window;
        int screen;

        bool init_xlib_window()
        {
            display = XOpenDisplay(nullptr);
            if (display == nullptr)
            {
                RLOG(ERROR, "XOpenDisplay() failed!");
                return false;
            }

            screen = DefaultScreen(display);
            unsigned int win_border_width = 2;
            int x = 0;
            int y = 0;
            unsigned int width = 600;
            unsigned int height = 400;
            window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                         x, y,  width, height,
                                         win_border_width,
                                         BlackPixel(display, screen),
                                         WhitePixel(display, screen));

            return true;
        }

        void refresh_xlib_window()
        {
            XFlush(display);
        }

        void free_xlib()
        {
            XCloseDisplay(display);
        }

        QWindow *native_window;
        QWidget *native_widget;
    };

    NativeWidget::NativeWidget(QWidget *parent)
        : QWidget(parent)
    {
        impl = std::make_unique<NativeWidgetImpl>();

        if (!impl->init_xlib_window())
        {
            RLOG(ERROR, "init xlib window failed");
            exit(-1);
        }

        impl->native_window = QWindow::fromWinId(impl->window);
        if (impl->native_window == nullptr)
        {
            RLOG(ERROR, "embeding a xlib window inside a QWindow is not be supported");
            exit(-1);
        }
        impl->native_widget = createWindowContainer(impl->native_window, this);

        auto main_layout = new QVBoxLayout(this);
        main_layout->setMargin(5);
        main_layout->addWidget(impl->native_widget);

        setFixedSize(810, 810);
    }

    NativeWidget::~NativeWidget()
    {
        impl->free_xlib();
    }

    void NativeWidget::refresh()
    {
        impl->refresh_xlib_window();
    }

    // Native render widget

    struct NativeRenderWidgetImpl : public NativeWidgetImpl
    {
        NativeRenderWidgetImpl(std::unique_ptr<NativeWidgetImpl> &impl)
        {
            display = impl->display;
            window = impl->window;
            screen = impl->screen;
        }

        XImage ximage_init;
        std::vector<XImage *> ximages;

        int width;
        int height;

        void init_ximage()
        {
            ximage_init.width = static_cast<int>(width);
            ximage_init.height = static_cast<int>(height);
            ximage_init.xoffset = 0;
            ximage_init.format = ZPixmap;
            ximage_init.byte_order = LSBFirst;
            ximage_init.bitmap_unit = 32;
            ximage_init.bitmap_bit_order = LSBFirst;
            ximage_init.bitmap_pad = 32;
            ximage_init.depth = 24;
            ximage_init.bytes_per_line = width * 4;
            ximage_init.bits_per_pixel = 32;
            ximage_init.red_mask = 0xff0000;
            ximage_init.green_mask = 0x00ff00;
            ximage_init.blue_mask = 0xff;

            if (XInitImage(&ximage_init) == 0)
            {
                RLOG(ERROR, "XImage init failed");
            }
        }

    };

    NativeRenderWidget::NativeRenderWidget(QWidget *parent)
        : NativeWidget (parent)
    {
        impl = std::make_unique<NativeRenderWidgetImpl>(NativeWidget::impl);

        impl->width = 800;
        impl->height = 800;
        impl->init_ximage();

        m_framebuffer_count = 2;
        update_framebuffers();

    }

    NativeRenderWidget::~NativeRenderWidget()
    {

    }

    void NativeRenderWidget::set_size(unsigned int width, unsigned int height)
    {
        impl->width = width;
        impl->height = height;
        update_framebuffers();
        setFixedSize(static_cast<int>(width), static_cast<int>(height));
    }

    void NativeRenderWidget::set_framebuffer_count(unsigned int count)
    {
        m_framebuffer_count = count;
        update_framebuffers();
    }

    void NativeRenderWidget::update_framebuffers()
    {
        m_framebuffers.clear();
        for (auto img : impl->ximages)
        {
            impl->ximage_init.f.destroy_image(img);
        }
        impl->ximages.clear();

        for (unsigned int i = 0; i < m_framebuffer_count; i++)
        {
            auto framebuffer = std::make_shared<FrameBuffer>(impl->width, impl->height);
            m_framebuffers.push_back(framebuffer);
            auto ximage =  impl->ximage_init.f.create_image(impl->display, DefaultVisual(impl->display, impl->screen), 24, ZPixmap, 0,
                                                            reinterpret_cast<char *>(m_framebuffers[i]->data),
                                                            impl->width, impl->height, 32, impl->width*4);
            impl->ximages.push_back(ximage);
        }
        m_current_idx = 0;
    }

    std::shared_ptr<FrameBuffer> NativeRenderWidget::get_next_framebuffer()
    {
        auto next_idx = (m_current_idx + 1) % m_framebuffer_count;
        std::cout << "next idx" << next_idx << std::endl;
        return m_framebuffers[next_idx];
    }

    unsigned int NativeRenderWidget::current_framebuffer_idx()
    {
        return m_current_idx;
    }

    void NativeRenderWidget::show_next_framebuffer()
    {
        m_current_idx = (m_current_idx + 1) % m_framebuffer_count;
        XPutImage(impl->display, impl->window, DefaultGC(impl->display, impl->screen),
                  impl->ximages[m_current_idx], 0, 0, 0, 0, impl->width, impl->height);
        refresh();
    }

    void NativeRenderWidget::showEvent(QShowEvent *e)
    {
        (void)(*e);
        RLOG(INFO, "native render widget show");

    }
}
}


















