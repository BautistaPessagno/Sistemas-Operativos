#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  const int num_children = 10;
  const char *child_path = "./ej2/child";

  for (int i = 0; i < num_children; i++) {
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      return EXIT_FAILURE;
    }

    if (pid == 0) {
      char *child_argv[] = {"child", NULL};
      if (execve(child_path, child_argv, environ) == -1) {
        perror("execve");
        _exit(127);
      }
    }
  }

  int remaining = num_children;
  while (remaining > 0) {
    int status = 0;
    pid_t done = waitpid(-1, &status, 0);
    if (done == -1) {
      if (errno == EINTR) {
        continue;
      }
      perror("waitpid");
      return EXIT_FAILURE;
    }

    if (WIFEXITED(status)) {
      int code = WEXITSTATUS(status);
      printf("Padre: proceso hijo %d terminó con código %d\n", (int)done, code);
    } else if (WIFSIGNALED(status)) {
      int sig = WTERMSIG(status);
      printf("Padre: proceso hijo %d terminó por señal %d\n", (int)done, sig);
    } else {
      printf("Padre: proceso hijo %d terminó (estado 0x%x)\n", (int)done, status);
    }

    remaining--;
  }

  printf("Padre: todos los hijos han terminado. Saliendo.\n");
  return EXIT_SUCCESS;
}

