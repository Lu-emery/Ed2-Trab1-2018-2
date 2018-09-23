#include "coisas.h"

//MST

  /* Insere City no MST
    * inputs: trabaler, city
    * outputs:  nenhum
    * pré-condicao: existencia e alocação do trabaler e do city, indice valido
    * pós-condicao: City registrado no traveler no indice do mesmo -1
    pois a primeira cidade será sempre a cidade 1*/
  Mst* insereCity (Mst* mst, City* p) {
      mst->arrayCity[(p->index)] = p;
      return mst;
  }

  /* Cria city
    * inputs: Numero da cidade, coordenadas x e y
    * outputs: City devidamente alocado
    * pré-condicao: os campos enviados existem
    * pós-condicao: City criado*/
  City* criaCity (int ind, float x, float y) {
    City* p = (City*) malloc(sizeof(City));
    p->index = ind;
    p->x = x;
    p->y = y;
    return p;
  }

  /*Aloca e preenche os dados do traveler
    * inputs: nome, tipo de grafo dado por entrada(sempre sera MST),
    tipo de peso dos arcos (sempre sera EUC_2D), dimensão(quantidade de cidades)
    * outputs: traveler alocado e preenchido com seus daods
    * pré-condicao: os campos enviados existem
    * pós-condicao: traveler alocado e preenchido com seus daods*/
  Mst* criaMst(char* nome, char* type, char* edgeWeightType, int dimension, Mst* arv) {
    arv->arrayCity = (City**) malloc((dimension + 1)*sizeof(City*));
    arv->nome = strdup(nome);
    arv->type = strdup(type);
    arv->edgeWeightType = strdup(edgeWeightType);
    arv->dimension = dimension;

    return arv;
  }

  /* Printa na tela o traveler e seus city
    * inputs: traveler
    * outputs: nenhum
    * pré-condicao: traveler devidamente alocado e preenchido
    * pós-condicao: dados do traveler printados na tela*/
  void imprimeMst (Edge* arvMinima, Mst* mst, FILE* saida) {
    int dimension = mst->dimension;
    fprintf(saida, "Name: %s \nTYPE: %s  \nEdge: %s \nDimension: %d \nMST_SECTION \n", mst->nome, mst->type, mst->edgeWeightType, dimension);

    for (int i = 0; i < dimension-1; i++) {
      imprimeEdge(arvMinima[i], saida);
    }
    fprintf(saida, "EOF\n");
    printf("MST Imprimida com sucesso\n\n");
  }


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

  void imprimeEdge(Edge edge, FILE* saida) {
    fprintf(saida, "%d %d\n", edge.ori, edge.dest);
  }

//VERTICES E ADJACÊNCIAS
  Vertice** preencheVetorVertice (Edge* arvMinima, int dimension) {
      Vertice** vetorVertice = (Vertice**) calloc(dimension+1, sizeof(Vertice*));
      for(int i = 0; i < dimension-1; i++) {
          insereEmVetorVertices(vetorVertice, arvMinima[i]);
      }
      return vetorVertice;
  }

  void insereEmVetorVertices (Vertice** vet, Edge entrada) {
    int indiceOri = entrada.ori;
    int indiceDest = entrada.dest;
    //printf(" %d %d\n", entrada.ori, entrada.dest);
    //Checa se Ori existe
    if (vet[indiceOri] == NULL) {
      // printf("Criou um vertice origem [%d]\n", indiceOri);
      vet[indiceOri] = (Vertice*) malloc(sizeof(Vertice));
      vet[indiceOri]->indice = indiceOri;
      vet[indiceOri]->pilhaAdjacentes = NULL;
      //vet[indiceOri]->cor = branco; //para a DFS
    }
    //Checa se Dest existe
    if (vet[indiceDest] == NULL) {
      // printf("Criou um vertice destino [%d]\n", indiceDest);
      vet[indiceDest] = (Vertice*) malloc(sizeof(Vertice));
      vet[indiceDest]->indice = indiceDest;
      vet[indiceDest]->pilhaAdjacentes = NULL;
      //vet[indiceDest]->cor = branco; //para a DFS
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

 //TOUR

  void DFS (Vertice** vet, int dimension, FILE* saida) {
    for(int i = 1; i <= dimension; i++){
      vet[i]->cor = branco;
    }
      DFS_Visit(vet[1], saida);
    }

  void DFS_Visit (Vertice* vert, FILE* saida) {
    fprintf(saida, "%d\n", vert->indice);
    vert->cor = cinza;
    Adjacencia* aux = vert->pilhaAdjacentes;

    while(aux != NULL) {
      if(aux->vertice->cor == branco) {
        DFS_Visit(aux->vertice, saida);
      }
    aux = aux->prox;
  }

    vert->cor = preto;
  }

   void imprimeTour (Vertice** vet, Mst* mst, FILE* saida) {

     //Imprime cabeçalho
     fprintf(saida, "Name: %s \nTYPE: Tour  \nEdge: %s \nDimension: %d \nTour_SECTION \n", mst->nome, mst->edgeWeightType, mst->dimension);

     DFS(vet, mst->dimension, saida);
     fprintf(saida,"EOF\n");
     printf("Tour imprimido com sucesso\n");


   }


//AUXILIARES

  Mst* leArquivo (FILE* entrada, Mst* arv) {
    char type[10], edgeWeightType[20], nome[40], comentario[20];
    int dimension;

    fscanf(entrada, "NAME: %s\n", nome);

    do {
      //printf("ignorando o comentario\n");
      fscanf(entrada, "%s", comentario);
    } while (strcmp(comentario, "TYPE:") != 0);

    fscanf(entrada, " %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\nNODE_COORD_SECTION\n", type, &dimension, edgeWeightType);
    arv = criaMst(nome, type, edgeWeightType, dimension, arv);

    for (int i = 0; i < dimension; ++i) {
      int index;
      float x, y;
      fscanf(entrada, "%d %f %f\n", &index, &x, &y);

      insereCity(arv, criaCity(index, x, y));
    }
    return arv;
  }

  Edge* criaVetorAresta (Mst* arv, int tam) {
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

    qsort(vetEdge, tam, sizeof(Edge), compara);

    return vetEdge;
  }

  //free all
  Mst* freeMst(Mst* arv) {
    free(arv->nome);
    free(arv->type);
    free(arv->edgeWeightType);
    for(int i = 0; i <= arv->dimension; i++) {
      if (arv->arrayCity[i] != NULL) {
         free(arv->arrayCity[i]);
      }
    }
    free(arv->arrayCity);
    free(arv);
    return NULL;
  }

  Vertice** freeVetorVertices(Vertice** vert, int dimension) {
    for(int i = 1; i <= dimension; i++) {
      if (vert[i]->pilhaAdjacentes != NULL) {
        Adjacencia* aux = vert[i]->pilhaAdjacentes;
        Adjacencia* auxProx = aux->prox;
        while (auxProx != NULL) {
          free(aux);
          aux = auxProx;
          auxProx = auxProx->prox;
        }
        free(aux);
        free(auxProx);
      }
      free(vert[i]);
    }
    free(vert);
    return NULL;
  }
