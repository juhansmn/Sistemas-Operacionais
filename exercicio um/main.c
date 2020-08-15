#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct N{
  char* string;
  struct N* prox;
  struct N* ant;
} node;

void imprimir_invertido(node* ultimo){
  node* temp;
  temp = ultimo;

  while(temp != NULL){
    printf("Nome: %s\n", temp->string);
    temp=temp->ant;
  }

  if(temp == NULL){
    printf("O programa finalizou.");
  }
}

int main(){
  node* primeiro = NULL;
  node* ultimo = NULL;
  node* no;

  int i = 0;

  printf("Digite 'FIM' para encerrar a digitação.\n");

  while(1){
    char *temp;
    temp = malloc(10);
    
    scanf("%s", temp);

    if (strncmp(temp, "FIM", 10) == 0){
      imprimir_invertido(ultimo);
      return 0;
    } 

    no = (node*)malloc(sizeof(node));
    no->string = temp;
    no->ant = ultimo;
    no->prox = NULL;

    if (primeiro == NULL){
      primeiro = no;
      ultimo = no; 
    }
    else{
      ultimo->prox = no;
      ultimo = no;
    }
  }
}