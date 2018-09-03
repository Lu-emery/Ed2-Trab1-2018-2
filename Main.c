#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "coisas.h"

int main(int argc, char const *argv[])
{
	char type[10], edgeWeightType[20], nome[40];
	int dimension;



	//structs
	Tsp* arv;

	if (argc != 2) {
		printf("Insira o nome do arquivo de entrada\n");
		return 1;
	}

	FILE* entrada = fopen(argv[1], "r");

	while (!feof(entrada)) {

		printf("Lendo NAME\n");
		fscanf(entrada, "NAME: %s\n", nome);
		printf("NAME: %s\n", nome);
		char teste[20];
		printf("Lendo TYPE\n");
		while (strcmp(teste, "TYPE:") != 0) {
			printf("ignorando o comentario\n");
			fscanf(entrada, "%s", teste);
		}
		fscanf(entrada, " %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\nNODE_COORD_SECTION\n", type, &dimension, edgeWeightType);
		printf("TYPE: %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\n", type, dimension, edgeWeightType);
		arv = criaTsp(nome, type, edgeWeightType, dimension);

		for (int i = 0; i < dimension; ++i) {
			int index;
			float x, y;
			fscanf(entrada, "%d %f %f\n", &index, &x, &y);
			//FEZ UNS E PAROU //TESTE
			printf("Ponto índice: %d\nX=%.1f | Y=%.1f", index, x, y);
			Ponto* p = criaPonto(index, x, y);
			imprimePonto(p);
			inserePonto(arv, p);
		}
	}
	fclose(entrada);

	imprimeTsp(arv);
	/*
		NAME: berlin52
		COMMENT: 52 locations in
		Berlin (Groetschel)
		TYPE: TSP
		DIMENSION: 52
		EDGE_WEIGHT_TYPE: EUC_2D
		NODE_COORD_SECTION
		1 565.0 575.0
		2 25.0 185.0
		3 345.0 750.0
		4 945.0 685.0
		...
	*/


	return 0;
}
