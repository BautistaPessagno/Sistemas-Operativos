#include <i386/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define QPROCESS 10

int main(int argc, char *argv[]) {

  for (int i = 1; i < QPROCESS; i++) {
    if (fork() == 0) { // si es el hijo entonces
      printf("proceso %d con pid hijo %d y pid %d padre \n", i, getpid(),
             getppid());
      exit(0);
    }
  }
  // el siguiente fork va a entrar al while infinito igual que el proceso padre
  fork();

  while (1) {
  }

  return 0;
}
