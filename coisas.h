#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "quick_find.h"

//STRUCTS
  typedef struct city City;
  typedef struct tsp Tsp;
  typedef struct edge Edge;
  typedef struct adjacencia Adjacencia;
  typedef struct vertice Vertice;

  //city equivale a Cidade no problema
  struct city {
      int index;
      float x;
      float y;
  };

  //TSP (travelling salesman problem)
  //Também contém os elementos da entrada
  struct tsp {
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


//TSP
  City* criaCity(int, float, float);
  void imprimeCity(City*);
  Tsp* insereCity(Tsp*, City*);
  Tsp* criaTsp(char*, char*, char*, int );
  void imprimeTsp (Tsp*);

//Edge
  int distance(City*, City*);
  int compara(const void*, const void*);

//Vertice de adjacência
  Vertice** preencheVetorVertice(Edge*, int);
  void insereEmVetorVertices(Vertice**, Edge);
  Adjacencia* criaAdjacencia(Vertice*);

//Auxiliares
  Tsp* leArquivo(FILE*, Tsp*);
  Edge* criaVetorAresta(Tsp*, int);

 //TOUR
  void DFS(Vertice**, int);
  void DFS_Visit(Vertice*);
