#include "shell.h"

/**
 * Parse the input string into argv array
 * Caveat: Prevents overflow of argv, but doesn't handle the case where there are more than max_args tokens
 */
void parse_argv_from_input(char *input, char *argv[], int *argc, const int max_args)
{
  *argc = 0;
  const char delims[] = " \t\n\r\f\v";
  char *token = strtok(input, delims);
  while (token != NULL && *argc < max_args)
  {
    argv[(*argc)++] = token;
    token = strtok(NULL, " ");
  }
  argv[*argc] = NULL;
}
