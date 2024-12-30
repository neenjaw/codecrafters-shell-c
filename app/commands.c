#include "shell.h"

struct command commands[] = {
    {"exit", &exit_command},
    {"echo", &echo_command},
    {"type", &type_command}};

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

int type_command(char *argv[])
{
  const char *command_name = argv[1];
  if (command_name == NULL)
  {
    printf("type: missing command argument\n");
    return 1;
  }

  command_handler_t handler = get_command_handler(command_name);
  if (handler != NULL)
  {
    printf("%s is a shell builtin\n", command_name);
    return 0;
  }

  printf("%s: not found\n", command_name);
  return 1;
}

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
