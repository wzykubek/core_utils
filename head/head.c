#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void show_help() {
  printf("Usage: head [OPTION]...  [FILE]...\n");
  printf("Print the first 10 lines of each FILE to standart output.\n");
  printf("\nMandatory arguments to long options are mandatory for short options too.\n");
  printf("\t-n, --lines NUM\t\tprint the first NUM lines instead of the first 10\n");
  printf("\t\t--help\t\t\tdisplay this help and exit\n");
  printf("\t\t--verbose \t\talways print headers giving file names\n");
  printf("\nThis is samedamci's implementation of head - Unix core utility.\n");
  printf("More informations available on <https://github.com/samedamci/core_utils>\n");
}

int main(int argc, char **argv) {
  int output_lines_num = 10;
  static int verbose_flag;
  int c;
  int option_index = 0;

  if (argc < 2)
    exit(EXIT_FAILURE);

  while (1) {
    static struct option long_options[] = {
      {"verbose", no_argument, 0, 'v'},
      {"quiet", no_argument, 0, 'q'},
      {"bytes", required_argument, 0, 'c'},
      {"lines", required_argument, 0, 'n'},
      {"version", no_argument, 0, 1},
      {"zero-terminated", no_argument, 0, 2},
      {"help", no_argument, 0, 3},
      {0, 0, 0, 0}
    };

    c = getopt_long(argc, argv, "n:c:qzv", long_options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 0:
      if (long_options[option_index].flag != 0)
        break;
      printf("option %s", long_options[option_index].name);
      if (optarg)
        printf(" with arg %s", optarg);
      printf("\n");
      break;
    case 'q':
      // TODO
      break;
    case 'v':
      verbose_flag = 1;
      break;
    case 1:
      printf("%s\n%s\n", "head (samedamci's implementation) 0.1",
          "License ISC.");
    case 2:
      // TODO
      break;
    case 'n':
      output_lines_num = atoi(optarg);
      break;
    case 'c':
      // TODO
      break;
    case '?':
      printf("Try \'head --help\' for more information\n");
      exit(EXIT_FAILURE);
      break;
    case 3:
      show_help();
      exit(EXIT_SUCCESS);
    }
  }

  FILE *fp;
  char *filename = argv[argc - 1];

  fp = fopen(filename, "r");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }

  if (verbose_flag == 1)
    printf("==> %s <==\n", filename);

  char ch;
  int lines = 0;

  while ((ch = fgetc(fp)) != EOF) {
    if (lines == output_lines_num)
      break;
    if (ch == '\n')
      lines++;

    fputc(ch, stdout);
  }

  fclose(fp);
  return 0;
}
