#include "coisas.h"

int main(int argc, char const *argv[]){
	//Entrada
	//Abertura do arquivo de entrada
	if (argc != 2) {
		printf("Insira o nome do arquivo de entrada\n");
		return 1;
	}
	FILE* entrada = fopen(argv[1], "r");

	//TSP
	Tsp* arv = (Tsp*) malloc(sizeof(Tsp));
	arv = leArquivo(entrada, arv);

	fclose(entrada);

	//Edges
	int tam = ((arv->dimension*arv->dimension) - arv->dimension)/2;
	Edge* vetEdge = criaVetorAresta(arv, tam);
	// printf("VETOR EDGE\n");
	// for(int i = 0; i < tam; i++){
	// 	printf("[%d] %d %d\n", i, vetEdge[i].ori, vetEdge[i].dest);
	// }
	// printf("===\nVETOR EDGE\n===");
	// printf("\n\n");

	//Quick find
	int indice_find = 0;
	UF_init(arv->dimension+1);
	Edge* arvMinima = (Edge*)malloc((arv->dimension)*sizeof(Edge));


	for(int i = 1; i <= tam && indice_find <= arv->dimension; i++) {
		//printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
		if(UF_union(vetEdge[i].ori, vetEdge[i].dest)){
			arvMinima[indice_find] = vetEdge[i];
			indice_find++;
		}
	}

	printf("Indice Find = %d\n", indice_find);
	for(int i = 0; i <= indice_find; i++ ){
		printf("[%d] %d %d\n", i, arvMinima[i].ori, arvMinima[i].dest);
	}
	printf("===================\nACABOU DE IMPRIMIR O SORT\n====================\n\n");

	//Vertice de lista
	Vertice** vertices = preencheVetorVertice(arvMinima, arv->dimension);

	for(int i = 1; i <= arv->dimension; i++) {
		printf("Vertice %d -> ", i);
		if (vertices[i]->pilhaAdjacentes != NULL) {
			Adjacencia* aux = vertices[i]->pilhaAdjacentes;
			while(aux != NULL) {
				printf("%d -> ", aux->vertice->indice);
				aux = aux->prox;
				}
			}
			printf(" NULL\n");
	}
	printf("\n\n\n");

	//int* tour = DFS(vertices, arv->dimension);

	return 0;
}
