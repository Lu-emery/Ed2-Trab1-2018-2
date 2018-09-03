all: coisas

coisas: coisas.o Main.o
  gcc -o exe coisas.o Main.o

coisas.o:
  gcc -c coisas.c

Main.o:
  gcc -c Main.c

clean:
  rm *.o
