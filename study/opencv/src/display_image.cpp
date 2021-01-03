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
    cv::namedWindow("Display Image", WINDOW_FREERATIO);
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}
