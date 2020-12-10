#include <stdio.h>
#include <stdlib.h>

#include <time.h> 
#include <math.h>
#include <unistd.h>
#include <pthread.h> 
#include <sys/wait.h>
#include <sys/types.h>

int gerarPontoAleatorio();

//número total de pontos a serem simulados
int pontos = 1000000;
int fileDescriptor[2];

int main(void) {
  void filhoInicial();
  void pai();

  if (pipe(fileDescriptor) == -1) {
    return 1;
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("ERRO");
  } 
  else if ( pid == 0 ) {
    filhoInicial();
  } 
  else {
    pai();
  }
}

//estima o número de PI a partir dos cilcos e da quantidade de pontos
void estimarNumeroPI(int ciclos) {
  double pi = 4 * (double) ciclos / (double) pontos;

  printf("PI é aproximadamente: %f\n", pi);
}

void filhoInicial() {
  int x = gerarPontoAleatorio();

  close(fileDescriptor[0]);
  if (write(fileDescriptor[1], &x, sizeof(int)) == -1){
    printf("Não foi possível escrever");
  }

  close(fileDescriptor[1]);
  printf("Foram necessários %d/%d pontos simulados.\n", x, pontos);
}

int gerarPontoAleatorio() {
  //garantindo seed
  srand(time(0));

  //número de pontos simulados
  int j = 0;

  for(int i = 0; i < pontos; i++) {
    double x = (double)(rand() % 100 + 1)/(double)100;
    double y = (double)(rand() % 100 + 1)/(double)100;

    if ((pow(x, 2) + pow(y, 2)) <= 1) {
        j++;
    }
  }

  return j;
}

void pai() {
  int y;

  close(fileDescriptor[1]);
  read(fileDescriptor[0], &y, sizeof(int));
  
  close(fileDescriptor[0]);
  estimarNumeroPI(y);
}