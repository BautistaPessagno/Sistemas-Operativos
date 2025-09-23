#include <semaphore.h>
#include <sys/semaphore.h>

sem_t hay_cupo;
sem_t embarque_mutex;
int alumno_embarcado_count = 0;

void init_sems() {
  sem_init(&hay_cupo, 0, 20);
  sem_init(&embarque_mutex, 0, 1);
}

void embarcar() {}
void partir() {}

void alumno() {
  while (1) {

    sem_wait(&hay_cupo);
    sem_wait(&embarque_mutex);
    alumno_embarcado_count++;
    embarcar();
    sem_post(&embarque_mutex);
  }
}

void embarcacion() {
  while (1) {

    // parte con los que se subieron y parte
    sem_wait(&embarque_mutex);
    partir();

    // una vez que termino, se bajan todos
    // para evitar que suban  bajen al mismo tiempo primero bajo a todos
    while (alumno_embarcado_count != 0) {
      sem_post(&hay_cupo);
      alumno_embarcado_count--;
    }
    // una vez que bajaron todos libero
    sem_post(&embarque_mutex);
  }
}
