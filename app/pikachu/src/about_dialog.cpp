#include "about_dialog.h"

#include <QVBoxLayout>
#include <QLabel>

namespace reality
{
    namespace pikachu
    {
    AboutDialog::AboutDialog(QWidget *parent)
        : QMessageBox(parent)
    {
//        QVBoxLayout *layout = new QVBoxLayout(this);
//        layout->setContentsMargins(0, 10, 0, 10);

//        QLabel *version_label = new QLabel(this);
//        version_label->setText("Version: 1.0.0");
//        QLabel *copy_right_label = new QLabel(this);
//        copy_right_label->setText("Author: Wei Huang\nCopyright (C) 2021 Wei Huang");

//        layout->addWidget(version_label, Qt::AlignCenter);
//        layout->addWidget(copy_right_label, Qt::AlignCenter);

        setText("Version: 1.0.0\nAuthor: Wei Huang\nCopyright (C) 2021 Wei Huang");
        setWindowTitle("About Pikachu");
    }
    }
}
