#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help() {}

static char *input;
static int trailing_newline = 1;
static int escapes_interpretation = 0;

void short_opt(int argc, char **argv, int *j) {
  for (int i = 1; argv[*j][i]; i++) {
    switch (argv[*j][i]) {
    case 'n':
      trailing_newline = 0;
      break;
    case 'e':
      escapes_interpretation = 1;
      break;
    case 'E':
      // default
      break;
    default:
      show_help();
      exit(EXIT_SUCCESS);
    }
  }
}

void echo(char *input) {
  size_t n = strlen(input);
  for (int i = 0; i < n; i++) {
    if (input[i] == '\\') {
      if (escapes_interpretation == 1) {
        switch (input[++i]) {
        case 'n':
          printf("\n");
          break;
        case 't':
          printf("\t");
          break;
        case 'v':
          printf("\v");
          break;
        case 'r':
          printf("\r");
          break;
        case 'a':
          printf("\a");
          break;
        case 'b':
          printf("\b");
          break;
        case 'c':
          return;
          break;
        case 'f':
          printf("\f");
          break;
        case 'e':
          printf("\e");
          break;
        default:
          printf("\\%c", input[i]);
        }
      } else
        printf("\\");
    } else {
      printf("%c", input[i]);
    }
  }

  if (trailing_newline == 1)
    printf("\n");
}

int main(int argc, char **argv) {
  if (argc < 2) exit(EXIT_SUCCESS);
  for (int j = 1; argc - j; j++) {
    if (argv[j][0] == '-') {
      if (strcmp(argv[j], "--version") == 0) {
        puts("version 0.1");
      } else if (strcmp(argv[j], "--help") == 0) {
        show_help();
        exit(EXIT_SUCCESS);
      } else {
        short_opt(argc, argv, &j);
      }
    } else {
      input = argv[j];
    }
  }

  echo(input);
}
