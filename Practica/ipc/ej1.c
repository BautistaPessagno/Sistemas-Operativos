#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/semaphore.h>

sem_t my_sem;

void my_init(int *s, int initial_value) { *s = initial_value; }

void my_down(int *s) {
  sem_wait(&my_sem);
  // mientras que sem sea 0 lo devuelve
  while (*s <= 0) {
    sem_post(&my_sem);
    sem_wait(&my_sem);
  }
  (*s)--;
  sem_post(&my_sem);
}

void up(int *s) {
  sem_wait(&my_sem);
  (*s)++;
  sem_post(&my_sem);
}
