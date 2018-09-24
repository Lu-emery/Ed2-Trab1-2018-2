PRIMEIRO TRABALHO DE ESTRUTURA DE DADOS 2 2018/2

INTEGRANTES:
	LUCAS MENDONÇA EMERY CADE (2017100210)
	LUCAS MORAES SOARES DE SOUZA (2016101245)


ARQUIVOS:
	in/
	mst/
	tour/
	main.c
	makefile
	quick_find.c
	quick_find.h
	tsp.c
	tsp.h


REQUISITOS:
	Arquivos de entrada devem estar na pasta "in/".
	As pastas "mst/" e "tour/" devem ser criadas antes, visto que o programa não tem permissão de criar as pastas.
	Antes da execução do trabalho, o comando "make" deve ser executado.
	O trabalho deve ser executado com o comando "./trab1 <problema>.tsp", onde o "<problema>" é o mesmo que o "NAME" do arquivo '.tsp'.


COMENTÁRIOS:
	Usamos a estrutura "Weighted Quick Union" para fazer a MST.
	Usamos a estrutura "Lista de Adjacência" para fazer o tour.
	Arquivos de saída são colocados nas pastas "mst/" e "tour/".
	Um arquivo "tamanhos.txt" é criado na pasta do executável para checagem dos tamanhos da MST e do tour.

	O tempo "time" no arquivo relatório é referente ao "real" exibido no comando "time" e foi testado em computador pessoal, não no Labgrad.

	O tempo de trabalho foi bem dividido entre os integrantes do grupo, ambos tendo participação em todas as etapas do trabalho.

	O trabalho se encontra no GitHub no endereço <https://github.com/Lu-emery/Ed2-Trab1-2018-2>