#include <stdio.h>
#include <string.h>

int main()
{
  // Flush after every printf
  setbuf(stdout, NULL);

  // Print prompt
  printf("$ ");

  // Wait for user input
  char input[100];
  fgets(input, 100, stdin);

  // Remove trailing newline
  input[strcspn(input, "\n")] = 0;

  // Handle invalid command input
  printf("%s: command not found\n", input);

  return 0;
}
