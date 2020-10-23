#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  cv::Mat img(256, 256, CV_8UC1, 250);
  cv::Mat hist;
  
  char c;

  cv::Mat region1(31, 31, CV_8UC1, 70);
  cv::Mat region2(63, 63, CV_8UC1, 170);

  region2.copyTo(img(cv::Rect(128, 128, 63, 63)));
  region1.copyTo(img(cv::Rect(144, 144, 31, 31)));

  float counts[] = {0.0, 0.0, 0.0};
  for(int i=0; i<256; i++) {
    for(int j=0; j<256; j++) {
      if(img.at<uchar>(i, j) == 150) counts[2] += 1.0; 
      if(img.at<uchar>(i, j) == 70) counts[1] += 1.0; 
      if(img.at<uchar>(i, j) == 20) counts[0] += 1.0; 
    }
  }
  cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());  
  
  counts[1] += counts[0];
  counts[2] += counts[1];

  cv::imshow("img antes", img);

  for(int i=0; i<256; i++) {
    for(int j=0; j<256; j++) {
      if(img.at<uchar>(i, j) == 150) img.at<uchar>(i, j) = (uchar)counts[2];
      if(img.at<uchar>(i, j) == 70) img.at<uchar>(i, j) = (uchar)counts[1];
      if(img.at<uchar>(i, j) == 20) img.at<uchar>(i, j) = (uchar)counts[0];
    }
  }

  cv::imshow("img dps", img);
  while(1) {
    c = cv::waitKey();
    if(c == 27) break;
  }  
}
