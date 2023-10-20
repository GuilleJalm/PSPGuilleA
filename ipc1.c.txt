#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <time.h>
void main(){

     int fd[2]; 
     char buffer[30];
     pid_t pid;
     
     time_t hora;
    char *fecha ;
    time(&hora);
    fecha = ctime(&hora);
    
     // Creamos el pipe
     pipe(fd); 
     
     //Se crea un proceso hijo
     pid = fork();

     if (pid==0)
     
     {
                close(fd[1]); // Cierra el descriptor de escritura
                printf("El hijo se dispone a leee del PIPE \n");
                read(fd[0], &fecha, sizeof(fecha));
                printf("\t Mensaje leido del pipe: %s \n", fecha);
     
     }
     
     else
     
     {
                close(fd[0]); // Cierra el descriptor de lectura
                char datetime_str[20]; // Suficiente espacio para almacenar la fecha y hora
               
                printf("El padre escribe en el PIPE...\n");
                
                write(fd[1], &fecha, sizeof(fecha));  
                wait(NULL);    
     }
     
        
}