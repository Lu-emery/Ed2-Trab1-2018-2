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

	//Quick find
	int indice_find = 0;
	UF_init(arv->dimension);
	Edge* arvMinima = (Edge*)malloc(sizeof(Edge)*(arv->dimension - 1));


	for(int i = 1; i <= tam-1 && indice_find < arv->dimension; i++) {
		//printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
		if(UF_union(vetEdge[i].ori, vetEdge[i].dest)){
			arvMinima[indice_find] = vetEdge[i];
			indice_find++;
		}
	}
	int vetTour[arv->dimension];
	int indice_tour = 1;

	vetTour[0] = arvMinima[0].ori;
	vetTour[1] = arvMinima[0].dest;

	printf("%d\n%d\n",vetTour[0], vetTour[1] );

	for(int i = 1; indice_tour < arv->dimension; i++) {
		//printf("%d %d\n", arvMinima[i].ori, arvMinima[i].dest);


		//aresta back
		if(contidoNoTour(vetTour, arvMinima[i], indice_tour)) {
			indice_tour++;
			vetTour[indice_tour] = arvMinima[i].dest;
			printf("%d\n", vetTour[indice_tour]);
			if(i >= arv->dimension){
				i = 0;
			}
		}

	}

	/*
	char saidaMst[strlen(arv->nome)+5];
	strcpy(saidaMst, arv->nome);
	printf("%s\n", saidaMst);
	strcat(saidaMst, ".mst");
	printf("%s\n", saidaMst);

	FILE* arqMst = fopen(saidaMst, "w");
	if (arqMst == NULL) {
		printf("Deu treta, corre\n");
		exit(1);
	}
	fprintf(arqMst, "NAME: %s\nTYPE: MST\narv->dimension: %d\nMST_SECTION\n", arv->nome, arv->dimension);
	for(int i = 0; i < arv->dimension; i++) {
		fprintf(arqMst, "%d %d", arvMinima[i].ori, arvMinima[i].dest); //TESTE
	} //TESTE

	fclose(arqMst);
	*/


	/*
	NAME: berlin52
	TYPE: MST
	arv->dimension: 52
	MST_SECTION
	35 36
	*/

	return 0;
}

//COdigos antigos
//
// Edge tour[52];
// int contador = 1;
// for (int i = 1; i <= dimension; i+=(dimension-contador)) {
// 	Edge minimo = vetEdge[i];
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
qsort(vetEdge, cont, sizeof(Edge), compara);
printf("Valores do vetor sortados\n");


for(int i = 1; i <= cont-1; i++) {
	printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
}
*/
