#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Exercise 21 — dup2 & I/O Redirection
//
// Concept: dup2(oldfd, newfd) makes newfd point to the same thing as oldfd.
// It's how you redirect stdin/stdout to a pipe or file.
//
// For example, to make a child's stdout go into a pipe:
//   dup2(fds[1], STDOUT_FILENO)  // STDOUT_FILENO = 1
// Now anything the child writes to stdout goes into the pipe instead.
//
// This is how "ls | grep .c" works:
//   ls child:   dup2(pipe_write, stdout) → execs ls → ls writes to pipe
//   grep child: dup2(pipe_read, stdin)  → execs grep → grep reads from pipe
//
// After dup2, close the original fd — you don't need it anymore since
// stdin/stdout now point to the pipe.
//
// Tasks:
// 1. Create a pipe
// 2. Fork a child
// 3. Child:
//    - dup2(fds[1], STDOUT_FILENO) to redirect stdout to pipe
//    - close fds[0] and fds[1] (stdout already points to pipe)
//    - execlp("ls", "ls", "-l", NULL)
// 4. Parent:
//    - close fds[1]
//    - read from fds[0] and print what you get
//    - close fds[0]
//    - waitpid
//
// The child never calls write() directly — ls writes to its stdout
// which you've redirected to the pipe. The parent reads ls's output.
//
// Goal: understand how dup2 connects programs to pipes without them
// knowing about it — the foundation of shell I/O redirection.


int main() {
    int fds[2];
    if(pipe(fds) == -1) { return -1; }

    pid_t pid = fork();

    if(pid == -1){
        return -1;
    } else if(pid == 0) { // child process
        dup2(fds[1],STDOUT_FILENO);
        close(fds[0]);
        close(fds[1]);
        execlp("ls","ls","-l", NULL);
    } else { // parent process
        char buf[4096];
        close(fds[1]);
        ssize_t bytes = read(fds[0], buf, sizeof(buf));
        write(1, buf, bytes);
        close(fds[0]);
        waitpid(pid,NULL,0);
    }
    return 0;
}