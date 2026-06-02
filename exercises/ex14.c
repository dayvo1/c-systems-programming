#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Exercise 14 — HTTP Server (basics)
//
// Concept: HTTP is just a text protocol on top of TCP.
// When a browser connects, it sends a plain text request like:
//
//   GET / HTTP/1.1\r\n
//   Host: localhost\r\n
//   \r\n
//
// Your server reads that request, then sends back a plain text response:
//
//   HTTP/1.1 200 OK\r\n
//   Content-Type: text/html\r\n
//   Content-Length: 13\r\n
//   \r\n
//   Hello, World!
//
// The blank line (\r\n\r\n) separates headers from the body.
// Content-Length tells the browser how many bytes the body is.
// Without it the browser won't know when the response ends.
//
// Tasks:
// 1. Set up a persistent TCP server on port 8080 (same as ex13)
// 2. When a client connects, recv() the HTTP request into a buffer
// 3. Print the raw request to the terminal so you can see what the browser sends
// 4. Send back a valid HTTP response with:
//    - Status line: "HTTP/1.1 200 OK\r\n"
//    - Header: "Content-Type: text/html\r\n"
//    - Content-Length header with the correct body length
//    - Blank line: "\r\n"
//    - Body: "<h1>Hello from my server!</h1>"
// 5. close() the client fd after sending
//
// To test: run bin/ex14 then open http://localhost:8080 in your browser.
// You should see "Hello from my server!" rendered as a heading.
//
// Goal: understand that HTTP is just text over TCP — no magic, just a format.


int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = 8080;
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;

    int server_binded = bind(server_socket, (struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr));
    if(server_binded == -1) { return -1;}

    int server_listening = listen(server_socket, 1);
    if(server_listening == -1) { return -1;}


    struct sockaddr_in client_sockaddr;
    socklen_t client_sockaddr_size = sizeof(client_sockaddr);
    ssize_t bytes_recieved;
    ssize_t bytes_sent;
    char buf[1024];
    char response[1100];
    char welcome[100] = "<h1>Hello from my server!</h1>";

    while(1) {
        int client_fd = accept(server_socket, (struct sockaddr*)&client_sockaddr, &client_sockaddr_size);
        bytes_recieved = recv(client_fd, buf, sizeof(buf),0);
        printf("Message from client: %s", buf);
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n<h1>Hello from my server!</h1>", strlen(welcome));
        bytes_sent = send(client_fd, response, strlen(response), 0);
        printf("bytes sent: %zd", bytes_sent);

        int closed_client = close(client_fd);
        if(closed_client == -1) { return -1; }
    }
    
    return 0;
}