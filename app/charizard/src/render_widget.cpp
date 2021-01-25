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
        setMinimumSize(800, 800);

        m_width = 800;
        m_height = 800;
        m_data = (char32_t*)malloc(sizeof(char32_t) * m_width * m_height);
        memset(m_data, 0xff, sizeof(uint32_t) * m_width * m_height);
        m_image = new QImage((const uchar *)m_data, m_width,
                             m_height, m_width * 4, QImage::Format_ARGB32);

        m_present_image = std::make_shared<PresentImage>();
        m_present_image->data = m_data;
        m_present_image->width = m_width;
        m_handle->set_image(m_present_image);
    }

    void RenderWidget::paintEvent(QPaintEvent *)
    {
        qDebug() << "paint event";
        QPainter painter(this);

        QRect target_rect = QRect(0, 0, m_width, m_height);
        QRect source_rect = m_image->rect();
//        QImage image((const uchar *)m_data, m_width,
//                                          m_height, m_width * 4, QImage::Format_ARGB32);
//        image.
//        auto c = image.pixel(0, 0);
//        image.setPixel(0, 0, 0x12345678);
//        image.setPixel(0, 0, c);

//        c = image.pixel(0, image.height()-1);
//        image.setPixel(0, image.height()-1, 0x12345678);
//        image.setPixel(0, image.height()-1, c);

//        image.setPixel(0, 0, 0x12345678);
//        image.setPixel(0, 0, c);

//        c = image.pixel(image.width() - 1, image.height() -1);
//        image.setPixel(image.width() - 1, image.height()-1, 0x12345678);
//        image.setPixel(image.width() - 1, image.height()-1, c);
        qDebug() << "image cache key: " << m_image->cacheKey();
        painter.drawImage(target_rect, *m_image, source_rect);
    }

    }
}
