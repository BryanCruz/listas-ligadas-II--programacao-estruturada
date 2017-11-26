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

    //free(x);

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
            fprintf(stderr, "Erro: memória insuficiente para criar novos digitos\n");
            exit(1);
        }
    }
    digito x = livres;
    livres = livres->prox;

    x->valor = valor;
    x->prox = NULL;

    return x;
/*
    digito x = (digito) malloc(sizeof(struct digito_s));
    if(x == NULL){
      fprintf(stderr, "Erro na alocação de memória\n");
      exit(1);
    }

    x->valor = valor;
    x->prox = NULL;

    return x;
*/
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


    digito inicioNumero1 = numero1;
    digito inicioNumero2 = numero2;

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
      carry = 0;
      while(aux->valor >= 10){
        aux->valor -= 10;
        carry++;
      }

      //salva o valor
      aux->prox = resultado;
      resultado = aux;
    }

    //adiciona um novo digito se ainda tivermos algum carry
    if(carry > 0){
      digito aux = novo(carry);
      aux->prox = resultado;
      resultado = aux;
    }

    //volta as listas pra condição original delas
    inverter(&inicioNumero1);
    inverter(&inicioNumero2);

    while(resultado != NULL && resultado->valor == 0){
      digito zeroAEsquerda = resultado;
      resultado = resultado->prox;
      deletar(zeroAEsquerda);
    }

    if(resultado == NULL) resultado = novo(0);
    return resultado;
}

digito multiplicar(digito numero1, digito numero2){
  digito resultado = NULL;

  //inverte os numeros pois a conta tem o sentido direita pra esquerda
  inverter(&numero1);
  inverter(&numero2);

  digito inicioNumero1 = numero1;
  digito inicioNumero2 = numero2;

  //faz a multiplicacao
  //  numero2
  //X numero1
  int carry = 0, qtdZerosAMais = 0;
  while(numero1 != NULL){

    digito resultadoAux = NULL;

    //corrige o valor devido à posição decimal
    //do digito que está multiplicando
    for(int i = qtdZerosAMais; i > 0; i--){
      digito aux = novo(0);
      aux->prox = resultadoAux;
      resultadoAux = aux;
    }
    qtdZerosAMais++;

    carry = 0;
    while(numero2 != NULL){

      digito aux = novo(carry);

      //multiplica os valores e soma o carry
      aux->valor += numero1->valor * numero2->valor;

      //itera a variavel
      numero2 = numero2->prox;

      //verifica se tem que "enviar" o carry
      carry = 0;
      while(aux->valor >= 10){
        aux->valor -= 10;
        carry++;
      }

      //salva o valor
      aux->prox = resultadoAux;
      resultadoAux = aux;
    }

    //adiciona um novo digito se ainda tivermos algum carry
    if(carry > 0){
      digito aux = novo(carry);
      aux->prox = resultadoAux;
      resultadoAux = aux;
    }

    //soma o valor atual com o anterior
    digito copiaResultado = resultado;
    resultado = somar(resultado, resultadoAux);
    deletarLista(copiaResultado);
    //iteração
    numero2 = inicioNumero2;
    numero1 = numero1->prox;

    //limpa a memoria do resultadoAux criado
    deletarLista(resultadoAux);
  }

  //volta as listas pra condição original delas
  inverter(&inicioNumero1);
  inverter(&inicioNumero2);

  while(resultado != NULL && resultado->valor == 0){
    digito zeroAEsquerda = resultado;
    resultado = resultado->prox;
    deletar(zeroAEsquerda);
  }

  if(resultado == NULL) resultado = novo(0);
  return resultado;
}

int main(){
    livres = NULL;
    op = '+';

    int teste = 0;

    digito numero1 = NULL, numero2 = NULL;
    int cont = 0;
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
        fprintf(stderr, "%d\n", ++cont);
    }
    return 0;
}
