#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// Exercise 17 — Fork: Handling Multiple Clients Simultaneously
//
// Concept: Your servers so far handle one client at a time. While you're
// serving one client, all others wait. Real servers handle many clients
// simultaneously.
//
// The simplest way to do this in C is fork() — it creates a copy of your
// process. The child handles the client, the parent goes back to accept().
//
// fork() returns:
//   >0  — you are the parent, return value is the child's PID
//    0  — you are the child
//   -1  — error
//
// After fork(), both parent and child have copies of all open file descriptors.
// The child should close server_socket (it doesn't need to accept new connections).
// The parent should close client_fd (it's the child's job to handle it).
//
//   while(1) {
//       int client_fd = accept(...);
//       pid_t pid = fork();
//       if (pid == 0) {
//           // child: handle client, then exit
//           close(server_socket);
//           // ... do work ...
//           close(client_fd);
//           exit(0);
//       } else {
//           // parent: close client_fd and loop back to accept
//           close(client_fd);
//       }
//   }
//
// Tasks:
// 1. Set up the server the same way as previous exercises (port 8080)
// 2. After accept(), fork()
// 3. Child process: send "Hello from child process!\n" to the client, then exit
// 4. Parent process: close client_fd and loop back to accept
// 5. Test with two nc connections simultaneously — both should get a response
//
// To test:
//   Terminal 1: bin/ex17
//   Terminal 2: nc localhost 8080
//   Terminal 3: nc localhost 8080  (while terminal 2 is still connected)
//
// Goal: understand how fork() enables concurrent connections and why
// parent/child need to close the right file descriptors.


int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    const int port = 8080;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        return -1;
    }

    if(listen(server_socket, 1) == -1) {
        return -1;
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    signal(SIGCHLD, SIG_IGN);
    while(1) {
        int client_fd = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        pid_t pid = fork();
        
        if(pid == -1) {
            send(client_fd, "Error", sizeof("Error"), 0);
        }
        else if(pid == 0) {
            close(server_socket);
            send(client_fd, "Hello from child process!", sizeof("Hello from child process!"), 0);
            sleep(10); 
            close(client_fd);
            exit(0);
        } else {
            close(client_fd);
        }
    }
    return 0;
}