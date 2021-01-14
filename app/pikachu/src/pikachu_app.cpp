#include "pikachu_app.h"

#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

namespace reality
{
    namespace pikachu
    {
        PikachuApplication::PikachuApplication(int argc, char **argv)
            :QApplication(argc, argv)
        {

        }

        void PikachuApplication::add_mouse_move_cb(std::function<void(QMouseEvent *)> f)
        {
            m_mouse_move_cbs.push_back(f);
        }

        bool PikachuApplication::notify(QObject *obj, QEvent *e)
        {
            if (e->type() == QEvent::MouseMove)
            {
                auto move_e = dynamic_cast<QMouseEvent *>(e);
                qDebug() << "mouse move event: " << move_e->pos();
                for (auto f : m_mouse_move_cbs)
                {
                    f(move_e);
                }
            }
            return QApplication::notify(obj, e);
        }
    }
}
