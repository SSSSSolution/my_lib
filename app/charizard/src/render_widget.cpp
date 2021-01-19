#include "render_widget.h"

#include <QVBoxLayout>
#include <QPixmap>
#include <QApplication>
#include <QPainter>
#include <QDebug>

namespace reality
{
    namespace charizard
    {
    RenderWidget::RenderWidget(RenderHandle *handle, QWidget *parent)
        : QWidget(parent), m_handle(handle)
    {
        auto c = connect(m_handle, &RenderHandle::draw, this, [this](){
//            m_image_label->setPixmap(QPixmap::fromImage(*m_image));
            update();
            QApplication::processEvents();
        });
        assert(c != nullptr);

//        m_image_label = new QLabel(this);

//        auto main_layout = new QVBoxLayout(this);
//        main_layout->setMargin(5);
//        main_layout->addWidget(m_image_label);
//        main_layout->setAlignment(m_image_label, Qt::AlignCenter);

//        m_image_label->setMinimumSize(400, 400);
//        m_image_label->setStyleSheet("background-color:blue;");
        setMinimumSize(400, 400);

        m_width = 500;
        m_height = 500;
        m_data = (uint32_t*)malloc(sizeof(uint32_t) * m_width * m_height);
        memset(m_data, 0xff, sizeof(uint32_t) * m_width * m_height);
        m_image = new QImage((const uchar *)m_data, m_width,
                             m_height, m_width * 4, QImage::Format_ARGB32);

        m_handle->set_image(m_data, m_width, m_height);
    }

    void RenderWidget::paintEvent(QPaintEvent *)
    {
        qDebug() << "paint event";
        QPainter painter(this);

        QRect target_rect = QRect(0, 0, 400, 400);
        QRect source_rect = m_image->rect();
//        QImage image((const uchar *)m_data, m_width,
//                                          m_height, m_width * 4, QImage::Format_ARGB32);
//        image.
        m_image->bits();
        painter.drawImage(target_rect, *m_image, source_rect);
    }

    }
}
