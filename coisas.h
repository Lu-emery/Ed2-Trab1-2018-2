#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//city equivale a Cidade no problema
struct city {
    int index;
    float x;
    float y;
}typedef city;

//TSP (travelling salesman problem)
//ao decorrer do codigo iremos nos referir ao TSP
//como travaler
struct tsp{
    char* type;
    char* edgeWeightType;
    char* nome;
    int dimension;
    city** arraycity;
}typedef Tsp;

struct edge{
    int distance;
    int ori;
    int dest;

}typedef edge;



city* criaCity(int , float, float);
void imprimeCity(city* );
Tsp* insereCity(Tsp*, city*);
Tsp* criaTsp(char* , char* , char* , int );
void imprimeTsp (Tsp* );
int distance(city*, city*);
int compara(const void* ,const void* );
