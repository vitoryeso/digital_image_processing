#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

void equalize(cv::Mat& plane, cv::Mat& hist);
int main(int argc, char** argv) {
  cv::VideoCapture cap("http://192.168.0.13:8080/video");
  cv::Mat frame;
  cv::Mat hist;
  int dark_lv(255);
  char c;

  int nbins(64);
  int histh(nbins/2), histw(nbins);
  float range[] = {0, 255};
  const float* histRange = { range };
  
  cv::Mat histImg(histh, histw, CV_8UC1, cv::Scalar(0));

  while(1) {
    cap >> frame;
    cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);

    cv::calcHist(&frame, 1, 0, cv::Mat(), hist, 1, &nbins, &histRange, true, false);

    cv::normalize(hist, hist, 0, histh, cv::NORM_MINMAX, -1, cv::Mat()); /* dtype = -1 para o output ter o msm tipo do hist de input */

    histImg.setTo(cv::Scalar(0));

    for(int i=0; i<nbins; i++) {
        cv::line(histImg, cv::Point(i, histh), cv::Point(i,histh - cvRound(hist.at<float>(i))), cv::Scalar(255), 1, 8, 0);
    }

    histImg.copyTo(frame(cv::Rect(0, 0, nbins, histh)));

    /* aplicando algum escurecimento na imagem pra ver o efeito da equalizacao */
    cv::normalize(frame, frame, 0, dark_lv, cv::NORM_MINMAX, -1, cv::Mat());
    cv::imshow("cam", frame);
    equalize(frame, hist);
    cv::imshow("equalized", frame);
    c = cv::waitKey(30);
    if(c == 27) break;
    if(c == 104) {
      if(dark_lv > 10) dark_lv -= 10;
      else dark_lv = 0;
    }
    if(c == 108) {
      if(dark_lv < 245) dark_lv += 10;
      else dark_lv = 255;
    }


  }
}

/* vai receber o frame e o histograma do frame, calcular o histograma acumulado, e fazer a equalizacao no frame */
void equalize(cv::Mat& plane, cv::Mat& hist) {
  cv::Mat histAcc(hist.clone());
  for(int i=1; i<hist.cols; i++) {
    hist.at<float>(i) += hist.at<float>(i - 1);
  }
  for(int i=0; i<plane.rows; i++) {
    for(int j=0; j<plane.cols; j++) {
      plane.at<uchar>(i, j) = (uchar)hist.at<float>(plane.at<uchar>(i, j));
    }
  }
}
