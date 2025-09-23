#include <semaphore.h>
#include <stdlib.h>
#include <sys/semaphore.h>

#define PAPEL 0
#define TABACO 1
#define FOSFORO 2

sem_t table_mutex;
sem_t fumador_ready;
sem_t table_ready;
int materials[2];

void init_sems() {
  sem_init(&table_mutex, 0, 1);
  sem_init(&fumador_ready, 0, 1);
  sem_init(&table_ready, 0, 0);
}

// el id corresponde a lo que tiene
void fumador(int id) {
  while (1) {
    sem_wait(&table_ready);

    sem_wait(&table_mutex);

    char complements = 1;
    for (int i = 0; i < 2; i++) {
      if (materials[i] == id) {
        complements = 0;
        break;
      }
    }
    if (complements) {
      // agarra los materiales que le faltan
      // arma el cigarrillo
      // fuma
      sem_post(&fumador_ready);
    }

    sem_post(&table_mutex);
  }
}

void agente() {
  while (1) {
    sem_wait(&fumador_ready);

    sem_wait(&table_mutex);
    int r = rand() % 3;

    materials[0] = (r + 1) % 3;
    materials[1] = (r + 2) % 3;

    sem_post(&table_mutex);

    for (int i = 0; i < 3; i++)
      sem_post(&table_ready);
  }
}
