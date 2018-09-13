#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "coisas.h"

int main(int argc, char const *argv[]){
	//structs
	Tsp* arv;
	//variaveis
	char type[10], edgeWeightType[20], nome[40],comentario[20];
	int dimension;

	if (argc != 2) {
		printf("Insira o nome do arquivo de entrada\n");
		return 1;
	}
	FILE* entrada = fopen(argv[1], "r");

	fscanf(entrada, "NAME: %s\n", nome);

	while (strcmp(comentario, "TYPE:") != 0) {
		//printf("ignorando o comentario\n");
		fscanf(entrada, "%s", comentario);
	}

	fscanf(entrada, " %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\nNODE_COORD_SECTION\n", type, &dimension, edgeWeightType);
	arv = criaTsp(nome, type, edgeWeightType, dimension);

	for (int i = 0; i <= dimension; ++i) {
		int index;
		float x, y;
		fscanf(entrada, "%d %f %f\n", &index, &x, &y);
		//FEZ UNS E PAROU //TESTE
		insereCity(arv, criaCity(index, x, y) );
	}
	fclose(entrada);


	

	return 0;
}
