#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose_flag;
static int output_lines_num = 10;
static char *filename = "\0";
static FILE *input;

void show_help() {
  printf("Usage: head [OPTION]...  [FILE]...\n");
  printf("Print the first 10 lines of each FILE to standart output.\n");
  printf("\nWith no FILE read standard input.\n");
  printf("\nMandatory arguments to long options are mandatory for short "
         "options too.\n");
  printf("\t-n, --lines NUM\t\tprint the first NUM lines instead of the first "
         "10\n");
  printf("\t\t--help\t\t\tdisplay this help and exit\n");
  printf("\t\t--verbose \t\talways print headers giving file names\n");
  printf("\nThis is samedamci's implementation of head - Unix core utility.\n");
  printf("More informations available on "
         "<https://github.com/samedamci/core_utils>\n");
}

void short_opt(int argc, char **argv, int *j) {
  for (int i = 1; argv[*j][i]; i++) {
    switch (argv[*j][i]) {
    case 'v':
      verbose_flag = 1;
      break;
    case 'q':
      break;
    case 'c':
      break;
    case 'n':
      if (*j + 1 < argc)
        output_lines_num = atoi(argv[++*j]);
      return;
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
      if (strcmp(argv[j], "--verbose") == 0) {
        verbose_flag = 1;
      } else if (strcmp(argv[j], "--quiet") == 0) {
        continue;
      } else if (strcmp(argv[j], "--bytes") == 0) {
        continue;
      } else if (strcmp(argv[j], "--lines") == 0) {
        output_lines_num = atoi(argv[++j]);
      } else if (strcmp(argv[j], "--zero-terminated") == 0) {
        continue;
      } else if (strcmp(argv[j], "--version") == 0) {
        continue;
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

  if (verbose_flag == 1) {
    if (filename[0] != '\0')
      printf("==> %s <==\n", filename);
    else
      puts("==> standard input <==");
  }

  char ch;
  int lines = 0;

  while ((ch = fgetc(input)) != EOF) {
    if (lines == output_lines_num)
      break;
    if (ch == '\n')
      lines++;

    fputc(ch, stdout);
  }

  fclose(input);
  return 0;
}
