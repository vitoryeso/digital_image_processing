#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat img;
    unsigned xmin, ymin, xmax, ymax;

    cout << "type two points (xmin, ymin, xmax, ymin)" << endl;
    cin >> xmin >> ymin >> xmax >> ymax;

    namedWindow("image", WINDOW_AUTOSIZE);
    img = imread(argv[1], IMREAD_COLOR);
    for(unsigned i=ymin; i<=ymax; i++) {
        for(unsigned j=xmin; j<=xmax; j++) {
            img.at<Vec3b>(i, j)[0] = 255 - img.at<Vec3b>(i, j)[0]; 
            img.at<Vec3b>(i, j)[1] = 255 - img.at<Vec3b>(i, j)[1]; 
            img.at<Vec3b>(i, j)[2] = 255 - img.at<Vec3b>(i, j)[2]; 
        }
    }
    imshow("image", img);
    waitKey();
}
