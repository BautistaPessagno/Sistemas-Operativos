#include <semaphore.h>

sem_t mutex_reader;
int mutex_reader_count;

sem_t mutex_writer;
int mutex_writer_count;
sem_t mutex_no_writer_waiting;

sem_t mutex_free;

void access_database() {}

void init_sems() {
  sem_init(&mutex_reader, 1, 1);
  sem_init(&mutex_writer, 1, 1);
  sem_init(&mutex_no_writer_waiting, 1, 1);
  sem_init(&mutex_free, 1, 1);
}

void reader() {
  while (1) {
    // chequea que no existan writerts esperando
    /*como esta inicializado en uno, a menos que ya
     lo hayan tomado no deberia haber problema (creo) */
    sem_wait(&mutex_no_writer_waiting);
    sem_post(&mutex_no_writer_waiting);

    sem_wait(&mutex_reader);
    if (mutex_reader_count++ == 0) {
      sem_wait(&mutex_free);
    }
    sem_post(&mutex_reader);

    access_database();

    sem_wait(&mutex_reader);
    if (--mutex_reader_count == 0) {
      sem_post(&mutex_free);
    }
    sem_post(&mutex_reader);
  }
}

void writer() {
  while (1) {

    sem_wait(&mutex_writer);
    if (mutex_writer_count++ == 0) {

      // captura el no_writer para avisar que hay un writer esperando
      sem_wait(&mutex_no_writer_waiting);
      sem_wait(&mutex_free);
    }

    access_database();

    sem_post(&mutex_writer);

    sem_wait(&mutex_writer);
    if (--mutex_writer_count == 0) {
      sem_post(&mutex_no_writer_waiting);
      sem_post(&mutex_free);
    }
    sem_post(&mutex_writer);
  }
}
