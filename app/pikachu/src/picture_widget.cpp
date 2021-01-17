#include "picture_widget.h"

#include <QVBoxLayout>
#include <QResizeEvent>
#include <QDebug>

namespace reality
{
namespace pikachu
{
    PictureWidget::PictureWidget(ConversionHandle *handle, QWidget *parent)
        : QWidget(parent),
          m_handle(handle)
    {
        setStyleSheet("background-color:black;");

        m_picture_label = new QLabel(this);
        m_picture_label->setAlignment(Qt::AlignCenter);
//        m_picture_label->setStyleSheet("background-color:blue;");

        QVBoxLayout *main_layout = new QVBoxLayout(this);
        main_layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Maximum));
        main_layout->addWidget(m_picture_label);
        main_layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Maximum));

        auto res = connect(m_handle, SIGNAL(sig_show_picture(QString)),
                this, SLOT(slot_load(QString)));
        assert(res != nullptr);
    }

    void PictureWidget::slot_load(QString file_path)
    {
        m_picture_path = file_path;

        m_pixmap =  QPixmap(m_picture_path);
        auto show_pixmap = m_pixmap.scaled(m_picture_label->width(), m_picture_label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_picture_label->setPixmap(show_pixmap);
        m_picture_label->setMinimumSize(QSize(1, 1));
    }

    void PictureWidget::showEvent(QShowEvent *e)
    {
//       m_picture_label->resize(e->size());
    }

    void PictureWidget::resizeEvent(QResizeEvent *e)
    {
        auto show_pixmap = m_pixmap.scaled(m_picture_label->width(), m_picture_label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_picture_label->setPixmap(show_pixmap);
    }
}
}
