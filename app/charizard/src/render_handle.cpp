#include "render_handle.h"

namespace reality
{
    namespace charizard
    {
    RenderHandle::RenderHandle(QObject *parent)
        : QObject(parent)
    {

    }

    void RenderHandle::set_image(uint32_t *data, int width, int height)
    {
        m_data = data;
        m_width = width;
        m_height = height;
    }

    void RenderHandle::draw_line(const QPoint &start, const QPoint &end)
    {
        assert(m_data != nullptr);
        // to do
        for (int i = 0; i < 144; i++)
        {
            emit draw();
        }
    }



    }
}
