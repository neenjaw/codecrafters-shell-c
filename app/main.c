#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_INPUT_LENGTH = 100;
const int MAX_ARGV = 10;

bool str_starts_with(const char *str, const char *prefix)
{
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

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

typedef int (*command_handler_t)(char *argv[]);

struct command
{
  const char *name;
  command_handler_t handler;
};

/**
 * Exit command handler
 */
int exit_command(char *argv[])
{
  int code = strtol(argv[1], NULL, 10);
  exit(code);
}

int echo_command(char *argv[])
{
  const int FIRST = 1;
  for (int i = FIRST; i < MAX_ARGV; i++)
  {
    if (argv[i] == NULL)
    {
      break;
    }

    if (i == FIRST)
    {
      printf("%s", argv[i]);
    }
    else
    {
      printf(" %s", argv[i]);
    }
  }
  printf("\n");
  return 0;
}

/**
 * List of commands
 */
struct command commands[] = {
    {"exit", &exit_command},
    {"echo", &echo_command}};

/**
 * Get the command handler for the given command
 */
command_handler_t get_command_handler(const char *command)
{
  for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
  {
    if (strcmp(commands[i].name, command) == 0)
    {
      return commands[i].handler;
    }
  }
  return NULL;
}

int main()
{
  // Flush after every printf
  setbuf(stdout, NULL);

  while (true)
  {
    // Print prompt
    printf("$ ");

    // Wait for user input
    char input[MAX_INPUT_LENGTH];
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Remove trailing newline
    input[strcspn(input, "\n")] = '\0';

    // Parse input into argv
    char *argv[MAX_ARGV];
    int argc = 0;
    parse_argv_from_input(input, argv, &argc, MAX_ARGV);

    if (argc == 0)
    {
      continue;
    }

    // Get the possible command
    const char *command = argv[0];

    // Get the command handler
    const command_handler_t handler = get_command_handler(command);

    // If the command exists, call the handler
    if (handler != NULL)
    {
      handler(argv);
    }
    else
    {
      // Handle invalid command input
      printf("%s: command not found\n", input);
    }
  }

  return 0;
}
