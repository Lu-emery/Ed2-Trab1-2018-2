#include "coisas.h"

int main(int argc, char const *argv[]){
	//Entrada
	//Abertura do arquivo de entrada
	if (argc != 2) {
		printf("Insira o nome do arquivo de entrada\n");
		return 1;
	}

	int entradaSize = strlen(argv[1]+3+1);
	char entradaNome[entradaSize];
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

	//Edges
	int tam = ((arv->dimension*arv->dimension) - arv->dimension)/2;
	Edge* vetEdge = criaVetorAresta(arv, tam);


	//Quick find
	int indice_find = 0;
	UF_init(arv->dimension+1);
	Edge* arvMinima = (Edge*)malloc((arv->dimension-1)*sizeof(Edge));


	for(int i = 1; i <= tam && indice_find <= (arv->dimension-1); i++) {
		//printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
		if(UF_union(vetEdge[i].ori, vetEdge[i].dest)) {
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
	char saidaMSTNome[saidaMSTSize];
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
	//Vertice de lista
	Vertice** vertices = preencheVetorVertice(arvMinima, arv->dimension);

	int saidaTourSize = strlen(argv[1]+6+5+1);
	char saidaTourNome[saidaTourSize];
	strcpy(saidaTourNome, "tour/");
	strcat(saidaTourNome, arv->nome);
	strcat(saidaTourNome, ".tour");
	if(saidaTourNome == NULL){
		printf("ERRO NA HORA DE CRIAR O ARQUIVO SAIDATOUR");
	}
	FILE* saidaTour = fopen(saidaTourNome, "w");

	imprimeTour(vertices, arv, saidaTour);

	fclose(saidaTour);

	printf("Preparando para dar free na UF\n\n");
	UF_free();
	printf("UF liberada com sucesso\n\n\n\n");
	printf("Preparando para dar free nos vértices\n\n");
	vertices = freeVetorVertices(vertices, arv->dimension);
	printf("Vertices liberados com sucesso\n\n\n\n");
	printf("Preparando para dar free no vetEdge\n\n");
	free(vetEdge);
	vetEdge = NULL;
	printf("VetEdge liberado com sucesso\n\n\n\n");
	printf("Preparando para dar free na arvMinima\n\n");
	free(arvMinima);
	arvMinima = NULL;
	printf("ArvMinima liberada com sucesso\n\n\n\n");
	printf("Preparando para dar free na MST\n\n");
	arv = freeMst(arv);
	printf("MST liberada com sucesso\n\n\n\n");


	return 0;
}
