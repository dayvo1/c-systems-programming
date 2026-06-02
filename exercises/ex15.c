#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Exercise 15 — HTTP Routing
//
// Concept: Real web servers don't serve the same response for every request.
// They look at the request path and send different responses.
//
// The first line of an HTTP request tells you everything:
//   "GET /about HTTP/1.1\r\n..."
//    ^^^  ^^^^^^
//    method  path
//
// You can use strstr() to check if a string contains a substring:
//   if (strstr(buf, "GET /about")) { ... }
//
// Routes to implement:
//   GET /        → "<h1>Home Page</h1>"
//   GET /about   → "<h1>About Page</h1>"
//   anything else → 404 response:
//                   "HTTP/1.1 404 Not Found\r\n..."
//                   "<h1>404 - Not Found</h1>"
//
// Tasks:
// 1. Set up the server the same way as ex14
// 2. After recv(), inspect the request buffer to determine the path
// 3. Use if/else with strstr() to send the right response for each route
// 4. For unknown paths send a proper 404 response
//
// To test: run bin/ex15 then visit in your browser:
//   http://localhost:8080/
//   http://localhost:8080/about
//   http://localhost:8080/anything
//
// Goal: understand how HTTP routing works at the raw socket level.


int main() {

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    int port = 8080;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int server_binded = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(server_binded == -1) { return -1;}

    int server_listening = listen(server_socket, 1);
    if(server_listening == -1) { return -1;}

   struct sockaddr_in client_addr;
   socklen_t client_addr_length = sizeof(client_addr);
   char buf[1024];
   char response[1024];
   char welcome[100] = "<h1> Hello from Home page of server!</h1>";
   char about[100] = "<h1> Hello from About page of server!</h1>";
   char fOf[100] = "<h1>404 - Not Found</h1>";

   while(1) {
        int client_fd = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_length);
        int recieved = recv(client_fd, buf, sizeof(buf), 0);
        printf("Message from client: %s", buf);

        if (strstr(buf, "GET / ")) {
            snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n%s", strlen(welcome), welcome);
            send(client_fd, response, strlen(response), 0);
        }
        else if (strstr(buf, "GET /about")) {
            snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n%s", strlen(about), about);
            send(client_fd, response, strlen(response), 0);
        } else {
            snprintf(response, sizeof(response), "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n%s", strlen(fOf), fOf);
            send(client_fd, response, strlen(response), 0);
        }

        int closed_client = close(client_fd);
        if(closed_client == -1) { return -1; }
   }

    return 0;
}