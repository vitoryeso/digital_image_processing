#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
  cv::Mat frame;
  char c;

  cv::VideoCapture cap("http://192.168.0.13:8080/video");
  if(!cap.isOpened()) {
    std::cout << "camera indisponivel" << std::endl;
    return -1; 
  }

  int WIDTH=640, HEIGHT=480;
  cap.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);

  cv::Mat RegionA(HEIGHT/2, WIDTH/2, frame.type());
  cv::Mat RegionB(HEIGHT/2, WIDTH/2, frame.type());
  cv::Mat RegionC(HEIGHT/2, WIDTH/2, frame.type());
  cv::Mat RegionD(HEIGHT/2, WIDTH/2, frame.type());
  cv::Mat cloneFrame;

  while(1) {
    cap >> frame;

    cloneFrame = frame.clone();
    RegionA = frame(cv::Rect(0, 0, WIDTH/2, HEIGHT/2));
    RegionB = frame(cv::Rect(WIDTH/2, HEIGHT/2, WIDTH/2, HEIGHT/2)).clone();
    RegionC = frame(cv::Rect(0, HEIGHT/2, WIDTH/2, HEIGHT/2));
    RegionD = frame(cv::Rect(WIDTH/2, 0, WIDTH/2, HEIGHT/2)).clone();
    //RegionAux = RegionA;
    //RegionA.setTo(RegionB);
    //RegionB.setTo(RegionAux);
    //frame(cv::Range(0, HEIGHT/2), cv::Range(0, WIDTH/2)) = RegionB;
    //frame(cv::Range(HEIGHT/2, HEIGHT), cv::Range(HEIGHT/2, HEIGHT)) = RegionA;
    //
    RegionA.copyTo(frame(cv::Rect(WIDTH/2, HEIGHT/2, RegionA.cols, RegionA.rows)));
    RegionB.copyTo(frame(cv::Rect(0, 0, RegionA.cols, RegionA.rows)));
    RegionC.copyTo(frame(cv::Rect(WIDTH/2, 0, RegionA.cols, RegionA.rows)));
    RegionD.copyTo(frame(cv::Rect(0, HEIGHT/2, RegionA.cols, RegionA.rows)));

    cv::imshow("frame trocado", frame);
    cv::imshow("frame original", cloneFrame);

    c = cv::waitKey(30);
    if(c == 27) break;
  }
  return 0;
}
