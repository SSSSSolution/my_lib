#ifndef REALITY_PIKACHU_CONVERSION_HANDLE_H
#define REALITY_PIKACHU_CONVERSION_HANDLE_H

#include <memory>
#include <vector>
#include <QObject>
#include <QImage>
#include "opencv2/opencv.hpp"

namespace reality
{
    namespace pikachu
    {
    class ConversionHandle : public QObject
    {
        Q_OBJECT
    public:
        ConversionHandle(QObject *parent);

        bool is_valid();
        void load_picture(QString path);
        void conversion_to_gray();
        void reverse_color();
        void gen_ascii_by_gray(int w);
        void save_picture(QString save_path);
        void undo() {};
        void redo() {};

    public:
        struct CharImage
        {
            std::shared_ptr<QImage> image;
            char c;
            int gray;
        };
        std::vector<std::shared_ptr<CharImage>> m_ascii_images;

    signals:
        void sig_show_picture(QString path);
        void sig_save_picture(QString path, bool success);

    private:
        std::shared_ptr<CharImage> find_char_by_average_gray(int gray);
        void init_ascii_images();

    private:
        QString m_cur_file_path;
        cv::Mat m_cur_image;
    };
    }
}












#endif
