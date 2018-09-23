#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "quick_find.h"

//STRUCTS
  typedef struct city City;
  typedef struct mst Mst;
  typedef struct edge Edge;
  typedef struct adjacencia Adjacencia;
  typedef struct vertice Vertice;

  //city equivale a Cidade no problema
  struct city {
      int index;
      float x;
      float y;
  };

  //MST (minimum spanning tree)
  //Também contém os elementos da entrada
  struct mst {
      char* type;
      char* edgeWeightType;
      char* nome;
      int dimension;
      City** arrayCity;
  };

  struct edge {
      int distance;
      int ori;
      int dest;
      int check;
  };

  struct adjacencia {
    Vertice* vertice;
    Adjacencia* prox;
  };

  struct vertice {
    int indice;
    int cor;
    Adjacencia* pilhaAdjacentes;
  };


//MST
  City* criaCity(int, float, float);
  void imprimeCity(City*);
  Mst* insereCity(Mst*, City*);
  Mst* criaMst(char*, char*, char*, int, Mst*);
  void imprimeMst (Edge* arvMinima, Mst* mst, FILE* saidaMST);

//Edge
  int distance(City*, City*);
  int compara(const void*, const void*);
  void imprimeEdge(Edge edge, FILE* saida);

//Vertice de adjacência
  Vertice** preencheVetorVertice(Edge*, int);
  void insereEmVetorVertices(Vertice**, Edge);
  Adjacencia* criaAdjacencia(Vertice*);

//Auxiliares
  Mst* leArquivo(FILE*, Mst*);
  Edge* criaVetorAresta(Mst*, int);

 //TOUR
  #define branco 1
  #define preto 0
  #define cinza -1

  void DFS(Vertice**, int, FILE*);
  void DFS_Visit(Vertice*, FILE*);
  void imprimeTour(Vertice**, Mst*, FILE*);

  //free
  Mst* freeMst(Mst*);
  Vertice** freeVetorVertices(Vertice**, int);
