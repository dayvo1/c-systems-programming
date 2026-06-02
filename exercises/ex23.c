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

    return 0;
}
