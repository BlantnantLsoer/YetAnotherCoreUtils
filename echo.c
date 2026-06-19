#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FORMATTED true
#define UNFORMATTED false

int process_char(char **c, bool formatted) {
  int value;
  if (**c != '\\' || !formatted) {
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

void print(char **arg, bool formatted) {
  while (**arg != '\0') {
    int output = process_char(arg, formatted);
    if (output == -1) {
      break;
    }
    printf("%c", output);
  }
}

void print_input(int argc, char ***argv, bool formatted) {
  if (optind == 1)
    return;
  for (; optind < argc; optind++) {
    char *arg = (*argv)[optind];
    print(&arg, formatted);
  }
}
int main(int argc, char **argv) {
  int opt;
  opterr = 0;
  bool invalid = false;
  bool n_argument = false;
  while ((opt = getopt(argc, argv, "+neE")) != -1) {
    if (opt == 'n')
      n_argument = true;
    switch (opt) {
    case '?':
      if (invalid)
        break;
      char *arg = argv[1];
      print(&arg, FORMATTED);
      printf(" ");
      for (size_t i = 2; i < argc; i++) {
        arg = (argv)[i];
        print(&arg, FORMATTED);
      }
      printf("\n");
      invalid = true;
      break;
    case 'n':
      if (!invalid)
        print_input(argc, &argv, FORMATTED);
      break;
    case 'e':
      if (!invalid)
        print_input(argc, &argv, FORMATTED);
      break;
    case 'E':
      if (!invalid)
        print_input(argc, &argv, UNFORMATTED);
      break;

    default:
      if (!invalid)
        print_input(argc, &argv, FORMATTED);
      break;
    }
  }

  if (optind == 1) {
    char *arg = argv[optind];
    print(&arg, FORMATTED);
    for (optind++; optind < argc; optind++) {
      arg = argv[optind];
      printf(" ");
      print(&arg, FORMATTED);
    }
  }
  if (!n_argument && !invalid)
    printf("\n");

  return 0;
}
