#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "quick_find.h"

//city equivale a Cidade no problema
struct city {
    int index;
    float x;
    float y;
} typedef City;

//TSP (travelling salesman problem)
//Também contém os elementos da entrada
struct tsp{
    char* type;
    char* edgeWeightType;
    char* nome;
    int dimension;
    City** arrayCity;
} typedef Tsp;

struct edge{
    int distance;
    int ori;
    int dest;
    int check;
} typedef Edge;


//TSP
City* criaCity(int , float, float);
void imprimeCity(City* );
Tsp* insereCity(Tsp*, City*);
Tsp* criaTsp(char*, char*, char*, int );
void imprimeTsp (Tsp* );

//Edge
int distance(City*, City*);
int compara(const void*, const void* );

//Tour
int prox_Tour(int, Edge*, int);
int contidoNoTour(int*, Edge, int);

//Auxiliares
Tsp* leArquivo(FILE*, Tsp*);
Edge* criaVetorAresta(Tsp*, int);
