
#include <semaphore.h>

/*
Tiene que ocurrir de la siguiente manera:

a1 antes que b2 y b1 antes que a2.
Posibles casos

a1->b2->b1->a2
a1->b1->b2->a2
a1->b1->a2->b2

 b1->a1->b2->a2
 b1->a2->a1->b2
 b1->a1->a2->b2


 */

sem_t b1_done;

sem_t a1_done;

void init_sem() {
  sem_init(&a1_done, 1, 1);
  sem_init(&b1_done, 1, 1);
}
// proceso A

void a1() {}

void a2() {}

void proceso_A() {

  a1();
  sem_post(&a1_done);
  sem_wait(&b1_done);
  a2();
}

// proceso B

void b1() {}

void b2() {}

void proceso_B() {
  b1();
  sem_post(&b1_done);
  sem_wait(&a1_done);
  b2();
}
