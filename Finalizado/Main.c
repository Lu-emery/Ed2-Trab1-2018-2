#include "coisas.h"

int main(int argc, char const *argv[]){
	//Entrada
	//Abertura do arquivo de entrada
	if (argc != 2) {
		printf("Insira o nome do arquivo de entrada\n");
		return 1;
	}

	int entradaSize = strlen(argv[1]+3+1);
	char* entradaNome = malloc(entradaSize*sizeof(char));
	strcpy (entradaNome, "in/");
	strcat (entradaNome, argv[1]);

	FILE* entrada = fopen(entradaNome, "r");
	if (entrada == NULL) {
		printf("ERRO AO ABRIR O ARQUIVO DE ENTRADA %s\n", entradaNome);
	}

	//MST
	Mst* arv = (Mst*) malloc(sizeof(Mst));
	arv = leArquivo(entrada, arv);

	fclose(entrada);
	free(entradaNome);

	//Edges
	int tam = ((arv->dimension*arv->dimension) - arv->dimension)/2;
	Edge* vetEdge = criaVetorAresta(arv, tam);


	//Quick find
	int indice_find = 0;
	UF_init(arv->dimension+1);
	Edge* arvMinima = (Edge*)malloc((arv->dimension-1)*sizeof(Edge));


	for(int i = 1; i <= tam && indice_find <= (arv->dimension-1); i++) {
		//printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
		if(UF_union(vetEdge[i].ori, vetEdge[i].dest)){
			arvMinima[indice_find] = vetEdge[i];
			indice_find++;
		}
	}

	// printf("TESTE ARV MIN\n");
	// for (int i = 0; i < arv->dimension-1; i++) {
	// 	printf("%d %d\n", arvMinima[i].ori, arvMinima[i].dest);
	// }
	// printf("======\n\n\n");

	int saidaMSTSize = strlen(argv[1]+5+4+1);
	char* saidaMSTNome = malloc(saidaMSTSize*sizeof(char));
	strcpy(saidaMSTNome, "mst/");
	strcat(saidaMSTNome, arv->nome);
	strcat(saidaMSTNome, ".mst");
	FILE* saidaMST = fopen(saidaMSTNome, "w");
	if (saidaMST == NULL) {
		printf("ERRO NA HORA DE CRIAR O ARQUIVO SAIDAMST\n\n\n\n\n\n");
		exit(1);
	}

	imprimeMst(arvMinima, arv, saidaMST);
	fclose(saidaMST);
	free(saidaMSTNome);
	//Vertice de lista
	Vertice** vertices = preencheVetorVertice(arvMinima, arv->dimension);


	for(int i = 1; i <= arv->dimension; i++) {
		if (vertices[i]->pilhaAdjacentes != NULL) {
			Adjacencia* aux = vertices[i]->pilhaAdjacentes;
			while(aux != NULL) {
				aux = aux->prox;
				}
			}
	}

	int saidaTourSize = strlen(argv[1]+6+5+1);
	char* saidaTourNome = malloc(saidaTourSize*sizeof(char));
	strcpy(saidaTourNome, "tour/");
	strcat(saidaTourNome, arv->nome);
	strcat(saidaTourNome, ".tour");
	if(saidaTourNome == NULL){
		printf("ERRO NA HORA DE CRIAR O ARQUIVO SAIDATOUR");
	}
	FILE* saidaTour = fopen(saidaTourNome, "w");

	imprimeTour(vertices, arv, saidaTour);

	fclose(saidaTour);
	free(saidaTourNome);

	return 0;
}
