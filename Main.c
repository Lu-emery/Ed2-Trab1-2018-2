#include "coisas.h"

int main(int argc, char const *argv[]){
	//structs
	Tsp* arv;
	//variaveis
	char type[10], edgeWeightType[20], nome[40],comentario[20];
	int dimension;

	//TSP
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

		insereCity(arv, criaCity(index, x, y));
	}
	fclose(entrada);

	//Edges
	int cont = ((dimension*dimension) - dimension)/2;
	edge vetEdge[cont];

	cont=1;
	for(int i = 1; i < dimension; i++) {
		for(int j = i+1; j <= dimension; j++) {
			vetEdge[cont].distance = distance(arv->arraycity[i], arv->arraycity[j]);
			vetEdge[cont].ori = i;
			vetEdge[cont].dest = j;
			cont++;
		}
	}

	printf("Sortando os valores do vetor\n");
	qsort(vetEdge, cont, sizeof(edge), compara);
	printf("Valores do vetor sortados\n");

	//Quick find
	int indice_find = 0;
	// UF_init(dimension);
	edge* vetEdgeTuor = (edge*)malloc(sizeof(edge)*(dimension - 1));


	// for(int i = 1; i <= cont-1 && indice_find < dimension; i++) {
		//printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
		// if(UF_union(vetEdge[i].ori, vetEdge[i].dest)){
			// vetEdgeTuor[indice_find] = vetEdge[i];
			// indice_find++;
		// }
	// }

	// for(int i = 0; i < indice_find; i++){
		// printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdgeTuor[i].ori, vetEdgeTuor[i].dest, vetEdgeTuor[i].distance);
	// }


	/*
	for(int i = 1; i < cont; i++) {
		printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
	}
	// */
	// edge tour[52];
	// int contador = 1;
	// for (int i = 1; i <= dimension; i+=(dimension-contador)) {
	// 	edge minimo = vetEdge[i];
	// 	for (int j = 2; j <= (i-contador); j++) {
	// 		if (vetEdge[j].distance < minimo.distance) {
	// 			minimo = vetEdge[j];
	// 		}
	// 	}
	// 	tour[contador] = minimo;
	// 	contador++;
	// }
    //
	// for(int i = 1; i < dimension; i++) {
	// 	printf("[%d] A distância entre %d e %d é :%d \n", i, tour[i].ori, tour[i].dest, tour[i].distance); //TESTE
	// }

	/* Chora sort
	printf("Sortando os valores do vetor\n");
	qsort(vetEdge, cont, sizeof(edge), compara);
	printf("Valores do vetor sortados\n");


	for(int i = 1; i <= cont-1; i++) {
		printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
	}
	*/




	return 0;
}
