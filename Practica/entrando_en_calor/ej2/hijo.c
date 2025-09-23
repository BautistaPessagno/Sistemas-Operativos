#include <stdio.h>
#include <unistd.h>

int main() {

  int id = getpid();
  printf("soy el hijo %d\n", id);
}
