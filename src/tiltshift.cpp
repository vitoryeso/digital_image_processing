#include <iostream>
#include <math.h>
#include <cstdio>
#include <opencv2/opencv.hpp>

/* pegar a funcao do alfa, criar uma imagem do alfa que varia so no x
 * fazer a imagem negativa, dessa criada
 * multiplicar a do alfa com a imagem original, a negativa com a img borrada
 * somar as duas
 */
double alfa;
int d_slider = 0;
int d_slider_max = 100;

int l1_slider = -10;
int l1_slider_max = 200;

int l2_slider = 100;
int l2_slider_max = 450;

//int blur_slider = 3;
//int blur_slider_max = 13;

cv::Mat image1, blended; 
cv::Mat image_pond1, image_pond2;
cv::Mat image_32f, image_blured;
cv::Mat imageTop;

cv::Mat planes[3];
cv::Mat planes2[3];

cv::Mat alfa_img, alfa_img2;

int WIDTH, HEIGHT;


int blur_filter_size = 27;
std::vector<float> media(blur_filter_size*blur_filter_size, 
                                      (float)1/(blur_filter_size*blur_filter_size));

cv::Mat mask(blur_filter_size, blur_filter_size, CV_32F, media.data());

char TrackbarName[50];

/*
void on_trackbar_blur(int, void*) {
  if(blur_slider < 3) {
    blur_slider = 3;
  }
  if(blur_slider%2 == 0) {
    blur_slider -= 1;
  }
}
*/

double alfa_function(int x) {
  return 0.5*(std::tanh((x-l1_slider)/(double)d_slider) - std::tanh((x-l2_slider)/(double)d_slider));
}

void build_alfa_img() {
  alfa_img = cv::Mat(HEIGHT, WIDTH, CV_32F);
  alfa_img2 = cv::Mat(HEIGHT, WIDTH, CV_32F);
  
  for(int i=0; i<HEIGHT; i++) {
    for(int j=0;  j<WIDTH; j++) {
      alfa_img.at<float>(i, j) = alfa_function(i);
      alfa_img2.at<float>(i, j) = 1 - alfa_function(i);
    }
  }
  cv::imshow("alfa 1", alfa_img);
  cv::imshow("alfa 2", alfa_img2);
}

void on_trackbar_blend(int, void*){
  build_alfa_img();
  cv::split(image_32f, planes);
  cv::split(image_blured, planes2);
  for(int i=0; i<3; i++) {
    cv::multiply(alfa_img, planes[i], planes[i]);
    cv::multiply(alfa_img2, planes2[i], planes2[i]);
    cv::add(planes[i], planes2[i], planes[i]);
  }
  cv::merge(planes, 3, blended);

  blended.convertTo(blended, CV_8U);
  cv::imshow("addweighted", blended);
}

int main(int argvc, char** argv){
  image1 = cv::imread(argv[1]);
  WIDTH = image1.cols;
  HEIGHT = image1.rows;
  
  image1.convertTo(image_32f, CV_32F);
  cv::filter2D(image_32f, image_blured, image_32f.depth(), mask);

  cv::namedWindow("addweighted", 1);

  std::sprintf( TrackbarName, "d x %d", d_slider_max );
  cv::createTrackbar( TrackbarName, "addweighted",
                                      &d_slider,
                                      d_slider_max,
                                      on_trackbar_blend );
  std::sprintf( TrackbarName, "l1 x %d", l1_slider_max );
  cv::createTrackbar( TrackbarName, "addweighted",
                                      &l1_slider,
                                      l1_slider_max,
                                      on_trackbar_blend );
  std::sprintf( TrackbarName, "l2 x %d", l2_slider_max );
  cv::createTrackbar( TrackbarName, "addweighted",
                                      &l2_slider,
                                      l2_slider_max,
                                      on_trackbar_blend );
  on_trackbar_blend(d_slider, 0 );

  cv::waitKey(0);
  return 0;
}
