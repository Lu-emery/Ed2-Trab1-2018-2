#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct city city;
typedef struct tsp Tsp;
typedef struct edge edge;



city* criaCity(int ind, float x, float y);
void imprimeCity(city* p);
Tsp* insereCity(Tsp* traveler, city* p);
Tsp* criaTsp(char* nome, char* type, char* edgeWeightType, int dimension);
void imprimeTsp (Tsp* tsp);
