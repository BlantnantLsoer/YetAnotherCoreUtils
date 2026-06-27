#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool newline_argument = false;
bool escape_argument = true;
int index_argc = 1;

int to_hex(char c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  if ('a' <= c && c <= 'f')
    return c - 'a' + 10;
  if ('A' <= c && c <= 'F')
    return c - 'A' + 10;
  return -1;
}

int process_hex(char **c) {
  // Process hex
  char character = *(*c + 1);
  char character_two = *(*c + 2);
  if (!isxdigit(character))
    return '\0';
  if (!isxdigit(character_two)) {
    *c = *c + 1;
    return to_hex(character);
  }
  *c = *c + 2;
  char buf[3];
  buf[2] = '\0';
  buf[0] = character;
  buf[1] = character_two;
  return strtol(buf, NULL, 16);
}

int process_octal(char **c) {
  char buf[4];
  char character = *(*c + 1);
  char character_two = *(*c + 2);
  char character_three = *(*c + 3);
  if (!((character - '0' >= 0 && character - '0' <= 7))) {
    return '\0';
  }
  if (!((character_two - '0' >= 0 && character_two - '0' <= 7))) {
    *c = *c + 1;
    return character - '0';
  }
  if (!((character_three - '0' >= 0 && character_three - '0' <= 7))) {
    *c = *c + 2;
    buf[2] = '\0';
    buf[0] = character;
    buf[1] = character_two;
    return strtol(buf, NULL, 8);
  }
  *c = *c + 3;
  buf[3] = '\0';
  buf[0] = character;
  buf[1] = character_two;
  buf[2] = character_three;
  return strtol(buf, NULL, 8);
}

int process_switch_statement(char **c) {
  int value;
  char character = **c;

  if (character == 'x') {
    return process_hex(c);
  }
  if (character == '0') {
    return process_octal(c);
  }
  // Process octal
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
    exit(EXIT_SUCCESS);
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
  default:
    return -2;
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
    value = *(*c - 1);
    *c = *c - 1;
  }
  // Advance string after finishing parsing
  (*c) = (*c) + 1;
  return value;
}

void print(char *arg) {
  while (*arg != '\0') {
    int output = process_char(&arg);
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
