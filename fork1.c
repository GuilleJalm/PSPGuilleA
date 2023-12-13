#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t p1, p2, p3, p4, p5;
    int idp2;
    int idp3;
    int idp4;
   
    p1 = getpid();  // Obtener el ID del proceso actual (P1)
   
    printf("P1 (Padre): PID = %d\n", p1);
   
    p2 = fork();  // Crear el primer hijo (P2)
   
    if (p2 == 0) {
      idp2=getpid();

       if(idp2%2==0){
printf("Par P2: PID = %d, PPID = %d\n", getpid(), getppid());
       }else{
         printf("Impar P2: %d\n",idp2);
       }
    } else {
        p3 = fork();  // Crear el segundo hijo (P3)
       
        if (p3 == 0) {
           idp3=getpid();
       if(idp3%2==0){
	printf("Par P3: PID = %d, PPID = %d\n", getpid(), getppid());
       }else{
         printf("Impar P3: %d\n",idp3);
       }
        } else {
            p4 = fork();  // Crear el tercer hijo (P4)
           
            if (p4 == 0) {
              idp4=getpid();
       if(idp4%2==0){
printf("Par P4: PID = %d, PPID = %d\n", getpid(), getppid());
       }else{
         printf("Impar P4: %d\n",idp4);
       }
            } else {
                // Proceso padre (P1) espera a sus hijos
                wait(NULL);
                wait(NULL);

            }
        }
    }
   
    return 0;
}
