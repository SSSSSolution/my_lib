#ifndef REALITY_CHARIZARD_RENDER_HANDLE_H
#define REALITY_CHARIZARD_RENDER_HANDLE_H

#include <memory>
#include <QObject>
#include <QPoint>
#include "soft_renderer.h"
#include "model.h"
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
            void draw_line(const QPointF &start, const QPointF &end);
            void draw_unit_cube();

        signals:
            void draw();

        private:
            PresentImage present_image;
            std::unique_ptr<UnitCubeModel> m_unit_cube_model;
        };
    }
}













#endif
