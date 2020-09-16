#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat img;
    img = cv::imread(argv[1]);//, cv::IMREAD_GRAYSCALE);
    cv::rectangle(img, cv::Point(10, 10), cv::Point(40, 40), cv::Scalar(0, 0, 255, 255), 2);
    cv::imshow(argv[1], img);
    cv::waitKey();
    return 0;
}
