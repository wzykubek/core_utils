#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int numerate = 0;
static char *filename = "\0";
static FILE *input;

void show_help() {}

void short_opt(int argc, char **argv, int *j) {
  for (int i = 1; argv[*j][i]; i++) {
    switch (argv[*j][i]) {
    case 'n':
      numerate = 1;
      break;
    default:
      show_help();
      exit(0);
    }
  }
}

int main(int argc, char **argv) {
  input = stdin;

  for (int j = 1; argc - j; j++) {
    if (argv[j][0] == '-') {
      if (strcmp(argv[j], "--version") == 0) {
        puts("version 0.1");
      } else if (strcmp(argv[j], "--help") == 0) {
        show_help();
        exit(0);
      } else {
        short_opt(argc, argv, &j);
      }
    } else {
      filename = argv[j];
    }
  }

  if (filename[0] != '\0')
    input = fopen(filename, "r");

  if (input == NULL)
    exit(EXIT_FAILURE);

  int line_num =1;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  while ((read = getline(&line, &len, input)) != EOF) {
    if (numerate == 1) {
      printf("\t%d\t%s", line_num, line);
      ++line_num;
    } else
      printf("%s", line);
  }

  fclose(input);
  return 0;
}
