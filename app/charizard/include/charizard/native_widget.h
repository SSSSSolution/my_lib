#ifndef REALITY_CHARIZARD_NATIVE_WIDGET_H
#define REALITY_CHARIZARD_NATIVE_WIDGET_H

#include <memory>
#include <QWidget>
#include "rlog.h"
#include "types.h"

namespace reality
{
    namespace charizard
    {
    struct NativeWidgetImpl;
    class NativeWidget : public QWidget
    {
        Q_OBJECT
    public:
        NativeWidget(QWidget *parent);
        ~NativeWidget();

        void refresh();

    protected:
        std::unique_ptr<NativeWidgetImpl> impl;
    };



    struct NativeRenderWidgetImpl;
    class NativeRenderWidget : public NativeWidget
    {
        Q_OBJECT
    public:
        NativeRenderWidget(QWidget *parent);
        ~NativeRenderWidget();

        void set_framebuffer_count(unsigned int);
        void set_size(unsigned int width, unsigned int height);
        std::shared_ptr<FrameBuffer> get_next_framebuffer();
        unsigned int current_framebuffer_idx();
        void show_next_framebuffer();

    protected:
        virtual void showEvent(QShowEvent *e);

    private:
        void update_framebuffers();

    private:
        std::unique_ptr<NativeRenderWidgetImpl> impl;
        std::vector<std::shared_ptr<FrameBuffer>> m_framebuffers;

        unsigned int m_framebuffer_count;

        unsigned int m_current_idx;
    };

    }
}

#endif
