#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// semaphore
sem_t men_mutex;
int men_count;

sem_t women_mutex;
int women_count;

sem_t bathroom_free_mutex;

void init_sems() {
  // se inicializan todos en uno ya que estan todos habilitados en inicio
  sem_init(&men_mutex, 1, 1);
  sem_init(&women_mutex, 1, 1);
  sem_init(&bathroom_free_mutex, 1, 1);
}

void ir_al_bano() {}

void men() {

  // registra que hay un hombre queriendo ir al bano
  sem_wait(&men_mutex);
  if (men_count++ == 0) {
    // si no hay hombres adentro veo si esta habilitado
    sem_wait(&bathroom_free_mutex);
  }
  sem_post(&men_mutex);

  ir_al_bano();

  // ya hizo todo entonces sale
  sem_wait(&men_mutex);
  if (--men_count == 0) {
    sem_post(&bathroom_free_mutex);
  }
  sem_post(&men_mutex);
}

// analogo women
