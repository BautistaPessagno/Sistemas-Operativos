#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 4096
#define ITER_MAX 100000000

int main(void) {
  // llenamos un buffer con datos
  char buffer[BUFF_SIZE];
  for (int i = 0; i < BUFF_SIZE; i++) {
    buffer[i] = 'E';
  }

  int fd = open("tempfile", O_CREAT | O_WRONLY, 0644);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  for (int i = 0; i < ITER_MAX; i++) {
    if (write(fd, buffer, BUFF_SIZE) == -1) {
      perror("write");
      return 1;
      ;
    }
  }

  close(fd);

  return 0;
}
