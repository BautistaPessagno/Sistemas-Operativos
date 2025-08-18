#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define QPROCESS 10

//Definimos el pid y status globales
pid_t wpid;
int status = 0;

int main(){

    //Definimos parámetros para el execve
    char *newargv_p[] = { "p", NULL };
	char *newenviron[] = { NULL };

    //Abrimos o creamos el archivo de salida.
    int fd = open("salida.txt", O_CREAT | O_WRONLY, 0644);
    if(fd < 0){
        perror("open");
        exit(1);
    }


    for(size_t i = 0; i < QPROCESS; i++){
        pid_t pid_p;

        //Creamos el proceso p
        if((pid_p = fork()) == 0){
            
            //Duplicamos el fd de salida estandar para redirigirloy 
            dup2(fd, STDOUT_FILENO);
            close(fd);

            execve("p", newargv_p, newenviron);
            perror("execve proceso p");
            exit(1);
		}

        //El programa c no nos interesa

        //El padre espera a que terminen los dos hijos
        //WNOHANG es una macro que vale cero y se pasa como parámetro al PID
        while((wpid = waitpid(-1, &status, WNOHANG) > 0));
    }
    

    printf("\nTerminaron todos los hijos\n");

    return 0;
}
