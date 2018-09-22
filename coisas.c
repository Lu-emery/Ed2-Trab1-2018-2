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
  City* criaCity (int ind, float x, float y) {
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
  void imprimeCity (City* p) {
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
//


//EDGE

  int distance (City* a, City* b){
      int dist = sqrt( pow((a->x - b->x),2) + pow((a->y - b->y),2) );
      return dist;
  }

  int compara (const void* x, const void* y) {
      int ret;

      Edge* edgeX = (Edge*) x;
      Edge* edgeY = (Edge*) y;

      ///printf("Comparando as distâncias %d e %d\n", edgeX->distance, edgeY->distance);
      ret = (edgeX->distance - edgeY->distance);
      return ret;
  }



//Vertice adj
  Vertice** preencheVetorVertice (Edge* arvMinima, int dimension) {
      Vertice** vetorVertice = (Vertice**) calloc(dimension, sizeof(Vertice*));


      for(int i = 0; i < dimension; i++){
          insereEmVetorVertices(vetorVertice, arvMinima[i]);
      }

      return vetorVertice;
  }

  void insereEmVetorVertices (Vertice** vet, Edge entrada) {
    int indiceOri = entrada.ori;
    int indiceDest = entrada.dest;
    //Checa se Ori existe
    if (vet[indiceOri] == NULL) {
      // printf("Criou um vertice origem [%d]\n", indiceOri);
      vet[indiceOri] = malloc(sizeof(Vertice));
      vet[indiceOri]->indice = indiceOri;
      vet[indiceOri]->pilhaAdjacentes = NULL;
    }
    //Checa se Dest existe
    if (vet[indiceDest] == NULL) {
      // printf("Criou um vertice destino [%d]\n", indiceDest);
      vet[indiceDest] = malloc(sizeof(Vertice));
      vet[indiceDest]->indice = indiceDest;
      vet[indiceDest]->pilhaAdjacentes = NULL;
    }
    //Cria a estrutura Adjacência do vértice destino
    Adjacencia* a = criaAdjacencia(vet[indiceDest]);
    //Faz ele ser o primeiro elemento da pilha de adjacência do vértice origem
    a->prox = vet[indiceOri]->pilhaAdjacentes;
    vet[indiceOri]->pilhaAdjacentes = a;
    a = criaAdjacencia(vet[indiceOri]);
    a->prox = vet[indiceDest]->pilhaAdjacentes;
    vet[indiceDest]->pilhaAdjacentes = a;
    //printf("Vertice Teste %d\n", vet[indiceOri]->pilhaAdjacentes->vertice->indice);
  }

  Adjacencia* criaAdjacencia (Vertice* vert) {
    Adjacencia* a = (Adjacencia*) malloc(sizeof(Adjacencia));
    a->vertice = vert;
    a->prox = NULL;
    return a;
  }

 //Tour
 #define branco 1
 #define preto 0
 #define cinza -1

   void DFS(Vertice** vet, int dimension){
     for(int i = 1; i < dimension; i++){
       vet[i]->cor = branco;
     }

    DFS_Visit(vet[1]);
   }

   void DFS_Visit(Vertice* vert){
     printf("%d\n", vert->indice);
     vert->cor = cinza;
     Adjacencia* aux = vert->pilhaAdjacentes;

     while(aux != NULL){
         if(aux->vertice->cor == branco){
             DFS_Visit(aux->vertice);
         }
         aux = aux->prox;
     }

     vert->cor = preto;
   }


//AUXILIARES

  Tsp* leArquivo (FILE* entrada, Tsp* arv) {
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

  Edge* criaVetorAresta (Tsp* arv, int tam) {
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
