/* no pueden haber ratones y gatos en la cocina al mismo tiempo */
/* solo puede haber hasta tres ratones al mismo tiempo */

#include <semaphore.h>
#include <sys/semaphore.h>

int ratones_counter;
sem_t ratones_mutex;
sem_t no_gato_mutex;
sem_t kitchen_mutex;
sem_t max_ratones;

void init_sems() {
  sem_init(&ratones_mutex, 0, 0);
  sem_init(&no_gato_mutex, 0, 1);
  sem_init(&kitchen_mutex, 0, 1);
  sem_init(&max_ratones, 0, 1);
}

void raton() {
  while (1) {

    sem_wait(&no_gato_mutex);
    sem_post(&no_gato_mutex);

    sem_wait(&ratones_mutex);
    /* se fija si ya hay tres ratones */
    if (ratones_counter++ == 0) {
      sem_wait(&kitchen_mutex);
    } else if (ratones_counter >= 3) {
      sem_wait(&max_ratones);
    }
    sem_post(&ratones_mutex);
    // entra
    // hace cosas de ratones...
    // sale

    sem_wait(&ratones_mutex);

    if (--ratones_counter == 0) {
      sem_post(&kitchen_mutex);
    } else if (ratones_counter == 2) {
      sem_post(&max_ratones);
    }
    sem_post(&ratones_mutex);
  }
}

void gato() {
  /* captura el no_gato_mutex para que no entren mas ratones */
  sem_wait(&no_gato_mutex);
  // espera a que se libere
  sem_wait(&kitchen_mutex);
  // cocina libre para el gato
  // entra el gato
  // hace cosas de gatos...
  // ahora sale
  sem_post(&kitchen_mutex);
  sem_post(&no_gato_mutex);
}
