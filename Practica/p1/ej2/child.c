#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  unsigned int seed = (unsigned int)(time(NULL) ^ getpid());
  srand(seed);
  int sleep_seconds = (rand() % 5) + 1; // 1..5 segundos

  printf("Hijo PID=%d: durmiendo %d s\n", (int)getpid(), sleep_seconds);
  fflush(stdout);
  sleep((unsigned int)sleep_seconds);
  printf("Hijo PID=%d: terminé\n", (int)getpid());
  return sleep_seconds % 2; // devuelve 0 o 1 como código de salida
}


