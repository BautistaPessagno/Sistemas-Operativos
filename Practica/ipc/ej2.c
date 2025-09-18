#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/semaphore.h>

#define N 5

sem_t forks[N];

void eat() {}
void think() {}

void filosofo(int id) {
  while (1) {
    // casi 1: numero par
    if (id % 2 == 0) {
      sem_wait(&forks[id]);
      sem_wait(&forks[(id + 1) % N]);
    }
    // caso contrario espero al reves
    else {
      sem_wait(&forks[(id + 1) % N]);
      sem_wait(&forks[id]);
    }
    // una vez que tiene los dos come
    eat();
    // deja los tenedores
    sem_post(&forks[id]);
    sem_post(&forks[id]);
    think();
  }
}
