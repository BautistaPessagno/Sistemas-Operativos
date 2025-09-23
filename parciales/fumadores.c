/* El problema de los fumadores de cigarrillos (Patil 1971).
 * Considere un sistema con tres procesos fumadores y un proceso agente.
 * Cada fumador está continuamente armando y fumando cigarrillos.
 * Sin embargo, para armar un cigarrillo, el fumador necesita tres ingredientes:
 * tabaco, papel y fósforos. Uno de los procesos fumadores tiene papel, otro
 * tiene el tabaco y el tercero los fósforos. El agente tiene una cantidad
 * infinita de los tres materiales. El agente coloca dos de los ingredientes
 * sobre la mesa. El fumador que tiene el ingrediente restante armaría un
 * cigarrillo y se lo fuma, avisando al agente cuando termina. Entonces, el
 * agente coloca dos de los tres ingredientes y se repite el ciclo. Escriba un
 * programa para sincronizar al agente y los fumadores utilizando semáforos. */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/semaphore.h>
#include <time.h>

#define PAPEL 0
#define TABACO 1
#define FOSFORO 2

sem_t materiales[3]; // caso 1: fosforo y tabaco. Caso 2: Papel y fosoforo. Caso
                     // 3: papel y tabaco
sem_t materiales_done;

void init_sems() {
  for (int i = 0; i < 3; i++)
    sem_init(&materiales[i], 0, 0);
  sem_init(&materiales_done, 0, 1);
}

// lo que tienen esta asociado al ID
void fumador(int id) {
  while (1) {
    sem_wait(&materiales[id]);
    // fumar
    sem_post(&materiales_done);
  }
}

void agente() {
  while (1) {
    srand(time(NULL));
    sem_wait(&materiales_done);
    int r = rand() % 3;
    sem_post(&materiales[r]);
  }
}
