#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t p1, p2, p3, p4, p5;
    int acumulado;

    p1 = getpid();
    acumulado = p1;
    printf("P1 (Padre original): PID = %d, Acumulado = %d\n", p1, acumulado);

    p2 = fork();

    if (p2 == 0) {
        if (getpid() % 2 == 0) {
                acumulado += 10;
            } else {
                acumulado -= 100;
            }
        printf("P2: PID = %d, Acumulado = %d\n", getpid(), acumulado);

        p5 = fork();

        if (p5 == 0) {
            if (getpid() % 2 == 0) {
                acumulado += 10;
            } else {
                acumulado -= 100;
            }
            printf("P5: PID = %d, Acumulado = %d\n", getpid(), acumulado);
        } else {
            wait(NULL); // P2 espera a que P5 termine
        }
    } else {
        p3 = fork();

        if (p3 == 0) {
            if (getpid() % 2 == 0) {
                acumulado += 10;
            } else {
                acumulado -= 100;
            }
            printf("P3: PID = %d, Acumulado = %d\n", getpid(), acumulado);

            p4 = fork();

            if (p4 == 0) {
                if (getpid() % 2 == 0) {
                    acumulado += 10;
                } else {
                    acumulado -= 100;
                }
                printf("P4: PID = %d, Acumulado = %d\n", getpid(), acumulado);
            } else {
                wait(NULL); // P3 espera a que P4 termine
            }
        } else {
            wait(NULL); // P1 espera a que P2 y P3 terminen
        }
    }

    return 0;
}


