#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void list_directory_recursive(const char *directory_path, int depth) {
  DIR *directory_stream = opendir(directory_path);
  if (directory_stream == NULL) {
    perror("opendir");
    return;
  }

  struct dirent *directory_entry;
  while ((directory_entry = readdir(directory_stream)) != NULL) {
    const char *entry_name = directory_entry->d_name;
    if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0) {
      continue;
    }

    char full_path[PATH_MAX];
    int written = snprintf(full_path, sizeof(full_path), "%s/%s",
                           directory_path, entry_name);
    if (written < 0 || written >= (int)sizeof(full_path)) {
      fprintf(stderr, "Ruta demasiado larga: %s/%s\n", directory_path,
              entry_name);
      continue;
    }

    struct stat entry_stat;
    if (stat(full_path, &entry_stat) != 0) {
      perror("stat");
      continue;
    }

    printf("%*s[%s] %s\n", depth * 2, "",
           S_ISDIR(entry_stat.st_mode) ? "DIR" : "FILE", entry_name);

    if (S_ISDIR(entry_stat.st_mode)) {
      list_directory_recursive(full_path, depth + 1);
    }
  }

  closedir(directory_stream);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <directorio>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *path = argv[1];
  struct stat path_stat;
  if (stat(path, &path_stat) != 0) {
    perror("stat");
    return EXIT_FAILURE;
  }

  if (S_ISDIR(path_stat.st_mode)) {
    printf("[DIR] %s\n", path);
    list_directory_recursive(path, 1);
  } else {
    printf("[FILE] %s\n", path);
  }

  return EXIT_SUCCESS;
}
