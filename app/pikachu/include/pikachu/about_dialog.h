#ifndef REALITY_PIKACHU_ABOUT_DIALOG_H
#define REALITY_PIKACHU_ABOUT_DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
namespace reality
{
    namespace pikachu
    {
    class AboutDialog : public QMessageBox
    {
        Q_OBJECT
    public:
        AboutDialog(QWidget *parent);

    private:
    };
    }
}




#endif
