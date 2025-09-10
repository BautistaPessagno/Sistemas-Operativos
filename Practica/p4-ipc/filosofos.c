#include <semaphore.h>

#define N 5

// un semaforo por tenedor
sem_t forks[N];

void filosofo(int id) {

  while (1) {
    if (id % 2 == 0) {
      // toma el derecho primero
      down(&forks[(id + 1) % N]);

      down(&forks[id]);
    } else {
      down(&forks[id]);

      down(&forks[(id + 1)]);
    }
    // si tiene los dos come
    // eat()

    up(&forks[id]);
    up(&forks[(id + 1)]);
  }
}
