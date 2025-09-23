#include <_stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dirent.h>

void printDir(char *dir, int offset);

int main(int argc, char *argv[]) {
  if (argc < 1) {
    printf("Argumentos insuficientes");
    return 1;
  }
  printDir(argv[1], 0);
}

void printDir(char *dir, int offset) {
  struct dirent *dp;
  // abrir el dir
  DIR *dirp = opendir(dir);

  char path[1000];

  if (dirp == NULL) {
    return;
  }

  while ((dp = readdir(dirp)) != NULL) {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..")) {
      if (dp->d_type == DT_DIR)
        printf("d ");
      else if (dp->d_type == DT_REG)
        printf("f ");

      for (size_t i = 0; i < offset; i++) {
        printf("\t");
      }
      printf("%s\n", dp->d_name);

      strcpy(path, dir);
      strcat(path, "/");
      strcat(path, dp->d_name);

      // Llamada recursiva
      printDir(path, offset + 1);
    }
  }

  closedir(dirp);
}
