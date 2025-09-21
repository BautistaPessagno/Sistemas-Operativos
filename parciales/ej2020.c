#include <semaphore.h>
#include <stdio.h>
#include <sys/semaphore.h>

sem_t car_mutex;
sem_t detergente_mutex;
int detergente_mutex_disponible = 25; // en litros
sem_t detergente_last_5_mutex;
sem_t no_detergente_mutex;
sem_t pistola_secadora;

void init_sems() {
  sem_init(&no_detergente_mutex, 1, 1);
  sem_init(&car_mutex, 1, 0);
  sem_init(&detergente_mutex, 1, 1);
  sem_init(&pistola_secadora, 1, 3);
  sem_init(&detergente_last_5_mutex, 1, 1);
}

void robots() {
  while (1) {
    sem_wait(&car_mutex);
    // region critica del manejo de detergente
    // al ser 5, elijo que uno haga primerop el prelavado y y el lavado antes
    sem_wait(&detergente_mutex);
    sem_wait(&detergente_last_5_mutex);
    // agarro 5
    detergente_mutex_disponible -= 5;

    if (detergente_mutex_disponible > 5)
      sem_post(&detergente_mutex);

    sem_post(&detergente_mutex);

    // pre lavado

    sem_wait(&detergente_mutex);
    sem_wait(&no_detergente_mutex);

    // agarro otros 5
    detergente_mutex_disponible -= 5;

    if (detergente_mutex_disponible != 0)
      sem_post(&no_detergente_mutex);

    sem_post(&detergente_mutex);

    // lavado final

    // devuelvo todo

    sem_wait(&detergente_mutex);

    detergente_mutex_disponible += 10;

    // si previamente ea 0, devuelvo ambos mutex que bvloquea

    if (detergente_mutex_disponible == 10) {
      sem_post(&detergente_last_5_mutex);
      sem_post(&no_detergente_mutex);
    }

    sem_post(&detergente_mutex);

    // agarro la pistola
    sem_wait(&pistola_secadora);
    // la uso
    sem_post(&pistola_secadora);

    sem_post(&car_mutex);
  }
}
