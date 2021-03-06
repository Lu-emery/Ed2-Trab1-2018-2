#include "tsp.h"

//AUXILIARES
  /* Le arquivo de entrada e aloca suas informações em uma estrutura
     especializada para guarda-las
    * inputs: arquivo de entrada, ponteiro para o tipo especializada q guardará
              as informações do arquivo de entrada
    * outputs: estrutura especializado
    * pré-condicao: arquivo alocado e aberto para leitura
    * pós-condicao: estrutura especializada para leitura do arquivo alocado
                    e preenchido*/
  Data* leArquivo (FILE* entrada, Data* dadosEntrada) {
    char type[10], edgeWeightType[20], nome[40], comentario[20];
    int dimension;

    fscanf(entrada, "NAME: %s\n", nome);

    //os comentarios são informações inuteis, por isso tudo entre nome e
    //type deve ser ignorado
    do {
      fscanf(entrada, "%s", comentario);
    } while (strcmp(comentario, "TYPE:") != 0);

    fscanf(entrada, " %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\nNODE_COORD_SECTION\n", type, &dimension, edgeWeightType);
    dadosEntrada = criaData(nome, type, edgeWeightType, dimension, dadosEntrada);

    //cria todas as edges e insere elas no arquivo de entrada
    for (int i = 0; i < dimension; ++i) {
      int index;
      float x, y;
      fscanf(entrada, "%d %f %f\n", &index, &x, &y);

      insereCity(dadosEntrada, criaCity(index, x, y));
    }
    return dadosEntrada;
  }

  /* Calcula a distancia entre duas cidades
    * inputs: duas citys
    * outputs: a distancia
    * pré-condicao: cidades estejam mallocadas
    * pós-condicao: nenhuma*/
    int distance (City* a, City* b){
        int dist = sqrt( pow((a->x - b->x),2) + pow((a->y - b->y),2) );
        return dist;
    }

    /* Callback para comparar duas distancias
      * inputs: ponteiros void para as edges
      * outputs: diferença entre a distancias de edges diferentes
      * pré-condicao: alocação das edges
      * pós-condicao: nenhuma*/
    int compara (const void* x, const void* y) {
        int ret;

        Edge* edgeX = (Edge*) x;
        Edge* edgeY = (Edge*) y;

        ///printf("Comparando as distâncias %d e %d\n", edgeX->distance, edgeY->distance);
        ret = (edgeX->distance - edgeY->distance);
        return ret;
    }


//DATA
  /* Insere City no DATA
    * inputs: trabaler, city
    * outputs:  nenhum
    * pré-condicao: existencia e alocação do trabaler e do city, indice valido
    * pós-condicao: City registrado no traveler no indice do mesmo -1
    pois a primeira cidade será sempre a cidade 1*/
  Data* insereCity (Data* data, City* p) {
      data->arrayCity[(p->index)] = p;
      return data;
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
    * inputs: nome, tipo de grafo dado por entrada(sempre sera DATA),
    tipo de peso dos arcos (sempre sera EUC_2D), dimensão(quantidade de cidades)
    * outputs: traveler alocado e preenchido com seus daods
    * pré-condicao: os campos enviados existem
    * pós-condicao: traveler alocado e preenchido com seus daods*/
  Data* criaData(char* nome, char* type, char* edgeWeightType, int dimension, Data* dadosEntrada) {
    dadosEntrada->arrayCity = (City**) malloc((dimension + 1)*sizeof(City*));
    dadosEntrada->nome = strdup(nome);
    dadosEntrada->type = strdup(type);
    dadosEntrada->edgeWeightType = strdup(edgeWeightType);
    dadosEntrada->dimension = dimension;

    return dadosEntrada;
  }

  /* Printa na tela o traveler e seus city
    * inputs: traveler
    * outputs: nenhum
    * pré-condicao: traveler devidamente alocado e preenchido
    * pós-condicao: dados do traveler printados na tela*/
  void imprimeData (Edge* arvMinima, Data* data, FILE* saida) {
    int dimension = data->dimension;
    fprintf(saida, "NAME: %s\nTYPE: MST\nDIMENSION: %d\nMST_SECTION\n", data->nome, dimension);

    for (int i = 0; i < dimension-1; i++) {
      imprimeEdge(arvMinima[i], saida);
    }
    fprintf(saida, "EOF\n");
    // printf("DATA Imprimida com sucesso\n\n");
  }


//EDGE
  /*Aloca e preenche um vetor de todas as arestas possiveis no grafo
    * inputs: estrutura contendo dados do arquivo, quantidade de arestas
              possiveis no grafo dado
    * outputs: vetor de todas as arestas
    * pré-condicao:estrutura contendo as informações do arquivo alocado e
                   preenchido, tam equivalente ao tamanho máximo de arestas
                   do grafo
    * pós-condicao:vetor de aresta alocado e preenchido*/
  Edge* criaVetorAresta (Data* dadosEntrada, int tam) {
    Edge* vetEdge = (Edge*)malloc((tam+1)*sizeof(Edge));

    int cont = 1;
    for(int i = 1; i < dadosEntrada->dimension; i++) {
      for(int j = i+1; j <= dadosEntrada->dimension; j++) {
        vetEdge[cont].distance = distance(dadosEntrada->arrayCity[i], dadosEntrada->arrayCity[j]);
        vetEdge[cont].ori = i;
        vetEdge[cont].dest = j;
        vetEdge[cont].check = 0;
        cont++;
      }
    }

    qsort(vetEdge+1, tam, sizeof(Edge), compara);

    return vetEdge;
  }

  /* Imprime no arquivo de saida referente a DATA
    * inputs: uma edge e o arquivo em q vai ser escrito a DATA
    * outputs: nenhum
    * pré-condicao: edge allocado, arquivo saido aberto/existente
    * pós-condicao: o arquivo foi escrito*/
  void imprimeEdge(Edge edge, FILE* saida) {
    fprintf(saida, "%d %d\n", edge.ori, edge.dest);
  }


//VERTICES E ADJACÊNCIAS
  /*
  * inputs: arvore minima, tamanho do cetor vertices
  * outputs: vetor de vertices alocado e preenchido
  * pré-condicao: arvore minima alocada
  * pós-condicao: nenhuma*/
    Vertice** preencheVetorVertice (Edge* arvMinima, int dimension) {
      Vertice** vetorVertice = (Vertice**) calloc(dimension+1, sizeof(Vertice*));
      for(int i = 0; i < dimension-1; i++) {
          insereEmVetorVertices(vetorVertice, arvMinima[i]);
      }
      return vetorVertice;
  }

  /*Insere o vertive caso nao exista e coloca o vertive destino da edge
    na lista de adjacencia do vertive origem e vice versa, isso pq o grafo
    é não direcional
    * inputs: vetor de vertices, edge
    * outputs: nenhum
    * pré-condicao: vet alocado e edge alocado
    * pós-condicao: vertive criado e/ou sua lista de adjacencia atualizada*/
  void insereEmVetorVertices (Vertice** vet, Edge entrada) {
    int indiceOri = entrada.ori;
    int indiceDest = entrada.dest;

    //Checa se Ori existe
    if (vet[indiceOri] == NULL) {
      // printf("Criou um vertice origem [%d]\n", indiceOri);
      vet[indiceOri] = (Vertice*) malloc(sizeof(Vertice));
      vet[indiceOri]->indice = indiceOri;
      vet[indiceOri]->pilhaAdjacentes = NULL;
      vet[indiceOri]->cor = branco; //para a DFS
    }
    //Checa se Dest existe
    if (vet[indiceDest] == NULL) {
      // printf("Criou um vertice destino [%d]\n", indiceDest);
      vet[indiceDest] = (Vertice*) malloc(sizeof(Vertice));
      vet[indiceDest]->indice = indiceDest;
      vet[indiceDest]->pilhaAdjacentes = NULL;
      vet[indiceDest]->cor = branco; //para a DFS
    }
    //Cria a estrutura Adjacência do vértice destino
    Adjacencia* a = criaAdjacencia(vet[indiceDest]);
    //Faz ele ser o primeiro elemento da pilha de adjacência do vértice origem
    a->prox = vet[indiceOri]->pilhaAdjacentes;
    vet[indiceOri]->pilhaAdjacentes = a;
    a = criaAdjacencia(vet[indiceOri]);
    a->prox = vet[indiceDest]->pilhaAdjacentes;
    vet[indiceDest]->pilhaAdjacentes = a;
  }

  /* aloca a estrutura adjacencia e retorna ela
    * inputs: vertice que sera o primeiro vertiece adjacente na adjacencia
              em questão
    * outputs: uma adjacencia alocada e preenchida com o primerio vertor
    * pré-condicao: vert alocado
    * pós-condicao: nenhum*/
  Adjacencia* criaAdjacencia (Vertice* vert) {
    Adjacencia* a = (Adjacencia*) malloc(sizeof(Adjacencia));
    a->vertice = vert;
    a->prox = NULL;
    return a;
  }


 //TOUR
  Vertice* ultimoAcessado;
 /* Busca em Profundidade
   * inputs: Vertice atual, arquivo em q sera escrito o vertice conforme
             percorrido
   * outputs: nenhuma
   * pré-condicao: vert alocado, saida alocado e aberto
   * pós-condicao: vertice atual escrito no aquivo e sua cor atualizada
                   primeiro para cinza de chegacem e depois preto de concluido*/
  int DFS_Visit (Vertice* vert, FILE* saida, Data* dadosEntrada) {
    int tourLen = 0;
    fprintf(saida, "%d\n", vert->indice);
    vert->cor = cinza;
    Adjacencia* aux = vert->pilhaAdjacentes;

    while(aux != NULL) {//O de N
      if(aux->vertice->cor == branco) {
        tourLen += distance(dadosEntrada->arrayCity[ultimoAcessado->indice], dadosEntrada->arrayCity[aux->vertice->indice]);
        ultimoAcessado = aux->vertice;
        tourLen += DFS_Visit(aux->vertice, saida, dadosEntrada);
      }
      aux = aux->prox;
    }

    vert->cor = preto;
    return tourLen;
  }

  /* Imprime arquivo do Tuor
    * inputs: vetor de vertices, dados da entrada, arquivo em q o tour deve
              ser escrito
    * outputs: nenhuma
    * pré-condicao: vet alocado, dados de entrada lidos e alocados na estrutura
                    especializada par tal, arquivo de saida alocado e aberto
                    a leitura
    * pós-condicao: arquivo de saida preenchido com o cabeçalho padrão de
                    para arquivos de tour e o tuor em si*/
   int imprimeTour (Vertice** vet, Data* data, FILE* saida) {
     int tourLen = 0;
     //Imprime cabeçalho
     fprintf(saida, "NAME: %s\nTYPE: TOUR\nDIMENSION: %d\nTOUR_SECTION\n", data->nome, data->dimension);
     ultimoAcessado = vet[1];
     tourLen += DFS_Visit(vet[1], saida, data);

     int distFinal = distance(data->arrayCity[ultimoAcessado->indice], data->arrayCity[vet[1]->indice]);

     tourLen += distFinal;

     fprintf(saida,"EOF\n");
     // printf("Tour imprimido com sucesso\n");

     return tourLen;
   }


//FREE
  /* Libera todos os mallocs contidos na estrutura especializada q guarda
     as informações do arquivo
    * inputs: estrutura especializada de dados do arquivo
    * outputs: NULL
    * pré-condicao: arquivo de entrada alocado
    * pós-condicao: memoria do arquivo de entrada liberada*/
  Data* freeData(Data* dadosEntrada) {
    free(dadosEntrada->nome);
    free(dadosEntrada->type);
    free(dadosEntrada->edgeWeightType);
    for(int i = 1; i <= dadosEntrada->dimension; i++) {
      if (dadosEntrada->arrayCity[i] != NULL) {
         free(dadosEntrada->arrayCity[i]);
      }
    }
    free(dadosEntrada->arrayCity);
    free(dadosEntrada);
    return NULL;
  }

  /* Libera todos os mallocs contidos na estrutura q guarda os vertices
     e suas adjacencias
    * inputs: lista de vertives e seu tamanho
    * outputs: NULL
    * pré-condicao: arquivo de entrada alocado
    * pós-condicao: memoria do arquivo de entrada liberada*/
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
