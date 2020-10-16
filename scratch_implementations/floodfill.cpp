#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stack>

using namespace std;

void floodfill(cv::Mat& M, cv::Point p, int label);

cv::Mat M;

static void onMouse(int event, int x, int y, int flags, void* param) {
  if(event == cv::EVENT_LBUTTONDOWN) {
    unsigned b, g, r;
    b = M.at<cv::Vec3b>(y, x)[0];
    g = M.at<cv::Vec3b>(y, x)[1];
    r = M.at<cv::Vec3b>(y, x)[2];
    cout << "x: " << x << ", y: " << y << ", rgb: (" << r << ", " << g << ", " << b << ")" << endl;
  }
}

int main(int argc, char** argv) {
  M = cv::imread(argv[1], cv::IMREAD_COLOR);
  
  cv::namedWindow("img", 0);
  cv::setMouseCallback("img", onMouse, 0);
  while(1) {
    cv::imshow("img", M);
    char c = (char)cv::waitKey();
    if(c == 27) break;
  }

}

void get_neighbors();
void floodfill(cv::Mat&M, cv::Point p, cv::Vec3b label) {
  stack<cv::Point> stk; 
  stk.push(p);
  while(stk.size() > 0) {
    p.
  }
}

