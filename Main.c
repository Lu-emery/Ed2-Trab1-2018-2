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

		insereCity(arv, criaCity(index, x, y) );
	}
	fclose(entrada);

	//Edges
	int cont = ( (dimension*dimension) - dimension)/2;
	edge vetEdge[cont+1];

	cont=1;
	for(int i = 1; i < dimension; i++){
		for(int j = i+1; j <= dimension; j++){
			vetEdge[cont].distance = distance(arv->arraycity[i],arv->arraycity[j]);
			vetEdge[cont].ori = i;
			vetEdge[cont].dest = j;
			cont++;
		}
	}

	for(int i = 1; i < cont; i++){
		printf("%d ",vetEdge[i].distance);
	}


	return 0;
}
