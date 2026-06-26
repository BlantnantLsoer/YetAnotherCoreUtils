#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool newline_argument = false;
bool escape_argument = true;
int index_argc = 1;

int process_switch_statement(char **c) {
  int value;
  char character = **c;

  // Process hex
  if (character == 'x') {
    char buffer[3];
    buffer[2] = '\0';
    for (int i = 0; i < 3; i++) {
      buffer[i] = (*c + 1)[i];
    }
    char *endptr = NULL;
    long v = strtol(buffer, &endptr, 16);
    if (endptr == buffer) {
      // no hex digit
      *c = *c + 1;
      return -2;
    }
    value = (int)v;
    *c = *c + 2;
    return value;
  }

  // Process octal
  if (character == '0') {
    char buffer[4];
    for (int i = 0; i < 4; i++) {
      buffer[i] = (*c + 1)[i];
    }
    char *endptr = NULL;
    long v = strtol(buffer, &endptr, 16);
    if (endptr == buffer) {
      // no octal digit
      *c = *c + 1;
      return -2;
    }
    *c = *c + 3;
    value = (int)v;
    return value;
  }
  switch (character) {
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
  return value;
}
int process_char(char **c) {
  int value = **c;
  // If it's not formatted, doesn't matter what character it is, return
  if (!escape_argument) {
    (*c) = (*c) + 1;
    return value;
  }
  // If it's not a backslash, don't care, return
  if (value != '\\') {
    (*c) = (*c) + 1;
    return value;
  }

  (*c) = (*c) + 1;
  // It is formatted AND a backslash
  // Parse which escape character
  value = process_switch_statement(c);
  if (value == -2) {
    value = process_char(c);
  }
  // Advance string after finishing parsing
  (*c) = (*c) + 1;
  return value;
}

void print(char *arg) {
  while (*arg != '\0') {
    int output = process_char(&arg);
    if (output == -1) {
      newline_argument = true;
      break;
    }
    printf("%c", output);
  }
}

void print_input(int argc, char **argv) {
  for (; index_argc < argc; index_argc++) {
    char *arg = argv[index_argc];
    print(arg);
    if (index_argc < argc - 1)
      printf(" ");
  }
}

void processArguments(int argc, char **argv) {
  bool invalid_args = false;
  for (int i = index_argc; i < argc; i++) {
    if (argv[i][0] != '-') {
      index_argc = i;
      break;
    }
    char *ptr = argv[i] + 1;
    while (*ptr != '\0') {
      if (*ptr == 'n' || *ptr == 'e' || *ptr == 'E') {
        switch (*ptr) {
        case 'n':
          newline_argument = true;
          break;
        case 'e':
          escape_argument = true;
          break;
        case 'E':
          escape_argument = false;
          break;
        }
        ptr++;
      } else {
        invalid_args = true;
        index_argc = i;
        break;
      }
    }
    if (invalid_args)
      break;
  }
}
int main(int argc, char **argv) {
  processArguments(argc, argv);
  print_input(argc, argv);
  if (!newline_argument)
    printf("\n");

  return 0;
}
