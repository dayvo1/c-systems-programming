#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Exercise 13 — Persistent Server (accept loop + echo)
//
// Concept: Your ex11 server handled one connection then quit.
// Real servers run forever, handling connections one after another.
// The fix is simple — wrap accept() in a while(1) loop.
//
// This server will also ECHO back whatever the client sends.
// That means after accepting, you recv() from the client and send() it back.
// Echo servers are the "hello world" of networking.
//
// recv() returns:
//    >0  — bytes received, data is in the buffer
//     0  — client disconnected
//    -1  — error
//
// Tasks:
// 1. Set up the server socket the same way as ex11 (socket, bind, listen)
// 2. Wrap accept() in a while(1) loop
// 3. Inside the loop, recv() from the client in another loop until recv returns 0
// 4. Echo each chunk back with send()
// 5. Print each message to the terminal so you can see what's coming in
// 6. close() the client fd after the inner loop, then go back to waiting
//
// To test: run bin/ex13 in one terminal, then in another:
//   nc localhost 8080
// Type messages and press enter — you should see them echoed back.
// Press Ctrl+C to quit nc, the server should keep running and accept new connections.
//
// Goal: understand the persistent server loop and how recv return value
// signals connection state.


int main() {

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    int port = 8080;
    server_sockaddr.sin_port = htons(port);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;

    int binded = bind(server_socket, (struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr));
    if(binded == -1) { return -1; }

    int listening = listen(server_socket, 1);

    struct sockaddr_in client_sockaddr;
    socklen_t client_sockaddr_len = sizeof(client_sockaddr);

    char buf[1024];

    while(1) {
        int client_fd = accept(server_socket, (struct sockaddr*)&client_sockaddr, &client_sockaddr_len);
        ssize_t bytes; 
        char response[1100];
        while((bytes = recv(client_fd, buf, sizeof(buf), 0)) > 0) {
            printf("sent from client: %s", buf);
            snprintf(response, sizeof(response), "Sent back from server: %s\n", buf);
            ssize_t send_back = send(client_fd, response, strlen(response), 0);
        }
        int closed = close(client_fd);
        if(closed == -1) { return -1; }
    }

    return 0;
}