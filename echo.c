#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
  int size = BUFFER_SIZE;
  char *buffer = (char *)malloc(size);
  int c;
  size_t index = 0;
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      printf("%s ", argv[i]);
    }
  }
  printf("\n");
  free(buffer);

  return 0;
}
