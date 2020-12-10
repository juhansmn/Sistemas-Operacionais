#include <stdio.h>
#include <string.h>

typedef struct em {
  int liberado; 
  size_t tamanho;
  struct em *proximo; 
} _em;

char memoria[4096]; 
_em *espacoMemoria = (void *)memoria;

void inicializar() {
    espacoMemoria->liberado = 1;
    espacoMemoria->tamanho = sizeof(memoria) - sizeof(_em);
    espacoMemoria->proximo = NULL;
}

void imprimirTamanho() {
    _em *espaco = espacoMemoria;
    int i = 1;

    while (espaco != NULL) {
        printf("Seção %d. %lu de espaço total.\n", i, espaco->tamanho);

        if (espaco->liberado == 1){
            printf("Memória LIVRE\n\n");
        }
        else{
            printf("Memória CHEIA\n\n");
        }

        espaco = espaco->proximo;
        i++;
    }
}

void *aloca(size_t nbytes) {
    _em *posMemoria;    
    posMemoria = espacoMemoria;
    
    while((posMemoria->tamanho < nbytes || posMemoria->liberado == 0) && posMemoria->proximo != NULL) { 
        posMemoria = posMemoria->proximo;
    }

    if (posMemoria->tamanho == nbytes) {
        posMemoria->liberado = 0;

        void *aux = ++posMemoria;
        printf("ESCRITO: %p.\n", aux);
        return aux;
    } 
    else if(posMemoria->tamanho > nbytes) { 
        _em *secao = (void *)(posMemoria + sizeof(_em) + nbytes); 

        secao->liberado = 1;
        secao->tamanho = posMemoria->tamanho - sizeof(_em) - nbytes;
        secao->proximo = posMemoria->proximo; 

        posMemoria->liberado = 0; 
        posMemoria->tamanho = nbytes + sizeof(_em); 
        posMemoria->proximo = secao; 

        void *aux = ++posMemoria; 
        printf("ESCRITO: %p.\n\n", aux);
        return aux;

    } 
    else {
        printf("ERRO: Memória sem espaço disponível!\n");
        return NULL;
    }
}

void liberado(void *p) {
    if (p >= (void *) memoria && p <= (void *) (memoria + sizeof(memoria))) {
        _em *posMemoria = p;

        printf("LIMPO: %p.\n", (void *)posMemoria);

        posMemoria--; 
        posMemoria->liberado = 1; 
    }
}

int main(void) {
    inicializar();

    imprimirTamanho();

    int *ex = (int *) aloca(sizeof(int));
    imprimirTamanho();
    
    *ex = 500;

    liberado(ex);
}