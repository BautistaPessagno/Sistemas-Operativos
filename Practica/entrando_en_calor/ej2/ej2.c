#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main() {

  for (int i = 0; i < 10; i++) {
    int p = fork();
    if (p == -1) {
      exit(1);
    }

    // es el hijo
    else if (p == 0) {
      execve("hijo", NULL, environ);
    } else {
      waitpid(p, NULL, 0);
    }
  }
  return 0;
}
