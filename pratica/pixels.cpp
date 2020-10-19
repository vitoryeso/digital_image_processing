#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat img;
    Vec3b val; /* tipo Vec3b que eh tipo um vector. usado para armazenar quantidades pequenas de valores */
    

    img = imread(argv[1], IMREAD_GRAYSCALE);
    if(!img.data) /* verificando se a imagem leu. data contem os bytes brutos da imagem */
        cout << "a imagem nao abriu" << endl;

    /* iniciando a janela */
    namedWindow("window", WINDOW_AUTOSIZE);


    /* vamos acessar os pixels da imagem
     * a estrutura Mat contém os bytes, e devemos escolher a estrutura que esses bytes serao lidos 
     * como vamos ler a imagem em grayscale, o tipo dos dados estarao em `unsigned char` ou `uchar` */
    for(unsigned i=90; i<100; i++) {
        for(unsigned j=10; j<200; j++) {
            /* atribuindo a cor preta */
            img.at<uchar>(i, j) = 0;
        }
    }
    
    imshow("window", img);
    waitKey();

    /* agora vamos fazer o msm com a imagem colorida */

    /* iniciando uma cor no formato BGR*/
    val[0] = 255;
    val[1] = 0;
    val[2] = 255;

    img = imread(argv[1], cv::IMREAD_COLOR);
    
    /* para imagens coloridas, ler no formato Vec3b */
    for(unsigned i=90; i<100; i++) {
        for(unsigned j=10; j<200; j++) {
            img.at<Vec3b>(i, j) = val;
        }
    }
    imshow("window", img);
    waitKey(); 

    return 0;
}
