#include "preloading_widget.h"
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QScreen>

namespace reality
{
namespace pikachu
{
    PreloadingWindget::PreloadingWindget(QApplication *app)
        : QSplashScreen(QPixmap("/home/reality/data/images/wallhaven-7232p9.jpg"))
    {
        this->setWindowFlag(Qt::WindowStaysOnTopHint, true);
        this->setMouseTracking(true);
    }

    PreloadingWindget::~PreloadingWindget() = default;

    void PreloadingWindget::init()
    {
        auto res = connect(&m_raise_timer, &QTimer::timeout, this, [this](){
            this->show();
            this->raise();
        });
        assert(res != nullptr);
        m_raise_timer.start(10);

        bool close_me = false;
        m_close_timer.singleShot(4000, this, [this, &close_me](){
            close_me = true;
            m_last_geometry = geometry();
            this->m_raise_timer.stop();
        });

        while (!close_me)
        {
            QCoreApplication::processEvents();
        }
    }

    QRect &PreloadingWindget::get_last_geometry()
    {
        return m_last_geometry;
    }

    void PreloadingWindget::mousePressEvent(QMouseEvent *event)
    {
        m_mouse_pressed = true;
        m_mouse_last_pos = event->globalPos();
    }

    void PreloadingWindget::mouseMoveEvent(QMouseEvent *event)
    {
        if (m_mouse_pressed)
        {
            auto m_diff = event->globalPos() - m_mouse_last_pos;
            auto rect = this->geometry();
            rect.moveTo(rect.x() + m_diff.x(), rect.y() + m_diff.y());
            this->setGeometry(rect);
            m_mouse_last_pos = event->globalPos();
        }
    }

    void PreloadingWindget::mouseReleaseEvent(QMouseEvent *event)
    {
        m_mouse_pressed = false;
    }
}

}












