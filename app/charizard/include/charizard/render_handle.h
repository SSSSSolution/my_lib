#ifndef REALITY_CHARIZARD_RENDER_HANDLE_H
#define REALITY_CHARIZARD_RENDER_HANDLE_H

#include <memory>
#include <QObject>
#include <QPoint>
#include "soft_renderer.h"
#include "model.h"
#include "exector.h"
#include "soft_renderer.h"
#include "native_widget.h"
#include "scenes.h"
namespace reality
{
    namespace charizard
    {
        class RenderHandle : public QObject
        {
            Q_OBJECT
        public:
            RenderHandle(NativeRenderWidget *native_widget, QObject *parent);

            void draw_line(const QPointF &start, const QPointF &end);
            void draw_triangle_(const QPointF &A, const QPointF &B, const QPointF &C, SampleCount sample);

            void run();
            void stop();

            void clear();

        private:
            NativeRenderWidget *m_native_widget;
            std::shared_ptr<SoftRenderer> m_renderer;
            std::unique_ptr<Exector> m_exector;
            std::shared_ptr<Scenes> m_scenes;
            std::shared_ptr<std::thread> t;

            r_math::Vec2f A, B, C;
        };
    }
}













#endif
