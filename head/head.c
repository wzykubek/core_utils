#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Now this implementation support only one file and
// arguments must be in the proper sequence.

int main(int argc, char **argv) {
  int output_lines_num = 11;
  int verbose = 0;

  if ((argc == 2) && !strncmp(argv[1], "-h", 3)) {
    fputs("Usage: head [OPTION] file\n", stdout);
    exit(EXIT_SUCCESS);
  } else if ((argc >= 2) && !strncmp(argv[1], "-n", 3)) {
    output_lines_num = atoi(argv[2]);
  } else if ((argc >= 2) && !strncmp(argv[1], "-v", 3))  {
    verbose = 1;
  }

  FILE *fp;
  char *filename = argv[argc - 1];

  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("%s\n", "Specify filename as last argument.");
    exit(EXIT_FAILURE);
  }

  if (verbose == 1)
    printf("%s%s%s\n", "==> ", filename, " <==");

  char ch;
  int lines = 0;

  while((ch = fgetc(fp)) != EOF) {
    if (lines == output_lines_num)
      break;
    if (ch == '\n')
      lines++;

    fputc(ch, stdout);
  }

  fclose(fp);
  return 0;
}
