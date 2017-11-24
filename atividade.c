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

void deletar(digito x){
    x->prox = livres;
    livres = x;
}

void deletarLista(digito l){
  while(l != NULL){
    digito aux = l->prox;
    deletar(l);
    l = aux;
  }
}

digito novo(int valor){
    if(livres == NULL){
        int qtd = 1024;
        digito aux = (digito) malloc(qtd*sizeof(struct digito_s));

        if(aux != NULL){
            for(int i = 0; i < qtd; i++){
                deletar(aux+i);
            }
        }else{
            printf("Erro: memória insuficiente para criar novos digitos\n");
            return NULL;
        }
    }
    digito x = livres;
    livres = livres->prox;

    x->valor = valor;
    x->prox = NULL;

    return x;
}

void imprimirNumero(digito numero){
    while (numero != NULL){
        printf("%d", numero->valor);
        numero = numero->prox;
    }
    printf("\n");
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
        while(rodando != NULL && scanf("%c", &o) > 0 && (o != '+' && o != '*' && o != '\n')){
            rodando->prox = novo(charToInt(o));
            rodando = rodando->prox;
        }

        if(o == '+' || o == '*'){
            definirOperacao(o);
        }

    }

    return numero;
}

void inverter(digito *numero){
  digito x = *numero;
  *numero = NULL;

  while (x != NULL) {
    digito y = x->prox;
    x->prox = *numero;
    *numero = x;
    x = y;
  }
}

digito somar(digito numero1, digito numero2){
    digito resultado = NULL;

    //inverte os numeros pois a conta tem o sentido direita pra esquerda
    inverter(&numero1);
    inverter(&numero2);

    int carry = 0;
    //faz a soma digito por digito
    while(numero1 != NULL || numero2 != NULL){
      digito aux = novo(carry);
      if(numero1 != NULL){
        //soma o valor
        aux->valor += numero1->valor;

        //itera a variavel
        numero1 = numero1->prox;
      }
      if(numero2 != NULL){
        //soma o valor
        aux->valor += numero2->valor;

        //itera a variavel
        numero2 = numero2->prox;
      }

      //verifica se tem que "enviar" o carry
      if(aux->valor >= 10){
        aux->valor -= 10;
        carry = 1;
      }else{
        carry = 0;
      }

      //salva o valor
      aux->prox = resultado;
      resultado = aux;
    }

    //volta as listas pra condição original delas
    inverter(&numero1);
    inverter(&numero2);

    return resultado;
}

digito multiplicar(digito numero1, digito numero2){
    return NULL;
}

int main(){
    livres = NULL;
    op;

    int teste = 0;

    digito numero1 = NULL, numero2 = NULL;
    while((numero1 = lerNumero()) != NULL){
        numero2 = lerNumero();

        digito resultado = NULL;
        if(op == '+'){
            resultado = somar(numero1, numero2);
        }else{
            resultado = multiplicar(numero1, numero2);
        }

        if(teste){
          printf("Numero 1: ");
          imprimirNumero(numero1);

          printf("Numero 2: ");
          imprimirNumero(numero2);

          printf("Operação: %c\n", retornarOperacao());

          printf("Resultado: ");
          imprimirNumero(resultado);
        }else{
          imprimirNumero(resultado);
        }
        deletarLista(numero1);
        deletarLista(numero2);
        deletarLista(resultado);
    }
    return 0;
}
