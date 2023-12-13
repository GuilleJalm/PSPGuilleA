#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include <time.h>

int main() {
    int fd[2];
    int sumandos[2];
    int suma, resta, producto, division;

    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // Código para el proceso hijo
        close(fd[0]);

       // srand(time(NULL)); // Inicializar la semilla de generación de números aleatorios

        sumandos[0] = 1 + rand() % 50; // Generar número aleatorio entre 1 y 50
        sumandos[1] = 1 + rand() % 50; // Generar número aleatorio entre 1 y 50

        printf("Hijo: Generados números aleatorios %d y %d\n", sumandos[0], sumandos[1]);

        write(fd[1], sumandos, sizeof(sumandos));

        close(fd[1]);
       
    } else {
        // Código para el proceso padre
        close(fd[1]);

        read(fd[0], sumandos, sizeof(sumandos));

        suma = sumandos[0] + sumandos[1];
        resta = sumandos[0] - sumandos[1];
        producto = sumandos[0] * sumandos[1];
        division = sumandos[0] / sumandos[1];

        printf("Padre: Aquí tienes los resultados de las operaciones.\n");
        printf("Suma: %d\n", suma);
        printf("Resta: %d\n", resta);
        printf("Producto: %d\n", producto);
        printf("División: %d\n", division);

        close(fd[0]);
     
        wait(NULL);
    }

    return 0;
}


