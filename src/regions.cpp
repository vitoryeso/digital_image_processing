#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    VideoCapture cap("http://192.168.0.13:8080/video");
    if(!cap.isOpened()) cout << "camera indisponivel" << endl;

    Mat img;
    unsigned xmin, ymin, xmax, ymax;

    cout << "type two points (xmin, ymin, xmax, ymin)" << endl;
    cin >> xmin >> ymin >> xmax >> ymax;

    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    char c;
    while(1) {
      cap >> img;
      for(unsigned i=ymin; i<=ymax; i++) {
          for(unsigned j=xmin; j<=xmax; j++) {
              img.at<Vec3b>(i, j)[0] = 255 - img.at<Vec3b>(i, j)[0]; 
              img.at<Vec3b>(i, j)[1] = 255 - img.at<Vec3b>(i, j)[1]; 
              img.at<Vec3b>(i, j)[2] = 255 - img.at<Vec3b>(i, j)[2]; 
          }
      }
      imshow("image", img);
      c = waitKey(30);
      if(c == 27) break;
    }
    return 0;
}
