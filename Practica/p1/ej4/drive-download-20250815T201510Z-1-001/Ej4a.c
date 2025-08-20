#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QPROCESS 10

// Definimos el pid y status globales
pid_t wpid;
int status = 0;

int main() {

  // Definimos parámetros para el execve
  char *newargv_c[] = {"c", NULL};
  char *newargv_p[] = {"p", NULL};
  char *newenviron[] = {NULL};

  // Descriptores para el pipe (fd[0] es lectura y fd[1] es escritura)
  int fd[2];

  // Creamos el pipe
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(1);
  }

  for (size_t i = 0; i < QPROCESS; i++) {
    pid_t pid_p, pid_c;

    // Creamos el proceso p
    if ((pid_p = fork()) == 0) { // se es 0 es el padre
      // Cerramos lo que no sirve del pipe y redirigimos el stdout a la
      // escritura del pipe
      close(fd[0]); // Cerranmos el extremo de lectura (no nos importa)
      dup2(fd[1], STDOUT_FILENO); // Duplicamos y redirigimos el de escritura
      close(fd[1]); // Cerramos el escritura después de duplicarlo

      execve("p", newargv_p, newenviron);
      perror("execve proceso p");
      exit(1);
    }

    // Creamos el proceso c
    if ((pid_p = fork()) == 0) {
      // Cerramos lo que no sirve del pipe y redirigimos el stdout a la
      // escritura del pipe
      close(fd[1]); // Cerranmos el extremo de escritura (no nos importa)
      dup2(fd[0], STDIN_FILENO); // Duplicamos y redirigimos el de escritura
      close(fd[0]);              // Cerramos el escritura después de duplicarlo

      execve("c", newargv_c, newenviron);
      perror("execve proceso c");
      exit(1);
    }

    // El padre cierra los extremos del pipe, ya que no los necesita
    close(fd[0]);
    close(fd[1]);

    // El padre espera a que terminen los dos hijos
    // WNOHANG es una macro que vale cero y se pasa como parámetro al PID
    while ((wpid = waitpid(-1, &status, WNOHANG) > 0))
      ;
  }

  printf("\nTerminaron todos los hijos\n");

  return 0;
}
