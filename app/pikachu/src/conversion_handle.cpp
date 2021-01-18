#include "conversion_handle.h"
#include <QDebug>
#include <QApplication>
#include <QPainter>
#include <QFontDatabase>

#include "config.h"

namespace reality
{
    namespace pikachu
    {
    ConversionHandle::ConversionHandle(QObject *parent)
        :QObject(parent)
    {
        init_ascii_images();
    }

    bool ConversionHandle::is_valid()
    {
        return !m_cur_file_path.isEmpty();
    }

    void ConversionHandle::load_picture(QString path)
    {
        qDebug() << "emit show_picture";

        auto image = cv::imread(path.toStdString(), cv::IMREAD_COLOR);
        if (!image.data)
        {
            qDebug() << "Error: can't read file " << m_cur_file_path;
            QApplication::quit();
        }

        m_cur_image.release();
        m_cur_image = image;
        m_cur_file_path = path;
        emit sig_show_picture(m_cur_file_path);
    }

    static unsigned char rgb_to_gray(int r, int g, int b)
    {
        auto gray = (r*38 + g*75 + b*15) >> 7;
        return gray;
    }

    void ConversionHandle::conversion_to_gray()
    {
        if (m_cur_file_path.isEmpty())
        {
            return;
        }
        qDebug() << "conversion to gray";

        int height = m_cur_image.rows;
        int width = m_cur_image.cols;
        int channels = m_cur_image.channels();

        cv::Mat gray_image(height, width, CV_8UC3);
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                int b = m_cur_image.data[channels * (row * width + col) + 0];
                int g = m_cur_image.data[channels * (row * width + col) + 1];
                int r = m_cur_image.data[channels * (row * width + col) + 2];
                gray_image.data[channels * (row * width + col) + 0] = rgb_to_gray(r, g, b);
                gray_image.data[channels * (row * width + col) + 1] = rgb_to_gray(r, g, b);
                gray_image.data[channels * (row * width + col) + 2] = rgb_to_gray(r, g, b);
            }
        }

        if (!imwrite("/tmp/pikachu/gray.jpg", gray_image))
        {
            qDebug() << "Error: can't save file " << m_cur_file_path;
            QApplication::quit();

        }
        m_cur_image.release();
        m_cur_image = gray_image;
        m_cur_file_path = "/tmp/pikachu/gray.jpg";
        emit sig_show_picture(m_cur_file_path);
    }

    static int reverse_color_value(int color)
    {
        return 255 - color;
    }

    void ConversionHandle::reverse_color()
    {
        if (!is_valid())
        {
            return;
        }

        qDebug() << "reverse color";

        int height = m_cur_image.rows;
        int width = m_cur_image.cols;
        int channels = m_cur_image.channels();

        cv::Mat reverse_image(height, width, CV_8UC3);
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                int b = m_cur_image.data[channels * (row * width + col) + 0];
                int g = m_cur_image.data[channels * (row * width + col) + 1];
                int r = m_cur_image.data[channels * (row * width + col) + 2];
                reverse_image.data[channels * (row * width + col) + 0] = reverse_color_value(b);
                reverse_image.data[channels * (row * width + col) + 1] = reverse_color_value(g);
                reverse_image.data[channels * (row * width + col) + 2] = reverse_color_value(r);
            }
        }

        if (!imwrite("/tmp/pikachu/reverse.jpg", reverse_image))
        {
            qDebug() << "Error: can't save file " << m_cur_file_path;
            QApplication::quit();

        }
        m_cur_image.release();
        m_cur_image = reverse_image;
        m_cur_file_path = "/tmp/pikachu/reverse.jpg";
        emit sig_show_picture(m_cur_file_path);
    }

    void ConversionHandle::gen_ascii_by_gray(int w)
    {
        if (!is_valid())
        {
            return;
        }

        qDebug() << "gen_ascii_by_gray";

        int height = m_cur_image.rows;
        int width = m_cur_image.cols;
        int channels = m_cur_image.channels();

        std::cout << "ascii image width: " << m_ascii_images[0]->image->width()
                  << "ascii image height: " << m_ascii_images[0]->image->height() << std::endl;
        int width_per_block = width / w;
        std::cout << "width_per_block: " <<width_per_block << std::endl;
        assert(width_per_block != 0);
        int height_per_block = width_per_block * m_ascii_images[0]->image->height() / m_ascii_images[0]->image->width();
        std::cout << "height_per_block: " <<height_per_block << std::endl;
        assert(height_per_block != 0);
        int h = height / height_per_block;
        std::cout << " w " << w << " h " << h << std::endl;
        std::cout << "width: " << width << " height: " << height << std::endl;

        auto text_height = m_ascii_images[0]->image->height();
        auto text_width = m_ascii_images[0]->image->width();
        cv::Mat text_image(h * text_height,
                w * text_width, CV_8UC3);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                int average_gray = 0;
                int total_gray = 0;

                int start_y = i * height_per_block;
                int end_y = (i+1) * height_per_block;
                int start_x = j * width_per_block;
                int end_x = (j + 1) * width_per_block;
                assert(end_y <= height && end_x <= width);

                for (int k = start_y; k < end_y; k++)
                {
                    for (int l = start_x; l < end_x; l++)
                    {
                        int b = m_cur_image.data[channels * (k * width + l) + 0];
                        int g = m_cur_image.data[channels * (k * width + l) + 1];
                        int r = m_cur_image.data[channels * (k * width + l) + 2];
                        int gray = rgb_to_gray(r, g, b);
                        total_gray += gray;
                    }
                }
                average_gray = total_gray / (width_per_block * height_per_block);
                auto char_image = find_char_by_average_gray(average_gray);
                std::cout << char_image->c;

                int line = 0;
                for (int o = i * text_height; o < (i+1) * text_height; o++)
                {
                    QRgb *rgb = (QRgb*)char_image->image->scanLine(line++);
                    int pos = 0;
                    for (int p = j * text_width; p < (j+1) * text_width; p++)
                    {
                        text_image.data[3 * (o * text_width * w + p) + 0] = qBlue(rgb[pos]);
                        text_image.data[3 * (o * text_width * w + p) + 1] = qGreen(rgb[pos]);
                        text_image.data[3 * (o * text_width * w + p) + 2] = qRed(rgb[pos]);
                        pos++;
                    }
                }
            }
            std::cout << std::endl;
        }
        std::cout << "text_image: " << text_image.rows << ", " << text_image.cols << std::endl;

        if (!imwrite("/tmp/pikachu/text.jpg", text_image))
        {
            qDebug() << "Error: can't save file " << m_cur_file_path;
            QApplication::quit();

        }
        m_cur_image.release();
        m_cur_image = text_image;
        m_cur_file_path = "/tmp/pikachu/text.jpg";
        emit sig_show_picture(m_cur_file_path);
    }

    void ConversionHandle::save_picture(QString save_path)
    {
        if (m_cur_file_path.isEmpty())
        {
            return;
        }

        bool success = imwrite(save_path.toStdString(), m_cur_image);
        if (!success)
        {
            qDebug() << "Error: can't save file " << m_cur_file_path;
        }

        emit sig_save_picture(save_path, success);
    }

    static bool less_then(const std::shared_ptr<ConversionHandle::CharImage> &m1,
                          const std::shared_ptr<ConversionHandle::CharImage> &m2)
    {
        return m1->gray < m2->gray;
    }

    void ConversionHandle::init_ascii_images()
    {
        QFontDatabase base;
        qDebug() << "Qt support font: ";
        for (auto fn : base.families())
        {
            qDebug() << fn;
        }

        std::cout << "ascii char: " << std::endl;
        for (int i = 32; i < 127; i++)
        {
            char c = static_cast<char>(i);
            std::cout << c << " ";

            QFont font;
            font.setPointSize(25);
            font.setFamily("Monospace");
            font.setLetterSpacing(QFont::AbsoluteSpacing, 0);

            QFontMetrics font_metrices(font);
            auto image = std::make_shared<QImage>(QSize(font_metrices.width(QString(c)),
                                                        font_metrices.height()), QImage::Format_RGB32);
            image->fill(0xffffffff);
            QPainter painter(image.get());
            painter.setPen(QColor(Qt::black));
            painter.setFont(font);

            painter.drawText(image->rect(), Qt::AlignCenter, QString(c));

            std::string file_path = "/tmp/pikachu/ascii_images/";
            std::string c_str;
            c_str.push_back(i);
            file_path.append(c_str).append(".jpg");

            auto save_image = std::make_shared<QImage>();
//            *save_image = image->copy(0, image->height() / 2 - 0.9 * image->width(), image->width(), 1.8 * image->width());
            save_image = image;
            auto res = save_image->save(QString(file_path.c_str()));

            auto cImage = std::make_shared<CharImage>();
            cImage->image = save_image;
            cImage->c = c;
            m_ascii_images.push_back(cImage);

            assert(res == true);
        }
        std::cout << std::endl;

        // gen gray map
        std::map<char, int> char_gray_map;
        for (auto char_image : m_ascii_images)
        {
            // calculate gray
            uint64_t gray_total = 0;
            for (int i = 0; i < char_image->image->height(); i++)
            {
                QRgb *line = (QRgb *)char_image->image->scanLine(i);
                for (int j = 0; j < char_image->image->width(); j++)
                {
                    gray_total += qGray(line[j]);
                }
            }
            gray_total -= char_image->image->width() * char_image->image->height() * 0.2 * 255;
            char_image->gray = gray_total / (char_image->image->width() * char_image->image->height() * 0.8);
            std::cout << "char " << char_image->c << " " << "gray: " << char_image->gray << std::endl;
        }

        std::sort(m_ascii_images.begin(), m_ascii_images.end(), less_then);
        qDebug() << "the gray sort: ";
        for (auto char_image : m_ascii_images)
        {
            std::cout << char_image->c << " gray: " << char_image->gray << std::endl;
            qDebug() << char_image->image->size();
        }
    }

    std::shared_ptr<ConversionHandle::CharImage> ConversionHandle::find_char_by_average_gray(int gray)
    {
        int i = 0;
        for (; i < m_ascii_images.size(); i++)
        {
            if (gray <= m_ascii_images[i]->gray)
            {
                break;
            }
        }
        if (i == m_ascii_images.size())
        {
            i--;
        }
        return m_ascii_images[i];
    }

    }
}



























