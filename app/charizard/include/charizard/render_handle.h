#ifndef REALITY_CHARIZARD_RENDER_HANDLE_H
#define REALITY_CHARIZARD_RENDER_HANDLE_H

#include <QObject>
#include <QPoint>

namespace reality
{
    namespace charizard
    {
        class RenderHandle : public QObject
        {
            Q_OBJECT
        public:
            RenderHandle(QObject *parent);

            void set_image(uint32_t *data, int width, int height);
            void draw_line(const QPoint &start, const QPoint &end);

        signals:
            void draw();

        private:
            uint32_t *m_data = nullptr;
            int m_width = 0;
            int m_height = 0;
        };
    }
}













#endif
