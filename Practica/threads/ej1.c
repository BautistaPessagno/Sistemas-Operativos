#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5

#define ITERATIONS 1000000


pthread_t threads[N];

sem_t sem;

void *inc_num();

static int num = 0;

// sumar 1000 veces
int main() {
  sem_init(&sem, 0, 1);
  for (int i = 0; i < N; i++) {
    pthread_create(&threads[i], NULL, inc_num, NULL);
  }
  
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  sem_destroy(&sem);

  printf("num = %d", num);
}

void *inc_num() {
  for (int i = 0; i < ITERATIONS; i++) {
    sem_wait(&sem);
    num++;
    sem_post(&sem);
  } 
  pthread_exit(NULL);
}
