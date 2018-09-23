#include "tsp.h"

int main(int argc, char const *argv[]){
	//Entrada
	//Abertura do arquivo de entrada
	if (argc != 2) {
		printf("Insira o nome do arquivo de entrada\n");
		return 1;
	}
	//tamanho do nome do arquivo + in/ + /n
	int entradaSize = strlen(argv[1]+3+1);
	char entradaNome[entradaSize];
	strcpy (entradaNome, "in/");
	strcat (entradaNome, argv[1]);


	FILE* entrada = fopen(entradaNome, "r");
	if (entrada == NULL) {
		printf("ERRO AO ABRIR O ARQUIVO DE ENTRADA %s\n", entradaNome);
	}

	//DATA
	Data* dadosEntrada = (Data*) malloc(sizeof(Data));
	dadosEntrada = leArquivo(entrada, dadosEntrada);//preenchimento dos dados referentes ao arquivo
	//de entrada na struct dadosEntrada
	fclose(entrada);

	//Edges
	//calcula o tamanho necessario para gerar edges q saem de todos
	//os vertices para todos. Tal formula equivale a diagonal principal
	//e o triangulo superior da matriz dos vertices.
	int tam = ((dadosEntrada->dimension*dadosEntrada->dimension) - dadosEntrada->dimension)/2;
	Edge* vetEdge = criaVetorAresta(dadosEntrada, tam);//cria todas as edges possiveis


	//Quick find
	int indice_find = 0;
	UF_init(dadosEntrada->dimension+1);
	Edge* arvMinima = (Edge*)malloc((dadosEntrada->dimension-1)*sizeof(Edge));


	for(int i = 1; i <= tam && indice_find <= (dadosEntrada->dimension-1); i++) {
		//printf("[%d] A distância entre %d e %d é :%d \n", i, vetEdge[i].ori, vetEdge[i].dest, vetEdge[i].distance); //TESTE
		if(UF_union(vetEdge[i].ori, vetEdge[i].dest)) {
			arvMinima[indice_find] = vetEdge[i];
			indice_find++;
		}
	}

	int saidaMstSize = strlen(argv[1]+5+4+1);
	char saidaMstNome[saidaMstSize];
	strcpy(saidaMstNome, "mst/");
	strcat(saidaMstNome, dadosEntrada->nome);
	strcat(saidaMstNome, ".mst");
	FILE* saidaMst = fopen(saidaMstNome, "w");
	if (saidaMst == NULL) {
		printf("ERRO NA HORA DE CRIAR O ARQUIVO SAIDAMst\n\n\n\n\n\n");
		exit(1);
	}

	imprimeData(arvMinima, dadosEntrada, saidaMst);
	fclose(saidaMst);
	//Vertice de lista
	Vertice** vertices = preencheVetorVertice(arvMinima, dadosEntrada->dimension);

	int saidaTourSize = strlen(argv[1]+6+5+1);
	char saidaTourNome[saidaTourSize];
	strcpy(saidaTourNome, "tour/");
	strcat(saidaTourNome, dadosEntrada->nome);
	strcat(saidaTourNome, ".tour");
	if(saidaTourNome == NULL){
		printf("ERRO NA HORA DE CRIAR O ARQUIVO SAIDATOUR");
	}
	FILE* saidaTour = fopen(saidaTourNome, "w");

	imprimeTour(vertices, dadosEntrada, saidaTour);

	fclose(saidaTour);

	// printf("Preparando para dar free na UF\n\n");
	UF_free();
	// printf("UF liberada com sucesso\n\n\n\n");
	// printf("Preparando para dar free nos vértices\n\n");
	vertices = freeVetorVertices(vertices, dadosEntrada->dimension);
	// printf("Vertices liberados com sucesso\n\n\n\n");
	// printf("Preparando para dar free no vetEdge\n\n");
	free(vetEdge);
	vetEdge = NULL;
	// printf("VetEdge liberado com sucesso\n\n\n\n");
	// printf("Preparando para dar free na arvMinima\n\n");
	free(arvMinima);
	arvMinima = NULL;
	// printf("ArvMinima liberada com sucesso\n\n\n\n");
	// printf("Preparando para dar free na DATA\n\n");
	dadosEntrada = freeData(dadosEntrada);
	// printf("DATA liberada com sucesso\n\n\n\n");


	return 0;
}
