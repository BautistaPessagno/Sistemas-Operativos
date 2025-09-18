/* Un pequeño local comercial del centro tiene un único baño para sus empleados,
 * los cuales son de ambos sexos. El dueño desea que su */
/* uso sea exclusivo para un único sexo y para ello instaló una señal con 3
 * posiciones en la puerta: */
/* LIBRE, MUJERES, HOMBRES */
/* Ahora necesita capacitar al personal para que use el baño de forma adecuada.
 * Para esto solicita instrucciones precisas (código) para */
/* ambos sexos, que garanticen que en ningún momento habrá personas de distintos
 * sexos dentro del baño. */

// el como el hombre va al baño es analogo a la mujer
#include <semaphore.h>
#include <sys/semaphore.h>
#include <sys/wait.h>
#define HOMBRE 1
#define MUJER 0

sem_t men_count_mutex;
int men_count = 0;

sem_t women_count_mutex;

int women_count = 0;

sem_t toilet_mutex; // 0 ocupado, 1 libre

void set_sems() {

  // sem_t men_count_mutex = 1;
  sem_init(&men_count_mutex, 1, 1);

  // sem_t women_count_mutex = 1;
  sem_init(&women_count_mutex, 1, 1);

  // sem_t toilet_mutex = 1;
  sem_init(&toilet_mutex, 1, 1);
}

void use_toilet() {}

void woman() {
  while (1) {
    // entrar al baño
    sem_wait(&women_count_mutex);

    if (women_count++ == 0) {  // es la primera
      sem_wait(&toilet_mutex); // espera al semaforo de si esta libre y lo marca
                               // como usado
      // esto asegura que solo existan hombres o mujerees
    }
    sem_post(&women_count_mutex);

    use_toilet();

    // salir del baño
    //// si sale la ultima habilito tanto para hombre como mujer
    sem_wait(&women_count_mutex);
    if (--women_count == 0) {
      sem_post(&toilet_mutex);
    }
    sem_post(&women_count_mutex);
  }
}

void men() {
  while (1) {
    // entrar al baño
    sem_wait(&men_count_mutex);
    if (men_count++ == 0) {    // es la primera
      sem_wait(&toilet_mutex); // espera al semaforo de si esta libre y lo marca
                               // como usado
    }
    sem_post(&men_count_mutex);

    use_toilet();

    // salir del baño
    // si sale la ultima habilito tanto para hombre como mujer
    sem_wait(&men_count_mutex);
    if (--men_count == 0) {
      sem_post(&toilet_mutex);
    }
    sem_post(&men_count_mutex);
  }
}
