#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

typedef std::pair<unsigned, unsigned> upair;

/* retorna a media dos valores nao-brancos dos vizinhos */
unsigned maior_ocorrencia(cv::Mat& img, cv::Point p);

/* retorna um vizinho branco se nao tiver retorna o ponto recebido*/
cv::Point vizinho_branco(cv::Mat& img, cv::Point p);


/* input: imagem resultante do pontilismo.cpp
 * output: imagem com os pontos dilatados (possivel sobreposicao)
 *
 * pra isso vamos usar o canny.cpp para pegar as bordas dos pontos e depois dilatalos
*/

int main(int argc, char** argv) {
  cv::Mat img_pontilhada, img_canny;

  //std::string cmd = "./canny " + filename;
  char cmd[100] = "./pratica/canny ";
  strcat(cmd, argv[1]);

  
  std::cout << "COMANDO: " << cmd << std::endl;
  /* executando o canny */
  std::system(cmd);

  img_pontilhada = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  if(img_pontilhada.rows <= 0) std::cout << "NAO LEU IMAGEM PONTILHADA" << std::endl;

  img_canny = cv::imread("./cannyborders.png", cv::IMREAD_GRAYSCALE);
  if(img_canny.rows <= 0) std::cout << "NAO LEU IMAGEM CANNY" << std::endl;

  /* aqui comeca */
  /* primeiro vamos varrer a imagem, procurando os pontos de borda. provavelmente pixels de valor 255
   * depois vamos contar quantas bordas bem definidas tem usando o FloodFill
   * pra cada borda dessa, vamos procurar algum valor dentro dela na imagem pontilhada
   * depois pegamos essa mesma posicao + algum raio e preenchemos com as mesmas cores da imagem pontilhada (deve estar em brancho nesses pontos */

  cv::Mat mask = cv::Mat::zeros(img_pontilhada.rows, img_pontilhada.cols, CV_8UC1);

  std::cout << "img height: " << img_canny.rows << std::endl;
  std::cout << "img width: " << img_canny.cols << std::endl;

  cv::imshow("imagem pontilhada antes", img_pontilhada);

  int count(1), count2(0);
  for (int i=0; i<img_canny.rows; i++) {
    for (int j=0; j<img_canny.cols; j++) {
      if (img_canny.at<uchar>(i, j) == 255) {
        count2++;
        if (count%3 == 0 || 1) {
          cv::circle(img_pontilhada, /*vizinho_branco(img_pontilhada,*/ cv::Point(j, i), 3, 
              maior_ocorrencia(img_pontilhada, cv::Point(j, i)),
              cv::FILLED, 8, 0);
          count = 1;
        }
        else count++;
      }
    }
  }
  std::cout << "COUNT BRANCOS: " << count2 << std::endl;


  //cv::addWeighted(mask, alpha, img_pontilhada, beta, 0.0, img_pontilhada);



  cv::imshow("imagem pontilhada depois", img_pontilhada);
  cv::imshow("bordas de canny", img_canny);

  cv::imwrite("cannypoints_output1.png", img_pontilhada);

  cv::waitKey(0);

  return 0;
}

unsigned maior_ocorrencia(cv::Mat& img, cv::Point p) {
  std::vector<unsigned> V;
  std::set<unsigned> S;
  cv::Point P;

  upair w[8] = {upair(1,1), upair(1, 0), upair(0, 1), upair(-1, -1), 
    upair(-1, 0), upair(0, -1), upair(1, -1), upair(-1, 1)};

  unsigned val;
  for (int i=0; i<8; i++) {
    P.y = p.y + w[i].first;
    P.x = p.x + w[i].second;
    if (P.y < 0 || P.y >= img.cols) continue;
    if (P.x < 0 || P.x >= img.rows) continue;

    val = img.at<uchar>(P.y, P.x);
    if (val < 235) V.push_back(val);
  }
  for (int i=0; i<(int)V.size(); i++) {
    S.insert(V[i]);
  }
  unsigned max_occurrences(0), occurrences;
  for (int s : S) {
    occurrences = std::count(V.begin(), V.end(), s);
    if (occurrences > max_occurrences) {
      max_occurrences = occurrences;
      val = s;
    }
  }

  return val;
}

cv::Point vizinho_branco(cv::Mat& img, cv::Point p) {
  cv::Point P;
  unsigned val;
  upair w[8] = {upair(1,1), upair(1, 0), upair(0, 1), upair(-1, -1), 
    upair(-1, 0), upair(0, -1), upair(1, -1), upair(-1, 1)};

  for (int i=0; i<8; i++) {
    P.y = p.y + w[i].first;
    P.x = p.x + w[i].second;
    if (P.y < 0 || P.y >= img.cols) continue;
    if (P.x < 0 || P.x >= img.rows) continue;

    val = img.at<uchar>(P.y, P.x);
    if (val == 255) return P;
  }

  return p;
}
