#include "quick_find.h"

static int* id;
static int* sz;

void UF_init(int size) {
    id = (int*)malloc(sizeof(int)*size);
    sz = (int*)malloc(sizeof(int)*size);


    for (int i = 0; i < size; i++) {
            id[i] = i; // Cada objeto comeca na sua propria componente.
            sz[i] = 1;
    } // N acessos ao array.

}

int UF_find(int p) {
  while (p != id[p]) {
    id[p] = id[id[p]];
    p = id[p];
  }
    return p; // Retorna o id da componente de p. 1 acesso.
}

int UF_union(int p, int q){
    int i = UF_find(p);
    int j = UF_find(q);

    if(i == j) return 0;

    if(sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    }
    else{
        id[j] = i;
        sz[i] += sz[j];
    }

    return 1;

}
