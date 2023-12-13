#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2], fd2[2];
    int dni;
    char bufferLetra[30];
    
    
    pipe(fd);
    pipe(fd2);
    
    pid_t pid = fork();

    if (pid == 0) {
        // Código para el proceso hijo
        printf("Hijo: Introduzca su dni sin espacios y sin letra:");
        scanf("%d", &dni);
        
        close(fd[0]); // Cierra el descriptor de lectura del pipe1 
	close(fd2[1]); // Cierra el descriptor de escritura dle pipe2
        
        write(fd[1],&dni,sizeof(dni));
        close(fd[1]);

        read(fd2[0], bufferLetra, sizeof(bufferLetra));
        printf("La letra del NIF ES: %c\n", bufferLetra[0]);
        
        close(fd2[0]);
	
        
    } else {
        // Código para el proceso padre
        close(fd[1]); // Cierra el descriptor de escritura del pipe1
        close(fd2[0]); // cierra el descriptor de lectura del pipe2
        
        read(fd[0], &dni, sizeof(dni)); //lee el dni enviado por el hijo 
       
        char letra[] = "TRWAGMYFPDXBNJZSQVHLCKE";
         dni %= 23; 
         printf("He calculado la letra del nif\n ");
         

        write(fd2[1], &letra[dni], sizeof(letra[dni]));
        close(fd2[1]); // cerramos descriptores una vez usados
	 close(fd[0]);
	 
        wait(NULL);
    }

    return 0;
}


