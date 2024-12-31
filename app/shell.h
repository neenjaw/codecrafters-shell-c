#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGV 10

typedef struct
{
  const char *path;
} config_t;

typedef int (*command_handler_t)(char *argv[], const config_t *config);

typedef struct
{
  const char *name;
  command_handler_t handler;
} command_t;

// Command function prototypes
int exit_command(char *argv[], const config_t *config);
int echo_command(char *argv[], const config_t *config);
int type_command(char *argv[], const config_t *config);
command_handler_t get_command_handler(const char *command_name);
char *find_command_in_path(const config_t *config, const char *command_name);

// Helper function prototypes
void parse_argv_from_input(char *input, char *argv[], int *argc, const int max_args);
bool str_starts_with(const char *str, const char *prefix);

#endif // SHELL_H
