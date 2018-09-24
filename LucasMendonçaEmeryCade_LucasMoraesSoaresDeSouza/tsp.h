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
    Adjacencia* prox;
  };

  struct vertice {
    int indice;
    int cor;
    Adjacencia* pilhaAdjacentes;
  };

  //Auxiliares
    Data* leArquivo(FILE*, Data*);
    int distance(City*, City*);
    int compara(const void*, const void*);

//DATA
  City* criaCity(int, float, float);
  void imprimeCity(City*);
  Data* insereCity(Data*, City*);
  Data* criaData(char*, char*, char*, int, Data*);
  void imprimeData (Edge* arvMinima, Data* data, FILE* saidaDATA);

//Edge
  Edge* criaVetorAresta(Data*, int);
  void imprimeEdge(Edge edge, FILE* saida);

//Vertice de adjacência
  Vertice** preencheVetorVertice(Edge*, int);
  void insereEmVetorVertices(Vertice**, Edge);
  Adjacencia* criaAdjacencia(Vertice*);

 //TOUR
  #define branco 1
  #define preto 0
  #define cinza -1

  int DFS_Visit(Vertice*, FILE*, Data*);
  int imprimeTour(Vertice**, Data*, FILE*);

  //FREE
  Data* freeData(Data*);
  Vertice** freeVetorVertices(Vertice**, int);
