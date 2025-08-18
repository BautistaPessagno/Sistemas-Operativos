#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QPROCESS 10

//Definimos el pid y status globales
pid_t wpid;
int status = 0;

int main(){

    //Definimos parámetros para el execve
    //char *newargv_c[] = { "c", NULL };
    char *newargv_p[] = { "p", NULL };
	char *newenviron[] = { NULL };

    for(size_t i = 0; i < QPROCESS; i++){
        pid_t pid_p;

        //Creamos el proceso p
        if((pid_p = fork()) == 0){

            execve("p", newargv_p, newenviron);
            perror("execve proceso p");
            exit(1);
		}

        //No hacemos nada con el proceso c porque no nos importa

        //El padre no espera a que terminen los hijos
        printf("Proceso p en segundo plano con PID: %d\n", pid_p);
    }
    
    printf("\nProceso p corriendo en background, padre terminado\n");

    return 0;
}