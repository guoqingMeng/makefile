
#include "test1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
using namespace cv;
void A::fun()
{
    printf("%s\n", "test!");
    cv::Mat image(cv::Size(100,100), CV_8UC3, cv::Scalar(100));
    if (image.empty())
    {
        return;
    }
    cv::imshow("image", image);
    cv::waitKey(0);
}