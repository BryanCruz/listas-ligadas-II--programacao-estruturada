#include<stdio.h>

typedef struct digito_s * digito;

struct digito_s{
    int valor;
    digito_s * prox;
}


