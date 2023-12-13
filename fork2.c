#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t p1, p2, p3, p4;

    p1 = getpid();
    printf("P1 (Padre original): PID = %d, PPID = %d, Suma = %d\n", p1, getppid(), p1 + getppid());

    p2 = fork();

    if (p2 == 0) {
        printf("P2: PID = %d, PPID = %d, Suma = %d\n", getpid(), getppid(), getpid() + getppid());

        p3 = fork();

        if (p3 == 0) {
            printf("P3: PID = %d, PPID = %d, Suma = %d\n", getpid(), getppid(), getpid() + getppid());

            p4 = fork();

            if (p4 == 0) {
                printf("P4: PID = %d, PPID = %d, Suma = %d\n", getpid(), getppid(), getpid() + getppid());
            } else {
                wait(NULL); // P3 espera a que P4 termine
            }
        } else {
            wait(NULL); // P2 espera a que P3 termine
        }
    } else {
        wait(NULL); // P1 espera a que P2 termine
    }

    return 0;
}

