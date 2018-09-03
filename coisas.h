#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ponto Ponto;

typedef struct tsp Tsp;


Ponto* criaPonto(int ind, float x, float y);
void imprimePonto(Ponto* p);
Tsp* inserePonto(Tsp* traveler, Ponto* p);
Tsp* criaTsp(char* nome, char* type, char* edgeWeightType, int dimension);
void imprimeTsp (Tsp* tsp);
