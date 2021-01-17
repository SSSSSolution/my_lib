#ifndef REALITY_PIKACHU_PICTURE_WIDGET_H
#define REALITY_PIKACHU_PICTURE_WIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QEvent>

#include "conversion_handle.h"

namespace reality
{
    namespace pikachu
    {
    class PictureWidget : public QWidget
    {
        Q_OBJECT
    public:
        PictureWidget(ConversionHandle * handle, QWidget *parent);

    protected:
        virtual void showEvent(QShowEvent *e) override;
        virtual void resizeEvent(QResizeEvent *e) override;

    public slots:
        void slot_load(QString file_path);

    private:
        QLabel *m_picture_label;
        QString m_picture_path;
        QPixmap m_pixmap;

        ConversionHandle *m_handle;
    };
    }
}

#endif
