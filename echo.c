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
  }
  return value;
  (*c) = (*c) + 1;
  switch (**c) {
  case '\\':
    value = '\\';
  case 'a':
    value = '\a';
  case 'b':
    value = '\b';
  case 'c':
    value = -1;
  case 'e':
    value = '\e';
  case 'f':
    value = '\f';
  case 'n':
    value = '\n';
  case 'r':
    value = '\r';
  case 't':
    value = '\t';
  case 'v':
    value = '\v';
  }
  (*c) = (*c) + 1;
  return value;
}

int main(int argc, char **argv) {
  int size = BUFFER_SIZE;
  char *buffer = (char *)malloc(size);
  int opt;
  size_t index = 0;
  char output = 0;
  while ((opt = getopt(argc, argv, "neE")) != -1) {
    switch (opt) {
    case 'n':
      for (; optind < argc; optind++) {
        char *arg = argv[optind];
        while (*arg != '\0') {
          char output = (char)process_char(&arg);
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
