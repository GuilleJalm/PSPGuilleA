#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>

void
main ()
{

  int fd[2], fd2[2];
  pid_t pid;

  // Creamos los pipes
  pipe (fd);
  pipe(fd2);

  int numero1;
  int factorial;
  
  pid = fork ();
  if (pid == 0)
    {

      close (fd[1]);
      close(fd2[0]);
 
      read (fd[0], &numero1, sizeof (numero1));
     
      
          factorial = 1;
        for (int i = numero1; i > 0; i--) {
            factorial = factorial*i;
        }
        
      write (fd2[1], &factorial, sizeof (factorial));

	close(fd[0]);
	close(fd2[1]);
    }



  else

    {
      close (fd[0]);		// Cierra el descriptor de lectura del pipe1
      
      close(fd2[0]);	// Cierra el descriptor de escritura del pipe2
      printf ("Generando numero aleatorio:\n");
      numero1 = rand () % 10;
      printf ("numero = %d\n", numero1);
      write (fd[1], &numero1, sizeof (numero1));
    
      read(fd2[0], &factorial, sizeof(factorial));
      
      printf("El resultado del factorial es: %d", factorial);
    
    
	close(fd[1]);
	close(fd2[0]);
      wait (NULL);
    }


}
