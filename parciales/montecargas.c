/* En un hotel hay vehículos automáticos pequeños y grandes, cada uno de ellos
 * representado por un proceso concurrente. Estamos interesados en controlar la
 * entrada de dichos vehículos en un montacargas, en el que caben hasta 4
 * vehículos pequeños o 2 pequeños y 1 grande. Resolver el problema usando
 * semáforos. */

#include <semaphore.h>
#include <sys/semaphore.h>

int small_car_count = 0;
int big_car_count = 0;
sem_t montacargas_mutex;
sem_t grande_mutex;
sem_t montecargas_space;
sem_t space_available;
sem_t chico_mutex;

void init_sems() {
  sem_init(&montacargas_mutex, 0, 1);
  sem_init(&grande_mutex, 0, 1);
  sem_init(&space_available, 0, 4);
  sem_init(&chico_mutex, 0, 1);
}

void big() {
  while (1) {
    sem_wait(&montacargas_mutex);
    // una vez que tiene acceso se fija si ya hay un grande
    sem_wait(&grande_mutex);
    // hay lugar entonces usa dos
    sem_wait()
  }
}

void small() {}
