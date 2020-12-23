#include "opencv2/core/types.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <vector>
#include <iostream>

int main (int argc, char** argv) {
  cv::VideoCapture cap("http://192.168.0.33:8080/video");

  if (!cap.isOpened()) {
    return -1;
  }

  cv::Mat frame, frame_gray;

  cap >> frame;
  if (frame.empty()) {
    return -1;
  }
  cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);

  /* gerando os pontos com o algoritmo de harris-shi-tomasi */
  std::vector<cv::Point2f> p0, p1;
  cv::goodFeaturesToTrack(frame_gray, p0, 100, 0.3, 7, cv::Mat(), 7);

  /* criando uma mascara pra desenhar os pontos */
  cv::Mat mask = cv::Mat::zeros(frame.size(), frame.type());

  int c;
  while (true) {
    cv::Mat new_frame, new_gray;

    cap >> new_frame;
    if (new_frame.empty()) {
      break; 
    } 
    cvtColor(new_frame, new_gray, cv::COLOR_BGR2GRAY);

    /* lucas-kanadi algorithm */
    std::vector<uchar> status;
    std::vector<float> err;
    /* parametros para a otimizacao do algoritmo (metodo de newton) */
    cv::TermCriteria criteria = cv::TermCriteria((cv::TermCriteria::COUNT) + (cv::TermCriteria::EPS), 10, 0.03);
    cv::calcOpticalFlowPyrLK(frame_gray, new_gray, p0, p1, status, err, cv::Size(15, 15), 2, criteria); 

    std::vector<cv::Point2f> draw_points;
    /* desenhando na mascara o flow */
    for (uint i=0; i<p0.size(); i++) {
      /* verificando se fo achado um ponto novo */
      if (status[i] == 1) {
        draw_points.push_back(p1[i]); 
        cv::line(mask, p1[i], p0[i], cv::Scalar(0, 255, 0), 2);
        cv::circle(new_frame, p1[i], 5, cv::Scalar(0, 255, 0), -1);
      }
    }
    cv::Mat img;
    cv::add(new_frame, mask, img);

    cv::imshow("win", img);

    c = cv::waitKey(30);

    if (c == 'q' || c == 27) {
      break;
    }
    /* resetando os pontos */
    if (c == 's') {
      cv::goodFeaturesToTrack(new_gray, p0, 100, 0.3, 7, cv::Mat(), 7);
      mask = cv::Mat::zeros(frame.size(), frame.type());
    }
    else {
      p0 = draw_points;
    }

    frame_gray = new_gray.clone();
  }

  return 0;
}

