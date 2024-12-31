#include "shell.h"

command_t commands[] = {
    {"exit", &exit_command},
    {"echo", &echo_command},
    {"type", &type_command}};

/**
 * Exit command handler
 */
int exit_command(char *argv[], const config_t *config)
{
  int code = strtol(argv[1], NULL, 10);
  exit(code);
}

int echo_command(char *argv[], const config_t *config)
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

int type_command(char *argv[], const config_t *config)
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

  char *full_command_path = find_command_in_path(config, command_name);
  if (full_command_path != NULL)
  {
    printf("%s is %s\n", command_name, full_command_path);
    free(full_command_path);
    return 0;
  }

  printf("%s: not found\n", command_name);
  return 1;
}

/**
 * Get the command handler for the given command
 */
command_handler_t get_command_handler(const char *command_name)
{
  for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
  {
    if (strcmp(commands[i].name, command_name) == 0)
    {
      return commands[i].handler;
    }
  }
  return NULL;
}

char *find_command_in_path(const config_t *config, const char *command_name)
{
  char *path = strdup(config->path);
  if (path == NULL)
  {
    return NULL;
  }

  char *dir;
  char *token = strtok(path, ":");

  while (token != NULL)
  {
    // Construct the full path to the executable
    char *full_path = malloc(strlen(token) + strlen("/") + strlen(command_name) + 2);
    if (full_path == NULL)
    {
      perror("malloc");
      return NULL;
    }
    sprintf(full_path, "%s/%s", token, command_name);

    // Check if the file exists and is executable
    if (access(full_path, X_OK) == 0)
    {
      return full_path; // Return the full path
    }

    free(full_path);
    token = strtok(NULL, ":");
  }

  return NULL; // Command not found
}
