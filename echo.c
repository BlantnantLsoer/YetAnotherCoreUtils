#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int process_char(char **c) {
  int value;
  if (**c != '\\') {
    value = **c;
    (*c) = (*c) + 1;
    return value;
  }
  (*c) = (*c) + 1;
  switch (**c) {
  case '\\':
    value = '\\';
    break;
  case 'a':
    value = '\a';
    break;
  case 'b':
    value = '\b';
    break;
  case 'c':
    value = -1;
    break;
  case 'e':
    value = '\e';
    break;
  case 'f':
    value = '\f';
    break;
  case 'n':
    value = '\n';
    break;
  case 'r':
    value = '\r';
    break;
  case 't':
    value = '\t';
    break;
  case 'v':
    value = '\v';
    break;
  }
  (*c) = (*c) + 1;
  return value;
}

int main(int argc, char **argv) {
  int size = BUFFER_SIZE;
  char *buffer = (char *)malloc(size);
  int opt;
  size_t index = 0;
  while ((opt = getopt(argc, argv, "neE")) != -1) {
    switch (opt) {
    case 'n':
      for (; optind < argc; optind++) {
        char *arg = argv[optind];
        while (*arg != '\0') {
          int output = process_char(&arg);
          if (output == -1) {
            break;
          }
          printf("%c", output);
        }
      }
      break;
    case 'e':

      printf("Printed out e\n");
      break;
    case 'E':

      printf("Printed out E\n");
      break;

    default:

      break;
    }
  }
  free(buffer);

  return 0;
}
