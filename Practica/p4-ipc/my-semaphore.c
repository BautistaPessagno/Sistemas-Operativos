#include <semaphore.h>

sem_t my_sem;

void my_init(int *s, int initial_value) { *s = initial_value; }

void down(int *s) {
  sem_wait(&my_sem);

  // lo desbloquea si s es mayor a 0
  while (*s <= 0) {
    sem_post(&my_sem);
    sem_wait(&my_sem);
  }
  // una vez que lo recibe decrementa
  (*s)--;
  sem_post(&my_sem);
}

void my_up(int *s) {
  sem_wait(&my_sem);
  (*s)++;
  sem_post(&my_sem);
}
