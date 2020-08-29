#include <stdio.h>
#include <sys/utsname.h>

//Juan Victor Suman

int main(void) {
    struct utsname data;

    uname(&data);

    printf("nome do sistema operacional: %s\n", data.sysname);
    printf("nome dentro de uma rede: %s\n", data.nodename);
    printf("release do sistema operacional: %s\n", data.release);
    printf("versão do sistema operacional: %s\n", data.version);
    printf("identificador do hardware: %s\n", data.machine);
}