#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

int main(int argc, char** argv) {
    cv::Mat img;
    vector<cv::Mat> planes;
    cv::Mat histR, histG, histB;

    int nbins(64);
    int histh(nbins/2), histw(nbins);
    float range[] = {0, 255};
    const float* histRange = { range };

    img = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::split(img, planes);

    cv::Mat histImgR(histh, histw, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat histImgG(histh, histw, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat histImgB(histh, histw, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::calcHist(&planes[0], 1, 0, cv::Mat(), histR, 1, &nbins, &histRange, true, false);
    cv::calcHist(&planes[1], 1, 0, cv::Mat(), histG, 1, &nbins, &histRange, true, false);
    cv::calcHist(&planes[2], 1, 0, cv::Mat(), histB, 1, &nbins, &histRange, true, false);

    cv::normalize(histR, histR, 0, histh, cv::NORM_MINMAX, -1, cv::Mat()); /* dtype = -1 para o output ter o msm tipo do hist de input */
    cv::normalize(histG, histG, 0, histh, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(histB, histB, 0, histh, cv::NORM_MINMAX, -1, cv::Mat());

    histImgR.setTo(cv::Scalar(0));
    histImgG.setTo(cv::Scalar(0));
    histImgB.setTo(cv::Scalar(0));

    /* como normalizou, os valores estao em float */
    for(int i=0; i<nbins; i++) {
        cv::line(histImgR, cv::Point(i, histh), cv::Point(i,histh - cvRound(histR.at<float>(i))), cv::Scalar(255, 0, 0), 1, 8, 0);
        cv::line(histImgG, cv::Point(i, histh), cv::Point(i,histh - cvRound(histG.at<float>(i))), cv::Scalar(0, 255, 0), 1, 8, 0);
        cv::line(histImgB, cv::Point(i, histh), cv::Point(i,histh - cvRound(histB.at<float>(i))), cv::Scalar(0, 0, 255), 1, 8, 0);
    }

    histImgR.copyTo(img(cv::Rect(0, 0, nbins, histh)));
    histImgG.copyTo(img(cv::Rect(0, histh, nbins, histh)));
    histImgB.copyTo(img(cv::Rect(0, 2*histh, nbins, histh)));

    cv::imshow(argv[1], img);
    cv::waitKey();
}
