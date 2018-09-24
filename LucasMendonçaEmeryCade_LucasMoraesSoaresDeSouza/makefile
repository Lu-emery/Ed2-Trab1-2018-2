test: tsp.o Main.o quick.o
	gcc -o trab1 tsp.o Main.o quick_find.o -lm

tsp.o:
	gcc -c tsp.c

Main.o:
	gcc -c Main.c

quick.o:
	gcc -c quick_find.c

clean:
	rm *o
