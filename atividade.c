#include<stdio.h>
typedef struct digito_s * digito;
struct digito_s{
    int valor;
    struct digito_s * prox;
};

int char_to_int(char c){
    return (int)c - 48;
}

digito lerNumero(){
    char o;
    scanf("%c", &o);
    if (o == EOF)  return NULL;

    digito rodando = NULL;

    //leitura da lista (numero)
    digito numero = novo(char_to_int(o)); //inicio da lista
    rodando = numero;
    while(scanf("%c", &o) > 0 && (o != '+' && o != '*' && o != '\n')){
        rodando->prox = novo(char_to_int(o));
        rodando = rodando->prox;
    }

    return numero1;
}

digito lerOperacao(){
    return NULL;
}

int main(){
    digito numero1 = NULL, numero2 = NULL;   
    while((numero1 = lerNumero) != NULL){
        char op = lerOperacao;            
        numero2 = lerNumero;
    }
    return 0;
}
