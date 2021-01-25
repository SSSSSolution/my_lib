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

        protected:
            virtual void paintEvent(QPaintEvent *) override;

        private:
            QLabel *m_image_label;
            RenderHandle *m_handle;
            std::shared_ptr<PresentImage> m_present_image;

            QImage *m_image;
            char32_t *m_data;
            int m_width;
            int m_height;
        };
    }
}

#endif
