#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void UF_init(int size);
int UF_find(int p);
int UF_union(int p, int q);
void UF_free();
