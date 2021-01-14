#ifndef REALITY_PIKACHU_PIKACHU_APPLICATION_H
#define REALITY_PIKACHU_PIKACHU_APPLICATION_H

#include <QApplication>
#include <functional>
#include <vector>
#include <QMouseEvent>

namespace reality
{
    namespace pikachu
    {
        class PikachuApplication : public QApplication
        {
        public:
            PikachuApplication(int argc, char **argv);

            void add_mouse_move_cb(std::function<void(QMouseEvent *)> f);
            virtual bool notify(QObject *obj, QEvent *e) override;

        private:
            std::vector<std::function<void(QMouseEvent *)>> m_mouse_move_cbs;
        };
    }
}





#endif
