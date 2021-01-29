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

        setFixedSize(610, 410);
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
    NativeRenderWidget::NativeRenderWidget(QWidget *parent)
        : NativeWidget (parent)
    {
        m_width = 600;
        m_height = 400;
        m_framebuffer_count = 2;
        update_framebuffers();
    }

    void NativeRenderWidget::set_size(unsigned int width, unsigned int height)
    {
        m_width = width;
        m_height = height;
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
        for (int i = 0; i < m_framebuffer_count; i++)
        {
            auto framebuffer = std::make_shared<FrameBuffer>(m_width, m_height);
            m_framebuffers.push_back(framebuffer);
        }
        m_current_idx = 0;
    }

    std::shared_ptr<FrameBuffer> NativeRenderWidget::get_next_framebuffer()
    {
        auto next_idx = (m_current_idx + 1) % m_framebuffer_count;
        return m_framebuffers[next_idx];
    }

    unsigned int NativeRenderWidget::current_framebuffer_idx()
    {
        return m_current_idx;
    }

    void NativeRenderWidget::show_next_framebuffer()
    {
        // show m_framebuffer[current_idx]
        // to do
        XImage ximage;
        ximage.width = static_cast<int>(m_width);
        ximage.height = static_cast<int>(m_height);
        ximage.xoffset = 0;
        ximage.format = XYPixmap;
        ximage.byte_order = LSBFirst;
        ximage.bitmap_unit = 32;
        ximage.bitmap_bit_order = LSBFirst;
        ximage.bitmap_pad = 32;
        ximage.depth = 1;
        ximage.bytes_per_line = 76;
        ximage.bits_per_pixel = 1;
        ximage.red_mask = 0xff0000;
        ximage.green_mask = 0x00ff00;
        ximage.blue_mask = 0xff;
        ximage.data = reinterpret_cast<char *>(m_framebuffers[m_current_idx]->data);

//        XPutImage(impl->display, impl->window, &ximage, )
        m_current_idx = (m_current_idx + 1) % m_framebuffer_count;
    }

    void NativeRenderWidget::showEvent(QShowEvent *e)
    {
        RLOG(INFO, "native render widget show");

    }

    void NativeRenderWidget::test_slot()
    {
        auto ximage = XGetImage(impl->display, impl->window, 0, 0, m_width, m_height, 1, XYPixmap);
        std::cout << "width: " << ximage->width << std::endl;
        std::cout << "height: " << ximage->height << std::endl;
        std::cout << "xoffset " << ximage->xoffset << std::endl;
        std::cout << "format " << ximage->format << std::endl;
        std::cout << "byte_order " << ximage->byte_order << std::endl;
        std::cout << "bitmap_unit " << ximage->bitmap_unit << std::endl;
        std::cout << "bitmap_bit_order " << ximage->bitmap_bit_order << std::endl;
        std::cout << "bitmap_pad " << ximage->bitmap_pad << std::endl;
        std::cout << "depth" << ximage->depth << std::endl;
        std::cout << "bytes_per_line " << ximage->bytes_per_line << std::endl;
        std::cout << "bits_per_pixel: " << ximage->bits_per_pixel << std::endl;
        std::cout << "red_mask: " << std::hex << ximage->red_mask << std::endl;
        std::cout << "green_mask: " << ximage->green_mask << std::endl;
        std::cout << "blue_mask: " << ximage->blue_mask << std::endl;

        XImage image;
        image.width = static_cast<int>(m_width);
        image.height = static_cast<int>(m_height);
        image.xoffset = 0;
        image.format = ZPixmap;
        image.byte_order = LSBFirst;
        image.bitmap_unit = 32;
        image.bitmap_bit_order = LSBFirst;
        image.bitmap_pad = 32;
        image.depth = 32;
        image.bytes_per_line = m_width * 4;
        image.bits_per_pixel = 32;
        image.red_mask = 0xff0000;
        image.green_mask = 0x00ff00;
        image.blue_mask = 0xff;
        image.data = reinterpret_cast<char *>(m_framebuffers[m_current_idx]->data);

        for (int i = 0; i < 600; i++)
        {
            for (int j = 0; j < 400; j++)
            {
//                image1->f.put_pixel(image1, i, j, 0x000000ff);
                *(m_framebuffers[m_current_idx]->data + j * 600 + i) = 0xff0000ff;
            }
        }


        std::cout << "XInitImage: " <<  std::dec << XInitImage(&image) << std::endl;
        XImage *image1 = image.f.create_image(impl->display, DefaultVisual(impl->display, impl->screen), 24, ZPixmap, 0,
                                     reinterpret_cast<char *>(m_framebuffers[m_current_idx]->data),
                                     600, 400, 32, 600*4);
        for (int i = 0; i < 600; i++)
        {
            for (int j = 0; j < 400; j++)
            {
                image1->f.put_pixel(image1, i, j, 0x00ff0000);
//               *(m_framebuffers[m_current_idx]->data + j * 600 + i) = 0xff0000;
            }
        }

        for (int i = 0; i < 1000; i++)
        {
            std::cout << std::hex << *(m_framebuffers[m_current_idx]->data + i) << std::endl;
        }


        std::cout << std::dec << "width: " << image1->width << std::endl;
        std::cout << "height: " << image1->height << std::endl;
        std::cout << "xoffset " << image1->xoffset << std::endl;
        std::cout << "format " << image1->format << std::endl;
        std::cout << "byte_order " << image1->byte_order << std::endl;
        std::cout << "bitmap_unit " << image1->bitmap_unit << std::endl;
        std::cout << "bitmap_bit_order " << image1->bitmap_bit_order << std::endl;
        std::cout << "bitmap_pad " << image1->bitmap_pad << std::endl;
        std::cout << "depth" << image1->depth << std::endl;
        std::cout << "bytes_per_line " << image1->bytes_per_line << std::endl;
        std::cout << "bits_per_pixel: " << image1->bits_per_pixel << std::endl;
        std::cout << "red_mask: " << std::hex << image1->red_mask << std::endl;
        std::cout << "green_mask: " << image1->green_mask << std::endl;
        std::cout << "blue_mask: " << image1->blue_mask << std::endl;

        GC gc = DefaultGC(impl->display, impl->screen);
       XPutImage(impl->display, impl->window, gc, image1, 0, 0, 0, 0, 600, 400);
        refresh();
    }
}
}


















