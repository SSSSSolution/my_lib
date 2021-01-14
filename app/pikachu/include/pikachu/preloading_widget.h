#ifndef REALITY_PIKACHU_PRELOADING_WIDGET_H
#define REALITY_PIKACHU_PRELOADING_WIDGET_H

#include <QSplashScreen>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>

namespace reality
{
namespace pikachu
{
    class PreloadingWindget : public QSplashScreen
    {
        Q_OBJECT
    public:
        PreloadingWindget(QApplication *app);
        ~PreloadingWindget();

        void init();
        QRect &get_last_geometry();

        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;
        virtual void mouseMoveEvent(QMouseEvent *event) override;

    private:
        QTimer m_raise_timer;
        QTimer m_close_timer;

        // for show
        bool m_first_mouse_move = true;
        // for move widget
        bool m_mouse_pressed;
        QPoint m_mouse_last_pos;
        // for last geometry
        QRect m_last_geometry;
    };
}
}

#endif
