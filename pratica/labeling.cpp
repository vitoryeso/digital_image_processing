#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

int main(int argc, char** argv) {
    cv::Mat img, realce;
    unsigned width, height, n_objects(0), n_holes(0);

    cv::Point p;
    img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    if(!img.data) {
        cout << "erro ao carregar a imagem" << endl;
        return -1;
    }

    width = img.cols;
    height = img.rows;
    
    cout << "WIDTH: " << width << ", HEIGHT: " << height << endl;

    cv::imshow("imagem com obj nas bordas", img);

    /* primeiramente removendo os objetos nas bordas */
    /* varrendo a primeira e ultima coluna */
    for(unsigned i=0; i<height; i++) {
      if(img.at<uchar>(i, 0) == 255) 
        cv::floodFill(img, cv::Point(i, 0), 0);
      if(img.at<uchar>(i, width - 1) == 255) 
        cv::floodFill(img, cv::Point(i, width - 1), 0);
    }

    /* varrendo a primeira e ultima linha */
    for(unsigned j=0; j<width; j++) {
      if(img.at<uchar>(0, j) == 255){
        cout << "row: 0, col: " << j << endl;
        cv::waitKey(0);
        cv::floodFill(img, cv::Point(0, j), 0, 0, cv::Scalar(), cv::Scalar(), cv::FLOODFILL_MASK_ONLY);
      }
      if(img.at<uchar>(height - 1, j) == 255) {
        cv::floodFill(img, cv::Point(height - 1, j), 0);
      }
    }

    cv::imshow("imagem sem obj nas bordas", img);

    cv::waitKey(0);
    p.x = 0;
    p.y = 0;
    /* contagem de objetos. fazendo o preenchimento com o numero do objeto
     * a primeira coordenada eh varrida pra baixo
     * a segunda coordenada eh varrida pra direita */
    for(unsigned i=0; i<height; i++) {
        for(unsigned j=0; j<width; j++) {
            if(img.at<uchar>(i, j) == 255) {
                // na representacao do ponto, a coordenada x deve ser a coordenada varrida para a direita
                p.x = j;
                p.y = i;
                cv::floodFill(img, p, ++n_objects); 
            }
        }
    }

    /* fazendo um contraste para a contagem de objetos com buracos */
    p.x = 0;
    p.y = 0;
    cv::floodFill(img, p, 255);

    /* fazendo a contagem de buracos e preenchendo cada buraco para que fique visivel */
    for(unsigned i=0; i<height; i++) {
        for(unsigned j=0; j<width; j++) {
            if(img.at<uchar>(i, j) == 0) {
                p.x = j;
                p.y = i;
                n_holes++;
                cv::floodFill(img, p, 255); 
            }
        }
    }

    cout << "Numero de bolhas: " << n_objects << endl;
    cout << "Numero de buracos: " << n_holes << endl;

    cv::imshow(argv[1], img);
    cv::imwrite("imgs/contagem_bolhas.png", img);
    cv::waitKey();
}
