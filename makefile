test: coisas.o Main.o quick.o
	gcc -o exe coisas.o Main.o quick_find.o -lm

coisas.o:
	gcc -c coisas.c

Main.o:
	gcc -c Main.c

quick.o:
	gcc -c quick_find.c

clean:
	rm *o *gch
