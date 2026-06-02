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

int main() {
        
    while(1) {
        printf("mysh> ");
        char usr_input[1024];
        fgets(usr_input, sizeof(usr_input), stdin);
    
        usr_input[strcspn(usr_input, "\n")] = '\0'; 
        char* command = strtok(usr_input, " ");
        char* argv[64];
        int i = 0;
        argv[i++] = command;
        while(command != NULL) {
            command = strtok(NULL, " ");
            argv[i++] = command;
        }

        if(strcmp(argv[0], "exit") == 0) { break; }
        pid_t pid = fork();

        if(pid == -1) {
            return -1;
        } else if(pid == 0) {
            execvp(argv[0], argv);
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
        
    }
    return 0;
}