#include "coisas.h"

//Ponto equivale a Cidade no problema
struct ponto {
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
    Ponto** arrayPontos;
};

/* Insere ponto no TSP
* inputs: trabaler, ponto
* outputs:  nenhum
* pré-condicao: existencia e alocação do trabaler e do ponto, indice valido
* pós-condicao: ponto registrado no travaler no indice do mesmo -1
pois a primeira cidade será sempre a cidade 1*/
Tsp* inserePonto (Tsp* traveler, Ponto* p) {
    traveler->arrayPontos[(p->index)-1] = p;
    return traveler;
}

/* Cria ponto
* inputs: Numero da cidade, coordenadas x e y
* outputs: ponto devidamente alocado
* pré-condicao: os campos enviados existem
* pós-condicao: ponto criado*/
Ponto* criaPonto(int ind, float x, float y) {
  Ponto* p = (Ponto*) malloc(sizeof(p));
  p->index = ind;
  p->x = x;
  p->y = y;
  return p;
}

/* Imprime ponto
* inputs: ponto que deve ser impresso
* outputs: nenhum
* pré-condicao: ponto devidadmente alocado
* pós-condicao: dados referentes ao ponto printados na tela*/
void imprimePonto(Ponto* p) {
  printf("Ponto índice: %d\nX=%.1f | Y=%.1f", p->index, p->x, p->y);
}

/*Aloca e preenche os dados do travaler
* inputs: nome, tipo de grafo dado por entrada(sempre sera TSP),
tipo de peso dos arcos (sempre sera EUC_2D), dimensão(quantidade de cidades)
* outputs: travaler alocado e preenchido com seus daods
* pré-condicao: os campos enviados existem
* pós-condicao: travaler alocado e preenchido com seus daods*/
Tsp* criaTsp(char* nome, char* type, char* edgeWeightType, int dimension) {
  Tsp* tsp = (Tsp*) malloc(sizeof(tsp));

  printf("\n\nNAME: %s\n", nome);

  tsp->nome = (char*)malloc((strlen(nome)+1)*sizeof(char));
  strcpy(tsp->nome, nome);

  tsp->type = (char*)malloc((strlen(type)+1)*sizeof(char));
  strcpy(tsp->type, type);

  tsp->edgeWeightType = (char*)malloc((strlen(edgeWeightType)+1)*sizeof(char));
  strcpy(tsp->edgeWeightType, edgeWeightType);

  tsp->dimension = dimension;
  printf("\n\nnome2: %s\n", tsp->nome);
  tsp->arrayPontos = (Ponto**) malloc(tsp->dimension*sizeof(Ponto*));

  printf("\n\nnome3: %s\n", tsp->nome);
  return tsp;
}

/* Printa na tela o travaler e seus pontos
* inputs: travaler
* outputs: nenhum
* pré-condicao: travaler devidamente alocado e preenchido
* pós-condicao: dados do travaler printados na tela*/
void imprimeTsp (Tsp* tsp) {
  int dimension = tsp->dimension;
  printf("Name: %s \nTYPE: %s  \nEdge: %s \nDimension: %d \n", tsp->nome, tsp->type, tsp->edgeWeightType, dimension);
  // for (int i = 0; i < dimension; i++) {
  //   imprimePonto(tsp->arrayPontos[i]);
  // }
  printf("\n\n");
}


/*
* inputs:
* outputs:
* pré-condicao:
* pós-condicao:*/
