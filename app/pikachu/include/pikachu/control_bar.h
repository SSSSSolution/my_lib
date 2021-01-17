#ifndef REALITY_PIKACHU_CONTROL_BAR_H
#define REALITY_PIKACHU_CONTROL_BAR_H

#include <QWidget>
#include <QPushButton>
#include <QString>

#include "conversion_handle.h"

namespace reality
{
    namespace pikachu
    {
    class ControlBar : public QWidget
    {
        Q_OBJECT
    public:
        ControlBar(ConversionHandle *handle, QWidget *parent);

    private:
        QPushButton *m_load_btn;
        QPushButton *m_conversion_gray_btn;
        QPushButton *m_reverse_btn;

        QPushButton *m_gen_ascii_by_gray;
        QPushButton *m_save_btn;

        ConversionHandle *m_handle;
    };
    }
}


#endif
