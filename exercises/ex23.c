#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

// Exercise 23 — Shell with Pipes
//
// Concept: When you type "ls | grep .c" in a shell, the shell:
//   1. Detects the "|" in the input
//   2. Creates a pipe
//   3. Forks two children
//   4. Left child:  stdout → pipe write end, then execs "ls"
//   5. Right child: stdin  → pipe read end,  then execs "grep .c"
//   6. Parent closes both pipe ends and waits for both children
//
// You built all the pieces:
//   ex20 — pipes
//   ex21 — dup2 to redirect stdout/stdin
//   ex22 — shell loop with fork+exec
//
// Now combine them.
//
// Tasks:
// 1. Start with your ex22 shell loop
// 2. After reading input, check if any token is "|"
//    Hint: scan argv after building it, find the index of "|"
// 3. If no pipe found — run the command normally (same as ex22)
// 4. If pipe found:
//    a. Split argv into left[] and right[] at the "|"
//       left[]  = tokens before "|", NULL-terminated
//       right[] = tokens after  "|", NULL-terminated
//    b. Create a pipe: pipe(fds)
//    c. Fork first child (left command):
//       - dup2(fds[1], STDOUT_FILENO) — redirect stdout to pipe
//       - close fds[0] and fds[1]
//       - execvp(left[0], left)
//       - exit(1)
//    d. Fork second child (right command):
//       - dup2(fds[0], STDIN_FILENO)  — redirect stdin from pipe
//       - close fds[0] and fds[1]
//       - execvp(right[0], right)
//       - exit(1)
//    e. Parent:
//       - close fds[0] and fds[1]
//       - waitpid for both children
//
// To test:
//   bin/ex23
//   mysh> ls
//   mysh> ls | grep .c
//   mysh> echo hello world | grep hello
//   mysh> exit
//
// Note: only handle one pipe for now (two commands). 
// Multiple pipes (a | b | c) are an extension.
//
// Goal: understand that "|" in a shell is just pipe() + dup2() + fork() + exec(),
// and that you've now built it yourself.

int main() {

    while(1) {
        printf("mysh> ");
        char usr_input[1024];
        fgets(usr_input, sizeof(usr_input), stdin);
        char* argv[64];
        usr_input[strcspn(usr_input, "\n")] = '\0';
        char* command = strtok(usr_input, " ");
        int i = 0;
        argv[i++] = command;
        while(command != NULL) {
            command = strtok(NULL, " ");
            argv[i++] = command;
        }
        if(argv[0] == NULL) { continue; }
        int fds[2];
        int pipe_idx = -1;
        char* left[64];
        char* right[64];
        for(int j = 0; j < i; j++) {
            if(argv[j] != NULL && strcmp(argv[j], "|") == 0) {
                if(pipe(fds) == -1) { return -1; }
                pipe_idx = j;
            }
        }

        if(pipe_idx != -1) {
            for(int k = 0; k < pipe_idx; k++) {
                left[k] = argv[k];
            }
            left[pipe_idx] = NULL;

            for(int l = pipe_idx + 1; l < i; l++) {
                right[l - (pipe_idx +1)] = argv[l];
            }

            pid_t child_1 = fork();
            if(child_1 == -1) {
                return -1;
            } else if(child_1 == 0) {
                dup2(fds[1], STDOUT_FILENO);
                close(fds[0]);
                close(fds[1]);
                execvp(left[0], left);
                exit(1);
            }

            pid_t child_2 = fork();
            if(child_2 == -1) {
                return -1;
            } else if(child_2 == 0) {
                dup2(fds[0], STDIN_FILENO);
                close(fds[0]);
                close(fds[1]);
                execvp(right[0], right);
                exit(1);
            }

            close(fds[0]);
            close(fds[1]);
            waitpid(child_1, NULL, 0);
            waitpid(child_2, NULL, 0);
            
        } else {
            if(strcmp(argv[0], "exit") == 0) { break; }
            pid_t pid = fork();
            if(pid == -1) { return -1; }
            else if(pid == 0) { execvp(argv[0], argv); exit(1); }
            else { waitpid(pid, NULL, 0); }
        }
        
    }   
    return 0;
}
