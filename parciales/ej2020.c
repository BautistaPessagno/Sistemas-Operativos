#include <semaphore.h>
#include <stdio.h>
#include <sys/semaphore.h>

sem_t car_mutex;
sem_t detergente_mutex;
sem_t detergente_disponible_prelavado;
sem_t detergente_disponible_lavado;

sem_t pistola_secadora;

void init_sems() {
  //puede sacar 4 veces 5 litros
  sem_init(&detergente_disponible_prelavado, 1, 4);
  sem_init(&detergente_disponible_lavado, 1, 5);
  sem_init(&car_mutex, 1, 0);
  sem_init(&detergente_mutex, 1, 1);
  sem_init(&pistola_secadora, 1, 3);
}

void robots() {
  while (1) {
    sem_wait(&car_mutex);
    // region critica del manejo de detergente
    //en el pre lavado solo se puede sacar hasta 20 litros
    //para evitar deadlock
    sem_wait(&detergente_mutex);
    sem_wait(&detergente_disponible_lavado);
    sem_wait(&detergente_disponible_prelavado);

    // pre lavado

    sem_post(&detergente_mutex);

    //consigo otros 5 para el lavado
    sem_wait(&detergente_mutex);


    // agarro otros 5
    sem_wait(&detergente_disponible_lavado);

    //lavado

    sem_post(&detergente_mutex);

    // lavado final

    // devuelvo todo
    sem_wait(&detergente_mutex);
    
    sem_post(&detergente_disponible_lavado);
    sem_post(&detergente_disponible_prelavado);


    sem_post(&detergente_mutex);

    // agarro la pistola
    sem_wait(&pistola_secadora);
    // la uso
    sem_post(&pistola_secadora);

    sem_post(&car_mutex);
  }
}
