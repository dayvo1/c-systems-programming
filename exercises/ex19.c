#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Exercise 19 — Processes & exec()
//
// Concept: fork() creates a copy of your process. exec() replaces the current
// process with a completely different program. Together they're how the shell
// works — when you type "ls", the shell forks itself, then the child calls
// exec("ls") which replaces the child with the ls program.
//
// exec family:
//   execl(path, arg0, arg1, ..., NULL)   — list of args
//   execv(path, argv[])                  — array of args
//   execlp(name, arg0, ..., NULL)        — search PATH for program
//
// The last argument must always be NULL — that's how exec knows where args end.
// If exec succeeds, it never returns — the process is replaced.
// If exec fails, it returns -1.
//
// waitpid(pid, &status, 0) — parent waits for a specific child to finish
//
// Tasks:
// 1. fork() a child process
// 2. In the child, use execl() to run "/bin/ls" with args: "ls", "-l", NULL
// 3. In the parent, use waitpid() to wait for the child to finish
// 4. After waitpid returns, print "child finished"
// 5. Fork a second child and use execlp() to run "echo" with "hello from echo"
//    Wait for it too
//
// Goal: understand how fork+exec is the foundation of how every shell
// runs programs, and why they are two separate operations.


int main() {
    pid_t child_1 = fork();
    if(child_1 == -1){
        return -1;
    }
    else if(child_1 == 0){
        execl("/bin/ls", "ls", "-l", NULL);
        exit(1);
    } else {
        int status;
        waitpid(child_1, &status, 0);
        printf("child 1 finished\n");
    }

    pid_t child_2 = fork();
    if(child_2 == -1){
        return -1;
    }
    else if(child_2 == 0){
        execlp("echo", "echo", "hello from echo", NULL);
    } else {
        int status;
        waitpid(child_2, &status, 0);
        printf("child 2 finished\n");
    }


    return 0;
}