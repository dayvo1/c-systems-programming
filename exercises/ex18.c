#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// Exercise 18 — System Calls
//
// Concept: Everything your C program does that touches the OS goes through
// system calls. printf, fopen, socket, fork — they all end up as syscalls.
// A syscall is a request from your program to the kernel to do something
// it can't do itself (access hardware, manage processes, network I/O).
//
// You've been using syscalls all along through library wrappers.
// Now you'll use them directly with the lower-level functions:
//
//   open()   instead of fopen()
//   read()   instead of fread()
//   write()  instead of fwrite()/printf()
//   close()  (same as before)
//
// These return file descriptors (ints) just like sockets do.
// write(1, "hello\n", 6) writes to stdout (fd 1).
// read(0, buf, n)        reads from stdin (fd 0).
//
// open() flags:
//   O_RDONLY  — open for reading
//   O_WRONLY  — open for writing
//   O_CREAT   — create if doesn't exist (needs a mode argument)
//   O_TRUNC   — truncate file to 0 on open
//
// #include <fcntl.h> for open() flags
//
// Tasks:
// 1. Use write() to print "Hello from write()\n" to stdout (fd 1)
// 2. Use open() to open "projects/data.txt" for reading (O_RDONLY)
// 3. Use read() to read its contents into a buffer
// 4. Use write() to print the contents to stdout
// 5. close() the file descriptor
// 6. Use open() to create a new file "projects/output.txt" with O_WRONLY | O_CREAT | O_TRUNC
//    Pass 0644 as the mode (standard file permissions)
// 7. Use write() to write some text into it
// 8. close() it
//
// Goal: understand that file I/O, sockets, and stdin/stdout are all
// just file descriptors — the same read/write interface works for all of them.
#include <fcntl.h>

int main() {
    write(1, "Hello from write()\n", 20);
    int data_fd = open("projects/data.txt", O_RDONLY);
    off_t size = lseek(data_fd, 0, SEEK_END);
    lseek(data_fd, 0, SEEK_SET);
    char* buf = malloc(size + 1);
    ssize_t bytes = read(data_fd, buf, size);
    write(1, buf, bytes);
    close(data_fd);
    free(buf);
    int output_fd = open("projects/output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(output_fd, "writing from main() to output.txt\n", sizeof("writing from main() to output.txt\n"));
    close(output_fd);

    return 0;
}