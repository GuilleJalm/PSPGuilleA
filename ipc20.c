#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    int numeros[2];
    int resultado;
    char caracter;
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // Código para el proceso hijo
        close(fd[1]); // Cierra el descriptor de escritura

        read(fd[0], numeros, sizeof(numeros));
        read(fd[0], &caracter, sizeof(caracter));
        close(fd[0]);

        int resultado;
        if (caracter == '+') {
            resultado = numeros[0] + numeros[1];
        } else {
            printf("Hijo: Carácter no válido\n");
            exit(1);
        }

        printf("Hijo: Números recibidos: %d y %d\n", numeros[0], numeros[1]);
        printf("Hijo: Carácter recibido: %c\n", caracter);
        printf("El resultado de la operación es %d\n", resultado);

    } else {
        // Código para el proceso padre
        close(fd[0]); // Cierra el descriptor de lectura

        printf("Padre: Introduzca dos números: ");
        scanf("%d %d", &numeros[0], &numeros[1]);

        printf("Padre: Introduzca un carácter: ");
        scanf(" %c", &caracter);

        write(fd[1], numeros, sizeof(numeros));
        write(fd[1], &caracter, sizeof(caracter));
        close(fd[1]);

        wait(NULL);
    }

    return 0;
}

