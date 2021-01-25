#ifndef REALITY_CHARIZARD_RENDER_HANDLE_H
#define REALITY_CHARIZARD_RENDER_HANDLE_H

#include <memory>
#include <QObject>
#include <QPoint>
#include "soft_renderer.h"
#include "model.h"
#include "exector.h"
#include "soft_renderer.h"

namespace reality
{
    namespace charizard
    {
        class RenderHandle : public QObject
        {
            Q_OBJECT
        public:
            RenderHandle(QObject *parent);

            void set_image(std::shared_ptr<PresentImage> image);
            void draw_line(const QPointF &start, const QPointF &end);
            void draw_triangle_(const QPointF &A, const QPointF &B, const QPointF &C, SampleCount sample);
            void draw_unit_cube();

            void run();
            void stop();

            void clear();

        signals:
            void draw();

        private:
            std::shared_ptr<PresentImage> present_image;
            std::unique_ptr<UnitCubeModel> m_unit_cube_model;

            std::shared_ptr<SoftRenderer> m_renderer;
            std::unique_ptr<Exector> m_exector;
        };
    }
}













#endif
