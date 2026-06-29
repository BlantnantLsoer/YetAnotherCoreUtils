#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int index_argc = 0;
void processArguments(int argc, char **argv) {
  char *opts = "AbeEnstTuv";
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      continue;
    }
    char *ptr = argv[i] + 1;
    while (*ptr) {
      if (strchr(opts, *ptr) == NULL) {
        printf("cat: invalid option -- '%c'\n", *ptr);
        exit(EXIT_FAILURE);
      }
      ptr++;
    }
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      continue;
    }
    char *ptr = argv[i] + 1;
    while (*ptr) {
      switch (*ptr) {
      case 'A':
        puts("yay");
        break;
      case 'b':
        break;
      case 'e':
        break;
      case 'E':
        break;
      case 's':
        break;
      case 't':
        break;
      case 'T':
        break;
      case 'u':
        break;
      case 'v':
        break;
      }
      ptr++;
    }
  }
}

int main(int argc, char **argv) {
  // processArguments(argc, argv);
  if (argc < 2 || strcmp(argv[index_argc], "-") == 0) {
    int c;
    while (1) {
      c = getchar();
      if (c == EOF) {
        break;
      }
      putchar(c);
    }
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-") == 0) {
      int c;
      while (1) {
        c = getchar();
        if (c == EOF) {
          break;
        }
        putchar(c);
      }
      continue;
    }
    FILE *f = fopen(argv[i], "r");
    if (f == NULL) {
      perror("fopen");
      return 1;
    }
    fseek(f, 0, SEEK_END);
    unsigned int bytes = ftell(f);
    fseek(f, 0, SEEK_SET);
    int c;
    while ((c = fgetc(f)) != EOF) {
      putchar(c);
    }
    fclose(f);
  }

  return 0;
}
