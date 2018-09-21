#include "coisas.h"

//TSP

  /* Insere City no TSP
  * inputs: trabaler, city
  * outputs:  nenhum
  * pré-condicao: existencia e alocação do trabaler e do city, indice valido
  * pós-condicao: City registrado no traveler no indice do mesmo -1
  pois a primeira cidade será sempre a cidade 1*/
  Tsp* insereCity (Tsp* tsp, City* p) {
      tsp->arrayCity[(p->index)] = p;
      return tsp;
  }

  /* Cria city
  * inputs: Numero da cidade, coordenadas x e y
  * outputs: City devidamente alocado
  * pré-condicao: os campos enviados existem
  * pós-condicao: City criado*/
  City* criaCity(int ind, float x, float y) {
    City* p = (City*) malloc(sizeof(p));
    p->index = ind;
    p->x = x;
    p->y = y;
    return p;
  }

  /* Imprime city
  * inputs: City que deve ser impresso
  * outputs: nenhum
  * pré-condicao: City devidadmente alocado
  * pós-condicao: dados referentes ao City printados na tela*/
  void imprimeCity(City* p) {
    printf("City índice: %d | X=%.1f | Y=%.1f \n", p->index, p->x, p->y);
  }

  /*Aloca e preenche os dados do traveler
  * inputs: nome, tipo de grafo dado por entrada(sempre sera TSP),
  tipo de peso dos arcos (sempre sera EUC_2D), dimensão(quantidade de cidades)
  * outputs: traveler alocado e preenchido com seus daods
  * pré-condicao: os campos enviados existem
  * pós-condicao: traveler alocado e preenchido com seus daods*/
  Tsp* criaTsp(char* nome, char* type, char* edgeWeightType, int dimension) {
    Tsp* tsp = (Tsp*) malloc(sizeof(Tsp));

    tsp->arrayCity = (City**) malloc((dimension + 1)*sizeof(City*));
    tsp->nome = strdup(nome);
    tsp->type = strdup(type);
    tsp->edgeWeightType = strdup(edgeWeightType);
    tsp->dimension = dimension;

    return tsp;
  }

  /* Printa na tela o traveler e seus city
  * inputs: traveler
  * outputs: nenhum
  * pré-condicao: traveler devidamente alocado e preenchido
  * pós-condicao: dados do traveler printados na tela*/
  void imprimeTsp (Tsp* tsp) {
    int dimension = tsp->dimension;
    printf("Name: %s \nTYPE: %s  \nEdge: %s \nDimension: %d \n", tsp->nome, tsp->type, tsp->edgeWeightType, dimension);
    for (int i = 1; i <= dimension; i++) {
      imprimeCity(tsp->arrayCity[i]);
    }
    printf("\n\n");
  }



//EDGE

  int distance(City* a, City* b){
      int dist = sqrt( pow((a->x - b->x),2) + pow((a->y - b->y),2) );
      return dist;
  }

  int compara(const void* x, const void* y) {
      int ret;

      Edge* edgeX = (Edge*) x;
      Edge* edgeY = (Edge*) y;

      ///printf("Comparando as distâncias %d e %d\n", edgeX->distance, edgeY->distance);
      ret = (edgeX->distance - edgeY->distance);
      return ret;
  }



//TOUR

  int prox_Tour(int ultimo, Edge* arvMinima, int dimension ){
      for(int i = 0; i < dimension; i++){
          if(arvMinima[i].ori == i) return 1;
      }

      return 0;
  }

  int contidoNoTour(int* vetTour, Edge e, int indice_tour ){
      //printf("test\n" );
      for(int i = 0; i <= indice_tour; i++){
          if(vetTour[i] == e.ori) return 1;
      }

      return 0;
  }



//AUXILIARES

  Tsp* leArquivo(FILE* entrada, Tsp* arv) {
    char type[10], edgeWeightType[20], nome[40],comentario[20];
    int dimension;

    fscanf(entrada, "NAME: %s\n", nome);

    while (strcmp(comentario, "TYPE:") != 0) {
      //printf("ignorando o comentario\n");
      fscanf(entrada, "%s", comentario);
    }

    fscanf(entrada, " %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\nNODE_COORD_SECTION\n", type, &dimension, edgeWeightType);
    arv = criaTsp(nome, type, edgeWeightType, dimension);

    for (int i = 0; i <= dimension; ++i) {
      int index;
      float x, y;
      fscanf(entrada, "%d %f %f\n", &index, &x, &y);

      insereCity(arv, criaCity(index, x, y));
    }
    return arv;
  }

  Edge* criaVetorAresta(Tsp* arv, int tam) {
    Edge* vetEdge = (Edge*)malloc((tam+1)*sizeof(Edge));

    int cont = 1;
    for(int i = 1; i < arv->dimension; i++) {
      for(int j = i+1; j <= arv->dimension; j++) {
        vetEdge[cont].distance = distance(arv->arrayCity[i], arv->arrayCity[j]);
        vetEdge[cont].ori = i;
        vetEdge[cont].dest = j;
        vetEdge[cont].check = 0;
        cont++;
      }
    }

    //printf("%d\n",cont );

    printf("Sortando os valores do vetor\n");
    qsort(vetEdge, tam, sizeof(Edge), compara);
    printf("Valores do vetor sortados\n");

    return vetEdge;
  }

/*
* inputs:
* outputs:
* pré-condicao:
* pós-condicao:



24 48
35 36
34 35
5 15
5 24
5 6
20 50
38 40
37 40
39 40
36 39
24 38
2 7
1 22
5 48
38 48
32 49
15 24
6 24
34 39
37 48
15 38
1 49
8 41
4 6
6 48
15 48
19 45
7 42
34 37
24 40
18 31
34 44
40 48
36 49
9 10
35 49
36 37
36 40
6 38
1 32
15 40
19 41
34 40
22 49
20 23
35 44
15 37
4 5
22 31
34 49
4 25
*/
