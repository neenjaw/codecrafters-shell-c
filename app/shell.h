#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGV 10

struct config
{
  char *path;
};
extern struct config config;

typedef int (*command_handler_t)(char *argv[]);

struct command
{
  const char *name;
  command_handler_t handler;
};
extern struct command commands[];

// Command function prototypes
int exit_command(char *argv[]);
int echo_command(char *argv[]);
int type_command(char *argv[]);
command_handler_t get_command_handler(const char *command);

// Helper function prototypes
void parse_argv_from_input(char *input, char *argv[], int *argc, const int max_args);
bool str_starts_with(const char *str, const char *prefix);

#endif // SHELL_H
