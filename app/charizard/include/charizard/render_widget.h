#ifndef REALITY_CHARIZARD_RENDER_WIDGET_H
#define REALITY_CHARIZARD_RENDER_WIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>

#include "render_handle.h"

namespace reality
{
    namespace charizard
    {
        class RenderWidget : public QWidget
        {
            Q_OBJECT
        public:
            RenderWidget(RenderHandle *handle, QWidget *parent);

        private:
            QLabel *m_image_label;
            RenderHandle *m_handle;
            QImage *m_image;
            uint32_t *m_data;
            int m_width;
            int m_height;
        };
    }
}

#endif
