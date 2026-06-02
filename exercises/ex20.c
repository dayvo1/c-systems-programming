#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

// Exercise 20 — Pipes
//
// Concept: A pipe is a one-way communication channel between two processes.
// One process writes to one end, another reads from the other end.
// This is how shell pipes work: ls | grep .c
// ls writes to the pipe, grep reads from it.
//
// pipe(int fds[2]) creates a pipe and gives you two file descriptors:
//   fds[0] — read end
//   fds[1] — write end
//
// After fork(), both parent and child have both ends open.
// You must close the end you don't use in each process — otherwise
// the reader will block forever waiting for the write end to close.
//
// Tasks:
// 1. Call pipe() to create a pipe — check for failure
// 2. fork() a child process
// 3. Child (writer):
//    - close fds[0] (read end — child doesn't need it)
//    - write "hello from child\n" to fds[1]
//    - close fds[1]
//    - exit(0)
// 4. Parent (reader):
//    - close fds[1] (write end — parent doesn't need it)
//    - read from fds[0] into a buffer
//    - print what was read
//    - close fds[0]
//    - waitpid for child
//
// Goal: understand how pipes connect processes and why closing
// unused ends is critical for the pipe to work correctly.


int main() {
    int fds[2];
    if(pipe(fds) == -1) { return -1; }

    pid_t pid = fork();

    if(pid == -1){ 
        return -1;
    } else if(pid == 0) {
        close(fds[0]);
        write(fds[1], "Hello from child\n", sizeof("Hello from child\n"));
        close(fds[1]);
        exit(0);
    } else {
        char* buf = malloc(64);
        close(fds[1]);
        read(fds[0], buf, 64);
        printf("printed from buf: %s", buf);
        close(fds[0]);
        waitpid(pid, NULL, 0);
        free(buf);
        printf("fds[0]: %d\nfds[1]: %d\n",fds[0],fds[1]);
    }

    return 0;
}