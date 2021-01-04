#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: display_image <Image_Path>\n");
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], 1);

    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    cv::namedWindow("Display Image", WINDOW_GUI_EXPANDED);
    imshow("Display Image", image);

    waitKey(0);
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    std::cout << "M = " << std::endl << M << std::endl << std::endl;
    Mat E = Mat::eye(4, 4, CV_64F);
    std::cout << "eye = " << std::endl << E << std::endl;

    Mat O = Mat::ones(2, 2, CV_32F);
    std::cout << "O = " << std::endl << O << std::endl;

    Mat Z = Mat::zeros(3, 3, CV_8UC1);
    std::cout << "Z = " << std::endl << Z << std::endl;
    return 0;
}
