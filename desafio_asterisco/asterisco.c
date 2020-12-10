#include <stdio.h>

int main() {
  char c = '*';
  char n = '\n';
  while(1) {
    putchar(c);
    putchar(n);
    setvbuf(stdout, NULL, _IOFBF, 0);
    fflush(stdout);
  } 
}