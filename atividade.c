#include<stdio.h>
#include<stdlib.h>

typedef struct digito_s * digito;
struct digito_s{
    int valor;
    struct digito_s * prox;
};

digito livres = NULL;
char op;

int charToInt(char c){
    return (int)(c - '0');
}

void definirOperacao(char c){
    op = c;
}

char retornarOperacao(){
    return op;
}

void imprimirNumero(digito numero){
    while (numero != NULL){
        printf("%d", numero->valor);
        numero = numero->prox;
    }
    printf("\n");
}

void deleta(digito x){
    x->prox = livres;
    livres = x;
}

digito novo(int valor){
    if(livres == NULL){
        int qtd = 1024;
        digito aux = (digito) malloc(qtd*sizeof(struct digito_s));
        
        if(aux != NULL){
            for(int i = 0; i < qtd; i++){
                deleta(aux+i);
            }
        }else{
            printf("Erro: memória insuficiente para criar novos digitos\n");
            return NULL;
        }
    }
    digito x = livres;
    x->valor = valor;
    x->prox = NULL;
    livres = livres->prox;
    
    return x;
}

digito lerNumero(){
    char o;
    digito numero = NULL;
    
    if(scanf("%c", &o) != EOF){
        //leitura da lista (numero)
        numero = novo(charToInt(o)); //inicio da lista
        
        /*le cada valor e insere como um digito
          no inicio do numero que já está gravado*/
        digito rodando = numero;
        while(scanf("%c", &o) > 0 && (o != '+' && o != '*' && o != '\n')){
            rodando->prox = novo(charToInt(o));
            rodando = rodando->prox;
        }
        
        if(o == '+' || o == '*'){
            definirOperacao(o);
        }
    }
    
    return numero;
}

digito somar(digito numero1, digito numero2){
    digito resultado = NULL;

    //preciso rodar os nós do resultado
    while(numero1 != NULL || numero2 != NULL){
        if(numero1 != NULL && numero2 != NULL){
            resultado = novo(numero1->valor + numero2->valor);
        }else{
            if(numero2 == NULL){
                resultado = novo(numero1->valor);
            }else{
                resultado = novo(numero2->valor);
            }
        }
    }
    
    return resultado;    
}

digito multiplicar(digito numero1, digito numero2){
    return NULL;
}

int main(){
    livres = NULL;
    op;
    
    digito numero1 = NULL, numero2 = NULL;   
    while((numero1 = lerNumero()) != NULL){
        numero2 = lerNumero();
        
        digito resultado = NULL;
        if(op == '+'){
            resultado = somar(numero1, numero2);
        }else{
            resultado = multiplicar(numero1, numero2);
        }
        
        printf("Numero 1: ");
        imprimirNumero(numero1);
        
        printf("Numero 2: ");
        imprimirNumero(numero2);
        
        printf("Operação: %c\n", retornarOperacao());
        
        printf("Resultado: ");
        imprimirNumero(resultado);
        
    }
    return 0;
}
