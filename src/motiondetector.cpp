#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
  cv::VideoCapture cap("http://192.168.0.13:8080/video");
  cv::Mat frame;
  char c;

  cv::Mat hist, lastHist;
  int nbins(64);
  int histh(nbins/2), histw(nbins);
  float range[] = {0, 255};
  const float* histRange = { range };

  cv::Mat histImg(histh, histw, CV_8UC1, cv::Scalar(0));

  cv::Mat provMat;
  float mean(0.0), thresh(30.0);

  while(1) {
    cap >> frame;
    cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);

    cv::calcHist(&frame, 1, 0, cv::Mat(), hist, 1, &nbins, &histRange, true, false);
    cv::normalize(hist, hist, 0, histh, cv::NORM_MINMAX, -1, cv::Mat()); 

    histImg.setTo(cv::Scalar(0));

    for(int i=0; i<nbins; i++)
      cv::line(histImg, cv::Point(i, histh), cv::Point(i, histh- cvRound(hist.at<float>(i))), cv::Scalar(255), 1, 8, 0);

    if(lastHist.rows > 2) {
      cv::subtract(hist, lastHist, provMat, cv::Mat(), -1);
      cv::pow(provMat, 2.0, provMat);
      mean = cv::mean(provMat).val[0]; 
      if(mean > thresh) {
        cv::circle(frame, cv::Point(frame.rows/2, frame.cols/2), 50, cv::Scalar(255), 1);
      }
    }
    lastHist = hist.clone();

    histImg.copyTo(frame(cv::Rect(0, 0, nbins, histh)));

    cv::imshow("frame", frame);
    c = cv::waitKey(30);
    if(c == 27) break;
  }
}
