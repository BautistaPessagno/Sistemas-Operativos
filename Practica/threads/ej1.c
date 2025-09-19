#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 5

#define ITERATIONS 1000000

pthread_t threads[N];

pthread_mutex_t m;

void *inc_num();

static int num = 0;

// sumar 1000 veces
int main() {
  pthread_mutex_init(&m, NULL);
  for (int i = 0; i < N; i++) {
    pthread_create(&threads[i], NULL, inc_num, NULL);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&m);

  printf("num = %d", num);
}

void *inc_num() {
  for (int i = 0; i < ITERATIONS; i++) {
    pthread_mutex_lock(&m);
    num++;
    pthread_mutex_unlock(&m);
  }
  pthread_exit(NULL);
}
