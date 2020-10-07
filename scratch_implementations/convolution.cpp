#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

#define WIDTH 19 
#define HEIGHT 9 

/* padding 0: no padding
 * padding 1: padding with zeros
 * padding 2: 2x padding with zeros */
void conv(cv::Mat& img, cv::Mat& kernel, cv::Mat& output, unsigned stride, unsigned padding);

float conv_window(cv::Mat& img, cv::Mat& kernel, cv::Point initial);

void printMat(cv::Mat& img);

int main(void) {
    cv::Mat A(HEIGHT, WIDTH, CV_32FC1, cv::Scalar(155));
    cv::Mat out(HEIGHT, WIDTH, CV_32FC1, cv::Scalar(0));

    cv::Mat kernel(3, 3, CV_32FC1, cv::Scalar(-1.0));
    kernel.at<float>(1, 1) = 8.0;


    conv(A, kernel, out, 1, 1);
    std::cout << "output" << std::endl;
    printMat(out);
    out.release();

    return 0;
}

void printMat(cv::Mat& A) {
    for(int i=0; i<A.rows; i++) {
        for(int j=0; j<A.cols; j++) std::cout << (float)A.at<float>(i, j) << " ";
        std::cout << std::endl;
    }
}

float conv_window(cv::Mat& img, cv::Mat& kernel, cv::Point initial) {
    float sum(0.0);
    for(int i=0; i<kernel.rows; i++) {
        for(int j=0; j<kernel.cols; j++) {
            sum += img.at<float>(i + initial.x, j + initial.y) * kernel.at<float>(i, j);
        }
    }
    return sum;
}

void conv(cv::Mat& img, cv::Mat& kernel, cv::Mat& output, unsigned stride=1, unsigned padding=1) {
    int output_width = ((img.cols - kernel.cols + 2*padding)/stride) + 1;
    int output_height = ((img.rows - kernel.rows + 2*padding)/stride) + 1;

    if(output.rows != output_height || output.cols != output_width) {
        output = cv::Mat(output_height, output_width, CV_32FC1, cv::Scalar(0));
    }

    if(padding > 0)
        cv::copyMakeBorder(img, img, padding, padding, padding, padding, CV_8UC1, cv::Scalar(0));

    printf("padded shape: (%d, %d)", img.cols, img.rows);
    printf("output shape: (%d, %d)", output.cols, output.rows);
    for(int i=0; i<=output_height; i++) {
        for(int j=0; j<=output_width; j++) {
            //std::cout << "i, j: " << i << " " << j << " => " << conv_window(img, kernel, cv::Point(i, j)) << std::endl;
            output.at<float>(i, j) = conv_window(img, kernel, cv::Point(i, j));
        }
    }
    cv::normalize(output, output, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
}
