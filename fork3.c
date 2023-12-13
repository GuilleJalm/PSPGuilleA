#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t p1, p2, p3, p4, p5, p6;

    p1 = getpid();
    printf("P1 (Padre original): PID = %d, Abuelo = No tiene\n", p1);

    p2 = fork();

    if (p2 == 0) {
        printf("P2: PID = %d, Abuelo = %d\n", getpid(), p1);

        p3 = fork();

        if (p3 == 0) {
            printf("P3: PID = %d, Abuelo = %d\n", getpid(), getppid());

            p5 = fork();

            if (p5 == 0) {
                printf("P5: PID = %d, Abuelo = %d\n", getpid(), p1);
            } else {
                wait(NULL); // P3 espera a que P5 termine
            }
        } else {
            p4 = fork();

            if (p4 == 0) {
                printf("P4: PID = %d, Abuelo = %d\n", getpid(), p1);

                p6 = fork();

                if (p6 == 0) {
                    printf("P6: PID = %d, Abuelo = %d\n", getpid(), p1);
                } else {
                    wait(NULL); // P4 espera a que P6 termine
                }
            } else {
                wait(NULL); // P2 espera a que P3 y P4 terminen
            }
        }
    } else {
        wait(NULL); // P1 espera a que P2 termine
    }

    return 0;
}

