#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "quick_find.h"

//STRUCTS
  typedef struct city City;
  typedef struct data Data;
  typedef struct edge Edge;
  typedef struct adjacencia Adjacencia;
  typedef struct vertice Vertice;

  //city equivale a Cidade no problema
  struct city {
      int index;
      float x;
      float y;
  };

  //DATA (minimum spanning tree)
  //Também contém os elementos da entrada
  struct data {
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
    int distance;
    Adjacencia* prox;
  };

  struct vertice {
    int indice;
    int cor;
    Adjacencia* pilhaAdjacentes;
  };


//DATA
  City* criaCity(int, float, float);
  void imprimeCity(City*);
  Data* insereCity(Data*, City*);
  Data* criaData(char*, char*, char*, int, Data*);
  void imprimeData (Edge* arvMinima, Data* data, FILE* saidaDATA);

//Edge
  int distance(City*, City*);
  int compara(const void*, const void*);
  void imprimeEdge(Edge edge, FILE* saida);

//Vertice de adjacência
  Vertice** preencheVetorVertice(Edge*, int);
  void insereEmVetorVertices(Vertice**, Edge);
  Adjacencia* criaAdjacencia(Vertice*, int);

//Auxiliares
  Data* leArquivo(FILE*, Data*);
  Edge* criaVetorAresta(Data*, int);

 //TOUR
  #define branco 1
  #define preto 0
  #define cinza -1

  int DFS_Visit(Vertice*, FILE*);
  void imprimeTour(Vertice**, Data*, FILE*);

  //free
  Data* freeData(Data*);
  Vertice** freeVetorVertices(Vertice**, int);
