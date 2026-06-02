#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

// Exercise 22 — Mini Shell
//
// Concept: A shell is just a loop that:
//   1. Prints a prompt
//   2. Reads a line of input
//   3. Parses it into a command + arguments
//   4. Forks a child
//   5. Child execs the command
//   6. Parent waits for child to finish
//   7. Go back to step 1
//
// You have all the pieces. Now put them together.
//
// Useful functions:
//   fgets(buf, size, stdin)   — read a line from the user
//   strtok(str, delim)        — split a string by delimiter
//                               first call: strtok(str, " ")
//                               subsequent calls: strtok(NULL, " ")
//   execvp(cmd, argv[])       — exec using PATH, takes argv array
//
// strtok example:
//   char input[] = "ls -l /tmp";
//   char *token = strtok(input, " ");   // token = "ls"
//   token = strtok(NULL, " ");          // token = "-l"
//   token = strtok(NULL, " ");          // token = "/tmp"
//   token = strtok(NULL, " ");          // token = NULL (end)
//
// argv for execvp must be a NULL-terminated array:
//   char *argv[] = {"ls", "-l", "/tmp", NULL}
//
// Tasks:
// 1. Loop forever printing "mysh> " as your prompt
// 2. Read a line with fgets
// 3. Strip the trailing newline from fgets (\n at end of input)
// 4. Parse the line into tokens using strtok, build an argv array
// 5. Fork a child — child calls execvp(argv[0], argv)
// 6. Parent calls waitpid, then loops back to prompt
// 7. Handle the "exit" command to break the loop and quit
//
// To test:
//   bin/ex22
//   mysh> ls
//   mysh> ls -l
//   mysh> echo hello world
//   mysh> exit
//
// Goal: understand that a shell is just fork+exec in a loop,
// and that you've now built one from scratch.
