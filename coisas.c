#include "coisas.h"

//city equivale a Cidade no problema
struct city {
    int index;
    float x;
    float y;
};

//TSP (travelling salesman problem)
//ao decorrer do codigo iremos nos referir ao TSP
//como travaler
struct tsp{
    char* type;
    char* edgeWeightType;
    char* nome;
    int dimension;
    city** arraycity;
};

struct edge{
    int ori;
    int dest;
    
}

/* Insere city no TSP
* inputs: trabaler, city
* outputs:  nenhum
* pré-condicao: existencia e alocação do trabaler e do city, indice valido
* pós-condicao: city registrado no travaler no indice do mesmo -1
pois a primeira cidade será sempre a cidade 1*/
Tsp* insereCity (Tsp* traveler, city* p) {
    traveler->arraycity[(p->index)] = p;
    return traveler;
}

/* Cria city
* inputs: Numero da cidade, coordenadas x e y
* outputs: city devidamente alocado
* pré-condicao: os campos enviados existem
* pós-condicao: city criado*/
city* criaCity(int ind, float x, float y) {
  city* p = (city*) malloc(sizeof(p));
  p->index = ind;
  p->x = x;
  p->y = y;
  return p;
}

/* Imprime city
* inputs: city que deve ser impresso
* outputs: nenhum
* pré-condicao: city devidadmente alocado
* pós-condicao: dados referentes ao city printados na tela*/
void imprimeCity(city* p) {
  printf("city índice: %d | X=%.1f | Y=%.1f \n", p->index, p->x, p->y);
}

/*Aloca e preenche os dados do travaler
* inputs: nome, tipo de grafo dado por entrada(sempre sera TSP),
tipo de peso dos arcos (sempre sera EUC_2D), dimensão(quantidade de cidades)
* outputs: travaler alocado e preenchido com seus daods
* pré-condicao: os campos enviados existem
* pós-condicao: travaler alocado e preenchido com seus daods*/
Tsp* criaTsp(char* nome, char* type, char* edgeWeightType, int dimension) {
  Tsp* tsp = (Tsp*) malloc(sizeof(tsp));

  tsp->arraycity = (city**) malloc( (dimension + 1)*sizeof(city*));
  tsp->nome = strdup(nome);
  tsp->type = strdup(type);
  tsp->edgeWeightType = strdup(edgeWeightType);
  tsp->dimension = dimension;

  return tsp;
}

/* Printa na tela o travaler e seus city
* inputs: travaler
* outputs: nenhum
* pré-condicao: travaler devidamente alocado e preenchido
* pós-condicao: dados do travaler printados na tela*/
void imprimeTsp (Tsp* tsp) {
  int dimension = tsp->dimension;
  printf("Name: %s \nTYPE: %s  \nEdge: %s \nDimension: %d \n", tsp->nome, tsp->type, tsp->edgeWeightType, dimension);
  for (int i = 1; i <= dimension; i++) {
    imprimeCity(tsp->arraycity[i]);
  }
  printf("\n\n");
}


/*
* inputs:
* outputs:
* pré-condicao:
* pós-condicao:*/
