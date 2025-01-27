#include "shell.h"

int main()
{
  const config_t shell_config = {
      .path = getenv("PATH")};

  // Flush after every printf
  setbuf(stdout, NULL);

  while (true)
  {
    // Print prompt
    printf("$ ");

    // Wait for user input
    char input[MAX_INPUT_LENGTH];
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Parse input into argv
    input[strcspn(input, "\n")] = '\0';
    char *argv[MAX_ARGV];
    int argc = 0;
    parse_argv_from_input(input, argv, &argc, MAX_ARGV);

    if (argc == 0)
    {
      continue;
    }

    // Get the possible command
    const char *command = argv[0];
    const command_handler_t handler = get_command_handler(command);

    if (handler != NULL)
    {
      handler(argv, &shell_config);
    }
    else
    {
      exec_command(argv, &shell_config);
    }
  }

  return 0;
}
