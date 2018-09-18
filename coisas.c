#include "coisas.h"


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
  Tsp* tsp = (Tsp*) malloc(sizeof(Tsp));

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

int distance(city* a, city* b){
    int dist = sqrt( pow((a->x - b->x),2) + pow((a->y - b->y),2) );
    return dist;
}

int compara(const void* x, const void* y) {
    int ret;

    edge* edgeX = (edge*) x;
    edge* edgeY = (edge*) y;

    ///printf("Comparando as distâncias %d e %d\n", edgeX->distance, edgeY->distance);
    ret = (edgeX->distance - edgeY->distance);
    return ret;
}

int prox_Tour(int ultimo, edge* arvMinima, int dimension ){
    for(int i = 0; i < dimension; i++){
        if(arvMinima[i].ori == i) return 1;
    }

    return 0;
}

int contidoNoTour(int* vetTour, edge e, int indice_tour ){
    //printf("test\n" );
    for(int i = 0; i <= indice_tour; i++){
        if(vetTour[i] == e.ori){
            vetTour[i].check = 1;
            return 1;
        }
    }

    return 0;
}
/*
* inputs:
* outputs:
* pré-condicao:
* pós-condicao:



24 48
35 36
34 35
5 15
5 24
5 6
20 50
38 40
37 40
39 40
36 39
24 38
2 7
1 22
5 48
38 48
32 49
15 24
6 24
34 39
37 48
15 38
1 49
8 41
4 6
6 48
15 48
19 45
7 42
34 37
24 40
18 31
34 44
40 48
36 49
9 10
35 49
36 37
36 40
6 38
1 32
15 40
19 41
34 40
22 49
20 23
35 44
15 37
4 5
22 31
34 49
4 25
*/
