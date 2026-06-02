#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Exercise 11 — TCP Server
//
// Concept: A socket is a file descriptor for network communication.
// Building a TCP server requires 5 steps in order:
//
//   1. socket()  — create the socket (like opening a file)
//   2. bind()    — attach it to an IP address and port
//   3. listen()  — mark it as a passive socket waiting for connections
//   4. accept()  — block until a client connects, returns a new fd
//   5. send/recv — communicate with the client
//   6. close()   — close the file descriptors when done
//
// Key structures:
//   struct sockaddr_in  — holds IP address and port
//     .sin_family       — address family: AF_INET (IPv4)
//     .sin_port         — port in network byte order: htons(port)
//     .sin_addr.s_addr  — IP address: INADDR_ANY means accept any interface
//
// htons() — "host to network short" — converts port to big-endian byte order
// Network byte order is always big-endian regardless of your machine.
//
// Tasks:
// 1. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0)
//    Check for failure (returns -1)
// 2. Fill in a struct sockaddr_in for port 8080, INADDR_ANY
// 3. bind() the socket to that address — check for failure
// 4. listen() with a backlog of 1 — check for failure
// 5. Print "waiting for connection..." then call accept()
// 6. Once accepted, send the message "Hello from server\n" using send()
// 7. close() both the client fd and the server fd
//
// To test: run ./ex11 in one terminal, then in another run:
//   nc localhost 8080
// You should see the message appear in the nc terminal.
//
// Goal: understand the server socket lifecycle and how a connection is established.


int main() {
    
   int s = socket(AF_INET, SOCK_STREAM, 0);
   if(s == -1) { return -1;}

   int port = 8080;
   struct sockaddr_in sa;
   sa.sin_family = AF_INET;
   sa.sin_port = htons(port);
   sa.sin_addr.s_addr = INADDR_ANY;

   int b = bind(s, (struct sockaddr *)&sa, sizeof(sa));
   if(b == -1) {return -1;}

   int li = listen(s, 1);
   if(li == -1) { return -1;}

   printf("Waiting for connection...\n");

   struct sockaddr_in client_addr;
   socklen_t client_size = sizeof(client_addr);
   int client_fd = accept(s, (struct sockaddr *)&client_addr, &client_size);

   ssize_t sending = send(client_fd,"Hello from server\n", sizeof("Hello from server\n"), 0);
   if(sending == -1){return -1;}
   printf("Number of bytes sent: %zd\n", sending);

   int closed_sa = close(s);
   if(closed_sa == -1) { return -1;}
   int closed_client_fs = close(client_fd);
   if(closed_client_fs == -1) { return -1;}

   return 0;

}