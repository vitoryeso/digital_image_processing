### Detecção de Bordas com o Algoritmo de Canny

![Diagrama Canny](imgs/blockdiag_canny.png "Diagrama de Blocos Canny")

Primeiramente é feito um borramento na imagem com um **filtro Gaussiano**, para reduzir _pixels_ ruidosos, que podem comprometer o funcionamento do detector de bordas, assim como compromete o funcionamento de diversos algoritmos de processamento de imagens. Após isso, é calculado o gradiente da imagem, resultando em vetores para cada _pixel_ da imagem. Esses vetores terão os seus ângulos classificados em intervalos de angulação menores.

Depois dessa primeira etapa, podemos utilizar as classificações dos ângulos para verificar se _pixels_ vizinhos estão apontando para a mesma direção e posteriormente aplicamos um sub-algoritmo chamado de Supressão de não-máximos, que anota em uma outra imagem (chamada de imagem de não-máximos) algum valor para os _pixels_ que são máximos locais (comparados com os seus vizinhos) e um valor nulo para os que não forem máximos locais.

Com isso, a etapa final é a de limiarização na imagem de não-máximos, para traçãr melhor as bordas (podem ficar com alguns buracos antes dessa etapa). Essa limiarização é feita com dois limiares (<img src="https://render.githubusercontent.com/render/math?math=T_1"> e <img src="https://render.githubusercontent.com/render/math?math=T_2">) em que os _pixels_ que passarem pelo limiar <img src="https://render.githubusercontent.com/render/math?math=T_1"> serão denominados de pontos de borda forte. Os _pixels_ que não são pontos de borda forte, mas que passem do segundo limiar <img src="https://render.githubusercontent.com/render/math?math=T_2"> são chamados de pontos de borda fraca. Após isso, verificamos se existe algum ponto de borda forte na vizinhança de todos os pontos de borda fraca, se tiver, ligamos os pontos. Dessa forma temos bordas mais bem definidas no nosso algoritmo.

### Canny e a arte do Pontilhismo

Apesar do algoritmo de Canny ter diversas utilidades e aplicações, vamos explorar o seu uso no aprimoramento de uma técnica de pintura conhecida como Pontilhismo. Essa técnica se da na pintura de quadros utilizando apenas pontos, como podemos ver nessa pintura de [George Seurat](https://en.wikipedia.org/wiki/Georges_Seurat).

![EiffelTower](https://www.georgesseurat.org/thumbnail/80000/80434/mini_normal/The-Eiffel-Tower-1889.jpg?ts=1459229076 "Eiffel Tower")

Para simular esse efeito em imagens digitais, podemos simplesmente varrer toda a imagem, e ir pintando uma imagem (inicialmente em branco) com circulos preenchidos com valores respectivos a imagem original, como pode ser visto nesse exemplo:

<img style="float: left;" src="imgs/luffy2_gray.jpg">
<img style="float: right;" src="imgs/luffy2.jpg">

Podemos ver quer essa implementação não foi tão bem fiel a técnica do pontilhismo, tendo em vista que alguns pontos da imagens possuem lacunas, o que não deixa a imagem tão atraente. Aqui que entra o algoritmo de Canny.

O algoritmo de Canny pode ser utilizado para encontrar as bordas dos pontos desenhados, e com isso, criar uma melhoria na imagem, pintando também próximo as bordas dos pontos.

### Canny + Pontilhismo
