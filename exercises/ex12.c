#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Exercise 12 — TCP Client
//
// Concept: In ex11 you built the server side. Now you'll build the client.
// A client is simpler — no bind, no listen, no accept.
// It just creates a socket and calls connect() to reach the server.
//
// Client lifecycle:
//   1. socket()   — create the socket
//   2. connect()  — connect to the server's IP and port
//   3. recv()     — receive data from the server
//   4. close()    — close the socket
//
// connect() takes the same struct sockaddr_in as bind() but this time
// you fill in the SERVER's address, not your own.
//
// inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)
//   — converts an IP string to binary form and stores it in sin_addr
//   — "pton" = "presentation to network"
//
// Tasks:
// 1. Create a TCP socket
// 2. Fill in a sockaddr_in with the server address: 127.0.0.1, port 8080
//    Use inet_pton to set the IP address
// 3. connect() to the server — check for failure
// 4. recv() the server's message into a buffer and print it
// 5. close() the socket
//
// To test: run bin/ex11 in one terminal, then run bin/ex12 in another.
// ex12 should print "Hello from server".
//
// Goal: understand the client side of the TCP connection and how
// connect() mirrors the server's accept().


int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_sockaddr;
    client_sockaddr.sin_family = AF_INET;
    int port = 8080;
    client_sockaddr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1",&client_sockaddr.sin_addr);

    int connected = connect(client_socket, (struct sockaddr *)&client_sockaddr, sizeof(client_sockaddr));
    if(connected == -1) {return -1;}

    char buf[1024];
    ssize_t recieved = recv(client_socket, buf, sizeof(buf), 0);
    if(recieved == -1) { return -1;}

    printf("Number of bytes recieved: %zd\n" , recieved);
    printf("Message recieved: %s\n", buf);

    int closed_client_socket = close(client_socket);
    if(closed_client_socket == -1) { return -1;}

    return 0;
}