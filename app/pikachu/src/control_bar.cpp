#include "control_bar.h"
#include <QVBoxLayout>
#include <QObject>
#include <QFileDialog>

namespace reality
{
namespace pikachu
{
    ControlBar::ControlBar(ConversionHandle *handle, QWidget *parent)
        : QWidget(parent),
          m_handle(handle)
    {
        m_load_btn = new QPushButton("Load", this);
        connect(m_load_btn, &QPushButton::clicked, this, [this]()
        {
            QString file_path = QFileDialog::getOpenFileName(
                        this, "Open a file", "/",
                        "images(*.png *.jpeg *.bmp *.jpg)");
            if (!file_path.isEmpty())
            {
                this->m_handle->load_picture(file_path);
            }
        });

        m_conversion_gray_btn = new QPushButton("gray", this);
        connect(m_conversion_gray_btn, &QPushButton::clicked, this, [this]()
        {
            this->m_handle->conversion_to_gray();
        });

        m_reverse_btn = new QPushButton("reverse", this);
        connect(m_reverse_btn, &QPushButton::clicked, this, [this]()
        {
            this->m_handle->reverse_color();
        });

        m_gen_ascii_by_gray = new QPushButton("gen by gray", this);
        connect(m_gen_ascii_by_gray, &QPushButton::clicked, this, [this]()
        {
            this->m_handle->gen_ascii_by_gray(120);
        });

        m_save_btn = new QPushButton("save", this);
        connect(m_save_btn, &QPushButton::clicked, this, [this]()
        {
            if (!m_handle->is_valid())
            {
                return;
            }
            auto save_path = QFileDialog::getSaveFileName(this, "Save picture",
                                                          "~/", "*.jpg");
            if (!save_path.isEmpty())
            {
                this->m_handle->save_picture(save_path);
            }
        });

        auto main_layout = new QVBoxLayout(this);
        main_layout->setMargin(5);
        main_layout->addWidget(m_load_btn);
        main_layout->addWidget(m_conversion_gray_btn);
        main_layout->addWidget(m_reverse_btn);

        main_layout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding,
                                                   QSizePolicy::Expanding));
        main_layout->addWidget(m_gen_ascii_by_gray);
        main_layout->addWidget(m_save_btn);

        setMinimumWidth(500);

    }
}
}
